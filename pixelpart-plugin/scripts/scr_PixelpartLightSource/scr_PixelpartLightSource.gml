/// @desc Node that emits light.
/// Light sources illuminate the effect and can be used to model phenomena like sunlight, lamps and torches.
/// Particles with a material that has lighting enabled (for example built-in materials with the suffix Lit)
/// are shaded by light from light sources in the scene.
/// @param {pointer} _effect_ptr Pointer to internal effect runtime object
/// @param {real} _node_id Node ID
function PixelpartLightSource(_effect_ptr, _node_id) : PixelpartNode(_effect_ptr, _node_id) constructor
{
	// How quickly the light looses intensity on the way to its outer radius.
	attenuation = new PixelpartAnimatedPropertyFloat(
		ptr(pixelpart_light_source_get_attenuation(_effect_ptr, _node_id)));

	// Color of the light emitted by the light source.
	color = new PixelpartAnimatedPropertyFloat4(
		ptr(pixelpart_light_source_get_color(_effect_ptr, _node_id)));

	// How strongly the light shines.
	intensity = new PixelpartAnimatedPropertyFloat(
		ptr(pixelpart_light_source_get_intensity(_effect_ptr, _node_id)));
}
