#include "Common.h"
#include "Error.h"
#include "Buffer.h"
#include "EffectRuntime.h"
#include "pixelpart-runtime/types/Types.h"
#include "pixelpart-runtime/types/Id.h"
#include "pixelpart-runtime/effect/StaticProperty.h"
#include "pixelpart-runtime/effect/AnimatedProperty.h"
#include "pixelpart-runtime/effect/ForceField.h"
#include "pixelpart-runtime/effect/AttractionField.h"
#include "pixelpart-runtime/effect/AccelerationField.h"
#include "pixelpart-runtime/effect/VectorField.h"
#include "pixelpart-runtime/effect/NoiseField.h"
#include "pixelpart-runtime/effect/DragField.h"
#include <cstdint>
#include <string>
#include <exception>
#include <algorithm>

namespace pixelpart_gm {
std::string forceFieldPropertyPtrString = "";
}

extern "C" {
GM_EXPORT pixelpart_gm::real GM_API pixelpart_force_field_set_infinite(pixelpart_gm::string runtimePtr, pixelpart_gm::real forceFieldId, pixelpart_gm::real mode) {
	pixelpart_gm::EffectRuntime* effectRuntime = pixelpart_gm::parsePtr<pixelpart_gm::EffectRuntime>(runtimePtr);
	if(!effectRuntime) {
		pixelpart_gm::lastError = pixelpart_gm::invalidEffectRuntimeError;
		return -1;
	}

	try {
		pixelpart::ForceField& forceField =
			effectRuntime->effectAsset.effect().sceneGraph().at<pixelpart::ForceField>(pixelpart::id_t(forceFieldId));

		forceField.infinite(mode);

		return 1;
	}
	catch(const std::exception& e) {
		pixelpart_gm::lastError = std::string(e.what());
	}

	return -1;
}

GM_EXPORT pixelpart_gm::real GM_API pixelpart_force_field_is_infinite(pixelpart_gm::string runtimePtr, pixelpart_gm::real forceFieldId) {
	pixelpart_gm::EffectRuntime* effectRuntime = pixelpart_gm::parsePtr<pixelpart_gm::EffectRuntime>(runtimePtr);
	if(!effectRuntime) {
		pixelpart_gm::lastError = pixelpart_gm::invalidEffectRuntimeError;
		return -1;
	}

	try {
		const pixelpart::ForceField& forceField =
			effectRuntime->effectAsset.effect().sceneGraph().at<pixelpart::ForceField>(pixelpart::id_t(forceFieldId));

		return forceField.infinite() ? 1 : 0;
	}
	catch(const std::exception& e) {
		pixelpart_gm::lastError = std::string(e.what());
	}

	return -1;
}

GM_EXPORT pixelpart_gm::const_string GM_API pixelpart_force_field_get_strength(pixelpart_gm::string runtimePtr, pixelpart_gm::real forceFieldId) {
	pixelpart_gm::EffectRuntime* effectRuntime = pixelpart_gm::parsePtr<pixelpart_gm::EffectRuntime>(runtimePtr);
	if(!effectRuntime) {
		pixelpart_gm::lastError = pixelpart_gm::invalidEffectRuntimeError;
		pixelpart_gm::forceFieldPropertyPtrString = "";

		return pixelpart_gm::forceFieldPropertyPtrString.c_str();
	}

	try {
		pixelpart::ForceField& forceField =
			effectRuntime->effectAsset.effect().sceneGraph().at<pixelpart::ForceField>(pixelpart::id_t(forceFieldId));

		pixelpart_gm::forceFieldPropertyPtrString = pixelpart_gm::ptrToString(
			&forceField.strength());
	}
	catch(const std::exception& e) {
		pixelpart_gm::lastError = std::string(e.what());
		pixelpart_gm::forceFieldPropertyPtrString = "";
	}

	return pixelpart_gm::forceFieldPropertyPtrString.c_str();
}

GM_EXPORT pixelpart_gm::const_string GM_API pixelpart_attraction_field_get_falloff_power(pixelpart_gm::string runtimePtr, pixelpart_gm::real forceFieldId) {
	pixelpart_gm::EffectRuntime* effectRuntime = pixelpart_gm::parsePtr<pixelpart_gm::EffectRuntime>(runtimePtr);
	if(!effectRuntime) {
		pixelpart_gm::lastError = pixelpart_gm::invalidEffectRuntimeError;
		pixelpart_gm::forceFieldPropertyPtrString = "";

		return pixelpart_gm::forceFieldPropertyPtrString.c_str();
	}

	try {
		pixelpart::AttractionField& forceField =
			effectRuntime->effectAsset.effect().sceneGraph().at<pixelpart::AttractionField>(pixelpart::id_t(forceFieldId));

		pixelpart_gm::forceFieldPropertyPtrString = pixelpart_gm::ptrToString(
			&forceField.falloffPower());
	}
	catch(const std::exception& e) {
		pixelpart_gm::lastError = std::string(e.what());
		pixelpart_gm::forceFieldPropertyPtrString = "";
	}

	return pixelpart_gm::forceFieldPropertyPtrString.c_str();
}

GM_EXPORT pixelpart_gm::const_string GM_API pixelpart_acceleration_field_get_acceleration_direction(pixelpart_gm::string runtimePtr, pixelpart_gm::real forceFieldId) {
	pixelpart_gm::EffectRuntime* effectRuntime = pixelpart_gm::parsePtr<pixelpart_gm::EffectRuntime>(runtimePtr);
	if(!effectRuntime) {
		pixelpart_gm::lastError = pixelpart_gm::invalidEffectRuntimeError;
		pixelpart_gm::forceFieldPropertyPtrString = "";

		return pixelpart_gm::forceFieldPropertyPtrString.c_str();
	}

	try {
		pixelpart::AccelerationField& forceField =
			effectRuntime->effectAsset.effect().sceneGraph().at<pixelpart::AccelerationField>(pixelpart::id_t(forceFieldId));

		pixelpart_gm::forceFieldPropertyPtrString = pixelpart_gm::ptrToString(
			&forceField.accelerationDirection());
	}
	catch(const std::exception& e) {
		pixelpart_gm::lastError = std::string(e.what());
		pixelpart_gm::forceFieldPropertyPtrString = "";
	}

	return pixelpart_gm::forceFieldPropertyPtrString.c_str();
}

GM_EXPORT pixelpart_gm::const_string GM_API pixelpart_acceleration_field_get_acceleration_direction_variance(pixelpart_gm::string runtimePtr, pixelpart_gm::real forceFieldId) {
	pixelpart_gm::EffectRuntime* effectRuntime = pixelpart_gm::parsePtr<pixelpart_gm::EffectRuntime>(runtimePtr);
	if(!effectRuntime) {
		pixelpart_gm::lastError = pixelpart_gm::invalidEffectRuntimeError;
		pixelpart_gm::forceFieldPropertyPtrString = "";

		return pixelpart_gm::forceFieldPropertyPtrString.c_str();
	}

	try {
		pixelpart::AccelerationField& forceField =
			effectRuntime->effectAsset.effect().sceneGraph().at<pixelpart::AccelerationField>(pixelpart::id_t(forceFieldId));

		pixelpart_gm::forceFieldPropertyPtrString = pixelpart_gm::ptrToString(
			&forceField.accelerationDirectionVariance());
	}
	catch(const std::exception& e) {
		pixelpart_gm::lastError = std::string(e.what());
		pixelpart_gm::forceFieldPropertyPtrString = "";
	}

	return pixelpart_gm::forceFieldPropertyPtrString.c_str();
}

GM_EXPORT pixelpart_gm::const_string GM_API pixelpart_acceleration_field_get_acceleration_strength_variance(pixelpart_gm::string runtimePtr, pixelpart_gm::real forceFieldId) {
	pixelpart_gm::EffectRuntime* effectRuntime = pixelpart_gm::parsePtr<pixelpart_gm::EffectRuntime>(runtimePtr);
	if(!effectRuntime) {
		pixelpart_gm::lastError = pixelpart_gm::invalidEffectRuntimeError;
		pixelpart_gm::forceFieldPropertyPtrString = "";

		return pixelpart_gm::forceFieldPropertyPtrString.c_str();
	}

	try {
		pixelpart::AccelerationField& forceField =
			effectRuntime->effectAsset.effect().sceneGraph().at<pixelpart::AccelerationField>(pixelpart::id_t(forceFieldId));

		pixelpart_gm::forceFieldPropertyPtrString = pixelpart_gm::ptrToString(
			&forceField.accelerationStrengthVariance());
	}
	catch(const std::exception& e) {
		pixelpart_gm::lastError = std::string(e.what());
		pixelpart_gm::forceFieldPropertyPtrString = "";
	}

	return pixelpart_gm::forceFieldPropertyPtrString.c_str();
}

GM_EXPORT pixelpart_gm::real GM_API pixelpart_acceleration_field_set_acceleration_grid_size(pixelpart_gm::string runtimePtr, pixelpart_gm::real forceFieldId, pixelpart_gm::string valueBufferPtr) {
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
		pixelpart::AccelerationField& forceField =
			effectRuntime->effectAsset.effect().sceneGraph().at<pixelpart::AccelerationField>(pixelpart::id_t(forceFieldId));

		pixelpart_gm::Buffer valueBuffer(valueBufferPtr);
		std::int32_t x = static_cast<std::int32_t>(std::max(valueBuffer.read<pixelpart::float_t>(), 1.0));
		std::int32_t y = static_cast<std::int32_t>(std::max(valueBuffer.read<pixelpart::float_t>(), 1.0));
		std::int32_t z = static_cast<std::int32_t>(std::max(valueBuffer.read<pixelpart::float_t>(), 1.0));

		forceField.accelerationGrid(x, y, z);
		forceField.randomizeAccelerationGrid(pixelpart_gm::rng);

		return 1;
	}
	catch(const std::exception& e) {
		pixelpart_gm::lastError = std::string(e.what());
	}

	return -1;
}

