#include "Common.h"
#include "Error.h"
#include "Buffer.h"
#include "pixelpart-runtime/effect/BuiltInMaterialMetadata.h"
#include "pixelpart-runtime/effect/BuiltInMaterialRepository.h"
#include <string>

namespace pixelpart_gm {
pixelpart::BuiltInMaterialRepository builtInMaterialRepository;
}

extern "C" {
GM_EXPORT pixelpart_gm::real GM_API pixelpart_get_builtin_material_parameter_count(pixelpart_gm::string materialName) {
	const pixelpart::BuiltInMaterialMetadata* builtInMaterial = pixelpart_gm::builtInMaterialRepository.material(std::string(materialName));
	if(!builtInMaterial) {
		pixelpart_gm::lastError = pixelpart_gm::resourceNotFoundError;
		return -1;
	}

	return static_cast<pixelpart_gm::real>(builtInMaterial->parameters().size());
}

GM_EXPORT pixelpart_gm::real GM_API pixelpart_get_builtin_material_parameters(pixelpart_gm::string materialName, pixelpart_gm::string idBufferPtr, pixelpart_gm::string nameBufferPtr) {
	if(!idBufferPtr || !nameBufferPtr) {
		pixelpart_gm::lastError = pixelpart_gm::invalidArgumentError;
		return -1;
	}

	const pixelpart::BuiltInMaterialMetadata* builtInMaterial = pixelpart_gm::builtInMaterialRepository.material(std::string(materialName));
	if(!builtInMaterial) {
		pixelpart_gm::lastError = pixelpart_gm::resourceNotFoundError;
		return -1;
	}

	pixelpart_gm::Buffer idBuffer(idBufferPtr);
	pixelpart_gm::Buffer nameBuffer(nameBufferPtr);

	for(const auto& [parameterId, parameter] : builtInMaterial->parameters()) {
		idBuffer.write(parameterId.value());
		nameBuffer.writeString(parameter.name().c_str());
	}

	return 1;
}
}
