/// @desc Force field that accelerates particles towards a given direction.
///	Acceleration fields also allow you to subdivide the force area with a grid,
///	where each grid cell has a different force direction and strength.
///	This can be useful for organic looking particle motion.
/// @param {string} _effect_ptr Pointer to internal effect runtime object
/// @param {real} _node_id Node ID
function PixelpartAccelerationField(_effect_ptr, _node_id) : PixelpartForceField(_effect_ptr, _node_id) constructor
{
	// Direction in which particles are accelerated, in degrees.
	// For 3D effects, the direction is composed of roll, yaw and pitch.
	acceleration_direction = new PixelpartAnimatedPropertyFloat3(
		pixelpart_acceleration_field_get_acceleration_direction(_effect_ptr, _node_id));

	// How much the force direction varies between cells of the grid.
	acceleration_direction_variance = new PixelpartAnimatedPropertyFloat(
		pixelpart_acceleration_field_get_acceleration_direction_variance(_effect_ptr, _node_id));

	// How much the force strength varies between cells of the grid.
	acceleration_strength_variance = new PixelpartAnimatedPropertyFloat(
		pixelpart_acceleration_field_get_acceleration_strength_variance(_effect_ptr, _node_id));

	/// @desc Set the number of cells in each dimension of the force field grid.
	/// Each cell of the grid varies in direction and strength determined by the direction and strength variance values.
	/// @param {real} _x Size on X axis
	/// @param {real} _y Size on Y axis
	/// @param {real} _z Size on Z axis
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

	/// @desc The number of grid cells on the X axis of the force field grid.
	/// @returns {real} Size on X axis
	static get_acceleration_grid_size_x = function()
	{
		return pixelpart_acceleration_field_get_acceleration_grid_size_x(effect_ptr, node_id);
	}

	/// @desc The number of grid cells on the Y axis of the force field grid.
	/// @returns {real} Size on Y axis
	static get_acceleration_grid_size_y = function()
	{
		return pixelpart_acceleration_field_get_acceleration_grid_size_y(effect_ptr, node_id);
	}

	/// @desc The number of grid cells on the Z axis of the force field grid.
	/// @returns {real} Size on Z axis
	static get_acceleration_grid_size_z = function()
	{
		return pixelpart_acceleration_field_get_acceleration_grid_size_z(effect_ptr, node_id);
	}
}
