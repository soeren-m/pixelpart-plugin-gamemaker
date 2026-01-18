#include "Common.h"

namespace pixelpart_gm {
std::string ptrToString(void* ptr) {
	static const std::size_t bufferSize = 128;
	static char buffer[bufferSize];

	std::to_chars_result result =
		std::to_chars(buffer, buffer + bufferSize, reinterpret_cast<std::uintptr_t>(ptr), 16);

	return result.ec == std::errc()
		? std::string(buffer, result.ptr - buffer)
		: std::string();
}
}
