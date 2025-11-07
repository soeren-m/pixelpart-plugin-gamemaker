enum PixelpartShapeType
{
	POINT = 0,
	LINE = 1,
	ELLIPSE = 2,
	RECTANGLE = 3,
	PATH = 4,
	ELLIPSOID = 5,
	CUBOID = 6,
	CYLINDER = 7
}

enum PixelpartDistributionType
{
	UNIFORM = 0,
	CENTER = 1,
	HOLE = 2,
	BOUNDARY = 3,
	GRID_RANDOM = 4,
	GRID_ORDERED = 5
}

enum PixelpartGridOrderType
{
	XYZ = 0,
	XZY = 1,
	YXZ = 2,
	YZX = 3,
	ZXY = 4,
	ZYX = 5
}

enum PixelpartEmissionModeType
{
	CONTINUOUS = 0,
	BURST_START = 1,
	BURST_END = 2
}

enum PixelpartDirectionModeType
{
	FIXED = 0,
	OUTWARDS = 1,
	INWARDS = 2,
	INHERIT = 3,
	INHERIT_INVERSE = 4
}

function PixelpartParticleEmitter(_effect_ptr, _node_id) : PixelpartNode(_effect_ptr, _node_id) constructor
{
	direction = new PixelpartAnimatedPropertyFloat3(
		ptr(pixelpart_particle_emitter_get_direction(_effect_ptr, _node_id)));
	spread = new PixelpartAnimatedPropertyFloat(
		ptr(pixelpart_particle_emitter_get_spread(_effect_ptr, _node_id)));

	static set_shape = function(_shape)
	{
		pixelpart_particle_emitter_set_shape(effect_ptr, node_id, _shape);
	}
	static get_shape = function()
	{
		return pixelpart_particle_emitter_get_shape(effect_ptr, node_id);
	}
	static add_shape_point = function(_x, _y, _z)
	{
		var _param_buffer = buffer_create(3 * 8, buffer_fixed, 8);
		buffer_write(_param_buffer, buffer_f64, _x);
		buffer_write(_param_buffer, buffer_f64, _y);
		buffer_write(_param_buffer, buffer_f64, _z);
		pixelpart_particle_emitter_add_shape_point(effect_ptr, node_id,
			buffer_get_address(_param_buffer));
		buffer_delete(_param_buffer);
	}
	static remove_shape_point = function(_index)
	{
		pixelpart_particle_emitter_remove_shape_point(effect_ptr, node_id, _index);
	}
	static set_shape_point = function(_index, _x, _y, _z)
	{
		var _param_buffer = buffer_create(3 * 8, buffer_fixed, 8);
		buffer_write(_param_buffer, buffer_f64, _x);
		buffer_write(_param_buffer, buffer_f64, _y);
		buffer_write(_param_buffer, buffer_f64, _z);
		pixelpart_particle_emitter_set_shape_point(effect_ptr, node_id, _index,
			buffer_get_address(_param_buffer));
		buffer_delete(_param_buffer);
	}
	static get_shape_point = function(_index)
	{
		var _result_buffer = buffer_create(3 * 8, buffer_fixed, 8);
		pixelpart_particle_emitter_get_shape_point(effect_ptr, node_id, _index);
		var _x = buffer_read(_result_buffer, buffer_f64);
		var _y = buffer_read(_result_buffer, buffer_f64);
		var _z = buffer_read(_result_buffer, buffer_f64);
		buffer_delete(_result_buffer);

		return [_x, _y, _z];
	}
	static get_shape_point_count = function()
	{
		return pixelpart_particle_emitter_get_shape_point_count(effect_ptr, node_id);
	}

	static set_distribution = function(_mode)
	{
		pixelpart_particle_emitter_set_distribution(effect_ptr, node_id, _mode);
	}
	static get_distribution = function()
	{
		return pixelpart_particle_emitter_get_distribution(effect_ptr, node_id);
	}

	static set_grid_order = function(_mode)
	{
		pixelpart_particle_emitter_set_grid_order(effect_ptr, node_id, _mode);
	}
	static get_grid_order = function()
	{
		return pixelpart_particle_emitter_get_grid_order(effect_ptr, node_id);
	}

	static set_grid_size = function(_x, _y, _z)
	{
		var _param_buffer = buffer_create(3 * 8, buffer_fixed, 8);
		buffer_write(_param_buffer, buffer_f64, _x);
		buffer_write(_param_buffer, buffer_f64, _y);
		buffer_write(_param_buffer, buffer_f64, _z);
		pixelpart_particle_emitter_set_grid_size(effect_ptr, node_id,
			buffer_get_address(_param_buffer));
		buffer_delete(_param_buffer);
	}
	static get_grid_size_x = function()
	{
		return pixelpart_particle_emitter_get_grid_size_x(effect_ptr, node_id);
	}
	static get_grid_size_y = function()
	{
		return pixelpart_particle_emitter_get_grid_size_y(effect_ptr, node_id);
	}
	static get_grid_size_z = function()
	{
		return pixelpart_particle_emitter_get_grid_size_z(effect_ptr, node_id);
	}

	static set_emission_mode = function(_mode)
	{
		pixelpart_particle_emitter_set_emission_mode(effect_ptr, node_id, _mode);
	}
	static get_emission_mode = function()
	{
		return pixelpart_particle_emitter_get_emission_mode(effect_ptr, node_id);
	}

	static set_direction_mode = function(_mode)
	{
		pixelpart_particle_emitter_set_direction_mode(effect_ptr, node_id, _mode);
	}
	static get_direction_mode = function()
	{
		return pixelpart_particle_emitter_get_direction_mode(effect_ptr, node_id);
	}
}
