function PixelpartNode(_effect_ptr, _node_id) constructor
{
	effect_ptr = _effect_ptr;
	node_id = _node_id;
	position = new PixelpartAnimatedPropertyFloat3(
		ptr(pixelpart_node_get_position(_effect_ptr, _node_id)));
	rotation = new PixelpartAnimatedPropertyFloat3(
		ptr(pixelpart_node_get_rotation(_effect_ptr, _node_id)));
	scale = new PixelpartAnimatedPropertyFloat3(
		ptr(pixelpart_node_get_scale(_effect_ptr, _node_id)));

	static get_type = function()
	{
		return pixelpart_node_get_type(effect_ptr, node_id);
	}

	static get_id = function()
	{
		return node_id;
	}

	static get_parent_id = function()
	{
		return pixelpart_node_get_parent_id(effect_ptr, node_id);
	}

	static get_name = function()
	{
		return pixelpart_node_get_name(effect_ptr, node_id);
	}

	static set_lifetime_start = function(_start)
	{
		pixelpart_node_set_start(effect_ptr, node_id, _start);
	}
	static get_lifetime_start = function()
	{
		return pixelpart_node_get_start(effect_ptr, node_id);
	}

	static set_lifetime_duration = function(_duration)
	{
		pixelpart_node_set_duration(effect_ptr, node_id, _duration);
	}
	static get_lifetime_duration = function()
	{
		return pixelpart_node_get_duration(effect_ptr, node_id);
	}

	static set_repeat = function(_repeat)
	{
		pixelpart_node_set_repeat(effect_ptr, node_id, _repeat);
	}
	static is_repeating = function()
	{
		return pixelpart_node_is_repeating(effect_ptr, node_id);
	}

	static is_active = function()
	{
		return pixelpart_node_is_active(effect_ptr, node_id);
	}

	static get_local_time = function()
	{
		return pixelpart_node_get_local_time(effect_ptr, node_id);
	}
}