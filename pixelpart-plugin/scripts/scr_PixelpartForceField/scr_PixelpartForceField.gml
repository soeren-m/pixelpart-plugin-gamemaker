/// @desc Node that interacts with particles in a given area by applying forces
/// and changing the particles' velocity.
/// Force fields affect particles by attracting, repelling or accelerating them in some direction
/// and can be used to model gravity, wind and other natural effects.
/// @param {pointer} _effect_ptr Pointer to internal effect runtime object
/// @param {real} _node_id Node ID
function PixelpartForceField(_effect_ptr, _node_id) : PixelpartNode(_effect_ptr, _node_id) constructor
{
	// How strongly particles are affected by the force field.
	// Negative values reverse the force direction. Attraction fields then repel particles, for example.
	strength = new PixelpartAnimatedPropertyFloat(
		ptr(pixelpart_force_field_get_strength(_effect_ptr, _node_id)));

	/// @desc Set whether the force field has an infinite area of effect.
	/// @param {bool} _mode Whether the force field has an infinite area of effect
	static set_infinite = function(_mode)
	{
		pixelpart_force_field_set_infinite(effect_ptr, node_id, _mode);
	}

	/// @desc Whether the force field has an infinite area of effect.
	/// @returns {bool} Whether the force field has an infinite area of effect
	static is_infinite = function()
	{
		return bool(pixelpart_force_field_is_infinite(effect_ptr, node_id));
	}
}
