#include "VertexBuffer.h"
#include <cstdint>

namespace pixelpart_gms2 {
VertexBuffer::VertexBuffer(char* ptr) : Buffer(ptr) {

}

void VertexBuffer::addVertex(glm::vec3 position,
	glm::vec4 color, glm::vec2 textureCoord,
	glm::vec3 velocity, float life, float id) {
	write(position.x);
	write(position.y);
	write(static_cast<std::uint8_t>(color.r * 255.0f));
	write(static_cast<std::uint8_t>(color.g * 255.0f));
	write(static_cast<std::uint8_t>(color.b * 255.0f));
	write(static_cast<std::uint8_t>(color.a * 255.0f));
	write(textureCoord);
	write(velocity);
	write(life);
	write(id);
}
}