#include "EffectRuntime.h"
#include "Error.h"
#include "Buffer.h"
#include "pixelpart-runtime/types/Types.h"
#include "pixelpart-runtime/effect/Curve.h"
#include "pixelpart-runtime/effect/Transform.h"
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

namespace pixelpart_gm {
std::shared_ptr<pixelpart::ThreadPool> threadPool;
std::mt19937 rng;

std::string effectResourcePtrString = "";
std::string effectRuntimePtrString = "";
}

extern "C" {
GM_EXPORT pixelpart_gm::const_string GM_API pixelpart_load_effect_resource(pixelpart_gm::string data, pixelpart_gm::real size) {
	if(!data || size <= 0) {
		pixelpart_gm::lastError = "Effect data is empty";
		pixelpart_gm::effectResourcePtrString = "";

		return pixelpart_gm::effectResourcePtrString.c_str();
	}

	try {
		pixelpart_gm::EffectResource* effectResource = new pixelpart_gm::EffectResource();
		effectResource->effectAsset = pixelpart::deserializeEffectAsset(data, static_cast<std::size_t>(size));

		pixelpart_gm::effectResourcePtrString = pixelpart_gm::ptrToString(effectResource);

		return pixelpart_gm::effectResourcePtrString.c_str();
	}
	catch(const std::exception& e) {
		pixelpart_gm::lastError = std::string(e.what());
	}

	pixelpart_gm::effectResourcePtrString = "";

	return pixelpart_gm::effectResourcePtrString.c_str();
}

GM_EXPORT pixelpart_gm::real GM_API pixelpart_delete_effect_resource(pixelpart_gm::string resourcePtr) {
	pixelpart_gm::EffectResource* effectResource = pixelpart_gm::parsePtr<pixelpart_gm::EffectResource>(resourcePtr);
	if(!effectResource) {
		pixelpart_gm::lastError = pixelpart_gm::invalidEffectResourceError;
		return -1;
	}

	delete effectResource;

	return 1;
}

GM_EXPORT pixelpart_gm::const_string GM_API pixelpart_create_effect(pixelpart_gm::string resourcePtr) {
	pixelpart_gm::EffectResource* effectResource = pixelpart_gm::parsePtr<pixelpart_gm::EffectResource>(resourcePtr);
	if(!effectResource) {
		pixelpart_gm::lastError = pixelpart_gm::invalidEffectResourceError;
		pixelpart_gm::effectRuntimePtrString = "";

		return pixelpart_gm::effectRuntimePtrString.c_str();
	}

	try {
		pixelpart_gm::EffectRuntime* effectRuntime = new pixelpart_gm::EffectRuntime();
		effectRuntime->effectAsset = effectResource->effectAsset;

#ifdef PIXELPART_RUNTIME_MULTITHREADING
		effectRuntime->effectEngine = std::make_unique<pixelpart::MultiThreadedEffectEngine>(
			effectRuntime->effectAsset.effect(),
			std::make_shared<pixelpart::DefaultParticleGenerator>(),
			std::make_shared<pixelpart::DefaultParticleModifier>(),
			pixelpart_gm::threadPool);
#else
		effectRuntime->effectEngine = std::make_unique<pixelpart::SingleThreadedEffectEngine>(
			effectRuntime->effectAsset.effect(),
			std::make_shared<pixelpart::DefaultParticleGenerator>(),
			std::make_shared<pixelpart::DefaultParticleModifier>());
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
				vertexFormat, pixelpart_gm::threadPool);
		}

		pixelpart_gm::effectRuntimePtrString = pixelpart_gm::ptrToString(effectRuntime);

		return pixelpart_gm::effectRuntimePtrString.c_str();
	}
	catch(const std::exception& e) {
		pixelpart_gm::lastError = std::string(e.what());
	}

	pixelpart_gm::effectRuntimePtrString = "";

	return pixelpart_gm::effectRuntimePtrString.c_str();
}

GM_EXPORT pixelpart_gm::real GM_API pixelpart_delete_effect(pixelpart_gm::string runtimePtr) {
	pixelpart_gm::EffectRuntime* effectRuntime = pixelpart_gm::parsePtr<pixelpart_gm::EffectRuntime>(runtimePtr);
	if(!effectRuntime) {
		pixelpart_gm::lastError = pixelpart_gm::invalidEffectRuntimeError;
		return -1;
	}

	delete effectRuntime;

	return 1;
}

GM_EXPORT pixelpart_gm::real GM_API pixelpart_set_effect_scale(pixelpart_gm::string runtimePtr, pixelpart_gm::real scaleX, pixelpart_gm::real scaleY) {
	pixelpart_gm::EffectRuntime* effectRuntime = pixelpart_gm::parsePtr<pixelpart_gm::EffectRuntime>(runtimePtr);
	if(!effectRuntime) {
		pixelpart_gm::lastError = pixelpart_gm::invalidEffectRuntimeError;
		return -1;
	}

	effectRuntime->effectScale = pixelpart::float3_t(scaleX, scaleY, 1.0);

	return 1;
}

