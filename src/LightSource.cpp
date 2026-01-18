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

namespace pixelpart_gm {
std::string lightSourcePropertyPtrString = "";
}

extern "C" {
GM_EXPORT pixelpart_gm::const_string GM_API pixelpart_light_source_get_attenuation(pixelpart_gm::string runtimePtr, pixelpart_gm::real lightSourceId) {
	pixelpart_gm::EffectRuntime* effectRuntime = pixelpart_gm::parsePtr<pixelpart_gm::EffectRuntime>(runtimePtr);
	if(!effectRuntime) {
		pixelpart_gm::lastError = pixelpart_gm::invalidEffectRuntimeError;
		pixelpart_gm::lightSourcePropertyPtrString = "";

		return pixelpart_gm::lightSourcePropertyPtrString.c_str();
	}

	try {
		pixelpart::LightSource& lightSource =
			effectRuntime->effectAsset.effect().sceneGraph().at<pixelpart::LightSource>(pixelpart::id_t(lightSourceId));

		pixelpart_gm::lightSourcePropertyPtrString = pixelpart_gm::ptrToString(&lightSource.attenuation());
	}
	catch(const std::exception& e) {
		pixelpart_gm::lastError = std::string(e.what());
		pixelpart_gm::lightSourcePropertyPtrString = "";
	}

	return pixelpart_gm::lightSourcePropertyPtrString.c_str();
}

GM_EXPORT pixelpart_gm::const_string GM_API pixelpart_light_source_get_color(pixelpart_gm::string runtimePtr, pixelpart_gm::real lightSourceId) {
	pixelpart_gm::EffectRuntime* effectRuntime = pixelpart_gm::parsePtr<pixelpart_gm::EffectRuntime>(runtimePtr);
	if(!effectRuntime) {
		pixelpart_gm::lastError = pixelpart_gm::invalidEffectRuntimeError;
		pixelpart_gm::lightSourcePropertyPtrString = "";

		return pixelpart_gm::lightSourcePropertyPtrString.c_str();
	}

	try {
		pixelpart::LightSource& lightSource =
			effectRuntime->effectAsset.effect().sceneGraph().at<pixelpart::LightSource>(pixelpart::id_t(lightSourceId));

		pixelpart_gm::lightSourcePropertyPtrString = pixelpart_gm::ptrToString(&lightSource.color());
	}
	catch(const std::exception& e) {
		pixelpart_gm::lastError = std::string(e.what());
		pixelpart_gm::lightSourcePropertyPtrString = "";
	}

	return pixelpart_gm::lightSourcePropertyPtrString.c_str();
}

GM_EXPORT pixelpart_gm::const_string GM_API pixelpart_light_source_get_intensity(pixelpart_gm::string runtimePtr, pixelpart_gm::real lightSourceId) {
	pixelpart_gm::EffectRuntime* effectRuntime = pixelpart_gm::parsePtr<pixelpart_gm::EffectRuntime>(runtimePtr);
	if(!effectRuntime) {
		pixelpart_gm::lastError = pixelpart_gm::invalidEffectRuntimeError;
		pixelpart_gm::lightSourcePropertyPtrString = "";

		return pixelpart_gm::lightSourcePropertyPtrString.c_str();
	}

	try {
		pixelpart::LightSource& lightSource =
			effectRuntime->effectAsset.effect().sceneGraph().at<pixelpart::LightSource>(pixelpart::id_t(lightSourceId));

		pixelpart_gm::lightSourcePropertyPtrString = pixelpart_gm::ptrToString(&lightSource.intensity());
	}
	catch(const std::exception& e) {
		pixelpart_gm::lastError = std::string(e.what());
		pixelpart_gm::lightSourcePropertyPtrString = "";
	}

	return pixelpart_gm::lightSourcePropertyPtrString.c_str();
}

GM_EXPORT pixelpart_gm::const_string GM_API pixelpart_spot_light_source_get_spot_angle(pixelpart_gm::string runtimePtr, pixelpart_gm::real lightSourceId) {
	pixelpart_gm::EffectRuntime* effectRuntime = pixelpart_gm::parsePtr<pixelpart_gm::EffectRuntime>(runtimePtr);
	if(!effectRuntime) {
		pixelpart_gm::lastError = pixelpart_gm::invalidEffectRuntimeError;
		pixelpart_gm::lightSourcePropertyPtrString = "";

		return pixelpart_gm::lightSourcePropertyPtrString.c_str();
	}

	try {
		pixelpart::SpotLightSource& lightSource =
			effectRuntime->effectAsset.effect().sceneGraph().at<pixelpart::SpotLightSource>(pixelpart::id_t(lightSourceId));

		pixelpart_gm::lightSourcePropertyPtrString = pixelpart_gm::ptrToString(&lightSource.spotAngle());
	}
	catch(const std::exception& e) {
		pixelpart_gm::lastError = std::string(e.what());
		pixelpart_gm::lightSourcePropertyPtrString = "";
	}

	return pixelpart_gm::lightSourcePropertyPtrString.c_str();
}

GM_EXPORT pixelpart_gm::const_string GM_API pixelpart_spot_light_source_get_spot_angle_attenuation(pixelpart_gm::string runtimePtr, pixelpart_gm::real lightSourceId) {
	pixelpart_gm::EffectRuntime* effectRuntime = pixelpart_gm::parsePtr<pixelpart_gm::EffectRuntime>(runtimePtr);
	if(!effectRuntime) {
		pixelpart_gm::lastError = pixelpart_gm::invalidEffectRuntimeError;
		pixelpart_gm::lightSourcePropertyPtrString = "";

		return pixelpart_gm::lightSourcePropertyPtrString.c_str();
	}

	try {
		pixelpart::SpotLightSource& lightSource =
			effectRuntime->effectAsset.effect().sceneGraph().at<pixelpart::SpotLightSource>(pixelpart::id_t(lightSourceId));

		pixelpart_gm::lightSourcePropertyPtrString = pixelpart_gm::ptrToString(&lightSource.spotAngleAttenuation());
	}
	catch(const std::exception& e) {
		pixelpart_gm::lastError = std::string(e.what());
		pixelpart_gm::lightSourcePropertyPtrString = "";
	}

	return pixelpart_gm::lightSourcePropertyPtrString.c_str();
}
}
