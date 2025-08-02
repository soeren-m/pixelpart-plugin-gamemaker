#include "Common.h"
#include "Error.h"
#include "Buffer.h"
#include "VertexBuffer.h"
#include "EffectRuntime.h"
#include "pixelpart-runtime/common/Math.h"
#include "pixelpart-runtime/common/Transform.h"
#include "pixelpart-runtime/common/Id.h"
#include "pixelpart-runtime/effect/ParticleEmitter.h"
#include "pixelpart-runtime/effect/ParticleType.h"
#include "pixelpart-runtime/effect/Effect.h"
#include "pixelpart-runtime/effect/ParticleRuntimeId.h"
#include "pixelpart-runtime/engine/ParticleCollection.h"
#define GLM_ENABLE_EXPERIMENTAL
#include "pixelpart-runtime/glm/gtx/norm.hpp"
#include "pixelpart-runtime/glm/gtx/vector_angle.hpp"
#include <cstdint>
#include <cstring>
#include <cmath>
#include <string>
#include <algorithm>
#include <exception>

namespace pixelpart_gms2 {
pixelpart::float3_t rotate2d(const pixelpart::float3_t& p, const pixelpart::float3_t& o, pixelpart::float_t a) {
	pixelpart::float_t s = std::sin(glm::radians(a));
	pixelpart::float_t c = std::cos(glm::radians(a));

	return pixelpart::float3_t(
		(p.x - o.x) * c - (p.y - o.y) * s + o.x,
		(p.x - o.x) * s + (p.y - o.y) * c + o.y,
		0.0);
}
pixelpart::mat3_t rotation3d(const pixelpart::float3_t& angle) {
	pixelpart::float3_t rotation = glm::radians(angle);
	pixelpart::float_t cy = std::cos(rotation.y);
	pixelpart::float_t sy = std::sin(rotation.y);
	pixelpart::float_t cp = std::cos(rotation.z);
	pixelpart::float_t sp = std::sin(rotation.z);
	pixelpart::float_t cr = std::cos(rotation.x);
	pixelpart::float_t sr = std::sin(rotation.x);

	return pixelpart::mat3_t(
		pixelpart::float3_t(cy * cr + sy * sp * sr, sr * cp, -sy * cr + cy * sp * sr),
		pixelpart::float3_t(-cy * sr + sy * sp * cr, cr * cp, sr * sy + cy * sp * cr),
		pixelpart::float3_t(sy * cp, -sp, cy * cp));
}
pixelpart::mat3_t lookAt(const pixelpart::float3_t& direction) {
	pixelpart::float3_t up = pixelpart::float3_t(0.0, 1.0, 0.0);
	pixelpart::float3_t front = glm::normalize(direction);
	pixelpart::float3_t right = glm::normalize(glm::cross(front, up));
	up = glm::normalize(glm::cross(right, front));

	return pixelpart::mat3_t(right, up, -front);
}
}

