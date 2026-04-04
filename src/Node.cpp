#include "Common.h"
#include "Error.h"
#include "Buffer.h"
#include "EffectRuntime.h"
#include "pixelpart-runtime/common/Types.h"
#include "pixelpart-runtime/common/Id.h"
#include "pixelpart-runtime/effect/AnimatedProperty.h"
#include "pixelpart-runtime/effect/GroupNode.h"
#include "pixelpart-runtime/effect/ParticleEmitter.h"
#include "pixelpart-runtime/effect/AttractionField.h"
#include "pixelpart-runtime/effect/AccelerationField.h"
#include "pixelpart-runtime/effect/VectorField.h"
#include "pixelpart-runtime/effect/NoiseField.h"
#include "pixelpart-runtime/effect/DragField.h"
#include "pixelpart-runtime/effect/LineCollider.h"
#include "pixelpart-runtime/effect/PlaneCollider.h"
#include "pixelpart-runtime/effect/DirectionalLightSource.h"
#include "pixelpart-runtime/effect/PointLightSource.h"
#include "pixelpart-runtime/effect/SpotLightSource.h"
#include <cstdint>
#include <cstring>
#include <string>
#include <algorithm>
#include <exception>

namespace pixelpart_gm {
std::string nodePropertyPtrString = "";
}

