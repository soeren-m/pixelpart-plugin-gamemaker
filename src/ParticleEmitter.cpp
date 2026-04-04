#include "Common.h"
#include "Error.h"
#include "Buffer.h"
#include "EffectRuntime.h"
#include "pixelpart-runtime/common/Id.h"
#include "pixelpart-runtime/common/Types.h"
#include "pixelpart-runtime/common/Curve.h"
#include "pixelpart-runtime/math/Geometry.h"
#include "pixelpart-runtime/effect/AnimatedProperty.h"
#include "pixelpart-runtime/effect/ParticleEmitter.h"
#include <cstdint>
#include <cstring>
#include <string>
#include <vector>
#include <exception>
#include <algorithm>

namespace pixelpart_gm {
std::string particleEmitterPropertyPtrString = "";

void setParticleEmitterShapePoints(pixelpart::ParticleEmitter& particleEmitter, const std::vector<pixelpart::float3_t>& points) {
	std::vector<pixelpart::float_t> distances(points.size(), 0.0);
	pixelpart::float_t length = 0.0;

	for(std::size_t i = 1; i < points.size(); i++) {
		length += std::max(pixelpart::math::distance(points[i], points[i - 1]), 0.000001);
		distances[i] = length;
	}

	pixelpart::Curve<pixelpart::float3_t> modifiedPath;
	for(std::size_t i = 0; i < points.size(); i++) {
		modifiedPath.addPoint(distances[i] / length, points[i]);
	}

	particleEmitter.path() = modifiedPath;
}

std::vector<pixelpart::float3_t> getParticleEmitterShapePoints(const pixelpart::ParticleEmitter& particleEmitter) {
	std::vector<pixelpart::float3_t> points(particleEmitter.path().pointCount(), pixelpart::float3_t(0.0));
	for(std::size_t i = 0; i < particleEmitter.path().pointCount(); i++) {
		points[i] = particleEmitter.path().point(i).value;
	}

	return points;
}
}

