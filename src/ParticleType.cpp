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

namespace pixelpart_gms2 {
std::string particleTypePropertyPtrString = "";
}

extern "C" {
GMS2_EXPORT pixelpart_gms2::real GMS2_API pixelpart_find_particle_type(pixelpart_gms2::string runtimePtr, pixelpart_gms2::string bufferPtr) {
	pixelpart_gms2::EffectRuntime* effectRuntime = reinterpret_cast<pixelpart_gms2::EffectRuntime*>(runtimePtr);
	if(!effectRuntime) {
		pixelpart_gms2::lastError = pixelpart_gms2::invalidEffectRuntimeError;
		return -1;
	}

	std::string name(bufferPtr);
	for(const auto& particleType : effectRuntime->effectAsset.effect().particleTypes()) {
		if(particleType.name() == name) {
			return particleType.id().value();
		}
	}

	return -1;
}

GMS2_EXPORT pixelpart_gms2::real GMS2_API pixelpart_find_particle_type_by_index(pixelpart_gms2::string runtimePtr, pixelpart_gms2::real particleTypeIndex) {
	pixelpart_gms2::EffectRuntime* effectRuntime = reinterpret_cast<pixelpart_gms2::EffectRuntime*>(runtimePtr);
	if(!effectRuntime) {
		pixelpart_gms2::lastError = pixelpart_gms2::invalidEffectRuntimeError;
		return -1;
	}
	else if(particleTypeIndex < 0 || particleTypeIndex >= effectRuntime->effectAsset.effect().particleTypes().count()) {
		pixelpart_gms2::lastError = pixelpart_gms2::invalidArgumentError;
		return -1;
	}

	return effectRuntime->effectAsset.effect().particleTypes().atIndex(static_cast<std::uint32_t>(particleTypeIndex)).id().value();
}

GMS2_EXPORT pixelpart_gms2::real GMS2_API pixelpart_particle_type_exists(pixelpart_gms2::string runtimePtr, pixelpart_gms2::real particleTypeId) {
	pixelpart_gms2::EffectRuntime* effectRuntime = reinterpret_cast<pixelpart_gms2::EffectRuntime*>(runtimePtr);
	if(!effectRuntime) {
		pixelpart_gms2::lastError = pixelpart_gms2::invalidEffectRuntimeError;
		return -1;
	}

	return effectRuntime->effectAsset.effect().particleTypes().contains(pixelpart::id_t(particleTypeId)) ? 1 : 0;
}

GMS2_EXPORT pixelpart_gms2::real GMS2_API pixelpart_particle_type_get_index(pixelpart_gms2::string runtimePtr, pixelpart_gms2::real particleTypeId) {
	pixelpart_gms2::EffectRuntime* effectRuntime = reinterpret_cast<pixelpart_gms2::EffectRuntime*>(runtimePtr);
	if(!effectRuntime) {
		pixelpart_gms2::lastError = pixelpart_gms2::invalidEffectRuntimeError;
		return -1;
	}

	std::uint32_t particleTypeIndex = effectRuntime->effectAsset.effect().particleTypes().indexOf(pixelpart::id_t(particleTypeId));
	if(particleTypeIndex == pixelpart::id_t::nullValue) {
		return -1;
	}

	return static_cast<pixelpart_gms2::real>(particleTypeIndex);
}

GMS2_EXPORT pixelpart_gms2::real GMS2_API pixelpart_particle_type_get_parent_id(pixelpart_gms2::string runtimePtr, pixelpart_gms2::real particleTypeId) {
	pixelpart_gms2::EffectRuntime* effectRuntime = reinterpret_cast<pixelpart_gms2::EffectRuntime*>(runtimePtr);
	if(!effectRuntime) {
		pixelpart_gms2::lastError = pixelpart_gms2::invalidEffectRuntimeError;
		return -1;
	}

	try {
		const pixelpart::ParticleType& particleType =
			effectRuntime->effectAsset.effect().particleTypes().at(pixelpart::id_t(particleTypeId));

		return particleType.parentId().value();
	}
	catch(const std::exception& e) {
		pixelpart_gms2::lastError = std::string(e.what());
	}

	return -1;
}

GMS2_EXPORT pixelpart_gms2::const_string GMS2_API pixelpart_particle_type_get_name(pixelpart_gms2::string runtimePtr, pixelpart_gms2::real particleTypeId) {
	pixelpart_gms2::EffectRuntime* effectRuntime = reinterpret_cast<pixelpart_gms2::EffectRuntime*>(runtimePtr);
	if(!effectRuntime) {
		pixelpart_gms2::lastError = pixelpart_gms2::invalidEffectRuntimeError;
		return "";
	}

	try {
		const pixelpart::ParticleType& particleType =
			effectRuntime->effectAsset.effect().particleTypes().at(pixelpart::id_t(particleTypeId));

		return particleType.name().c_str();
	}
	catch(const std::exception& e) {
		pixelpart_gms2::lastError = std::string(e.what());
	}

	return "";
}

GMS2_EXPORT pixelpart_gms2::real GMS2_API pixelpart_particle_type_set_position_relative(pixelpart_gms2::string runtimePtr, pixelpart_gms2::real particleTypeId, pixelpart_gms2::real relative) {
	pixelpart_gms2::EffectRuntime* effectRuntime = reinterpret_cast<pixelpart_gms2::EffectRuntime*>(runtimePtr);
	if(!effectRuntime) {
		pixelpart_gms2::lastError = pixelpart_gms2::invalidEffectRuntimeError;
		return -1;
	}

	try {
		pixelpart::ParticleType& particleType =
			effectRuntime->effectAsset.effect().particleTypes().at(pixelpart::id_t(particleTypeId));

		particleType.positionRelative(relative > 0.5);

		return 1;
	}
	catch(const std::exception& e) {
		pixelpart_gms2::lastError = std::string(e.what());
	}

	return -1;
}

GMS2_EXPORT pixelpart_gms2::real GMS2_API pixelpart_particle_type_is_position_relative(pixelpart_gms2::string runtimePtr, pixelpart_gms2::real particleTypeId) {
	pixelpart_gms2::EffectRuntime* effectRuntime = reinterpret_cast<pixelpart_gms2::EffectRuntime*>(runtimePtr);
	if(!effectRuntime) {
		pixelpart_gms2::lastError = pixelpart_gms2::invalidEffectRuntimeError;
		return -1;
	}

	try {
		const pixelpart::ParticleType& particleType =
			effectRuntime->effectAsset.effect().particleTypes().at(pixelpart::id_t(particleTypeId));

		return particleType.positionRelative() ? 1 : 0;
	}
	catch(const std::exception& e) {
		pixelpart_gms2::lastError = std::string(e.what());
	}

	return -1;
}

GMS2_EXPORT pixelpart_gms2::real GMS2_API pixelpart_particle_type_set_rotation_mode(pixelpart_gms2::string runtimePtr, pixelpart_gms2::real particleTypeId, pixelpart_gms2::real mode) {
	pixelpart_gms2::EffectRuntime* effectRuntime = reinterpret_cast<pixelpart_gms2::EffectRuntime*>(runtimePtr);
	if(!effectRuntime) {
		pixelpart_gms2::lastError = pixelpart_gms2::invalidEffectRuntimeError;
		return -1;
	}

	try {
		pixelpart::ParticleType& particleType =
			effectRuntime->effectAsset.effect().particleTypes().at(pixelpart::id_t(particleTypeId));

		particleType.rotationMode(static_cast<pixelpart::RotationMode>(mode));

		return 1;
	}
	catch(const std::exception& e) {
		pixelpart_gms2::lastError = std::string(e.what());
	}

	return -1;
}

GMS2_EXPORT pixelpart_gms2::real GMS2_API pixelpart_particle_type_get_rotation_mode(pixelpart_gms2::string runtimePtr, pixelpart_gms2::real particleTypeId) {
	pixelpart_gms2::EffectRuntime* effectRuntime = reinterpret_cast<pixelpart_gms2::EffectRuntime*>(runtimePtr);
	if(!effectRuntime) {
		pixelpart_gms2::lastError = pixelpart_gms2::invalidEffectRuntimeError;
		return -1;
	}

	try {
		const pixelpart::ParticleType& particleType =
			effectRuntime->effectAsset.effect().particleTypes().at(pixelpart::id_t(particleTypeId));

		return static_cast<pixelpart_gms2::real>(particleType.rotationMode());
	}
	catch(const std::exception& e) {
		pixelpart_gms2::lastError = std::string(e.what());
	}

	return -1;
}

GMS2_EXPORT pixelpart_gms2::real GMS2_API pixelpart_particle_type_set_alignment_mode(pixelpart_gms2::string runtimePtr, pixelpart_gms2::real particleTypeId, pixelpart_gms2::real mode) {
	pixelpart_gms2::EffectRuntime* effectRuntime = reinterpret_cast<pixelpart_gms2::EffectRuntime*>(runtimePtr);
	if(!effectRuntime) {
		pixelpart_gms2::lastError = pixelpart_gms2::invalidEffectRuntimeError;
		return -1;
	}

	try {
		pixelpart::ParticleType& particleType =
			effectRuntime->effectAsset.effect().particleTypes().at(pixelpart::id_t(particleTypeId));

		particleType.alignmentMode(static_cast<pixelpart::AlignmentMode>(mode));

		return 1;
	}
	catch(const std::exception& e) {
		pixelpart_gms2::lastError = std::string(e.what());
	}

	return -1;
}

GMS2_EXPORT pixelpart_gms2::real GMS2_API pixelpart_particle_type_get_alignment_mode(pixelpart_gms2::string runtimePtr, pixelpart_gms2::real particleTypeId) {
	pixelpart_gms2::EffectRuntime* effectRuntime = reinterpret_cast<pixelpart_gms2::EffectRuntime*>(runtimePtr);
	if(!effectRuntime) {
		pixelpart_gms2::lastError = pixelpart_gms2::invalidEffectRuntimeError;
		return -1;
	}

	try {
		const pixelpart::ParticleType& particleType =
			effectRuntime->effectAsset.effect().particleTypes().at(pixelpart::id_t(particleTypeId));

		return static_cast<pixelpart_gms2::real>(particleType.alignmentMode());
	}
	catch(const std::exception& e) {
		pixelpart_gms2::lastError = std::string(e.what());
	}

	return -1;
}

GMS2_EXPORT pixelpart_gms2::const_string GMS2_API pixelpart_particle_type_get_pivot(pixelpart_gms2::string runtimePtr, pixelpart_gms2::real particleTypeId) {
	pixelpart_gms2::EffectRuntime* effectRuntime = reinterpret_cast<pixelpart_gms2::EffectRuntime*>(runtimePtr);
	if(!effectRuntime) {
		pixelpart_gms2::lastError = pixelpart_gms2::invalidEffectRuntimeError;
		pixelpart_gms2::particleTypePropertyPtrString = pixelpart_gms2::nullPointerString;

		return pixelpart_gms2::particleTypePropertyPtrString.c_str();
	}

	try {
		pixelpart::ParticleType& particleType =
			effectRuntime->effectAsset.effect().particleTypes().at(pixelpart::id_t(particleTypeId));

		pixelpart_gms2::particleTypePropertyPtrString = pixelpart_gms2::toBufferString(
			&particleType.pivot());
	}
	catch(const std::exception& e) {
		pixelpart_gms2::lastError = std::string(e.what());
		pixelpart_gms2::particleTypePropertyPtrString = pixelpart_gms2::nullPointerString;
	}

	return pixelpart_gms2::particleTypePropertyPtrString.c_str();
}

GMS2_EXPORT pixelpart_gms2::const_string GMS2_API pixelpart_particle_type_get_motion_path_force(pixelpart_gms2::string runtimePtr, pixelpart_gms2::real particleTypeId) {
	pixelpart_gms2::EffectRuntime* effectRuntime = reinterpret_cast<pixelpart_gms2::EffectRuntime*>(runtimePtr);
	if(!effectRuntime) {
		pixelpart_gms2::lastError = pixelpart_gms2::invalidEffectRuntimeError;
		pixelpart_gms2::particleTypePropertyPtrString = pixelpart_gms2::nullPointerString;

		return pixelpart_gms2::particleTypePropertyPtrString.c_str();
	}

	try {
		pixelpart::ParticleType& particleType =
			effectRuntime->effectAsset.effect().particleTypes().at(pixelpart::id_t(particleTypeId));

		pixelpart_gms2::particleTypePropertyPtrString = pixelpart_gms2::toBufferString(
			&particleType.motionPathForce());
	}
	catch(const std::exception& e) {
		pixelpart_gms2::lastError = std::string(e.what());
		pixelpart_gms2::particleTypePropertyPtrString = pixelpart_gms2::nullPointerString;
	}

	return pixelpart_gms2::particleTypePropertyPtrString.c_str();
}

GMS2_EXPORT pixelpart_gms2::real GMS2_API pixelpart_particle_type_set_visible(pixelpart_gms2::string runtimePtr, pixelpart_gms2::real particleTypeId, pixelpart_gms2::real visible) {
	pixelpart_gms2::EffectRuntime* effectRuntime = reinterpret_cast<pixelpart_gms2::EffectRuntime*>(runtimePtr);
	if(!effectRuntime) {
		pixelpart_gms2::lastError = pixelpart_gms2::invalidEffectRuntimeError;
		return -1;
	}

	try {
		pixelpart::ParticleType& particleType =
			effectRuntime->effectAsset.effect().particleTypes().at(pixelpart::id_t(particleTypeId));

		particleType.visible(visible);

		return 1;
	}
	catch(const std::exception& e) {
		pixelpart_gms2::lastError = std::string(e.what());
	}

	return -1;
}

GMS2_EXPORT pixelpart_gms2::real GMS2_API pixelpart_particle_type_is_visible(pixelpart_gms2::string runtimePtr, pixelpart_gms2::real particleTypeId) {
	pixelpart_gms2::EffectRuntime* effectRuntime = reinterpret_cast<pixelpart_gms2::EffectRuntime*>(runtimePtr);
	if(!effectRuntime) {
		pixelpart_gms2::lastError = pixelpart_gms2::invalidEffectRuntimeError;
		return -1;
	}

	try {
		const pixelpart::ParticleType& particleType =
			effectRuntime->effectAsset.effect().particleTypes().at(pixelpart::id_t(particleTypeId));

		return particleType.visible() ? 1 : 0;
	}
	catch(const std::exception& e) {
		pixelpart_gms2::lastError = std::string(e.what());
	}

	return -1;
}

GMS2_EXPORT pixelpart_gms2::real GMS2_API pixelpart_particle_type_set_layer(pixelpart_gms2::string runtimePtr, pixelpart_gms2::real particleTypeId, pixelpart_gms2::real layer) {
	pixelpart_gms2::EffectRuntime* effectRuntime = reinterpret_cast<pixelpart_gms2::EffectRuntime*>(runtimePtr);
	if(!effectRuntime) {
		pixelpart_gms2::lastError = pixelpart_gms2::invalidEffectRuntimeError;
		return -1;
	}

	try {
		pixelpart::ParticleType& particleType =
			effectRuntime->effectAsset.effect().particleTypes().at(pixelpart::id_t(particleTypeId));

		particleType.layer(static_cast<std::uint32_t>(std::max(layer, static_cast<pixelpart_gms2::real>(0))));

		return 1;
	}
	catch(const std::exception& e) {
		pixelpart_gms2::lastError = std::string(e.what());
	}

	return -1;
}

GMS2_EXPORT pixelpart_gms2::real GMS2_API pixelpart_particle_type_get_layer(pixelpart_gms2::string runtimePtr, pixelpart_gms2::real particleTypeId) {
	pixelpart_gms2::EffectRuntime* effectRuntime = reinterpret_cast<pixelpart_gms2::EffectRuntime*>(runtimePtr);
	if(!effectRuntime) {
		pixelpart_gms2::lastError = pixelpart_gms2::invalidEffectRuntimeError;
		return -1;
	}

	try {
		const pixelpart::ParticleType& particleType =
			effectRuntime->effectAsset.effect().particleTypes().at(pixelpart::id_t(particleTypeId));

		return static_cast<pixelpart_gms2::real>(particleType.layer());
	}
	catch(const std::exception& e) {
		pixelpart_gms2::lastError = std::string(e.what());
	}

	return -1;
}

GMS2_EXPORT pixelpart_gms2::real GMS2_API pixelpart_particle_type_get_material_id(pixelpart_gms2::string runtimePtr, pixelpart_gms2::real particleTypeId, pixelpart_gms2::string bufferPtr, pixelpart_gms2::real bufferSize) {
	pixelpart_gms2::EffectRuntime* effectRuntime = reinterpret_cast<pixelpart_gms2::EffectRuntime*>(runtimePtr);
	if(!effectRuntime) {
		pixelpart_gms2::lastError = pixelpart_gms2::invalidEffectRuntimeError;
		return -1;
	}
	else if(!bufferPtr || bufferSize < 2) {
		pixelpart_gms2::lastError = pixelpart_gms2::invalidArgumentError;
		return -1;
	}

	try {
		const pixelpart::ParticleType& particleType = effectRuntime->effectAsset.effect().particleTypes().at(pixelpart::id_t(particleTypeId));
		if(particleType.materialInstance().materialId().empty()) {
			return 0;
		}

		std::size_t size = std::min(particleType.materialInstance().materialId().size(), static_cast<std::size_t>(bufferSize) - 1);
		std::memcpy(bufferPtr, particleType.materialInstance().materialId().c_str(), size);
		bufferPtr[size] = '\0';

		return static_cast<pixelpart_gms2::real>(size);
	}
	catch(const std::exception& e) {
		pixelpart_gms2::lastError = std::string(e.what());
	}

	return -1;
}

GMS2_EXPORT pixelpart_gms2::real GMS2_API pixelpart_particle_type_is_material_builtin(pixelpart_gms2::string runtimePtr, pixelpart_gms2::real particleTypeId) {
	pixelpart_gms2::EffectRuntime* effectRuntime = reinterpret_cast<pixelpart_gms2::EffectRuntime*>(runtimePtr);
	if(!effectRuntime) {
		pixelpart_gms2::lastError = pixelpart_gms2::invalidEffectRuntimeError;
		return -1;
	}

	try {
		const pixelpart::ParticleType& particleType =
			effectRuntime->effectAsset.effect().particleTypes().at(pixelpart::id_t(particleTypeId));

		return particleType.materialInstance().builtInMaterial() ? 1 : 0;
	}
	catch(const std::exception& e) {
		pixelpart_gms2::lastError = std::string(e.what());
	}

	return -1;
}

GMS2_EXPORT pixelpart_gms2::real GMS2_API pixelpart_particle_type_get_material_parameter_count(pixelpart_gms2::string runtimePtr, pixelpart_gms2::real particleTypeId) {
	pixelpart_gms2::EffectRuntime* effectRuntime = reinterpret_cast<pixelpart_gms2::EffectRuntime*>(runtimePtr);
	if(!effectRuntime) {
		pixelpart_gms2::lastError = pixelpart_gms2::invalidEffectRuntimeError;
		return -1;
	}

	try {
		const pixelpart::ParticleType& particleType =
			effectRuntime->effectAsset.effect().particleTypes().at(pixelpart::id_t(particleTypeId));

		return static_cast<pixelpart_gms2::real>(particleType.materialInstance().materialParameters().size());
	}
	catch(const std::exception& e) {
		pixelpart_gms2::lastError = std::string(e.what());
	}

	return -1;
}

GMS2_EXPORT pixelpart_gms2::real GMS2_API pixelpart_particle_type_get_material_parameter_ids(pixelpart_gms2::string runtimePtr, pixelpart_gms2::real particleTypeId, pixelpart_gms2::string parameterIdBufferPtr) {
	pixelpart_gms2::EffectRuntime* effectRuntime = reinterpret_cast<pixelpart_gms2::EffectRuntime*>(runtimePtr);
	if(!effectRuntime) {
		pixelpart_gms2::lastError = pixelpart_gms2::invalidEffectRuntimeError;
		return -1;
	}
	else if(!parameterIdBufferPtr) {
		pixelpart_gms2::lastError = pixelpart_gms2::invalidArgumentError;
		return -1;
	}

	try {
		const pixelpart::ParticleType& particleType =
			effectRuntime->effectAsset.effect().particleTypes().at(pixelpart::id_t(particleTypeId));

		pixelpart_gms2::Buffer parameterIdBuffer(parameterIdBufferPtr);
		for(const auto& parameterEntry : particleType.materialInstance().materialParameters()) {
			parameterIdBuffer.write<std::uint32_t>(parameterEntry.first.value());
		}
	}
	catch(const std::exception& e) {
		pixelpart_gms2::lastError = std::string(e.what());
	}

	return -1;
}

GMS2_EXPORT pixelpart_gms2::real GMS2_API pixelpart_particle_type_get_material_parameter_type(pixelpart_gms2::string runtimePtr, pixelpart_gms2::real particleTypeId, pixelpart_gms2::real parameterId) {
	pixelpart_gms2::EffectRuntime* effectRuntime = reinterpret_cast<pixelpart_gms2::EffectRuntime*>(runtimePtr);
	if(!effectRuntime) {
		pixelpart_gms2::lastError = pixelpart_gms2::invalidEffectRuntimeError;
		return -1;
	}

	try {
		const pixelpart::ParticleType& particleType =
			effectRuntime->effectAsset.effect().particleTypes().at(pixelpart::id_t(particleTypeId));

		return static_cast<pixelpart_gms2::real>(particleType.materialInstance().materialParameters().at(parameterId).type());
	}
	catch(const std::exception& e) {
		pixelpart_gms2::lastError = std::string(e.what());
	}

	return -1;
}

GMS2_EXPORT pixelpart_gms2::real GMS2_API pixelpart_particle_type_get_material_parameter_value(pixelpart_gms2::string runtimePtr, pixelpart_gms2::real particleTypeId, pixelpart_gms2::real parameterId, pixelpart_gms2::string resultBufferPtr) {
	pixelpart_gms2::EffectRuntime* effectRuntime = reinterpret_cast<pixelpart_gms2::EffectRuntime*>(runtimePtr);
	if(!effectRuntime) {
		pixelpart_gms2::lastError = pixelpart_gms2::invalidEffectRuntimeError;
		return -1;
	}

	try {
		const pixelpart::ParticleType& particleType =
			effectRuntime->effectAsset.effect().particleTypes().at(pixelpart::id_t(particleTypeId));

		pixelpart_gms2::Buffer resultBuffer(resultBufferPtr);

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
				pixelpart_gms2::lastError = "Unsupported parameter type";
				return -1;
		}

		return 1;
	}
	catch(const std::exception& e) {
		pixelpart_gms2::lastError = std::string(e.what());
	}

	return -1;
}

