#ifndef EFFECT_RUNTIME_H
#define EFFECT_RUNTIME_H

#include "Common.h"
#include "pixelpart-runtime/common/Types.h"
#include "pixelpart-runtime/common/Math.h"
#include "pixelpart-runtime/common/ThreadPool.h"
#include "pixelpart-runtime/effect/ParticleEmissionPair.h"
#include "pixelpart-runtime/asset/EffectAsset.h"
#include "pixelpart-runtime/engine/EffectEngine.h"
#include "pixelpart-runtime/vertex/ParticleVertexGenerator.h"
#include <memory>
#include <cstdint>
#include <unordered_map>
#include <random>

namespace pixelpart_gm {
#ifdef PIXELPART_RUNTIME_MULTITHREADING
extern std::shared_ptr<pixelpart::ThreadPool> threadPool;
#endif

extern std::mt19937 rng;

struct EffectRuntime {
	pixelpart::EffectAsset effectAsset;
	std::unique_ptr<pixelpart::EffectEngine> effectEngine;
	pixelpart::float_t simulationTime = 0.0;

	pixelpart::float3_t effectScale = pixelpart::float3_t(1.0);

	std::unordered_map<pixelpart::ParticleEmissionPair,
		std::unique_ptr<pixelpart::ParticleVertexGenerator>> vertexGenerators;
};
}

#endif
