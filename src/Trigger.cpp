#include "Common.h"
#include "Error.h"
#include "Buffer.h"
#include "EffectRuntime.h"
#include "pixelpart-runtime/common/Id.h"
#include "pixelpart-runtime/effect/Trigger.h"
#include "pixelpart-runtime/effect/TriggerCollection.h"
#include <cstdlib>
#include <string>
#include <vector>
#include <algorithm>
#include <exception>

extern "C" {
GMS2_EXPORT pixelpart_gms2::real GMS2_API pixelpart_get_trigger_count(pixelpart_gms2::string runtimePtr) {
	pixelpart_gms2::EffectRuntime* effectRuntime = pixelpart_gms2::parsePtr<pixelpart_gms2::EffectRuntime>(runtimePtr);
	if(!effectRuntime) {
		pixelpart_gms2::lastError = pixelpart_gms2::invalidEffectRuntimeError;
		return -1;
	}

	return static_cast<pixelpart_gms2::real>(effectRuntime->effectAsset.effect().triggers().size());
}

GMS2_EXPORT pixelpart_gms2::real GMS2_API pixelpart_get_triggers(pixelpart_gms2::string runtimePtr, pixelpart_gms2::string idBufferPtr, pixelpart_gms2::string nameBufferPtr) {
	pixelpart_gms2::EffectRuntime* effectRuntime = pixelpart_gms2::parsePtr<pixelpart_gms2::EffectRuntime>(runtimePtr);
	if(!effectRuntime) {
		pixelpart_gms2::lastError = pixelpart_gms2::invalidEffectRuntimeError;
		return -1;
	}
	else if(!idBufferPtr || !nameBufferPtr) {
		pixelpart_gms2::lastError = pixelpart_gms2::invalidArgumentError;
		return -1;
	}

	const pixelpart::TriggerCollection& triggers = effectRuntime->effectAsset.effect().triggers();

	std::vector<pixelpart::id_t> triggerIds;
	triggerIds.reserve(triggers.size());
	for(const auto& entry : triggers) {
		triggerIds.push_back(entry.first);
	}

	std::sort(triggerIds.begin(), triggerIds.end());

	pixelpart_gms2::Buffer idBuffer(idBufferPtr);
	pixelpart_gms2::Buffer nameBuffer(nameBufferPtr);

	for(pixelpart::id_t triggerId : triggerIds) {
		const pixelpart::Trigger& trigger = triggers.at(triggerId);

		idBuffer.write(triggerId.value());
		nameBuffer.writeString(trigger.name().c_str());
	}

	return 1;
}

GMS2_EXPORT pixelpart_gms2::real GMS2_API pixelpart_activate_trigger(pixelpart_gms2::string runtimePtr, pixelpart_gms2::real triggerId) {
	pixelpart_gms2::EffectRuntime* effectRuntime = pixelpart_gms2::parsePtr<pixelpart_gms2::EffectRuntime>(runtimePtr);
	if(!effectRuntime || !effectRuntime->effectEngine) {
		pixelpart_gms2::lastError = pixelpart_gms2::invalidEffectRuntimeError;
		return -1;
	}

	effectRuntime->effectEngine->activateTrigger(pixelpart::id_t(triggerId));

	return 1;
}

GMS2_EXPORT pixelpart_gms2::real GMS2_API pixelpart_is_trigger_activated(pixelpart_gms2::string runtimePtr, pixelpart_gms2::real triggerId) {
	pixelpart_gms2::EffectRuntime* effectRuntime = pixelpart_gms2::parsePtr<pixelpart_gms2::EffectRuntime>(runtimePtr);
	if(!effectRuntime || !effectRuntime->effectEngine) {
		pixelpart_gms2::lastError = pixelpart_gms2::invalidEffectRuntimeError;
		return -1;
	}

	return effectRuntime->effectEngine->context().triggerActivated(pixelpart::id_t(triggerId)) ? 1 : 0;
}
}
