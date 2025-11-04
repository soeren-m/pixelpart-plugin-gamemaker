#include "Error.h"
#include "Common.h"

namespace pixelpart_gms2 {
std::string lastError ="";

const std::string invalidEffectRuntimeError = "Invalid effect runtime";
const std::string invalidPropertyError = "Invalid property";
const std::string invalidArgumentError = "Invalid argument";
}

extern "C" {
GMS2_EXPORT pixelpart_gms2::const_string GMS2_API pixelpart_last_error() {
	return pixelpart_gms2::lastError.c_str();
}
}