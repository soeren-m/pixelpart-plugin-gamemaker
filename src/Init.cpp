#include "Common.h"
#include "Error.h"
#include "EffectRuntime.h"
#include "pixelpart-runtime/common/StdThreadPool.h"
#include "pixelpart-runtime/effect/ComputeGraph.h"
#include <memory>
#include <exception>

extern "C" {
GM_EXPORT pixelpart_gm::real pixelpart_init() {
	try {
#ifdef PIXELPART_RUNTIME_MULTITHREADING
		pixelpart_gm::threadPool = std::make_shared<pixelpart::StdThreadPool>(
			std::thread::hardware_concurrency());
#endif

		pixelpart::ComputeGraph::nodeFactory.registerBuiltInNodes();

		return 1;
	}
	catch(const std::exception& e) {
		pixelpart_gm::lastError = std::string(e.what());
	}

	return -1;
}

GM_EXPORT pixelpart_gm::real pixelpart_shutdown() {
#ifdef PIXELPART_RUNTIME_MULTITHREADING
	pixelpart_gm::threadPool = nullptr;
#endif

	return 1;
}
}