GM_EXPORT pixelpart_gm::real GM_API pixelpart_acceleration_field_get_acceleration_grid_size_x(pixelpart_gm::string runtimePtr, pixelpart_gm::real forceFieldId) {
	pixelpart_gm::EffectRuntime* effectRuntime = pixelpart_gm::parsePtr<pixelpart_gm::EffectRuntime>(runtimePtr);
	if(!effectRuntime) {
		pixelpart_gm::lastError = pixelpart_gm::invalidEffectRuntimeError;
		return -1;
	}

	try {
		const pixelpart::AccelerationField& forceField =
			effectRuntime->effectAsset.effect().sceneGraph().at<pixelpart::AccelerationField>(pixelpart::id_t(forceFieldId));

		return forceField.accelerationGridSizeX();
	}
	catch(const std::exception& e) {
		pixelpart_gm::lastError = std::string(e.what());
	}

	return -1;
}

GM_EXPORT pixelpart_gm::real GM_API pixelpart_acceleration_field_get_acceleration_grid_size_y(pixelpart_gm::string runtimePtr, pixelpart_gm::real forceFieldId) {
	pixelpart_gm::EffectRuntime* effectRuntime = pixelpart_gm::parsePtr<pixelpart_gm::EffectRuntime>(runtimePtr);
	if(!effectRuntime) {
		pixelpart_gm::lastError = pixelpart_gm::invalidEffectRuntimeError;
		return -1;
	}

	try {
		const pixelpart::AccelerationField& forceField =
			effectRuntime->effectAsset.effect().sceneGraph().at<pixelpart::AccelerationField>(pixelpart::id_t(forceFieldId));

		return forceField.accelerationGridSizeY();
	}
	catch(const std::exception& e) {
		pixelpart_gm::lastError = std::string(e.what());
	}

	return -1;
}

