if(ANDROID)
	target_sources(pixelpart-gamemaker PRIVATE
		AndroidNativeLib.cpp)
elseif(IOS)
	target_sources(pixelpart-gamemaker PRIVATE
		PixelpartiOS.mm)
else()
	target_sources(pixelpart-gamemaker PRIVATE
		AnimatedPropertyFloat.cpp
		AnimatedPropertyFloat2.cpp
		AnimatedPropertyFloat3.cpp
		AnimatedPropertyFloat4.cpp
		Buffer.cpp
		BuiltInMaterial.cpp
		Collider.cpp
		Common.cpp
		EffectEvent.cpp
		EffectInput.cpp
		EffectRuntime.cpp
		EffectTrigger.cpp
		Error.cpp
		ForceField.cpp
		Init.cpp
		LightSource.cpp
		Node.cpp
		ParticleEmitter.cpp
		ParticleType.cpp
		Rendering.cpp
		Resources.cpp
		StaticPropertyBool.cpp
		StaticPropertyFloat.cpp
		StaticPropertyFloat2.cpp
		StaticPropertyFloat3.cpp
		StaticPropertyFloat4.cpp
		StaticPropertyInt.cpp)
endif()
