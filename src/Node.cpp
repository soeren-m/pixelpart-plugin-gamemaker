#include "Common.h"
#include "Error.h"
#include "Buffer.h"
#include "EffectRuntime.h"
#include "pixelpart-runtime/common/Math.h"
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

namespace pixelpart_gms2 {
std::string nodePropertyPtrString = "";
}

extern "C" {
GMS2_EXPORT pixelpart_gms2::real GMS2_API pixelpart_find_node(pixelpart_gms2::string runtimePtr, pixelpart_gms2::string bufferPtr) {
	pixelpart_gms2::EffectRuntime* effectRuntime = reinterpret_cast<pixelpart_gms2::EffectRuntime*>(runtimePtr);
	if(!effectRuntime) {
		pixelpart_gms2::lastError = pixelpart_gms2::invalidEffectRuntimeError;
		return -1;
	}

	std::string name(bufferPtr);
	for(const auto& node : effectRuntime->effectAsset.effect().sceneGraph()) {
		if(node->name() == name) {
			return node->id().value();
		}
	}

	return -1;
}

GMS2_EXPORT pixelpart_gms2::real GMS2_API pixelpart_find_node_by_index(pixelpart_gms2::string runtimePtr, pixelpart_gms2::real nodeIndex) {
	pixelpart_gms2::EffectRuntime* effectRuntime = reinterpret_cast<pixelpart_gms2::EffectRuntime*>(runtimePtr);
	if(!effectRuntime) {
		pixelpart_gms2::lastError = pixelpart_gms2::invalidEffectRuntimeError;
		return -1;
	}
	else if(nodeIndex < 0 || nodeIndex >= effectRuntime->effectAsset.effect().sceneGraph().count()) {
		pixelpart_gms2::lastError = pixelpart_gms2::invalidArgumentError;
		return -1;
	}

	return effectRuntime->effectAsset.effect().sceneGraph().atIndex(static_cast<std::uint32_t>(nodeIndex)).id().value();
}

GMS2_EXPORT pixelpart_gms2::real GMS2_API pixelpart_node_exists(pixelpart_gms2::string runtimePtr, pixelpart_gms2::real nodeId) {
	pixelpart_gms2::EffectRuntime* effectRuntime = reinterpret_cast<pixelpart_gms2::EffectRuntime*>(runtimePtr);
	if(!effectRuntime) {
		pixelpart_gms2::lastError = pixelpart_gms2::invalidEffectRuntimeError;
		return -1;
	}

	return effectRuntime->effectAsset.effect().sceneGraph().contains(static_cast<std::uint32_t>(nodeId)) ? 1 : 0;
}

GMS2_EXPORT pixelpart_gms2::real GMS2_API pixelpart_node_get_type(pixelpart_gms2::string runtimePtr, pixelpart_gms2::real nodeId) {
	pixelpart_gms2::EffectRuntime* effectRuntime = reinterpret_cast<pixelpart_gms2::EffectRuntime*>(runtimePtr);
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
		pixelpart_gms2::lastError = pixelpart_gms2::invalidEffectRuntimeError;
		return static_cast<pixelpart_gms2::real>(pixelpart_node_type::unknown);
	}

	try {
		const pixelpart::Node& node =
			effectRuntime->effectAsset.effect().sceneGraph().at(pixelpart::id_t(nodeId));

		if(dynamic_cast<const pixelpart::GroupNode*>(&node)) {
			return static_cast<pixelpart_gms2::real>(pixelpart_node_type::groupNode);
		}
		else if(dynamic_cast<const pixelpart::ParticleEmitter*>(&node)) {
			return static_cast<pixelpart_gms2::real>(pixelpart_node_type::particleEmitter);
		}
		else if(dynamic_cast<const pixelpart::AttractionField*>(&node)) {
			return static_cast<pixelpart_gms2::real>(pixelpart_node_type::attractionField);
		}
		else if(dynamic_cast<const pixelpart::AccelerationField*>(&node)) {
			return static_cast<pixelpart_gms2::real>(pixelpart_node_type::accelerationField);
		}
		else if(dynamic_cast<const pixelpart::VectorField*>(&node)) {
			return static_cast<pixelpart_gms2::real>(pixelpart_node_type::vectorField);
		}
		else if(dynamic_cast<const pixelpart::NoiseField*>(&node)) {
			return static_cast<pixelpart_gms2::real>(pixelpart_node_type::noiseField);
		}
		else if(dynamic_cast<const pixelpart::DragField*>(&node)) {
			return static_cast<pixelpart_gms2::real>(pixelpart_node_type::dragField);
		}
		else if(dynamic_cast<const pixelpart::LineCollider*>(&node)) {
			return static_cast<pixelpart_gms2::real>(pixelpart_node_type::lineCollider);
		}
		else if(dynamic_cast<const pixelpart::PlaneCollider*>(&node)) {
			return static_cast<pixelpart_gms2::real>(pixelpart_node_type::planeCollider);
		}
		else if(dynamic_cast<const pixelpart::DirectionalLightSource*>(&node)) {
			return static_cast<pixelpart_gms2::real>(pixelpart_node_type::directionalLightSource);
		}
		else if(dynamic_cast<const pixelpart::PointLightSource*>(&node)) {
			return static_cast<pixelpart_gms2::real>(pixelpart_node_type::pointLightSource);
		}
		else if(dynamic_cast<const pixelpart::SpotLightSource*>(&node)) {
			return static_cast<pixelpart_gms2::real>(pixelpart_node_type::spotLightSource);
		}

		return static_cast<pixelpart_gms2::real>(pixelpart_node_type::unknown);
	}
	catch(const std::exception& e) {
		pixelpart_gms2::lastError = std::string(e.what());
	}

	return static_cast<pixelpart_gms2::real>(pixelpart_node_type::unknown);
}

