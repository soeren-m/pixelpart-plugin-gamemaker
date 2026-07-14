#include "Common.h"
#include "Buffer.h"
#include "Error.h"
#include "pixelpart-runtime/types/Types.h"
#include "pixelpart-runtime/effect/AnimatedProperty.h"
#include <cstddef>
#include <algorithm>

extern "C" {
GM_EXPORT pixelpart_gm::real GM_API pixelpart_animated_property_float3_at(pixelpart_gm::string propertyPtr, pixelpart_gm::real position, pixelpart_gm::string valueBufferPtr) {
	pixelpart::AnimatedProperty<pixelpart::float3_t>* property = pixelpart_gm::parsePtr<pixelpart::AnimatedProperty<pixelpart::float3_t>>(propertyPtr);
	if(!property) {
		pixelpart_gm::lastError = pixelpart_gm::invalidPropertyError;
		return -1;
	}
	else if(!valueBufferPtr) {
		pixelpart_gm::lastError = pixelpart_gm::invalidArgumentError;
		return -1;
	}

	pixelpart_gm::Buffer valueBuffer(valueBufferPtr);
	valueBuffer.write(property->at(position));

	return 1;
}

GM_EXPORT pixelpart_gm::real GM_API pixelpart_animated_property_float3_add_keyframe(pixelpart_gm::string propertyPtr, pixelpart_gm::real position, pixelpart_gm::string valueBufferPtr) {
	pixelpart::AnimatedProperty<pixelpart::float3_t>* property = pixelpart_gm::parsePtr<pixelpart::AnimatedProperty<pixelpart::float3_t>>(propertyPtr);
	if(!property) {
		pixelpart_gm::lastError = pixelpart_gm::invalidPropertyError;
		return -1;
	}
	else if(!valueBufferPtr) {
		pixelpart_gm::lastError = pixelpart_gm::invalidArgumentError;
		return -1;
	}

	pixelpart_gm::Buffer valueBuffer(valueBufferPtr);
	property->addKeyframe(position, valueBuffer.read<pixelpart::float3_t>());

	return 1;
}

GM_EXPORT pixelpart_gm::real GM_API pixelpart_animated_property_float3_remove_keyframe(pixelpart_gm::string propertyPtr, pixelpart_gm::real index) {
	pixelpart::AnimatedProperty<pixelpart::float3_t>* property = pixelpart_gm::parsePtr<pixelpart::AnimatedProperty<pixelpart::float3_t>>(propertyPtr);
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

GM_EXPORT pixelpart_gm::real GM_API pixelpart_animated_property_float3_set_keyframe_value(pixelpart_gm::string propertyPtr, pixelpart_gm::real index, pixelpart_gm::string valueBufferPtr) {
	pixelpart::AnimatedProperty<pixelpart::float3_t>* property = pixelpart_gm::parsePtr<pixelpart::AnimatedProperty<pixelpart::float3_t>>(propertyPtr);
	if(!property) {
		pixelpart_gm::lastError = pixelpart_gm::invalidPropertyError;
		return -1;
	}
	else if(index < 0 || !valueBufferPtr) {
		pixelpart_gm::lastError = pixelpart_gm::invalidArgumentError;
		return -1;
	}

	pixelpart_gm::Buffer valueBuffer(valueBufferPtr);
	property->setKeyframeValue(static_cast<std::size_t>(index), valueBuffer.read<pixelpart::float3_t>());

	return 1;
}

GM_EXPORT pixelpart_gm::real GM_API pixelpart_animated_property_float3_set_keyframe_position(pixelpart_gm::string propertyPtr, pixelpart_gm::real index, pixelpart_gm::real position) {
	pixelpart::AnimatedProperty<pixelpart::float3_t>* property = pixelpart_gm::parsePtr<pixelpart::AnimatedProperty<pixelpart::float3_t>>(propertyPtr);
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

GM_EXPORT pixelpart_gm::real GM_API pixelpart_animated_property_float3_clear_keyframes(pixelpart_gm::string propertyPtr) {
	pixelpart::AnimatedProperty<pixelpart::float3_t>* property = pixelpart_gm::parsePtr<pixelpart::AnimatedProperty<pixelpart::float3_t>>(propertyPtr);
	if(!property) {
		pixelpart_gm::lastError = pixelpart_gm::invalidPropertyError;
		return -1;
	}

	property->clearKeyframes();

	return 1;
}

GM_EXPORT pixelpart_gm::real GM_API pixelpart_animated_property_float3_keyframe_count(pixelpart_gm::string propertyPtr) {
	pixelpart::AnimatedProperty<pixelpart::float3_t>* property = pixelpart_gm::parsePtr<pixelpart::AnimatedProperty<pixelpart::float3_t>>(propertyPtr);
	if(!property) {
		pixelpart_gm::lastError = pixelpart_gm::invalidPropertyError;
		return -1;
	}

	return static_cast<pixelpart_gm::real>(property->keyframeCount());
}

GM_EXPORT pixelpart_gm::real GM_API pixelpart_animated_property_float3_keyframe_value(pixelpart_gm::string propertyPtr, pixelpart_gm::real index, pixelpart_gm::string valueBufferPtr) {
	pixelpart::AnimatedProperty<pixelpart::float3_t>* property = pixelpart_gm::parsePtr<pixelpart::AnimatedProperty<pixelpart::float3_t>>(propertyPtr);
	if(!property) {
		pixelpart_gm::lastError = pixelpart_gm::invalidPropertyError;
		return -1;
	}
	else if(index < 0 || static_cast<std::size_t>(index) >= property->keyframeCount() || !valueBufferPtr) {
		pixelpart_gm::lastError = pixelpart_gm::invalidArgumentError;
		return -1;
	}

	pixelpart_gm::Buffer valueBuffer(valueBufferPtr);
	valueBuffer.write(property->keyframe(static_cast<std::size_t>(index)).value);

	return 1;
}

GM_EXPORT pixelpart_gm::real GM_API pixelpart_animated_property_float3_keyframe_index(pixelpart_gm::string propertyPtr, pixelpart_gm::real position, pixelpart_gm::real epsilon) {
	pixelpart::AnimatedProperty<pixelpart::float3_t>* property = pixelpart_gm::parsePtr<pixelpart::AnimatedProperty<pixelpart::float3_t>>(propertyPtr);
	if(!property) {
		pixelpart_gm::lastError = pixelpart_gm::invalidPropertyError;
		return -1;
	}

	auto index = property->keyframeIndex(position, epsilon);

	return index ? static_cast<pixelpart_gm::real>(index.value()) : -1;
}

GM_EXPORT pixelpart_gm::real GM_API pixelpart_animated_property_float3_set_keyframe_interpolation(pixelpart_gm::string propertyPtr, pixelpart_gm::real method) {
	pixelpart::AnimatedProperty<pixelpart::float3_t>* property = pixelpart_gm::parsePtr<pixelpart::AnimatedProperty<pixelpart::float3_t>>(propertyPtr);
	if(!property) {
		pixelpart_gm::lastError = pixelpart_gm::invalidPropertyError;
		return -1;
	}

	property->keyframeInterpolation(static_cast<pixelpart::CurveInterpolation>(method));

	return 1;
}

GM_EXPORT pixelpart_gm::real GM_API pixelpart_animated_property_float3_get_keyframe_interpolation(pixelpart_gm::string propertyPtr) {
	pixelpart::AnimatedProperty<pixelpart::float3_t>* property = pixelpart_gm::parsePtr<pixelpart::AnimatedProperty<pixelpart::float3_t>>(propertyPtr);
	if(!property) {
		pixelpart_gm::lastError = pixelpart_gm::invalidPropertyError;
		return -1;
	}

	return static_cast<pixelpart_gm::real>(property->keyframeInterpolation());
}
}
