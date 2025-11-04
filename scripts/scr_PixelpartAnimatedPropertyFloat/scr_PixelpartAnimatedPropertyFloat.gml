function PixelpartAnimatedPropertyFloat(_property_ptr) constructor
{
	property_ptr = _property_ptr;

	static at = function(_position)
	{
		pixelpart_animated_property_float_at(property_ptr, _position);
	}

	static add_keyframe = function(_position, _value)
	{
		pixelpart_animated_property_float_add_keyframe(property_ptr, _position, _value);
	}
	static remove_keyframe = function(_index)
	{
		pixelpart_animated_property_float_remove_keyframe(property_ptr, _index);
	}

	static set_keyframe_value = function(_index, _value)
	{
		pixelpart_animated_property_float_set_keyframe_value(property_ptr, _index, _value);
	}
	static set_keyframe_position = function(_index, _position)
	{
		pixelpart_animated_property_float_set_keyframe_position(property_ptr, _index, _position);
	}

	static clear_keyframes = function()
	{
		pixelpart_animated_property_float_clear_keyframes(property_ptr);
	}

	static keyframe_count = function()
	{
		return pixelpart_animated_property_float_keyframe_count(property_ptr);
	}

	static keyframe_value = function(_index)
	{
		pixelpart_animated_property_float_keyframe_value(property_ptr, _index);
	}
	static keyframe_index = function(_position, epsilon)
	{
		pixelpart_animated_property_float_keyframe_index(property_ptr, _position, epsilon);
	}

	static set_keyframe_interpolation = function(_method)
	{
		pixelpart_animated_property_float_set_keyframe_interpolation(property_ptr, _method);
	}
	static get_keyframe_interpolation = function()
	{
		return pixelpart_animated_property_float_get_keyframe_interpolation(property_ptr);
	}

	static enable_adaptive_cache = function()
	{
		pixelpart_animated_property_float_enable_adaptive_cache(property_ptr);
	}
	static enable_fixed_cache = function(size)
	{
		pixelpart_animated_property_float_enable_fixed_cache(property_ptr, size);
	}
}