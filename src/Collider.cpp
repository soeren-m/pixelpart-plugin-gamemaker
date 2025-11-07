#include "Common.h"
#include "Error.h"
#include "Buffer.h"
#include "EffectRuntime.h"
#include "pixelpart-runtime/common/Id.h"
#include "pixelpart-runtime/common/Math.h"
#include "pixelpart-runtime/effect/StaticProperty.h"
#include "pixelpart-runtime/effect/AnimatedProperty.h"
#include "pixelpart-runtime/effect/Collider.h"
#include "pixelpart-runtime/effect/LineCollider.h"
#include <cstring>
#include <string>
#include <exception>

namespace pixelpart_gms2 {
std::string colliderPropertyPtrString = "";
}

extern "C" {
GMS2_EXPORT pixelpart_gms2::const_string GMS2_API pixelpart_collider_get_kill_on_contact(pixelpart_gms2::string runtimePtr, pixelpart_gms2::real colliderId) {
	pixelpart_gms2::EffectRuntime* effectRuntime = reinterpret_cast<pixelpart_gms2::EffectRuntime*>(runtimePtr);
	if(!effectRuntime) {
		pixelpart_gms2::lastError = pixelpart_gms2::invalidEffectRuntimeError;
		pixelpart_gms2::colliderPropertyPtrString = pixelpart_gms2::nullPointerString;

		return pixelpart_gms2::colliderPropertyPtrString.c_str();
	}

	try {
		pixelpart::Collider& collider =
			effectRuntime->effectAsset.effect().sceneGraph().at<pixelpart::Collider>(pixelpart::id_t(colliderId));

		pixelpart_gms2::colliderPropertyPtrString = pixelpart_gms2::toBufferString(&collider.killOnContact());
	}
	catch(const std::exception& e) {
		pixelpart_gms2::lastError = std::string(e.what());
		pixelpart_gms2::colliderPropertyPtrString = pixelpart_gms2::nullPointerString;
	}

	return pixelpart_gms2::colliderPropertyPtrString.c_str();
}

GMS2_EXPORT pixelpart_gms2::const_string GMS2_API pixelpart_collider_get_bounce(pixelpart_gms2::string runtimePtr, pixelpart_gms2::real colliderId) {
	pixelpart_gms2::EffectRuntime* effectRuntime = reinterpret_cast<pixelpart_gms2::EffectRuntime*>(runtimePtr);
	if(!effectRuntime) {
		pixelpart_gms2::lastError = pixelpart_gms2::invalidEffectRuntimeError;
		pixelpart_gms2::colliderPropertyPtrString = pixelpart_gms2::nullPointerString;

		return pixelpart_gms2::colliderPropertyPtrString.c_str();
	}

	try {
		pixelpart::Collider& collider =
			effectRuntime->effectAsset.effect().sceneGraph().at<pixelpart::Collider>(pixelpart::id_t(colliderId));

		pixelpart_gms2::colliderPropertyPtrString = pixelpart_gms2::toBufferString(&collider.bounce());
	}
	catch(const std::exception& e) {
		pixelpart_gms2::lastError = std::string(e.what());
		pixelpart_gms2::colliderPropertyPtrString = pixelpart_gms2::nullPointerString;
	}

	return pixelpart_gms2::colliderPropertyPtrString.c_str();
}

GMS2_EXPORT pixelpart_gms2::const_string GMS2_API pixelpart_collider_get_friction(pixelpart_gms2::string runtimePtr, pixelpart_gms2::real colliderId) {
	pixelpart_gms2::EffectRuntime* effectRuntime = reinterpret_cast<pixelpart_gms2::EffectRuntime*>(runtimePtr);
	if(!effectRuntime) {
		pixelpart_gms2::lastError = pixelpart_gms2::invalidEffectRuntimeError;
		pixelpart_gms2::colliderPropertyPtrString = pixelpart_gms2::nullPointerString;

		return pixelpart_gms2::colliderPropertyPtrString.c_str();
	}

	try {
		pixelpart::Collider& collider =
			effectRuntime->effectAsset.effect().sceneGraph().at<pixelpart::Collider>(pixelpart::id_t(colliderId));

		pixelpart_gms2::colliderPropertyPtrString = pixelpart_gms2::toBufferString(&collider.friction());
	}
	catch(const std::exception& e) {
		pixelpart_gms2::lastError = std::string(e.what());
		pixelpart_gms2::colliderPropertyPtrString = pixelpart_gms2::nullPointerString;
	}

	return pixelpart_gms2::colliderPropertyPtrString.c_str();
}

GMS2_EXPORT pixelpart_gms2::real GMS2_API pixelpart_line_collider_add_point(pixelpart_gms2::string runtimePtr, pixelpart_gms2::real colliderId, pixelpart_gms2::string valueBufferPtr) {
	pixelpart_gms2::EffectRuntime* effectRuntime = reinterpret_cast<pixelpart_gms2::EffectRuntime*>(runtimePtr);
	if(!effectRuntime) {
		pixelpart_gms2::lastError = pixelpart_gms2::invalidEffectRuntimeError;
		return -1;
	}
	else if(!valueBufferPtr) {
		pixelpart_gms2::lastError = pixelpart_gms2::invalidArgumentError;
		return -1;
	}

	try {
		pixelpart::LineCollider& collider =
			effectRuntime->effectAsset.effect().sceneGraph().at<pixelpart::LineCollider>(pixelpart::id_t(colliderId));

		pixelpart_gms2::Buffer valueBuffer(valueBufferPtr);
		collider.points().push_back(valueBuffer.read<pixelpart::float3_t>());

		return 1;
	}
	catch(const std::exception& e) {
		pixelpart_gms2::lastError = std::string(e.what());
	}

	return -1;
}

GMS2_EXPORT pixelpart_gms2::real GMS2_API pixelpart_line_collider_set_point(pixelpart_gms2::string runtimePtr, pixelpart_gms2::real colliderId, pixelpart_gms2::real index, pixelpart_gms2::string valueBufferPtr) {
	pixelpart_gms2::EffectRuntime* effectRuntime = reinterpret_cast<pixelpart_gms2::EffectRuntime*>(runtimePtr);
	if(!effectRuntime) {
		pixelpart_gms2::lastError = pixelpart_gms2::invalidEffectRuntimeError;
		return -1;
	}
	else if(index < 0 || !valueBufferPtr) {
		pixelpart_gms2::lastError = pixelpart_gms2::invalidArgumentError;
		return -1;
	}

	try {
		pixelpart::LineCollider& collider =
			effectRuntime->effectAsset.effect().sceneGraph().at<pixelpart::LineCollider>(pixelpart::id_t(colliderId));

		pixelpart_gms2::Buffer valueBuffer(valueBufferPtr);
		collider.points().at(static_cast<std::size_t>(index)) = valueBuffer.read<pixelpart::float3_t>();

		return 1;
	}
	catch(const std::exception& e) {
		pixelpart_gms2::lastError = std::string(e.what());
	}

	return -1;
}

GMS2_EXPORT pixelpart_gms2::real GMS2_API pixelpart_line_collider_remove_point(pixelpart_gms2::string runtimePtr, pixelpart_gms2::real colliderId, pixelpart_gms2::real index) {
	pixelpart_gms2::EffectRuntime* effectRuntime = reinterpret_cast<pixelpart_gms2::EffectRuntime*>(runtimePtr);
	if(!effectRuntime) {
		pixelpart_gms2::lastError = pixelpart_gms2::invalidEffectRuntimeError;
		return -1;
	}
	else if(index < 0) {
		pixelpart_gms2::lastError = pixelpart_gms2::invalidArgumentError;
		return -1;
	}

	try {
		pixelpart::LineCollider& collider =
			effectRuntime->effectAsset.effect().sceneGraph().at<pixelpart::LineCollider>(pixelpart::id_t(colliderId));

		collider.points().erase(collider.points().begin() + static_cast<std::size_t>(index));

		return 1;
	}
	catch(const std::exception& e) {
		pixelpart_gms2::lastError = std::string(e.what());
	}

	return -1;
}

GMS2_EXPORT pixelpart_gms2::real GMS2_API pixelpart_line_collider_get_point(pixelpart_gms2::string runtimePtr, pixelpart_gms2::real colliderId, pixelpart_gms2::real index, pixelpart_gms2::string valueBufferPtr) {
	pixelpart_gms2::EffectRuntime* effectRuntime = reinterpret_cast<pixelpart_gms2::EffectRuntime*>(runtimePtr);
	if(!effectRuntime) {
		pixelpart_gms2::lastError = pixelpart_gms2::invalidEffectRuntimeError;
		return -1;
	}
	else if(index < 0 || !valueBufferPtr) {
		pixelpart_gms2::lastError = pixelpart_gms2::invalidArgumentError;
		return -1;
	}

	try {
		pixelpart::LineCollider& collider =
			effectRuntime->effectAsset.effect().sceneGraph().at<pixelpart::LineCollider>(pixelpart::id_t(colliderId));

		pixelpart_gms2::Buffer valueBuffer(valueBufferPtr);
		valueBuffer.write(collider.points().at(static_cast<std::size_t>(index)));

		return 1;
	}
	catch(const std::exception& e) {
		pixelpart_gms2::lastError = std::string(e.what());
	}

	return -1;
}

GMS2_EXPORT pixelpart_gms2::real GMS2_API pixelpart_line_collider_get_point_count(pixelpart_gms2::string runtimePtr, pixelpart_gms2::real colliderId) {
	pixelpart_gms2::EffectRuntime* effectRuntime = reinterpret_cast<pixelpart_gms2::EffectRuntime*>(runtimePtr);
	if(!effectRuntime) {
		pixelpart_gms2::lastError = pixelpart_gms2::invalidEffectRuntimeError;
		return -1;
	}

	try {
		pixelpart::LineCollider& collider =
			effectRuntime->effectAsset.effect().sceneGraph().at<pixelpart::LineCollider>(pixelpart::id_t(colliderId));

		return static_cast<pixelpart_gms2::real>(collider.points().size());
	}
	catch(const std::exception& e) {
		pixelpart_gms2::lastError = std::string(e.what());
	}

	return -1;
}
}