GM_EXPORT pixelpart_gm::real GM_API pixelpart_acceleration_field_get_acceleration_grid_size_z(pixelpart_gm::string runtimePtr, pixelpart_gm::real forceFieldId) {
	pixelpart_gm::EffectRuntime* effectRuntime = pixelpart_gm::parsePtr<pixelpart_gm::EffectRuntime>(runtimePtr);
	if(!effectRuntime) {
		pixelpart_gm::lastError = pixelpart_gm::invalidEffectRuntimeError;
		return -1;
	}

	try {
		const pixelpart::AccelerationField& forceField =
			effectRuntime->effectAsset.effect().sceneGraph().at<pixelpart::AccelerationField>(pixelpart::id_t(forceFieldId));

		return forceField.accelerationGridSizeZ();
	}
	catch(const std::exception& e) {
		pixelpart_gm::lastError = std::string(e.what());
	}

	return -1;
}

GM_EXPORT pixelpart_gm::real GM_API pixelpart_vector_field_set_vector_field_filter(pixelpart_gm::string runtimePtr, pixelpart_gm::real forceFieldId, pixelpart_gm::real filter) {
	pixelpart_gm::EffectRuntime* effectRuntime = pixelpart_gm::parsePtr<pixelpart_gm::EffectRuntime>(runtimePtr);
	if(!effectRuntime) {
		pixelpart_gm::lastError = pixelpart_gm::invalidEffectRuntimeError;
		return -1;
	}

	try {
		pixelpart::VectorField& forceField =
			effectRuntime->effectAsset.effect().sceneGraph().at<pixelpart::VectorField>(pixelpart::id_t(forceFieldId));

		forceField.vectorFieldFilter(static_cast<pixelpart::VectorField::Filter>(filter));

		return 1;
	}
	catch(const std::exception& e) {
		pixelpart_gm::lastError = std::string(e.what());
	}

	return -1;
}

