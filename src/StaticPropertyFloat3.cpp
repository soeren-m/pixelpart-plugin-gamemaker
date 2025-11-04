#include "Common.h"
#include "Buffer.h"
#include "Error.h"
#include "pixelpart-runtime/common/Types.h"
#include "pixelpart-runtime/effect/StaticProperty.h"

extern "C" {
GMS2_EXPORT pixelpart_gms2::real GMS2_API pixelpart_static_property_float3_value(pixelpart_gms2::string propertyPtr, pixelpart_gms2::string valueBufferPtr) {
	pixelpart::StaticProperty<pixelpart::float3_t>* property = reinterpret_cast<pixelpart::StaticProperty<pixelpart::float3_t>*>(propertyPtr);
	if(!property) {
		pixelpart_gms2::lastError = pixelpart_gms2::invalidPropertyError;
		return -1;
	}
	else if(!valueBufferPtr) {
		pixelpart_gms2::lastError = pixelpart_gms2::invalidArgumentError;
		return -1;
	}

	pixelpart_gms2::Buffer valueBuffer(valueBufferPtr);
	valueBuffer.write(property->value());

	return 1;
}

GMS2_EXPORT pixelpart_gms2::real GMS2_API pixelpart_static_property_float3_set_base_value(pixelpart_gms2::string propertyPtr, pixelpart_gms2::string valueBufferPtr) {
	pixelpart::StaticProperty<pixelpart::float3_t>* property = reinterpret_cast<pixelpart::StaticProperty<pixelpart::float3_t>*>(propertyPtr);
	if(!property) {
		pixelpart_gms2::lastError = pixelpart_gms2::invalidPropertyError;
		return -1;
	}
	else if(!valueBufferPtr) {
		pixelpart_gms2::lastError = pixelpart_gms2::invalidArgumentError;
		return -1;
	}

	pixelpart_gms2::Buffer valueBuffer(valueBufferPtr);
	property->baseValue(valueBuffer.read<pixelpart::float3_t>());

	return 1;
}

GMS2_EXPORT pixelpart_gms2::real GMS2_API pixelpart_static_property_float3_get_base_value(pixelpart_gms2::string propertyPtr, pixelpart_gms2::string valueBufferPtr) {
	pixelpart::StaticProperty<pixelpart::float3_t>* property = reinterpret_cast<pixelpart::StaticProperty<pixelpart::float3_t>*>(propertyPtr);
	if(!property) {
		pixelpart_gms2::lastError = pixelpart_gms2::invalidPropertyError;
		return -1;
	}
	else if(!valueBufferPtr) {
		pixelpart_gms2::lastError = pixelpart_gms2::invalidArgumentError;
		return -1;
	}

	pixelpart_gms2::Buffer valueBuffer(valueBufferPtr);
	valueBuffer.write(property->baseValue());

	return 1;
}
}