#include "Common.h"
#include "Error.h"
#include "EffectRuntime.h"
#include "pixelpart-runtime/common/StdThreadPool.h"
#include "pixelpart-runtime/effect/ComputeGraph.h"
#include <memory>
#include <exception>

extern "C" {
GMS2_EXPORT pixelpart_gms2::real pixelpart_init() {
	try {
#ifdef PIXELPART_RUNTIME_MULTITHREADING
		pixelpart_gms2::threadPool = std::make_shared<pixelpart::StdThreadPool>(
			std::thread::hardware_concurrency());
#endif

		pixelpart::ComputeGraph::nodeFactory.registerBuiltInNodes();

		return 1;
	}
	catch(const std::exception& e) {
		pixelpart_gms2::lastError = std::string(e.what());
	}

	return -1;
}

GMS2_EXPORT pixelpart_gms2::real pixelpart_shutdown() {
#ifdef PIXELPART_RUNTIME_MULTITHREADING
	pixelpart_gms2::threadPool = nullptr;
#endif

	return 1;
}
}
