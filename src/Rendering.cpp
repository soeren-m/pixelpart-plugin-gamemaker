#include "Common.h"
#include "Error.h"
#include "Buffer.h"
#include "VertexBuffer.h"
#include "EffectRuntime.h"
#include "pixelpart-runtime/common/Math.h"
#include "pixelpart-runtime/common/Curve.h"
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
#include <vector>
#include <algorithm>
#include <exception>

namespace pixelpart_gms2 {
template <typename T>
std::vector<typename pixelpart::Curve<T>::Point> orderedPoints(const pixelpart::float_t* positionList, const T* valueList, const std::uint32_t* order, std::uint32_t count) {
	std::vector<typename pixelpart::Curve<T>::Point> result;
	result.resize(count);
	for(std::uint32_t index = 0; index < count; index++) {
		result[index] = typename pixelpart::Curve<T>::Point{ positionList[index], valueList[order[index]] };
	}

	return result;
}

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

GMS2_EXPORT pixelpart_gms2::real GMS2_API pixelpart_prepare_particle_trail_vertex_data(pixelpart_gms2::string runtimePtr, pixelpart_gms2::real particleEmitterId, pixelpart_gms2::real particleTypeId) {
	const pixelpart::float_t epsilon = 0.000001;

	pixelpart_gms2::EffectRuntime* effectRuntime = reinterpret_cast<pixelpart_gms2::EffectRuntime*>(runtimePtr);
	if(!effectRuntime) {
		pixelpart_gms2::lastError = pixelpart_gms2::invalidEffectRuntimeError;
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

		if(!particleCollection || particleCollection->count() < 2) {
			return 0;
		}

		pixelpart::ParticleCollection::ReadPtr particles = particleCollection->readPtr();
		std::uint32_t particleCount = particleCollection->count();

		std::vector<std::uint32_t> sortKeys(particleCount);
		std::iota(sortKeys.begin(), sortKeys.end(), 0);
		std::sort(sortKeys.begin(), sortKeys.end(), [&particles](std::uint32_t p0, std::uint32_t p1) {
			return (particles.parentId[p0] != particles.parentId[p1])
				? particles.parentId[p0] > particles.parentId[p1]
				: particles.id[p0] > particles.id[p1];
		});

		pixelpart_gms2::ParticleMeshData& meshData = effectRuntime->meshData[runtimeId];
		std::unordered_map<std::uint32_t, pixelpart_gms2::TrailMeshData>& trails = meshData.trails;

		for(auto& entry : trails) {
			entry.second.particleCount = 0;
		}

		pixelpart_gms2::TrailMeshData* currentTrail = nullptr;
		for(std::uint32_t p = 0, particleParentId = 0, trailId = 0xFFFFFFFE; p < particleCount; p++) {
			particleParentId = particles.parentId[sortKeys[p]];

			if(particleParentId != trailId) {
				trailId = particleParentId;
				currentTrail = &trails[trailId];
			}

			currentTrail->particleCount++;
		}

		for(auto it = trails.begin(); it != trails.end(); ) {
			if(it->second.particleCount == 0) {
				it = trails.erase(it);
			}
			else {
				it++;
			}
		}

		currentTrail = nullptr;

		switch(particleType.trailRendererSettings().smoothingMethod) {
			case pixelpart::ParticleTrailRendererSettings::SmoothingMethod::spline: {
				for(std::uint32_t p = 0, particleParentId = 0, trailId = 0xFFFFFFFE; p < particleCount; p++) {
					std::uint32_t particleIndex = sortKeys[p];
					particleParentId = particles.parentId[particleIndex];

					if(particleParentId != trailId) {
						trailId = particleParentId;
						currentTrail = &trails.at(trailId);

						std::vector<pixelpart::float_t> relativeParticlePosition(currentTrail->particleCount);
						relativeParticlePosition[0] = 0.0;

						currentTrail->length = 0.0;
						for(std::uint32_t q = 1; q < currentTrail->particleCount; q++) {
							currentTrail->length += glm::length(particles.globalPosition[sortKeys[p + q]] - particles.globalPosition[sortKeys[p + q - 1]]);
							relativeParticlePosition[q] = currentTrail->length;
						}
						for(std::uint32_t q = 1; q < currentTrail->particleCount; q++) {
							relativeParticlePosition[q] /= currentTrail->length;
						}

						pixelpart::Curve<pixelpart::float3_t> positionCurve(pixelpart::CurveInterpolation::spline);
						positionCurve.enableFixedCache(particleType.trailRendererSettings().smoothingSegmentCount);
						positionCurve.points(pixelpart_gms2::orderedPoints(relativeParticlePosition.data(), particles.globalPosition, sortKeys.data() + p, currentTrail->particleCount));

						pixelpart::Curve<pixelpart::float3_t> sizeCurve(pixelpart::CurveInterpolation::spline);
						sizeCurve.enableFixedCache(particleType.trailRendererSettings().smoothingSegmentCount);
						sizeCurve.points(pixelpart_gms2::orderedPoints(relativeParticlePosition.data(), particles.size, sortKeys.data() + p, currentTrail->particleCount));

						pixelpart::Curve<pixelpart::float4_t> colorCurve(pixelpart::CurveInterpolation::spline);
						colorCurve.enableFixedCache(particleType.trailRendererSettings().smoothingSegmentCount);
						colorCurve.points(pixelpart_gms2::orderedPoints(relativeParticlePosition.data(), particles.color, sortKeys.data() + p, currentTrail->particleCount));

						pixelpart::Curve<pixelpart::float3_t> velocityCurve(pixelpart::CurveInterpolation::spline);
						velocityCurve.enableFixedCache(particleType.trailRendererSettings().smoothingSegmentCount);
						velocityCurve.points(pixelpart_gms2::orderedPoints(relativeParticlePosition.data(), particles.velocity, sortKeys.data() + p, currentTrail->particleCount));

						pixelpart::Curve<pixelpart::float_t> lifeCurve(pixelpart::CurveInterpolation::spline);
						lifeCurve.enableFixedCache(particleType.trailRendererSettings().smoothingSegmentCount);
						lifeCurve.points(pixelpart_gms2::orderedPoints(relativeParticlePosition.data(), particles.life, sortKeys.data() + p, currentTrail->particleCount));

						currentTrail->position = positionCurve.cache();
						currentTrail->size = sizeCurve.cache();
						currentTrail->color = colorCurve.cache();
						currentTrail->velocity = velocityCurve.cache();
						currentTrail->life = lifeCurve.cache();
						currentTrail->direction.resize(particleType.trailRendererSettings().smoothingSegmentCount);
						currentTrail->directionToEdge.resize(particleType.trailRendererSettings().smoothingSegmentCount);
						currentTrail->index.resize(particleType.trailRendererSettings().smoothingSegmentCount);
					}
				}

				break;
			}

			default: {
				for(std::uint32_t p = 0, q = 0, particleParentId = 0, trailId = 0xFFFFFFFE; p < particleCount; p++, q++) {
					std::uint32_t particleIndex = sortKeys[p];
					particleParentId = particles.parentId[particleIndex];

					if(particleParentId != trailId) {
						trailId = particleParentId;
						q = 0;

						currentTrail = &trails.at(trailId);
						currentTrail->position.resize(currentTrail->particleCount);
						currentTrail->size.resize(currentTrail->particleCount);
						currentTrail->color.resize(currentTrail->particleCount);
						currentTrail->velocity.resize(currentTrail->particleCount);
						currentTrail->life.resize(currentTrail->particleCount);
						currentTrail->direction.resize(currentTrail->particleCount);
						currentTrail->directionToEdge.resize(currentTrail->particleCount);
						currentTrail->index.resize(currentTrail->particleCount);
					}

					currentTrail->position[q] = particles.globalPosition[particleIndex];
					currentTrail->size[q] = particles.size[particleIndex];
					currentTrail->color[q] = particles.color[particleIndex];
					currentTrail->velocity[q] = particles.velocity[particleIndex];
					currentTrail->life[q] = particles.life[particleIndex];
				}

				break;
			}
		}

		std::uint32_t vertexCount = 0;

		for(auto& entry : trails) {
			pixelpart_gms2::TrailMeshData& trail = entry.second;
			trail.length = 0.0;

			if(trail.position.size() < 2) {
				continue;
			}

			std::size_t last = trail.position.size() - 1;
			for(std::size_t i = 0; i < last; i++) {
				pixelpart::float3_t toNext = trail.position[i + 1] - trail.position[i];
				pixelpart::float_t distance = std::max(glm::length(toNext), epsilon);

				trail.direction[i] = toNext / distance;
				trail.index[i] = trail.length;
				trail.length += distance;
			}

			trail.direction[last] = trail.direction[last - 1];
			trail.index[last] = trail.length;

			for(std::size_t i = last; i > 0; i--) {
				pixelpart::float3_t toEdge = trail.direction[i] - trail.direction[i - 1];
				pixelpart::float_t toEdgeLength = glm::length(toEdge);
				if(toEdgeLength < epsilon) {
					trail.directionToEdge[i] = pixelpart::float3_t(
						-trail.direction[i].y,
						trail.direction[i].x,
						trail.direction[i].z);
				}
				else {
					trail.directionToEdge[i] = (glm::dot(glm::cross(trail.direction[i], pixelpart::float3_t(0.0, 0.0, 1.0)), toEdge / toEdgeLength) < 0.0)
						? +toEdge / toEdgeLength
						: -toEdge / toEdgeLength;
				}
			}

			trail.directionToEdge[0] = trail.directionToEdge[1];

			for(pixelpart::float_t& index : trail.index) {
				index /= trail.length;
			}

			vertexCount += (static_cast<std::uint32_t>(trail.position.size()) - 1) * 12;
		}

		return vertexCount;
	}
	catch(const std::exception& e) {
		pixelpart_gms2::lastError = std::string(e.what());
	}

	return -1;
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

		pixelpart::float2_t uv[4] = {
			pixelpart::float2_t(0, 0),
			pixelpart::float2_t(1, 0),
			pixelpart::float2_t(1, 1),
			pixelpart::float2_t(0, 1)
		};

		pixelpart_gms2::VertexBuffer vertexBuffer(vertexBufferPtr);

		for(std::uint32_t p = 0; p < particleCount; p++) {
			pixelpart::float3_t position[4];
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

			vertexBuffer.addVertex(position[0], particles.color[p], uv[0], particles.velocity[p], particles.life[p], particles.id[p]);
			vertexBuffer.addVertex(position[1], particles.color[p], uv[1], particles.velocity[p], particles.life[p], particles.id[p]);
			vertexBuffer.addVertex(position[3], particles.color[p], uv[3], particles.velocity[p], particles.life[p], particles.id[p]);
			vertexBuffer.addVertex(position[1], particles.color[p], uv[1], particles.velocity[p], particles.life[p], particles.id[p]);
			vertexBuffer.addVertex(position[2], particles.color[p], uv[2], particles.velocity[p], particles.life[p], particles.id[p]);
			vertexBuffer.addVertex(position[3], particles.color[p], uv[3], particles.velocity[p], particles.life[p], particles.id[p]);
		}

		return 1;
	}
	catch(const std::exception& e) {
		pixelpart_gms2::lastError = std::string(e.what());
	}

