function PixelpartEffect(_effect_resource) constructor
{
	effect_resource = _effect_resource;

	playing = true;
	loop = false;
	loop_time = 1;
	warmup_time = 0;
	speed = 1;
	frame_rate = 60;

	effect_scale = 1;
	flip_h = false;
	flip_v = true;

	advance_effect_param_buffer = buffer_create(5 * 8, buffer_fixed, 1);

	effect_ptr = pointer_null;
	effect_renderer = pointer_null;

	if !buffer_exists(effect_resource.data_buffer)
	{
		show_debug_message("[Pixelpart] Effect resource has not been loaded properly");
		return;
	}

	// Deserialize effect
	effect_ptr = ptr(pixelpart_load_effect(
		buffer_read(effect_resource.data_buffer, buffer_string),
		buffer_get_size(effect_resource.data_buffer)));

	if effect_ptr != pointer_null
	{
		effect_renderer = new PixelpartEffectRenderer(effect_ptr);
	}
	else
	{
		show_debug_message("[Pixelpart] Failed to load effect with error: {0}",
			pixelpart_last_error());
	}

	static cleanup = function()
	{
		if effect_renderer != pointer_null
		{
			effect_renderer.cleanup();
			delete effect_renderer;
		}

		if effect_ptr != pointer_null
		{
			pixelpart_delete_effect(effect_ptr);
			effect_ptr = pointer_null;
		}
	}

	static draw = function()
	{
		if effect_ptr == pointer_null
		{
			return;
		}

		effect_renderer.render();
	}

	static is_3d = function()
	{
		if effect_ptr == pointer_null
		{
			show_debug_message("[Pixelpart] Effect is not associated with any effect asset");
			return false;
		}

		return pixelpart_is_effect_3d(effect_ptr);
	}

	static get_current_time = function()
	{
		if effect_ptr == pointer_null
		{
			show_debug_message("[Pixelpart] Effect is not associated with any effect asset");
			return 0;
		}

		return pixelpart_get_effect_time(effect_ptr);
	}

	static advance = function(_dt, _pos_x, _pos_y)
	{
		if effect_ptr == pointer_null || !playing
		{
			return;
		}

		pixelpart_set_effect_scale(effect_ptr,
			effect_scale * (flip_h ? -1.0 : +1.0),
			effect_scale * (flip_v ? -1.0 : +1.0));
		pixelpart_set_effect_transform(effect_ptr,
			_pos_x, _pos_y);

		var _time_step = 1.0 / max(frame_rate, 0.01);
		buffer_seek(advance_effect_param_buffer, buffer_seek_start, 0);
		buffer_write(advance_effect_param_buffer, buffer_f64, _dt);
		buffer_write(advance_effect_param_buffer, buffer_f64, loop);
		buffer_write(advance_effect_param_buffer, buffer_f64, loop_time);
		buffer_write(advance_effect_param_buffer, buffer_f64, speed);
		buffer_write(advance_effect_param_buffer, buffer_f64, _time_step);

		pixelpart_advance_effect(effect_ptr, buffer_get_address(advance_effect_param_buffer));
	}

	static restart_effect = function(remove_particles)
	{
		// TODO
	}

	static spawn_particles = function(particle_emitter_name, particle_type_name, count)
	{
		// TODO
	}

	#region Inputs

	static set_input_bool = function(input_name, value)
	{
		// TODO
	}

	static set_input_int = function(input_name, value)
	{
		// TODO
	}

	static set_input_float = function(input_name, value)
	{
		// TODO
	}

	static set_input_float2 = function(input_name, x, y)
	{
		// TODO
	}

	static set_input_float3 = function(input_name, x, y, z)
	{
		// TODO
	}

	static set_input_float4 = function(input_name, x, y, z, w)
	{
		// TODO
	}

	static get_input_bool = function(input_name)
	{
		// TODO
	}

	static get_input_int = function(input_name)
	{
		// TODO
	}

	static get_input_float = function(input_name)
	{
		// TODO
	}

	static get_input_float2 = function(input_name)
	{
		// TODO
	}

	static get_input_float3 = function(input_name)
	{
		// TODO
	}

	static get_input_float4 = function(input_name)
	{
		// TODO
	}

	#endregion

	#region Triggers

	static activate_trigger = function(trigger_name)
	{
		// TODO
	}

	static is_trigger_activated = function(trigger_name)
	{
		// TODO
	}

	#endregion

	#region Nodes

	static find_node = function(node_name)
	{
		// TODO
	}

	static get_node = function(id)
	{
		// TODO
	}

	static get_node_at_index = function(index)
	{
		// TODO
	}

	#endregion

	#region Particle types

	static find_particle_type = function(particle_type_name)
	{
		// TODO
	}

	static get_particle_type = function(id)
	{
		// TODO
	}

	static get_particle_type_at_index = function(index)
	{
		// TODO
	}

	#endregion
}