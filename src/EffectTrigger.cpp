#include "Common.h"
#include "Error.h"
#include "Buffer.h"
#include "EffectRuntime.h"
#include "pixelpart-runtime/common/Id.h"
#include "pixelpart-runtime/effect/EffectTrigger.h"
#include "pixelpart-runtime/effect/EffectTriggerCollection.h"
#include <cstdlib>
#include <string>
#include <vector>
#include <algorithm>
#include <exception>

extern "C" {
GM_EXPORT pixelpart_gm::real GM_API pixelpart_get_effect_trigger_count(pixelpart_gm::string runtimePtr) {
	pixelpart_gm::EffectRuntime* effectRuntime = pixelpart_gm::parsePtr<pixelpart_gm::EffectRuntime>(runtimePtr);
	if(!effectRuntime) {
		pixelpart_gm::lastError = pixelpart_gm::invalidEffectRuntimeError;
		return -1;
	}

	return static_cast<pixelpart_gm::real>(effectRuntime->effectAsset.effect().triggers().size());
}

GM_EXPORT pixelpart_gm::real GM_API pixelpart_get_effect_triggers(pixelpart_gm::string runtimePtr, pixelpart_gm::string idBufferPtr, pixelpart_gm::string nameBufferPtr) {
	pixelpart_gm::EffectRuntime* effectRuntime = pixelpart_gm::parsePtr<pixelpart_gm::EffectRuntime>(runtimePtr);
	if(!effectRuntime) {
		pixelpart_gm::lastError = pixelpart_gm::invalidEffectRuntimeError;
		return -1;
	}
	else if(!idBufferPtr || !nameBufferPtr) {
		pixelpart_gm::lastError = pixelpart_gm::invalidArgumentError;
		return -1;
	}

	const pixelpart::EffectTriggerCollection& triggers = effectRuntime->effectAsset.effect().triggers();

	std::vector<pixelpart::id_t> triggerIds;
	triggerIds.reserve(triggers.size());
	for(const auto& entry : triggers) {
		triggerIds.push_back(entry.first);
	}

	std::sort(triggerIds.begin(), triggerIds.end());

	pixelpart_gm::Buffer idBuffer(idBufferPtr);
	pixelpart_gm::Buffer nameBuffer(nameBufferPtr);

	for(pixelpart::id_t triggerId : triggerIds) {
		const pixelpart::EffectTrigger& trigger = triggers.at(triggerId);

		idBuffer.write(triggerId.value());
		nameBuffer.writeString(trigger.name().c_str());
	}

	return 1;
}

GM_EXPORT pixelpart_gm::real GM_API pixelpart_activate_effect_trigger(pixelpart_gm::string runtimePtr, pixelpart_gm::real triggerId) {
	pixelpart_gm::EffectRuntime* effectRuntime = pixelpart_gm::parsePtr<pixelpart_gm::EffectRuntime>(runtimePtr);
	if(!effectRuntime || !effectRuntime->effectEngine) {
		pixelpart_gm::lastError = pixelpart_gm::invalidEffectRuntimeError;
		return -1;
	}

	effectRuntime->effectEngine->activateTrigger(pixelpart::id_t(triggerId));

	return 1;
}

GM_EXPORT pixelpart_gm::real GM_API pixelpart_is_effect_trigger_activated(pixelpart_gm::string runtimePtr, pixelpart_gm::real triggerId) {
	pixelpart_gm::EffectRuntime* effectRuntime = pixelpart_gm::parsePtr<pixelpart_gm::EffectRuntime>(runtimePtr);
	if(!effectRuntime || !effectRuntime->effectEngine) {
		pixelpart_gm::lastError = pixelpart_gm::invalidEffectRuntimeError;
		return -1;
	}

	return effectRuntime->effectEngine->context().triggerActivated(pixelpart::id_t(triggerId)) ? 1 : 0;
}
}
