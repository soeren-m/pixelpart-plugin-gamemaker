effect_resource = new PixelpartEffectResource();
effect_resource.load(effect_resource_path);

effect = new PixelpartEffect(effect_resource);

finished_event = effect.finished_event;

restart = function(_clear)
{
	effect.restart(_clear);
}

spawn_particles = function(_particle_emitter_name, _particle_type_name, _count)
{
	effect.spawn_particles(_particle_emitter_name, _particle_type_name, _count);
}

get_current_time = function()
{
	return effect.get_current_time();
}

is_3d = function()
{
	return effect.is_3d();
}

#region Inputs

set_input_bool = function(_input_name, _value)
{
	effect.set_input_bool(_input_name, _value);
}

set_input_int = function(_input_name, _value)
{
	effect.set_input_int(_input_name, _value);
}

set_input_float = function(_input_name, _value)
{
	effect.set_input_float(_input_name, _value);
}

set_input_float2 = function(_input_name, _x, _y)
{
	effect.set_input_float2(_input_name, _x, _y);
}

set_input_float3 = function(_input_name, _x, _y, _z)
{
	effect.set_input_float3(_input_name, _x, _y, _z);
}

set_input_float4 = function(_input_name, _x, _y, _z, _w)
{
	effect.set_input_float4(_input_name, _x, _y, _z, _w);
}

get_input_bool = function(_input_name)
{
	return effect.get_input_bool(_input_name);
}

get_input_int = function(_input_name)
{
	return effect.get_input_int(_input_name);
}

get_input_float = function(_input_name)
{
	return effect.get_input_float(_input_name);
}

get_input_float2 = function(_input_name)
{
	return effect.get_input_float2(_input_name);
}

get_input_float3 = function(_input_name)
{
	return effect.get_input_float3(_input_name);
}

get_input_float4 = function(_input_name)
{
	return effect.get_input_float4(_input_name);
}

#endregion

#region Triggers

activate_trigger = function(_trigger_name)
{
	effect.activate_trigger(_trigger_name);
}

is_trigger_activated = function(_trigger_name)
{
	return effect.is_trigger_activated(_trigger_name);
}

#endregion

#region Nodes

find_node = function(_node_name)
{
	return effect.find_node(_node_name);
}

get_node = function(_id)
{
	return effect.get_node(_id);
}

get_node_at_index = function(_index)
{
	return effect.get_node_at_index(_index);
}

#endregion

#region Particle types

find_particle_type = function(_particle_type_name)
{
	return effect.find_particle_type(_particle_type_name);
}

get_particle_type = function(_id)
{
	return effect.get_particle_type(_id);
}

get_particle_type_at_index = function(_index)
{
	return effect.get_particle_type_at_index(_index);
}

#endregion
