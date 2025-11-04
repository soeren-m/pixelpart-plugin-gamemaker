#ifndef EFFECT_RUNTIME_H
#define EFFECT_RUNTIME_H

#include "Common.h"
#include "pixelpart-runtime/common/Types.h"
#include "pixelpart-runtime/common/Math.h"
#include "pixelpart-runtime/effect/ParticleRuntimeId.h"
#include "pixelpart-runtime/asset/EffectAsset.h"
#include "pixelpart-runtime/engine/EffectEngine.h"
#include "pixelpart-runtime/engine/ParticleCollection.h"
#include <memory>
#include <cstdint>
#include <vector>
#include <unordered_map>
#include <random>

namespace pixelpart_gms2 {
extern std::mt19937 rng;

struct TrailMeshData {
	std::uint32_t particleCount = 0;
	pixelpart::float_t length = 0.0;

	std::vector<pixelpart::float3_t> position;
	std::vector<pixelpart::float3_t> size;
	std::vector<pixelpart::float4_t> color;
	std::vector<pixelpart::float3_t> velocity;
	std::vector<pixelpart::float_t> life;
	std::vector<pixelpart::float3_t> direction;
	std::vector<pixelpart::float3_t> directionToEdge;
	std::vector<pixelpart::float_t> index;
};

struct ParticleMeshData {
	pixelpart::ParticleCollection sortedParticleCollection;
	std::vector<std::uint32_t> sortKeys;

	std::unordered_map<std::uint32_t, TrailMeshData> trails;
};

struct EffectRuntime {
	pixelpart::EffectAsset effectAsset;
	std::unique_ptr<pixelpart::EffectEngine> effectEngine;
	pixelpart::float_t simulationTime = 0.0;

	pixelpart::float3_t effectScale = pixelpart::float3_t(1.0);
	std::unordered_map<pixelpart::ParticleRuntimeId, ParticleMeshData> meshData;
};
}

#endif