/// @desc An object in an effect like a particle emitter or a force field.
/// Nodes can be moved, rotated and scaled and move together with their parent node if present.
/// @param {string} _effect_ptr Pointer to internal effect runtime object
/// @param {real} _node_id Node ID
function PixelpartNode(_effect_ptr, _node_id) constructor
{
	effect_ptr = _effect_ptr;
	node_id = _node_id;

	// Position of the node.
	position = new PixelpartAnimatedPropertyFloat3(
		pixelpart_node_get_position(_effect_ptr, _node_id));

	// Rotation of the node in degrees.
	// For 3D effects, the rotation is composed of roll, yaw and pitch.
	rotation = new PixelpartAnimatedPropertyFloat3(
		pixelpart_node_get_rotation(_effect_ptr, _node_id));

	// Size of the node.
	scale = new PixelpartAnimatedPropertyFloat3(
		pixelpart_node_get_scale(_effect_ptr, _node_id));

	/// @desc Type of the node.
	/// @returns {real} Type
	static get_type = function()
	{
		return pixelpart_node_get_type(effect_ptr, node_id);
	}

	/// @desc ID of the node.
	/// @returns {real} ID
	static get_id = function()
	{
		return node_id;
	}

	/// @desc ID of the node's parent.
	/// @returns {real} Parent ID or "-1" if the node has no parent
	static get_parent_id = function()
	{
		return pixelpart_node_get_parent_id(effect_ptr, node_id);
	}

	/// @desc Name of the node.
	/// @returns {string} Name
	static get_name = function()
	{
		return pixelpart_node_get_name(effect_ptr, node_id);
	}

	/// @desc Set time until the node becomes active.
	/// @param {real} _start Time in seconds until the node becomes active
	static set_lifetime_start = function(_start)
	{
		pixelpart_node_set_start(effect_ptr, node_id, _start);
	}

	/// @desc Time in seconds until the node becomes active.
	/// @returns {real} Time in seconds until the node becomes active
	static get_lifetime_start = function()
	{
		return pixelpart_node_get_start(effect_ptr, node_id);
	}

	/// @desc Set how long the node stays active in seconds.
	/// @param {real} _duration How long the node stays active in seconds
	static set_lifetime_duration = function(_duration)
	{
		pixelpart_node_set_duration(effect_ptr, node_id, _duration);
	}

	/// @desc How long the node is active in seconds.
	/// @returns {real} How long the node is active in seconds
	static get_lifetime_duration = function()
	{
		return pixelpart_node_get_duration(effect_ptr, node_id);
	}

	/// @desc Set whether the node repeats its behavior after its lifetime is over.
	/// @param {bool} _repeat Wether the node repeats its behavior after its lifetime is over
	static set_repeat = function(_repeat)
	{
		pixelpart_node_set_repeat(effect_ptr, node_id, _repeat);
	}

	/// @desc Wether the node repeats its behavior after its lifetime is over.
	/// @returns {bool} Wether the node repeats its behavior after its lifetime is over
	static is_repeating = function()
	{
		return bool(pixelpart_node_is_repeating(effect_ptr, node_id));
	}

	/// @desc Return whether the node is active at the current point in time.
	/// @returns {bool} Whether the node is active at the current point in time.
	static is_active = function()
	{
		return bool(pixelpart_node_is_active(effect_ptr, node_id));
	}

	/// @desc Return the time fraction the emitter has been active for, in range 0.0 (0%) to 1.0 (100%).
	/// @returns {real} Time fraction the emitter has been active for
	static get_local_time = function()
	{
		return pixelpart_node_get_local_time(effect_ptr, node_id);
	}
}
