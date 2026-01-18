#include "Error.h"
#include "Common.h"

namespace pixelpart_gm {
std::string lastError ="";

const std::string invalidEffectRuntimeError = "Invalid effect runtime";
const std::string invalidPropertyError = "Invalid property";
const std::string invalidArgumentError = "Invalid argument";
}

extern "C" {
GM_EXPORT pixelpart_gm::const_string GM_API pixelpart_last_error() {
	return pixelpart_gm::lastError.c_str();
}
}