GM_EXPORT pixelpart_gm::real GM_API pixelpart_vector_field_get_vector_field_filter(pixelpart_gm::string runtimePtr, pixelpart_gm::real forceFieldId) {
	pixelpart_gm::EffectRuntime* effectRuntime = pixelpart_gm::parsePtr<pixelpart_gm::EffectRuntime>(runtimePtr);
	if(!effectRuntime) {
		pixelpart_gm::lastError = pixelpart_gm::invalidEffectRuntimeError;
		return -1;
	}

	try {
		const pixelpart::VectorField& forceField =
			effectRuntime->effectAsset.effect().sceneGraph().at<pixelpart::VectorField>(pixelpart::id_t(forceFieldId));

		return static_cast<pixelpart_gm::real>(forceField.vectorFieldFilter());
	}
	catch(const std::exception& e) {
		pixelpart_gm::lastError = std::string(e.what());
	}

	return -1;
}

GM_EXPORT pixelpart_gm::const_string GM_API pixelpart_vector_field_get_tightness(pixelpart_gm::string runtimePtr, pixelpart_gm::real forceFieldId) {
	pixelpart_gm::EffectRuntime* effectRuntime = pixelpart_gm::parsePtr<pixelpart_gm::EffectRuntime>(runtimePtr);
	if(!effectRuntime) {
		pixelpart_gm::lastError = pixelpart_gm::invalidEffectRuntimeError;
		pixelpart_gm::forceFieldPropertyPtrString = "";

		return pixelpart_gm::forceFieldPropertyPtrString.c_str();
	}

	try {
		pixelpart::VectorField& forceField =
			effectRuntime->effectAsset.effect().sceneGraph().at<pixelpart::VectorField>(pixelpart::id_t(forceFieldId));

		pixelpart_gm::forceFieldPropertyPtrString = pixelpart_gm::ptrToString(
			&forceField.tightness());
	}
	catch(const std::exception& e) {
		pixelpart_gm::lastError = std::string(e.what());
		pixelpart_gm::forceFieldPropertyPtrString = "";
	}

	return pixelpart_gm::forceFieldPropertyPtrString.c_str();
}