GMS2_EXPORT pixelpart_gms2::real GMS2_API pixelpart_particle_type_get_renderer(pixelpart_gms2::string runtimePtr, pixelpart_gms2::real particleTypeId) {
	pixelpart_gms2::EffectRuntime* effectRuntime = reinterpret_cast<pixelpart_gms2::EffectRuntime*>(runtimePtr);
	if(!effectRuntime) {
		pixelpart_gms2::lastError = pixelpart_gms2::invalidEffectRuntimeError;
		return -1;
	}

	try {
		const pixelpart::ParticleType& particleType =
			effectRuntime->effectAsset.effect().particleTypes().at(pixelpart::id_t(particleTypeId));

		return static_cast<pixelpart_gms2::real>(particleType.renderer());
	}
	catch(const std::exception& e) {
		pixelpart_gms2::lastError = std::string(e.what());
	}

	return -1;
}

GMS2_EXPORT pixelpart_gms2::const_string GMS2_API pixelpart_particle_type_get_mesh_renderer_mesh_resource_id(pixelpart_gms2::string runtimePtr, pixelpart_gms2::real particleTypeId) {
	pixelpart_gms2::EffectRuntime* effectRuntime = reinterpret_cast<pixelpart_gms2::EffectRuntime*>(runtimePtr);
	if(!effectRuntime) {
		pixelpart_gms2::lastError = pixelpart_gms2::invalidEffectRuntimeError;
		return "";
	}

	try {
		const pixelpart::ParticleType& particleType =
			effectRuntime->effectAsset.effect().particleTypes().at(pixelpart::id_t(particleTypeId));

		return particleType.meshRendererSettings().meshResourceId.c_str();
	}
	catch(const std::exception& e) {
		pixelpart_gms2::lastError = std::string(e.what());
	}

	return "";
}

