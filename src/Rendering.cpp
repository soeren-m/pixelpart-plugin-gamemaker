#include "Common.h"
#include "Error.h"
#include "Buffer.h"
#include "VertexBuffer.h"
#include "EffectRuntime.h"
#include "pixelpart-runtime/common/Math.h"
#include "pixelpart-runtime/common/Curve.h"
#include "pixelpart-runtime/common/Transform.h"
#include "pixelpart-runtime/common/Id.h"
#include "pixelpart-runtime/effect/ParticleEmissionPair.h"
#include "pixelpart-runtime/effect/ParticleType.h"
#include "pixelpart-runtime/effect/Effect.h"
#include "pixelpart-runtime/effect/EffectRuntimeContext.h"
#include "pixelpart-runtime/engine/ParticleCollection.h"
#include "pixelpart-runtime/vertex/VertexDataBufferCollection.h"
#include "pixelpart-runtime/vertex/SceneContext.h"
#include <cstdint>
#include <cstring>
#include <cmath>
#include <string>
#include <vector>
#include <algorithm>
#include <exception>

extern "C" {
GMS2_EXPORT pixelpart_gms2::real GMS2_API pixelpart_get_sorted_particle_runtime_instances(pixelpart_gms2::string runtimePtr, pixelpart_gms2::string indexBufferPtr) {
	pixelpart_gms2::EffectRuntime* effectRuntime = reinterpret_cast<pixelpart_gms2::EffectRuntime*>(runtimePtr);
	if(!effectRuntime) {
		pixelpart_gms2::lastError = pixelpart_gms2::invalidEffectRuntimeError;
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

GMS2_EXPORT pixelpart_gms2::real GMS2_API pixelpart_construct_particle_geometry(pixelpart_gms2::string runtimePtr, pixelpart_gms2::real particleEmitterId, pixelpart_gms2::real particleTypeId, pixelpart_gms2::string bufferSizeBufferPtr) {
	pixelpart_gms2::EffectRuntime* effectRuntime = reinterpret_cast<pixelpart_gms2::EffectRuntime*>(runtimePtr);
	if(!effectRuntime) {
		pixelpart_gms2::lastError = pixelpart_gms2::invalidEffectRuntimeError;
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

		effectRuntime->vertexBufferDimensions[emissionPair] = bufferDimensions;

		pixelpart_gms2::Buffer bufferSizeBuffer(bufferSizeBufferPtr);
		for(std::size_t bufferSize : bufferDimensions) {
			bufferSizeBuffer.write(static_cast<std::uint32_t>(bufferSize));
		}

		return 1;
	}
	catch(const std::exception& e) {
		pixelpart_gms2::lastError = std::string(e.what());
	}

	return -1;
}

GMS2_EXPORT pixelpart_gms2::real GMS2_API pixelpart_generate_particle_vertex_data(pixelpart_gms2::string runtimePtr, pixelpart_gms2::real particleEmitterId, pixelpart_gms2::real particleTypeId, pixelpart_gms2::string vertexBufferPtr) {
	pixelpart_gms2::EffectRuntime* effectRuntime = reinterpret_cast<pixelpart_gms2::EffectRuntime*>(runtimePtr);
	if(!effectRuntime) {
		pixelpart_gms2::lastError = pixelpart_gms2::invalidEffectRuntimeError;
		return -1;
	}
	else if(!vertexBufferPtr) {
		pixelpart_gms2::lastError = pixelpart_gms2::invalidArgumentError;
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

		const auto& bufferDimensions = effectRuntime->vertexBufferDimensions[emissionPair];

		pixelpart::EffectRuntimeContext runtimeContext = effectRuntime->effectEngine->context();
		pixelpart::SceneContext sceneContext;
		sceneContext.effectScale = effectRuntime->effectScale;

		std::vector<glm::vec4> colorBuffer;
		colorBuffer.resize(bufferDimensions[1]);

		auto& vertexGenerator = effectRuntime->vertexGenerators.at(emissionPair);
		vertexGenerator->generateVertexData(pixelpart::VertexDataBufferCollection({
				reinterpret_cast<std::uint8_t*>(vertexBufferPtr),
				reinterpret_cast<std::uint8_t*>(colorBuffer.data())
			}),
			particleCollection->readPtr(),
			particleCollection->count(),
			runtimeContext, sceneContext);

		std::size_t colorVertexOffset = sizeof(float) * 2;
		std::size_t vertexStride = sizeof(float) * 6 + sizeof(std::uint8_t) * 4;

		for(std::size_t vertexIndex = 0; vertexIndex < bufferDimensions[0]; vertexIndex++) {
			const glm::vec4& color = colorBuffer[vertexIndex];

			std::size_t bufferOffset = vertexIndex * vertexStride + colorVertexOffset;
			*reinterpret_cast<std::uint8_t*>(vertexBufferPtr + bufferOffset + 0) = static_cast<std::uint8_t>(std::clamp(color.r * 255.0f, 0.0f, 255.0f));
			*reinterpret_cast<std::uint8_t*>(vertexBufferPtr + bufferOffset + 1) = static_cast<std::uint8_t>(std::clamp(color.g * 255.0f, 0.0f, 255.0f));
			*reinterpret_cast<std::uint8_t*>(vertexBufferPtr + bufferOffset + 2) = static_cast<std::uint8_t>(std::clamp(color.b * 255.0f, 0.0f, 255.0f));
			*reinterpret_cast<std::uint8_t*>(vertexBufferPtr + bufferOffset + 3) = static_cast<std::uint8_t>(std::clamp(color.a * 255.0f, 0.0f, 255.0f));
		}

		return 1;
	}
	catch(const std::exception& e) {
		pixelpart_gms2::lastError = std::string(e.what());
	}

	return -1;
}
}