	return -1;
}

GMS2_EXPORT pixelpart_gms2::real GMS2_API pixelpart_get_particle_trail_vertex_data(pixelpart_gms2::string runtimePtr, pixelpart_gms2::real particleEmitterId, pixelpart_gms2::real particleTypeId, pixelpart_gms2::string vertexBufferPtr) {
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

		if(!particleCollection || particleCollection->count() < 2) {
			return 0;
		}

		pixelpart::ParticleCollection::ReadPtr particles = particleCollection->readPtr();
		std::uint32_t particleCount = particleCollection->count();

		pixelpart_gms2::ParticleMeshData& meshData = effectRuntime->meshData[runtimeId];
		pixelpart_gms2::VertexBuffer vertexBuffer(vertexBufferPtr);

		for(const auto& entry : meshData.trails) {
			const pixelpart_gms2::TrailMeshData& trail = entry.second;
			if(trail.position.size() < 2) {
				continue;
			}

			std::uint32_t trailSegmentCount = static_cast<std::uint32_t>(trail.position.size()) - 1;

			for(std::uint32_t p = 0; p < trailSegmentCount; p++) {
				pixelpart::float3_t startToEdgeDirection = trail.directionToEdge[p];
				pixelpart::float3_t endToEdgeDirection = trail.directionToEdge[p + 1];

				pixelpart::float3_t startToEdge = startToEdgeDirection * std::max(trail.size[p].x, std::max(trail.size[p].y, trail.size[p].z)) * 0.5;
				pixelpart::float3_t endToEdge = endToEdgeDirection * std::max(trail.size[p + 1].x, std::max(trail.size[p + 1].y, trail.size[p + 1].z)) * 0.5;

				pixelpart::float3_t position[5] = {
					(trail.position[p] + startToEdge) * effectRuntime->effectScale,
					(trail.position[p] - startToEdge) * effectRuntime->effectScale,
					(trail.position[p + 1] + endToEdge) * effectRuntime->effectScale,
					(trail.position[p + 1] - endToEdge) * effectRuntime->effectScale,
					(trail.position[p] + trail.position[p + 1]) * 0.5 * effectRuntime->effectScale
				};

				pixelpart::float2_t uv[5];
				switch(particleType.trailRendererSettings().textureRotation) {
					case pixelpart::ParticleTrailRendererSettings::TextureRotation::left:
						uv[0] = pixelpart::float2_t(trail.index[p] * particleType.trailRendererSettings().textureUVFactor, 1.0);
						uv[1] = pixelpart::float2_t(trail.index[p] * particleType.trailRendererSettings().textureUVFactor, 0.0);
						uv[2] = pixelpart::float2_t(trail.index[p + 1] * particleType.trailRendererSettings().textureUVFactor, 1.0);
						uv[3] = pixelpart::float2_t(trail.index[p + 1] * particleType.trailRendererSettings().textureUVFactor, 0.0);
						uv[4] = pixelpart::float2_t((trail.index[p] + trail.index[p + 1]) * 0.5 * particleType.trailRendererSettings().textureUVFactor, 0.5);
						break;
					case pixelpart::ParticleTrailRendererSettings::TextureRotation::down:
						uv[0] = pixelpart::float2_t(1.0, 1.0 - trail.index[p] * particleType.trailRendererSettings().textureUVFactor);
						uv[1] = pixelpart::float2_t(0.0, 1.0 - trail.index[p] * particleType.trailRendererSettings().textureUVFactor);
						uv[2] = pixelpart::float2_t(1.0, 1.0 - trail.index[p + 1] * particleType.trailRendererSettings().textureUVFactor);
						uv[3] = pixelpart::float2_t(0.0, 1.0 - trail.index[p + 1] * particleType.trailRendererSettings().textureUVFactor);
						uv[4] = pixelpart::float2_t(0.5, 1.0 - (trail.index[p] + trail.index[p + 1]) * 0.5 * particleType.trailRendererSettings().textureUVFactor);
						break;
					case pixelpart::ParticleTrailRendererSettings::TextureRotation::right:
						uv[0] = pixelpart::float2_t(1.0 - trail.index[p] * particleType.trailRendererSettings().textureUVFactor, 0.0);
						uv[1] = pixelpart::float2_t(1.0 - trail.index[p] * particleType.trailRendererSettings().textureUVFactor, 1.0);
						uv[2] = pixelpart::float2_t(1.0 - trail.index[p + 1] * particleType.trailRendererSettings().textureUVFactor, 0.0);
						uv[3] = pixelpart::float2_t(1.0 - trail.index[p + 1] * particleType.trailRendererSettings().textureUVFactor, 1.0);
						uv[4] = pixelpart::float2_t(1.0 - (trail.index[p] + trail.index[p + 1]) * 0.5 * particleType.trailRendererSettings().textureUVFactor, 0.5);
						break;
					default:
						uv[0] = pixelpart::float2_t(0.0, trail.index[p] * particleType.trailRendererSettings().textureUVFactor);
						uv[1] = pixelpart::float2_t(1.0, trail.index[p] * particleType.trailRendererSettings().textureUVFactor);
						uv[2] = pixelpart::float2_t(0.0, trail.index[p + 1] * particleType.trailRendererSettings().textureUVFactor);
						uv[3] = pixelpart::float2_t(1.0, trail.index[p + 1] * particleType.trailRendererSettings().textureUVFactor);
						uv[4] = pixelpart::float2_t(0.5, (trail.index[p] + trail.index[p + 1]) * 0.5 * particleType.trailRendererSettings().textureUVFactor);
						break;
				}

				pixelpart::float4_t colorStart = trail.color[p];
				pixelpart::float4_t colorEnd = trail.color[p + 1];
				pixelpart::float4_t colorCenter = (trail.color[p] + trail.color[p + 1]) * 0.5;

				pixelpart::float3_t velocityStart = trail.velocity[p];
				pixelpart::float3_t velocityEnd = trail.velocity[p + 1];
				pixelpart::float3_t velocityCenter = (trail.velocity[p] + trail.velocity[p + 1]) * 0.5;

				pixelpart::float_t lifeStart = trail.life[p];
				pixelpart::float_t lifeEnd = trail.life[p + 1];
				pixelpart::float_t lifeCenter = (trail.life[p] + trail.life[p + 1]) * 0.5;

				vertexBuffer.addVertex(position[0], colorStart, uv[0], velocityStart, lifeStart, entry.first);
				vertexBuffer.addVertex(position[1], colorStart, uv[1], velocityStart, lifeStart, entry.first);
				vertexBuffer.addVertex(position[4], colorCenter, uv[4], velocityCenter, lifeCenter, entry.first);
				vertexBuffer.addVertex(position[2], colorEnd, uv[2], velocityEnd, lifeEnd, entry.first);
				vertexBuffer.addVertex(position[0], colorStart, uv[0], velocityStart, lifeStart, entry.first);
				vertexBuffer.addVertex(position[4], colorCenter, uv[4], velocityCenter, lifeCenter, entry.first);
				vertexBuffer.addVertex(position[1], colorStart, uv[1], velocityStart, lifeStart, entry.first);
				vertexBuffer.addVertex(position[3], colorEnd, uv[3], velocityEnd, lifeEnd, entry.first);
				vertexBuffer.addVertex(position[4], colorCenter, uv[4], velocityCenter, lifeCenter, entry.first);
				vertexBuffer.addVertex(position[3], colorEnd, uv[3], velocityEnd, lifeEnd, entry.first);
				vertexBuffer.addVertex(position[2], colorEnd, uv[2], velocityEnd, lifeEnd, entry.first);
				vertexBuffer.addVertex(position[4], colorCenter, uv[4], velocityCenter, lifeCenter, entry.first);
			}
		}

		return 1;
	}
	catch(const std::exception& e) {
		pixelpart_gms2::lastError = std::string(e.what());
	}

	return -1;
}
}