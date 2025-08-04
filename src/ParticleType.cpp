#include "Common.h"
#include "Error.h"
#include "Buffer.h"
#include "EffectRuntime.h"
#include "pixelpart-runtime/common/Math.h"
#include "pixelpart-runtime/common/Id.h"
#include "pixelpart-runtime/effect/StaticProperty.h"
#include "pixelpart-runtime/effect/AnimatedProperty.h"
#include "pixelpart-runtime/effect/ParticleType.h"
#include <cstdint>
#include <cstring>
#include <string>
#include <algorithm>
#include <exception>

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

	return effectRuntime->effectAsset.effect().particleTypes().contains(particleTypeId) ? 1 : 0;
}

GMS2_EXPORT pixelpart_gms2::real GMS2_API pixelpart_particle_type_get_index(pixelpart_gms2::string runtimePtr, pixelpart_gms2::real particleTypeId) {
	pixelpart_gms2::EffectRuntime* effectRuntime = reinterpret_cast<pixelpart_gms2::EffectRuntime*>(runtimePtr);
	if(!effectRuntime) {
		pixelpart_gms2::lastError = pixelpart_gms2::invalidEffectRuntimeError;
		return -1;
	}

	std::uint32_t particleTypeIndex = effectRuntime->effectAsset.effect().particleTypes().indexOf(particleTypeId);
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

GMS2_EXPORT pixelpart_gms2::real GMS2_API pixelpart_particle_type_get_name(pixelpart_gms2::string runtimePtr, pixelpart_gms2::real particleTypeId, pixelpart_gms2::string bufferPtr, pixelpart_gms2::real bufferSize) {
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
		const pixelpart::ParticleType& particleType =
			effectRuntime->effectAsset.effect().particleTypes().at(particleTypeId);
		if(particleType.name().empty()) {
			return 0;
		}

		std::size_t size = std::min(particleType.name().size(), static_cast<std::size_t>(bufferSize) - 1);
		std::memcpy(bufferPtr, particleType.name().c_str(), size);
		bufferPtr[size] = '\0';

		return static_cast<pixelpart_gms2::real>(size);
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
}