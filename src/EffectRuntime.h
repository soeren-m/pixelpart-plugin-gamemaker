#ifndef EFFECT_RUNTIME_H
#define EFFECT_RUNTIME_H

#include "Common.h"
#include "pixelpart-runtime/types/Types.h"
#include "pixelpart-runtime/types/Id.h"
#include "pixelpart-runtime/platform/ThreadPool.h"
#include "pixelpart-runtime/effect/ParticleEmissionPair.h"
#include "pixelpart-runtime/asset/EffectAsset.h"
#include "pixelpart-runtime/engine/EffectEngine.h"
#include "pixelpart-runtime/vertex/ParticleVertexGenerator.h"
#include <memory>
#include <cstdint>
#include <vector>
#include <unordered_map>
#include <random>

namespace pixelpart_gm {
extern std::shared_ptr<pixelpart::ThreadPool> threadPool;
extern std::mt19937 rng;

struct EffectResource {
	pixelpart::EffectAsset effectAsset;
};

struct EffectRuntime {
	pixelpart::EffectAsset effectAsset;
	std::unique_ptr<pixelpart::EffectEngine> effectEngine;
	pixelpart::float_t simulationTime = 0.0;
	std::vector<pixelpart::id_t> invokedEventIds;

	pixelpart::float3_t effectScale = pixelpart::float3_t(1.0);

	std::unordered_map<pixelpart::ParticleEmissionPair,
		std::unique_ptr<pixelpart::ParticleVertexGenerator>> vertexGenerators;
};
}

#endif