extern "C" {
GM_EXPORT pixelpart_gm::real GM_API pixelpart_particle_emitter_set_shape(pixelpart_gm::string runtimePtr, pixelpart_gm::real emitterId, pixelpart_gm::real shape) {
	pixelpart_gm::EffectRuntime* effectRuntime = pixelpart_gm::parsePtr<pixelpart_gm::EffectRuntime>(runtimePtr);
	if(!effectRuntime) {
		pixelpart_gm::lastError = pixelpart_gm::invalidEffectRuntimeError;
		return -1;
	}

	try {
		pixelpart::ParticleEmitter& emitter =
			effectRuntime->effectAsset.effect().sceneGraph().at<pixelpart::ParticleEmitter>(pixelpart::id_t(emitterId));

		emitter.shape(static_cast<pixelpart::ParticleEmitter::Shape>(static_cast<std::uint32_t>(shape)));

		return 1;
	}
	catch(const std::exception& e) {
		pixelpart_gm::lastError = std::string(e.what());
	}

	return -1;
}

GM_EXPORT pixelpart_gm::real GM_API pixelpart_particle_emitter_get_shape(pixelpart_gm::string runtimePtr, pixelpart_gm::real emitterId) {
	pixelpart_gm::EffectRuntime* effectRuntime = pixelpart_gm::parsePtr<pixelpart_gm::EffectRuntime>(runtimePtr);
	if(!effectRuntime) {
		pixelpart_gm::lastError = pixelpart_gm::invalidEffectRuntimeError;
		return -1;
	}

	try {
		const pixelpart::ParticleEmitter& emitter =
			effectRuntime->effectAsset.effect().sceneGraph().at<pixelpart::ParticleEmitter>(pixelpart::id_t(emitterId));

		return static_cast<pixelpart_gm::real>(emitter.shape());
	}
	catch(const std::exception& e) {
		pixelpart_gm::lastError = std::string(e.what());
	}

	return -1;
}

GM_EXPORT pixelpart_gm::real GM_API pixelpart_particle_emitter_add_shape_point(pixelpart_gm::string runtimePtr, pixelpart_gm::real emitterId, pixelpart_gm::string valueBufferPtr) {
	pixelpart_gm::EffectRuntime* effectRuntime = pixelpart_gm::parsePtr<pixelpart_gm::EffectRuntime>(runtimePtr);
	if(!effectRuntime) {
		pixelpart_gm::lastError = pixelpart_gm::invalidEffectRuntimeError;
		return -1;
	}
	else if(!valueBufferPtr) {
		pixelpart_gm::lastError = pixelpart_gm::invalidArgumentError;
		return -1;
	}

	try {
		pixelpart::ParticleEmitter& emitter =
			effectRuntime->effectAsset.effect().sceneGraph().at<pixelpart::ParticleEmitter>(pixelpart::id_t(emitterId));

		std::vector<pixelpart::float3_t> points = pixelpart_gm::getParticleEmitterShapePoints(emitter);

		pixelpart_gm::Buffer valueBuffer(valueBufferPtr);
		points.push_back(valueBuffer.read<pixelpart::float3_t>());

		pixelpart_gm::setParticleEmitterShapePoints(emitter, points);

		return 1;
	}
	catch(const std::exception& e) {
		pixelpart_gm::lastError = std::string(e.what());
	}

	return -1;
}

GM_EXPORT pixelpart_gm::real GM_API pixelpart_particle_emitter_remove_shape_point(pixelpart_gm::string runtimePtr, pixelpart_gm::real emitterId, pixelpart_gm::real index) {
	pixelpart_gm::EffectRuntime* effectRuntime = pixelpart_gm::parsePtr<pixelpart_gm::EffectRuntime>(runtimePtr);
	if(!effectRuntime) {
		pixelpart_gm::lastError = pixelpart_gm::invalidEffectRuntimeError;
		return -1;
	}
	else if(index < 0) {
		pixelpart_gm::lastError = pixelpart_gm::invalidArgumentError;
		return -1;
	}

	try {
		pixelpart::ParticleEmitter& emitter =
			effectRuntime->effectAsset.effect().sceneGraph().at<pixelpart::ParticleEmitter>(pixelpart::id_t(emitterId));

		std::vector<pixelpart::float3_t> points = pixelpart_gm::getParticleEmitterShapePoints(emitter);
		points.erase(points.begin() + static_cast<std::size_t>(index));

		pixelpart_gm::setParticleEmitterShapePoints(emitter, points);

		return 1;
	}
	catch(const std::exception& e) {
		pixelpart_gm::lastError = std::string(e.what());
	}

	return -1;
}

GM_EXPORT pixelpart_gm::real GM_API pixelpart_particle_emitter_set_shape_point(pixelpart_gm::string runtimePtr, pixelpart_gm::real emitterId, pixelpart_gm::real index, pixelpart_gm::string valueBufferPtr) {
	pixelpart_gm::EffectRuntime* effectRuntime = pixelpart_gm::parsePtr<pixelpart_gm::EffectRuntime>(runtimePtr);
	if(!effectRuntime) {
		pixelpart_gm::lastError = pixelpart_gm::invalidEffectRuntimeError;
		return -1;
	}
	else if(index < 0 || !valueBufferPtr) {
		pixelpart_gm::lastError = pixelpart_gm::invalidArgumentError;
		return -1;
	}

	try {
		pixelpart::ParticleEmitter& emitter =
			effectRuntime->effectAsset.effect().sceneGraph().at<pixelpart::ParticleEmitter>(pixelpart::id_t(emitterId));

		std::vector<pixelpart::float3_t> points = pixelpart_gm::getParticleEmitterShapePoints(emitter);

		pixelpart_gm::Buffer valueBuffer(valueBufferPtr);
		points.at(static_cast<std::size_t>(index)) = valueBuffer.read<pixelpart::float3_t>();

		pixelpart_gm::setParticleEmitterShapePoints(emitter, points);

		return 1;
	}
	catch(const std::exception& e) {
		pixelpart_gm::lastError = std::string(e.what());
	}

	return -1;
}

GM_EXPORT pixelpart_gm::real GM_API pixelpart_particle_emitter_get_shape_point(pixelpart_gm::string runtimePtr, pixelpart_gm::real emitterId, pixelpart_gm::real index, pixelpart_gm::string valueBufferPtr) {
	pixelpart_gm::EffectRuntime* effectRuntime = pixelpart_gm::parsePtr<pixelpart_gm::EffectRuntime>(runtimePtr);
	if(!effectRuntime) {
		pixelpart_gm::lastError = pixelpart_gm::invalidEffectRuntimeError;
		return -1;
	}
	else if(index < 0 || !valueBufferPtr) {
		pixelpart_gm::lastError = pixelpart_gm::invalidArgumentError;
		return -1;
	}

	try {
		const pixelpart::ParticleEmitter& emitter =
			effectRuntime->effectAsset.effect().sceneGraph().at<pixelpart::ParticleEmitter>(pixelpart::id_t(emitterId));

		pixelpart_gm::Buffer valueBuffer(valueBufferPtr);
		valueBuffer.write(emitter.path().point(static_cast<std::size_t>(index)).value);

		return 1;
	}
	catch(const std::exception& e) {
		pixelpart_gm::lastError = std::string(e.what());
	}

	return -1;
}

GM_EXPORT pixelpart_gm::real GM_API pixelpart_particle_emitter_get_shape_point_count(pixelpart_gm::string runtimePtr, pixelpart_gm::real emitterId) {
	pixelpart_gm::EffectRuntime* effectRuntime = pixelpart_gm::parsePtr<pixelpart_gm::EffectRuntime>(runtimePtr);
	if(!effectRuntime) {
		pixelpart_gm::lastError = pixelpart_gm::invalidEffectRuntimeError;
		return -1;
	}

	try {
		const pixelpart::ParticleEmitter& emitter =
			effectRuntime->effectAsset.effect().sceneGraph().at<pixelpart::ParticleEmitter>(pixelpart::id_t(emitterId));

		return static_cast<pixelpart_gm::real>(emitter.path().pointCount());
	}
	catch(const std::exception& e) {
		pixelpart_gm::lastError = std::string(e.what());
	}

	return -1;
}

GM_EXPORT pixelpart_gm::real GM_API pixelpart_particle_emitter_set_distribution(pixelpart_gm::string runtimePtr, pixelpart_gm::real emitterId, pixelpart_gm::real mode) {
	pixelpart_gm::EffectRuntime* effectRuntime = pixelpart_gm::parsePtr<pixelpart_gm::EffectRuntime>(runtimePtr);
	if(!effectRuntime) {
		pixelpart_gm::lastError = pixelpart_gm::invalidEffectRuntimeError;
		return -1;
	}

	try {
		pixelpart::ParticleEmitter& emitter =
			effectRuntime->effectAsset.effect().sceneGraph().at<pixelpart::ParticleEmitter>(pixelpart::id_t(emitterId));

		emitter.distribution(static_cast<pixelpart::ParticleEmitter::Distribution>(mode));

		return 1;
	}
	catch(const std::exception& e) {
		pixelpart_gm::lastError = std::string(e.what());
	}

	return -1;
}

GM_EXPORT pixelpart_gm::real GM_API pixelpart_particle_emitter_get_distribution(pixelpart_gm::string runtimePtr, pixelpart_gm::real emitterId) {
	pixelpart_gm::EffectRuntime* effectRuntime = pixelpart_gm::parsePtr<pixelpart_gm::EffectRuntime>(runtimePtr);
	if(!effectRuntime) {
		pixelpart_gm::lastError = pixelpart_gm::invalidEffectRuntimeError;
		return -1;
	}

	try {
		const pixelpart::ParticleEmitter& emitter =
			effectRuntime->effectAsset.effect().sceneGraph().at<pixelpart::ParticleEmitter>(pixelpart::id_t(emitterId));

		return static_cast<pixelpart_gm::real>(emitter.distribution());
	}
	catch(const std::exception& e) {
		pixelpart_gm::lastError = std::string(e.what());
	}

	return -1;
}

GM_EXPORT pixelpart_gm::real GM_API pixelpart_particle_emitter_set_grid_order(pixelpart_gm::string runtimePtr, pixelpart_gm::real emitterId, pixelpart_gm::real mode) {
	pixelpart_gm::EffectRuntime* effectRuntime = pixelpart_gm::parsePtr<pixelpart_gm::EffectRuntime>(runtimePtr);
	if(!effectRuntime) {
		pixelpart_gm::lastError = pixelpart_gm::invalidEffectRuntimeError;
		return -1;
	}

	try {
		pixelpart::ParticleEmitter& emitter =
			effectRuntime->effectAsset.effect().sceneGraph().at<pixelpart::ParticleEmitter>(pixelpart::id_t(emitterId));

		emitter.gridOrder(static_cast<pixelpart::ParticleEmitter::GridOrder>(mode));

		return 1;
	}
	catch(const std::exception& e) {
		pixelpart_gm::lastError = std::string(e.what());
	}

	return -1;
}

GM_EXPORT pixelpart_gm::real GM_API pixelpart_particle_emitter_get_grid_order(pixelpart_gm::string runtimePtr, pixelpart_gm::real emitterId) {
	pixelpart_gm::EffectRuntime* effectRuntime = pixelpart_gm::parsePtr<pixelpart_gm::EffectRuntime>(runtimePtr);
	if(!effectRuntime) {
		pixelpart_gm::lastError = pixelpart_gm::invalidEffectRuntimeError;
		return -1;
	}

	try {
		const pixelpart::ParticleEmitter& emitter =
			effectRuntime->effectAsset.effect().sceneGraph().at<pixelpart::ParticleEmitter>(pixelpart::id_t(emitterId));

		return static_cast<pixelpart_gm::real>(emitter.gridOrder());
	}
	catch(const std::exception& e) {
		pixelpart_gm::lastError = std::string(e.what());
	}

	return -1;
}

GM_EXPORT pixelpart_gm::real GM_API pixelpart_particle_emitter_set_grid_size(pixelpart_gm::string runtimePtr, pixelpart_gm::real emitterId, pixelpart_gm::string valueBufferPtr) {
	pixelpart_gm::EffectRuntime* effectRuntime = pixelpart_gm::parsePtr<pixelpart_gm::EffectRuntime>(runtimePtr);
	if(!effectRuntime) {
		pixelpart_gm::lastError = pixelpart_gm::invalidEffectRuntimeError;
		return -1;
	}
	else if(!valueBufferPtr) {
		pixelpart_gm::lastError = pixelpart_gm::invalidArgumentError;
		return -1;
	}

	try {
		pixelpart::ParticleEmitter& emitter =
			effectRuntime->effectAsset.effect().sceneGraph().at<pixelpart::ParticleEmitter>(pixelpart::id_t(emitterId));

		pixelpart_gm::Buffer valueBuffer(valueBufferPtr);
		std::uint32_t gridSizeX = std::max(valueBuffer.read<pixelpart::float_t>(), 1.0);
		std::uint32_t gridSizeY = std::max(valueBuffer.read<pixelpart::float_t>(), 1.0);
		std::uint32_t gridSizeZ = std::max(valueBuffer.read<pixelpart::float_t>(), 1.0);

		emitter.gridSize(gridSizeX, gridSizeY, gridSizeZ);

		return 1;
	}
	catch(const std::exception& e) {
		pixelpart_gm::lastError = std::string(e.what());
	}

	return -1;
}

GM_EXPORT pixelpart_gm::real GM_API pixelpart_particle_emitter_get_grid_size_x(pixelpart_gm::string runtimePtr, pixelpart_gm::real emitterId) {
	pixelpart_gm::EffectRuntime* effectRuntime = pixelpart_gm::parsePtr<pixelpart_gm::EffectRuntime>(runtimePtr);
	if(!effectRuntime) {
		pixelpart_gm::lastError = pixelpart_gm::invalidEffectRuntimeError;
		return -1;
	}

	try {
		const pixelpart::ParticleEmitter& emitter =
			effectRuntime->effectAsset.effect().sceneGraph().at<pixelpart::ParticleEmitter>(pixelpart::id_t(emitterId));

		return static_cast<pixelpart_gm::real>(emitter.gridSizeX());
	}
	catch(const std::exception& e) {
		pixelpart_gm::lastError = std::string(e.what());
	}

	return -1;
}

GM_EXPORT pixelpart_gm::real GM_API pixelpart_particle_emitter_get_grid_size_y(pixelpart_gm::string runtimePtr, pixelpart_gm::real emitterId) {
	pixelpart_gm::EffectRuntime* effectRuntime = pixelpart_gm::parsePtr<pixelpart_gm::EffectRuntime>(runtimePtr);
	if(!effectRuntime) {
		pixelpart_gm::lastError = pixelpart_gm::invalidEffectRuntimeError;
		return -1;
	}

	try {
		const pixelpart::ParticleEmitter& emitter =
			effectRuntime->effectAsset.effect().sceneGraph().at<pixelpart::ParticleEmitter>(pixelpart::id_t(emitterId));

		return static_cast<pixelpart_gm::real>(emitter.gridSizeY());
	}
	catch(const std::exception& e) {
		pixelpart_gm::lastError = std::string(e.what());
	}

	return -1;
}

GM_EXPORT pixelpart_gm::real GM_API pixelpart_particle_emitter_get_grid_size_z(pixelpart_gm::string runtimePtr, pixelpart_gm::real emitterId) {
	pixelpart_gm::EffectRuntime* effectRuntime = pixelpart_gm::parsePtr<pixelpart_gm::EffectRuntime>(runtimePtr);
	if(!effectRuntime) {
		pixelpart_gm::lastError = pixelpart_gm::invalidEffectRuntimeError;
		return -1;
	}

	try {
		const pixelpart::ParticleEmitter& emitter =
			effectRuntime->effectAsset.effect().sceneGraph().at<pixelpart::ParticleEmitter>(pixelpart::id_t(emitterId));

		return static_cast<pixelpart_gm::real>(emitter.gridSizeZ());
	}
	catch(const std::exception& e) {
		pixelpart_gm::lastError = std::string(e.what());
	}

	return -1;
}

GM_EXPORT pixelpart_gm::real GM_API pixelpart_particle_emitter_set_emission_mode(pixelpart_gm::string runtimePtr, pixelpart_gm::real emitterId, pixelpart_gm::real mode) {
	pixelpart_gm::EffectRuntime* effectRuntime = pixelpart_gm::parsePtr<pixelpart_gm::EffectRuntime>(runtimePtr);
	if(!effectRuntime) {
		pixelpart_gm::lastError = pixelpart_gm::invalidEffectRuntimeError;
		return -1;
	}

	try {
		pixelpart::ParticleEmitter& emitter =
			effectRuntime->effectAsset.effect().sceneGraph().at<pixelpart::ParticleEmitter>(pixelpart::id_t(emitterId));

		emitter.emissionMode(static_cast<pixelpart::ParticleEmitter::EmissionMode>(mode));

		return 1;
	}
	catch(const std::exception& e) {
		pixelpart_gm::lastError = std::string(e.what());
	}

	return -1;
}

GM_EXPORT pixelpart_gm::real GM_API pixelpart_particle_emitter_get_emission_mode(pixelpart_gm::string runtimePtr, pixelpart_gm::real emitterId) {
	pixelpart_gm::EffectRuntime* effectRuntime = pixelpart_gm::parsePtr<pixelpart_gm::EffectRuntime>(runtimePtr);
	if(!effectRuntime) {
		pixelpart_gm::lastError = pixelpart_gm::invalidEffectRuntimeError;
		return -1;
	}

	try {
		const pixelpart::ParticleEmitter& emitter =
			effectRuntime->effectAsset.effect().sceneGraph().at<pixelpart::ParticleEmitter>(pixelpart::id_t(emitterId));

		return static_cast<pixelpart_gm::real>(emitter.emissionMode());
	}
	catch(const std::exception& e) {
		pixelpart_gm::lastError = std::string(e.what());
	}

	return -1;
}

GM_EXPORT pixelpart_gm::real GM_API pixelpart_particle_emitter_set_direction_mode(pixelpart_gm::string runtimePtr, pixelpart_gm::real emitterId, pixelpart_gm::real mode) {
	pixelpart_gm::EffectRuntime* effectRuntime = pixelpart_gm::parsePtr<pixelpart_gm::EffectRuntime>(runtimePtr);
	if(!effectRuntime) {
		pixelpart_gm::lastError = pixelpart_gm::invalidEffectRuntimeError;
		return -1;
	}

	try {
		pixelpart::ParticleEmitter& emitter =
			effectRuntime->effectAsset.effect().sceneGraph().at<pixelpart::ParticleEmitter>(pixelpart::id_t(emitterId));

		emitter.directionMode(static_cast<pixelpart::ParticleEmitter::DirectionMode>(mode));

		return 1;
	}
	catch(const std::exception& e) {
		pixelpart_gm::lastError = std::string(e.what());
	}

	return -1;
}

GM_EXPORT pixelpart_gm::real GM_API pixelpart_particle_emitter_get_direction_mode(pixelpart_gm::string runtimePtr, pixelpart_gm::real emitterId) {
	pixelpart_gm::EffectRuntime* effectRuntime = pixelpart_gm::parsePtr<pixelpart_gm::EffectRuntime>(runtimePtr);
	if(!effectRuntime) {
		pixelpart_gm::lastError = pixelpart_gm::invalidEffectRuntimeError;
		return -1;
	}

	try {
		const pixelpart::ParticleEmitter& emitter =
			effectRuntime->effectAsset.effect().sceneGraph().at<pixelpart::ParticleEmitter>(pixelpart::id_t(emitterId));

		return static_cast<pixelpart_gm::real>(emitter.directionMode());
	}
	catch(const std::exception& e) {
		pixelpart_gm::lastError = std::string(e.what());
	}

	return -1;
}

GM_EXPORT pixelpart_gm::const_string GM_API pixelpart_particle_emitter_get_direction(pixelpart_gm::string runtimePtr, pixelpart_gm::real emitterId) {
	pixelpart_gm::EffectRuntime* effectRuntime = pixelpart_gm::parsePtr<pixelpart_gm::EffectRuntime>(runtimePtr);
	if(!effectRuntime) {
		pixelpart_gm::lastError = pixelpart_gm::invalidEffectRuntimeError;
		pixelpart_gm::particleEmitterPropertyPtrString = "";

		return pixelpart_gm::particleEmitterPropertyPtrString.c_str();
	}

	try {
		pixelpart::ParticleEmitter& emitter =
			effectRuntime->effectAsset.effect().sceneGraph().at<pixelpart::ParticleEmitter>(pixelpart::id_t(emitterId));

		pixelpart_gm::particleEmitterPropertyPtrString = pixelpart_gm::ptrToString(&emitter.direction());
	}
	catch(const std::exception& e) {
		pixelpart_gm::lastError = std::string(e.what());
		pixelpart_gm::particleEmitterPropertyPtrString = "";
	}

	return pixelpart_gm::particleEmitterPropertyPtrString.c_str();
}

GM_EXPORT pixelpart_gm::const_string GM_API pixelpart_particle_emitter_get_spread(pixelpart_gm::string runtimePtr, pixelpart_gm::real emitterId) {
	pixelpart_gm::EffectRuntime* effectRuntime = pixelpart_gm::parsePtr<pixelpart_gm::EffectRuntime>(runtimePtr);
	if(!effectRuntime) {
		pixelpart_gm::lastError = pixelpart_gm::invalidEffectRuntimeError;
		pixelpart_gm::particleEmitterPropertyPtrString = "";

		return pixelpart_gm::particleEmitterPropertyPtrString.c_str();
	}

	try {
		pixelpart::ParticleEmitter& emitter =
			effectRuntime->effectAsset.effect().sceneGraph().at<pixelpart::ParticleEmitter>(pixelpart::id_t(emitterId));

		pixelpart_gm::particleEmitterPropertyPtrString = pixelpart_gm::ptrToString(&emitter.spread());
	}
	catch(const std::exception& e) {
		pixelpart_gm::lastError = std::string(e.what());
		pixelpart_gm::particleEmitterPropertyPtrString = "";
	}

	return pixelpart_gm::particleEmitterPropertyPtrString.c_str();
}
}
