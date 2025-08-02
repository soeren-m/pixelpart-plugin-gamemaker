#ifndef COMMON_H
#define COMMON_H

#include <string>

#if defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(_WIN64)
	#define GMS2_API
	#define GMS2_EXPORT __declspec(dllexport)
#else
	#define GMS2_API
	#define GMS2_EXPORT
#endif

namespace pixelpart_gms2 {
using real = double;
using string = char*;
using const_string = const char*;

std::string toBufferString(void* ptr);
}

#endif