#include "Common.h"
#include "Error.h"
#include "pixelpart-runtime/common/Types.h"
#include "pixelpart-runtime/effect/StaticProperty.h"

extern "C" {
GM_EXPORT pixelpart_gm::real GM_API pixelpart_static_property_bool_value(pixelpart_gm::string propertyPtr) {
	pixelpart::StaticProperty<bool>* property = pixelpart_gm::parsePtr<pixelpart::StaticProperty<bool>>(propertyPtr);
	if(!property) {
		pixelpart_gm::lastError = pixelpart_gm::invalidPropertyError;
		return -1;
	}

	return property->value() ? 1 : 0;
}

GM_EXPORT pixelpart_gm::real GM_API pixelpart_static_property_bool_set_base_value(pixelpart_gm::string propertyPtr, pixelpart_gm::real value) {
	pixelpart::StaticProperty<bool>* property = pixelpart_gm::parsePtr<pixelpart::StaticProperty<bool>>(propertyPtr);
	if(!property) {
		pixelpart_gm::lastError = pixelpart_gm::invalidPropertyError;
		return -1;
	}

	property->baseValue(value > 0.5);

	return 1;
}

GM_EXPORT pixelpart_gm::real GM_API pixelpart_static_property_bool_get_base_value(pixelpart_gm::string propertyPtr) {
	pixelpart::StaticProperty<bool>* property = pixelpart_gm::parsePtr<pixelpart::StaticProperty<bool>>(propertyPtr);
	if(!property) {
		pixelpart_gm::lastError = pixelpart_gm::invalidPropertyError;
		return -1;
	}

	return property->baseValue() ? 1 : 0;
}
}