GMS2_EXPORT pixelpart_gms2::const_string GMS2_API pixelpart_particle_type_get_count(pixelpart_gms2::string runtimePtr, pixelpart_gms2::real particleTypeId) {
	pixelpart_gms2::EffectRuntime* effectRuntime = reinterpret_cast<pixelpart_gms2::EffectRuntime*>(runtimePtr);
	if(!effectRuntime) {
		pixelpart_gms2::lastError = pixelpart_gms2::invalidEffectRuntimeError;
		pixelpart_gms2::particleTypePropertyPtrString = pixelpart_gms2::nullPointerString;

		return pixelpart_gms2::particleTypePropertyPtrString.c_str();
	}

	try {
		pixelpart::ParticleType& particleType =
			effectRuntime->effectAsset.effect().particleTypes().at(pixelpart::id_t(particleTypeId));

		pixelpart_gms2::particleTypePropertyPtrString = pixelpart_gms2::toBufferString(
			&particleType.count());
	}
	catch(const std::exception& e) {
		pixelpart_gms2::lastError = std::string(e.what());
		pixelpart_gms2::particleTypePropertyPtrString = pixelpart_gms2::nullPointerString;
	}

	return pixelpart_gms2::particleTypePropertyPtrString.c_str();
}

GMS2_EXPORT pixelpart_gms2::const_string GMS2_API pixelpart_particle_type_get_lifespan(pixelpart_gms2::string runtimePtr, pixelpart_gms2::real particleTypeId) {
	pixelpart_gms2::EffectRuntime* effectRuntime = reinterpret_cast<pixelpart_gms2::EffectRuntime*>(runtimePtr);
	if(!effectRuntime) {
		pixelpart_gms2::lastError = pixelpart_gms2::invalidEffectRuntimeError;
		pixelpart_gms2::particleTypePropertyPtrString = pixelpart_gms2::nullPointerString;

		return pixelpart_gms2::particleTypePropertyPtrString.c_str();
	}

	try {
		pixelpart::ParticleType& particleType =
			effectRuntime->effectAsset.effect().particleTypes().at(pixelpart::id_t(particleTypeId));

		pixelpart_gms2::particleTypePropertyPtrString = pixelpart_gms2::toBufferString(
			&particleType.lifespan());
	}
	catch(const std::exception& e) {
		pixelpart_gms2::lastError = std::string(e.what());
		pixelpart_gms2::particleTypePropertyPtrString = pixelpart_gms2::nullPointerString;
	}

	return pixelpart_gms2::particleTypePropertyPtrString.c_str();
}

