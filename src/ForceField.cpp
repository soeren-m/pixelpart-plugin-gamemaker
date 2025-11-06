#include "Common.h"
#include "Error.h"
#include "Buffer.h"
#include "EffectRuntime.h"
#include "pixelpart-runtime/common/Id.h"
#include "pixelpart-runtime/common/Math.h"
#include "pixelpart-runtime/effect/StaticProperty.h"
#include "pixelpart-runtime/effect/AnimatedProperty.h"
#include "pixelpart-runtime/effect/ForceField.h"
#include "pixelpart-runtime/effect/AccelerationField.h"
#include "pixelpart-runtime/effect/VectorField.h"
#include "pixelpart-runtime/effect/NoiseField.h"
#include "pixelpart-runtime/effect/DragField.h"
#include <cstdint>
#include <string>
#include <exception>
#include <algorithm>

namespace pixelpart_gms2 {
std::string forceFieldPropertyPtrString = "";
}

extern "C" {
GMS2_EXPORT pixelpart_gms2::real GMS2_API pixelpart_force_field_set_infinite(pixelpart_gms2::string runtimePtr, pixelpart_gms2::real forceFieldId, pixelpart_gms2::real mode) {
	pixelpart_gms2::EffectRuntime* effectRuntime = reinterpret_cast<pixelpart_gms2::EffectRuntime*>(runtimePtr);
	if(!effectRuntime) {
		pixelpart_gms2::lastError = pixelpart_gms2::invalidEffectRuntimeError;
		return -1;
	}

	try {
		pixelpart::ForceField& forceField =
			effectRuntime->effectAsset.effect().sceneGraph().at<pixelpart::ForceField>(pixelpart::id_t(forceFieldId));

		forceField.infinite(mode);

		return 1;
	}
	catch(const std::exception& e) {
		pixelpart_gms2::lastError = std::string(e.what());
	}

	return -1;
}

GMS2_EXPORT pixelpart_gms2::real GMS2_API pixelpart_force_field_is_infinite(pixelpart_gms2::string runtimePtr, pixelpart_gms2::real forceFieldId) {
	pixelpart_gms2::EffectRuntime* effectRuntime = reinterpret_cast<pixelpart_gms2::EffectRuntime*>(runtimePtr);
	if(!effectRuntime) {
		pixelpart_gms2::lastError = pixelpart_gms2::invalidEffectRuntimeError;
		return -1;
	}

	try {
		const pixelpart::ForceField& forceField =
			effectRuntime->effectAsset.effect().sceneGraph().at<pixelpart::ForceField>(pixelpart::id_t(forceFieldId));

		return forceField.infinite() ? 1 : 0;
	}
	catch(const std::exception& e) {
		pixelpart_gms2::lastError = std::string(e.what());
	}

	return -1;
}

GMS2_EXPORT pixelpart_gms2::const_string GMS2_API pixelpart_force_field_get_strength(pixelpart_gms2::string runtimePtr, pixelpart_gms2::real forceFieldId) {
	pixelpart_gms2::EffectRuntime* effectRuntime = reinterpret_cast<pixelpart_gms2::EffectRuntime*>(runtimePtr);
	if(!effectRuntime) {
		pixelpart_gms2::lastError = pixelpart_gms2::invalidEffectRuntimeError;
		pixelpart_gms2::forceFieldPropertyPtrString = pixelpart_gms2::nullPointerString;

		return pixelpart_gms2::forceFieldPropertyPtrString.c_str();
	}

	try {
		pixelpart::ForceField& forceField =
			effectRuntime->effectAsset.effect().sceneGraph().at<pixelpart::ForceField>(pixelpart::id_t(forceFieldId));

		pixelpart_gms2::forceFieldPropertyPtrString = pixelpart_gms2::toBufferString(
			&forceField.strength());
	}
	catch(const std::exception& e) {
		pixelpart_gms2::lastError = std::string(e.what());
		pixelpart_gms2::forceFieldPropertyPtrString = pixelpart_gms2::nullPointerString;
	}

	return pixelpart_gms2::forceFieldPropertyPtrString.c_str();
}

GMS2_EXPORT pixelpart_gms2::const_string GMS2_API pixelpart_acceleration_field_get_acceleration_direction(pixelpart_gms2::string runtimePtr, pixelpart_gms2::real forceFieldId) {
	pixelpart_gms2::EffectRuntime* effectRuntime = reinterpret_cast<pixelpart_gms2::EffectRuntime*>(runtimePtr);
	if(!effectRuntime) {
		pixelpart_gms2::lastError = pixelpart_gms2::invalidEffectRuntimeError;
		pixelpart_gms2::forceFieldPropertyPtrString = pixelpart_gms2::nullPointerString;

		return pixelpart_gms2::forceFieldPropertyPtrString.c_str();
	}

	try {
		pixelpart::AccelerationField& forceField =
			effectRuntime->effectAsset.effect().sceneGraph().at<pixelpart::AccelerationField>(pixelpart::id_t(forceFieldId));

		pixelpart_gms2::forceFieldPropertyPtrString = pixelpart_gms2::toBufferString(
			&forceField.accelerationDirection());
	}
	catch(const std::exception& e) {
		pixelpart_gms2::lastError = std::string(e.what());
		pixelpart_gms2::forceFieldPropertyPtrString = pixelpart_gms2::nullPointerString;
	}

	return pixelpart_gms2::forceFieldPropertyPtrString.c_str();
}

GMS2_EXPORT pixelpart_gms2::const_string GMS2_API pixelpart_acceleration_field_get_acceleration_direction_variance(pixelpart_gms2::string runtimePtr, pixelpart_gms2::real forceFieldId) {
	pixelpart_gms2::EffectRuntime* effectRuntime = reinterpret_cast<pixelpart_gms2::EffectRuntime*>(runtimePtr);
	if(!effectRuntime) {
		pixelpart_gms2::lastError = pixelpart_gms2::invalidEffectRuntimeError;
		pixelpart_gms2::forceFieldPropertyPtrString = pixelpart_gms2::nullPointerString;

		return pixelpart_gms2::forceFieldPropertyPtrString.c_str();
	}

	try {
		pixelpart::AccelerationField& forceField =
			effectRuntime->effectAsset.effect().sceneGraph().at<pixelpart::AccelerationField>(pixelpart::id_t(forceFieldId));

		pixelpart_gms2::forceFieldPropertyPtrString = pixelpart_gms2::toBufferString(
			&forceField.accelerationDirectionVariance());
	}
	catch(const std::exception& e) {
		pixelpart_gms2::lastError = std::string(e.what());
		pixelpart_gms2::forceFieldPropertyPtrString = pixelpart_gms2::nullPointerString;
	}

	return pixelpart_gms2::forceFieldPropertyPtrString.c_str();
}

GMS2_EXPORT pixelpart_gms2::const_string GMS2_API pixelpart_acceleration_field_get_acceleration_strength_variance(pixelpart_gms2::string runtimePtr, pixelpart_gms2::real forceFieldId) {
	pixelpart_gms2::EffectRuntime* effectRuntime = reinterpret_cast<pixelpart_gms2::EffectRuntime*>(runtimePtr);
	if(!effectRuntime) {
		pixelpart_gms2::lastError = pixelpart_gms2::invalidEffectRuntimeError;
		pixelpart_gms2::forceFieldPropertyPtrString = pixelpart_gms2::nullPointerString;

		return pixelpart_gms2::forceFieldPropertyPtrString.c_str();
	}

	try {
		pixelpart::AccelerationField& forceField =
			effectRuntime->effectAsset.effect().sceneGraph().at<pixelpart::AccelerationField>(pixelpart::id_t(forceFieldId));

		pixelpart_gms2::forceFieldPropertyPtrString = pixelpart_gms2::toBufferString(
			&forceField.accelerationStrengthVariance());
	}
	catch(const std::exception& e) {
		pixelpart_gms2::lastError = std::string(e.what());
		pixelpart_gms2::forceFieldPropertyPtrString = pixelpart_gms2::nullPointerString;
	}

	return pixelpart_gms2::forceFieldPropertyPtrString.c_str();
}

GMS2_EXPORT pixelpart_gms2::real GMS2_API pixelpart_acceleration_field_set_acceleration_grid_size(pixelpart_gms2::string runtimePtr, pixelpart_gms2::real forceFieldId, pixelpart_gms2::string valueBufferPtr) {
	pixelpart_gms2::EffectRuntime* effectRuntime = reinterpret_cast<pixelpart_gms2::EffectRuntime*>(runtimePtr);
	if(!effectRuntime) {
		pixelpart_gms2::lastError = pixelpart_gms2::invalidEffectRuntimeError;
		return -1;
	}
	else if(!valueBufferPtr) {
		pixelpart_gms2::lastError = pixelpart_gms2::invalidArgumentError;
		return -1;
	}

	try {
		pixelpart::AccelerationField& forceField =
			effectRuntime->effectAsset.effect().sceneGraph().at<pixelpart::AccelerationField>(pixelpart::id_t(forceFieldId));

		pixelpart_gms2::Buffer valueBuffer(valueBufferPtr);
		std::int32_t x = static_cast<std::int32_t>(std::max(valueBuffer.read<pixelpart::float_t>(), 1.0));
		std::int32_t y = static_cast<std::int32_t>(std::max(valueBuffer.read<pixelpart::float_t>(), 1.0));
		std::int32_t z = static_cast<std::int32_t>(std::max(valueBuffer.read<pixelpart::float_t>(), 1.0));

		forceField.accelerationGrid(x, y, z);
		forceField.randomizeAccelerationGrid(pixelpart_gms2::rng);

		return 1;
	}
	catch(const std::exception& e) {
		pixelpart_gms2::lastError = std::string(e.what());
	}

	return -1;
}

GMS2_EXPORT pixelpart_gms2::real GMS2_API pixelpart_acceleration_field_get_acceleration_grid_size_x(pixelpart_gms2::string runtimePtr, pixelpart_gms2::real forceFieldId) {
	pixelpart_gms2::EffectRuntime* effectRuntime = reinterpret_cast<pixelpart_gms2::EffectRuntime*>(runtimePtr);
	if(!effectRuntime) {
		pixelpart_gms2::lastError = pixelpart_gms2::invalidEffectRuntimeError;
		return -1;
	}

	try {
		const pixelpart::AccelerationField& forceField =
			effectRuntime->effectAsset.effect().sceneGraph().at<pixelpart::AccelerationField>(pixelpart::id_t(forceFieldId));

		return forceField.accelerationGridSizeX();
	}
	catch(const std::exception& e) {
		pixelpart_gms2::lastError = std::string(e.what());
	}

	return -1;
}

GMS2_EXPORT pixelpart_gms2::real GMS2_API pixelpart_acceleration_field_get_acceleration_grid_size_y(pixelpart_gms2::string runtimePtr, pixelpart_gms2::real forceFieldId) {
	pixelpart_gms2::EffectRuntime* effectRuntime = reinterpret_cast<pixelpart_gms2::EffectRuntime*>(runtimePtr);
	if(!effectRuntime) {
		pixelpart_gms2::lastError = pixelpart_gms2::invalidEffectRuntimeError;
		return -1;
	}

	try {
		const pixelpart::AccelerationField& forceField =
			effectRuntime->effectAsset.effect().sceneGraph().at<pixelpart::AccelerationField>(pixelpart::id_t(forceFieldId));

		return forceField.accelerationGridSizeY();
	}
	catch(const std::exception& e) {
		pixelpart_gms2::lastError = std::string(e.what());
	}

	return -1;
}

GMS2_EXPORT pixelpart_gms2::real GMS2_API pixelpart_acceleration_field_get_acceleration_grid_size_z(pixelpart_gms2::string runtimePtr, pixelpart_gms2::real forceFieldId) {
	pixelpart_gms2::EffectRuntime* effectRuntime = reinterpret_cast<pixelpart_gms2::EffectRuntime*>(runtimePtr);
	if(!effectRuntime) {
		pixelpart_gms2::lastError = pixelpart_gms2::invalidEffectRuntimeError;
		return -1;
	}

	try {
		const pixelpart::AccelerationField& forceField =
			effectRuntime->effectAsset.effect().sceneGraph().at<pixelpart::AccelerationField>(pixelpart::id_t(forceFieldId));

		return forceField.accelerationGridSizeZ();
	}
	catch(const std::exception& e) {
		pixelpart_gms2::lastError = std::string(e.what());
	}

	return -1;
}

GMS2_EXPORT pixelpart_gms2::real GMS2_API pixelpart_vector_field_set_vector_field_filter(pixelpart_gms2::string runtimePtr, pixelpart_gms2::real forceFieldId, pixelpart_gms2::real filter) {
	pixelpart_gms2::EffectRuntime* effectRuntime = reinterpret_cast<pixelpart_gms2::EffectRuntime*>(runtimePtr);
	if(!effectRuntime) {
		pixelpart_gms2::lastError = pixelpart_gms2::invalidEffectRuntimeError;
		return -1;
	}

	try {
		pixelpart::VectorField& forceField =
			effectRuntime->effectAsset.effect().sceneGraph().at<pixelpart::VectorField>(pixelpart::id_t(forceFieldId));

		forceField.vectorFieldFilter(static_cast<pixelpart::VectorField::Filter>(filter));

		return 1;
	}
	catch(const std::exception& e) {
		pixelpart_gms2::lastError = std::string(e.what());
	}

	return -1;
}

GMS2_EXPORT pixelpart_gms2::real GMS2_API pixelpart_vector_field_get_vector_field_filter(pixelpart_gms2::string runtimePtr, pixelpart_gms2::real forceFieldId) {
	pixelpart_gms2::EffectRuntime* effectRuntime = reinterpret_cast<pixelpart_gms2::EffectRuntime*>(runtimePtr);
	if(!effectRuntime) {
		pixelpart_gms2::lastError = pixelpart_gms2::invalidEffectRuntimeError;
		return -1;
	}

	try {
		const pixelpart::VectorField& forceField =
			effectRuntime->effectAsset.effect().sceneGraph().at<pixelpart::VectorField>(pixelpart::id_t(forceFieldId));

		return static_cast<pixelpart_gms2::real>(forceField.vectorFieldFilter());
	}
	catch(const std::exception& e) {
		pixelpart_gms2::lastError = std::string(e.what());
	}

	return -1;
}

GMS2_EXPORT pixelpart_gms2::const_string GMS2_API pixelpart_vector_field_get_tightness(pixelpart_gms2::string runtimePtr, pixelpart_gms2::real forceFieldId) {
	pixelpart_gms2::EffectRuntime* effectRuntime = reinterpret_cast<pixelpart_gms2::EffectRuntime*>(runtimePtr);
	if(!effectRuntime) {
		pixelpart_gms2::lastError = pixelpart_gms2::invalidEffectRuntimeError;
		pixelpart_gms2::forceFieldPropertyPtrString = pixelpart_gms2::nullPointerString;

		return pixelpart_gms2::forceFieldPropertyPtrString.c_str();
	}

	try {
		pixelpart::VectorField& forceField =
			effectRuntime->effectAsset.effect().sceneGraph().at<pixelpart::VectorField>(pixelpart::id_t(forceFieldId));

		pixelpart_gms2::forceFieldPropertyPtrString = pixelpart_gms2::toBufferString(
			&forceField.tightness());
	}
	catch(const std::exception& e) {
		pixelpart_gms2::lastError = std::string(e.what());
		pixelpart_gms2::forceFieldPropertyPtrString = pixelpart_gms2::nullPointerString;
	}

	return pixelpart_gms2::forceFieldPropertyPtrString.c_str();
}

GMS2_EXPORT pixelpart_gms2::const_string GMS2_API pixelpart_noise_field_get_noise_octaves(pixelpart_gms2::string runtimePtr, pixelpart_gms2::real forceFieldId) {
	pixelpart_gms2::EffectRuntime* effectRuntime = reinterpret_cast<pixelpart_gms2::EffectRuntime*>(runtimePtr);
	if(!effectRuntime) {
		pixelpart_gms2::lastError = pixelpart_gms2::invalidEffectRuntimeError;
		pixelpart_gms2::forceFieldPropertyPtrString = pixelpart_gms2::nullPointerString;

		return pixelpart_gms2::forceFieldPropertyPtrString.c_str();
	}

	try {
		pixelpart::NoiseField& forceField =
			effectRuntime->effectAsset.effect().sceneGraph().at<pixelpart::NoiseField>(pixelpart::id_t(forceFieldId));

		pixelpart_gms2::forceFieldPropertyPtrString = pixelpart_gms2::toBufferString(
			&forceField.noiseOctaves());
	}
	catch(const std::exception& e) {
		pixelpart_gms2::lastError = std::string(e.what());
		pixelpart_gms2::forceFieldPropertyPtrString = pixelpart_gms2::nullPointerString;
	}

	return pixelpart_gms2::forceFieldPropertyPtrString.c_str();
}

GMS2_EXPORT pixelpart_gms2::const_string GMS2_API pixelpart_noise_field_get_noise_frequency(pixelpart_gms2::string runtimePtr, pixelpart_gms2::real forceFieldId) {
	pixelpart_gms2::EffectRuntime* effectRuntime = reinterpret_cast<pixelpart_gms2::EffectRuntime*>(runtimePtr);
	if(!effectRuntime) {
		pixelpart_gms2::lastError = pixelpart_gms2::invalidEffectRuntimeError;
		pixelpart_gms2::forceFieldPropertyPtrString = pixelpart_gms2::nullPointerString;

		return pixelpart_gms2::forceFieldPropertyPtrString.c_str();
	}

	try {
		pixelpart::NoiseField& forceField =
			effectRuntime->effectAsset.effect().sceneGraph().at<pixelpart::NoiseField>(pixelpart::id_t(forceFieldId));

		pixelpart_gms2::forceFieldPropertyPtrString = pixelpart_gms2::toBufferString(
			&forceField.noiseFrequency());
	}
	catch(const std::exception& e) {
		pixelpart_gms2::lastError = std::string(e.what());
		pixelpart_gms2::forceFieldPropertyPtrString = pixelpart_gms2::nullPointerString;
	}

	return pixelpart_gms2::forceFieldPropertyPtrString.c_str();
}

GMS2_EXPORT pixelpart_gms2::const_string GMS2_API pixelpart_noise_field_get_noise_persistence(pixelpart_gms2::string runtimePtr, pixelpart_gms2::real forceFieldId) {
	pixelpart_gms2::EffectRuntime* effectRuntime = reinterpret_cast<pixelpart_gms2::EffectRuntime*>(runtimePtr);
	if(!effectRuntime) {
		pixelpart_gms2::lastError = pixelpart_gms2::invalidEffectRuntimeError;
		pixelpart_gms2::forceFieldPropertyPtrString = pixelpart_gms2::nullPointerString;

		return pixelpart_gms2::forceFieldPropertyPtrString.c_str();
	}

	try {
		pixelpart::NoiseField& forceField =
			effectRuntime->effectAsset.effect().sceneGraph().at<pixelpart::NoiseField>(pixelpart::id_t(forceFieldId));

		pixelpart_gms2::forceFieldPropertyPtrString = pixelpart_gms2::toBufferString(
			&forceField.noisePersistence());
	}
	catch(const std::exception& e) {
		pixelpart_gms2::lastError = std::string(e.what());
		pixelpart_gms2::forceFieldPropertyPtrString = pixelpart_gms2::nullPointerString;
	}

	return pixelpart_gms2::forceFieldPropertyPtrString.c_str();
}

GMS2_EXPORT pixelpart_gms2::const_string GMS2_API pixelpart_noise_field_get_noise_lacunarity(pixelpart_gms2::string runtimePtr, pixelpart_gms2::real forceFieldId) {
	pixelpart_gms2::EffectRuntime* effectRuntime = reinterpret_cast<pixelpart_gms2::EffectRuntime*>(runtimePtr);
	if(!effectRuntime) {
		pixelpart_gms2::lastError = pixelpart_gms2::invalidEffectRuntimeError;
		pixelpart_gms2::forceFieldPropertyPtrString = pixelpart_gms2::nullPointerString;

		return pixelpart_gms2::forceFieldPropertyPtrString.c_str();
	}

	try {
		pixelpart::NoiseField& forceField =
			effectRuntime->effectAsset.effect().sceneGraph().at<pixelpart::NoiseField>(pixelpart::id_t(forceFieldId));

		pixelpart_gms2::forceFieldPropertyPtrString = pixelpart_gms2::toBufferString(
			&forceField.noiseLacunarity());
	}
	catch(const std::exception& e) {
		pixelpart_gms2::lastError = std::string(e.what());
		pixelpart_gms2::forceFieldPropertyPtrString = pixelpart_gms2::nullPointerString;
	}

	return pixelpart_gms2::forceFieldPropertyPtrString.c_str();
}

GMS2_EXPORT pixelpart_gms2::real GMS2_API pixelpart_noise_field_set_noise_animated(pixelpart_gms2::string runtimePtr, pixelpart_gms2::real forceFieldId, pixelpart_gms2::real animated) {
	pixelpart_gms2::EffectRuntime* effectRuntime = reinterpret_cast<pixelpart_gms2::EffectRuntime*>(runtimePtr);
	if(!effectRuntime) {
		pixelpart_gms2::lastError = pixelpart_gms2::invalidEffectRuntimeError;
		return -1;
	}

	try {
		pixelpart::NoiseField& forceField =
			effectRuntime->effectAsset.effect().sceneGraph().at<pixelpart::NoiseField>(pixelpart::id_t(forceFieldId));

		forceField.noiseAnimated(animated);

		return 1;
	}
	catch(const std::exception& e) {
		pixelpart_gms2::lastError = std::string(e.what());
	}

	return -1;
}

GMS2_EXPORT pixelpart_gms2::real GMS2_API pixelpart_noise_field_is_noise_animated(pixelpart_gms2::string runtimePtr, pixelpart_gms2::real forceFieldId) {
	pixelpart_gms2::EffectRuntime* effectRuntime = reinterpret_cast<pixelpart_gms2::EffectRuntime*>(runtimePtr);
	if(!effectRuntime) {
		pixelpart_gms2::lastError = pixelpart_gms2::invalidEffectRuntimeError;
		return -1;
	}

	try {
		const pixelpart::NoiseField& forceField =
			effectRuntime->effectAsset.effect().sceneGraph().at<pixelpart::NoiseField>(pixelpart::id_t(forceFieldId));

		return forceField.noiseAnimated() ? 1 : 0;
	}
	catch(const std::exception& e) {
		pixelpart_gms2::lastError = std::string(e.what());
	}

	return -1;
}

GMS2_EXPORT pixelpart_gms2::const_string GMS2_API pixelpart_noise_field_get_noise_animation_time_scale(pixelpart_gms2::string runtimePtr, pixelpart_gms2::real forceFieldId) {
	pixelpart_gms2::EffectRuntime* effectRuntime = reinterpret_cast<pixelpart_gms2::EffectRuntime*>(runtimePtr);
	if(!effectRuntime) {
		pixelpart_gms2::lastError = pixelpart_gms2::invalidEffectRuntimeError;
		pixelpart_gms2::forceFieldPropertyPtrString = pixelpart_gms2::nullPointerString;

		return pixelpart_gms2::forceFieldPropertyPtrString.c_str();
	}

	try {
		pixelpart::NoiseField& forceField =
			effectRuntime->effectAsset.effect().sceneGraph().at<pixelpart::NoiseField>(pixelpart::id_t(forceFieldId));

		pixelpart_gms2::forceFieldPropertyPtrString = pixelpart_gms2::toBufferString(
			&forceField.noiseAnimationTimeScale());
	}
	catch(const std::exception& e) {
		pixelpart_gms2::lastError = std::string(e.what());
		pixelpart_gms2::forceFieldPropertyPtrString = pixelpart_gms2::nullPointerString;
	}

	return pixelpart_gms2::forceFieldPropertyPtrString.c_str();
}

GMS2_EXPORT pixelpart_gms2::const_string GMS2_API pixelpart_noise_field_get_noise_animation_time_base(pixelpart_gms2::string runtimePtr, pixelpart_gms2::real forceFieldId) {
	pixelpart_gms2::EffectRuntime* effectRuntime = reinterpret_cast<pixelpart_gms2::EffectRuntime*>(runtimePtr);
	if(!effectRuntime) {
		pixelpart_gms2::lastError = pixelpart_gms2::invalidEffectRuntimeError;
		pixelpart_gms2::forceFieldPropertyPtrString = pixelpart_gms2::nullPointerString;

		return pixelpart_gms2::forceFieldPropertyPtrString.c_str();
	}

	try {
		pixelpart::NoiseField& forceField =
			effectRuntime->effectAsset.effect().sceneGraph().at<pixelpart::NoiseField>(pixelpart::id_t(forceFieldId));

		pixelpart_gms2::forceFieldPropertyPtrString = pixelpart_gms2::toBufferString(
			&forceField.noiseAnimationTimeBase());
	}
	catch(const std::exception& e) {
		pixelpart_gms2::lastError = std::string(e.what());
		pixelpart_gms2::forceFieldPropertyPtrString = pixelpart_gms2::nullPointerString;
	}

	return pixelpart_gms2::forceFieldPropertyPtrString.c_str();
}

GMS2_EXPORT pixelpart_gms2::const_string GMS2_API pixelpart_drag_field_get_velocity_influence(pixelpart_gms2::string runtimePtr, pixelpart_gms2::real forceFieldId) {
	pixelpart_gms2::EffectRuntime* effectRuntime = reinterpret_cast<pixelpart_gms2::EffectRuntime*>(runtimePtr);
	if(!effectRuntime) {
		pixelpart_gms2::lastError = pixelpart_gms2::invalidEffectRuntimeError;
		pixelpart_gms2::forceFieldPropertyPtrString = pixelpart_gms2::nullPointerString;

		return pixelpart_gms2::forceFieldPropertyPtrString.c_str();
	}

	try {
		pixelpart::DragField& forceField =
			effectRuntime->effectAsset.effect().sceneGraph().at<pixelpart::DragField>(pixelpart::id_t(forceFieldId));

		pixelpart_gms2::forceFieldPropertyPtrString = pixelpart_gms2::toBufferString(
			&forceField.velocityInfluence());
	}
	catch(const std::exception& e) {
		pixelpart_gms2::lastError = std::string(e.what());
		pixelpart_gms2::forceFieldPropertyPtrString = pixelpart_gms2::nullPointerString;
	}

	return pixelpart_gms2::forceFieldPropertyPtrString.c_str();
}

GMS2_EXPORT pixelpart_gms2::const_string GMS2_API pixelpart_drag_field_get_size_influence(pixelpart_gms2::string runtimePtr, pixelpart_gms2::real forceFieldId) {
	pixelpart_gms2::EffectRuntime* effectRuntime = reinterpret_cast<pixelpart_gms2::EffectRuntime*>(runtimePtr);
	if(!effectRuntime) {
		pixelpart_gms2::lastError = pixelpart_gms2::invalidEffectRuntimeError;
		pixelpart_gms2::forceFieldPropertyPtrString = pixelpart_gms2::nullPointerString;

		return pixelpart_gms2::forceFieldPropertyPtrString.c_str();
	}

	try {
		pixelpart::DragField& forceField =
			effectRuntime->effectAsset.effect().sceneGraph().at<pixelpart::DragField>(pixelpart::id_t(forceFieldId));

		pixelpart_gms2::forceFieldPropertyPtrString = pixelpart_gms2::toBufferString(
			&forceField.sizeInfluence());
	}
	catch(const std::exception& e) {
		pixelpart_gms2::lastError = std::string(e.what());
		pixelpart_gms2::forceFieldPropertyPtrString = pixelpart_gms2::nullPointerString;
	}

	return pixelpart_gms2::forceFieldPropertyPtrString.c_str();
}
}