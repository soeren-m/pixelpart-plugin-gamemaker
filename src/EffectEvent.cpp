#include "Common.h"
#include "Error.h"
#include "Buffer.h"
#include "EffectRuntime.h"
#include "pixelpart-runtime/types/Id.h"
#include "pixelpart-runtime/effect/EffectEvent.h"
#include "pixelpart-runtime/effect/EffectEventCollection.h"
#include <vector>
#include <algorithm>

extern "C" {
GM_EXPORT pixelpart_gm::real GM_API pixelpart_get_effect_event_count(pixelpart_gm::string runtimePtr) {
	pixelpart_gm::EffectRuntime* effectRuntime = pixelpart_gm::parsePtr<pixelpart_gm::EffectRuntime>(runtimePtr);
	if(!effectRuntime) {
		pixelpart_gm::lastError = pixelpart_gm::invalidEffectRuntimeError;
		return -1;
	}

	return static_cast<pixelpart_gm::real>(effectRuntime->effectAsset.effect().events().size());
}

GM_EXPORT pixelpart_gm::real GM_API pixelpart_get_effect_events(pixelpart_gm::string runtimePtr, pixelpart_gm::string idBufferPtr, pixelpart_gm::string nameBufferPtr) {
	pixelpart_gm::EffectRuntime* effectRuntime = pixelpart_gm::parsePtr<pixelpart_gm::EffectRuntime>(runtimePtr);
	if(!effectRuntime) {
		pixelpart_gm::lastError = pixelpart_gm::invalidEffectRuntimeError;
		return -1;
	}
	else if(!idBufferPtr || !nameBufferPtr) {
		pixelpart_gm::lastError = pixelpart_gm::invalidArgumentError;
		return -1;
	}

	const pixelpart::EffectEventCollection& events = effectRuntime->effectAsset.effect().events();

	std::vector<pixelpart::id_t> eventIds;
	eventIds.reserve(events.size());
	for(const auto& entry : events) {
		eventIds.push_back(entry.first);
	}

	std::sort(eventIds.begin(), eventIds.end());

	pixelpart_gm::Buffer idBuffer(idBufferPtr);
	pixelpart_gm::Buffer nameBuffer(nameBufferPtr);

	for(pixelpart::id_t eventId : eventIds) {
		const pixelpart::EffectEvent& event = events.at(eventId);

		idBuffer.write(eventId.value());
		nameBuffer.writeString(event.name().c_str());
	}

	return 1;
}

GM_EXPORT pixelpart_gm::real GM_API pixelpart_get_invoked_effect_events(pixelpart_gm::string runtimePtr, pixelpart_gm::string idBufferPtr) {
	pixelpart_gm::EffectRuntime* effectRuntime = pixelpart_gm::parsePtr<pixelpart_gm::EffectRuntime>(runtimePtr);
	if(!effectRuntime || !effectRuntime->effectEngine) {
		pixelpart_gm::lastError = pixelpart_gm::invalidEffectRuntimeError;
		return -1;
	}
    else if(!idBufferPtr) {
		pixelpart_gm::lastError = pixelpart_gm::invalidArgumentError;
		return -1;
	}

    pixelpart_gm::Buffer idBuffer(idBufferPtr);
	for(pixelpart::id_t eventId : effectRuntime->invokedEventIds) {
        idBuffer.write(eventId.value());
	}

	return static_cast<pixelpart_gm::real>(effectRuntime->invokedEventIds.size());
}
}