GMS2_EXPORT pixelpart_gms2::const_string GMS2_API pixelpart_particle_type_get_initial_size(pixelpart_gms2::string runtimePtr, pixelpart_gms2::real particleTypeId) {
	pixelpart_gms2::EffectRuntime* effectRuntime = reinterpret_cast<pixelpart_gms2::EffectRuntime*>(runtimePtr);
	if(!effectRuntime) {
		pixelpart_gms2::lastError = pixelpart_gms2::invalidEffectRuntimeError;
		pixelpart_gms2::particleTypePropertyPtrString = pixelpart_gms2::nullPointerString;

		return pixelpart_gms2::particleTypePropertyPtrString.c_str();
	}

	try {
		pixelpart::ParticleType& particleType =
			effectRuntime->effectAsset.effect().particleTypes().at(pixelpart::id_t(particleTypeId));

		pixelpart_gms2::particleTypePropertyPtrString = pixelpart_gms2::toBufferString(
			&particleType.initialSize());
	}
	catch(const std::exception& e) {
		pixelpart_gms2::lastError = std::string(e.what());
		pixelpart_gms2::particleTypePropertyPtrString = pixelpart_gms2::nullPointerString;
	}

	return pixelpart_gms2::particleTypePropertyPtrString.c_str();
}

GMS2_EXPORT pixelpart_gms2::const_string GMS2_API pixelpart_particle_type_get_initial_rotation(pixelpart_gms2::string runtimePtr, pixelpart_gms2::real particleTypeId) {
	pixelpart_gms2::EffectRuntime* effectRuntime = reinterpret_cast<pixelpart_gms2::EffectRuntime*>(runtimePtr);
	if(!effectRuntime) {
		pixelpart_gms2::lastError = pixelpart_gms2::invalidEffectRuntimeError;
		pixelpart_gms2::particleTypePropertyPtrString = pixelpart_gms2::nullPointerString;

		return pixelpart_gms2::particleTypePropertyPtrString.c_str();
	}

	try {
		pixelpart::ParticleType& particleType =
			effectRuntime->effectAsset.effect().particleTypes().at(pixelpart::id_t(particleTypeId));

		pixelpart_gms2::particleTypePropertyPtrString = pixelpart_gms2::toBufferString(
			&particleType.initialRotation());
	}
	catch(const std::exception& e) {
		pixelpart_gms2::lastError = std::string(e.what());
		pixelpart_gms2::particleTypePropertyPtrString = pixelpart_gms2::nullPointerString;
	}

	return pixelpart_gms2::particleTypePropertyPtrString.c_str();
}

