#include "Common.h"
#include "Error.h"
#include "pixelpart-runtime/common/Types.h"
#include "pixelpart-runtime/effect/StaticProperty.h"

extern "C" {
GMS2_EXPORT pixelpart_gms2::real GMS2_API pixelpart_static_property_int_value(pixelpart_gms2::string propertyPtr) {
	pixelpart::StaticProperty<pixelpart::int_t>* property = reinterpret_cast<pixelpart::StaticProperty<pixelpart::int_t>*>(propertyPtr);
	if(!property) {
		pixelpart_gms2::lastError = pixelpart_gms2::invalidPropertyError;
		return -1;
	}

	return static_cast<pixelpart_gms2::real>(property->value());
}

GMS2_EXPORT pixelpart_gms2::real GMS2_API pixelpart_static_property_int_set_base_value(pixelpart_gms2::string propertyPtr, pixelpart_gms2::real value) {
	pixelpart::StaticProperty<pixelpart::int_t>* property = reinterpret_cast<pixelpart::StaticProperty<pixelpart::int_t>*>(propertyPtr);
	if(!property) {
		pixelpart_gms2::lastError = pixelpart_gms2::invalidPropertyError;
		return -1;
	}

	property->baseValue(static_cast<pixelpart::int_t>(value));

	return 1;
}

GMS2_EXPORT pixelpart_gms2::real GMS2_API pixelpart_static_property_int_get_base_value(pixelpart_gms2::string propertyPtr) {
	pixelpart::StaticProperty<pixelpart::int_t>* property = reinterpret_cast<pixelpart::StaticProperty<pixelpart::int_t>*>(propertyPtr);
	if(!property) {
		pixelpart_gms2::lastError = pixelpart_gms2::invalidPropertyError;
		return -1;
	}

	return static_cast<pixelpart_gms2::real>(property->baseValue());
}
}