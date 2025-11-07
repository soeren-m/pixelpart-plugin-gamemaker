function PixelpartAnimatedPropertyFloat3(_property_ptr) constructor
{
	property_ptr = _property_ptr;

	static at = function(_position)
	{
		var _result_buffer = buffer_create(3 * 8, buffer_fixed, 8);
		pixelpart_animated_property_float3_at(property_ptr, _position,
			buffer_get_address(_result_buffer));
		var _x = buffer_read(_result_buffer, buffer_f64);
		var _y = buffer_read(_result_buffer, buffer_f64);
		var _z = buffer_read(_result_buffer, buffer_f64);
		buffer_delete(_result_buffer);

		return [_x, _y, _z];
	}

	static add_keyframe = function(_position, _x, _y, _z)
	{
		var _param_buffer = buffer_create(3 * 8, buffer_fixed, 8);
		buffer_write(_param_buffer, buffer_f64, _x);
		buffer_write(_param_buffer, buffer_f64, _y);
		buffer_write(_param_buffer, buffer_f64, _z);
		pixelpart_animated_property_float3_add_keyframe(property_ptr, _position,
			buffer_get_address(_param_buffer));
		buffer_delete(_param_buffer);
	}
	static remove_keyframe = function(_index)
	{
		pixelpart_animated_property_float3_remove_keyframe(property_ptr, _index);
	}

	static set_keyframe_value = function(_index, _x, _y, _z)
	{
		var _param_buffer = buffer_create(3 * 8, buffer_fixed, 8);
		buffer_write(_param_buffer, buffer_f64, _x);
		buffer_write(_param_buffer, buffer_f64, _y);
		buffer_write(_param_buffer, buffer_f64, _z);
		pixelpart_animated_property_float3_set_keyframe_value(property_ptr, _index,
			buffer_get_address(_param_buffer));
		buffer_delete(_param_buffer);
	}
	static set_keyframe_position = function(_index, _position)
	{
		pixelpart_animated_property_float3_set_keyframe_position(property_ptr, _index, _position);
	}

	static clear_keyframes = function()
	{
		pixelpart_animated_property_float3_clear_keyframes(property_ptr);
	}

	static keyframe_count = function()
	{
		return pixelpart_animated_property_float3_keyframe_count(property_ptr);
	}

	static keyframe_value = function(_index)
	{
		var _result_buffer = buffer_create(3 * 8, buffer_fixed, 8);
		pixelpart_animated_property_float3_keyframe_value(property_ptr, _index,
			buffer_get_address(_result_buffer));
		var _x = buffer_read(_result_buffer, buffer_f64);
		var _y = buffer_read(_result_buffer, buffer_f64);
		var _z = buffer_read(_result_buffer, buffer_f64);
		buffer_delete(_result_buffer);

		return [_x, _y, _z];
	}
	static keyframe_index = function(_position, epsilon)
	{
		pixelpart_animated_property_float3_keyframe_index(property_ptr, _position, epsilon);
	}

	static set_keyframe_interpolation = function(_method)
	{
		pixelpart_animated_property_float3_set_keyframe_interpolation(property_ptr, _method);
	}
	static get_keyframe_interpolation = function()
	{
		return pixelpart_animated_property_float3_get_keyframe_interpolation(property_ptr);
	}

	static enable_adaptive_cache = function()
	{
		pixelpart_animated_property_float3_enable_adaptive_cache(property_ptr);
	}
	static enable_fixed_cache = function(size)
	{
		pixelpart_animated_property_float3_enable_fixed_cache(property_ptr, size);
	}
}
