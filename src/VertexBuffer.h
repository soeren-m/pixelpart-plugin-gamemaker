#ifndef VERTEX_BUFFER_H
#define VERTEX_BUFFER_H

#include "Buffer.h"
#include "pixelpart-runtime/common/Math.h"

namespace pixelpart_gm {
class VertexBuffer : Buffer {
public:
	VertexBuffer(char* ptr);

	void addVertex(const pixelpart::float3_t& position,
		const pixelpart::float4_t& color,
		const pixelpart::float2_t& textureCoord,
		pixelpart::float_t life,
		std::uint32_t id);
};
}

#endif
