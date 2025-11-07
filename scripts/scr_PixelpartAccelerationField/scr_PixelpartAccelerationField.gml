function PixelpartAccelerationField(_effect_ptr, _node_id) : PixelpartForceField(_effect_ptr, _node_id) constructor
{
	acceleration_direction = new PixelpartAnimatedPropertyFloat3(
		ptr(pixelpart_acceleration_field_get_acceleration_direction(_effect_ptr, _node_id)));
	acceleration_direction_variance = new PixelpartAnimatedPropertyFloat(
		ptr(pixelpart_acceleration_field_get_acceleration_direction_variance(_effect_ptr, _node_id)));
	acceleration_strength_variance = new PixelpartAnimatedPropertyFloat(
		ptr(pixelpart_acceleration_field_get_acceleration_strength_variance(_effect_ptr, _node_id)));

	static set_acceleration_grid_size = function(_x, _y, _z)
	{
		var _param_buffer = buffer_create(3 * 8, buffer_fixed, 8);
		buffer_write(_param_buffer, buffer_f64, _x);
		buffer_write(_param_buffer, buffer_f64, _y);
		buffer_write(_param_buffer, buffer_f64, _z);
		pixelpart_acceleration_field_set_acceleration_grid_size(effect_ptr, node_id,
			buffer_get_address(_param_buffer));
		buffer_delete(_param_buffer);
	}
	static get_acceleration_grid_size_x = function()
	{
		return pixelpart_acceleration_field_get_acceleration_grid_size_x(effect_ptr, node_id);
	}
	static get_acceleration_grid_size_y = function()
	{
		return pixelpart_acceleration_field_get_acceleration_grid_size_y(effect_ptr, node_id);
	}
	static get_acceleration_grid_size_z = function()
	{
		return pixelpart_acceleration_field_get_acceleration_grid_size_z(effect_ptr, node_id);
	}
}
