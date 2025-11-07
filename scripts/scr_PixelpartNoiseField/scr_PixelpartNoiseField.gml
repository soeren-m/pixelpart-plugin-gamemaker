function PixelpartNoiseField(_effect_ptr, _node_id) : PixelpartForceField(_effect_ptr, _node_id) constructor
{
	noise_octaves = new PixelpartStaticPropertyInt(
		ptr(pixelpart_noise_field_get_noise_octaves(_effect_ptr, _node_id)));
	noise_frequency = new PixelpartAnimatedPropertyFloat(
		ptr(pixelpart_noise_field_get_noise_frequency(_effect_ptr, _node_id)));
	noise_persistence = new PixelpartAnimatedPropertyFloat(
		ptr(pixelpart_noise_field_get_noise_persistence(_effect_ptr, _node_id)));
	noise_lacunarity = new PixelpartAnimatedPropertyFloat(
		ptr(pixelpart_noise_field_get_noise_lacunarity(_effect_ptr, _node_id)));
	noise_animation_time_scale = new PixelpartStaticPropertyFloat(
		ptr(pixelpart_noise_field_get_noise_animation_time_scale(_effect_ptr, _node_id)));
	noise_animation_time_base = new PixelpartStaticPropertyFloat(
		ptr(pixelpart_noise_field_get_noise_animation_time_base(_effect_ptr, _node_id)));

	static set_noise_animated = function(_mode)
	{
		pixelpart_noise_field_set_noise_animated(effect_ptr, node_id, _mode);
	}
	static is_noise_animated = function()
	{
		return pixelpart_noise_field_is_noise_animated(effect_ptr, node_id);
	}
}
