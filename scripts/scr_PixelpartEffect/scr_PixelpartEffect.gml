function PixelpartEffect(_effect_resource, _particle_capacity = 10000) constructor
{
	playing = true;
	loop = false;
	loop_time = 1;
	warmup_time = 0;
	speed = 1;
	frame_rate = 60;
	seed = 0;
	random_seed = false;

	effect_scale = 1;
	flip_h = false;
	flip_v = true;

	finished_event = new PixelpartEvent();
	finished_event_invoked = false;

	advance_effect_param_buffer = buffer_create(7 * 8, buffer_fixed, 1);

	effect_ptr = pointer_null;
	effect_renderer = pointer_null;

	first_step = true;

	if !buffer_exists(_effect_resource.data_buffer)
	{
		show_debug_message("[Pixelpart] Effect resource has not been loaded properly");
		return;
	}

	// Deserialize effect
	effect_ptr = ptr(pixelpart_load_effect(
		buffer_read(_effect_resource.data_buffer, buffer_string),
		buffer_get_size(_effect_resource.data_buffer),
		_particle_capacity));

	if effect_ptr != pointer_null
	{
		effect_renderer = new PixelpartEffectRenderer(effect_ptr);
	}
	else
	{
		show_debug_message("[Pixelpart] Failed to load effect with error: {0}",
			pixelpart_last_error());
	}

	trigger_collection = new PixelpartTriggerCollection(effect_ptr);
	effect_input_collection = new PixelpartEffectInputCollection(effect_ptr);

	static cleanup = function()
	{
		delete finished_event;

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

		delete trigger_collection;
		delete effect_input_collection;
	}

	static draw = function()
	{
		if effect_ptr == pointer_null
		{
			return;
		}

		effect_renderer.render();
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

		if first_step
		{
			first_step = false;

			pixelpart_reseed_effect(effect_ptr, random_seed
				? current_time
				: seed);

			if warmup_time > 0.0
			{
				buffer_seek(advance_effect_param_buffer, buffer_seek_start, 0);
				buffer_write(advance_effect_param_buffer, buffer_f64, warmup_time);
				buffer_write(advance_effect_param_buffer, buffer_f64, 0.0);
				buffer_write(advance_effect_param_buffer, buffer_f64, 0.0);
				buffer_write(advance_effect_param_buffer, buffer_f64, 1.0);
				buffer_write(advance_effect_param_buffer, buffer_f64, _time_step);
				buffer_write(advance_effect_param_buffer, buffer_f64, seed);
				buffer_write(advance_effect_param_buffer, buffer_f64, random_seed);

				pixelpart_advance_effect(effect_ptr, buffer_get_address(advance_effect_param_buffer));
			}
		}

		buffer_seek(advance_effect_param_buffer, buffer_seek_start, 0);
		buffer_write(advance_effect_param_buffer, buffer_f64, _dt);
		buffer_write(advance_effect_param_buffer, buffer_f64, loop);
		buffer_write(advance_effect_param_buffer, buffer_f64, loop_time);
		buffer_write(advance_effect_param_buffer, buffer_f64, speed);
		buffer_write(advance_effect_param_buffer, buffer_f64, _time_step);
		buffer_write(advance_effect_param_buffer, buffer_f64, seed);
		buffer_write(advance_effect_param_buffer, buffer_f64, random_seed);

		pixelpart_advance_effect(effect_ptr, buffer_get_address(advance_effect_param_buffer));

		if !finished_event_invoked && !loop && pixelpart_is_effect_finished(effect_ptr)
		{
			finished_event_invoked = true;
			finished_event.invoke();
		}
	}

	static restart = function(_clear)
	{
		if effect_ptr == pointer_null
		{
			show_debug_message("[Pixelpart] Effect is not associated with any effect asset");
			return;
		}

		pixelpart_restart_effect(effect_ptr, _clear);
	}

	static spawn_particles = function(_particle_emitter_name, _particle_type_name, _count)
	{
		if effect_ptr == pointer_null
		{
			show_debug_message("[Pixelpart] Effect is not associated with any effect asset");
			return;
		}

		var _particle_emitter_id = pixelpart_find_node(effect_ptr, _particle_emitter_name);
		if !pixelpart_node_exists(effect_ptr, _particle_emitter_id)
		{
			show_debug_message("[Pixelpart] Unknown particle emitter \"" + _particle_emitter_name + "\"");
			return;
		}

		var _particle_type_id = pixelpart_find_particle_type(effect_ptr, _particle_type_name);
		if !pixelpart_particle_type_exists(effect_ptr, _particle_type_id)
		{
			show_debug_message("[Pixelpart] Unknown particle type \"" + _particle_type_name + "\"");
			return;
		}

		pixelpart_spawn_particles(effect_ptr, _particle_emitter_id, _particle_type_id, _count);
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

	static is_3d = function()
	{
		if effect_ptr == pointer_null
		{
			show_debug_message("[Pixelpart] Effect is not associated with any effect asset");
			return false;
		}

		return pixelpart_is_effect_3d(effect_ptr);
	}

	#region Inputs

	static set_input_bool = function(_input_name, _value)
	{
		var _input_id = effect_input_collection.get_input_id(_input_name);
		if _input_id < 0
		{
			return;
		}

		pixelpart_set_effect_input_bool(effect_ptr, _input_id, _value);
	}

	static set_input_int = function(_input_name, _value)
	{
		var _input_id = effect_input_collection.get_input_id(_input_name);
		if _input_id < 0
		{
			return;
		}

		pixelpart_set_effect_input_int(effect_ptr, _input_id, _value);
	}

	static set_input_float = function(_input_name, _value)
	{
		var _input_id = effect_input_collection.get_input_id(_input_name);
		if _input_id < 0
		{
			return;
		}

		pixelpart_set_effect_input_float(effect_ptr, _input_id, _value);
	}

	static set_input_float2 = function(_input_name, _x, _y)
	{
		var _input_id = effect_input_collection.get_input_id(_input_name);
		if _input_id < 0
		{
			return;
		}

		var _param_buffer = buffer_create(2 * 8, buffer_fixed, 8);
		buffer_write(_param_buffer, buffer_f64, _x);
		buffer_write(_param_buffer, buffer_f64, _y);
		pixelpart_set_effect_input_float2(effect_ptr, _input_id, buffer_get_address(_param_buffer));
		buffer_delete(_param_buffer);
	}

	static set_input_float3 = function(_input_name, _x, _y, _z)
	{
		var _input_id = effect_input_collection.get_input_id(_input_name);
		if _input_id < 0
		{
			return;
		}

		var _param_buffer = buffer_create(3 * 8, buffer_fixed, 8);
		buffer_write(_param_buffer, buffer_f64, _x);
		buffer_write(_param_buffer, buffer_f64, _y);
		buffer_write(_param_buffer, buffer_f64, _z);
		pixelpart_set_effect_input_float3(effect_ptr, _input_id, buffer_get_address(_param_buffer));
		buffer_delete(_param_buffer);
	}

	static set_input_float4 = function(_input_name, _x, _y, _z, _w)
	{
		var _input_id = effect_input_collection.get_input_id(_input_name);
		if _input_id < 0
		{
			return;
		}

		var _param_buffer = buffer_create(4 * 8, buffer_fixed, 8);
		buffer_write(_param_buffer, buffer_f64, _x);
		buffer_write(_param_buffer, buffer_f64, _y);
		buffer_write(_param_buffer, buffer_f64, _z);
		buffer_write(_param_buffer, buffer_f64, _w);
		pixelpart_set_effect_input_float4(effect_ptr, _input_id, buffer_get_address(_param_buffer));
		buffer_delete(_param_buffer);
	}

	static get_input_bool = function(_input_name)
	{
		var _input_id = effect_input_collection.get_input_id(_input_name);
		if _input_id < 0
		{
			return;
		}

		return pixelpart_get_effect_input_bool(effect_ptr, _input_id);
	}

	static get_input_int = function(_input_name)
	{
		var _input_id = effect_input_collection.get_input_id(_input_name);
		if _input_id < 0
		{
			return;
		}

		return pixelpart_get_effect_input_int(effect_ptr, _input_id);
	}

	static get_input_float = function(_input_name)
	{
		var _input_id = effect_input_collection.get_input_id(_input_name);
		if _input_id < 0
		{
			return;
		}

		return pixelpart_get_effect_input_float(effect_ptr, _input_id);
	}

	static get_input_float2 = function(_input_name)
	{
		var _input_id = effect_input_collection.get_input_id(_input_name);
		if _input_id < 0
		{
			return;
		}

		var _result_buffer = buffer_create(2 * 8, buffer_fixed, 8);
		pixelpart_get_effect_input_float2(effect_ptr, _input_id, buffer_get_address(_result_buffer))
		var _x = buffer_read(_result_buffer, buffer_f64);
		var _y = buffer_read(_result_buffer, buffer_f64);
		buffer_delete(_result_buffer);

		return [_x, _y];
	}

	static get_input_float3 = function(_input_name)
	{
		var _input_id = effect_input_collection.get_input_id(_input_name);
		if _input_id < 0
		{
			return;
		}

		var _result_buffer = buffer_create(3 * 8, buffer_fixed, 8);
		pixelpart_get_effect_input_float3(effect_ptr, _input_id, buffer_get_address(_result_buffer))
		var _x = buffer_read(_result_buffer, buffer_f64);
		var _y = buffer_read(_result_buffer, buffer_f64);
		var _z = buffer_read(_result_buffer, buffer_f64);
		buffer_delete(_result_buffer);

		return [_x, _y, _z];
	}

	static get_input_float4 = function(_input_name)
	{
		var _input_id = effect_input_collection.get_input_id(_input_name);
		if _input_id < 0
		{
			return;
		}

		var _result_buffer = buffer_create(4 * 8, buffer_fixed, 8);
		pixelpart_get_effect_input_float4(effect_ptr, _input_id, buffer_get_address(_result_buffer))
		var _x = buffer_read(_result_buffer, buffer_f64);
		var _y = buffer_read(_result_buffer, buffer_f64);
		var _z = buffer_read(_result_buffer, buffer_f64);
		var _w = buffer_read(_result_buffer, buffer_f64);
		buffer_delete(_result_buffer);

		return [_x, _y, _z, _w];
	}

	#endregion

	#region Triggers

	static activate_trigger = function(_trigger_name)
	{
		var _trigger_id = trigger_collection.get_trigger_id(_trigger_name);
		if _trigger_id < 0
		{
			return;
		}

		pixelpart_activate_trigger(effect_ptr, _trigger_id);
	}

	static is_trigger_activated = function(_trigger_name)
	{
		var _trigger_id = trigger_collection.get_trigger_id(_trigger_name);
		if _trigger_id < 0
		{
			return;
		}

		return pixelpart_is_trigger_activated(effect_ptr, _trigger_id);
	}

	#endregion

	#region Nodes

	static find_node = function(_node_name)
	{
		if effect_ptr == pointer_null
		{
			show_debug_message("[Pixelpart] Effect is not associated with any effect asset");
			return undefined;
		}

		var _id = pixelpart_find_node(effect_ptr, _node_name);
		if !pixelpart_node_exists(effect_ptr, _id)
		{
			return undefined;
		}

		var _node = pixelpart_create_node(effect_ptr, _id);
		if is_undefined(_node)
		{
			show_debug_message("[Pixelpart] Failed to create node");
		}

		return _node;
	}

	static get_node = function(_id)
	{
		if effect_ptr == pointer_null
		{
			show_debug_message("[Pixelpart] Effect is not associated with any effect asset");
			return undefined;
		}

		if !pixelpart_node_exists(effect_ptr, _id)
		{
			return undefined;
		}

		var _node = pixelpart_create_node(effect_ptr, _id);
		if is_undefined(_node)
		{
			show_debug_message("[Pixelpart] Failed to create node");
		}

		return _node;
	}

	static get_node_at_index = function(_index)
	{
		if effect_ptr == pointer_null
		{
			show_debug_message("[Pixelpart] Effect is not associated with any effect asset");
			return undefined;
		}

		var _id = pixelpart_find_node_by_index(effect_ptr, _index);
		if !pixelpart_node_exists(effect_ptr, _id)
		{
			return undefined;
		}

		var _node = pixelpart_create_node(effect_ptr, _id);
		if is_undefined(_node)
		{
			show_debug_message("[Pixelpart] Failed to create node");
		}

		return _node;
	}

	#endregion

	#region Particle types

	static find_particle_type = function(_particle_type_name)
	{
		if effect_ptr == pointer_null
		{
			show_debug_message("[Pixelpart] Effect is not associated with any effect asset");
			return undefined;
		}

		var _id = pixelpart_find_particle_type(effect_ptr, _particle_type_name);
		if !pixelpart_particle_type_exists(effect_ptr, _id)
		{
			return undefined;
		}

		var _particle_type = new PixelpartParticleType(effect_ptr, _id);
		if is_undefined(_particle_type)
		{
			show_debug_message("[Pixelpart] Failed to create particle type");
		}

		return _particle_type;
	}

	static get_particle_type = function(_id)
	{
		if effect_ptr == pointer_null
		{
			show_debug_message("[Pixelpart] Effect is not associated with any effect asset");
			return undefined;
		}

		if !pixelpart_particle_type_exists(effect_ptr, _id)
		{
			return undefined;
		}

		var _particle_type = new PixelpartParticleType(effect_ptr, _id);
		if is_undefined(_particle_type)
		{
			show_debug_message("[Pixelpart] Failed to create particle type");
		}

		return _particle_type;
	}

	static get_particle_type_at_index = function(_index)
	{
		if effect_ptr == pointer_null
		{
			show_debug_message("[Pixelpart] Effect is not associated with any effect asset");
			return undefined;
		}

		var _id = pixelpart_find_particle_type_by_index(effect_ptr, _index);
		if !pixelpart_particle_type_exists(effect_ptr, _id)
		{
			return undefined;
		}

		var _particle_type = new PixelpartParticleType(effect_ptr, _id);
		if is_undefined(_particle_type)
		{
			show_debug_message("[Pixelpart] Failed to create particle type");
		}

		return _particle_type;
	}

	#endregion
}
