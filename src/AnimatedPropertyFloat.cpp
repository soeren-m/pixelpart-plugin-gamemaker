#include "Common.h"
#include "Error.h"
#include "pixelpart-runtime/common/Types.h"
#include "pixelpart-runtime/effect/AnimatedProperty.h"
#include <cstddef>
#include <algorithm>

extern "C" {
GMS2_EXPORT pixelpart_gms2::real GMS2_API pixelpart_animated_property_float_at(pixelpart_gms2::string propertyPtr, pixelpart_gms2::real position) {
	pixelpart::AnimatedProperty<pixelpart::float_t>* property = pixelpart_gms2::parsePtr<pixelpart::AnimatedProperty<pixelpart::float_t>>(propertyPtr);
	if(!property) {
		pixelpart_gms2::lastError = pixelpart_gms2::invalidPropertyError;
		return -1;
	}

	return property->at(position);
}

GMS2_EXPORT pixelpart_gms2::real GMS2_API pixelpart_animated_property_float_add_keyframe(pixelpart_gms2::string propertyPtr, pixelpart_gms2::real position, pixelpart_gms2::real value) {
	pixelpart::AnimatedProperty<pixelpart::float_t>* property = pixelpart_gms2::parsePtr<pixelpart::AnimatedProperty<pixelpart::float_t>>(propertyPtr);
	if(!property) {
		pixelpart_gms2::lastError = pixelpart_gms2::invalidPropertyError;
		return -1;
	}

	property->addKeyframe(position, value);

	return 1;
}

GMS2_EXPORT pixelpart_gms2::real GMS2_API pixelpart_animated_property_float_remove_keyframe(pixelpart_gms2::string propertyPtr, pixelpart_gms2::real index) {
	pixelpart::AnimatedProperty<pixelpart::float_t>* property = pixelpart_gms2::parsePtr<pixelpart::AnimatedProperty<pixelpart::float_t>>(propertyPtr);
	if(!property) {
		pixelpart_gms2::lastError = pixelpart_gms2::invalidPropertyError;
		return -1;
	}
	else if(index < 0) {
		pixelpart_gms2::lastError = pixelpart_gms2::invalidArgumentError;
		return -1;
	}

	property->removeKeyframe(static_cast<std::size_t>(index));

	return 1;
}

GMS2_EXPORT pixelpart_gms2::real GMS2_API pixelpart_animated_property_float_set_keyframe_value(pixelpart_gms2::string propertyPtr, pixelpart_gms2::real index, pixelpart_gms2::real value) {
	pixelpart::AnimatedProperty<pixelpart::float_t>* property = pixelpart_gms2::parsePtr<pixelpart::AnimatedProperty<pixelpart::float_t>>(propertyPtr);
	if(!property) {
		pixelpart_gms2::lastError = pixelpart_gms2::invalidPropertyError;
		return -1;
	}
	else if(index < 0) {
		pixelpart_gms2::lastError = pixelpart_gms2::invalidArgumentError;
		return -1;
	}

	property->setKeyframeValue(static_cast<std::size_t>(index), value);

	return 1;
}

GMS2_EXPORT pixelpart_gms2::real GMS2_API pixelpart_animated_property_float_set_keyframe_position(pixelpart_gms2::string propertyPtr, pixelpart_gms2::real index, pixelpart_gms2::real position) {
	pixelpart::AnimatedProperty<pixelpart::float_t>* property = pixelpart_gms2::parsePtr<pixelpart::AnimatedProperty<pixelpart::float_t>>(propertyPtr);
	if(!property) {
		pixelpart_gms2::lastError = pixelpart_gms2::invalidPropertyError;
		return -1;
	}
	else if(index < 0) {
		pixelpart_gms2::lastError = pixelpart_gms2::invalidArgumentError;
		return -1;
	}

	property->setKeyframePosition(static_cast<std::size_t>(index), position);

	return 1;
}

GMS2_EXPORT pixelpart_gms2::real GMS2_API pixelpart_animated_property_float_clear_keyframes(pixelpart_gms2::string propertyPtr) {
	pixelpart::AnimatedProperty<pixelpart::float_t>* property = pixelpart_gms2::parsePtr<pixelpart::AnimatedProperty<pixelpart::float_t>>(propertyPtr);
	if(!property) {
		pixelpart_gms2::lastError = pixelpart_gms2::invalidPropertyError;
		return -1;
	}

	property->clearKeyframes();

	return 1;
}

GMS2_EXPORT pixelpart_gms2::real GMS2_API pixelpart_animated_property_float_keyframe_count(pixelpart_gms2::string propertyPtr) {
	pixelpart::AnimatedProperty<pixelpart::float_t>* property = pixelpart_gms2::parsePtr<pixelpart::AnimatedProperty<pixelpart::float_t>>(propertyPtr);
	if(!property) {
		pixelpart_gms2::lastError = pixelpart_gms2::invalidPropertyError;
		return -1;
	}

	return static_cast<pixelpart_gms2::real>(property->keyframeCount());
}

GMS2_EXPORT pixelpart_gms2::real GMS2_API pixelpart_animated_property_float_keyframe_value(pixelpart_gms2::string propertyPtr, pixelpart_gms2::real index) {
	pixelpart::AnimatedProperty<pixelpart::float_t>* property = pixelpart_gms2::parsePtr<pixelpart::AnimatedProperty<pixelpart::float_t>>(propertyPtr);
	if(!property) {
		pixelpart_gms2::lastError = pixelpart_gms2::invalidPropertyError;
		return -1;
	}
	else if(index < 0 || static_cast<std::size_t>(index) >= property->keyframeCount()) {
		pixelpart_gms2::lastError = pixelpart_gms2::invalidArgumentError;
		return -1;
	}

	return property->keyframe(static_cast<std::size_t>(index)).value;
}

GMS2_EXPORT pixelpart_gms2::real GMS2_API pixelpart_animated_property_float_keyframe_index(pixelpart_gms2::string propertyPtr, pixelpart_gms2::real position, pixelpart_gms2::real epsilon) {
	pixelpart::AnimatedProperty<pixelpart::float_t>* property = pixelpart_gms2::parsePtr<pixelpart::AnimatedProperty<pixelpart::float_t>>(propertyPtr);
	if(!property) {
		pixelpart_gms2::lastError = pixelpart_gms2::invalidPropertyError;
		return -1;
	}

	return static_cast<pixelpart_gms2::real>(property->keyframeIndex(position, epsilon));
}

GMS2_EXPORT pixelpart_gms2::real GMS2_API pixelpart_animated_property_float_set_keyframe_interpolation(pixelpart_gms2::string propertyPtr, pixelpart_gms2::real method) {
	pixelpart::AnimatedProperty<pixelpart::float_t>* property = pixelpart_gms2::parsePtr<pixelpart::AnimatedProperty<pixelpart::float_t>>(propertyPtr);
	if(!property) {
		pixelpart_gms2::lastError = pixelpart_gms2::invalidPropertyError;
		return -1;
	}

	property->keyframeInterpolation(static_cast<pixelpart::CurveInterpolation>(method));

	return 1;
}

GMS2_EXPORT pixelpart_gms2::real GMS2_API pixelpart_animated_property_float_get_keyframe_interpolation(pixelpart_gms2::string propertyPtr) {
	pixelpart::AnimatedProperty<pixelpart::float_t>* property = pixelpart_gms2::parsePtr<pixelpart::AnimatedProperty<pixelpart::float_t>>(propertyPtr);
	if(!property) {
		pixelpart_gms2::lastError = pixelpart_gms2::invalidPropertyError;
		return -1;
	}

	return static_cast<pixelpart_gms2::real>(property->keyframeInterpolation());
}

GMS2_EXPORT pixelpart_gms2::real GMS2_API pixelpart_animated_property_float_enable_adaptive_cache(pixelpart_gms2::string propertyPtr) {
	pixelpart::AnimatedProperty<pixelpart::float_t>* property = pixelpart_gms2::parsePtr<pixelpart::AnimatedProperty<pixelpart::float_t>>(propertyPtr);
	if(!property) {
		pixelpart_gms2::lastError = pixelpart_gms2::invalidPropertyError;
		return -1;
	}

	property->enableAdaptiveCache();

	return 1;
}

GMS2_EXPORT pixelpart_gms2::real GMS2_API pixelpart_animated_property_float_enable_fixed_cache(pixelpart_gms2::string propertyPtr, pixelpart_gms2::real size) {
	pixelpart::AnimatedProperty<pixelpart::float_t>* property = pixelpart_gms2::parsePtr<pixelpart::AnimatedProperty<pixelpart::float_t>>(propertyPtr);
	if(!property) {
		pixelpart_gms2::lastError = pixelpart_gms2::invalidPropertyError;
		return -1;
	}

	property->enableFixedCache(static_cast<std::size_t>(std::max(size, 1.0)));

	return 1;
}
}
