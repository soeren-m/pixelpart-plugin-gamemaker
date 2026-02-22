#include "Common.h"
#include "Error.h"
#include "Buffer.h"
#include "EffectRuntime.h"
#include "pixelpart-runtime/common/Id.h"
#include "pixelpart-runtime/common/Math.h"
#include "pixelpart-runtime/effect/StaticProperty.h"
#include "pixelpart-runtime/effect/AnimatedProperty.h"
#include "pixelpart-runtime/effect/ParticleType.h"
#include <cstdint>
#include <cstring>
#include <string>
#include <algorithm>
#include <exception>

namespace pixelpart_gm {
std::string particleTypePropertyPtrString = "";
}

extern "C" {
GM_EXPORT pixelpart_gm::real GM_API pixelpart_find_particle_type(pixelpart_gm::string runtimePtr, pixelpart_gm::string name) {
	pixelpart_gm::EffectRuntime* effectRuntime = pixelpart_gm::parsePtr<pixelpart_gm::EffectRuntime>(runtimePtr);
	if(!effectRuntime) {
		pixelpart_gm::lastError = pixelpart_gm::invalidEffectRuntimeError;
		return -1;
	}

	std::string particleTypeName(name);
	for(const auto& particleType : effectRuntime->effectAsset.effect().particleTypes()) {
		if(particleType.name() == particleTypeName) {
			return particleType.id().value();
		}
	}

	return -1;
}

GM_EXPORT pixelpart_gm::real GM_API pixelpart_find_particle_type_by_index(pixelpart_gm::string runtimePtr, pixelpart_gm::real particleTypeIndex) {
	pixelpart_gm::EffectRuntime* effectRuntime = pixelpart_gm::parsePtr<pixelpart_gm::EffectRuntime>(runtimePtr);
	if(!effectRuntime) {
		pixelpart_gm::lastError = pixelpart_gm::invalidEffectRuntimeError;
		return -1;
	}
	else if(particleTypeIndex < 0 || particleTypeIndex >= effectRuntime->effectAsset.effect().particleTypes().count()) {
		pixelpart_gm::lastError = pixelpart_gm::invalidArgumentError;
		return -1;
	}

	return effectRuntime->effectAsset.effect().particleTypes().atIndex(static_cast<std::uint32_t>(particleTypeIndex)).id().value();
}

GM_EXPORT pixelpart_gm::real GM_API pixelpart_particle_type_exists(pixelpart_gm::string runtimePtr, pixelpart_gm::real particleTypeId) {
	pixelpart_gm::EffectRuntime* effectRuntime = pixelpart_gm::parsePtr<pixelpart_gm::EffectRuntime>(runtimePtr);
	if(!effectRuntime) {
		pixelpart_gm::lastError = pixelpart_gm::invalidEffectRuntimeError;
		return -1;
	}
	else if(particleTypeId < 0) {
		return 0;
	}

	return effectRuntime->effectAsset.effect().particleTypes().contains(pixelpart::id_t(particleTypeId)) ? 1 : 0;
}

GM_EXPORT pixelpart_gm::real GM_API pixelpart_particle_type_get_index(pixelpart_gm::string runtimePtr, pixelpart_gm::real particleTypeId) {
	pixelpart_gm::EffectRuntime* effectRuntime = pixelpart_gm::parsePtr<pixelpart_gm::EffectRuntime>(runtimePtr);
	if(!effectRuntime) {
		pixelpart_gm::lastError = pixelpart_gm::invalidEffectRuntimeError;
		return -1;
	}

	std::uint32_t particleTypeIndex = effectRuntime->effectAsset.effect().particleTypes().indexOf(pixelpart::id_t(particleTypeId));
	if(particleTypeIndex == pixelpart::id_t::nullValue) {
		return -1;
	}

	return static_cast<pixelpart_gm::real>(particleTypeIndex);
}

GM_EXPORT pixelpart_gm::real GM_API pixelpart_particle_type_get_parent_id(pixelpart_gm::string runtimePtr, pixelpart_gm::real particleTypeId) {
	pixelpart_gm::EffectRuntime* effectRuntime = pixelpart_gm::parsePtr<pixelpart_gm::EffectRuntime>(runtimePtr);
	if(!effectRuntime) {
		pixelpart_gm::lastError = pixelpart_gm::invalidEffectRuntimeError;
		return -1;
	}

	try {
		const pixelpart::ParticleType& particleType =
			effectRuntime->effectAsset.effect().particleTypes().at(pixelpart::id_t(particleTypeId));

		return particleType.parentId().valid() ? static_cast<pixelpart_gm::real>(particleType.parentId().value()) : -1;
	}
	catch(const std::exception& e) {
		pixelpart_gm::lastError = std::string(e.what());
	}

	return -1;
}

GM_EXPORT pixelpart_gm::const_string GM_API pixelpart_particle_type_get_name(pixelpart_gm::string runtimePtr, pixelpart_gm::real particleTypeId) {
	pixelpart_gm::EffectRuntime* effectRuntime = pixelpart_gm::parsePtr<pixelpart_gm::EffectRuntime>(runtimePtr);
	if(!effectRuntime) {
		pixelpart_gm::lastError = pixelpart_gm::invalidEffectRuntimeError;
		return "";
	}

	try {
		const pixelpart::ParticleType& particleType =
			effectRuntime->effectAsset.effect().particleTypes().at(pixelpart::id_t(particleTypeId));

		return particleType.name().c_str();
	}
	catch(const std::exception& e) {
		pixelpart_gm::lastError = std::string(e.what());
	}

	return "";
}

GM_EXPORT pixelpart_gm::real GM_API pixelpart_particle_type_set_position_relative(pixelpart_gm::string runtimePtr, pixelpart_gm::real particleTypeId, pixelpart_gm::real relative) {
	pixelpart_gm::EffectRuntime* effectRuntime = pixelpart_gm::parsePtr<pixelpart_gm::EffectRuntime>(runtimePtr);
	if(!effectRuntime) {
		pixelpart_gm::lastError = pixelpart_gm::invalidEffectRuntimeError;
		return -1;
	}

	try {
		pixelpart::ParticleType& particleType =
			effectRuntime->effectAsset.effect().particleTypes().at(pixelpart::id_t(particleTypeId));

		particleType.positionRelative(relative > 0.5);

		return 1;
	}
	catch(const std::exception& e) {
		pixelpart_gm::lastError = std::string(e.what());
	}

	return -1;
}

GM_EXPORT pixelpart_gm::real GM_API pixelpart_particle_type_is_position_relative(pixelpart_gm::string runtimePtr, pixelpart_gm::real particleTypeId) {
	pixelpart_gm::EffectRuntime* effectRuntime = pixelpart_gm::parsePtr<pixelpart_gm::EffectRuntime>(runtimePtr);
	if(!effectRuntime) {
		pixelpart_gm::lastError = pixelpart_gm::invalidEffectRuntimeError;
		return -1;
	}

	try {
		const pixelpart::ParticleType& particleType =
			effectRuntime->effectAsset.effect().particleTypes().at(pixelpart::id_t(particleTypeId));

		return particleType.positionRelative() ? 1 : 0;
	}
	catch(const std::exception& e) {
		pixelpart_gm::lastError = std::string(e.what());
	}

	return -1;
}

GM_EXPORT pixelpart_gm::real GM_API pixelpart_particle_type_set_rotation_mode(pixelpart_gm::string runtimePtr, pixelpart_gm::real particleTypeId, pixelpart_gm::real mode) {
	pixelpart_gm::EffectRuntime* effectRuntime = pixelpart_gm::parsePtr<pixelpart_gm::EffectRuntime>(runtimePtr);
	if(!effectRuntime) {
		pixelpart_gm::lastError = pixelpart_gm::invalidEffectRuntimeError;
		return -1;
	}

	try {
		pixelpart::ParticleType& particleType =
			effectRuntime->effectAsset.effect().particleTypes().at(pixelpart::id_t(particleTypeId));

		particleType.rotationMode(static_cast<pixelpart::RotationMode>(mode));

		return 1;
	}
	catch(const std::exception& e) {
		pixelpart_gm::lastError = std::string(e.what());
	}

	return -1;
}

GM_EXPORT pixelpart_gm::real GM_API pixelpart_particle_type_get_rotation_mode(pixelpart_gm::string runtimePtr, pixelpart_gm::real particleTypeId) {
	pixelpart_gm::EffectRuntime* effectRuntime = pixelpart_gm::parsePtr<pixelpart_gm::EffectRuntime>(runtimePtr);
	if(!effectRuntime) {
		pixelpart_gm::lastError = pixelpart_gm::invalidEffectRuntimeError;
		return -1;
	}

	try {
		const pixelpart::ParticleType& particleType =
			effectRuntime->effectAsset.effect().particleTypes().at(pixelpart::id_t(particleTypeId));

		return static_cast<pixelpart_gm::real>(particleType.rotationMode());
	}
	catch(const std::exception& e) {
		pixelpart_gm::lastError = std::string(e.what());
	}

	return -1;
}

GM_EXPORT pixelpart_gm::real GM_API pixelpart_particle_type_set_alignment_mode(pixelpart_gm::string runtimePtr, pixelpart_gm::real particleTypeId, pixelpart_gm::real mode) {
	pixelpart_gm::EffectRuntime* effectRuntime = pixelpart_gm::parsePtr<pixelpart_gm::EffectRuntime>(runtimePtr);
	if(!effectRuntime) {
		pixelpart_gm::lastError = pixelpart_gm::invalidEffectRuntimeError;
		return -1;
	}

	try {
		pixelpart::ParticleType& particleType =
			effectRuntime->effectAsset.effect().particleTypes().at(pixelpart::id_t(particleTypeId));

		particleType.alignmentMode(static_cast<pixelpart::AlignmentMode>(mode));

		return 1;
	}
	catch(const std::exception& e) {
		pixelpart_gm::lastError = std::string(e.what());
	}

	return -1;
}

GM_EXPORT pixelpart_gm::real GM_API pixelpart_particle_type_get_alignment_mode(pixelpart_gm::string runtimePtr, pixelpart_gm::real particleTypeId) {
	pixelpart_gm::EffectRuntime* effectRuntime = pixelpart_gm::parsePtr<pixelpart_gm::EffectRuntime>(runtimePtr);
	if(!effectRuntime) {
		pixelpart_gm::lastError = pixelpart_gm::invalidEffectRuntimeError;
		return -1;
	}

	try {
		const pixelpart::ParticleType& particleType =
			effectRuntime->effectAsset.effect().particleTypes().at(pixelpart::id_t(particleTypeId));

		return static_cast<pixelpart_gm::real>(particleType.alignmentMode());
	}
	catch(const std::exception& e) {
		pixelpart_gm::lastError = std::string(e.what());
	}

	return -1;
}

GM_EXPORT pixelpart_gm::const_string GM_API pixelpart_particle_type_get_pivot(pixelpart_gm::string runtimePtr, pixelpart_gm::real particleTypeId) {
	pixelpart_gm::EffectRuntime* effectRuntime = pixelpart_gm::parsePtr<pixelpart_gm::EffectRuntime>(runtimePtr);
	if(!effectRuntime) {
		pixelpart_gm::lastError = pixelpart_gm::invalidEffectRuntimeError;
		pixelpart_gm::particleTypePropertyPtrString = "";

		return pixelpart_gm::particleTypePropertyPtrString.c_str();
	}

	try {
		pixelpart::ParticleType& particleType =
			effectRuntime->effectAsset.effect().particleTypes().at(pixelpart::id_t(particleTypeId));

		pixelpart_gm::particleTypePropertyPtrString = pixelpart_gm::ptrToString(
			&particleType.pivot());
	}
	catch(const std::exception& e) {
		pixelpart_gm::lastError = std::string(e.what());
		pixelpart_gm::particleTypePropertyPtrString = "";
	}

	return pixelpart_gm::particleTypePropertyPtrString.c_str();
}

GM_EXPORT pixelpart_gm::const_string GM_API pixelpart_particle_type_get_motion_path_force(pixelpart_gm::string runtimePtr, pixelpart_gm::real particleTypeId) {
	pixelpart_gm::EffectRuntime* effectRuntime = pixelpart_gm::parsePtr<pixelpart_gm::EffectRuntime>(runtimePtr);
	if(!effectRuntime) {
		pixelpart_gm::lastError = pixelpart_gm::invalidEffectRuntimeError;
		pixelpart_gm::particleTypePropertyPtrString = "";

		return pixelpart_gm::particleTypePropertyPtrString.c_str();
	}

	try {
		pixelpart::ParticleType& particleType =
			effectRuntime->effectAsset.effect().particleTypes().at(pixelpart::id_t(particleTypeId));

		pixelpart_gm::particleTypePropertyPtrString = pixelpart_gm::ptrToString(
			&particleType.motionPathForce());
	}
	catch(const std::exception& e) {
		pixelpart_gm::lastError = std::string(e.what());
		pixelpart_gm::particleTypePropertyPtrString = "";
	}

	return pixelpart_gm::particleTypePropertyPtrString.c_str();
}

GM_EXPORT pixelpart_gm::real GM_API pixelpart_particle_type_set_visible(pixelpart_gm::string runtimePtr, pixelpart_gm::real particleTypeId, pixelpart_gm::real visible) {
	pixelpart_gm::EffectRuntime* effectRuntime = pixelpart_gm::parsePtr<pixelpart_gm::EffectRuntime>(runtimePtr);
	if(!effectRuntime) {
		pixelpart_gm::lastError = pixelpart_gm::invalidEffectRuntimeError;
		return -1;
	}

	try {
		pixelpart::ParticleType& particleType =
			effectRuntime->effectAsset.effect().particleTypes().at(pixelpart::id_t(particleTypeId));

		particleType.visible(visible);

		return 1;
	}
	catch(const std::exception& e) {
		pixelpart_gm::lastError = std::string(e.what());
	}

	return -1;
}

GM_EXPORT pixelpart_gm::real GM_API pixelpart_particle_type_is_visible(pixelpart_gm::string runtimePtr, pixelpart_gm::real particleTypeId) {
	pixelpart_gm::EffectRuntime* effectRuntime = pixelpart_gm::parsePtr<pixelpart_gm::EffectRuntime>(runtimePtr);
	if(!effectRuntime) {
		pixelpart_gm::lastError = pixelpart_gm::invalidEffectRuntimeError;
		return -1;
	}

	try {
		const pixelpart::ParticleType& particleType =
			effectRuntime->effectAsset.effect().particleTypes().at(pixelpart::id_t(particleTypeId));

		return particleType.visible() ? 1 : 0;
	}
	catch(const std::exception& e) {
		pixelpart_gm::lastError = std::string(e.what());
	}

	return -1;
}

GM_EXPORT pixelpart_gm::real GM_API pixelpart_particle_type_set_layer(pixelpart_gm::string runtimePtr, pixelpart_gm::real particleTypeId, pixelpart_gm::real layer) {
	pixelpart_gm::EffectRuntime* effectRuntime = pixelpart_gm::parsePtr<pixelpart_gm::EffectRuntime>(runtimePtr);
	if(!effectRuntime) {
		pixelpart_gm::lastError = pixelpart_gm::invalidEffectRuntimeError;
		return -1;
	}

	try {
		pixelpart::ParticleType& particleType =
			effectRuntime->effectAsset.effect().particleTypes().at(pixelpart::id_t(particleTypeId));

		particleType.layer(static_cast<std::uint32_t>(std::max(layer, static_cast<pixelpart_gm::real>(0))));

		return 1;
	}
	catch(const std::exception& e) {
		pixelpart_gm::lastError = std::string(e.what());
	}

	return -1;
}

GM_EXPORT pixelpart_gm::real GM_API pixelpart_particle_type_get_layer(pixelpart_gm::string runtimePtr, pixelpart_gm::real particleTypeId) {
	pixelpart_gm::EffectRuntime* effectRuntime = pixelpart_gm::parsePtr<pixelpart_gm::EffectRuntime>(runtimePtr);
	if(!effectRuntime) {
		pixelpart_gm::lastError = pixelpart_gm::invalidEffectRuntimeError;
		return -1;
	}

	try {
		const pixelpart::ParticleType& particleType =
			effectRuntime->effectAsset.effect().particleTypes().at(pixelpart::id_t(particleTypeId));

		return static_cast<pixelpart_gm::real>(particleType.layer());
	}
	catch(const std::exception& e) {
		pixelpart_gm::lastError = std::string(e.what());
	}

	return -1;
}

GM_EXPORT pixelpart_gm::const_string GM_API pixelpart_particle_type_get_material_id(pixelpart_gm::string runtimePtr, pixelpart_gm::real particleTypeId) {
	pixelpart_gm::EffectRuntime* effectRuntime = pixelpart_gm::parsePtr<pixelpart_gm::EffectRuntime>(runtimePtr);
	if(!effectRuntime) {
		pixelpart_gm::lastError = pixelpart_gm::invalidEffectRuntimeError;
		return "";
	}

	try {
		const pixelpart::ParticleType& particleType = effectRuntime->effectAsset.effect().particleTypes().at(pixelpart::id_t(particleTypeId));
		if(particleType.materialInstance().materialId().empty()) {
			return 0;
		}

		return particleType.materialInstance().materialId().c_str();
	}
	catch(const std::exception& e) {
		pixelpart_gm::lastError = std::string(e.what());
	}

	return "";
}

GM_EXPORT pixelpart_gm::real GM_API pixelpart_particle_type_is_material_builtin(pixelpart_gm::string runtimePtr, pixelpart_gm::real particleTypeId) {
	pixelpart_gm::EffectRuntime* effectRuntime = pixelpart_gm::parsePtr<pixelpart_gm::EffectRuntime>(runtimePtr);
	if(!effectRuntime) {
		pixelpart_gm::lastError = pixelpart_gm::invalidEffectRuntimeError;
		return -1;
	}

	try {
		const pixelpart::ParticleType& particleType =
			effectRuntime->effectAsset.effect().particleTypes().at(pixelpart::id_t(particleTypeId));

		return particleType.materialInstance().builtInMaterial() ? 1 : 0;
	}
	catch(const std::exception& e) {
		pixelpart_gm::lastError = std::string(e.what());
	}

	return -1;
}

GM_EXPORT pixelpart_gm::real GM_API pixelpart_particle_type_get_material_parameter_count(pixelpart_gm::string runtimePtr, pixelpart_gm::real particleTypeId) {
	pixelpart_gm::EffectRuntime* effectRuntime = pixelpart_gm::parsePtr<pixelpart_gm::EffectRuntime>(runtimePtr);
	if(!effectRuntime) {
		pixelpart_gm::lastError = pixelpart_gm::invalidEffectRuntimeError;
		return -1;
	}

	try {
		const pixelpart::ParticleType& particleType =
			effectRuntime->effectAsset.effect().particleTypes().at(pixelpart::id_t(particleTypeId));

		return static_cast<pixelpart_gm::real>(particleType.materialInstance().materialParameters().size());
	}
	catch(const std::exception& e) {
		pixelpart_gm::lastError = std::string(e.what());
	}

	return -1;
}

GM_EXPORT pixelpart_gm::real GM_API pixelpart_particle_type_get_material_parameter_ids(pixelpart_gm::string runtimePtr, pixelpart_gm::real particleTypeId, pixelpart_gm::string parameterIdBufferPtr) {
	pixelpart_gm::EffectRuntime* effectRuntime = pixelpart_gm::parsePtr<pixelpart_gm::EffectRuntime>(runtimePtr);
	if(!effectRuntime) {
		pixelpart_gm::lastError = pixelpart_gm::invalidEffectRuntimeError;
		return -1;
	}
	else if(!parameterIdBufferPtr) {
		pixelpart_gm::lastError = pixelpart_gm::invalidArgumentError;
		return -1;
	}

	try {
		const pixelpart::ParticleType& particleType =
			effectRuntime->effectAsset.effect().particleTypes().at(pixelpart::id_t(particleTypeId));

		pixelpart_gm::Buffer parameterIdBuffer(parameterIdBufferPtr);
		for(const auto& parameterEntry : particleType.materialInstance().materialParameters()) {
			parameterIdBuffer.write<std::uint32_t>(parameterEntry.first.value());
		}
	}
	catch(const std::exception& e) {
		pixelpart_gm::lastError = std::string(e.what());
	}

	return -1;
}

GM_EXPORT pixelpart_gm::real GM_API pixelpart_particle_type_get_material_parameter_type(pixelpart_gm::string runtimePtr, pixelpart_gm::real particleTypeId, pixelpart_gm::real parameterId) {
	pixelpart_gm::EffectRuntime* effectRuntime = pixelpart_gm::parsePtr<pixelpart_gm::EffectRuntime>(runtimePtr);
	if(!effectRuntime) {
		pixelpart_gm::lastError = pixelpart_gm::invalidEffectRuntimeError;
		return -1;
	}

	try {
		const pixelpart::ParticleType& particleType =
			effectRuntime->effectAsset.effect().particleTypes().at(pixelpart::id_t(particleTypeId));

		return static_cast<pixelpart_gm::real>(particleType.materialInstance().materialParameters().at(parameterId).type());
	}
	catch(const std::exception& e) {
		pixelpart_gm::lastError = std::string(e.what());
	}

	return -1;
}

GM_EXPORT pixelpart_gm::real GM_API pixelpart_particle_type_get_material_parameter_value(pixelpart_gm::string runtimePtr, pixelpart_gm::real particleTypeId, pixelpart_gm::real parameterId, pixelpart_gm::string resultBufferPtr) {
	pixelpart_gm::EffectRuntime* effectRuntime = pixelpart_gm::parsePtr<pixelpart_gm::EffectRuntime>(runtimePtr);
	if(!effectRuntime) {
		pixelpart_gm::lastError = pixelpart_gm::invalidEffectRuntimeError;
		return -1;
	}

	try {
		const pixelpart::ParticleType& particleType =
			effectRuntime->effectAsset.effect().particleTypes().at(pixelpart::id_t(particleTypeId));

		pixelpart_gm::Buffer resultBuffer(resultBufferPtr);

		const pixelpart::VariantParameter::Value& parameterValue =
			particleType.materialInstance().materialParameters().at(parameterId);

		switch(parameterValue.type()) {
			case pixelpart::VariantParameter::Value::Type::type_int:
				resultBuffer.write(static_cast<std::int32_t>(parameterValue.valueInt()));
				break;
			case pixelpart::VariantParameter::Value::Type::type_float:
				resultBuffer.write(parameterValue.valueFloat());
				break;
			case pixelpart::VariantParameter::Value::Type::type_float2:
				resultBuffer.write(parameterValue.valueFloat2());
				break;
			case pixelpart::VariantParameter::Value::Type::type_float3:
				resultBuffer.write(parameterValue.valueFloat3());
				break;
			case pixelpart::VariantParameter::Value::Type::type_float4:
				resultBuffer.write(parameterValue.valueFloat4());
				break;
			case pixelpart::VariantParameter::Value::Type::type_bool:
				resultBuffer.write(parameterValue.valueBool());
				break;
			case pixelpart::VariantParameter::Value::Type::type_enum:
				resultBuffer.write(parameterValue.valueEnum());
				break;
			case pixelpart::VariantParameter::Value::Type::type_color:
				resultBuffer.write(parameterValue.valueColor());
				break;
			case pixelpart::VariantParameter::Value::Type::type_resource_image:
				std::strncpy(resultBufferPtr, parameterValue.valueResourceId().c_str(), 2048);
				break;
			default:
				pixelpart_gm::lastError = "Unsupported parameter type";
				return -1;
		}

		return 1;
	}
	catch(const std::exception& e) {
		pixelpart_gm::lastError = std::string(e.what());
	}

	return -1;
}

GM_EXPORT pixelpart_gm::real GM_API pixelpart_particle_type_get_renderer(pixelpart_gm::string runtimePtr, pixelpart_gm::real particleTypeId) {
	pixelpart_gm::EffectRuntime* effectRuntime = pixelpart_gm::parsePtr<pixelpart_gm::EffectRuntime>(runtimePtr);
	if(!effectRuntime) {
		pixelpart_gm::lastError = pixelpart_gm::invalidEffectRuntimeError;
		return -1;
	}

	try {
		const pixelpart::ParticleType& particleType =
			effectRuntime->effectAsset.effect().particleTypes().at(pixelpart::id_t(particleTypeId));

		return static_cast<pixelpart_gm::real>(particleType.renderer());
	}
	catch(const std::exception& e) {
		pixelpart_gm::lastError = std::string(e.what());
	}

	return -1;
}

GM_EXPORT pixelpart_gm::const_string GM_API pixelpart_particle_type_get_mesh_renderer_mesh_resource_id(pixelpart_gm::string runtimePtr, pixelpart_gm::real particleTypeId) {
	pixelpart_gm::EffectRuntime* effectRuntime = pixelpart_gm::parsePtr<pixelpart_gm::EffectRuntime>(runtimePtr);
	if(!effectRuntime) {
		pixelpart_gm::lastError = pixelpart_gm::invalidEffectRuntimeError;
		return "";
	}

	try {
		const pixelpart::ParticleType& particleType =
			effectRuntime->effectAsset.effect().particleTypes().at(pixelpart::id_t(particleTypeId));

		return particleType.meshRendererSettings().meshResourceId.c_str();
	}
	catch(const std::exception& e) {
		pixelpart_gm::lastError = std::string(e.what());
	}

	return "";
}

GM_EXPORT pixelpart_gm::const_string GM_API pixelpart_particle_type_get_count(pixelpart_gm::string runtimePtr, pixelpart_gm::real particleTypeId) {
	pixelpart_gm::EffectRuntime* effectRuntime = pixelpart_gm::parsePtr<pixelpart_gm::EffectRuntime>(runtimePtr);
	if(!effectRuntime) {
		pixelpart_gm::lastError = pixelpart_gm::invalidEffectRuntimeError;
		pixelpart_gm::particleTypePropertyPtrString = "";

		return pixelpart_gm::particleTypePropertyPtrString.c_str();
	}

	try {
		pixelpart::ParticleType& particleType =
			effectRuntime->effectAsset.effect().particleTypes().at(pixelpart::id_t(particleTypeId));

		pixelpart_gm::particleTypePropertyPtrString = pixelpart_gm::ptrToString(
			&particleType.count());
	}
	catch(const std::exception& e) {
		pixelpart_gm::lastError = std::string(e.what());
		pixelpart_gm::particleTypePropertyPtrString = "";
	}

	return pixelpart_gm::particleTypePropertyPtrString.c_str();
}

GM_EXPORT pixelpart_gm::const_string GM_API pixelpart_particle_type_get_lifespan(pixelpart_gm::string runtimePtr, pixelpart_gm::real particleTypeId) {
	pixelpart_gm::EffectRuntime* effectRuntime = pixelpart_gm::parsePtr<pixelpart_gm::EffectRuntime>(runtimePtr);
	if(!effectRuntime) {
		pixelpart_gm::lastError = pixelpart_gm::invalidEffectRuntimeError;
		pixelpart_gm::particleTypePropertyPtrString = "";

		return pixelpart_gm::particleTypePropertyPtrString.c_str();
	}

	try {
		pixelpart::ParticleType& particleType =
			effectRuntime->effectAsset.effect().particleTypes().at(pixelpart::id_t(particleTypeId));

		pixelpart_gm::particleTypePropertyPtrString = pixelpart_gm::ptrToString(
			&particleType.lifespan());
	}
	catch(const std::exception& e) {
		pixelpart_gm::lastError = std::string(e.what());
		pixelpart_gm::particleTypePropertyPtrString = "";
	}

	return pixelpart_gm::particleTypePropertyPtrString.c_str();
}

GM_EXPORT pixelpart_gm::const_string GM_API pixelpart_particle_type_get_initial_size(pixelpart_gm::string runtimePtr, pixelpart_gm::real particleTypeId) {
	pixelpart_gm::EffectRuntime* effectRuntime = pixelpart_gm::parsePtr<pixelpart_gm::EffectRuntime>(runtimePtr);
	if(!effectRuntime) {
		pixelpart_gm::lastError = pixelpart_gm::invalidEffectRuntimeError;
		pixelpart_gm::particleTypePropertyPtrString = "";

		return pixelpart_gm::particleTypePropertyPtrString.c_str();
	}

	try {
		pixelpart::ParticleType& particleType =
			effectRuntime->effectAsset.effect().particleTypes().at(pixelpart::id_t(particleTypeId));

		pixelpart_gm::particleTypePropertyPtrString = pixelpart_gm::ptrToString(
			&particleType.initialSize());
	}
	catch(const std::exception& e) {
		pixelpart_gm::lastError = std::string(e.what());
		pixelpart_gm::particleTypePropertyPtrString = "";
	}

	return pixelpart_gm::particleTypePropertyPtrString.c_str();
}

GM_EXPORT pixelpart_gm::const_string GM_API pixelpart_particle_type_get_initial_rotation(pixelpart_gm::string runtimePtr, pixelpart_gm::real particleTypeId) {
	pixelpart_gm::EffectRuntime* effectRuntime = pixelpart_gm::parsePtr<pixelpart_gm::EffectRuntime>(runtimePtr);
	if(!effectRuntime) {
		pixelpart_gm::lastError = pixelpart_gm::invalidEffectRuntimeError;
		pixelpart_gm::particleTypePropertyPtrString = "";

		return pixelpart_gm::particleTypePropertyPtrString.c_str();
	}

	try {
		pixelpart::ParticleType& particleType =
			effectRuntime->effectAsset.effect().particleTypes().at(pixelpart::id_t(particleTypeId));

		pixelpart_gm::particleTypePropertyPtrString = pixelpart_gm::ptrToString(
			&particleType.initialRotation());
	}
	catch(const std::exception& e) {
		pixelpart_gm::lastError = std::string(e.what());
		pixelpart_gm::particleTypePropertyPtrString = "";
	}

	return pixelpart_gm::particleTypePropertyPtrString.c_str();
}

GM_EXPORT pixelpart_gm::const_string GM_API pixelpart_particle_type_get_initial_velocity(pixelpart_gm::string runtimePtr, pixelpart_gm::real particleTypeId) {
	pixelpart_gm::EffectRuntime* effectRuntime = pixelpart_gm::parsePtr<pixelpart_gm::EffectRuntime>(runtimePtr);
	if(!effectRuntime) {
		pixelpart_gm::lastError = pixelpart_gm::invalidEffectRuntimeError;
		pixelpart_gm::particleTypePropertyPtrString = "";

		return pixelpart_gm::particleTypePropertyPtrString.c_str();
	}

	try {
		pixelpart::ParticleType& particleType =
			effectRuntime->effectAsset.effect().particleTypes().at(pixelpart::id_t(particleTypeId));

		pixelpart_gm::particleTypePropertyPtrString = pixelpart_gm::ptrToString(
			&particleType.initialVelocity());
	}
	catch(const std::exception& e) {
		pixelpart_gm::lastError = std::string(e.what());
		pixelpart_gm::particleTypePropertyPtrString = "";
	}

	return pixelpart_gm::particleTypePropertyPtrString.c_str();
}

GM_EXPORT pixelpart_gm::const_string GM_API pixelpart_particle_type_get_inherited_velocity(pixelpart_gm::string runtimePtr, pixelpart_gm::real particleTypeId) {
	pixelpart_gm::EffectRuntime* effectRuntime = pixelpart_gm::parsePtr<pixelpart_gm::EffectRuntime>(runtimePtr);
	if(!effectRuntime) {
		pixelpart_gm::lastError = pixelpart_gm::invalidEffectRuntimeError;
		pixelpart_gm::particleTypePropertyPtrString = "";

		return pixelpart_gm::particleTypePropertyPtrString.c_str();
	}

	try {
		pixelpart::ParticleType& particleType =
			effectRuntime->effectAsset.effect().particleTypes().at(pixelpart::id_t(particleTypeId));

		pixelpart_gm::particleTypePropertyPtrString = pixelpart_gm::ptrToString(
			&particleType.inheritedVelocity());
	}
	catch(const std::exception& e) {
		pixelpart_gm::lastError = std::string(e.what());
		pixelpart_gm::particleTypePropertyPtrString = "";
	}

	return pixelpart_gm::particleTypePropertyPtrString.c_str();
}

GM_EXPORT pixelpart_gm::const_string GM_API pixelpart_particle_type_get_initial_opacity(pixelpart_gm::string runtimePtr, pixelpart_gm::real particleTypeId) {
	pixelpart_gm::EffectRuntime* effectRuntime = pixelpart_gm::parsePtr<pixelpart_gm::EffectRuntime>(runtimePtr);
	if(!effectRuntime) {
		pixelpart_gm::lastError = pixelpart_gm::invalidEffectRuntimeError;
		pixelpart_gm::particleTypePropertyPtrString = "";

		return pixelpart_gm::particleTypePropertyPtrString.c_str();
	}

	try {
		pixelpart::ParticleType& particleType =
			effectRuntime->effectAsset.effect().particleTypes().at(pixelpart::id_t(particleTypeId));

		pixelpart_gm::particleTypePropertyPtrString = pixelpart_gm::ptrToString(
			&particleType.initialOpacity());
	}
	catch(const std::exception& e) {
		pixelpart_gm::lastError = std::string(e.what());
		pixelpart_gm::particleTypePropertyPtrString = "";
	}

	return pixelpart_gm::particleTypePropertyPtrString.c_str();
}

GM_EXPORT pixelpart_gm::const_string GM_API pixelpart_particle_type_get_motion_path(pixelpart_gm::string runtimePtr, pixelpart_gm::real particleTypeId) {
	pixelpart_gm::EffectRuntime* effectRuntime = pixelpart_gm::parsePtr<pixelpart_gm::EffectRuntime>(runtimePtr);
	if(!effectRuntime) {
		pixelpart_gm::lastError = pixelpart_gm::invalidEffectRuntimeError;
		pixelpart_gm::particleTypePropertyPtrString = "";

		return pixelpart_gm::particleTypePropertyPtrString.c_str();
	}

	try {
		pixelpart::ParticleType& particleType =
			effectRuntime->effectAsset.effect().particleTypes().at(pixelpart::id_t(particleTypeId));

		pixelpart_gm::particleTypePropertyPtrString = pixelpart_gm::ptrToString(
			&particleType.motionPath());
	}
	catch(const std::exception& e) {
		pixelpart_gm::lastError = std::string(e.what());
		pixelpart_gm::particleTypePropertyPtrString = "";
	}

	return pixelpart_gm::particleTypePropertyPtrString.c_str();
}

GM_EXPORT pixelpart_gm::const_string GM_API pixelpart_particle_type_get_size(pixelpart_gm::string runtimePtr, pixelpart_gm::real particleTypeId) {
	pixelpart_gm::EffectRuntime* effectRuntime = pixelpart_gm::parsePtr<pixelpart_gm::EffectRuntime>(runtimePtr);
	if(!effectRuntime) {
		pixelpart_gm::lastError = pixelpart_gm::invalidEffectRuntimeError;
		pixelpart_gm::particleTypePropertyPtrString = "";

		return pixelpart_gm::particleTypePropertyPtrString.c_str();
	}

	try {
		pixelpart::ParticleType& particleType =
			effectRuntime->effectAsset.effect().particleTypes().at(pixelpart::id_t(particleTypeId));

		pixelpart_gm::particleTypePropertyPtrString = pixelpart_gm::ptrToString(
			&particleType.size());
	}
	catch(const std::exception& e) {
		pixelpart_gm::lastError = std::string(e.what());
		pixelpart_gm::particleTypePropertyPtrString = "";
	}

	return pixelpart_gm::particleTypePropertyPtrString.c_str();
}

GM_EXPORT pixelpart_gm::const_string GM_API pixelpart_particle_type_get_stretch(pixelpart_gm::string runtimePtr, pixelpart_gm::real particleTypeId) {
	pixelpart_gm::EffectRuntime* effectRuntime = pixelpart_gm::parsePtr<pixelpart_gm::EffectRuntime>(runtimePtr);
	if(!effectRuntime) {
		pixelpart_gm::lastError = pixelpart_gm::invalidEffectRuntimeError;
		pixelpart_gm::particleTypePropertyPtrString = "";

		return pixelpart_gm::particleTypePropertyPtrString.c_str();
	}

	try {
		pixelpart::ParticleType& particleType =
			effectRuntime->effectAsset.effect().particleTypes().at(pixelpart::id_t(particleTypeId));

		pixelpart_gm::particleTypePropertyPtrString = pixelpart_gm::ptrToString(
			&particleType.stretch());
	}
	catch(const std::exception& e) {
		pixelpart_gm::lastError = std::string(e.what());
		pixelpart_gm::particleTypePropertyPtrString = "";
	}

	return pixelpart_gm::particleTypePropertyPtrString.c_str();
}

GM_EXPORT pixelpart_gm::const_string GM_API pixelpart_particle_type_get_physical_size(pixelpart_gm::string runtimePtr, pixelpart_gm::real particleTypeId) {
	pixelpart_gm::EffectRuntime* effectRuntime = pixelpart_gm::parsePtr<pixelpart_gm::EffectRuntime>(runtimePtr);
	if(!effectRuntime) {
		pixelpart_gm::lastError = pixelpart_gm::invalidEffectRuntimeError;
		pixelpart_gm::particleTypePropertyPtrString = "";

		return pixelpart_gm::particleTypePropertyPtrString.c_str();
	}

	try {
		pixelpart::ParticleType& particleType =
			effectRuntime->effectAsset.effect().particleTypes().at(pixelpart::id_t(particleTypeId));

		pixelpart_gm::particleTypePropertyPtrString = pixelpart_gm::ptrToString(
			&particleType.physicalSize());
	}
	catch(const std::exception& e) {
		pixelpart_gm::lastError = std::string(e.what());
		pixelpart_gm::particleTypePropertyPtrString = "";
	}

	return pixelpart_gm::particleTypePropertyPtrString.c_str();
}

GM_EXPORT pixelpart_gm::const_string GM_API pixelpart_particle_type_get_rotation(pixelpart_gm::string runtimePtr, pixelpart_gm::real particleTypeId) {
	pixelpart_gm::EffectRuntime* effectRuntime = pixelpart_gm::parsePtr<pixelpart_gm::EffectRuntime>(runtimePtr);
	if(!effectRuntime) {
		pixelpart_gm::lastError = pixelpart_gm::invalidEffectRuntimeError;
		pixelpart_gm::particleTypePropertyPtrString = "";

		return pixelpart_gm::particleTypePropertyPtrString.c_str();
	}

	try {
		pixelpart::ParticleType& particleType =
			effectRuntime->effectAsset.effect().particleTypes().at(pixelpart::id_t(particleTypeId));

		pixelpart_gm::particleTypePropertyPtrString = pixelpart_gm::ptrToString(
			&particleType.rotation());
	}
	catch(const std::exception& e) {
		pixelpart_gm::lastError = std::string(e.what());
		pixelpart_gm::particleTypePropertyPtrString = "";
	}

	return pixelpart_gm::particleTypePropertyPtrString.c_str();
}

GM_EXPORT pixelpart_gm::const_string GM_API pixelpart_particle_type_get_rotation_by_speed(pixelpart_gm::string runtimePtr, pixelpart_gm::real particleTypeId) {
	pixelpart_gm::EffectRuntime* effectRuntime = pixelpart_gm::parsePtr<pixelpart_gm::EffectRuntime>(runtimePtr);
	if(!effectRuntime) {
		pixelpart_gm::lastError = pixelpart_gm::invalidEffectRuntimeError;
		pixelpart_gm::particleTypePropertyPtrString = "";

		return pixelpart_gm::particleTypePropertyPtrString.c_str();
	}

	try {
		pixelpart::ParticleType& particleType =
			effectRuntime->effectAsset.effect().particleTypes().at(pixelpart::id_t(particleTypeId));

		pixelpart_gm::particleTypePropertyPtrString = pixelpart_gm::ptrToString(
			&particleType.rotationBySpeed());
	}
	catch(const std::exception& e) {
		pixelpart_gm::lastError = std::string(e.what());
		pixelpart_gm::particleTypePropertyPtrString = "";
	}

	return pixelpart_gm::particleTypePropertyPtrString.c_str();
}

GM_EXPORT pixelpart_gm::const_string GM_API pixelpart_particle_type_get_acceleration(pixelpart_gm::string runtimePtr, pixelpart_gm::real particleTypeId) {
	pixelpart_gm::EffectRuntime* effectRuntime = pixelpart_gm::parsePtr<pixelpart_gm::EffectRuntime>(runtimePtr);
	if(!effectRuntime) {
		pixelpart_gm::lastError = pixelpart_gm::invalidEffectRuntimeError;
		pixelpart_gm::particleTypePropertyPtrString = "";

		return pixelpart_gm::particleTypePropertyPtrString.c_str();
	}

	try {
		pixelpart::ParticleType& particleType =
			effectRuntime->effectAsset.effect().particleTypes().at(pixelpart::id_t(particleTypeId));

		pixelpart_gm::particleTypePropertyPtrString = pixelpart_gm::ptrToString(
			&particleType.acceleration());
	}
	catch(const std::exception& e) {
		pixelpart_gm::lastError = std::string(e.what());
		pixelpart_gm::particleTypePropertyPtrString = "";
	}

	return pixelpart_gm::particleTypePropertyPtrString.c_str();
}

GM_EXPORT pixelpart_gm::const_string GM_API pixelpart_particle_type_get_radial_acceleration(pixelpart_gm::string runtimePtr, pixelpart_gm::real particleTypeId) {
	pixelpart_gm::EffectRuntime* effectRuntime = pixelpart_gm::parsePtr<pixelpart_gm::EffectRuntime>(runtimePtr);
	if(!effectRuntime) {
		pixelpart_gm::lastError = pixelpart_gm::invalidEffectRuntimeError;
		pixelpart_gm::particleTypePropertyPtrString = "";

		return pixelpart_gm::particleTypePropertyPtrString.c_str();
	}

	try {
		pixelpart::ParticleType& particleType =
			effectRuntime->effectAsset.effect().particleTypes().at(pixelpart::id_t(particleTypeId));

		pixelpart_gm::particleTypePropertyPtrString = pixelpart_gm::ptrToString(
			&particleType.radialAcceleration());
	}
	catch(const std::exception& e) {
		pixelpart_gm::lastError = std::string(e.what());
		pixelpart_gm::particleTypePropertyPtrString = "";
	}

	return pixelpart_gm::particleTypePropertyPtrString.c_str();
}

GM_EXPORT pixelpart_gm::const_string GM_API pixelpart_particle_type_get_weight(pixelpart_gm::string runtimePtr, pixelpart_gm::real particleTypeId) {
	pixelpart_gm::EffectRuntime* effectRuntime = pixelpart_gm::parsePtr<pixelpart_gm::EffectRuntime>(runtimePtr);
	if(!effectRuntime) {
		pixelpart_gm::lastError = pixelpart_gm::invalidEffectRuntimeError;
		pixelpart_gm::particleTypePropertyPtrString = "";

		return pixelpart_gm::particleTypePropertyPtrString.c_str();
	}

	try {
		pixelpart::ParticleType& particleType =
			effectRuntime->effectAsset.effect().particleTypes().at(pixelpart::id_t(particleTypeId));

		pixelpart_gm::particleTypePropertyPtrString = pixelpart_gm::ptrToString(
			&particleType.weight());
	}
	catch(const std::exception& e) {
		pixelpart_gm::lastError = std::string(e.what());
		pixelpart_gm::particleTypePropertyPtrString = "";
	}

	return pixelpart_gm::particleTypePropertyPtrString.c_str();
}

GM_EXPORT pixelpart_gm::const_string GM_API pixelpart_particle_type_get_bounce(pixelpart_gm::string runtimePtr, pixelpart_gm::real particleTypeId) {
	pixelpart_gm::EffectRuntime* effectRuntime = pixelpart_gm::parsePtr<pixelpart_gm::EffectRuntime>(runtimePtr);
	if(!effectRuntime) {
		pixelpart_gm::lastError = pixelpart_gm::invalidEffectRuntimeError;
		pixelpart_gm::particleTypePropertyPtrString = "";

		return pixelpart_gm::particleTypePropertyPtrString.c_str();
	}

	try {
		pixelpart::ParticleType& particleType =
			effectRuntime->effectAsset.effect().particleTypes().at(pixelpart::id_t(particleTypeId));

		pixelpart_gm::particleTypePropertyPtrString = pixelpart_gm::ptrToString(
			&particleType.bounce());
	}
	catch(const std::exception& e) {
		pixelpart_gm::lastError = std::string(e.what());
		pixelpart_gm::particleTypePropertyPtrString = "";
	}

	return pixelpart_gm::particleTypePropertyPtrString.c_str();
}

GM_EXPORT pixelpart_gm::const_string GM_API pixelpart_particle_type_get_friction(pixelpart_gm::string runtimePtr, pixelpart_gm::real particleTypeId) {
	pixelpart_gm::EffectRuntime* effectRuntime = pixelpart_gm::parsePtr<pixelpart_gm::EffectRuntime>(runtimePtr);
	if(!effectRuntime) {
		pixelpart_gm::lastError = pixelpart_gm::invalidEffectRuntimeError;
		pixelpart_gm::particleTypePropertyPtrString = "";

		return pixelpart_gm::particleTypePropertyPtrString.c_str();
	}

	try {
		pixelpart::ParticleType& particleType =
			effectRuntime->effectAsset.effect().particleTypes().at(pixelpart::id_t(particleTypeId));

		pixelpart_gm::particleTypePropertyPtrString = pixelpart_gm::ptrToString(
			&particleType.friction());
	}
	catch(const std::exception& e) {
		pixelpart_gm::lastError = std::string(e.what());
		pixelpart_gm::particleTypePropertyPtrString = "";
	}

	return pixelpart_gm::particleTypePropertyPtrString.c_str();
}

GM_EXPORT pixelpart_gm::const_string GM_API pixelpart_particle_type_get_color(pixelpart_gm::string runtimePtr, pixelpart_gm::real particleTypeId) {
	pixelpart_gm::EffectRuntime* effectRuntime = pixelpart_gm::parsePtr<pixelpart_gm::EffectRuntime>(runtimePtr);
	if(!effectRuntime) {
		pixelpart_gm::lastError = pixelpart_gm::invalidEffectRuntimeError;
		pixelpart_gm::particleTypePropertyPtrString = "";

		return pixelpart_gm::particleTypePropertyPtrString.c_str();
	}

	try {
		pixelpart::ParticleType& particleType =
			effectRuntime->effectAsset.effect().particleTypes().at(pixelpart::id_t(particleTypeId));

		pixelpart_gm::particleTypePropertyPtrString = pixelpart_gm::ptrToString(
			&particleType.color());
	}
	catch(const std::exception& e) {
		pixelpart_gm::lastError = std::string(e.what());
		pixelpart_gm::particleTypePropertyPtrString = "";
	}

	return pixelpart_gm::particleTypePropertyPtrString.c_str();
}

GM_EXPORT pixelpart_gm::const_string GM_API pixelpart_particle_type_get_opacity(pixelpart_gm::string runtimePtr, pixelpart_gm::real particleTypeId) {
	pixelpart_gm::EffectRuntime* effectRuntime = pixelpart_gm::parsePtr<pixelpart_gm::EffectRuntime>(runtimePtr);
	if(!effectRuntime) {
		pixelpart_gm::lastError = pixelpart_gm::invalidEffectRuntimeError;
		pixelpart_gm::particleTypePropertyPtrString = "";

		return pixelpart_gm::particleTypePropertyPtrString.c_str();
	}

	try {
		pixelpart::ParticleType& particleType =
			effectRuntime->effectAsset.effect().particleTypes().at(pixelpart::id_t(particleTypeId));

		pixelpart_gm::particleTypePropertyPtrString = pixelpart_gm::ptrToString(
			&particleType.opacity());
	}
	catch(const std::exception& e) {
		pixelpart_gm::lastError = std::string(e.what());
		pixelpart_gm::particleTypePropertyPtrString = "";
	}

	return pixelpart_gm::particleTypePropertyPtrString.c_str();
}

GM_EXPORT pixelpart_gm::const_string GM_API pixelpart_particle_type_get_lifespan_variance(pixelpart_gm::string runtimePtr, pixelpart_gm::real particleTypeId) {
	pixelpart_gm::EffectRuntime* effectRuntime = pixelpart_gm::parsePtr<pixelpart_gm::EffectRuntime>(runtimePtr);
	if(!effectRuntime) {
		pixelpart_gm::lastError = pixelpart_gm::invalidEffectRuntimeError;
		pixelpart_gm::particleTypePropertyPtrString = "";

		return pixelpart_gm::particleTypePropertyPtrString.c_str();
	}

	try {
		pixelpart::ParticleType& particleType =
			effectRuntime->effectAsset.effect().particleTypes().at(pixelpart::id_t(particleTypeId));

		pixelpart_gm::particleTypePropertyPtrString = pixelpart_gm::ptrToString(
			&particleType.lifespanVariance());
	}
	catch(const std::exception& e) {
		pixelpart_gm::lastError = std::string(e.what());
		pixelpart_gm::particleTypePropertyPtrString = "";
	}

	return pixelpart_gm::particleTypePropertyPtrString.c_str();
}

GM_EXPORT pixelpart_gm::const_string GM_API pixelpart_particle_type_get_size_variance(pixelpart_gm::string runtimePtr, pixelpart_gm::real particleTypeId) {
	pixelpart_gm::EffectRuntime* effectRuntime = pixelpart_gm::parsePtr<pixelpart_gm::EffectRuntime>(runtimePtr);
	if(!effectRuntime) {
		pixelpart_gm::lastError = pixelpart_gm::invalidEffectRuntimeError;
		pixelpart_gm::particleTypePropertyPtrString = "";

		return pixelpart_gm::particleTypePropertyPtrString.c_str();
	}

	try {
		pixelpart::ParticleType& particleType =
			effectRuntime->effectAsset.effect().particleTypes().at(pixelpart::id_t(particleTypeId));

		pixelpart_gm::particleTypePropertyPtrString = pixelpart_gm::ptrToString(
			&particleType.sizeVariance());
	}
	catch(const std::exception& e) {
		pixelpart_gm::lastError = std::string(e.what());
		pixelpart_gm::particleTypePropertyPtrString = "";
	}

	return pixelpart_gm::particleTypePropertyPtrString.c_str();
}

GM_EXPORT pixelpart_gm::const_string GM_API pixelpart_particle_type_get_rotation_variance(pixelpart_gm::string runtimePtr, pixelpart_gm::real particleTypeId) {
	pixelpart_gm::EffectRuntime* effectRuntime = pixelpart_gm::parsePtr<pixelpart_gm::EffectRuntime>(runtimePtr);
	if(!effectRuntime) {
		pixelpart_gm::lastError = pixelpart_gm::invalidEffectRuntimeError;
		pixelpart_gm::particleTypePropertyPtrString = "";

		return pixelpart_gm::particleTypePropertyPtrString.c_str();
	}

	try {
		pixelpart::ParticleType& particleType =
			effectRuntime->effectAsset.effect().particleTypes().at(pixelpart::id_t(particleTypeId));

		pixelpart_gm::particleTypePropertyPtrString = pixelpart_gm::ptrToString(
			&particleType.rotationVariance());
	}
	catch(const std::exception& e) {
		pixelpart_gm::lastError = std::string(e.what());
		pixelpart_gm::particleTypePropertyPtrString = "";
	}

	return pixelpart_gm::particleTypePropertyPtrString.c_str();
}

GM_EXPORT pixelpart_gm::const_string GM_API pixelpart_particle_type_get_angular_velocity_variance(pixelpart_gm::string runtimePtr, pixelpart_gm::real particleTypeId) {
	pixelpart_gm::EffectRuntime* effectRuntime = pixelpart_gm::parsePtr<pixelpart_gm::EffectRuntime>(runtimePtr);
	if(!effectRuntime) {
		pixelpart_gm::lastError = pixelpart_gm::invalidEffectRuntimeError;
		pixelpart_gm::particleTypePropertyPtrString = "";

		return pixelpart_gm::particleTypePropertyPtrString.c_str();
	}

	try {
		pixelpart::ParticleType& particleType =
			effectRuntime->effectAsset.effect().particleTypes().at(pixelpart::id_t(particleTypeId));

		pixelpart_gm::particleTypePropertyPtrString = pixelpart_gm::ptrToString(
			&particleType.angularVelocityVariance());
	}
	catch(const std::exception& e) {
		pixelpart_gm::lastError = std::string(e.what());
		pixelpart_gm::particleTypePropertyPtrString = "";
	}

	return pixelpart_gm::particleTypePropertyPtrString.c_str();
}

GM_EXPORT pixelpart_gm::const_string GM_API pixelpart_particle_type_get_velocity_variance(pixelpart_gm::string runtimePtr, pixelpart_gm::real particleTypeId) {
	pixelpart_gm::EffectRuntime* effectRuntime = pixelpart_gm::parsePtr<pixelpart_gm::EffectRuntime>(runtimePtr);
	if(!effectRuntime) {
		pixelpart_gm::lastError = pixelpart_gm::invalidEffectRuntimeError;
		pixelpart_gm::particleTypePropertyPtrString = "";

		return pixelpart_gm::particleTypePropertyPtrString.c_str();
	}

	try {
		pixelpart::ParticleType& particleType =
			effectRuntime->effectAsset.effect().particleTypes().at(pixelpart::id_t(particleTypeId));

		pixelpart_gm::particleTypePropertyPtrString = pixelpart_gm::ptrToString(
			&particleType.velocityVariance());
	}
	catch(const std::exception& e) {
		pixelpart_gm::lastError = std::string(e.what());
		pixelpart_gm::particleTypePropertyPtrString = "";
	}

	return pixelpart_gm::particleTypePropertyPtrString.c_str();
}

GM_EXPORT pixelpart_gm::const_string GM_API pixelpart_particle_type_get_color_variance(pixelpart_gm::string runtimePtr, pixelpart_gm::real particleTypeId) {
	pixelpart_gm::EffectRuntime* effectRuntime = pixelpart_gm::parsePtr<pixelpart_gm::EffectRuntime>(runtimePtr);
	if(!effectRuntime) {
		pixelpart_gm::lastError = pixelpart_gm::invalidEffectRuntimeError;
		pixelpart_gm::particleTypePropertyPtrString = "";

		return pixelpart_gm::particleTypePropertyPtrString.c_str();
	}

	try {
		pixelpart::ParticleType& particleType =
			effectRuntime->effectAsset.effect().particleTypes().at(pixelpart::id_t(particleTypeId));

		pixelpart_gm::particleTypePropertyPtrString = pixelpart_gm::ptrToString(
			&particleType.colorVariance());
	}
	catch(const std::exception& e) {
		pixelpart_gm::lastError = std::string(e.what());
		pixelpart_gm::particleTypePropertyPtrString = "";
	}

	return pixelpart_gm::particleTypePropertyPtrString.c_str();
}

GM_EXPORT pixelpart_gm::const_string GM_API pixelpart_particle_type_get_opacity_variance(pixelpart_gm::string runtimePtr, pixelpart_gm::real particleTypeId) {
	pixelpart_gm::EffectRuntime* effectRuntime = pixelpart_gm::parsePtr<pixelpart_gm::EffectRuntime>(runtimePtr);
	if(!effectRuntime) {
		pixelpart_gm::lastError = pixelpart_gm::invalidEffectRuntimeError;
		pixelpart_gm::particleTypePropertyPtrString = "";

		return pixelpart_gm::particleTypePropertyPtrString.c_str();
	}

	try {
		pixelpart::ParticleType& particleType =
			effectRuntime->effectAsset.effect().particleTypes().at(pixelpart::id_t(particleTypeId));

		pixelpart_gm::particleTypePropertyPtrString = pixelpart_gm::ptrToString(
			&particleType.opacityVariance());
	}
	catch(const std::exception& e) {
		pixelpart_gm::lastError = std::string(e.what());
		pixelpart_gm::particleTypePropertyPtrString = "";
	}

	return pixelpart_gm::particleTypePropertyPtrString.c_str();
}
}
