// Types of emitter shapes.
enum PixelpartEmitterShape
{
	// The emitter generates particles at a single point.
	POINT = 0,

	// Particles are emitted on a straight line.
	LINE = 1,

	// Particles are emitted inside a circular or elliptical shape.
	ELLIPSE = 2,

	// Particles are emitted inside a rectangle.
	RECTANGLE = 3,

	// Particles are emitted on a custom path consisting of connected line segments.
	PATH = 4,

	// Particles are emitted inside a sphere or ellipsoid. Only for 3D effects.
	ELLIPSOID = 5,

	// Particles are emitted inside a cube. Only for 3D effects.
	CUBOID = 6,

	// Particles are emitted inside a cylinder. Only for 3D effects.
	CYLINDER = 7
}

// Particle distribution modes.
// When spawning particles inside the emitter shape, particle emitters can use different techniques
// to determine the exact points where particles are spawned.
// For example, you may want to spawn particles near the edge of the shape or on in a grid-like pattern.
enum PixelpartEmitterDistribution
{
	// Particles are spawned at randomly generated locations (uniform distribution) inside the emitter area.
	UNIFORM = 0,

	// Particles are created mostly around the center and less at the boundary.
	CENTER = 1,

	// More particles spawn near the emitter boundary and less in the center.
	HOLE = 2,

	// Particles are created only on the emitter boundary.
	BOUNDARY = 3,

	// Particles spawn at random points of a grid.
	GRID_RANDOM = 4,

	// Particles are created on points in a grid, one grid point after the other.
	GRID_ORDERED = 5
}

// Order of points for grid distribution mode.
enum PixelpartEmitterGridOrder
{
	XYZ = 0,
	XZY = 1,
	YXZ = 2,
	YZX = 3,
	ZXY = 4,
	ZYX = 5
}

// Modes for particle emission.
// The emission mode of particle emitters controls when particles are created during the lifetime of the emitter.
enum PixelpartEmitterEmissionMode
{
	// The emitter continuously spawns particles throughout its lifetime.
	CONTINUOUS = 0,

	// The emitter instantiates all particles immediately after being created.
	BURST_START = 1,

	// Particles are spawned at the end of the emitter lifetime, or
    // - if the emitter is a sub-emitter - when particles of the parent emitter
    // reach the end of their lifetime.
	BURST_END = 2
}

// Modes to determine the initial direction of particles.
// When a particle is created by the particle emitter,
// it decides in which direction to emit the particle
// based on the specified direction and the given direction mode.
enum PixelpartEmitterDirectionMode
{
	// Particles shoot off in a common direction.
	FIXED = 0,

	// Particles move away from the emitter.
	OUTWARDS = 1,

	// Particles move towards the emitter’s center.
	INWARDS = 2,

	// Particles move along the direction of the parent particle or emitter.
	INHERIT = 3,

	// Particles move against the direction of the parent particle or emitter.
	INHERIT_INVERSE = 4
}

