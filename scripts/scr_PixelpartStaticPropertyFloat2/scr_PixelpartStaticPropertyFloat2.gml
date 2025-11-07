function PixelpartStaticPropertyFloat2(_property_ptr) constructor
{
	property_ptr = _property_ptr;

	static value = function()
	{
		var _result_buffer = buffer_create(2 * 8, buffer_fixed, 8);
		pixelpart_static_property_float2_value(property_ptr,
			buffer_get_address(_result_buffer));
		var _x = buffer_read(_result_buffer, buffer_f64);
		var _y = buffer_read(_result_buffer, buffer_f64);
		buffer_delete(_result_buffer);

		return [_x, _y];
	}

	static set_base_value = function(_x, _y)
	{
		var _param_buffer = buffer_create(2 * 8, buffer_fixed, 8);
		buffer_write(_param_buffer, buffer_f64, _x);
		buffer_write(_param_buffer, buffer_f64, _y);
		pixelpart_static_property_float2_set_base_value(property_ptr,
			buffer_get_address(_param_buffer));
		buffer_delete(_param_buffer);
	}
	static get_base_value = function()
	{
		var _result_buffer = buffer_create(2 * 8, buffer_fixed, 8);
		pixelpart_static_property_float2_get_base_value(property_ptr,
			buffer_get_address(_result_buffer));
		var _x = buffer_read(_result_buffer, buffer_f64);
		var _y = buffer_read(_result_buffer, buffer_f64);
		buffer_delete(_result_buffer);

		return [_x, _y];
	}
}
