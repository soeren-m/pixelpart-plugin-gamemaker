#include "Buffer.h"
#include <cstring>

namespace pixelpart_gms2 {
Buffer::Buffer(char* ptr) : pointer(ptr) {

}

void Buffer::writeString(const char* str) {
	std::strcpy(pointer, str);
	pointer += std::strlen(str) + 1;
}

void Buffer::seek(std::ptrdiff_t count) {
	pointer += count;
}

char* Buffer::ptr() const {
	return pointer;
}
}