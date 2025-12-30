#include "Common.h"
#include "Error.h"
#include "EffectRuntime.h"
#include "pixelpart-runtime/effect/ImageResource.h"
#include <cstdint>
#include <cstring>
#include <string>
#include <exception>

extern "C" {
GMS2_EXPORT pixelpart_gms2::real GMS2_API pixelpart_get_image_resource_count(pixelpart_gms2::string runtimePtr) {
	pixelpart_gms2::EffectRuntime* effectRuntime = pixelpart_gms2::parsePtr<pixelpart_gms2::EffectRuntime>(runtimePtr);
	if(!effectRuntime) {
		pixelpart_gms2::lastError = pixelpart_gms2::invalidEffectRuntimeError;
		return -1;
	}

	return static_cast<pixelpart_gms2::real>(effectRuntime->effectAsset.effect().resources().images().size());
}

GMS2_EXPORT pixelpart_gms2::real GMS2_API pixelpart_get_image_resource_id(pixelpart_gms2::string runtimePtr, pixelpart_gms2::real index, pixelpart_gms2::string resourceIdBufferPtr, pixelpart_gms2::real resourceIdBufferSize) {
	pixelpart_gms2::EffectRuntime* effectRuntime = pixelpart_gms2::parsePtr<pixelpart_gms2::EffectRuntime>(runtimePtr);
	if(!effectRuntime) {
		pixelpart_gms2::lastError = pixelpart_gms2::invalidEffectRuntimeError;
		return -1;
	}
	else if(!resourceIdBufferPtr) {
		pixelpart_gms2::lastError = pixelpart_gms2::invalidArgumentError;
		return -1;
	}

	std::uint32_t currentIndex = 0;
	for(const auto& entry : effectRuntime->effectAsset.effect().resources().images()) {
		if(currentIndex != static_cast<std::uint32_t>(index)) {
			currentIndex++;
			continue;
		}

		if(entry.first.size() > static_cast<std::size_t>(resourceIdBufferSize)) {
			return 0;
		}

		std::memcpy(resourceIdBufferPtr, entry.first.c_str(), entry.first.size());
		resourceIdBufferPtr[entry.first.size()] = '\0';

		return static_cast<pixelpart_gms2::real>(entry.first.size());
	}

	return 0;
}

GMS2_EXPORT pixelpart_gms2::real GMS2_API pixelpart_get_image_resource_width(pixelpart_gms2::string runtimePtr, pixelpart_gms2::string resourceId) {
	pixelpart_gms2::EffectRuntime* effectRuntime = pixelpart_gms2::parsePtr<pixelpart_gms2::EffectRuntime>(runtimePtr);
	if(!effectRuntime) {
		pixelpart_gms2::lastError = pixelpart_gms2::invalidEffectRuntimeError;
		return -1;
	}
	else if(!resourceId) {
		pixelpart_gms2::lastError = pixelpart_gms2::invalidArgumentError;
		return -1;
	}

	try {
		const pixelpart::ImageResource& image =
			effectRuntime->effectAsset.effect().resources().images().at(std::string(resourceId));

		return static_cast<pixelpart_gms2::real>(image.width());
	}
	catch(const std::exception& e) {
		pixelpart_gms2::lastError = std::string(e.what());
	}

	return -1;
}

GMS2_EXPORT pixelpart_gms2::real GMS2_API pixelpart_get_image_resource_height(pixelpart_gms2::string runtimePtr, pixelpart_gms2::string resourceId) {
	pixelpart_gms2::EffectRuntime* effectRuntime = pixelpart_gms2::parsePtr<pixelpart_gms2::EffectRuntime>(runtimePtr);
	if(!effectRuntime) {
		pixelpart_gms2::lastError = pixelpart_gms2::invalidEffectRuntimeError;
		return -1;
	}
	else if(!resourceId) {
		pixelpart_gms2::lastError = pixelpart_gms2::invalidArgumentError;
		return -1;
	}

	try {
		const pixelpart::ImageResource& image =
			effectRuntime->effectAsset.effect().resources().images().at(std::string(resourceId));

		return static_cast<pixelpart_gms2::real>(image.height());
	}
	catch(const std::exception& e) {
		pixelpart_gms2::lastError = std::string(e.what());
	}

	return -1;
}

GMS2_EXPORT pixelpart_gms2::real GMS2_API pixelpart_get_image_resource_channels(pixelpart_gms2::string runtimePtr, pixelpart_gms2::string resourceId) {
	pixelpart_gms2::EffectRuntime* effectRuntime = pixelpart_gms2::parsePtr<pixelpart_gms2::EffectRuntime>(runtimePtr);
	if(!effectRuntime) {
		pixelpart_gms2::lastError = pixelpart_gms2::invalidEffectRuntimeError;
		return -1;
	}
	else if(!resourceId) {
		pixelpart_gms2::lastError = pixelpart_gms2::invalidArgumentError;
		return -1;
	}

	try {
		const pixelpart::ImageResource& image =
			effectRuntime->effectAsset.effect().resources().images().at(std::string(resourceId));

		return static_cast<pixelpart_gms2::real>(image.channels());
	}
	catch(const std::exception& e) {
		pixelpart_gms2::lastError = std::string(e.what());
	}

	return -1;
}

GMS2_EXPORT pixelpart_gms2::real GMS2_API pixelpart_get_image_resource_color_space(pixelpart_gms2::string runtimePtr, pixelpart_gms2::string resourceId) {
	pixelpart_gms2::EffectRuntime* effectRuntime = pixelpart_gms2::parsePtr<pixelpart_gms2::EffectRuntime>(runtimePtr);
	if(!effectRuntime) {
		pixelpart_gms2::lastError = pixelpart_gms2::invalidEffectRuntimeError;
		return -1;
	}
	else if(!resourceId) {
		pixelpart_gms2::lastError = pixelpart_gms2::invalidArgumentError;
		return -1;
	}

	try {
		const pixelpart::ImageResource& image =
			effectRuntime->effectAsset.effect().resources().images().at(std::string(resourceId));

		return static_cast<pixelpart_gms2::real>(image.colorSpace());
	}
	catch(const std::exception& e) {
		pixelpart_gms2::lastError = std::string(e.what());
	}

	return -1;
}

GMS2_EXPORT pixelpart_gms2::real GMS2_API pixelpart_get_image_resource_data_size(pixelpart_gms2::string runtimePtr, pixelpart_gms2::string resourceId) {
	pixelpart_gms2::EffectRuntime* effectRuntime = pixelpart_gms2::parsePtr<pixelpart_gms2::EffectRuntime>(runtimePtr);
	if(!effectRuntime) {
		pixelpart_gms2::lastError = pixelpart_gms2::invalidEffectRuntimeError;
		return -1;
	}
	else if(!resourceId) {
		pixelpart_gms2::lastError = pixelpart_gms2::invalidArgumentError;
		return -1;
	}

	try {
		const pixelpart::ImageResource& image =
			effectRuntime->effectAsset.effect().resources().images().at(std::string(resourceId));

		return static_cast<pixelpart_gms2::real>(image.data().size());
	}
	catch(const std::exception& e) {
		pixelpart_gms2::lastError = std::string(e.what());
	}

	return -1;
}

GMS2_EXPORT pixelpart_gms2::real GMS2_API pixelpart_get_image_resource_data(pixelpart_gms2::string runtimePtr, pixelpart_gms2::string resourceId, pixelpart_gms2::string imageDataBufferPtr) {
	pixelpart_gms2::EffectRuntime* effectRuntime = pixelpart_gms2::parsePtr<pixelpart_gms2::EffectRuntime>(runtimePtr);
	if(!effectRuntime) {
		pixelpart_gms2::lastError = pixelpart_gms2::invalidEffectRuntimeError;
		return -1;
	}
	else if(!resourceId || !imageDataBufferPtr) {
		pixelpart_gms2::lastError = pixelpart_gms2::invalidArgumentError;
		return -1;
	}

	try {
		const pixelpart::ImageResource& image =
			effectRuntime->effectAsset.effect().resources().images().at(std::string(resourceId));

		std::memcpy(imageDataBufferPtr, image.data().data(), image.data().size());

		return 1;
	}
	catch(const std::exception& e) {
		pixelpart_gms2::lastError = std::string(e.what());
	}

	return -1;
}
}
