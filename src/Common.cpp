#include "Common.h"
#include <cstdint>
#include <sstream>
#include <iomanip>

namespace pixelpart_gms2 {
std::string toBufferString(void* ptr) {
	std::stringstream stream;
	stream << std::hex << reinterpret_cast<std::uint64_t>(ptr);

	return stream.str();
}
}