GMS2_EXPORT pixelpart_gms2::const_string GMS2_API pixelpart_node_get_name(pixelpart_gms2::string runtimePtr, pixelpart_gms2::real nodeId) {
	pixelpart_gms2::EffectRuntime* effectRuntime = reinterpret_cast<pixelpart_gms2::EffectRuntime*>(runtimePtr);
	if(!effectRuntime) {
		pixelpart_gms2::lastError = pixelpart_gms2::invalidEffectRuntimeError;
		return "";
	}

	try {
		const pixelpart::Node& node =
			effectRuntime->effectAsset.effect().sceneGraph().at(pixelpart::id_t(nodeId));

		return node.name().c_str();
	}
	catch(const std::exception& e) {
		pixelpart_gms2::lastError = std::string(e.what());
	}

	return "";
}

GMS2_EXPORT pixelpart_gms2::real GMS2_API pixelpart_node_get_parent_id(pixelpart_gms2::string runtimePtr, pixelpart_gms2::real nodeId) {
	pixelpart_gms2::EffectRuntime* effectRuntime = reinterpret_cast<pixelpart_gms2::EffectRuntime*>(runtimePtr);
	if(!effectRuntime) {
		pixelpart_gms2::lastError = pixelpart_gms2::invalidEffectRuntimeError;
		return -1;
	}

	try {
		const pixelpart::Node& node =
			effectRuntime->effectAsset.effect().sceneGraph().at(pixelpart::id_t(nodeId));

		return node.parentId().value();
	}
	catch(const std::exception& e) {
		pixelpart_gms2::lastError = std::string(e.what());
	}

	return -1;
}

GMS2_EXPORT pixelpart_gms2::real GMS2_API pixelpart_node_set_start(pixelpart_gms2::string runtimePtr, pixelpart_gms2::real nodeId, pixelpart_gms2::real value) {
	pixelpart_gms2::EffectRuntime* effectRuntime = reinterpret_cast<pixelpart_gms2::EffectRuntime*>(runtimePtr);
	if(!effectRuntime) {
		pixelpart_gms2::lastError = pixelpart_gms2::invalidEffectRuntimeError;
		return -1;
	}

	try {
		pixelpart::Node& node =
			effectRuntime->effectAsset.effect().sceneGraph().at(pixelpart::id_t(nodeId));

		node.start(value);

		return 1;
	}
	catch(const std::exception& e) {
		pixelpart_gms2::lastError = std::string(e.what());
	}

	return -1;
}

GMS2_EXPORT pixelpart_gms2::real GMS2_API pixelpart_node_set_duration(pixelpart_gms2::string runtimePtr, pixelpart_gms2::real nodeId, pixelpart_gms2::real value) {
	pixelpart_gms2::EffectRuntime* effectRuntime = reinterpret_cast<pixelpart_gms2::EffectRuntime*>(runtimePtr);
	if(!effectRuntime) {
		pixelpart_gms2::lastError = pixelpart_gms2::invalidEffectRuntimeError;
		return -1;
	}

	try {
		pixelpart::Node& node =
			effectRuntime->effectAsset.effect().sceneGraph().at(pixelpart::id_t(nodeId));

		node.duration(value);

		return 1;
	}
	catch(const std::exception& e) {
		pixelpart_gms2::lastError = std::string(e.what());
	}

	return -1;
}

