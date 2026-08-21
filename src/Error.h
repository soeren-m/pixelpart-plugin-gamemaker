#ifndef ERROR_H
#define ERROR_H

#include <string>

namespace pixelpart_gm {
extern std::string lastError;

extern const std::string invalidEffectResourceError;
extern const std::string invalidEffectRuntimeError;
extern const std::string invalidPropertyError;
extern const std::string invalidArgumentError;
extern const std::string resourceNotFoundError;
}

#endif