GMS2_EXPORT pixelpart_gms2::const_string GMS2_API pixelpart_particle_type_get_initial_velocity(pixelpart_gms2::string runtimePtr, pixelpart_gms2::real particleTypeId) {
	pixelpart_gms2::EffectRuntime* effectRuntime = reinterpret_cast<pixelpart_gms2::EffectRuntime*>(runtimePtr);
	if(!effectRuntime) {
		pixelpart_gms2::lastError = pixelpart_gms2::invalidEffectRuntimeError;
		pixelpart_gms2::particleTypePropertyPtrString = pixelpart_gms2::nullPointerString;

		return pixelpart_gms2::particleTypePropertyPtrString.c_str();
	}

	try {
		pixelpart::ParticleType& particleType =
			effectRuntime->effectAsset.effect().particleTypes().at(pixelpart::id_t(particleTypeId));

		pixelpart_gms2::particleTypePropertyPtrString = pixelpart_gms2::toBufferString(
			&particleType.initialVelocity());
	}
	catch(const std::exception& e) {
		pixelpart_gms2::lastError = std::string(e.what());
		pixelpart_gms2::particleTypePropertyPtrString = pixelpart_gms2::nullPointerString;
	}

	return pixelpart_gms2::particleTypePropertyPtrString.c_str();
}

GMS2_EXPORT pixelpart_gms2::const_string GMS2_API pixelpart_particle_type_get_inherited_velocity(pixelpart_gms2::string runtimePtr, pixelpart_gms2::real particleTypeId) {
	pixelpart_gms2::EffectRuntime* effectRuntime = reinterpret_cast<pixelpart_gms2::EffectRuntime*>(runtimePtr);
	if(!effectRuntime) {
		pixelpart_gms2::lastError = pixelpart_gms2::invalidEffectRuntimeError;
		pixelpart_gms2::particleTypePropertyPtrString = pixelpart_gms2::nullPointerString;

		return pixelpart_gms2::particleTypePropertyPtrString.c_str();
	}

	try {
		pixelpart::ParticleType& particleType =
			effectRuntime->effectAsset.effect().particleTypes().at(pixelpart::id_t(particleTypeId));

		pixelpart_gms2::particleTypePropertyPtrString = pixelpart_gms2::toBufferString(
			&particleType.inheritedVelocity());
	}
	catch(const std::exception& e) {
		pixelpart_gms2::lastError = std::string(e.what());
		pixelpart_gms2::particleTypePropertyPtrString = pixelpart_gms2::nullPointerString;
	}

	return pixelpart_gms2::particleTypePropertyPtrString.c_str();
}

GMS2_EXPORT pixelpart_gms2::const_string GMS2_API pixelpart_particle_type_get_initial_opacity(pixelpart_gms2::string runtimePtr, pixelpart_gms2::real particleTypeId) {
	pixelpart_gms2::EffectRuntime* effectRuntime = reinterpret_cast<pixelpart_gms2::EffectRuntime*>(runtimePtr);
	if(!effectRuntime) {
		pixelpart_gms2::lastError = pixelpart_gms2::invalidEffectRuntimeError;
		pixelpart_gms2::particleTypePropertyPtrString = pixelpart_gms2::nullPointerString;

		return pixelpart_gms2::particleTypePropertyPtrString.c_str();
	}

	try {
		pixelpart::ParticleType& particleType =
			effectRuntime->effectAsset.effect().particleTypes().at(pixelpart::id_t(particleTypeId));

		pixelpart_gms2::particleTypePropertyPtrString = pixelpart_gms2::toBufferString(
			&particleType.initialOpacity());
	}
	catch(const std::exception& e) {
		pixelpart_gms2::lastError = std::string(e.what());
		pixelpart_gms2::particleTypePropertyPtrString = pixelpart_gms2::nullPointerString;
	}

	return pixelpart_gms2::particleTypePropertyPtrString.c_str();
}

GMS2_EXPORT pixelpart_gms2::const_string GMS2_API pixelpart_particle_type_get_motion_path(pixelpart_gms2::string runtimePtr, pixelpart_gms2::real particleTypeId) {
	pixelpart_gms2::EffectRuntime* effectRuntime = reinterpret_cast<pixelpart_gms2::EffectRuntime*>(runtimePtr);
	if(!effectRuntime) {
		pixelpart_gms2::lastError = pixelpart_gms2::invalidEffectRuntimeError;
		pixelpart_gms2::particleTypePropertyPtrString = pixelpart_gms2::nullPointerString;

		return pixelpart_gms2::particleTypePropertyPtrString.c_str();
	}

	try {
		pixelpart::ParticleType& particleType =
			effectRuntime->effectAsset.effect().particleTypes().at(pixelpart::id_t(particleTypeId));

		pixelpart_gms2::particleTypePropertyPtrString = pixelpart_gms2::toBufferString(
			&particleType.motionPath());
	}
	catch(const std::exception& e) {
		pixelpart_gms2::lastError = std::string(e.what());
		pixelpart_gms2::particleTypePropertyPtrString = pixelpart_gms2::nullPointerString;
	}

	return pixelpart_gms2::particleTypePropertyPtrString.c_str();
}

GMS2_EXPORT pixelpart_gms2::const_string GMS2_API pixelpart_particle_type_get_size(pixelpart_gms2::string runtimePtr, pixelpart_gms2::real particleTypeId) {
	pixelpart_gms2::EffectRuntime* effectRuntime = reinterpret_cast<pixelpart_gms2::EffectRuntime*>(runtimePtr);
	if(!effectRuntime) {
		pixelpart_gms2::lastError = pixelpart_gms2::invalidEffectRuntimeError;
		pixelpart_gms2::particleTypePropertyPtrString = pixelpart_gms2::nullPointerString;

		return pixelpart_gms2::particleTypePropertyPtrString.c_str();
	}

	try {
		pixelpart::ParticleType& particleType =
			effectRuntime->effectAsset.effect().particleTypes().at(pixelpart::id_t(particleTypeId));

		pixelpart_gms2::particleTypePropertyPtrString = pixelpart_gms2::toBufferString(
			&particleType.size());
	}
	catch(const std::exception& e) {
		pixelpart_gms2::lastError = std::string(e.what());
		pixelpart_gms2::particleTypePropertyPtrString = pixelpart_gms2::nullPointerString;
	}

	return pixelpart_gms2::particleTypePropertyPtrString.c_str();
}

GMS2_EXPORT pixelpart_gms2::const_string GMS2_API pixelpart_particle_type_get_stretch(pixelpart_gms2::string runtimePtr, pixelpart_gms2::real particleTypeId) {
	pixelpart_gms2::EffectRuntime* effectRuntime = reinterpret_cast<pixelpart_gms2::EffectRuntime*>(runtimePtr);
	if(!effectRuntime) {
		pixelpart_gms2::lastError = pixelpart_gms2::invalidEffectRuntimeError;
		pixelpart_gms2::particleTypePropertyPtrString = pixelpart_gms2::nullPointerString;

		return pixelpart_gms2::particleTypePropertyPtrString.c_str();
	}

	try {
		pixelpart::ParticleType& particleType =
			effectRuntime->effectAsset.effect().particleTypes().at(pixelpart::id_t(particleTypeId));

		pixelpart_gms2::particleTypePropertyPtrString = pixelpart_gms2::toBufferString(
			&particleType.stretch());
	}
	catch(const std::exception& e) {
		pixelpart_gms2::lastError = std::string(e.what());
		pixelpart_gms2::particleTypePropertyPtrString = pixelpart_gms2::nullPointerString;
	}

	return pixelpart_gms2::particleTypePropertyPtrString.c_str();
}