GM_EXPORT pixelpart_gm::real GM_API pixelpart_set_effect_transform(pixelpart_gm::string runtimePtr, pixelpart_gm::real x, pixelpart_gm::real y) {
	pixelpart_gm::EffectRuntime* effectRuntime = pixelpart_gm::parsePtr<pixelpart_gm::EffectRuntime>(runtimePtr);
	if(!effectRuntime) {
		pixelpart_gm::lastError = pixelpart_gm::invalidEffectRuntimeError;
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

GM_EXPORT pixelpart_gm::real GM_API pixelpart_advance_effect(pixelpart_gm::string runtimePtr, pixelpart_gm::string paramBufferPtr) {
	pixelpart_gm::EffectRuntime* effectRuntime = pixelpart_gm::parsePtr<pixelpart_gm::EffectRuntime>(runtimePtr);
	if(!effectRuntime) {
		pixelpart_gm::lastError = pixelpart_gm::invalidEffectRuntimeError;
		return -1;
	}

	pixelpart_gm::Buffer paramBuffer(paramBufferPtr);
	pixelpart::float_t dt = std::max(paramBuffer.read<pixelpart_gm::real>(), 0.0);
	bool loop = paramBuffer.read<pixelpart_gm::real>() > 0.5;
	pixelpart::float_t loopTime = std::max(paramBuffer.read<pixelpart_gm::real>(), 0.0);
	pixelpart::float_t speed = std::max(paramBuffer.read<pixelpart_gm::real>(), 0.0);
	pixelpart::float_t timeStep = std::max(paramBuffer.read<pixelpart_gm::real>() * speed, 0.001);
	std::uint32_t seed = static_cast<std::uint32_t>(std::max(paramBuffer.read<pixelpart_gm::real>(), 0.0));
	bool randomSeed = paramBuffer.read<pixelpart_gm::real>() > 0.5;

	effectRuntime->invokedEventIds.clear();

	effectRuntime->simulationTime += dt * speed;

	while(effectRuntime->simulationTime > timeStep) {
		effectRuntime->simulationTime -= timeStep;
		effectRuntime->effectEngine->advance(timeStep);

		for(pixelpart::id_t eventId : effectRuntime->effectEngine->context().invokedEvents()) {
			effectRuntime->invokedEventIds.push_back(eventId);
		}

		if(loop && effectRuntime->effectEngine->context().time() > loopTime) {
			effectRuntime->effectEngine->restart();

			if(!randomSeed) {
				effectRuntime->effectEngine->reseed(seed);
			}
		}
	}

	return 1;
}

GM_EXPORT pixelpart_gm::real GM_API pixelpart_restart_effect(pixelpart_gm::string runtimePtr, pixelpart_gm::real clear) {
	pixelpart_gm::EffectRuntime* effectRuntime = pixelpart_gm::parsePtr<pixelpart_gm::EffectRuntime>(runtimePtr);
	if(!effectRuntime) {
		pixelpart_gm::lastError = pixelpart_gm::invalidEffectRuntimeError;
		return -1;
	}

	if(clear) {
		effectRuntime->effectEngine->clearParticles();
	}

	effectRuntime->effectEngine->restart();

	return 1;
}

GM_EXPORT pixelpart_gm::real GM_API pixelpart_reseed_effect(pixelpart_gm::string runtimePtr, pixelpart_gm::real seed) {
	pixelpart_gm::EffectRuntime* effectRuntime = pixelpart_gm::parsePtr<pixelpart_gm::EffectRuntime>(runtimePtr);
	if(!effectRuntime) {
		pixelpart_gm::lastError = pixelpart_gm::invalidEffectRuntimeError;
		return -1;
	}

	effectRuntime->effectEngine->reseed(static_cast<std::uint32_t>(std::max(seed, 0.0)));

	return 1;
}

GM_EXPORT pixelpart_gm::real GM_API pixelpart_get_effect_time(pixelpart_gm::string runtimePtr) {
	pixelpart_gm::EffectRuntime* effectRuntime = pixelpart_gm::parsePtr<pixelpart_gm::EffectRuntime>(runtimePtr);
	if(!effectRuntime) {
		pixelpart_gm::lastError = pixelpart_gm::invalidEffectRuntimeError;
		return -1;
	}

	return effectRuntime->effectEngine->context().time();
}

GM_EXPORT pixelpart_gm::real GM_API pixelpart_is_effect_finished(pixelpart_gm::string runtimePtr) {
	pixelpart_gm::EffectRuntime* effectRuntime = pixelpart_gm::parsePtr<pixelpart_gm::EffectRuntime>(runtimePtr);
	if(!effectRuntime) {
		pixelpart_gm::lastError = pixelpart_gm::invalidEffectRuntimeError;
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

GM_EXPORT pixelpart_gm::real GM_API pixelpart_is_effect_3d(pixelpart_gm::string runtimePtr) {
	pixelpart_gm::EffectRuntime* effectRuntime = pixelpart_gm::parsePtr<pixelpart_gm::EffectRuntime>(runtimePtr);
	if(!effectRuntime) {
		pixelpart_gm::lastError = pixelpart_gm::invalidEffectRuntimeError;
		return -1;
	}

	return effectRuntime->effectAsset.effect().is3d() ? 1.0 : 0.0;
}

GM_EXPORT pixelpart_gm::real GM_API pixelpart_get_effect_node_count(pixelpart_gm::string runtimePtr) {
	pixelpart_gm::EffectRuntime* effectRuntime = pixelpart_gm::parsePtr<pixelpart_gm::EffectRuntime>(runtimePtr);
	if(!effectRuntime) {
		pixelpart_gm::lastError = pixelpart_gm::invalidEffectRuntimeError;
		return -1;
	}

	return static_cast<pixelpart_gm::real>(effectRuntime->effectAsset.effect().sceneGraph().count());
}

GM_EXPORT pixelpart_gm::real GM_API pixelpart_get_effect_particle_type_count(pixelpart_gm::string runtimePtr) {
	pixelpart_gm::EffectRuntime* effectRuntime = pixelpart_gm::parsePtr<pixelpart_gm::EffectRuntime>(runtimePtr);
	if(!effectRuntime) {
		pixelpart_gm::lastError = pixelpart_gm::invalidEffectRuntimeError;
		return -1;
	}

	return static_cast<pixelpart_gm::real>(effectRuntime->effectAsset.effect().particleTypes().count());
}

GM_EXPORT pixelpart_gm::real GM_API pixelpart_get_effect_particle_runtime_instance_count(pixelpart_gm::string runtimePtr) {
	pixelpart_gm::EffectRuntime* effectRuntime = pixelpart_gm::parsePtr<pixelpart_gm::EffectRuntime>(runtimePtr);
	if(!effectRuntime) {
		pixelpart_gm::lastError = pixelpart_gm::invalidEffectRuntimeError;
		return -1;
	}

	return static_cast<pixelpart_gm::real>(effectRuntime->effectAsset.effect().particleEmissionPairs().size());
}

GM_EXPORT pixelpart_gm::real GM_API pixelpart_get_effect_particle_runtime_instances(pixelpart_gm::string runtimePtr, pixelpart_gm::string instanceBufferPtr) {
	pixelpart_gm::EffectRuntime* effectRuntime = pixelpart_gm::parsePtr<pixelpart_gm::EffectRuntime>(runtimePtr);
	if(!effectRuntime) {
		pixelpart_gm::lastError = pixelpart_gm::invalidEffectRuntimeError;
		return -1;
	}

	pixelpart_gm::Buffer instanceBuffer = pixelpart_gm::Buffer(instanceBufferPtr);

	for(pixelpart::ParticleEmissionPair emissionPair : effectRuntime->effectAsset.effect().particleEmissionPairs()) {
		instanceBuffer.write<std::uint32_t>(emissionPair.emitterId.value());
		instanceBuffer.write<std::uint32_t>(emissionPair.typeId.value());
	}

	return 1;
}

GM_EXPORT pixelpart_gm::real GM_API pixelpart_get_effect_particle_count(pixelpart_gm::string runtimePtr, pixelpart_gm::real particleEmitterId, pixelpart_gm::real particleTypeId) {
	pixelpart_gm::EffectRuntime* effectRuntime = pixelpart_gm::parsePtr<pixelpart_gm::EffectRuntime>(runtimePtr);
	if(!effectRuntime) {
		pixelpart_gm::lastError = pixelpart_gm::invalidEffectRuntimeError;
		return -1;
	}

	const pixelpart::ParticleCollection* particleCollection = effectRuntime->effectEngine->state().particleCollection(
		pixelpart::id_t(particleEmitterId),
		pixelpart::id_t(particleTypeId));

	return particleCollection->count();
}

GM_EXPORT pixelpart_gm::real GM_API pixelpart_spawn_particles(pixelpart_gm::string runtimePtr, pixelpart_gm::real particleEmitterId, pixelpart_gm::real particleTypeId, pixelpart_gm::real count) {
	pixelpart_gm::EffectRuntime* effectRuntime = pixelpart_gm::parsePtr<pixelpart_gm::EffectRuntime>(runtimePtr);
	if(!effectRuntime) {
		pixelpart_gm::lastError = pixelpart_gm::invalidEffectRuntimeError;
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
