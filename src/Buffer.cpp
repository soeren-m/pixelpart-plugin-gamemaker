#include "Buffer.h"

namespace pixelpart_gms2 {
Buffer::Buffer(char* ptr) : pointer(ptr) {

}

void Buffer::seek(std::ptrdiff_t count) {
	pointer += count;
}
}