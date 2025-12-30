/// @desc Collider consisting of several connected line segments (2D only).
/// Line colliders combine several collision segments together and
/// are defined by a set of points at the vertices of the line segments.
/// @param {string} _effect_ptr Pointer to internal effect runtime object
/// @param {real} _node_id Node ID
function PixelpartLineCollider(_effect_ptr, _node_id) : PixelpartCollider(_effect_ptr, _node_id) constructor
{
	/// @desc Add a vertex to the end of the line collider.
	/// @param {real} _x X position
	/// @param {real} _y Y position
	/// @param {real} _z Z position
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

	/// @desc Change the location of a vertex in the line collider.
	/// @param {real} _index Index of the vertex
	/// @param {real} _x X position
	/// @param {real} _y Y position
	/// @param {real} _z Z position
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

	/// @desc Remove a vertex from the line collider.
	/// @param {real} _index Index of vertex to remove
	static remove_point = function(_index)
	{
		pixelpart_line_collider_remove_point(effect_ptr, node_id, _index);
	}

	/// @desc Location of a vertex in the line collider.
	/// @param {real} _index Index of the vertex
	/// @returns {array} Vertex location (x, y, z)
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

	/// @desc Number of vertices in the line collider.
	/// @returns {real} Number of vertices
	static get_point_count = function()
	{
		return pixelpart_line_collider_get_point_count(effect_ptr, node_id);
	}
}
