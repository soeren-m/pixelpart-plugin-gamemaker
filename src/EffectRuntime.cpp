#include "EffectRuntime.h"
#include "Error.h"
#include "Buffer.h"
#include "pixelpart-runtime/common/Math.h"
#include "pixelpart-runtime/common/Curve.h"
#include "pixelpart-runtime/common/Transform.h"
#include "pixelpart-runtime/effect/Node.h"
#include "pixelpart-runtime/engine/SingleThreadedEffectEngine.h"
#include "pixelpart-runtime/computegraph/ComputeGraph.h"
#include <string>
#include <algorithm>
#include <exception>

namespace pixelpart_gms2 {
std::mt19937 rng;

std::string effectRuntimePtrString = "";
}

extern "C" {
GMS2_EXPORT pixelpart_gms2::const_string GMS2_API pixelpart_load_effect(pixelpart_gms2::string data, pixelpart_gms2::real size, pixelpart_gms2::real particleCapacity) {
	if(!data || size <= 0) {
		pixelpart_gms2::lastError ="Effect data is empty";
		pixelpart_gms2::effectRuntimePtrString = pixelpart_gms2::nullPointerString;

		return pixelpart_gms2::effectRuntimePtrString.c_str();
	}

	try {
		pixelpart_gms2::EffectRuntime* effectRuntime = new pixelpart_gms2::EffectRuntime();
		effectRuntime->effectAsset = pixelpart::deserializeEffectAsset(data, static_cast<std::size_t>(size));
		effectRuntime->effectEngine = std::unique_ptr<pixelpart::SingleThreadedEffectEngine>(
			new pixelpart::SingleThreadedEffectEngine(effectRuntime->effectAsset.effect(), static_cast<std::uint32_t>(std::max(particleCapacity, 1.0))));

		effectRuntime->effectAsset.effect().applyInputs();

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
	pixelpart_gms2::real dt = std::max(paramBuffer.read<pixelpart_gms2::real>(), 0.0);
	pixelpart_gms2::real loop = paramBuffer.read<pixelpart_gms2::real>();
	pixelpart_gms2::real loopTime = std::max(paramBuffer.read<pixelpart_gms2::real>(), 0.0);
	pixelpart_gms2::real speed = std::max(paramBuffer.read<pixelpart_gms2::real>(), 0.0);
	pixelpart_gms2::real timeStep = std::max(paramBuffer.read<pixelpart_gms2::real>() * speed, 0.001);

	effectRuntime->simulationTime += dt * speed;

	while(effectRuntime->simulationTime > timeStep) {
		effectRuntime->simulationTime -= timeStep;
		effectRuntime->effectEngine->advance(timeStep);

		if(loop > 0.5 && effectRuntime->effectEngine->runtimeContext().time() > loopTime) {
			effectRuntime->effectEngine->restart(false);
		}
	}

	return 1;
}

GMS2_EXPORT pixelpart_gms2::real GMS2_API pixelpart_restart_effect(pixelpart_gms2::string runtimePtr, pixelpart_gms2::real reset) {
	pixelpart_gms2::EffectRuntime* effectRuntime = reinterpret_cast<pixelpart_gms2::EffectRuntime*>(runtimePtr);
	if(!effectRuntime) {
		pixelpart_gms2::lastError = pixelpart_gms2::invalidEffectRuntimeError;
		return -1;
	}

	effectRuntime->effectEngine->restart(reset > 0.5);

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

GMS2_EXPORT pixelpart_gms2::real GMS2_API pixelpart_get_effect_time(pixelpart_gms2::string runtimePtr) {
	pixelpart_gms2::EffectRuntime* effectRuntime = reinterpret_cast<pixelpart_gms2::EffectRuntime*>(runtimePtr);
	if(!effectRuntime) {
		pixelpart_gms2::lastError = pixelpart_gms2::invalidEffectRuntimeError;
		return -1;
	}

	return effectRuntime->effectEngine->runtimeContext().time();
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

	return static_cast<pixelpart_gms2::real>(effectRuntime->effectAsset.effect().particleRuntimeIds().size());
}

GMS2_EXPORT pixelpart_gms2::real GMS2_API pixelpart_get_effect_particle_runtime_instances(pixelpart_gms2::string runtimePtr, pixelpart_gms2::string instanceBufferPtr) {
	pixelpart_gms2::EffectRuntime* effectRuntime = reinterpret_cast<pixelpart_gms2::EffectRuntime*>(runtimePtr);
	if(!effectRuntime) {
		pixelpart_gms2::lastError = pixelpart_gms2::invalidEffectRuntimeError;
		return -1;
	}

	pixelpart_gms2::Buffer instanceBuffer = pixelpart_gms2::Buffer(instanceBufferPtr);

	for(const pixelpart::ParticleRuntimeId runtimeId : effectRuntime->effectAsset.effect().particleRuntimeIds()) {
		instanceBuffer.write<std::uint32_t>(runtimeId.emitterId.value());
		instanceBuffer.write<std::uint32_t>(runtimeId.typeId.value());
	}

	return 1;
}

GMS2_EXPORT pixelpart_gms2::real GMS2_API pixelpart_get_effect_particle_count(pixelpart_gms2::string runtimePtr, pixelpart_gms2::real particleEmitterId, pixelpart_gms2::real particleTypeId) {
	pixelpart_gms2::EffectRuntime* effectRuntime = reinterpret_cast<pixelpart_gms2::EffectRuntime*>(runtimePtr);
	if(!effectRuntime) {
		pixelpart_gms2::lastError = pixelpart_gms2::invalidEffectRuntimeError;
		return -1;
	}

	return effectRuntime->effectEngine->particleCount(
		pixelpart::id_t(particleEmitterId),
		pixelpart::id_t(particleTypeId));
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

	effectRuntime->effectEngine->spawnParticles(
		pixelpart::id_t(particleEmitterId),
		pixelpart::id_t(particleTypeId),
		static_cast<std::uint32_t>(count));

	return 1;
}
}
