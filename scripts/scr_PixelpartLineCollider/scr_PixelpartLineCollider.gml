function PixelpartLineCollider(_effect_ptr, _node_id) : PixelpartCollider(_effect_ptr, _node_id) constructor
{
	static add_point = function(_x, _y, _z)
	{
		var _param_buffer = buffer_create(3 * 8, buffer_fixed, 8);
		buffer_write(_param_buffer, buffer_f64, _x);
		buffer_write(_param_buffer, buffer_f64, _y);
		buffer_write(_param_buffer, buffer_f64, _z);
		pixelpart_line_collider_add_point(effect_ptr, node_id,
			buffer_get_address(_param_buffer));
		buffer_delete(_param_buffer);
	}

	static set_point = function(_index, _x, _y, _z)
	{
		var _param_buffer = buffer_create(3 * 8, buffer_fixed, 8);
		buffer_write(_param_buffer, buffer_f64, _x);
		buffer_write(_param_buffer, buffer_f64, _y);
		buffer_write(_param_buffer, buffer_f64, _z);
		pixelpart_line_collider_set_point(effect_ptr, node_id, _index,
			buffer_get_address(_param_buffer));
		buffer_delete(_param_buffer);
	}

	static remove_point = function(_index)
	{
		pixelpart_line_collider_remove_point(effect_ptr, node_id, _index);
	}

	static get_point = function(_index)
	{
		var _result_buffer = buffer_create(3 * 8, buffer_fixed, 8);
		pixelpart_line_collider_get_point(effect_ptr, node_id, _index);
		var _x = buffer_read(_result_buffer, buffer_f64);
		var _y = buffer_read(_result_buffer, buffer_f64);
		var _z = buffer_read(_result_buffer, buffer_f64);
		buffer_delete(_result_buffer);

		return [_x, _y, _z];
	}

	static get_point_count = function()
	{
		return pixelpart_line_collider_get_point_count(effect_ptr, node_id);
	}
}
