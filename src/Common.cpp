#include "Common.h"
#include <cstdint>
#include <sstream>
#include <iomanip>

namespace pixelpart_gms2 {
const std::string nullPointerString = "0000000000000000";

std::string toBufferString(void* ptr) {
	std::stringstream stream;
	stream << std::hex << reinterpret_cast<std::uint64_t>(ptr);

	return stream.str();
}
}