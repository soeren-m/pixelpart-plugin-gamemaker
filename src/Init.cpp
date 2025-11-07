#include "Common.h"
#include "Error.h"
#include "pixelpart-runtime/computegraph/ComputeGraph.h"
#include <exception>

extern "C" {
GMS2_EXPORT pixelpart_gms2::real pixelpart_init() {
	try {
		pixelpart::ComputeGraph::nodeFactory.registerBuiltInNodes();

		return 1;
	}
	catch(const std::exception& e) {
		pixelpart_gms2::lastError = std::string(e.what());
	}

	return -1;
}
}
