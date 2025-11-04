#include "Common.h"
#include "Error.h"
#include "pixelpart-runtime/common/Types.h"
#include "pixelpart-runtime/effect/StaticProperty.h"

extern "C" {
GMS2_EXPORT pixelpart_gms2::real GMS2_API pixelpart_static_property_float_value(pixelpart_gms2::string propertyPtr) {
	pixelpart::StaticProperty<pixelpart::float_t>* property = reinterpret_cast<pixelpart::StaticProperty<pixelpart::float_t>*>(propertyPtr);
	if(!property) {
		pixelpart_gms2::lastError = pixelpart_gms2::invalidPropertyError;
		return -1;
	}

	return property->value();
}

GMS2_EXPORT pixelpart_gms2::real GMS2_API pixelpart_static_property_float_set_base_value(pixelpart_gms2::string propertyPtr, pixelpart_gms2::real value) {
	pixelpart::StaticProperty<pixelpart::float_t>* property = reinterpret_cast<pixelpart::StaticProperty<pixelpart::float_t>*>(propertyPtr);
	if(!property) {
		pixelpart_gms2::lastError = pixelpart_gms2::invalidPropertyError;
		return -1;
	}

	property->baseValue(value);

	return 1;
}

GMS2_EXPORT pixelpart_gms2::real GMS2_API pixelpart_static_property_float_get_base_value(pixelpart_gms2::string propertyPtr) {
	pixelpart::StaticProperty<pixelpart::float_t>* property = reinterpret_cast<pixelpart::StaticProperty<pixelpart::float_t>*>(propertyPtr);
	if(!property) {
		pixelpart_gms2::lastError = pixelpart_gms2::invalidPropertyError;
		return -1;
	}

	return property->baseValue();
}
}