GM_EXPORT pixelpart_gm::const_string GM_API pixelpart_noise_field_get_noise_octaves(pixelpart_gm::string runtimePtr, pixelpart_gm::real forceFieldId) {
	pixelpart_gm::EffectRuntime* effectRuntime = pixelpart_gm::parsePtr<pixelpart_gm::EffectRuntime>(runtimePtr);
	if(!effectRuntime) {
		pixelpart_gm::lastError = pixelpart_gm::invalidEffectRuntimeError;
		pixelpart_gm::forceFieldPropertyPtrString = "";

		return pixelpart_gm::forceFieldPropertyPtrString.c_str();
	}

	try {
		pixelpart::NoiseField& forceField =
			effectRuntime->effectAsset.effect().sceneGraph().at<pixelpart::NoiseField>(pixelpart::id_t(forceFieldId));

		pixelpart_gm::forceFieldPropertyPtrString = pixelpart_gm::ptrToString(
			&forceField.noiseOctaves());
	}
	catch(const std::exception& e) {
		pixelpart_gm::lastError = std::string(e.what());
		pixelpart_gm::forceFieldPropertyPtrString = "";
	}

	return pixelpart_gm::forceFieldPropertyPtrString.c_str();
}

GM_EXPORT pixelpart_gm::const_string GM_API pixelpart_noise_field_get_noise_frequency(pixelpart_gm::string runtimePtr, pixelpart_gm::real forceFieldId) {
	pixelpart_gm::EffectRuntime* effectRuntime = pixelpart_gm::parsePtr<pixelpart_gm::EffectRuntime>(runtimePtr);
	if(!effectRuntime) {
		pixelpart_gm::lastError = pixelpart_gm::invalidEffectRuntimeError;
		pixelpart_gm::forceFieldPropertyPtrString = "";

		return pixelpart_gm::forceFieldPropertyPtrString.c_str();
	}

	try {
		pixelpart::NoiseField& forceField =
			effectRuntime->effectAsset.effect().sceneGraph().at<pixelpart::NoiseField>(pixelpart::id_t(forceFieldId));

		pixelpart_gm::forceFieldPropertyPtrString = pixelpart_gm::ptrToString(
			&forceField.noiseFrequency());
	}
	catch(const std::exception& e) {
		pixelpart_gm::lastError = std::string(e.what());
		pixelpart_gm::forceFieldPropertyPtrString = "";
	}

	return pixelpart_gm::forceFieldPropertyPtrString.c_str();
}

GM_EXPORT pixelpart_gm::const_string GM_API pixelpart_noise_field_get_noise_persistence(pixelpart_gm::string runtimePtr, pixelpart_gm::real forceFieldId) {
	pixelpart_gm::EffectRuntime* effectRuntime = pixelpart_gm::parsePtr<pixelpart_gm::EffectRuntime>(runtimePtr);
	if(!effectRuntime) {
		pixelpart_gm::lastError = pixelpart_gm::invalidEffectRuntimeError;
		pixelpart_gm::forceFieldPropertyPtrString = "";

		return pixelpart_gm::forceFieldPropertyPtrString.c_str();
	}

	try {
		pixelpart::NoiseField& forceField =
			effectRuntime->effectAsset.effect().sceneGraph().at<pixelpart::NoiseField>(pixelpart::id_t(forceFieldId));

		pixelpart_gm::forceFieldPropertyPtrString = pixelpart_gm::ptrToString(
			&forceField.noisePersistence());
	}
	catch(const std::exception& e) {
		pixelpart_gm::lastError = std::string(e.what());
		pixelpart_gm::forceFieldPropertyPtrString = "";
	}

	return pixelpart_gm::forceFieldPropertyPtrString.c_str();
}

