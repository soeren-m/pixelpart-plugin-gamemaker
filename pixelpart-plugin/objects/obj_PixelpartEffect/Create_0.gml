/// @desc Load effect

effect_resource = new PixelpartEffectResource();
effect_resource.load(effect_resource_path);

effect = new PixelpartEffect(effect_resource);

// Event that is invoked when the effect is finished.
// This event is never invoked for effects with repeating particle emitters.
finished_event = effect.finished_event;

// Custom effect event.
effect_event = effect.effect_event;

/// @desc Restart the effect.
/// @param {bool} _clear Whether to remove existing particles
restart = function(_clear)
{
	effect.restart(_clear);
}

/// @desc Generate particles of the given type from the given emitter.
/// @param {string} _particle_emitter_name Name of the particle emitter
/// @param {string} _particle_type_name Name of the particle type
/// @param {real} _count Number of particles to generate
spawn_particles = function(_particle_emitter_name, _particle_type_name, _count)
{
	effect.spawn_particles(_particle_emitter_name, _particle_type_name, _count);
}

/// @desc Time in seconds since the effect has started playing.
get_current_time = function()
{
	return effect.get_current_time();
}

#region Inputs

/// @desc Set effect input to the given value. The effect input must be of type bool.
/// @param {string} _input_name Name of the effect input
/// @param {bool} _value New value
set_input_bool = function(_input_name, _value)
{
	effect.set_input_bool(_input_name, _value);
}

// @desc Set effect input to the given value. The effect input must be of type int.
/// @param {string} _input_name Name of the effect input
/// @param {real} _value New value
set_input_int = function(_input_name, _value)
{
	effect.set_input_int(_input_name, _value);
}

/// @desc Set effect input to the given value. The effect input must be of type float.
/// @param {string} _input_name Name of the effect input
/// @param {real} _value New value
set_input_float = function(_input_name, _value)
{
	effect.set_input_float(_input_name, _value);
}

/// @desc Set effect input to the given value. The effect input must be of type float2.
/// @param {string} _input_name Name of the effect input
/// @param {real} _x X component of new value
/// @param {real} _y Y component of new value
set_input_float2 = function(_input_name, _x, _y)
{
	effect.set_input_float2(_input_name, _x, _y);
}

/// @desc Set effect input to the given value. The effect input must be of type float3.
/// @param {string} _input_name Name of the effect input
/// @param {real} _x X component of new value
/// @param {real} _y Y component of new value
/// @param {real} _z Z component of new value
set_input_float3 = function(_input_name, _x, _y, _z)
{
	effect.set_input_float3(_input_name, _x, _y, _z);
}

/// @desc Set effect input to the given value. The effect input must be of type float4.
/// @param {string} _input_name Name of the effect input
/// @param {real} _x X component of new value
/// @param {real} _y Y component of new value
/// @param {real} _z Z component of new value
/// @param {real} _w W component of new value
set_input_float4 = function(_input_name, _x, _y, _z, _w)
{
	effect.set_input_float4(_input_name, _x, _y, _z, _w);
}

/// @desc Return value of an effect input. The effect input must be of type bool.
/// @param {string} _input_name Name of the effect input
/// @returns {bool} Value of the effect input
get_input_bool = function(_input_name)
{
	return effect.get_input_bool(_input_name);
}

/// @desc Return value of an effect input. The effect input must be of type int.
/// @param {string} _input_name Name of the effect input
/// @returns {real} Value of the effect input
get_input_int = function(_input_name)
{
	return effect.get_input_int(_input_name);
}

/// @desc Return value of an effect input. The effect input must be of type float.
/// @param {string} _input_name Name of the effect input
/// @returns {real} Value of the effect input
get_input_float = function(_input_name)
{
	return effect.get_input_float(_input_name);
}

/// @desc Return value of an effect input. The effect input must be of type float2.
/// @param {string} _input_name Name of the effect input
/// @returns {array} Value of the effect input (x, y)
get_input_float2 = function(_input_name)
{
	return effect.get_input_float2(_input_name);
}

/// @desc Return value of an effect input. The effect input must be of type float3.
/// @param {string} _input_name Name of the effect input
/// @returns {array} Value of the effect input (x, y, z)
get_input_float3 = function(_input_name)
{
	return effect.get_input_float3(_input_name);
}

/// @desc Return value of an effect input. The effect input must be of type float4.
/// @param {string} _input_name Name of the effect input
/// @returns {array} Value of the effect input (x, y, z, w)
get_input_float4 = function(_input_name)
{
	return effect.get_input_float4(_input_name);
}

#endregion

#region Triggers

/// @desc Activate trigger with the given name.
/// @param {string} _trigger_name Name of the trigger
activate_trigger = function(_trigger_name)
{
	effect.activate_trigger(_trigger_name);
}

/// @desc Return whether the trigger with the given name was activated.
/// @param {string} _trigger_name Name of the trigger
/// @returns {bool} true if the trigger was activated
is_trigger_activated = function(_trigger_name)
{
	return effect.is_trigger_activated(_trigger_name);
}

#endregion

#region Nodes

/// @desc Return the node with the given name.
/// @param {string} _node_name Node name
/// @returns {struct|undefined} Node or undefined if no node with this name exists
find_node = function(_node_name)
{
	return effect.find_node(_node_name);
}

/// @desc Return the node with the given ID.
/// @param {real} _id Node ID
/// @returns {struct|undefined} Node or undefined if no node with this ID exists
get_node = function(_id)
{
	return effect.get_node(_id);
}

/// @desc Return the node at the given index.
/// @param {real} _index Node index, starting from 0
/// @returns {struct|undefined} Node or undefined if no node at this index exists
get_node_at_index = function(_index)
{
	return effect.get_node_at_index(_index);
}

#endregion

#region Particle types

/// @desc Return the particle type with the given name.
/// @param {string} _particle_type_name Particle type name
/// @returns {struct|undefined} Particle type or undefined if no particle type with this name exists
find_particle_type = function(_particle_type_name)
{
	return effect.find_particle_type(_particle_type_name);
}

/// @desc Return the particle type with the given ID.
/// @param {real} _id Particle type ID
/// @returns {struct|undefined} Particle type or undefined if no particle type with this ID exists
get_particle_type = function(_id)
{
	return effect.get_particle_type(_id);
}

/// @desc Return the particle type at the given index.
/// @param {real} _index Particle type index
/// @returns {struct|undefined} Particle type or undefined if no particle type at this index exists
get_particle_type_at_index = function(_index)
{
	return effect.get_particle_type_at_index(_index);
}

#endregion
