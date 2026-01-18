#include "Common.h"
#include "Error.h"
#include "pixelpart-runtime/common/Types.h"
#include "pixelpart-runtime/effect/StaticProperty.h"

extern "C" {
GM_EXPORT pixelpart_gm::real GM_API pixelpart_static_property_float_value(pixelpart_gm::string propertyPtr) {
	pixelpart::StaticProperty<pixelpart::float_t>* property = pixelpart_gm::parsePtr<pixelpart::StaticProperty<pixelpart::float_t>>(propertyPtr);
	if(!property) {
		pixelpart_gm::lastError = pixelpart_gm::invalidPropertyError;
		return -1;
	}

	return property->value();
}

GM_EXPORT pixelpart_gm::real GM_API pixelpart_static_property_float_set_base_value(pixelpart_gm::string propertyPtr, pixelpart_gm::real value) {
	pixelpart::StaticProperty<pixelpart::float_t>* property = pixelpart_gm::parsePtr<pixelpart::StaticProperty<pixelpart::float_t>>(propertyPtr);
	if(!property) {
		pixelpart_gm::lastError = pixelpart_gm::invalidPropertyError;
		return -1;
	}

	property->baseValue(value);

	return 1;
}

GM_EXPORT pixelpart_gm::real GM_API pixelpart_static_property_float_get_base_value(pixelpart_gm::string propertyPtr) {
	pixelpart::StaticProperty<pixelpart::float_t>* property = pixelpart_gm::parsePtr<pixelpart::StaticProperty<pixelpart::float_t>>(propertyPtr);
	if(!property) {
		pixelpart_gm::lastError = pixelpart_gm::invalidPropertyError;
		return -1;
	}

	return property->baseValue();
}
}