GM_EXPORT pixelpart_gm::const_string GM_API pixelpart_noise_field_get_noise_lacunarity(pixelpart_gm::string runtimePtr, pixelpart_gm::real forceFieldId) {
	pixelpart_gm::EffectRuntime* effectRuntime = pixelpart_gm::parsePtr<pixelpart_gm::EffectRuntime>(runtimePtr);
	if(!effectRuntime) {
		pixelpart_gm::lastError = pixelpart_gm::invalidEffectRuntimeError;
		pixelpart_gm::forceFieldPropertyPtrString = "";

		return pixelpart_gm::forceFieldPropertyPtrString.c_str();
	}

	try {
		pixelpart::NoiseField& forceField =
			effectRuntime->effectAsset.effect().sceneGraph().at<pixelpart::NoiseField>(pixelpart::id_t(forceFieldId));

		pixelpart_gm::forceFieldPropertyPtrString = pixelpart_gm::ptrToString(
			&forceField.noiseLacunarity());
	}
	catch(const std::exception& e) {
		pixelpart_gm::lastError = std::string(e.what());
		pixelpart_gm::forceFieldPropertyPtrString = "";
	}

	return pixelpart_gm::forceFieldPropertyPtrString.c_str();
}

GM_EXPORT pixelpart_gm::real GM_API pixelpart_noise_field_set_noise_animated(pixelpart_gm::string runtimePtr, pixelpart_gm::real forceFieldId, pixelpart_gm::real animated) {
	pixelpart_gm::EffectRuntime* effectRuntime = pixelpart_gm::parsePtr<pixelpart_gm::EffectRuntime>(runtimePtr);
	if(!effectRuntime) {
		pixelpart_gm::lastError = pixelpart_gm::invalidEffectRuntimeError;
		return -1;
	}

	try {
		pixelpart::NoiseField& forceField =
			effectRuntime->effectAsset.effect().sceneGraph().at<pixelpart::NoiseField>(pixelpart::id_t(forceFieldId));

		forceField.noiseAnimated(animated);

		return 1;
	}
	catch(const std::exception& e) {
		pixelpart_gm::lastError = std::string(e.what());
	}

	return -1;
}

GM_EXPORT pixelpart_gm::real GM_API pixelpart_noise_field_is_noise_animated(pixelpart_gm::string runtimePtr, pixelpart_gm::real forceFieldId) {
	pixelpart_gm::EffectRuntime* effectRuntime = pixelpart_gm::parsePtr<pixelpart_gm::EffectRuntime>(runtimePtr);
	if(!effectRuntime) {
		pixelpart_gm::lastError = pixelpart_gm::invalidEffectRuntimeError;
		return -1;
	}

	try {
		const pixelpart::NoiseField& forceField =
			effectRuntime->effectAsset.effect().sceneGraph().at<pixelpart::NoiseField>(pixelpart::id_t(forceFieldId));

		return forceField.noiseAnimated() ? 1 : 0;
	}
	catch(const std::exception& e) {
		pixelpart_gm::lastError = std::string(e.what());
	}

	return -1;
}

GM_EXPORT pixelpart_gm::const_string GM_API pixelpart_noise_field_get_noise_animation_time_scale(pixelpart_gm::string runtimePtr, pixelpart_gm::real forceFieldId) {
	pixelpart_gm::EffectRuntime* effectRuntime = pixelpart_gm::parsePtr<pixelpart_gm::EffectRuntime>(runtimePtr);
	if(!effectRuntime) {
		pixelpart_gm::lastError = pixelpart_gm::invalidEffectRuntimeError;
		pixelpart_gm::forceFieldPropertyPtrString = "";

		return pixelpart_gm::forceFieldPropertyPtrString.c_str();
	}

	try {
		pixelpart::NoiseField& forceField =
			effectRuntime->effectAsset.effect().sceneGraph().at<pixelpart::NoiseField>(pixelpart::id_t(forceFieldId));

		pixelpart_gm::forceFieldPropertyPtrString = pixelpart_gm::ptrToString(
			&forceField.noiseAnimationTimeScale());
	}
	catch(const std::exception& e) {
		pixelpart_gm::lastError = std::string(e.what());
		pixelpart_gm::forceFieldPropertyPtrString = "";
	}

	return pixelpart_gm::forceFieldPropertyPtrString.c_str();
}

