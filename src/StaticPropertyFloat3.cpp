#include "Common.h"
#include "Buffer.h"
#include "Error.h"
#include "pixelpart-runtime/common/Types.h"
#include "pixelpart-runtime/effect/StaticProperty.h"

extern "C" {
GM_EXPORT pixelpart_gm::real GM_API pixelpart_static_property_float3_value(pixelpart_gm::string propertyPtr, pixelpart_gm::string valueBufferPtr) {
	pixelpart::StaticProperty<pixelpart::float3_t>* property = pixelpart_gm::parsePtr<pixelpart::StaticProperty<pixelpart::float3_t>>(propertyPtr);
	if(!property) {
		pixelpart_gm::lastError = pixelpart_gm::invalidPropertyError;
		return -1;
	}
	else if(!valueBufferPtr) {
		pixelpart_gm::lastError = pixelpart_gm::invalidArgumentError;
		return -1;
	}

	pixelpart_gm::Buffer valueBuffer(valueBufferPtr);
	valueBuffer.write(property->value());

	return 1;
}

GM_EXPORT pixelpart_gm::real GM_API pixelpart_static_property_float3_set_base_value(pixelpart_gm::string propertyPtr, pixelpart_gm::string valueBufferPtr) {
	pixelpart::StaticProperty<pixelpart::float3_t>* property = pixelpart_gm::parsePtr<pixelpart::StaticProperty<pixelpart::float3_t>>(propertyPtr);
	if(!property) {
		pixelpart_gm::lastError = pixelpart_gm::invalidPropertyError;
		return -1;
	}
	else if(!valueBufferPtr) {
		pixelpart_gm::lastError = pixelpart_gm::invalidArgumentError;
		return -1;
	}

	pixelpart_gm::Buffer valueBuffer(valueBufferPtr);
	property->baseValue(valueBuffer.read<pixelpart::float3_t>());

	return 1;
}

GM_EXPORT pixelpart_gm::real GM_API pixelpart_static_property_float3_get_base_value(pixelpart_gm::string propertyPtr, pixelpart_gm::string valueBufferPtr) {
	pixelpart::StaticProperty<pixelpart::float3_t>* property = pixelpart_gm::parsePtr<pixelpart::StaticProperty<pixelpart::float3_t>>(propertyPtr);
	if(!property) {
		pixelpart_gm::lastError = pixelpart_gm::invalidPropertyError;
		return -1;
	}
	else if(!valueBufferPtr) {
		pixelpart_gm::lastError = pixelpart_gm::invalidArgumentError;
		return -1;
	}

	pixelpart_gm::Buffer valueBuffer(valueBufferPtr);
	valueBuffer.write(property->baseValue());

	return 1;
}
}
