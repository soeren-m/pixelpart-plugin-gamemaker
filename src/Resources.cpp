#include "Common.h"
#include "Error.h"
#include "EffectRuntime.h"
#include "pixelpart-runtime/effect/ImageResource.h"
#include <cstdint>
#include <cstring>
#include <string>
#include <exception>

extern "C" {
GM_EXPORT pixelpart_gm::real GM_API pixelpart_get_image_resource_count(pixelpart_gm::string runtimePtr) {
	pixelpart_gm::EffectRuntime* effectRuntime = pixelpart_gm::parsePtr<pixelpart_gm::EffectRuntime>(runtimePtr);
	if(!effectRuntime) {
		pixelpart_gm::lastError = pixelpart_gm::invalidEffectRuntimeError;
		return -1;
	}

	return static_cast<pixelpart_gm::real>(effectRuntime->effectAsset.effect().resources().images().size());
}

GM_EXPORT pixelpart_gm::const_string GM_API pixelpart_get_image_resource_id(pixelpart_gm::string runtimePtr, pixelpart_gm::real index) {
	pixelpart_gm::EffectRuntime* effectRuntime = pixelpart_gm::parsePtr<pixelpart_gm::EffectRuntime>(runtimePtr);
	if(!effectRuntime) {
		pixelpart_gm::lastError = pixelpart_gm::invalidEffectRuntimeError;
		return "";
	}

	std::uint32_t currentIndex = 0;
	for(const auto& [resourceName, resource] : effectRuntime->effectAsset.effect().resources().images()) {
		if(currentIndex != static_cast<std::uint32_t>(index)) {
			currentIndex++;
			continue;
		}

		return resourceName.c_str();
	}

	return "";
}

GM_EXPORT pixelpart_gm::real GM_API pixelpart_get_image_resource_width(pixelpart_gm::string runtimePtr, pixelpart_gm::string resourceId) {
	pixelpart_gm::EffectRuntime* effectRuntime = pixelpart_gm::parsePtr<pixelpart_gm::EffectRuntime>(runtimePtr);
	if(!effectRuntime) {
		pixelpart_gm::lastError = pixelpart_gm::invalidEffectRuntimeError;
		return -1;
	}
	else if(!resourceId) {
		pixelpart_gm::lastError = pixelpart_gm::invalidArgumentError;
		return -1;
	}

	try {
		const pixelpart::ImageResource& image =
			effectRuntime->effectAsset.effect().resources().images().at(std::string(resourceId));

		return static_cast<pixelpart_gm::real>(image.width());
	}
	catch(const std::exception& e) {
		pixelpart_gm::lastError = std::string(e.what());
	}

	return -1;
}

GM_EXPORT pixelpart_gm::real GM_API pixelpart_get_image_resource_height(pixelpart_gm::string runtimePtr, pixelpart_gm::string resourceId) {
	pixelpart_gm::EffectRuntime* effectRuntime = pixelpart_gm::parsePtr<pixelpart_gm::EffectRuntime>(runtimePtr);
	if(!effectRuntime) {
		pixelpart_gm::lastError = pixelpart_gm::invalidEffectRuntimeError;
		return -1;
	}
	else if(!resourceId) {
		pixelpart_gm::lastError = pixelpart_gm::invalidArgumentError;
		return -1;
	}

	try {
		const pixelpart::ImageResource& image =
			effectRuntime->effectAsset.effect().resources().images().at(std::string(resourceId));

		return static_cast<pixelpart_gm::real>(image.height());
	}
	catch(const std::exception& e) {
		pixelpart_gm::lastError = std::string(e.what());
	}

	return -1;
}

GM_EXPORT pixelpart_gm::real GM_API pixelpart_get_image_resource_channels(pixelpart_gm::string runtimePtr, pixelpart_gm::string resourceId) {
	pixelpart_gm::EffectRuntime* effectRuntime = pixelpart_gm::parsePtr<pixelpart_gm::EffectRuntime>(runtimePtr);
	if(!effectRuntime) {
		pixelpart_gm::lastError = pixelpart_gm::invalidEffectRuntimeError;
		return -1;
	}
	else if(!resourceId) {
		pixelpart_gm::lastError = pixelpart_gm::invalidArgumentError;
		return -1;
	}

	try {
		const pixelpart::ImageResource& image =
			effectRuntime->effectAsset.effect().resources().images().at(std::string(resourceId));

		return static_cast<pixelpart_gm::real>(image.channels());
	}
	catch(const std::exception& e) {
		pixelpart_gm::lastError = std::string(e.what());
	}

	return -1;
}

GM_EXPORT pixelpart_gm::real GM_API pixelpart_get_image_resource_color_space(pixelpart_gm::string runtimePtr, pixelpart_gm::string resourceId) {
	pixelpart_gm::EffectRuntime* effectRuntime = pixelpart_gm::parsePtr<pixelpart_gm::EffectRuntime>(runtimePtr);
	if(!effectRuntime) {
		pixelpart_gm::lastError = pixelpart_gm::invalidEffectRuntimeError;
		return -1;
	}
	else if(!resourceId) {
		pixelpart_gm::lastError = pixelpart_gm::invalidArgumentError;
		return -1;
	}

	try {
		const pixelpart::ImageResource& image =
			effectRuntime->effectAsset.effect().resources().images().at(std::string(resourceId));

		return static_cast<pixelpart_gm::real>(image.colorSpace());
	}
	catch(const std::exception& e) {
		pixelpart_gm::lastError = std::string(e.what());
	}

	return -1;
}

GM_EXPORT pixelpart_gm::real GM_API pixelpart_get_image_resource_data_size(pixelpart_gm::string runtimePtr, pixelpart_gm::string resourceId) {
	pixelpart_gm::EffectRuntime* effectRuntime = pixelpart_gm::parsePtr<pixelpart_gm::EffectRuntime>(runtimePtr);
	if(!effectRuntime) {
		pixelpart_gm::lastError = pixelpart_gm::invalidEffectRuntimeError;
		return -1;
	}
	else if(!resourceId) {
		pixelpart_gm::lastError = pixelpart_gm::invalidArgumentError;
		return -1;
	}

	try {
		const pixelpart::ImageResource& image =
			effectRuntime->effectAsset.effect().resources().images().at(std::string(resourceId));

		return static_cast<pixelpart_gm::real>(image.data().size());
	}
	catch(const std::exception& e) {
		pixelpart_gm::lastError = std::string(e.what());
	}

	return -1;
}

GM_EXPORT pixelpart_gm::real GM_API pixelpart_get_image_resource_data(pixelpart_gm::string runtimePtr, pixelpart_gm::string resourceId, pixelpart_gm::string imageDataBufferPtr) {
	pixelpart_gm::EffectRuntime* effectRuntime = pixelpart_gm::parsePtr<pixelpart_gm::EffectRuntime>(runtimePtr);
	if(!effectRuntime) {
		pixelpart_gm::lastError = pixelpart_gm::invalidEffectRuntimeError;
		return -1;
	}
	else if(!resourceId || !imageDataBufferPtr) {
		pixelpart_gm::lastError = pixelpart_gm::invalidArgumentError;
		return -1;
	}

	try {
		const pixelpart::ImageResource& image =
			effectRuntime->effectAsset.effect().resources().images().at(std::string(resourceId));

		std::memcpy(imageDataBufferPtr, image.data().data(), image.data().size());

		return 1;
	}
	catch(const std::exception& e) {
		pixelpart_gm::lastError = std::string(e.what());
	}

	return -1;
}
}