/// @desc Node that emits particles.
/// Particle emitters continuously spawn new particles of assigned particle types in a defined area.
/// They also define in which direction particles move initially.
/// @param {pointer} _effect_ptr Pointer to internal effect runtime object
/// @param {real} _node_id Node ID
function PixelpartParticleEmitter(_effect_ptr, _node_id) : PixelpartNode(_effect_ptr, _node_id) constructor
{
	// Direction in which particles move when spawned, in degrees.
	// For 3D effects, the direction is composed of roll, yaw and pitch.
	direction = new PixelpartAnimatedPropertyFloat3(
		ptr(pixelpart_particle_emitter_get_direction(_effect_ptr, _node_id)));

	// How much the direction varies.
	// A spread of 0° means that particles only move in the specified direction,
	// while 360° leads to particles shooting off in all directions.
	spread = new PixelpartAnimatedPropertyFloat(
		ptr(pixelpart_particle_emitter_get_spread(_effect_ptr, _node_id)));

	/// @desc Set shape of the emitter area.
	/// @param {real} _shape Shape of the emitter area
	static set_shape = function(_shape)
	{
		pixelpart_particle_emitter_set_shape(effect_ptr, node_id, _shape);
	}

	/// @desc Return shape of the emitter area.
	/// @returns {real} Shape of the emitter area
	static get_shape = function()
	{
		return pixelpart_particle_emitter_get_shape(effect_ptr, node_id);
	}

	/// @desc Add a new point to the emitter shape.
	/// Only applicable for emitter shape PATH.
	/// @param {real} _x X position
	/// @param {real} _y Y position
	/// @param {real} _z Z position
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

	/// @desc Remove the point at the given index from the emitter shape.
	/// Only applicable for emitter shape PATH.
	/// @param {real} _index Index of point to remove
	static remove_shape_point = function(_index)
	{
		pixelpart_particle_emitter_remove_shape_point(effect_ptr, node_id, _index);
	}

	/// @desc Change the location of the point at the given index in the emitter shape.
	/// Only applicable for emitter shape PATH.
	/// @param {real} _index Description
	/// @param {any} _x X position
	/// @param {any} _y Y position
	/// @param {any} _z Z position
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

	/// @desc Return the location of the point at the given index in the emitter shape.
	/// Only applicable for emitter shape PATH.
	/// @param {real} _index Index of point
	/// @returns {array} Location of point (x, y, z)
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

	/// @desc Return the number of points in the emitter shape.
	/// Only applicable for emitter shape PATH.
	/// @returns {real} Number of points
	static get_shape_point_count = function()
	{
		return pixelpart_particle_emitter_get_shape_point_count(effect_ptr, node_id);
	}

	/// @desc Set where particles are spawned inside the emitter area.
	/// When spawning particles inside the emitter shape,
	/// particle emitters can use different techniques to determine the exact points where particles are spawned.
	/// @param {real} _mode Distribution mode
	static set_distribution = function(_mode)
	{
		pixelpart_particle_emitter_set_distribution(effect_ptr, node_id, _mode);
	}

	/// Return where particles are spawned inside the emitter area.
	/// When spawning particles inside the emitter shape,
	/// particle emitters can use different techniques to determine the exact points where particles are spawned.
	/// @returns {real} Distribution mode
	static get_distribution = function()
	{
		return pixelpart_particle_emitter_get_distribution(effect_ptr, node_id);
	}

	/// @desc Set the grid order of grid distribution modes.
	/// @param {real} _mode Grid order
	static set_grid_order = function(_mode)
	{
		pixelpart_particle_emitter_set_grid_order(effect_ptr, node_id, _mode);
	}

	/// @desc Return the grid order of grid distribution modes.
	/// @returns {real} Grid order
	static get_grid_order = function()
	{
		return pixelpart_particle_emitter_get_grid_order(effect_ptr, node_id);
	}

	/// @desc Set the number of grid cells.
	/// Only applicable for grid distribution modes.
	/// @param {any} _x Number of cells in X direction
	/// @param {any} _y Number of cells in Y direction
	/// @param {any} _z Number of cells in Z direction
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

	/// @desc Return the number of grid cells in X direction.
	/// Only applicable for grid distribution modes.
	/// @returns {real} Number of cells
	static get_grid_size_x = function()
	{
		return pixelpart_particle_emitter_get_grid_size_x(effect_ptr, node_id);
	}

	/// @desc Return the number of grid cells in Y direction.
	/// Only applicable for grid distribution modes.
	/// @returns {real} Number of cells
	static get_grid_size_y = function()
	{
		return pixelpart_particle_emitter_get_grid_size_y(effect_ptr, node_id);
	}

	/// @desc Return the number of grid cells in Z direction.
	/// Only applicable for grid distribution modes.
	/// @returns {real} Number of cells
	static get_grid_size_z = function()
	{
		return pixelpart_particle_emitter_get_grid_size_z(effect_ptr, node_id);
	}

	/// @desc Set the emission mode.
	/// The emission mode of particle emitters controls
	/// when particles are created during the lifetime of the emitter.
	/// @param {real} _mode Emission mode
	static set_emission_mode = function(_mode)
	{
		pixelpart_particle_emitter_set_emission_mode(effect_ptr, node_id, _mode);
	}

	/// @desc Return the emission mode.
	/// The emission mode of particle emitters controls
	/// when particles are created during the lifetime of the emitter.
	/// @returns {real} Emission mode
	static get_emission_mode = function()
	{
		return pixelpart_particle_emitter_get_emission_mode(effect_ptr, node_id);
	}

	/// @desc Set the direction mode.
	/// When a particle is created by the particle emitter,
	/// it decides in which direction to emit the particle based on the specified direction and the given direction mode.
	/// @param {real} _mode Direction mode
	static set_direction_mode = function(_mode)
	{
		pixelpart_particle_emitter_set_direction_mode(effect_ptr, node_id, _mode);
	}

	/// @desc Get the direction mode
	/// When a particle is created by the particle emitter,
	/// it decides in which direction to emit the particle based on the specified direction and the given direction mode.
	/// @returns {real} Direction mode
	static get_direction_mode = function()
	{
		return pixelpart_particle_emitter_get_direction_mode(effect_ptr, node_id);
	}
}
