/// @desc Force field that generates random turbulent motion.
/// Noise fields are perfect for creating organic and unpredictable patterns.
/// @param {string} _effect_ptr Pointer to internal effect runtime object
/// @param {real} _node_id Node ID
function PixelpartNoiseField(_effect_ptr, _node_id) : PixelpartForceField(_effect_ptr, _node_id) constructor
{
	// How many layers of noise are blended together to produce the final velocity vector.
	noise_octaves = new PixelpartStaticPropertyInt(
		pixelpart_noise_field_get_noise_octaves(_effect_ptr, _node_id));

	// Base frequency of the noise generation.
	// Higher values produce more turbulent noise fields.
	noise_frequency = new PixelpartAnimatedPropertyFloat(
		pixelpart_noise_field_get_noise_frequency(_effect_ptr, _node_id));

	// How much the amplitude changes after each noise octave.
	noise_persistence = new PixelpartAnimatedPropertyFloat(
		pixelpart_noise_field_get_noise_persistence(_effect_ptr, _node_id));

	// How much the frequency changes after each noise octave.
	noise_lacunarity = new PixelpartAnimatedPropertyFloat(
		pixelpart_noise_field_get_noise_lacunarity(_effect_ptr, _node_id));

	// How fast the noise field changes.
	noise_animation_time_scale = new PixelpartStaticPropertyFloat(
		pixelpart_noise_field_get_noise_animation_time_scale(_effect_ptr, _node_id));

	// Time offset of the noise animation.
	noise_animation_time_base = new PixelpartStaticPropertyFloat(
		pixelpart_noise_field_get_noise_animation_time_base(_effect_ptr, _node_id));

	/// @desc Set whether the noise field is animated.
	/// @param {bool} _mode Whether the noise field is animated
	static set_noise_animated = function(_mode)
	{
		pixelpart_noise_field_set_noise_animated(effect_ptr, node_id, _mode);
	}

	/// @desc Whether the noise field is animated.
	/// @returns {bool} Whether the noise field is animated
	static is_noise_animated = function()
	{
		return bool(pixelpart_noise_field_is_noise_animated(effect_ptr, node_id));
	}
}