GMS2_EXPORT pixelpart_gms2::const_string GMS2_API pixelpart_particle_type_get_physical_size(pixelpart_gms2::string runtimePtr, pixelpart_gms2::real particleTypeId) {
	pixelpart_gms2::EffectRuntime* effectRuntime = reinterpret_cast<pixelpart_gms2::EffectRuntime*>(runtimePtr);
	if(!effectRuntime) {
		pixelpart_gms2::lastError = pixelpart_gms2::invalidEffectRuntimeError;
		pixelpart_gms2::particleTypePropertyPtrString = pixelpart_gms2::nullPointerString;

		return pixelpart_gms2::particleTypePropertyPtrString.c_str();
	}

	try {
		pixelpart::ParticleType& particleType =
			effectRuntime->effectAsset.effect().particleTypes().at(pixelpart::id_t(particleTypeId));

		pixelpart_gms2::particleTypePropertyPtrString = pixelpart_gms2::toBufferString(
			&particleType.physicalSize());
	}
	catch(const std::exception& e) {
		pixelpart_gms2::lastError = std::string(e.what());
		pixelpart_gms2::particleTypePropertyPtrString = pixelpart_gms2::nullPointerString;
	}

	return pixelpart_gms2::particleTypePropertyPtrString.c_str();
}

GMS2_EXPORT pixelpart_gms2::const_string GMS2_API pixelpart_particle_type_get_rotation(pixelpart_gms2::string runtimePtr, pixelpart_gms2::real particleTypeId) {
	pixelpart_gms2::EffectRuntime* effectRuntime = reinterpret_cast<pixelpart_gms2::EffectRuntime*>(runtimePtr);
	if(!effectRuntime) {
		pixelpart_gms2::lastError = pixelpart_gms2::invalidEffectRuntimeError;
		pixelpart_gms2::particleTypePropertyPtrString = pixelpart_gms2::nullPointerString;

		return pixelpart_gms2::particleTypePropertyPtrString.c_str();
	}

	try {
		pixelpart::ParticleType& particleType =
			effectRuntime->effectAsset.effect().particleTypes().at(pixelpart::id_t(particleTypeId));

		pixelpart_gms2::particleTypePropertyPtrString = pixelpart_gms2::toBufferString(
			&particleType.rotation());
	}
	catch(const std::exception& e) {
		pixelpart_gms2::lastError = std::string(e.what());
		pixelpart_gms2::particleTypePropertyPtrString = pixelpart_gms2::nullPointerString;
	}

	return pixelpart_gms2::particleTypePropertyPtrString.c_str();
}

GMS2_EXPORT pixelpart_gms2::const_string GMS2_API pixelpart_particle_type_get_rotation_by_speed(pixelpart_gms2::string runtimePtr, pixelpart_gms2::real particleTypeId) {
	pixelpart_gms2::EffectRuntime* effectRuntime = reinterpret_cast<pixelpart_gms2::EffectRuntime*>(runtimePtr);
	if(!effectRuntime) {
		pixelpart_gms2::lastError = pixelpart_gms2::invalidEffectRuntimeError;
		pixelpart_gms2::particleTypePropertyPtrString = pixelpart_gms2::nullPointerString;

		return pixelpart_gms2::particleTypePropertyPtrString.c_str();
	}

	try {
		pixelpart::ParticleType& particleType =
			effectRuntime->effectAsset.effect().particleTypes().at(pixelpart::id_t(particleTypeId));

		pixelpart_gms2::particleTypePropertyPtrString = pixelpart_gms2::toBufferString(
			&particleType.rotationBySpeed());
	}
	catch(const std::exception& e) {
		pixelpart_gms2::lastError = std::string(e.what());
		pixelpart_gms2::particleTypePropertyPtrString = pixelpart_gms2::nullPointerString;
	}

	return pixelpart_gms2::particleTypePropertyPtrString.c_str();
}

GMS2_EXPORT pixelpart_gms2::const_string GMS2_API pixelpart_particle_type_get_acceleration(pixelpart_gms2::string runtimePtr, pixelpart_gms2::real particleTypeId) {
	pixelpart_gms2::EffectRuntime* effectRuntime = reinterpret_cast<pixelpart_gms2::EffectRuntime*>(runtimePtr);
	if(!effectRuntime) {
		pixelpart_gms2::lastError = pixelpart_gms2::invalidEffectRuntimeError;
		pixelpart_gms2::particleTypePropertyPtrString = pixelpart_gms2::nullPointerString;

		return pixelpart_gms2::particleTypePropertyPtrString.c_str();
	}

	try {
		pixelpart::ParticleType& particleType =
			effectRuntime->effectAsset.effect().particleTypes().at(pixelpart::id_t(particleTypeId));

		pixelpart_gms2::particleTypePropertyPtrString = pixelpart_gms2::toBufferString(
			&particleType.acceleration());
	}
	catch(const std::exception& e) {
		pixelpart_gms2::lastError = std::string(e.what());
		pixelpart_gms2::particleTypePropertyPtrString = pixelpart_gms2::nullPointerString;
	}

	return pixelpart_gms2::particleTypePropertyPtrString.c_str();
}

GMS2_EXPORT pixelpart_gms2::const_string GMS2_API pixelpart_particle_type_get_radial_acceleration(pixelpart_gms2::string runtimePtr, pixelpart_gms2::real particleTypeId) {
	pixelpart_gms2::EffectRuntime* effectRuntime = reinterpret_cast<pixelpart_gms2::EffectRuntime*>(runtimePtr);
	if(!effectRuntime) {
		pixelpart_gms2::lastError = pixelpart_gms2::invalidEffectRuntimeError;
		pixelpart_gms2::particleTypePropertyPtrString = pixelpart_gms2::nullPointerString;

		return pixelpart_gms2::particleTypePropertyPtrString.c_str();
	}

	try {
		pixelpart::ParticleType& particleType =
			effectRuntime->effectAsset.effect().particleTypes().at(pixelpart::id_t(particleTypeId));

		pixelpart_gms2::particleTypePropertyPtrString = pixelpart_gms2::toBufferString(
			&particleType.radialAcceleration());
	}
	catch(const std::exception& e) {
		pixelpart_gms2::lastError = std::string(e.what());
		pixelpart_gms2::particleTypePropertyPtrString = pixelpart_gms2::nullPointerString;
	}

	return pixelpart_gms2::particleTypePropertyPtrString.c_str();
}