GM_EXPORT pixelpart_gm::const_string GM_API pixelpart_noise_field_get_noise_animation_time_base(pixelpart_gm::string runtimePtr, pixelpart_gm::real forceFieldId) {
	pixelpart_gm::EffectRuntime* effectRuntime = pixelpart_gm::parsePtr<pixelpart_gm::EffectRuntime>(runtimePtr);
	if(!effectRuntime) {
		pixelpart_gm::lastError = pixelpart_gm::invalidEffectRuntimeError;
		pixelpart_gm::forceFieldPropertyPtrString = "";

		return pixelpart_gm::forceFieldPropertyPtrString.c_str();
	}

	try {
		pixelpart::NoiseField& forceField =
			effectRuntime->effectAsset.effect().sceneGraph().at<pixelpart::NoiseField>(pixelpart::id_t(forceFieldId));

		pixelpart_gm::forceFieldPropertyPtrString = pixelpart_gm::ptrToString(
			&forceField.noiseAnimationTimeBase());
	}
	catch(const std::exception& e) {
		pixelpart_gm::lastError = std::string(e.what());
		pixelpart_gm::forceFieldPropertyPtrString = "";
	}

	return pixelpart_gm::forceFieldPropertyPtrString.c_str();
}

GM_EXPORT pixelpart_gm::const_string GM_API pixelpart_drag_field_get_velocity_influence(pixelpart_gm::string runtimePtr, pixelpart_gm::real forceFieldId) {
	pixelpart_gm::EffectRuntime* effectRuntime = pixelpart_gm::parsePtr<pixelpart_gm::EffectRuntime>(runtimePtr);
	if(!effectRuntime) {
		pixelpart_gm::lastError = pixelpart_gm::invalidEffectRuntimeError;
		pixelpart_gm::forceFieldPropertyPtrString = "";

		return pixelpart_gm::forceFieldPropertyPtrString.c_str();
	}

	try {
		pixelpart::DragField& forceField =
			effectRuntime->effectAsset.effect().sceneGraph().at<pixelpart::DragField>(pixelpart::id_t(forceFieldId));

		pixelpart_gm::forceFieldPropertyPtrString = pixelpart_gm::ptrToString(
			&forceField.velocityInfluence());
	}
	catch(const std::exception& e) {
		pixelpart_gm::lastError = std::string(e.what());
		pixelpart_gm::forceFieldPropertyPtrString = "";
	}

	return pixelpart_gm::forceFieldPropertyPtrString.c_str();
}

GM_EXPORT pixelpart_gm::const_string GM_API pixelpart_drag_field_get_size_influence(pixelpart_gm::string runtimePtr, pixelpart_gm::real forceFieldId) {
	pixelpart_gm::EffectRuntime* effectRuntime = pixelpart_gm::parsePtr<pixelpart_gm::EffectRuntime>(runtimePtr);
	if(!effectRuntime) {
		pixelpart_gm::lastError = pixelpart_gm::invalidEffectRuntimeError;
		pixelpart_gm::forceFieldPropertyPtrString = "";

		return pixelpart_gm::forceFieldPropertyPtrString.c_str();
	}

	try {
		pixelpart::DragField& forceField =
			effectRuntime->effectAsset.effect().sceneGraph().at<pixelpart::DragField>(pixelpart::id_t(forceFieldId));

		pixelpart_gm::forceFieldPropertyPtrString = pixelpart_gm::ptrToString(
			&forceField.sizeInfluence());
	}
	catch(const std::exception& e) {
		pixelpart_gm::lastError = std::string(e.what());
		pixelpart_gm::forceFieldPropertyPtrString = "";
	}

	return pixelpart_gm::forceFieldPropertyPtrString.c_str();
}
}
