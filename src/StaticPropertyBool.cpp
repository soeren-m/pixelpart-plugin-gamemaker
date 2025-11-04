#include "Common.h"
#include "Error.h"
#include "pixelpart-runtime/common/Types.h"
#include "pixelpart-runtime/effect/StaticProperty.h"

extern "C" {
GMS2_EXPORT pixelpart_gms2::real GMS2_API pixelpart_static_property_bool_value(pixelpart_gms2::string propertyPtr) {
	pixelpart::StaticProperty<bool>* property = reinterpret_cast<pixelpart::StaticProperty<bool>*>(propertyPtr);
	if(!property) {
		pixelpart_gms2::lastError = pixelpart_gms2::invalidPropertyError;
		return -1;
	}

	return property->value() ? 1 : 0;
}

GMS2_EXPORT pixelpart_gms2::real GMS2_API pixelpart_static_property_bool_set_base_value(pixelpart_gms2::string propertyPtr, pixelpart_gms2::real value) {
	pixelpart::StaticProperty<bool>* property = reinterpret_cast<pixelpart::StaticProperty<bool>*>(propertyPtr);
	if(!property) {
		pixelpart_gms2::lastError = pixelpart_gms2::invalidPropertyError;
		return -1;
	}

	property->baseValue(value > 0.5);

	return 1;
}

GMS2_EXPORT pixelpart_gms2::real GMS2_API pixelpart_static_property_bool_get_base_value(pixelpart_gms2::string propertyPtr) {
	pixelpart::StaticProperty<bool>* property = reinterpret_cast<pixelpart::StaticProperty<bool>*>(propertyPtr);
	if(!property) {
		pixelpart_gms2::lastError = pixelpart_gms2::invalidPropertyError;
		return -1;
	}

	return property->baseValue() ? 1 : 0;
}
}