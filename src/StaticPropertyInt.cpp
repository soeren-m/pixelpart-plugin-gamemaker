#include "Common.h"
#include "Error.h"
#include "pixelpart-runtime/common/Types.h"
#include "pixelpart-runtime/effect/StaticProperty.h"

extern "C" {
GM_EXPORT pixelpart_gm::real GM_API pixelpart_static_property_int_value(pixelpart_gm::string propertyPtr) {
	pixelpart::StaticProperty<pixelpart::int_t>* property = pixelpart_gm::parsePtr<pixelpart::StaticProperty<pixelpart::int_t>>(propertyPtr);
	if(!property) {
		pixelpart_gm::lastError = pixelpart_gm::invalidPropertyError;
		return -1;
	}

	return static_cast<pixelpart_gm::real>(property->value());
}

GM_EXPORT pixelpart_gm::real GM_API pixelpart_static_property_int_set_base_value(pixelpart_gm::string propertyPtr, pixelpart_gm::real value) {
	pixelpart::StaticProperty<pixelpart::int_t>* property = pixelpart_gm::parsePtr<pixelpart::StaticProperty<pixelpart::int_t>>(propertyPtr);
	if(!property) {
		pixelpart_gm::lastError = pixelpart_gm::invalidPropertyError;
		return -1;
	}

	property->baseValue(static_cast<pixelpart::int_t>(value));

	return 1;
}

GM_EXPORT pixelpart_gm::real GM_API pixelpart_static_property_int_get_base_value(pixelpart_gm::string propertyPtr) {
	pixelpart::StaticProperty<pixelpart::int_t>* property = pixelpart_gm::parsePtr<pixelpart::StaticProperty<pixelpart::int_t>>(propertyPtr);
	if(!property) {
		pixelpart_gm::lastError = pixelpart_gm::invalidPropertyError;
		return -1;
	}

	return static_cast<pixelpart_gm::real>(property->baseValue());
}
}