GMS2_EXPORT pixelpart_gms2::const_string GMS2_API pixelpart_particle_type_get_weight(pixelpart_gms2::string runtimePtr, pixelpart_gms2::real particleTypeId) {
	pixelpart_gms2::EffectRuntime* effectRuntime = reinterpret_cast<pixelpart_gms2::EffectRuntime*>(runtimePtr);
	if(!effectRuntime) {
		pixelpart_gms2::lastError = pixelpart_gms2::invalidEffectRuntimeError;
		pixelpart_gms2::particleTypePropertyPtrString = pixelpart_gms2::nullPointerString;

		return pixelpart_gms2::particleTypePropertyPtrString.c_str();
	}

	try {
		pixelpart::ParticleType& particleType =
			effectRuntime->effectAsset.effect().particleTypes().at(pixelpart::id_t(particleTypeId));

		pixelpart_gms2::particleTypePropertyPtrString = pixelpart_gms2::toBufferString(
			&particleType.weight());
	}
	catch(const std::exception& e) {
		pixelpart_gms2::lastError = std::string(e.what());
		pixelpart_gms2::particleTypePropertyPtrString = pixelpart_gms2::nullPointerString;
	}

	return pixelpart_gms2::particleTypePropertyPtrString.c_str();
}

GMS2_EXPORT pixelpart_gms2::const_string GMS2_API pixelpart_particle_type_get_bounce(pixelpart_gms2::string runtimePtr, pixelpart_gms2::real particleTypeId) {
	pixelpart_gms2::EffectRuntime* effectRuntime = reinterpret_cast<pixelpart_gms2::EffectRuntime*>(runtimePtr);
	if(!effectRuntime) {
		pixelpart_gms2::lastError = pixelpart_gms2::invalidEffectRuntimeError;
		pixelpart_gms2::particleTypePropertyPtrString = pixelpart_gms2::nullPointerString;

		return pixelpart_gms2::particleTypePropertyPtrString.c_str();
	}

	try {
		pixelpart::ParticleType& particleType =
			effectRuntime->effectAsset.effect().particleTypes().at(pixelpart::id_t(particleTypeId));

		pixelpart_gms2::particleTypePropertyPtrString = pixelpart_gms2::toBufferString(
			&particleType.bounce());
	}
	catch(const std::exception& e) {
		pixelpart_gms2::lastError = std::string(e.what());
		pixelpart_gms2::particleTypePropertyPtrString = pixelpart_gms2::nullPointerString;
	}

	return pixelpart_gms2::particleTypePropertyPtrString.c_str();
}

GMS2_EXPORT pixelpart_gms2::const_string GMS2_API pixelpart_particle_type_get_friction(pixelpart_gms2::string runtimePtr, pixelpart_gms2::real particleTypeId) {
	pixelpart_gms2::EffectRuntime* effectRuntime = reinterpret_cast<pixelpart_gms2::EffectRuntime*>(runtimePtr);
	if(!effectRuntime) {
		pixelpart_gms2::lastError = pixelpart_gms2::invalidEffectRuntimeError;
		pixelpart_gms2::particleTypePropertyPtrString = pixelpart_gms2::nullPointerString;

		return pixelpart_gms2::particleTypePropertyPtrString.c_str();
	}

	try {
		pixelpart::ParticleType& particleType =
			effectRuntime->effectAsset.effect().particleTypes().at(pixelpart::id_t(particleTypeId));

		pixelpart_gms2::particleTypePropertyPtrString = pixelpart_gms2::toBufferString(
			&particleType.friction());
	}
	catch(const std::exception& e) {
		pixelpart_gms2::lastError = std::string(e.what());
		pixelpart_gms2::particleTypePropertyPtrString = pixelpart_gms2::nullPointerString;
	}

	return pixelpart_gms2::particleTypePropertyPtrString.c_str();
}

GMS2_EXPORT pixelpart_gms2::const_string GMS2_API pixelpart_particle_type_get_color(pixelpart_gms2::string runtimePtr, pixelpart_gms2::real particleTypeId) {
	pixelpart_gms2::EffectRuntime* effectRuntime = reinterpret_cast<pixelpart_gms2::EffectRuntime*>(runtimePtr);
	if(!effectRuntime) {
		pixelpart_gms2::lastError = pixelpart_gms2::invalidEffectRuntimeError;
		pixelpart_gms2::particleTypePropertyPtrString = pixelpart_gms2::nullPointerString;

		return pixelpart_gms2::particleTypePropertyPtrString.c_str();
	}

	try {
		pixelpart::ParticleType& particleType =
			effectRuntime->effectAsset.effect().particleTypes().at(pixelpart::id_t(particleTypeId));

		pixelpart_gms2::particleTypePropertyPtrString = pixelpart_gms2::toBufferString(
			&particleType.color());
	}
	catch(const std::exception& e) {
		pixelpart_gms2::lastError = std::string(e.what());
		pixelpart_gms2::particleTypePropertyPtrString = pixelpart_gms2::nullPointerString;
	}

	return pixelpart_gms2::particleTypePropertyPtrString.c_str();
}

GMS2_EXPORT pixelpart_gms2::const_string GMS2_API pixelpart_particle_type_get_opacity(pixelpart_gms2::string runtimePtr, pixelpart_gms2::real particleTypeId) {
	pixelpart_gms2::EffectRuntime* effectRuntime = reinterpret_cast<pixelpart_gms2::EffectRuntime*>(runtimePtr);
	if(!effectRuntime) {
		pixelpart_gms2::lastError = pixelpart_gms2::invalidEffectRuntimeError;
		pixelpart_gms2::particleTypePropertyPtrString = pixelpart_gms2::nullPointerString;

		return pixelpart_gms2::particleTypePropertyPtrString.c_str();
	}

	try {
		pixelpart::ParticleType& particleType =
			effectRuntime->effectAsset.effect().particleTypes().at(pixelpart::id_t(particleTypeId));

		pixelpart_gms2::particleTypePropertyPtrString = pixelpart_gms2::toBufferString(
			&particleType.opacity());
	}
	catch(const std::exception& e) {
		pixelpart_gms2::lastError = std::string(e.what());
		pixelpart_gms2::particleTypePropertyPtrString = pixelpart_gms2::nullPointerString;
	}

	return pixelpart_gms2::particleTypePropertyPtrString.c_str();
}

GMS2_EXPORT pixelpart_gms2::const_string GMS2_API pixelpart_particle_type_get_lifespan_variance(pixelpart_gms2::string runtimePtr, pixelpart_gms2::real particleTypeId) {
	pixelpart_gms2::EffectRuntime* effectRuntime = reinterpret_cast<pixelpart_gms2::EffectRuntime*>(runtimePtr);
	if(!effectRuntime) {
		pixelpart_gms2::lastError = pixelpart_gms2::invalidEffectRuntimeError;
		pixelpart_gms2::particleTypePropertyPtrString = pixelpart_gms2::nullPointerString;

		return pixelpart_gms2::particleTypePropertyPtrString.c_str();
	}

	try {
		pixelpart::ParticleType& particleType =
			effectRuntime->effectAsset.effect().particleTypes().at(pixelpart::id_t(particleTypeId));

		pixelpart_gms2::particleTypePropertyPtrString = pixelpart_gms2::toBufferString(
			&particleType.lifespanVariance());
	}
	catch(const std::exception& e) {
		pixelpart_gms2::lastError = std::string(e.what());
		pixelpart_gms2::particleTypePropertyPtrString = pixelpart_gms2::nullPointerString;
	}

	return pixelpart_gms2::particleTypePropertyPtrString.c_str();
}