extern "C" {
GMS2_EXPORT pixelpart_gms2::real GMS2_API pixelpart_get_sorted_particle_runtime_instances(pixelpart_gms2::string runtimePtr, pixelpart_gms2::string indexBufferPtr) {
	pixelpart_gms2::EffectRuntime* effectRuntime = reinterpret_cast<pixelpart_gms2::EffectRuntime*>(runtimePtr);
	if(!effectRuntime) {
		pixelpart_gms2::lastError = pixelpart_gms2::invalidEffectRuntimeError;
		return -1;
	}

	const pixelpart::Effect& effect = effectRuntime->effectAsset.effect();

	std::vector<std::uint32_t> sortedIndices(effect.particleRuntimeIds().size());
	std::iota(sortedIndices.begin(), sortedIndices.end(), 0);
	std::sort(sortedIndices.begin(), sortedIndices.end(), [&effect](std::uint32_t i1, std::uint32_t i2) {
		const pixelpart::ParticleType& pt1 = effect.particleTypes().at(effect.particleRuntimeIds()[i1].typeId);
		const pixelpart::ParticleType& pt2 = effect.particleTypes().at(effect.particleRuntimeIds()[i2].typeId);

		return pt1.layer() < pt2.layer();
	});

	std::memcpy(indexBufferPtr, sortedIndices.data(), sortedIndices.size() * sizeof(std::uint32_t));

	return 1;
}

GMS2_EXPORT pixelpart_gms2::real GMS2_API pixelpart_prepare_particle_sprite_vertex_data(pixelpart_gms2::string runtimePtr, pixelpart_gms2::real particleEmitterId, pixelpart_gms2::real particleTypeId) {
	pixelpart_gms2::EffectRuntime* effectRuntime = reinterpret_cast<pixelpart_gms2::EffectRuntime*>(runtimePtr);
	if(!effectRuntime) {
		pixelpart_gms2::lastError = pixelpart_gms2::invalidEffectRuntimeError;
		return -1;
	}

	std::uint32_t particleCount = effectRuntime->effectEngine->particleCount(
		pixelpart::id_t(particleEmitterId),
		pixelpart::id_t(particleTypeId));

	return particleCount * 6;
}

GMS2_EXPORT pixelpart_gms2::real GMS2_API pixelpart_get_particle_sprite_vertex_data(pixelpart_gms2::string runtimePtr, pixelpart_gms2::real particleEmitterId, pixelpart_gms2::real particleTypeId, pixelpart_gms2::string vertexBufferPtr) {
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
		pixelpart::ParticleRuntimeId runtimeId = pixelpart::ParticleRuntimeId(
			pixelpart::id_t(particleEmitterId), pixelpart::id_t(particleTypeId));

		const pixelpart::Effect& effect = effectRuntime->effectAsset.effect();
		const pixelpart::ParticleEmitter& particleEmitter = effect.sceneGraph().at<pixelpart::ParticleEmitter>(pixelpart::id_t(particleEmitterId));
		const pixelpart::ParticleType& particleType = effect.particleTypes().at(pixelpart::id_t(particleTypeId));
		const pixelpart::ParticleCollection* particleCollection = effectRuntime->effectEngine->particles(
			pixelpart::id_t(particleEmitterId), pixelpart::id_t(particleTypeId));

		if(!particleCollection) {
			return 0;
		}

		pixelpart::ParticleCollection::ReadPtr particles = particleCollection->readPtr();
		std::uint32_t particleCount = particleCollection->count();

		pixelpart::Transform emitterTransform = effect.sceneGraph().globalTransform(particleEmitter.id(), effectRuntime->effectEngine->runtimeContext());
		pixelpart::float3_t emitterPosition = emitterTransform.position();
		pixelpart::mat3_t emitterRotationMatrix = pixelpart_gms2::rotation3d(emitterTransform.rotation());

		glm::vec2 uv[4] = {
			glm::vec2(0, 0),
			glm::vec2(1, 0),
			glm::vec2(1, 1),
			glm::vec2(0, 1)
		};

		pixelpart_gms2::VertexBuffer vertexBuffer(vertexBufferPtr);

		for(std::uint32_t p = 0; p < particleCount; p++) {
			glm::vec3 position[4];
			pixelpart::float3_t pivot = particleType.pivot().value() * particles.size[p];

			switch(particleType.alignmentMode()) {
				case pixelpart::AlignmentMode::motion: {
					pixelpart::float_t angle = glm::degrees(glm::orientedAngle(pixelpart::float2_t(0.0, 1.0), (particles.velocity[p] != pixelpart::float3_t(0.0))
						? pixelpart::float2_t(glm::normalize(particles.velocity[p]))
						: pixelpart::float2_t(0.0, 1.0)));
					position[0] = particles.globalPosition[p] + pixelpart_gms2::rotate2d(pixelpart::float3_t(-0.5, -0.5, 0.0) * particles.size[p], pivot, particles.rotation[p].x + angle);
					position[1] = particles.globalPosition[p] + pixelpart_gms2::rotate2d(pixelpart::float3_t(+0.5, -0.5, 0.0) * particles.size[p], pivot, particles.rotation[p].x + angle);
					position[2] = particles.globalPosition[p] + pixelpart_gms2::rotate2d(pixelpart::float3_t(+0.5, +0.5, 0.0) * particles.size[p], pivot, particles.rotation[p].x + angle);
					position[3] = particles.globalPosition[p] + pixelpart_gms2::rotate2d(pixelpart::float3_t(-0.5, +0.5, 0.0) * particles.size[p], pivot, particles.rotation[p].x + angle);
					break;
				}
				case pixelpart::AlignmentMode::emission: {
					pixelpart::float3_t emissionDirection = emitterPosition - particles.globalPosition[p];
					pixelpart::float_t angle = glm::degrees(glm::orientedAngle(pixelpart::float2_t(0.0, 1.0), (emissionDirection != pixelpart::float3_t(0.0))
						? pixelpart::float2_t(glm::normalize(emissionDirection))
						: pixelpart::float2_t(0.0, 1.0)));
					position[0] = particles.globalPosition[p] + pixelpart_gms2::rotate2d(pixelpart::float3_t(-0.5, -0.5, 0.0) * particles.size[p], pivot, particles.rotation[p].x + angle);
					position[1] = particles.globalPosition[p] + pixelpart_gms2::rotate2d(pixelpart::float3_t(+0.5, -0.5, 0.0) * particles.size[p], pivot, particles.rotation[p].x + angle);
					position[2] = particles.globalPosition[p] + pixelpart_gms2::rotate2d(pixelpart::float3_t(+0.5, +0.5, 0.0) * particles.size[p], pivot, particles.rotation[p].x + angle);
					position[3] = particles.globalPosition[p] + pixelpart_gms2::rotate2d(pixelpart::float3_t(-0.5, +0.5, 0.0) * particles.size[p], pivot, particles.rotation[p].x + angle);
					break;
				}
				case pixelpart::AlignmentMode::emitter: {
					pixelpart::mat3_t rotationMatrix = pixelpart_gms2::rotation3d(particles.rotation[p]);
					position[0] = particles.globalPosition[p] + emitterRotationMatrix * (rotationMatrix * (pixelpart::float3_t(-0.5, -0.5, 0.0) * particles.size[p] - pivot) + pivot);
					position[1] = particles.globalPosition[p] + emitterRotationMatrix * (rotationMatrix * (pixelpart::float3_t(+0.5, -0.5, 0.0) * particles.size[p] - pivot) + pivot);
					position[2] = particles.globalPosition[p] + emitterRotationMatrix * (rotationMatrix * (pixelpart::float3_t(+0.5, +0.5, 0.0) * particles.size[p] - pivot) + pivot);
					position[3] = particles.globalPosition[p] + emitterRotationMatrix * (rotationMatrix * (pixelpart::float3_t(-0.5, +0.5, 0.0) * particles.size[p] - pivot) + pivot);
					break;
				}
				default: {
					pixelpart::mat3_t rotationMatrix = pixelpart_gms2::rotation3d(particles.rotation[p]);
					position[0] = particles.globalPosition[p] + (rotationMatrix * (pixelpart::float3_t(-0.5, -0.5, 0.0) * particles.size[p] - pivot) + pivot);
					position[1] = particles.globalPosition[p] + (rotationMatrix * (pixelpart::float3_t(+0.5, -0.5, 0.0) * particles.size[p] - pivot) + pivot);
					position[2] = particles.globalPosition[p] + (rotationMatrix * (pixelpart::float3_t(+0.5, +0.5, 0.0) * particles.size[p] - pivot) + pivot);
					position[3] = particles.globalPosition[p] + (rotationMatrix * (pixelpart::float3_t(-0.5, +0.5, 0.0) * particles.size[p] - pivot) + pivot);
					break;
				}
			}

			position[0] *= effectRuntime->effectScale;
			position[1] *= effectRuntime->effectScale;
			position[2] *= effectRuntime->effectScale;
			position[3] *= effectRuntime->effectScale;

			glm::vec4 color(particles.color[p]);
			glm::vec3 velocity(particles.velocity[p]);
			float life = static_cast<float>(particles.life[p]);
			float id = static_cast<float>(particles.id[p]);

			vertexBuffer.addVertex(position[0], color, uv[0], velocity, life, id);
			vertexBuffer.addVertex(position[1], color, uv[1], velocity, life, id);
			vertexBuffer.addVertex(position[3], color, uv[3], velocity, life, id);
			vertexBuffer.addVertex(position[1], color, uv[1], velocity, life, id);
			vertexBuffer.addVertex(position[2], color, uv[2], velocity, life, id);
			vertexBuffer.addVertex(position[3], color, uv[3], velocity, life, id);
		}

		return 1;
	}
	catch(const std::exception& e) {
		pixelpart_gms2::lastError = std::string(e.what());
	}

	return -1;
}
}