GMS2_EXPORT pixelpart_gms2::real GMS2_API pixelpart_node_set_repeat(pixelpart_gms2::string runtimePtr, pixelpart_gms2::real nodeId, pixelpart_gms2::real value) {
	pixelpart_gms2::EffectRuntime* effectRuntime = reinterpret_cast<pixelpart_gms2::EffectRuntime*>(runtimePtr);
	if(!effectRuntime) {
		pixelpart_gms2::lastError = pixelpart_gms2::invalidEffectRuntimeError;
		return -1;
	}

	try {
		pixelpart::Node& node =
			effectRuntime->effectAsset.effect().sceneGraph().at(pixelpart::id_t(nodeId));

		node.repeat(value > 0.5);

		return 1;
	}
	catch(const std::exception& e) {
		pixelpart_gms2::lastError = std::string(e.what());
	}

	return -1;
}

GMS2_EXPORT pixelpart_gms2::real GMS2_API pixelpart_node_get_start(pixelpart_gms2::string runtimePtr, pixelpart_gms2::real nodeId) {
	pixelpart_gms2::EffectRuntime* effectRuntime = reinterpret_cast<pixelpart_gms2::EffectRuntime*>(runtimePtr);
	if(!effectRuntime) {
		pixelpart_gms2::lastError = pixelpart_gms2::invalidEffectRuntimeError;
		return -1;
	}

	try {
		const pixelpart::Node& node =
			effectRuntime->effectAsset.effect().sceneGraph().at(pixelpart::id_t(nodeId));

		return node.start();
	}
	catch(const std::exception& e) {
		pixelpart_gms2::lastError = std::string(e.what());
	}

	return -1;
}

GMS2_EXPORT pixelpart_gms2::real GMS2_API pixelpart_node_get_duration(pixelpart_gms2::string runtimePtr, pixelpart_gms2::real nodeId) {
	pixelpart_gms2::EffectRuntime* effectRuntime = reinterpret_cast<pixelpart_gms2::EffectRuntime*>(runtimePtr);
	if(!effectRuntime) {
		pixelpart_gms2::lastError = pixelpart_gms2::invalidEffectRuntimeError;
		return -1;
	}

	try {
		const pixelpart::Node& node =
			effectRuntime->effectAsset.effect().sceneGraph().at(pixelpart::id_t(nodeId));

		return node.duration();
	}
	catch(const std::exception& e) {
		pixelpart_gms2::lastError = std::string(e.what());
	}

	return -1;
}

GMS2_EXPORT pixelpart_gms2::real GMS2_API pixelpart_node_is_repeating(pixelpart_gms2::string runtimePtr, pixelpart_gms2::real nodeId) {
	pixelpart_gms2::EffectRuntime* effectRuntime = reinterpret_cast<pixelpart_gms2::EffectRuntime*>(runtimePtr);
	if(!effectRuntime) {
		pixelpart_gms2::lastError = pixelpart_gms2::invalidEffectRuntimeError;
		return -1;
	}

	try {
		const pixelpart::Node& node =
			effectRuntime->effectAsset.effect().sceneGraph().at(pixelpart::id_t(nodeId));

		return node.repeat() ? 1.0 : 0.0;
	}
	catch(const std::exception& e) {
		pixelpart_gms2::lastError = std::string(e.what());
	}

	return -1;
}

GMS2_EXPORT pixelpart_gms2::real GMS2_API pixelpart_node_is_active(pixelpart_gms2::string runtimePtr, pixelpart_gms2::real nodeId) {
	pixelpart_gms2::EffectRuntime* effectRuntime = reinterpret_cast<pixelpart_gms2::EffectRuntime*>(runtimePtr);
	if(!effectRuntime) {
		pixelpart_gms2::lastError = pixelpart_gms2::invalidEffectRuntimeError;
		return -1;
	}

	try {
		const pixelpart::Node& node =
			effectRuntime->effectAsset.effect().sceneGraph().at(pixelpart::id_t(nodeId));

		return node.active(effectRuntime->effectEngine->runtimeContext()) ? 1.0 : 0.0;
	}
	catch(const std::exception& e) {
		pixelpart_gms2::lastError = std::string(e.what());
	}

	return -1;
}

