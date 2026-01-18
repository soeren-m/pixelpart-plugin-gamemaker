#include "VertexBuffer.h"
#include <cstdint>

namespace pixelpart_gm {
VertexBuffer::VertexBuffer(char* ptr) : Buffer(ptr) {

}

void VertexBuffer::addVertex(const pixelpart::float3_t& position,
	const pixelpart::float4_t& color,
	const pixelpart::float2_t& textureCoord,
	pixelpart::float_t life,
	std::uint32_t id) {
	write(static_cast<float>(position.x));
	write(static_cast<float>(position.y));
	write(static_cast<std::uint8_t>(color.r * 255.0));
	write(static_cast<std::uint8_t>(color.g * 255.0));
	write(static_cast<std::uint8_t>(color.b * 255.0));
	write(static_cast<std::uint8_t>(color.a * 255.0));
	write(static_cast<float>(textureCoord.x));
	write(static_cast<float>(textureCoord.y));
	write(static_cast<float>(life));
	write(static_cast<float>(id));
}
}
