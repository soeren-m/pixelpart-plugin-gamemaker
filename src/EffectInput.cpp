#include "Common.h"
#include "Error.h"
#include "Buffer.h"
#include "EffectRuntime.h"
#include "pixelpart-runtime/types/Id.h"
#include "pixelpart-runtime/types/VariantValue.h"
#include "pixelpart-runtime/effect/EffectInput.h"
#include <cstdlib>
#include <string>
#include <vector>
#include <algorithm>
#include <exception>

extern "C" {
GM_EXPORT pixelpart_gm::real GM_API pixelpart_get_effect_input_count(pixelpart_gm::string runtimePtr) {
	pixelpart_gm::EffectRuntime* effectRuntime = pixelpart_gm::parsePtr<pixelpart_gm::EffectRuntime>(runtimePtr);
	if(!effectRuntime) {
		pixelpart_gm::lastError = pixelpart_gm::invalidEffectRuntimeError;
		return -1;
	}

	return static_cast<pixelpart_gm::real>(effectRuntime->effectAsset.effect().inputs().size());
}

GM_EXPORT pixelpart_gm::real GM_API pixelpart_get_effect_inputs(pixelpart_gm::string runtimePtr, pixelpart_gm::string idBufferPtr, pixelpart_gm::string typeBufferPtr, pixelpart_gm::string nameBufferPtr) {
	pixelpart_gm::EffectRuntime* effectRuntime = pixelpart_gm::parsePtr<pixelpart_gm::EffectRuntime>(runtimePtr);
	if(!effectRuntime) {
		pixelpart_gm::lastError = pixelpart_gm::invalidEffectRuntimeError;
		return -1;
	}
	else if(!idBufferPtr || !typeBufferPtr || !nameBufferPtr) {
		pixelpart_gm::lastError = pixelpart_gm::invalidArgumentError;
		return -1;
	}

	const pixelpart::EffectInputCollection& inputs = effectRuntime->effectAsset.effect().inputs();

	std::vector<pixelpart::id_t> inputIds;
	inputIds.reserve(inputs.size());
	for(const auto& entry : inputs) {
		inputIds.push_back(entry.first);
	}

	std::sort(inputIds.begin(), inputIds.end());

	pixelpart_gm::Buffer idBuffer(idBufferPtr);
	pixelpart_gm::Buffer typeBuffer(typeBufferPtr);
	pixelpart_gm::Buffer nameBuffer(nameBufferPtr);

	for(pixelpart::id_t inputId : inputIds) {
		const pixelpart::EffectInput& input = inputs.at(inputId);

		idBuffer.write(inputId.value());
		typeBuffer.write(static_cast<std::int32_t>(input.value().type()));
		nameBuffer.writeString(input.name().c_str());
	}

	return 1;
}

GM_EXPORT pixelpart_gm::real GM_API pixelpart_set_effect_input_bool(pixelpart_gm::string runtimePtr, pixelpart_gm::real inputId, pixelpart_gm::real value) {
	pixelpart_gm::EffectRuntime* effectRuntime = pixelpart_gm::parsePtr<pixelpart_gm::EffectRuntime>(runtimePtr);
	if(!effectRuntime) {
		pixelpart_gm::lastError = pixelpart_gm::invalidEffectRuntimeError;
		return -1;
	}

	try {
		pixelpart::EffectInput& input = effectRuntime->effectAsset.effect().inputs().at(pixelpart::id_t(inputId));
		input.value(pixelpart::VariantValue::Bool(value));

		effectRuntime->effectAsset.effect().applyInputs();

		return 1;
	}
	catch(const std::exception& e) {
		pixelpart_gm::lastError = std::string(e.what());
	}

	return -1;
}

GM_EXPORT pixelpart_gm::real GM_API pixelpart_set_effect_input_int(pixelpart_gm::string runtimePtr, pixelpart_gm::real inputId, pixelpart_gm::real value) {
	pixelpart_gm::EffectRuntime* effectRuntime = pixelpart_gm::parsePtr<pixelpart_gm::EffectRuntime>(runtimePtr);
	if(!effectRuntime) {
		pixelpart_gm::lastError = pixelpart_gm::invalidEffectRuntimeError;
		return -1;
	}

	try {
		pixelpart::EffectInput& input = effectRuntime->effectAsset.effect().inputs().at(pixelpart::id_t(inputId));
		input.value(pixelpart::VariantValue::Int(static_cast<pixelpart::int_t>(value)));

		effectRuntime->effectAsset.effect().applyInputs();

		return 1;
	}
	catch(const std::exception& e) {
		pixelpart_gm::lastError = std::string(e.what());
	}

	return -1;
}

GM_EXPORT pixelpart_gm::real GM_API pixelpart_set_effect_input_float(pixelpart_gm::string runtimePtr, pixelpart_gm::real inputId, pixelpart_gm::real value) {
	pixelpart_gm::EffectRuntime* effectRuntime = pixelpart_gm::parsePtr<pixelpart_gm::EffectRuntime>(runtimePtr);
	if(!effectRuntime) {
		pixelpart_gm::lastError = pixelpart_gm::invalidEffectRuntimeError;
		return -1;
	}

	try {
		pixelpart::EffectInput& input = effectRuntime->effectAsset.effect().inputs().at(pixelpart::id_t(inputId));
		input.value(pixelpart::VariantValue::Float(static_cast<pixelpart::float_t>(value)));

		effectRuntime->effectAsset.effect().applyInputs();

		return 1;
	}
	catch(const std::exception& e) {
		pixelpart_gm::lastError = std::string(e.what());
	}

	return -1;
}

GM_EXPORT pixelpart_gm::real GM_API pixelpart_set_effect_input_float2(pixelpart_gm::string runtimePtr, pixelpart_gm::real inputId, pixelpart_gm::string valueBufferPtr) {
	pixelpart_gm::EffectRuntime* effectRuntime = pixelpart_gm::parsePtr<pixelpart_gm::EffectRuntime>(runtimePtr);
	if(!effectRuntime) {
		pixelpart_gm::lastError = pixelpart_gm::invalidEffectRuntimeError;
		return -1;
	}
	else if(!valueBufferPtr) {
		pixelpart_gm::lastError = pixelpart_gm::invalidArgumentError;
		return -1;
	}

	pixelpart_gm::Buffer valueBuffer(valueBufferPtr);

	try {
		pixelpart::EffectInput& input = effectRuntime->effectAsset.effect().inputs().at(pixelpart::id_t(inputId));
		input.value(pixelpart::VariantValue::Float2(valueBuffer.read<pixelpart::float2_t>()));

		effectRuntime->effectAsset.effect().applyInputs();

		return 1;
	}
	catch(const std::exception& e) {
		pixelpart_gm::lastError = std::string(e.what());
	}

	return -1;
}

GM_EXPORT pixelpart_gm::real GM_API pixelpart_set_effect_input_float3(pixelpart_gm::string runtimePtr, pixelpart_gm::real inputId, pixelpart_gm::string valueBufferPtr) {
	pixelpart_gm::EffectRuntime* effectRuntime = pixelpart_gm::parsePtr<pixelpart_gm::EffectRuntime>(runtimePtr);
	if(!effectRuntime) {
		pixelpart_gm::lastError = pixelpart_gm::invalidEffectRuntimeError;
		return -1;
	}
	else if(!valueBufferPtr) {
		pixelpart_gm::lastError = pixelpart_gm::invalidArgumentError;
		return -1;
	}

	pixelpart_gm::Buffer valueBuffer(valueBufferPtr);

	try {
		pixelpart::EffectInput& input = effectRuntime->effectAsset.effect().inputs().at(pixelpart::id_t(inputId));
		input.value(pixelpart::VariantValue::Float3(valueBuffer.read<pixelpart::float3_t>()));

		effectRuntime->effectAsset.effect().applyInputs();

		return 1;
	}
	catch(const std::exception& e) {
		pixelpart_gm::lastError = std::string(e.what());
	}

	return -1;
}

GM_EXPORT pixelpart_gm::real GM_API pixelpart_set_effect_input_float4(pixelpart_gm::string runtimePtr, pixelpart_gm::real inputId, pixelpart_gm::string valueBufferPtr) {
	pixelpart_gm::EffectRuntime* effectRuntime = pixelpart_gm::parsePtr<pixelpart_gm::EffectRuntime>(runtimePtr);
	if(!effectRuntime) {
		pixelpart_gm::lastError = pixelpart_gm::invalidEffectRuntimeError;
		return -1;
	}
	else if(!valueBufferPtr) {
		pixelpart_gm::lastError = pixelpart_gm::invalidArgumentError;
		return -1;
	}

	pixelpart_gm::Buffer valueBuffer(valueBufferPtr);

	try {
		pixelpart::EffectInput& input = effectRuntime->effectAsset.effect().inputs().at(pixelpart::id_t(inputId));
		input.value(pixelpart::VariantValue::Float4(valueBuffer.read<pixelpart::float4_t>()));

		effectRuntime->effectAsset.effect().applyInputs();

		return 1;
	}
	catch(const std::exception& e) {
		pixelpart_gm::lastError = std::string(e.what());
	}

	return -1;
}

GM_EXPORT pixelpart_gm::real GM_API pixelpart_get_effect_input_bool(pixelpart_gm::string runtimePtr, pixelpart_gm::real inputId) {
	pixelpart_gm::EffectRuntime* effectRuntime = pixelpart_gm::parsePtr<pixelpart_gm::EffectRuntime>(runtimePtr);
	if(!effectRuntime) {
		pixelpart_gm::lastError = pixelpart_gm::invalidEffectRuntimeError;
		return -1;
	}

	try {
		const pixelpart::EffectInput& input = effectRuntime->effectAsset.effect().inputs().at(pixelpart::id_t(inputId));

		return input.value().toBool() ? 1 : 0;
	}
	catch(const std::exception& e) {
		pixelpart_gm::lastError = std::string(e.what());
	}

	return -1;
}

GM_EXPORT pixelpart_gm::real GM_API pixelpart_get_effect_input_int(pixelpart_gm::string runtimePtr, pixelpart_gm::real inputId) {
	pixelpart_gm::EffectRuntime* effectRuntime = pixelpart_gm::parsePtr<pixelpart_gm::EffectRuntime>(runtimePtr);
	if(!effectRuntime) {
		pixelpart_gm::lastError = pixelpart_gm::invalidEffectRuntimeError;
		return -1;
	}

	try {
		const pixelpart::EffectInput& input = effectRuntime->effectAsset.effect().inputs().at(pixelpart::id_t(inputId));

		return static_cast<pixelpart_gm::real>(input.value().toInt());
	}
	catch(const std::exception& e) {
		pixelpart_gm::lastError = std::string(e.what());
	}

	return -1;
}

GM_EXPORT pixelpart_gm::real GM_API pixelpart_get_effect_input_float(pixelpart_gm::string runtimePtr, pixelpart_gm::real inputId) {
	pixelpart_gm::EffectRuntime* effectRuntime = pixelpart_gm::parsePtr<pixelpart_gm::EffectRuntime>(runtimePtr);
	if(!effectRuntime) {
		pixelpart_gm::lastError = pixelpart_gm::invalidEffectRuntimeError;
		return -1;
	}

	try {
		const pixelpart::EffectInput& input = effectRuntime->effectAsset.effect().inputs().at(pixelpart::id_t(inputId));

		return static_cast<pixelpart_gm::real>(input.value().toFloat());
	}
	catch(const std::exception& e) {
		pixelpart_gm::lastError = std::string(e.what());
	}

	return -1;
}

GM_EXPORT pixelpart_gm::real GM_API pixelpart_get_effect_input_float2(pixelpart_gm::string runtimePtr, pixelpart_gm::real inputId, pixelpart_gm::string valueBufferPtr) {
	pixelpart_gm::EffectRuntime* effectRuntime = pixelpart_gm::parsePtr<pixelpart_gm::EffectRuntime>(runtimePtr);
	if(!effectRuntime) {
		pixelpart_gm::lastError = pixelpart_gm::invalidEffectRuntimeError;
		return -1;
	}

	try {
		const pixelpart::EffectInput& input = effectRuntime->effectAsset.effect().inputs().at(pixelpart::id_t(inputId));

		pixelpart_gm::Buffer valueBuffer(valueBufferPtr);
		valueBuffer.write(input.value().toFloat2());

		return 1;
	}
	catch(const std::exception& e) {
		pixelpart_gm::lastError = std::string(e.what());
	}

	return -1;
}

GM_EXPORT pixelpart_gm::real GM_API pixelpart_get_effect_input_float3(pixelpart_gm::string runtimePtr, pixelpart_gm::real inputId, pixelpart_gm::string valueBufferPtr) {
	pixelpart_gm::EffectRuntime* effectRuntime = pixelpart_gm::parsePtr<pixelpart_gm::EffectRuntime>(runtimePtr);
	if(!effectRuntime) {
		pixelpart_gm::lastError = pixelpart_gm::invalidEffectRuntimeError;
		return -1;
	}

	try {
		const pixelpart::EffectInput& input = effectRuntime->effectAsset.effect().inputs().at(pixelpart::id_t(inputId));

		pixelpart_gm::Buffer valueBuffer(valueBufferPtr);
		valueBuffer.write(input.value().toFloat3());

		return 1;
	}
	catch(const std::exception& e) {
		pixelpart_gm::lastError = std::string(e.what());
	}

	return -1;
}

GM_EXPORT pixelpart_gm::real GM_API pixelpart_get_effect_input_float4(pixelpart_gm::string runtimePtr, pixelpart_gm::real inputId, pixelpart_gm::string valueBufferPtr) {
	pixelpart_gm::EffectRuntime* effectRuntime = pixelpart_gm::parsePtr<pixelpart_gm::EffectRuntime>(runtimePtr);
	if(!effectRuntime) {
		pixelpart_gm::lastError = pixelpart_gm::invalidEffectRuntimeError;
		return -1;
	}

	try {
		const pixelpart::EffectInput& input = effectRuntime->effectAsset.effect().inputs().at(pixelpart::id_t(inputId));

		pixelpart_gm::Buffer valueBuffer(valueBufferPtr);
		valueBuffer.write(input.value().toFloat4());

		return 1;
	}
	catch(const std::exception& e) {
		pixelpart_gm::lastError = std::string(e.what());
	}

	return -1;
}
}
