#include "EffectRuntime.h"
#include "Error.h"
#include "Buffer.h"
#include "pixelpart-runtime/common/Math.h"
#include "pixelpart-runtime/common/Curve.h"
#include "pixelpart-runtime/common/Transform.h"
#include "pixelpart-runtime/effect/Effect.h"
#include "pixelpart-runtime/effect/Node.h"
#include "pixelpart-runtime/effect/ParticleEmitter.h"
#include "pixelpart-runtime/effect/ParticleType.h"
#include "pixelpart-runtime/effect/EffectRuntimeContext.h"
#include "pixelpart-runtime/engine/MultiThreadedEffectEngine.h"
#include "pixelpart-runtime/engine/SingleThreadedEffectEngine.h"
#include "pixelpart-runtime/engine/DefaultParticleGenerator.h"
#include "pixelpart-runtime/engine/DefaultParticleModifier.h"
#include "pixelpart-runtime/engine/ParticleCollection.h"
#include "pixelpart-runtime/vertex/VertexFormat.h"
#include "pixelpart-runtime/vertex/VertexAttribute.h"
#include <string>
#include <algorithm>
#include <exception>

namespace pixelpart_gms2 {
#ifdef PIXELPART_RUNTIME_MULTITHREADING
std::shared_ptr<pixelpart::ThreadPool> threadPool;
#endif

std::mt19937 rng;

std::string effectRuntimePtrString = "";
}

