function PixelpartForceField(_effect_ptr, _node_id) : PixelpartNode(_effect_ptr, _node_id) constructor
{
	strength = new PixelpartAnimatedPropertyFloat(
		ptr(pixelpart_force_field_get_strength(_effect_ptr, _node_id)));

	static set_infinite = function(_mode)
	{
		pixelpart_force_field_set_infinite(effect_ptr, node_id, _mode);
	}
	static is_infinite = function()
	{
		return pixelpart_force_field_is_infinite(effect_ptr, node_id);
	}
}
