#ifndef VERTEX_BUFFER_H
#define VERTEX_BUFFER_H

#include "Buffer.h"
#include "pixelpart-runtime/common/Math.h"

namespace pixelpart_gms2 {
class VertexBuffer : Buffer {
public:
	VertexBuffer(char* ptr);

	void addVertex(glm::vec3 position,
		glm::vec4 color, glm::vec2 textureCoord,
		glm::vec3 velocity, float life, float id);

private:
	char* pointer = nullptr;
};
}

#endif