extern "C" {
GMS2_EXPORT pixelpart_gms2::const_string GMS2_API pixelpart_load_effect(pixelpart_gms2::string data, pixelpart_gms2::real size, pixelpart_gms2::real particleCapacity) {
	if(!data || size <= 0) {
		pixelpart_gms2::lastError = "Effect data is empty";
		pixelpart_gms2::effectRuntimePtrString = pixelpart_gms2::nullPointerString;

		return pixelpart_gms2::effectRuntimePtrString.c_str();
	}

	try {
		pixelpart_gms2::EffectRuntime* effectRuntime = new pixelpart_gms2::EffectRuntime();
		effectRuntime->effectAsset = pixelpart::deserializeEffectAsset(data, static_cast<std::size_t>(size));

#ifdef PIXELPART_RUNTIME_MULTITHREADING
		effectRuntime->effectEngine = std::make_unique<pixelpart::MultiThreadedEffectEngine>(
			effectRuntime->effectAsset.effect(),
			std::make_shared<pixelpart::DefaultParticleGenerator>(),
			std::make_shared<pixelpart::DefaultParticleModifier>(),
			pixelpart_gms2::threadPool,
			static_cast<std::uint32_t>(std::max(particleCapacity, 1.0)));
#else
		effectRuntime->effectEngine = std::make_unique<pixelpart::SingleThreadedEffectEngine>(
			effectRuntime->effectAsset.effect(),
			std::make_shared<pixelpart::DefaultParticleGenerator>(),
			std::make_shared<pixelpart::DefaultParticleModifier>(),
			static_cast<std::uint32_t>(std::max(particleCapacity, 1.0)));
#endif

		effectRuntime->effectAsset.effect().applyInputs();

		std::size_t vertexStride = sizeof(float) * 6 + sizeof(std::uint8_t) * 4;

		pixelpart::VertexFormat vertexBasedVertexFormat({
				pixelpart::VertexAttribute(pixelpart::VertexAttributeUsage::position2d, pixelpart::VertexDataGenerationMode::vertex, pixelpart::VertexDataType::type_float, 0, 0, vertexStride),
				pixelpart::VertexAttribute(pixelpart::VertexAttributeUsage::color, pixelpart::VertexDataGenerationMode::vertex, pixelpart::VertexDataType::type_uint8, 0, sizeof(float) * 2, vertexStride),
				pixelpart::VertexAttribute(pixelpart::VertexAttributeUsage::texture_coord, pixelpart::VertexDataGenerationMode::vertex, pixelpart::VertexDataType::type_float, 0, sizeof(float) * 2 + sizeof(std::uint8_t) * 4, vertexStride),
				pixelpart::VertexAttribute(pixelpart::VertexAttributeUsage::life, pixelpart::VertexDataGenerationMode::vertex, pixelpart::VertexDataType::type_float, 0, sizeof(float) * 4 + sizeof(std::uint8_t) * 4, vertexStride),
				pixelpart::VertexAttribute(pixelpart::VertexAttributeUsage::id, pixelpart::VertexDataGenerationMode::vertex, pixelpart::VertexDataType::type_float, 0, sizeof(float) * 5 + sizeof(std::uint8_t) * 4, vertexStride)
			},
			pixelpart::VertexWindingOrder::ccw);

		for(const pixelpart::ParticleEmissionPair& emissionPair : effectRuntime->effectAsset.effect().particleEmissionPairs()) {
			const pixelpart::ParticleType& particleType = effectRuntime->effectAsset.effect().particleTypes().at(emissionPair.typeId);

			pixelpart::VertexFormat vertexFormat;
			switch(particleType.renderer()) {
				case pixelpart::ParticleRendererType::sprite:
				case pixelpart::ParticleRendererType::trail:
					vertexFormat = vertexBasedVertexFormat;
					break;
				default:
					break;
			}

			effectRuntime->vertexGenerators[emissionPair] = std::make_unique<pixelpart::ParticleVertexGenerator>(
				effectRuntime->effectAsset.effect(), emissionPair.emitterId, emissionPair.typeId,
				vertexFormat);
		}

		pixelpart_gms2::effectRuntimePtrString = pixelpart_gms2::toBufferString(effectRuntime);

		return pixelpart_gms2::effectRuntimePtrString.c_str();
	}
	catch(const std::exception& e) {
		pixelpart_gms2::lastError = std::string(e.what());
	}

	pixelpart_gms2::effectRuntimePtrString = pixelpart_gms2::nullPointerString;

	return pixelpart_gms2::effectRuntimePtrString.c_str();
}

GMS2_EXPORT pixelpart_gms2::real GMS2_API pixelpart_delete_effect(pixelpart_gms2::string runtimePtr) {
	pixelpart_gms2::EffectRuntime* effectRuntime = reinterpret_cast<pixelpart_gms2::EffectRuntime*>(runtimePtr);
	if(!effectRuntime) {
		pixelpart_gms2::lastError = pixelpart_gms2::invalidEffectRuntimeError;
		return -1;
	}

	delete effectRuntime;

	return 1;
}

GMS2_EXPORT pixelpart_gms2::real GMS2_API pixelpart_set_effect_scale(pixelpart_gms2::string runtimePtr, pixelpart_gms2::real scaleX, pixelpart_gms2::real scaleY) {
	pixelpart_gms2::EffectRuntime* effectRuntime = reinterpret_cast<pixelpart_gms2::EffectRuntime*>(runtimePtr);
	if(!effectRuntime) {
		pixelpart_gms2::lastError = pixelpart_gms2::invalidEffectRuntimeError;
		return -1;
	}

	effectRuntime->effectScale = pixelpart::float3_t(scaleX, scaleY, 1.0);

	return 1;
}

GMS2_EXPORT pixelpart_gms2::real GMS2_API pixelpart_set_effect_transform(pixelpart_gms2::string runtimePtr, pixelpart_gms2::real x, pixelpart_gms2::real y) {
	pixelpart_gms2::EffectRuntime* effectRuntime = reinterpret_cast<pixelpart_gms2::EffectRuntime*>(runtimePtr);
	if(!effectRuntime) {
		pixelpart_gms2::lastError = pixelpart_gms2::invalidEffectRuntimeError;
		return -1;
	}

	pixelpart::Transform transform(
		pixelpart::float3_t(x, y, 0),
		pixelpart::float3_t(0),
		pixelpart::float3_t(1));

	for(const std::unique_ptr<pixelpart::Node>& node : effectRuntime->effectAsset.effect().sceneGraph().nodes()) {
		if(node->parentId()) {
			continue;
		}

		node->position().keyframes({ pixelpart::Curve<pixelpart::float3_t>::Point{ 0.0,
			transform.position() / effectRuntime->effectScale
		} });
		node->rotation().keyframes({ pixelpart::Curve<pixelpart::float3_t>::Point{ 0.0,
			transform.rotation()
		} });
		node->scale().keyframes({ pixelpart::Curve<pixelpart::float3_t>::Point{ 0.0,
			transform.scale()
		} });
	}

	return 1;
}

GMS2_EXPORT pixelpart_gms2::real GMS2_API pixelpart_advance_effect(pixelpart_gms2::string runtimePtr, pixelpart_gms2::string paramBufferPtr) {
	pixelpart_gms2::EffectRuntime* effectRuntime = reinterpret_cast<pixelpart_gms2::EffectRuntime*>(runtimePtr);
	if(!effectRuntime) {
		pixelpart_gms2::lastError = pixelpart_gms2::invalidEffectRuntimeError;
		return -1;
	}

	pixelpart_gms2::Buffer paramBuffer(paramBufferPtr);
	pixelpart::float_t dt = std::max(paramBuffer.read<pixelpart_gms2::real>(), 0.0);
	bool loop = paramBuffer.read<pixelpart_gms2::real>() > 0.5;
	pixelpart::float_t loopTime = std::max(paramBuffer.read<pixelpart_gms2::real>(), 0.0);
	pixelpart::float_t speed = std::max(paramBuffer.read<pixelpart_gms2::real>(), 0.0);
	pixelpart::float_t timeStep = std::max(paramBuffer.read<pixelpart_gms2::real>() * speed, 0.001);
	std::uint32_t seed = static_cast<std::uint32_t>(std::max(paramBuffer.read<pixelpart_gms2::real>(), 0.0));
	bool randomSeed = paramBuffer.read<pixelpart_gms2::real>() > 0.5;

	effectRuntime->simulationTime += dt * speed;

	while(effectRuntime->simulationTime > timeStep) {
		effectRuntime->simulationTime -= timeStep;
		effectRuntime->effectEngine->advance(timeStep);

		if(loop && effectRuntime->effectEngine->context().time() > loopTime) {
			effectRuntime->effectEngine->restart();

			if(!randomSeed) {
				effectRuntime->effectEngine->reseed(seed);
			}
		}
	}

	return 1;
}

GMS2_EXPORT pixelpart_gms2::real GMS2_API pixelpart_restart_effect(pixelpart_gms2::string runtimePtr, pixelpart_gms2::real clear) {
	pixelpart_gms2::EffectRuntime* effectRuntime = reinterpret_cast<pixelpart_gms2::EffectRuntime*>(runtimePtr);
	if(!effectRuntime) {
		pixelpart_gms2::lastError = pixelpart_gms2::invalidEffectRuntimeError;
		return -1;
	}

	if(clear) {
		effectRuntime->effectEngine->clearParticles();
	}

	effectRuntime->effectEngine->restart();

	return 1;
}

GMS2_EXPORT pixelpart_gms2::real GMS2_API pixelpart_reseed_effect(pixelpart_gms2::string runtimePtr, pixelpart_gms2::real seed) {
	pixelpart_gms2::EffectRuntime* effectRuntime = reinterpret_cast<pixelpart_gms2::EffectRuntime*>(runtimePtr);
	if(!effectRuntime) {
		pixelpart_gms2::lastError = pixelpart_gms2::invalidEffectRuntimeError;
		return -1;
	}

	effectRuntime->effectEngine->reseed(static_cast<std::uint32_t>(std::max(seed, 0.0)));

	return 1;
}

GMS2_EXPORT pixelpart_gms2::real GMS2_API pixelpart_get_effect_time(pixelpart_gms2::string runtimePtr) {
	pixelpart_gms2::EffectRuntime* effectRuntime = reinterpret_cast<pixelpart_gms2::EffectRuntime*>(runtimePtr);
	if(!effectRuntime) {
		pixelpart_gms2::lastError = pixelpart_gms2::invalidEffectRuntimeError;
		return -1;
	}

	return effectRuntime->effectEngine->context().time();
}

GMS2_EXPORT pixelpart_gms2::real GMS2_API pixelpart_is_effect_finished(pixelpart_gms2::string runtimePtr) {
	pixelpart_gms2::EffectRuntime* effectRuntime = reinterpret_cast<pixelpart_gms2::EffectRuntime*>(runtimePtr);
	if(!effectRuntime) {
		pixelpart_gms2::lastError = pixelpart_gms2::invalidEffectRuntimeError;
		return -1;
	}

	const pixelpart::Effect& effect = effectRuntime->effectAsset.effect();
	pixelpart::float_t time = effectRuntime->effectEngine->context().time();

	for(const auto* particleEmitter : effect.sceneGraph().nodesWithType<pixelpart::ParticleEmitter>()) {
		if(!particleEmitter->primary()) {
			continue;
		}

		if(particleEmitter->active(effectRuntime->effectEngine->context()) || particleEmitter->repeat() ||
			time < particleEmitter->start() + particleEmitter->duration()) {
			return 0;
		}
	}

	for(const auto& [emissionPair, particleCollection] : effectRuntime->effectEngine->state().particleCollections()) {
		if(particleCollection.count() > 0) {
			return 0;
		}
	}

	return 1;
}

GMS2_EXPORT pixelpart_gms2::real GMS2_API pixelpart_is_effect_3d(pixelpart_gms2::string runtimePtr) {
	pixelpart_gms2::EffectRuntime* effectRuntime = reinterpret_cast<pixelpart_gms2::EffectRuntime*>(runtimePtr);
	if(!effectRuntime) {
		pixelpart_gms2::lastError = pixelpart_gms2::invalidEffectRuntimeError;
		return -1;
	}

	return effectRuntime->effectAsset.effect().is3d() ? 1.0 : 0.0;
}

GMS2_EXPORT pixelpart_gms2::real GMS2_API pixelpart_get_effect_node_count(pixelpart_gms2::string runtimePtr) {
	pixelpart_gms2::EffectRuntime* effectRuntime = reinterpret_cast<pixelpart_gms2::EffectRuntime*>(runtimePtr);
	if(!effectRuntime) {
		pixelpart_gms2::lastError = pixelpart_gms2::invalidEffectRuntimeError;
		return -1;
	}

	return static_cast<pixelpart_gms2::real>(effectRuntime->effectAsset.effect().sceneGraph().count());
}

GMS2_EXPORT pixelpart_gms2::real GMS2_API pixelpart_get_effect_particle_type_count(pixelpart_gms2::string runtimePtr) {
	pixelpart_gms2::EffectRuntime* effectRuntime = reinterpret_cast<pixelpart_gms2::EffectRuntime*>(runtimePtr);
	if(!effectRuntime) {
		pixelpart_gms2::lastError = pixelpart_gms2::invalidEffectRuntimeError;
		return -1;
	}

	return static_cast<pixelpart_gms2::real>(effectRuntime->effectAsset.effect().particleTypes().count());
}

GMS2_EXPORT pixelpart_gms2::real GMS2_API pixelpart_get_effect_particle_runtime_instance_count(pixelpart_gms2::string runtimePtr) {
	pixelpart_gms2::EffectRuntime* effectRuntime = reinterpret_cast<pixelpart_gms2::EffectRuntime*>(runtimePtr);
	if(!effectRuntime) {
		pixelpart_gms2::lastError = pixelpart_gms2::invalidEffectRuntimeError;
		return -1;
	}

	return static_cast<pixelpart_gms2::real>(effectRuntime->effectAsset.effect().particleEmissionPairs().size());
}

GMS2_EXPORT pixelpart_gms2::real GMS2_API pixelpart_get_effect_particle_runtime_instances(pixelpart_gms2::string runtimePtr, pixelpart_gms2::string instanceBufferPtr) {
	pixelpart_gms2::EffectRuntime* effectRuntime = reinterpret_cast<pixelpart_gms2::EffectRuntime*>(runtimePtr);
	if(!effectRuntime) {
		pixelpart_gms2::lastError = pixelpart_gms2::invalidEffectRuntimeError;
		return -1;
	}

	pixelpart_gms2::Buffer instanceBuffer = pixelpart_gms2::Buffer(instanceBufferPtr);

	for(pixelpart::ParticleEmissionPair emissionPair : effectRuntime->effectAsset.effect().particleEmissionPairs()) {
		instanceBuffer.write<std::uint32_t>(emissionPair.emitterId.value());
		instanceBuffer.write<std::uint32_t>(emissionPair.typeId.value());
	}

	return 1;
}

GMS2_EXPORT pixelpart_gms2::real GMS2_API pixelpart_get_effect_particle_count(pixelpart_gms2::string runtimePtr, pixelpart_gms2::real particleEmitterId, pixelpart_gms2::real particleTypeId) {
	pixelpart_gms2::EffectRuntime* effectRuntime = reinterpret_cast<pixelpart_gms2::EffectRuntime*>(runtimePtr);
	if(!effectRuntime) {
		pixelpart_gms2::lastError = pixelpart_gms2::invalidEffectRuntimeError;
		return -1;
	}

	const pixelpart::ParticleCollection* particleCollection = effectRuntime->effectEngine->state().particleCollection(
		pixelpart::id_t(particleEmitterId),
		pixelpart::id_t(particleTypeId));

	return particleCollection->count();
}

GMS2_EXPORT pixelpart_gms2::real GMS2_API pixelpart_spawn_particles(pixelpart_gms2::string runtimePtr, pixelpart_gms2::real particleEmitterId, pixelpart_gms2::real particleTypeId, pixelpart_gms2::real count) {
	pixelpart_gms2::EffectRuntime* effectRuntime = reinterpret_cast<pixelpart_gms2::EffectRuntime*>(runtimePtr);
	if(!effectRuntime) {
		pixelpart_gms2::lastError = pixelpart_gms2::invalidEffectRuntimeError;
		return -1;
	}
	else if(count <= 0) {
		return 0;
	}

	effectRuntime->effectEngine->generateParticles(
		static_cast<std::uint32_t>(count),
		pixelpart::id_t(particleEmitterId),
		pixelpart::id_t(particleTypeId),
		pixelpart::EffectRuntimeContext());

	return 1;
}
}
