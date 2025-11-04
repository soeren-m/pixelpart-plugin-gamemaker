enum PixelpartRotationMode
{
	ANGLE = 0,
	VELOCITY = 1
}

enum PixelpartAlignmentMode
{
	NONE = 0,
	CAMERA = 1,
	MOTION = 2,
	EMISSION = 3,
	EMITTER = 4
}

function PixelpartParticleType(_effect_ptr, _particle_type_id) constructor
{
	effect_ptr = _effect_ptr;
	particle_type_id = _particle_type_id;

	pivot = new PixelpartStaticPropertyFloat3(
		ptr(pixelpart_particle_type_get_pivot(_effect_ptr, _particle_type_id)));

	motion_path_force = new PixelpartStaticPropertyFloat(
		ptr(pixelpart_particle_type_get_motion_path_force(_effect_ptr, _particle_type_id)));

	count = new PixelpartAnimatedPropertyFloat(
		ptr(pixelpart_particle_type_get_count(_effect_ptr, _particle_type_id)));
	lifespan = new PixelpartAnimatedPropertyFloat(
		ptr(pixelpart_particle_type_get_lifespan(_effect_ptr, _particle_type_id)));
	initial_size = new PixelpartAnimatedPropertyFloat(
		ptr(pixelpart_particle_type_get_initial_size(_effect_ptr, _particle_type_id)));
	initial_rotation = new PixelpartAnimatedPropertyFloat3(
		ptr(pixelpart_particle_type_get_initial_rotation(_effect_ptr, _particle_type_id)));
	initial_velocity = new PixelpartAnimatedPropertyFloat(
		ptr(pixelpart_particle_type_get_initial_velocity(_effect_ptr, _particle_type_id)));
	inherited_velocity = new PixelpartAnimatedPropertyFloat(
		ptr(pixelpart_particle_type_get_inherited_velocity(_effect_ptr, _particle_type_id)));
	initial_opacity = new PixelpartAnimatedPropertyFloat(
		ptr(pixelpart_particle_type_get_initial_opacity(_effect_ptr, _particle_type_id)));

	motion_path = new PixelpartAnimatedPropertyFloat3(
		ptr(pixelpart_particle_type_get_motion_path(_effect_ptr, _particle_type_id)));
	size = new PixelpartAnimatedPropertyFloat3(
		ptr(pixelpart_particle_type_get_size(_effect_ptr, _particle_type_id)));
	stretch = new PixelpartAnimatedPropertyFloat3(
		ptr(pixelpart_particle_type_get_stretch(_effect_ptr, _particle_type_id)));
	physical_size = new PixelpartAnimatedPropertyFloat(
		ptr(pixelpart_particle_type_get_physical_size(_effect_ptr, _particle_type_id)));
	rotation = new PixelpartAnimatedPropertyFloat3(
		ptr(pixelpart_particle_type_get_rotation(_effect_ptr, _particle_type_id)));
	rotation_by_speed = new PixelpartAnimatedPropertyFloat3(
		ptr(pixelpart_particle_type_get_rotation_by_speed(_effect_ptr, _particle_type_id)));
	acceleration = new PixelpartAnimatedPropertyFloat(
		ptr(pixelpart_particle_type_get_acceleration(_effect_ptr, _particle_type_id)));
	radial_acceleration = new PixelpartAnimatedPropertyFloat(
		ptr(pixelpart_particle_type_get_radial_acceleration(_effect_ptr, _particle_type_id)));
	weight = new PixelpartAnimatedPropertyFloat(
		ptr(pixelpart_particle_type_get_weight(_effect_ptr, _particle_type_id)));
	bounce = new PixelpartAnimatedPropertyFloat(
		ptr(pixelpart_particle_type_get_bounce(_effect_ptr, _particle_type_id)));
	friction = new PixelpartAnimatedPropertyFloat(
		ptr(pixelpart_particle_type_get_friction(_effect_ptr, _particle_type_id)));
	color = new PixelpartAnimatedPropertyFloat4(
		ptr(pixelpart_particle_type_get_color(_effect_ptr, _particle_type_id)));
	opacity = new PixelpartAnimatedPropertyFloat(
		ptr(pixelpart_particle_type_get_opacity(_effect_ptr, _particle_type_id)));

	lifespan_variance = new PixelpartStaticPropertyFloat(
		ptr(pixelpart_particle_type_get_lifespan_variance(_effect_ptr, _particle_type_id)));
	size_variance = new PixelpartStaticPropertyFloat(
		ptr(pixelpart_particle_type_get_size_variance(_effect_ptr, _particle_type_id)));
	rotation_variance = new PixelpartStaticPropertyFloat3(
		ptr(pixelpart_particle_type_get_rotation_variance(_effect_ptr, _particle_type_id)));
	angular_velocity_variance = new PixelpartStaticPropertyFloat3(
		ptr(pixelpart_particle_type_get_angular_velocity_variance(_effect_ptr, _particle_type_id)));
	velocity_variance = new PixelpartStaticPropertyFloat(
		ptr(pixelpart_particle_type_get_velocity_variance(_effect_ptr, _particle_type_id)));
	color_variance = new PixelpartStaticPropertyFloat4(
		ptr(pixelpart_particle_type_get_color_variance(_effect_ptr, _particle_type_id)));
	opacity_variance = new PixelpartStaticPropertyFloat(
		ptr(pixelpart_particle_type_get_opacity_variance(_effect_ptr, _particle_type_id)));

	static get_id = function()
	{
		return particle_type_id;
	}

	static get_parent_id = function()
	{
		return pixelpart_particle_type_get_parent_id(effect_ptr, particle_type_id);
	}

	static get_name = function()
	{
		return pixelpart_particle_type_get_name(effect_ptr, particle_type_id);
	}

	static set_position_relative = function(_relative)
	{
		pixelpart_particle_type_set_position_relative(effect_ptr, node_id, _relative);
	}
	static is_position_relative = function()
	{
		return pixelpart_particle_type_is_position_relative(effect_ptr, node_id);
	}

	static set_rotation_mode = function(_mode)
	{
		pixelpart_particle_type_set_rotation_mode(effect_ptr, node_id, _mode);
	}
	static get_rotation_mode = function()
	{
		return pixelpart_particle_type_get_rotation_mode(effect_ptr, node_id);
	}

	static set_alignment_mode = function(_mode)
	{
		pixelpart_particle_type_set_alignment_mode(effect_ptr, node_id, _mode);
	}
	static get_alignment_mode = function()
	{
		return pixelpart_particle_type_get_alignment_mode(effect_ptr, node_id);
	}

	static set_visible = function(_visible)
	{
		pixelpart_particle_type_set_visible(effect_ptr, node_id, _visible);
	}
	static is_visible = function()
	{
		return pixelpart_particle_type_is_visible(effect_ptr, node_id);
	}

	static set_layer = function(_layer)
	{
		pixelpart_particle_type_set_layer(effect_ptr, node_id, _layer);
	}
	static get_layer = function()
	{
		return pixelpart_particle_type_get_layer(effect_ptr, node_id);
	}
}