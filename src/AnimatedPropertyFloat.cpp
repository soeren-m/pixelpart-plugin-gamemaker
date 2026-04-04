#include "Common.h"
#include "Error.h"
#include "pixelpart-runtime/common/Types.h"
#include "pixelpart-runtime/effect/AnimatedProperty.h"
#include <cstddef>
#include <algorithm>

extern "C" {
GM_EXPORT pixelpart_gm::real GM_API pixelpart_animated_property_float_at(pixelpart_gm::string propertyPtr, pixelpart_gm::real position) {
	pixelpart::AnimatedProperty<pixelpart::float_t>* property = pixelpart_gm::parsePtr<pixelpart::AnimatedProperty<pixelpart::float_t>>(propertyPtr);
	if(!property) {
		pixelpart_gm::lastError = pixelpart_gm::invalidPropertyError;
		return -1;
	}

	return property->at(position);
}

GM_EXPORT pixelpart_gm::real GM_API pixelpart_animated_property_float_add_keyframe(pixelpart_gm::string propertyPtr, pixelpart_gm::real position, pixelpart_gm::real value) {
	pixelpart::AnimatedProperty<pixelpart::float_t>* property = pixelpart_gm::parsePtr<pixelpart::AnimatedProperty<pixelpart::float_t>>(propertyPtr);
	if(!property) {
		pixelpart_gm::lastError = pixelpart_gm::invalidPropertyError;
		return -1;
	}

	property->addKeyframe(position, value);

	return 1;
}

GM_EXPORT pixelpart_gm::real GM_API pixelpart_animated_property_float_remove_keyframe(pixelpart_gm::string propertyPtr, pixelpart_gm::real index) {
	pixelpart::AnimatedProperty<pixelpart::float_t>* property = pixelpart_gm::parsePtr<pixelpart::AnimatedProperty<pixelpart::float_t>>(propertyPtr);
	if(!property) {
		pixelpart_gm::lastError = pixelpart_gm::invalidPropertyError;
		return -1;
	}
	else if(index < 0) {
		pixelpart_gm::lastError = pixelpart_gm::invalidArgumentError;
		return -1;
	}

	property->removeKeyframe(static_cast<std::size_t>(index));

	return 1;
}

GM_EXPORT pixelpart_gm::real GM_API pixelpart_animated_property_float_set_keyframe_value(pixelpart_gm::string propertyPtr, pixelpart_gm::real index, pixelpart_gm::real value) {
	pixelpart::AnimatedProperty<pixelpart::float_t>* property = pixelpart_gm::parsePtr<pixelpart::AnimatedProperty<pixelpart::float_t>>(propertyPtr);
	if(!property) {
		pixelpart_gm::lastError = pixelpart_gm::invalidPropertyError;
		return -1;
	}
	else if(index < 0) {
		pixelpart_gm::lastError = pixelpart_gm::invalidArgumentError;
		return -1;
	}

	property->setKeyframeValue(static_cast<std::size_t>(index), value);

	return 1;
}

GM_EXPORT pixelpart_gm::real GM_API pixelpart_animated_property_float_set_keyframe_position(pixelpart_gm::string propertyPtr, pixelpart_gm::real index, pixelpart_gm::real position) {
	pixelpart::AnimatedProperty<pixelpart::float_t>* property = pixelpart_gm::parsePtr<pixelpart::AnimatedProperty<pixelpart::float_t>>(propertyPtr);
	if(!property) {
		pixelpart_gm::lastError = pixelpart_gm::invalidPropertyError;
		return -1;
	}
	else if(index < 0) {
		pixelpart_gm::lastError = pixelpart_gm::invalidArgumentError;
		return -1;
	}

	property->setKeyframePosition(static_cast<std::size_t>(index), position);

	return 1;
}

GM_EXPORT pixelpart_gm::real GM_API pixelpart_animated_property_float_clear_keyframes(pixelpart_gm::string propertyPtr) {
	pixelpart::AnimatedProperty<pixelpart::float_t>* property = pixelpart_gm::parsePtr<pixelpart::AnimatedProperty<pixelpart::float_t>>(propertyPtr);
	if(!property) {
		pixelpart_gm::lastError = pixelpart_gm::invalidPropertyError;
		return -1;
	}

	property->clearKeyframes();

	return 1;
}

GM_EXPORT pixelpart_gm::real GM_API pixelpart_animated_property_float_keyframe_count(pixelpart_gm::string propertyPtr) {
	pixelpart::AnimatedProperty<pixelpart::float_t>* property = pixelpart_gm::parsePtr<pixelpart::AnimatedProperty<pixelpart::float_t>>(propertyPtr);
	if(!property) {
		pixelpart_gm::lastError = pixelpart_gm::invalidPropertyError;
		return -1;
	}

	return static_cast<pixelpart_gm::real>(property->keyframeCount());
}

GM_EXPORT pixelpart_gm::real GM_API pixelpart_animated_property_float_keyframe_value(pixelpart_gm::string propertyPtr, pixelpart_gm::real index) {
	pixelpart::AnimatedProperty<pixelpart::float_t>* property = pixelpart_gm::parsePtr<pixelpart::AnimatedProperty<pixelpart::float_t>>(propertyPtr);
	if(!property) {
		pixelpart_gm::lastError = pixelpart_gm::invalidPropertyError;
		return -1;
	}
	else if(index < 0 || static_cast<std::size_t>(index) >= property->keyframeCount()) {
		pixelpart_gm::lastError = pixelpart_gm::invalidArgumentError;
		return -1;
	}

	return property->keyframe(static_cast<std::size_t>(index)).value;
}

GM_EXPORT pixelpart_gm::real GM_API pixelpart_animated_property_float_keyframe_index(pixelpart_gm::string propertyPtr, pixelpart_gm::real position, pixelpart_gm::real epsilon) {
	pixelpart::AnimatedProperty<pixelpart::float_t>* property = pixelpart_gm::parsePtr<pixelpart::AnimatedProperty<pixelpart::float_t>>(propertyPtr);
	if(!property) {
		pixelpart_gm::lastError = pixelpart_gm::invalidPropertyError;
		return -1;
	}

	auto index = property->keyframeIndex(position, epsilon);

	return index ? static_cast<pixelpart_gm::real>(index.value()) : -1;
}

GM_EXPORT pixelpart_gm::real GM_API pixelpart_animated_property_float_set_keyframe_interpolation(pixelpart_gm::string propertyPtr, pixelpart_gm::real method) {
	pixelpart::AnimatedProperty<pixelpart::float_t>* property = pixelpart_gm::parsePtr<pixelpart::AnimatedProperty<pixelpart::float_t>>(propertyPtr);
	if(!property) {
		pixelpart_gm::lastError = pixelpart_gm::invalidPropertyError;
		return -1;
	}

	property->keyframeInterpolation(static_cast<pixelpart::CurveInterpolation>(method));

	return 1;
}

GM_EXPORT pixelpart_gm::real GM_API pixelpart_animated_property_float_get_keyframe_interpolation(pixelpart_gm::string propertyPtr) {
	pixelpart::AnimatedProperty<pixelpart::float_t>* property = pixelpart_gm::parsePtr<pixelpart::AnimatedProperty<pixelpart::float_t>>(propertyPtr);
	if(!property) {
		pixelpart_gm::lastError = pixelpart_gm::invalidPropertyError;
		return -1;
	}

	return static_cast<pixelpart_gm::real>(property->keyframeInterpolation());
}
}