extern "C" {
GM_EXPORT pixelpart_gm::real GM_API pixelpart_find_node(pixelpart_gm::string runtimePtr, pixelpart_gm::string name) {
	pixelpart_gm::EffectRuntime* effectRuntime = pixelpart_gm::parsePtr<pixelpart_gm::EffectRuntime>(runtimePtr);
	if(!effectRuntime) {
		pixelpart_gm::lastError = pixelpart_gm::invalidEffectRuntimeError;
		return -1;
	}

	std::string nodeName(name);
	for(const auto& node : effectRuntime->effectAsset.effect().sceneGraph()) {
		if(node->name() == nodeName) {
			return node->id().value();
		}
	}

	return -1;
}

GM_EXPORT pixelpart_gm::real GM_API pixelpart_find_node_by_index(pixelpart_gm::string runtimePtr, pixelpart_gm::real nodeIndex) {
	pixelpart_gm::EffectRuntime* effectRuntime = pixelpart_gm::parsePtr<pixelpart_gm::EffectRuntime>(runtimePtr);
	if(!effectRuntime) {
		pixelpart_gm::lastError = pixelpart_gm::invalidEffectRuntimeError;
		return -1;
	}
	else if(nodeIndex < 0 || nodeIndex >= effectRuntime->effectAsset.effect().sceneGraph().count()) {
		pixelpart_gm::lastError = pixelpart_gm::invalidArgumentError;
		return -1;
	}

	return effectRuntime->effectAsset.effect().sceneGraph().atIndex(static_cast<std::uint32_t>(nodeIndex)).id().value();
}

GM_EXPORT pixelpart_gm::real GM_API pixelpart_node_exists(pixelpart_gm::string runtimePtr, pixelpart_gm::real nodeId) {
	pixelpart_gm::EffectRuntime* effectRuntime = pixelpart_gm::parsePtr<pixelpart_gm::EffectRuntime>(runtimePtr);
	if(!effectRuntime) {
		pixelpart_gm::lastError = pixelpart_gm::invalidEffectRuntimeError;
		return -1;
	}
	else if(nodeId < 0) {
		return 0;
	}

	return effectRuntime->effectAsset.effect().sceneGraph().contains(static_cast<std::uint32_t>(nodeId)) ? 1 : 0;
}

GM_EXPORT pixelpart_gm::real GM_API pixelpart_node_get_type(pixelpart_gm::string runtimePtr, pixelpart_gm::real nodeId) {
	pixelpart_gm::EffectRuntime* effectRuntime = pixelpart_gm::parsePtr<pixelpart_gm::EffectRuntime>(runtimePtr);
	enum class pixelpart_node_type : std::int32_t {
		unknown = -1,
		groupNode = 0,
		particleEmitter = 1,
		attractionField = 2,
		accelerationField = 3,
		vectorField = 4,
		noiseField = 5,
		dragField = 6,
		lineCollider = 7,
		planeCollider = 8,
		directionalLightSource = 9,
		pointLightSource = 10,
		spotLightSource = 11
	};

	if(!effectRuntime) {
		pixelpart_gm::lastError = pixelpart_gm::invalidEffectRuntimeError;
		return static_cast<pixelpart_gm::real>(pixelpart_node_type::unknown);
	}

	try {
		const pixelpart::Node& node =
			effectRuntime->effectAsset.effect().sceneGraph().at(pixelpart::id_t(nodeId));

		if(dynamic_cast<const pixelpart::GroupNode*>(&node)) {
			return static_cast<pixelpart_gm::real>(pixelpart_node_type::groupNode);
		}
		else if(dynamic_cast<const pixelpart::ParticleEmitter*>(&node)) {
			return static_cast<pixelpart_gm::real>(pixelpart_node_type::particleEmitter);
		}
		else if(dynamic_cast<const pixelpart::AttractionField*>(&node)) {
			return static_cast<pixelpart_gm::real>(pixelpart_node_type::attractionField);
		}
		else if(dynamic_cast<const pixelpart::AccelerationField*>(&node)) {
			return static_cast<pixelpart_gm::real>(pixelpart_node_type::accelerationField);
		}
		else if(dynamic_cast<const pixelpart::VectorField*>(&node)) {
			return static_cast<pixelpart_gm::real>(pixelpart_node_type::vectorField);
		}
		else if(dynamic_cast<const pixelpart::NoiseField*>(&node)) {
			return static_cast<pixelpart_gm::real>(pixelpart_node_type::noiseField);
		}
		else if(dynamic_cast<const pixelpart::DragField*>(&node)) {
			return static_cast<pixelpart_gm::real>(pixelpart_node_type::dragField);
		}
		else if(dynamic_cast<const pixelpart::LineCollider*>(&node)) {
			return static_cast<pixelpart_gm::real>(pixelpart_node_type::lineCollider);
		}
		else if(dynamic_cast<const pixelpart::PlaneCollider*>(&node)) {
			return static_cast<pixelpart_gm::real>(pixelpart_node_type::planeCollider);
		}
		else if(dynamic_cast<const pixelpart::DirectionalLightSource*>(&node)) {
			return static_cast<pixelpart_gm::real>(pixelpart_node_type::directionalLightSource);
		}
		else if(dynamic_cast<const pixelpart::PointLightSource*>(&node)) {
			return static_cast<pixelpart_gm::real>(pixelpart_node_type::pointLightSource);
		}
		else if(dynamic_cast<const pixelpart::SpotLightSource*>(&node)) {
			return static_cast<pixelpart_gm::real>(pixelpart_node_type::spotLightSource);
		}

		return static_cast<pixelpart_gm::real>(pixelpart_node_type::unknown);
	}
	catch(const std::exception& e) {
		pixelpart_gm::lastError = std::string(e.what());
	}

	return static_cast<pixelpart_gm::real>(pixelpart_node_type::unknown);
}

GM_EXPORT pixelpart_gm::const_string GM_API pixelpart_node_get_name(pixelpart_gm::string runtimePtr, pixelpart_gm::real nodeId) {
	pixelpart_gm::EffectRuntime* effectRuntime = pixelpart_gm::parsePtr<pixelpart_gm::EffectRuntime>(runtimePtr);
	if(!effectRuntime) {
		pixelpart_gm::lastError = pixelpart_gm::invalidEffectRuntimeError;
		return "";
	}

	try {
		const pixelpart::Node& node =
			effectRuntime->effectAsset.effect().sceneGraph().at(pixelpart::id_t(nodeId));

		return node.name().c_str();
	}
	catch(const std::exception& e) {
		pixelpart_gm::lastError = std::string(e.what());
	}

	return "";
}

GM_EXPORT pixelpart_gm::real GM_API pixelpart_node_get_parent_id(pixelpart_gm::string runtimePtr, pixelpart_gm::real nodeId) {
	pixelpart_gm::EffectRuntime* effectRuntime = pixelpart_gm::parsePtr<pixelpart_gm::EffectRuntime>(runtimePtr);
	if(!effectRuntime) {
		pixelpart_gm::lastError = pixelpart_gm::invalidEffectRuntimeError;
		return -1;
	}

	try {
		const pixelpart::Node& node =
			effectRuntime->effectAsset.effect().sceneGraph().at(pixelpart::id_t(nodeId));

		return node.parentId().valid() ? static_cast<pixelpart_gm::real>(node.parentId().value()) : -1;
	}
	catch(const std::exception& e) {
		pixelpart_gm::lastError = std::string(e.what());
	}

	return -1;
}

GM_EXPORT pixelpart_gm::real GM_API pixelpart_node_set_start(pixelpart_gm::string runtimePtr, pixelpart_gm::real nodeId, pixelpart_gm::real value) {
	pixelpart_gm::EffectRuntime* effectRuntime = pixelpart_gm::parsePtr<pixelpart_gm::EffectRuntime>(runtimePtr);
	if(!effectRuntime) {
		pixelpart_gm::lastError = pixelpart_gm::invalidEffectRuntimeError;
		return -1;
	}

	try {
		pixelpart::Node& node =
			effectRuntime->effectAsset.effect().sceneGraph().at(pixelpart::id_t(nodeId));

		node.start(value);

		return 1;
	}
	catch(const std::exception& e) {
		pixelpart_gm::lastError = std::string(e.what());
	}

	return -1;
}

GM_EXPORT pixelpart_gm::real GM_API pixelpart_node_set_duration(pixelpart_gm::string runtimePtr, pixelpart_gm::real nodeId, pixelpart_gm::real value) {
	pixelpart_gm::EffectRuntime* effectRuntime = pixelpart_gm::parsePtr<pixelpart_gm::EffectRuntime>(runtimePtr);
	if(!effectRuntime) {
		pixelpart_gm::lastError = pixelpart_gm::invalidEffectRuntimeError;
		return -1;
	}

	try {
		pixelpart::Node& node =
			effectRuntime->effectAsset.effect().sceneGraph().at(pixelpart::id_t(nodeId));

		node.duration(value);

		return 1;
	}
	catch(const std::exception& e) {
		pixelpart_gm::lastError = std::string(e.what());
	}

	return -1;
}

GM_EXPORT pixelpart_gm::real GM_API pixelpart_node_set_repeat(pixelpart_gm::string runtimePtr, pixelpart_gm::real nodeId, pixelpart_gm::real value) {
	pixelpart_gm::EffectRuntime* effectRuntime = pixelpart_gm::parsePtr<pixelpart_gm::EffectRuntime>(runtimePtr);
	if(!effectRuntime) {
		pixelpart_gm::lastError = pixelpart_gm::invalidEffectRuntimeError;
		return -1;
	}

	try {
		pixelpart::Node& node =
			effectRuntime->effectAsset.effect().sceneGraph().at(pixelpart::id_t(nodeId));

		node.repeat(value > 0.5);

		return 1;
	}
	catch(const std::exception& e) {
		pixelpart_gm::lastError = std::string(e.what());
	}

	return -1;
}

GM_EXPORT pixelpart_gm::real GM_API pixelpart_node_get_start(pixelpart_gm::string runtimePtr, pixelpart_gm::real nodeId) {
	pixelpart_gm::EffectRuntime* effectRuntime = pixelpart_gm::parsePtr<pixelpart_gm::EffectRuntime>(runtimePtr);
	if(!effectRuntime) {
		pixelpart_gm::lastError = pixelpart_gm::invalidEffectRuntimeError;
		return -1;
	}

	try {
		const pixelpart::Node& node =
			effectRuntime->effectAsset.effect().sceneGraph().at(pixelpart::id_t(nodeId));

		return node.start();
	}
	catch(const std::exception& e) {
		pixelpart_gm::lastError = std::string(e.what());
	}

	return -1;
}

GM_EXPORT pixelpart_gm::real GM_API pixelpart_node_get_duration(pixelpart_gm::string runtimePtr, pixelpart_gm::real nodeId) {
	pixelpart_gm::EffectRuntime* effectRuntime = pixelpart_gm::parsePtr<pixelpart_gm::EffectRuntime>(runtimePtr);
	if(!effectRuntime) {
		pixelpart_gm::lastError = pixelpart_gm::invalidEffectRuntimeError;
		return -1;
	}

	try {
		const pixelpart::Node& node =
			effectRuntime->effectAsset.effect().sceneGraph().at(pixelpart::id_t(nodeId));

		return node.duration();
	}
	catch(const std::exception& e) {
		pixelpart_gm::lastError = std::string(e.what());
	}

	return -1;
}

GM_EXPORT pixelpart_gm::real GM_API pixelpart_node_is_repeating(pixelpart_gm::string runtimePtr, pixelpart_gm::real nodeId) {
	pixelpart_gm::EffectRuntime* effectRuntime = pixelpart_gm::parsePtr<pixelpart_gm::EffectRuntime>(runtimePtr);
	if(!effectRuntime) {
		pixelpart_gm::lastError = pixelpart_gm::invalidEffectRuntimeError;
		return -1;
	}

	try {
		const pixelpart::Node& node =
			effectRuntime->effectAsset.effect().sceneGraph().at(pixelpart::id_t(nodeId));

		return node.repeat() ? 1.0 : 0.0;
	}
	catch(const std::exception& e) {
		pixelpart_gm::lastError = std::string(e.what());
	}

	return -1;
}

GM_EXPORT pixelpart_gm::real GM_API pixelpart_node_is_active(pixelpart_gm::string runtimePtr, pixelpart_gm::real nodeId) {
	pixelpart_gm::EffectRuntime* effectRuntime = pixelpart_gm::parsePtr<pixelpart_gm::EffectRuntime>(runtimePtr);
	if(!effectRuntime) {
		pixelpart_gm::lastError = pixelpart_gm::invalidEffectRuntimeError;
		return -1;
	}

	try {
		const pixelpart::Node& node =
			effectRuntime->effectAsset.effect().sceneGraph().at(pixelpart::id_t(nodeId));

		return node.active(effectRuntime->effectEngine->context()) ? 1.0 : 0.0;
	}
	catch(const std::exception& e) {
		pixelpart_gm::lastError = std::string(e.what());
	}

	return -1;
}

GM_EXPORT pixelpart_gm::real GM_API pixelpart_node_get_local_time(pixelpart_gm::string runtimePtr, pixelpart_gm::real nodeId) {
	pixelpart_gm::EffectRuntime* effectRuntime = pixelpart_gm::parsePtr<pixelpart_gm::EffectRuntime>(runtimePtr);
	if(!effectRuntime) {
		pixelpart_gm::lastError = pixelpart_gm::invalidEffectRuntimeError;
		return -1;
	}

	try {
		const pixelpart::Node& node =
			effectRuntime->effectAsset.effect().sceneGraph().at(pixelpart::id_t(nodeId));

		return node.life(effectRuntime->effectEngine->context());
	}
	catch(const std::exception& e) {
		pixelpart_gm::lastError = std::string(e.what());
	}

	return -1;
}

GM_EXPORT pixelpart_gm::const_string GM_API pixelpart_node_get_position(pixelpart_gm::string runtimePtr, pixelpart_gm::real nodeId) {
	pixelpart_gm::EffectRuntime* effectRuntime = pixelpart_gm::parsePtr<pixelpart_gm::EffectRuntime>(runtimePtr);
	if(!effectRuntime) {
		pixelpart_gm::lastError = pixelpart_gm::invalidEffectRuntimeError;
		pixelpart_gm::nodePropertyPtrString = "";

		return pixelpart_gm::nodePropertyPtrString.c_str();
	}

	try {
		pixelpart::Node& node =
			effectRuntime->effectAsset.effect().sceneGraph().at(pixelpart::id_t(nodeId));

		pixelpart_gm::nodePropertyPtrString = pixelpart_gm::ptrToString(&node.position());
	}
	catch(const std::exception& e) {
		pixelpart_gm::lastError = std::string(e.what());
		pixelpart_gm::nodePropertyPtrString = "";
	}

	return pixelpart_gm::nodePropertyPtrString.c_str();
}

GM_EXPORT pixelpart_gm::const_string GM_API pixelpart_node_get_rotation(pixelpart_gm::string runtimePtr, pixelpart_gm::real nodeId) {
	pixelpart_gm::EffectRuntime* effectRuntime = pixelpart_gm::parsePtr<pixelpart_gm::EffectRuntime>(runtimePtr);
	if(!effectRuntime) {
		pixelpart_gm::lastError = pixelpart_gm::invalidEffectRuntimeError;
		pixelpart_gm::nodePropertyPtrString = "";

		return pixelpart_gm::nodePropertyPtrString.c_str();
	}

	try {
		pixelpart::Node& node =
			effectRuntime->effectAsset.effect().sceneGraph().at(pixelpart::id_t(nodeId));

		pixelpart_gm::nodePropertyPtrString = pixelpart_gm::ptrToString(&node.rotation());
	}
	catch(const std::exception& e) {
		pixelpart_gm::lastError = std::string(e.what());
		pixelpart_gm::nodePropertyPtrString = "";
	}

	return pixelpart_gm::nodePropertyPtrString.c_str();
}

GM_EXPORT pixelpart_gm::const_string GM_API pixelpart_node_get_scale(pixelpart_gm::string runtimePtr, pixelpart_gm::real nodeId) {
	pixelpart_gm::EffectRuntime* effectRuntime = pixelpart_gm::parsePtr<pixelpart_gm::EffectRuntime>(runtimePtr);
	if(!effectRuntime) {
		pixelpart_gm::lastError = pixelpart_gm::invalidEffectRuntimeError;
		pixelpart_gm::nodePropertyPtrString = "";

		return pixelpart_gm::nodePropertyPtrString.c_str();
	}

	try {
		pixelpart::Node& node =
			effectRuntime->effectAsset.effect().sceneGraph().at(pixelpart::id_t(nodeId));

		pixelpart_gm::nodePropertyPtrString = pixelpart_gm::ptrToString(&node.scale());
	}
	catch(const std::exception& e) {
		pixelpart_gm::lastError = std::string(e.what());
		pixelpart_gm::nodePropertyPtrString = "";
	}

	return pixelpart_gm::nodePropertyPtrString.c_str();
}
}
