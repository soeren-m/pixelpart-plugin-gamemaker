#ifndef COMMON_H
#define COMMON_H

#include <cstdint>
#include <cstring>
#include <string>
#include <charconv>

#ifdef __EMSCRIPTEN__
#include <emscripten.h>
#endif

#if defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(_WIN64)
	#define GM_API
	#define GM_EXPORT __declspec(dllexport)
#elif defined(__EMSCRIPTEN__)
	#define GM_API
	#define GM_EXPORT EMSCRIPTEN_KEEPALIVE
#else
	#define GM_API
	#define GM_EXPORT
#endif

namespace pixelpart_gm {
using real = double;
using string = char*;
using const_string = const char*;

std::string ptrToString(void* ptr);

template <typename T>
T* parsePtr(const char* str) {
	std::uintptr_t ptrValue;
	std::from_chars_result result = std::from_chars(str, str + std::strlen(str), ptrValue, 16);
	if(result.ec != std::errc()) {
		return nullptr;
	}

	return reinterpret_cast<T*>(ptrValue);
}
}

#endif
