#include "Common.h"
#include "Error.h"
#include "Buffer.h"
#include "EffectRuntime.h"
#include "pixelpart-runtime/types/Types.h"
#include "pixelpart-runtime/types/Id.h"
#include "pixelpart-runtime/effect/Curve.h"
#include "pixelpart-runtime/effect/Transform.h"
#include "pixelpart-runtime/effect/ParticleEmissionPair.h"
#include "pixelpart-runtime/effect/ParticleType.h"
#include "pixelpart-runtime/effect/Effect.h"
#include "pixelpart-runtime/effect/EffectRuntimeContext.h"
#include "pixelpart-runtime/engine/ParticleCollection.h"
#include "pixelpart-runtime/vertex/VertexDataBufferCollection.h"
#include "pixelpart-runtime/vertex/VertexDataBufferDimensions.h"
#include "pixelpart-runtime/vertex/SceneContext.h"
#include <cstdint>
#include <cstring>
#include <cmath>
#include <string>
#include <vector>
#include <algorithm>
#include <exception>

extern "C" {
GM_EXPORT pixelpart_gm::real GM_API pixelpart_get_sorted_particle_runtime_instances(pixelpart_gm::string runtimePtr, pixelpart_gm::string indexBufferPtr) {
	pixelpart_gm::EffectRuntime* effectRuntime = pixelpart_gm::parsePtr<pixelpart_gm::EffectRuntime>(runtimePtr);
	if(!effectRuntime) {
		pixelpart_gm::lastError = pixelpart_gm::invalidEffectRuntimeError;
		return -1;
	}

	const pixelpart::Effect& effect = effectRuntime->effectAsset.effect();

	std::vector<std::uint32_t> sortedIndices(effect.particleEmissionPairs().size());
	std::iota(sortedIndices.begin(), sortedIndices.end(), 0);
	std::sort(sortedIndices.begin(), sortedIndices.end(), [&effect](std::uint32_t i1, std::uint32_t i2) {
		const pixelpart::ParticleType& pt1 = effect.particleTypes().at(effect.particleEmissionPairs()[i1].typeId);
		const pixelpart::ParticleType& pt2 = effect.particleTypes().at(effect.particleEmissionPairs()[i2].typeId);

		return pt1.layer() < pt2.layer();
	});

	std::memcpy(indexBufferPtr, sortedIndices.data(), sortedIndices.size() * sizeof(std::uint32_t));

	return 1;
}

GM_EXPORT pixelpart_gm::real GM_API pixelpart_construct_particle_geometry(pixelpart_gm::string runtimePtr, pixelpart_gm::real particleEmitterId, pixelpart_gm::real particleTypeId, pixelpart_gm::string bufferSizeBufferPtr) {
	pixelpart_gm::EffectRuntime* effectRuntime = pixelpart_gm::parsePtr<pixelpart_gm::EffectRuntime>(runtimePtr);
	if(!effectRuntime) {
		pixelpart_gm::lastError = pixelpart_gm::invalidEffectRuntimeError;
		return -1;
	}

	try {
		pixelpart::ParticleEmissionPair emissionPair = pixelpart::ParticleEmissionPair(
			pixelpart::id_t(particleEmitterId), pixelpart::id_t(particleTypeId));

		const pixelpart::ParticleCollection* particleCollection = effectRuntime->effectEngine->state().particleCollection(
			emissionPair.emitterId, emissionPair.typeId);
		if(!particleCollection) {
			return 0;
		}

		pixelpart::EffectRuntimeContext runtimeContext = effectRuntime->effectEngine->context();
		pixelpart::SceneContext sceneContext;
		sceneContext.effectScale = effectRuntime->effectScale;

		auto& vertexGenerator = effectRuntime->vertexGenerators.at(emissionPair);
		pixelpart::VertexDataBufferDimensions bufferDimensions = vertexGenerator->buildGeometry(
			particleCollection->readPtr(),
			particleCollection->count(),
			runtimeContext, sceneContext);

		pixelpart_gm::Buffer bufferSizeBuffer(bufferSizeBufferPtr);
		for(std::size_t bufferSize : bufferDimensions) {
			bufferSizeBuffer.write(static_cast<std::uint32_t>(bufferSize));
		}

		return 1;
	}
	catch(const std::exception& e) {
		pixelpart_gm::lastError = std::string(e.what());
	}

	return -1;
}

GM_EXPORT pixelpart_gm::real GM_API pixelpart_generate_particle_vertex_data(pixelpart_gm::string runtimePtr, pixelpart_gm::real particleEmitterId, pixelpart_gm::real particleTypeId, pixelpart_gm::string vertexBufferPtr) {
	pixelpart_gm::EffectRuntime* effectRuntime = pixelpart_gm::parsePtr<pixelpart_gm::EffectRuntime>(runtimePtr);
	if(!effectRuntime) {
		pixelpart_gm::lastError = pixelpart_gm::invalidEffectRuntimeError;
		return -1;
	}
	else if(!vertexBufferPtr) {
		pixelpart_gm::lastError = pixelpart_gm::invalidArgumentError;
		return -1;
	}

	try {
		pixelpart::ParticleEmissionPair emissionPair = pixelpart::ParticleEmissionPair(
			pixelpart::id_t(particleEmitterId), pixelpart::id_t(particleTypeId));

		const pixelpart::ParticleCollection* particleCollection =
			effectRuntime->effectEngine->state().particleCollection(emissionPair.emitterId, emissionPair.typeId);
		if(!particleCollection) {
			return 0;
		}

		pixelpart::EffectRuntimeContext runtimeContext = effectRuntime->effectEngine->context();
		pixelpart::SceneContext sceneContext;
		sceneContext.effectScale = effectRuntime->effectScale;

		auto& vertexGenerator = effectRuntime->vertexGenerators.at(emissionPair);
		vertexGenerator->generateVertexData(pixelpart::VertexDataBufferCollection({
				reinterpret_cast<std::uint8_t*>(vertexBufferPtr)
			}),
			particleCollection->readPtr(),
			particleCollection->count(),
			runtimeContext, sceneContext);

		return 1;
	}
	catch(const std::exception& e) {
		pixelpart_gm::lastError = std::string(e.what());
	}

	return -1;
}
}