GMS2_EXPORT pixelpart_gms2::real GMS2_API pixelpart_node_get_local_time(pixelpart_gms2::string runtimePtr, pixelpart_gms2::real nodeId) {
	pixelpart_gms2::EffectRuntime* effectRuntime = reinterpret_cast<pixelpart_gms2::EffectRuntime*>(runtimePtr);
	if(!effectRuntime) {
		pixelpart_gms2::lastError = pixelpart_gms2::invalidEffectRuntimeError;
		return -1;
	}

	try {
		const pixelpart::Node& node =
			effectRuntime->effectAsset.effect().sceneGraph().at(pixelpart::id_t(nodeId));

		return node.life(effectRuntime->effectEngine->runtimeContext());
	}
	catch(const std::exception& e) {
		pixelpart_gms2::lastError = std::string(e.what());
	}

	return -1;
}

GMS2_EXPORT pixelpart_gms2::const_string GMS2_API pixelpart_node_get_position(pixelpart_gms2::string runtimePtr, pixelpart_gms2::real nodeId) {
	pixelpart_gms2::EffectRuntime* effectRuntime = reinterpret_cast<pixelpart_gms2::EffectRuntime*>(runtimePtr);
	if(!effectRuntime) {
		pixelpart_gms2::lastError = pixelpart_gms2::invalidEffectRuntimeError;
		pixelpart_gms2::nodePropertyPtrString = pixelpart_gms2::nullPointerString;

		return pixelpart_gms2::nodePropertyPtrString.c_str();
	}

	try {
		pixelpart::Node& node =
			effectRuntime->effectAsset.effect().sceneGraph().at(pixelpart::id_t(nodeId));

		pixelpart_gms2::nodePropertyPtrString = pixelpart_gms2::toBufferString(&node.position());
	}
	catch(const std::exception& e) {
		pixelpart_gms2::lastError = std::string(e.what());
		pixelpart_gms2::nodePropertyPtrString = pixelpart_gms2::nullPointerString;
	}

	return pixelpart_gms2::nodePropertyPtrString.c_str();
}

GMS2_EXPORT pixelpart_gms2::const_string GMS2_API pixelpart_node_get_rotation(pixelpart_gms2::string runtimePtr, pixelpart_gms2::real nodeId) {
	pixelpart_gms2::EffectRuntime* effectRuntime = reinterpret_cast<pixelpart_gms2::EffectRuntime*>(runtimePtr);
	if(!effectRuntime) {
		pixelpart_gms2::lastError = pixelpart_gms2::invalidEffectRuntimeError;
		pixelpart_gms2::nodePropertyPtrString = pixelpart_gms2::nullPointerString;

		return pixelpart_gms2::nodePropertyPtrString.c_str();
	}

	try {
		pixelpart::Node& node =
			effectRuntime->effectAsset.effect().sceneGraph().at(pixelpart::id_t(nodeId));

		pixelpart_gms2::nodePropertyPtrString = pixelpart_gms2::toBufferString(&node.rotation());
	}
	catch(const std::exception& e) {
		pixelpart_gms2::lastError = std::string(e.what());
		pixelpart_gms2::nodePropertyPtrString = pixelpart_gms2::nullPointerString;
	}

	return pixelpart_gms2::nodePropertyPtrString.c_str();
}

GMS2_EXPORT pixelpart_gms2::const_string GMS2_API pixelpart_node_get_scale(pixelpart_gms2::string runtimePtr, pixelpart_gms2::real nodeId) {
	pixelpart_gms2::EffectRuntime* effectRuntime = reinterpret_cast<pixelpart_gms2::EffectRuntime*>(runtimePtr);
	if(!effectRuntime) {
		pixelpart_gms2::lastError = pixelpart_gms2::invalidEffectRuntimeError;
		pixelpart_gms2::nodePropertyPtrString = pixelpart_gms2::nullPointerString;

		return pixelpart_gms2::nodePropertyPtrString.c_str();
	}

	try {
		pixelpart::Node& node =
			effectRuntime->effectAsset.effect().sceneGraph().at(pixelpart::id_t(nodeId));

		pixelpart_gms2::nodePropertyPtrString = pixelpart_gms2::toBufferString(&node.scale());
	}
	catch(const std::exception& e) {
		pixelpart_gms2::lastError = std::string(e.what());
		pixelpart_gms2::nodePropertyPtrString = pixelpart_gms2::nullPointerString;
	}

	return pixelpart_gms2::nodePropertyPtrString.c_str();
}
}