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

namespace pixelpart_gm {
std::string colliderPropertyPtrString = "";
}

extern "C" {
GM_EXPORT pixelpart_gm::const_string GM_API pixelpart_collider_get_kill_on_contact(pixelpart_gm::string runtimePtr, pixelpart_gm::real colliderId) {
	pixelpart_gm::EffectRuntime* effectRuntime = pixelpart_gm::parsePtr<pixelpart_gm::EffectRuntime>(runtimePtr);
	if(!effectRuntime) {
		pixelpart_gm::lastError = pixelpart_gm::invalidEffectRuntimeError;
		pixelpart_gm::colliderPropertyPtrString = "";

		return pixelpart_gm::colliderPropertyPtrString.c_str();
	}

	try {
		pixelpart::Collider& collider =
			effectRuntime->effectAsset.effect().sceneGraph().at<pixelpart::Collider>(pixelpart::id_t(colliderId));

		pixelpart_gm::colliderPropertyPtrString = pixelpart_gm::ptrToString(&collider.killOnContact());
	}
	catch(const std::exception& e) {
		pixelpart_gm::lastError = std::string(e.what());
		pixelpart_gm::colliderPropertyPtrString = "";
	}

	return pixelpart_gm::colliderPropertyPtrString.c_str();
}

GM_EXPORT pixelpart_gm::const_string GM_API pixelpart_collider_get_bounce(pixelpart_gm::string runtimePtr, pixelpart_gm::real colliderId) {
	pixelpart_gm::EffectRuntime* effectRuntime = pixelpart_gm::parsePtr<pixelpart_gm::EffectRuntime>(runtimePtr);
	if(!effectRuntime) {
		pixelpart_gm::lastError = pixelpart_gm::invalidEffectRuntimeError;
		pixelpart_gm::colliderPropertyPtrString = "";

		return pixelpart_gm::colliderPropertyPtrString.c_str();
	}

	try {
		pixelpart::Collider& collider =
			effectRuntime->effectAsset.effect().sceneGraph().at<pixelpart::Collider>(pixelpart::id_t(colliderId));

		pixelpart_gm::colliderPropertyPtrString = pixelpart_gm::ptrToString(&collider.bounce());
	}
	catch(const std::exception& e) {
		pixelpart_gm::lastError = std::string(e.what());
		pixelpart_gm::colliderPropertyPtrString = "";
	}

	return pixelpart_gm::colliderPropertyPtrString.c_str();
}

GM_EXPORT pixelpart_gm::const_string GM_API pixelpart_collider_get_friction(pixelpart_gm::string runtimePtr, pixelpart_gm::real colliderId) {
	pixelpart_gm::EffectRuntime* effectRuntime = pixelpart_gm::parsePtr<pixelpart_gm::EffectRuntime>(runtimePtr);
	if(!effectRuntime) {
		pixelpart_gm::lastError = pixelpart_gm::invalidEffectRuntimeError;
		pixelpart_gm::colliderPropertyPtrString = "";

		return pixelpart_gm::colliderPropertyPtrString.c_str();
	}

	try {
		pixelpart::Collider& collider =
			effectRuntime->effectAsset.effect().sceneGraph().at<pixelpart::Collider>(pixelpart::id_t(colliderId));

		pixelpart_gm::colliderPropertyPtrString = pixelpart_gm::ptrToString(&collider.friction());
	}
	catch(const std::exception& e) {
		pixelpart_gm::lastError = std::string(e.what());
		pixelpart_gm::colliderPropertyPtrString = "";
	}

	return pixelpart_gm::colliderPropertyPtrString.c_str();
}

GM_EXPORT pixelpart_gm::real GM_API pixelpart_line_collider_add_point(pixelpart_gm::string runtimePtr, pixelpart_gm::real colliderId, pixelpart_gm::string valueBufferPtr) {
	pixelpart_gm::EffectRuntime* effectRuntime = pixelpart_gm::parsePtr<pixelpart_gm::EffectRuntime>(runtimePtr);
	if(!effectRuntime) {
		pixelpart_gm::lastError = pixelpart_gm::invalidEffectRuntimeError;
		return -1;
	}
	else if(!valueBufferPtr) {
		pixelpart_gm::lastError = pixelpart_gm::invalidArgumentError;
		return -1;
	}

	try {
		pixelpart::LineCollider& collider =
			effectRuntime->effectAsset.effect().sceneGraph().at<pixelpart::LineCollider>(pixelpart::id_t(colliderId));

		pixelpart_gm::Buffer valueBuffer(valueBufferPtr);
		collider.points().push_back(valueBuffer.read<pixelpart::float3_t>());

		return 1;
	}
	catch(const std::exception& e) {
		pixelpart_gm::lastError = std::string(e.what());
	}

	return -1;
}

GM_EXPORT pixelpart_gm::real GM_API pixelpart_line_collider_set_point(pixelpart_gm::string runtimePtr, pixelpart_gm::real colliderId, pixelpart_gm::real index, pixelpart_gm::string valueBufferPtr) {
	pixelpart_gm::EffectRuntime* effectRuntime = pixelpart_gm::parsePtr<pixelpart_gm::EffectRuntime>(runtimePtr);
	if(!effectRuntime) {
		pixelpart_gm::lastError = pixelpart_gm::invalidEffectRuntimeError;
		return -1;
	}
	else if(index < 0 || !valueBufferPtr) {
		pixelpart_gm::lastError = pixelpart_gm::invalidArgumentError;
		return -1;
	}

	try {
		pixelpart::LineCollider& collider =
			effectRuntime->effectAsset.effect().sceneGraph().at<pixelpart::LineCollider>(pixelpart::id_t(colliderId));

		pixelpart_gm::Buffer valueBuffer(valueBufferPtr);
		collider.points().at(static_cast<std::size_t>(index)) = valueBuffer.read<pixelpart::float3_t>();

		return 1;
	}
	catch(const std::exception& e) {
		pixelpart_gm::lastError = std::string(e.what());
	}

	return -1;
}

GM_EXPORT pixelpart_gm::real GM_API pixelpart_line_collider_remove_point(pixelpart_gm::string runtimePtr, pixelpart_gm::real colliderId, pixelpart_gm::real index) {
	pixelpart_gm::EffectRuntime* effectRuntime = pixelpart_gm::parsePtr<pixelpart_gm::EffectRuntime>(runtimePtr);
	if(!effectRuntime) {
		pixelpart_gm::lastError = pixelpart_gm::invalidEffectRuntimeError;
		return -1;
	}
	else if(index < 0) {
		pixelpart_gm::lastError = pixelpart_gm::invalidArgumentError;
		return -1;
	}

	try {
		pixelpart::LineCollider& collider =
			effectRuntime->effectAsset.effect().sceneGraph().at<pixelpart::LineCollider>(pixelpart::id_t(colliderId));

		collider.points().erase(collider.points().begin() + static_cast<std::size_t>(index));

		return 1;
	}
	catch(const std::exception& e) {
		pixelpart_gm::lastError = std::string(e.what());
	}

	return -1;
}

GM_EXPORT pixelpart_gm::real GM_API pixelpart_line_collider_get_point(pixelpart_gm::string runtimePtr, pixelpart_gm::real colliderId, pixelpart_gm::real index, pixelpart_gm::string valueBufferPtr) {
	pixelpart_gm::EffectRuntime* effectRuntime = pixelpart_gm::parsePtr<pixelpart_gm::EffectRuntime>(runtimePtr);
	if(!effectRuntime) {
		pixelpart_gm::lastError = pixelpart_gm::invalidEffectRuntimeError;
		return -1;
	}
	else if(index < 0 || !valueBufferPtr) {
		pixelpart_gm::lastError = pixelpart_gm::invalidArgumentError;
		return -1;
	}

	try {
		pixelpart::LineCollider& collider =
			effectRuntime->effectAsset.effect().sceneGraph().at<pixelpart::LineCollider>(pixelpart::id_t(colliderId));

		pixelpart_gm::Buffer valueBuffer(valueBufferPtr);
		valueBuffer.write(collider.points().at(static_cast<std::size_t>(index)));

		return 1;
	}
	catch(const std::exception& e) {
		pixelpart_gm::lastError = std::string(e.what());
	}

	return -1;
}

GM_EXPORT pixelpart_gm::real GM_API pixelpart_line_collider_get_point_count(pixelpart_gm::string runtimePtr, pixelpart_gm::real colliderId) {
	pixelpart_gm::EffectRuntime* effectRuntime = pixelpart_gm::parsePtr<pixelpart_gm::EffectRuntime>(runtimePtr);
	if(!effectRuntime) {
		pixelpart_gm::lastError = pixelpart_gm::invalidEffectRuntimeError;
		return -1;
	}

	try {
		pixelpart::LineCollider& collider =
			effectRuntime->effectAsset.effect().sceneGraph().at<pixelpart::LineCollider>(pixelpart::id_t(colliderId));

		return static_cast<pixelpart_gm::real>(collider.points().size());
	}
	catch(const std::exception& e) {
		pixelpart_gm::lastError = std::string(e.what());
	}

	return -1;
}
}
