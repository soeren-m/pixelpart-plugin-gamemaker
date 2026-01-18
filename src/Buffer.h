#ifndef BUFFER_H
#define BUFFER_H

#include <cstddef>

namespace pixelpart_gm {
class Buffer {
public:
	Buffer(char* ptr);

	template <typename T>
	T read() {
		T value = *reinterpret_cast<T*>(pointer);
		pointer += sizeof(T);

		return value;
	}

	template <typename T>
	T peek() {
		return *reinterpret_cast<T*>(pointer);
	}

	template <typename T>
	void write(T value) {
		*reinterpret_cast<T*>(pointer) = value;
		pointer += sizeof(T);
	}

	template <typename T>
	void poke(T value) {
		*reinterpret_cast<T*>(pointer) = value;
	}

	void writeString(const char* str);

	void seek(std::ptrdiff_t count);

	char* ptr() const;

private:
	char* pointer = nullptr;
};
}

#endif
