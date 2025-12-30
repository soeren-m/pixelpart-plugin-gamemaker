// Whether the rotation property represents the exact rotation of particles or their angular velocity.
enum PixelpartRotationMode
{
	// Rotation property defines angle of rotation in degrees.
	ANGLE = 0,

	// Rotation property defines angular velocity in degrees/second.
	VELOCITY = 1
}

// Direction to which particles are aligned.
enum PixelpartAlignmentMode
{
	// Particles do not align to anything.
	NONE = 0,

	// Particles always face the camera (3D).
	CAMERA = 1,

	// Particles align to their own velocity vector.
	MOTION = 2,

	// Particles face their emitter.
	EMISSION = 3,

	// Particles copy the rotation of their emitter.
	EMITTER = 4
}

/// @desc Defines the appearance and behavior of particles.
/// Each particle emitter has a list of assigned particle types, which it will use for generating particles.
/// The particle type defines how particles move through space (e.g. velocity, acceleration) and
/// how they look (e.g. size, color).
/// Particle types can be assigned a parent particle type. This causes a particle of the parent type
/// to emit particles of the child particle type.
/// There are three types of particles, which determines how they are rendered.
/// - Sprite particle: The sprite renderer renders each particle as a separate sprite.
/// - Trail particle: The trail renderer generates continuous trails along the path of particles with the same parent particle.
/// - Mesh particle: The mesh renderer renders each particles as a three-dimensional mesh.
/// @param {string} _effect_ptr Pointer to internal effect runtime object
/// @param {real} _particle_type_id Particle type ID
function PixelpartParticleType(_effect_ptr, _particle_type_id) constructor
{
	effect_ptr = _effect_ptr;
	particle_type_id = _particle_type_id;

	// Center of rotation relative to the particle’s center.
	pivot = new PixelpartStaticPropertyFloat3(
		pixelpart_particle_type_get_pivot(_effect_ptr, _particle_type_id));

	// How much particles are influenced by the motion path.
	// Set to 0 to disable motion paths.
	motion_path_force = new PixelpartStaticPropertyFloat(
		pixelpart_particle_type_get_motion_path_force(_effect_ptr, _particle_type_id));

	// How many particles of this type are spawned by emitters.
	count = new PixelpartAnimatedPropertyFloat(
		pixelpart_particle_type_get_count(_effect_ptr, _particle_type_id));

	// How long particles exist after being spawned by emitters.
	lifespan = new PixelpartAnimatedPropertyFloat(
		pixelpart_particle_type_get_lifespan(_effect_ptr, _particle_type_id));

	// Size of each particle when created.
	initial_size = new PixelpartAnimatedPropertyFloat(
		pixelpart_particle_type_get_initial_size(_effect_ptr, _particle_type_id));

	// Rotation of each particle when created, in degrees.
	// For 3D effects, rotation is composed of roll, yaw and pitch.
	initial_rotation = new PixelpartAnimatedPropertyFloat3(
		pixelpart_particle_type_get_initial_rotation(_effect_ptr, _particle_type_id));

	// How fast each particle is initially after being spawned by the emitter.
	initial_velocity = new PixelpartAnimatedPropertyFloat(
		pixelpart_particle_type_get_initial_velocity(_effect_ptr, _particle_type_id));

	// How much speed particles inherit from the parent particle or emitter.
	inherited_velocity = new PixelpartAnimatedPropertyFloat(
		pixelpart_particle_type_get_inherited_velocity(_effect_ptr, _particle_type_id));

	// Opacity of each particle when created.
	initial_opacity = new PixelpartAnimatedPropertyFloat(
		pixelpart_particle_type_get_initial_opacity(_effect_ptr, _particle_type_id));

	// Motion path for particles.
	motion_path = new PixelpartAnimatedPropertyFloat3(
		pixelpart_particle_type_get_motion_path(_effect_ptr, _particle_type_id));

	// Size of each particle over its lifetime as a fraction of its initial size.
	size = new PixelpartAnimatedPropertyFloat3(
		pixelpart_particle_type_get_size(_effect_ptr, _particle_type_id));

	// How much particles are stretched based on their speed.
	stretch = new PixelpartAnimatedPropertyFloat3(
		pixelpart_particle_type_get_stretch(_effect_ptr, _particle_type_id));

	// Relative size of each particle for motion and collision calculations over its lifetime.
	physical_size = new PixelpartAnimatedPropertyFloat(
		pixelpart_particle_type_get_physical_size(_effect_ptr, _particle_type_id));

	// How particles rotate over time from their initial rotation, in degrees.
	// For 3D effects, rotation is composed of roll, yaw and pitch.
	rotation = new PixelpartAnimatedPropertyFloat3(
		pixelpart_particle_type_get_rotation(_effect_ptr, _particle_type_id));

	// How much particles rotate based on their velocity, in degrees.
	rotation_by_speed = new PixelpartAnimatedPropertyFloat3(
		pixelpart_particle_type_get_rotation_by_speed(_effect_ptr, _particle_type_id));

	// Linear acceleration applied to each particle over its lifetime.
	acceleration = new PixelpartAnimatedPropertyFloat(
		pixelpart_particle_type_get_acceleration(_effect_ptr, _particle_type_id));

	// Acceleration of each particle towards the emitter over its lifetime.
	radial_acceleration = new PixelpartAnimatedPropertyFloat(
		pixelpart_particle_type_get_radial_acceleration(_effect_ptr, _particle_type_id));

	// How strongly each particle is affected by force fields over its lifetime.
	weight = new PixelpartAnimatedPropertyFloat(
		pixelpart_particle_type_get_weight(_effect_ptr, _particle_type_id));

	// How much each particle bounces back from colliders over its lifetime.
	bounce = new PixelpartAnimatedPropertyFloat(
		pixelpart_particle_type_get_bounce(_effect_ptr, _particle_type_id));

	// How resistant each particle is to sliding down colliders over its lifetime.
	friction = new PixelpartAnimatedPropertyFloat(
		pixelpart_particle_type_get_friction(_effect_ptr, _particle_type_id));

	// Color of each particle over its lifetime.
	color = new PixelpartAnimatedPropertyFloat4(
		pixelpart_particle_type_get_color(_effect_ptr, _particle_type_id));

	// Opacity of each particle over its lifetime as a fraction of its initial opacity.
	opacity = new PixelpartAnimatedPropertyFloat(
		pixelpart_particle_type_get_opacity(_effect_ptr, _particle_type_id));

	// How much the lifespan varies between particles.
	lifespan_variance = new PixelpartStaticPropertyFloat(
		pixelpart_particle_type_get_lifespan_variance(_effect_ptr, _particle_type_id));

	// How much the size varies between particles.
	size_variance = new PixelpartStaticPropertyFloat(
		pixelpart_particle_type_get_size_variance(_effect_ptr, _particle_type_id));

	// How much the rotation varies between particles, in degrees.
	rotation_variance = new PixelpartStaticPropertyFloat3(
		pixelpart_particle_type_get_rotation_variance(_effect_ptr, _particle_type_id));

	// How much the angular velocity varies between particles, in degrees/second.
	angular_velocity_variance = new PixelpartStaticPropertyFloat3(
		pixelpart_particle_type_get_angular_velocity_variance(_effect_ptr, _particle_type_id));

	// How much the speed varies between particles.
	velocity_variance = new PixelpartStaticPropertyFloat(
		pixelpart_particle_type_get_velocity_variance(_effect_ptr, _particle_type_id));

	// How much the color varies between particles.
	color_variance = new PixelpartStaticPropertyFloat4(
		pixelpart_particle_type_get_color_variance(_effect_ptr, _particle_type_id));

	// How much the opacity varies between particles.
	opacity_variance = new PixelpartStaticPropertyFloat(
		pixelpart_particle_type_get_opacity_variance(_effect_ptr, _particle_type_id));

	/// @desc ID of the particle type.
	/// @returns {real} ID
	static get_id = function()
	{
		return particle_type_id;
	}

	/// @desc ID of the parent particle type.
	/// @returns {real} Parent ID or -1 if the particle type has no parent
	static get_parent_id = function()
	{
		return pixelpart_particle_type_get_parent_id(effect_ptr, particle_type_id);
	}

	/// @desc Name of the particle type.
	/// @returns {string} Name
	static get_name = function()
	{
		return pixelpart_particle_type_get_name(effect_ptr, particle_type_id);
	}

	/// @desc Set whether the position of particles is tied to the position of the emitter.
	/// @param {real} _relative Relative particle position
	static set_position_relative = function(_relative)
	{
		pixelpart_particle_type_set_position_relative(effect_ptr, node_id, _relative);
	}

	/// @desc Whether the position of particles is tied to the position of the emitter.
	/// @returns {bool} Relative particle position
	static is_position_relative = function()
	{
		return bool(pixelpart_particle_type_is_position_relative(effect_ptr, node_id));
	}

	/// @desc Set whether the rotation property represents the exact rotation of particles
	/// or their angular velocity.
	/// @param {real} _mode Rotation mode
	static set_rotation_mode = function(_mode)
	{
		pixelpart_particle_type_set_rotation_mode(effect_ptr, node_id, _mode);
	}

	/// @desc Whether the rotation property represents the exact rotation of particles
	/// or their angular velocity.
	/// @returns {real} Rotation mode
	static get_rotation_mode = function()
	{
		return pixelpart_particle_type_get_rotation_mode(effect_ptr, node_id);
	}

	/// @desc Set direction to which particles are aligned.
	/// @param {real} _mode Alignment mode
	static set_alignment_mode = function(_mode)
	{
		pixelpart_particle_type_set_alignment_mode(effect_ptr, node_id, _mode);
	}

	/// @desc Direction to which particles are aligned.
	/// @returns {real} Alignment mode
	static get_alignment_mode = function()
	{
		return pixelpart_particle_type_get_alignment_mode(effect_ptr, node_id);
	}

	/// @desc Set whether particles of this type are visible.
	/// @param {bool} _visible Whether particles of this type are visible
	static set_visible = function(_visible)
	{
		pixelpart_particle_type_set_visible(effect_ptr, node_id, _visible);
	}

	/// @desc Whether particles of this type are visible.
	/// @returns {bool} Whether particles of this type are visible
	static is_visible = function()
	{
		return bool(pixelpart_particle_type_is_visible(effect_ptr, node_id));
	}

	/// @desc Set layer particles are drawn on.
	/// Particles on upper layers occlude those on lower layers.
	/// @param {real} _layer Layer
	static set_layer = function(_layer)
	{
		pixelpart_particle_type_set_layer(effect_ptr, node_id, _layer);
	}

	/// @desc Layer particles are drawn on.
	/// @returns {real} Layer
	static get_layer = function()
	{
		return pixelpart_particle_type_get_layer(effect_ptr, node_id);
	}
}
