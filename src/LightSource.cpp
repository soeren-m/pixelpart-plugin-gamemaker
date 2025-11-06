#include "Common.h"
#include "Error.h"
#include "Buffer.h"
#include "EffectRuntime.h"
#include "pixelpart-runtime/common/Id.h"
#include "pixelpart-runtime/common/Math.h"
#include "pixelpart-runtime/effect/AnimatedProperty.h"
#include "pixelpart-runtime/effect/LightSource.h"
#include "pixelpart-runtime/effect/SpotLightSource.h"
#include <string>
#include <exception>

namespace pixelpart_gms2 {
std::string lightSourcePropertyPtrString = "";
}

extern "C" {
GMS2_EXPORT pixelpart_gms2::const_string GMS2_API pixelpart_light_source_get_attenuation(pixelpart_gms2::string runtimePtr, pixelpart_gms2::real lightSourceId) {
	pixelpart_gms2::EffectRuntime* effectRuntime = reinterpret_cast<pixelpart_gms2::EffectRuntime*>(runtimePtr);
	if(!effectRuntime) {
		pixelpart_gms2::lastError = pixelpart_gms2::invalidEffectRuntimeError;
		pixelpart_gms2::lightSourcePropertyPtrString = pixelpart_gms2::nullPointerString;

		return pixelpart_gms2::lightSourcePropertyPtrString.c_str();
	}

	try {
		pixelpart::LightSource& lightSource =
			effectRuntime->effectAsset.effect().sceneGraph().at<pixelpart::LightSource>(pixelpart::id_t(lightSourceId));

		pixelpart_gms2::lightSourcePropertyPtrString = pixelpart_gms2::toBufferString(&lightSource.attenuation());
	}
	catch(const std::exception& e) {
		pixelpart_gms2::lastError = std::string(e.what());
		pixelpart_gms2::lightSourcePropertyPtrString = pixelpart_gms2::nullPointerString;
	}

	return pixelpart_gms2::lightSourcePropertyPtrString.c_str();
}

GMS2_EXPORT pixelpart_gms2::const_string GMS2_API pixelpart_light_source_get_color(pixelpart_gms2::string runtimePtr, pixelpart_gms2::real lightSourceId) {
	pixelpart_gms2::EffectRuntime* effectRuntime = reinterpret_cast<pixelpart_gms2::EffectRuntime*>(runtimePtr);
	if(!effectRuntime) {
		pixelpart_gms2::lastError = pixelpart_gms2::invalidEffectRuntimeError;
		pixelpart_gms2::lightSourcePropertyPtrString = pixelpart_gms2::nullPointerString;

		return pixelpart_gms2::lightSourcePropertyPtrString.c_str();
	}

	try {
		pixelpart::LightSource& lightSource =
			effectRuntime->effectAsset.effect().sceneGraph().at<pixelpart::LightSource>(pixelpart::id_t(lightSourceId));

		pixelpart_gms2::lightSourcePropertyPtrString = pixelpart_gms2::toBufferString(&lightSource.color());
	}
	catch(const std::exception& e) {
		pixelpart_gms2::lastError = std::string(e.what());
		pixelpart_gms2::lightSourcePropertyPtrString = pixelpart_gms2::nullPointerString;
	}

	return pixelpart_gms2::lightSourcePropertyPtrString.c_str();
}

GMS2_EXPORT pixelpart_gms2::const_string GMS2_API pixelpart_light_source_get_intensity(pixelpart_gms2::string runtimePtr, pixelpart_gms2::real lightSourceId) {
	pixelpart_gms2::EffectRuntime* effectRuntime = reinterpret_cast<pixelpart_gms2::EffectRuntime*>(runtimePtr);
	if(!effectRuntime) {
		pixelpart_gms2::lastError = pixelpart_gms2::invalidEffectRuntimeError;
		pixelpart_gms2::lightSourcePropertyPtrString = pixelpart_gms2::nullPointerString;

		return pixelpart_gms2::lightSourcePropertyPtrString.c_str();
	}

	try {
		pixelpart::LightSource& lightSource =
			effectRuntime->effectAsset.effect().sceneGraph().at<pixelpart::LightSource>(pixelpart::id_t(lightSourceId));

		pixelpart_gms2::lightSourcePropertyPtrString = pixelpart_gms2::toBufferString(&lightSource.intensity());
	}
	catch(const std::exception& e) {
		pixelpart_gms2::lastError = std::string(e.what());
		pixelpart_gms2::lightSourcePropertyPtrString = pixelpart_gms2::nullPointerString;
	}

	return pixelpart_gms2::lightSourcePropertyPtrString.c_str();
}

GMS2_EXPORT pixelpart_gms2::const_string GMS2_API pixelpart_spot_light_source_get_spot_angle(pixelpart_gms2::string runtimePtr, pixelpart_gms2::real lightSourceId) {
	pixelpart_gms2::EffectRuntime* effectRuntime = reinterpret_cast<pixelpart_gms2::EffectRuntime*>(runtimePtr);
	if(!effectRuntime) {
		pixelpart_gms2::lastError = pixelpart_gms2::invalidEffectRuntimeError;
		pixelpart_gms2::lightSourcePropertyPtrString = pixelpart_gms2::nullPointerString;

		return pixelpart_gms2::lightSourcePropertyPtrString.c_str();
	}

	try {
		pixelpart::SpotLightSource& lightSource =
			effectRuntime->effectAsset.effect().sceneGraph().at<pixelpart::SpotLightSource>(pixelpart::id_t(lightSourceId));

		pixelpart_gms2::lightSourcePropertyPtrString = pixelpart_gms2::toBufferString(&lightSource.spotAngle());
	}
	catch(const std::exception& e) {
		pixelpart_gms2::lastError = std::string(e.what());
		pixelpart_gms2::lightSourcePropertyPtrString = pixelpart_gms2::nullPointerString;
	}

	return pixelpart_gms2::lightSourcePropertyPtrString.c_str();
}

GMS2_EXPORT pixelpart_gms2::const_string GMS2_API pixelpart_spot_light_source_get_spot_angle_attenuation(pixelpart_gms2::string runtimePtr, pixelpart_gms2::real lightSourceId) {
	pixelpart_gms2::EffectRuntime* effectRuntime = reinterpret_cast<pixelpart_gms2::EffectRuntime*>(runtimePtr);
	if(!effectRuntime) {
		pixelpart_gms2::lastError = pixelpart_gms2::invalidEffectRuntimeError;
		pixelpart_gms2::lightSourcePropertyPtrString = pixelpart_gms2::nullPointerString;

		return pixelpart_gms2::lightSourcePropertyPtrString.c_str();
	}

	try {
		pixelpart::SpotLightSource& lightSource =
			effectRuntime->effectAsset.effect().sceneGraph().at<pixelpart::SpotLightSource>(pixelpart::id_t(lightSourceId));

		pixelpart_gms2::lightSourcePropertyPtrString = pixelpart_gms2::toBufferString(&lightSource.spotAngleAttenuation());
	}
	catch(const std::exception& e) {
		pixelpart_gms2::lastError = std::string(e.what());
		pixelpart_gms2::lightSourcePropertyPtrString = pixelpart_gms2::nullPointerString;
	}

	return pixelpart_gms2::lightSourcePropertyPtrString.c_str();
}
}