GMS2_EXPORT pixelpart_gms2::const_string GMS2_API pixelpart_particle_type_get_size_variance(pixelpart_gms2::string runtimePtr, pixelpart_gms2::real particleTypeId) {
	pixelpart_gms2::EffectRuntime* effectRuntime = reinterpret_cast<pixelpart_gms2::EffectRuntime*>(runtimePtr);
	if(!effectRuntime) {
		pixelpart_gms2::lastError = pixelpart_gms2::invalidEffectRuntimeError;
		pixelpart_gms2::particleTypePropertyPtrString = pixelpart_gms2::nullPointerString;

		return pixelpart_gms2::particleTypePropertyPtrString.c_str();
	}

	try {
		pixelpart::ParticleType& particleType =
			effectRuntime->effectAsset.effect().particleTypes().at(pixelpart::id_t(particleTypeId));

		pixelpart_gms2::particleTypePropertyPtrString = pixelpart_gms2::toBufferString(
			&particleType.sizeVariance());
	}
	catch(const std::exception& e) {
		pixelpart_gms2::lastError = std::string(e.what());
		pixelpart_gms2::particleTypePropertyPtrString = pixelpart_gms2::nullPointerString;
	}

	return pixelpart_gms2::particleTypePropertyPtrString.c_str();
}

GMS2_EXPORT pixelpart_gms2::const_string GMS2_API pixelpart_particle_type_get_rotation_variance(pixelpart_gms2::string runtimePtr, pixelpart_gms2::real particleTypeId) {
	pixelpart_gms2::EffectRuntime* effectRuntime = reinterpret_cast<pixelpart_gms2::EffectRuntime*>(runtimePtr);
	if(!effectRuntime) {
		pixelpart_gms2::lastError = pixelpart_gms2::invalidEffectRuntimeError;
		pixelpart_gms2::particleTypePropertyPtrString = pixelpart_gms2::nullPointerString;

		return pixelpart_gms2::particleTypePropertyPtrString.c_str();
	}

	try {
		pixelpart::ParticleType& particleType =
			effectRuntime->effectAsset.effect().particleTypes().at(pixelpart::id_t(particleTypeId));

		pixelpart_gms2::particleTypePropertyPtrString = pixelpart_gms2::toBufferString(
			&particleType.rotationVariance());
	}
	catch(const std::exception& e) {
		pixelpart_gms2::lastError = std::string(e.what());
		pixelpart_gms2::particleTypePropertyPtrString = pixelpart_gms2::nullPointerString;
	}

	return pixelpart_gms2::particleTypePropertyPtrString.c_str();
}

GMS2_EXPORT pixelpart_gms2::const_string GMS2_API pixelpart_particle_type_get_angular_velocity_variance(pixelpart_gms2::string runtimePtr, pixelpart_gms2::real particleTypeId) {
	pixelpart_gms2::EffectRuntime* effectRuntime = reinterpret_cast<pixelpart_gms2::EffectRuntime*>(runtimePtr);
	if(!effectRuntime) {
		pixelpart_gms2::lastError = pixelpart_gms2::invalidEffectRuntimeError;
		pixelpart_gms2::particleTypePropertyPtrString = pixelpart_gms2::nullPointerString;

		return pixelpart_gms2::particleTypePropertyPtrString.c_str();
	}

	try {
		pixelpart::ParticleType& particleType =
			effectRuntime->effectAsset.effect().particleTypes().at(pixelpart::id_t(particleTypeId));

		pixelpart_gms2::particleTypePropertyPtrString = pixelpart_gms2::toBufferString(
			&particleType.angularVelocityVariance());
	}
	catch(const std::exception& e) {
		pixelpart_gms2::lastError = std::string(e.what());
		pixelpart_gms2::particleTypePropertyPtrString = pixelpart_gms2::nullPointerString;
	}

	return pixelpart_gms2::particleTypePropertyPtrString.c_str();
}

GMS2_EXPORT pixelpart_gms2::const_string GMS2_API pixelpart_particle_type_get_velocity_variance(pixelpart_gms2::string runtimePtr, pixelpart_gms2::real particleTypeId) {
	pixelpart_gms2::EffectRuntime* effectRuntime = reinterpret_cast<pixelpart_gms2::EffectRuntime*>(runtimePtr);
	if(!effectRuntime) {
		pixelpart_gms2::lastError = pixelpart_gms2::invalidEffectRuntimeError;
		pixelpart_gms2::particleTypePropertyPtrString = pixelpart_gms2::nullPointerString;

		return pixelpart_gms2::particleTypePropertyPtrString.c_str();
	}

	try {
		pixelpart::ParticleType& particleType =
			effectRuntime->effectAsset.effect().particleTypes().at(pixelpart::id_t(particleTypeId));

		pixelpart_gms2::particleTypePropertyPtrString = pixelpart_gms2::toBufferString(
			&particleType.velocityVariance());
	}
	catch(const std::exception& e) {
		pixelpart_gms2::lastError = std::string(e.what());
		pixelpart_gms2::particleTypePropertyPtrString = pixelpart_gms2::nullPointerString;
	}

	return pixelpart_gms2::particleTypePropertyPtrString.c_str();
}

GMS2_EXPORT pixelpart_gms2::const_string GMS2_API pixelpart_particle_type_get_color_variance(pixelpart_gms2::string runtimePtr, pixelpart_gms2::real particleTypeId) {
	pixelpart_gms2::EffectRuntime* effectRuntime = reinterpret_cast<pixelpart_gms2::EffectRuntime*>(runtimePtr);
	if(!effectRuntime) {
		pixelpart_gms2::lastError = pixelpart_gms2::invalidEffectRuntimeError;
		pixelpart_gms2::particleTypePropertyPtrString = pixelpart_gms2::nullPointerString;

		return pixelpart_gms2::particleTypePropertyPtrString.c_str();
	}

	try {
		pixelpart::ParticleType& particleType =
			effectRuntime->effectAsset.effect().particleTypes().at(pixelpart::id_t(particleTypeId));

		pixelpart_gms2::particleTypePropertyPtrString = pixelpart_gms2::toBufferString(
			&particleType.colorVariance());
	}
	catch(const std::exception& e) {
		pixelpart_gms2::lastError = std::string(e.what());
		pixelpart_gms2::particleTypePropertyPtrString = pixelpart_gms2::nullPointerString;
	}

	return pixelpart_gms2::particleTypePropertyPtrString.c_str();
}

GMS2_EXPORT pixelpart_gms2::const_string GMS2_API pixelpart_particle_type_get_opacity_variance(pixelpart_gms2::string runtimePtr, pixelpart_gms2::real particleTypeId) {
	pixelpart_gms2::EffectRuntime* effectRuntime = reinterpret_cast<pixelpart_gms2::EffectRuntime*>(runtimePtr);
	if(!effectRuntime) {
		pixelpart_gms2::lastError = pixelpart_gms2::invalidEffectRuntimeError;
		pixelpart_gms2::particleTypePropertyPtrString = pixelpart_gms2::nullPointerString;

		return pixelpart_gms2::particleTypePropertyPtrString.c_str();
	}

	try {
		pixelpart::ParticleType& particleType =
			effectRuntime->effectAsset.effect().particleTypes().at(pixelpart::id_t(particleTypeId));

		pixelpart_gms2::particleTypePropertyPtrString = pixelpart_gms2::toBufferString(
			&particleType.opacityVariance());
	}
	catch(const std::exception& e) {
		pixelpart_gms2::lastError = std::string(e.what());
		pixelpart_gms2::particleTypePropertyPtrString = pixelpart_gms2::nullPointerString;
	}

	return pixelpart_gms2::particleTypePropertyPtrString.c_str();
}
}
