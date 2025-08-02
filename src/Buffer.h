#ifndef BUFFER_H
#define BUFFER_H

namespace pixelpart_gms2 {
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
	void write(T value) {
		*reinterpret_cast<T*>(pointer) = value;
		pointer += sizeof(T);
	}

private:
	char* pointer = nullptr;
};
}

#endif