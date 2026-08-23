/// @desc Force field that moves particles in a vortex around its center.
/// @param {string} _effect_ptr Pointer to internal effect runtime object
/// @param {real} _node_id Node ID
function PixelpartVortexField(_effect_ptr, _node_id) : PixelpartForceField(_effect_ptr, _node_id) constructor
{
	// How strongly particles are accelerated outwards.
	tangential_strength = new PixelpartAnimatedPropertyFloat(
		pixelpart_vortex_field_get_tangential_strength(_effect_ptr, _node_id));

	// How strongly the vortex field attracts particles.
	radial_strength = new PixelpartAnimatedPropertyFloat(
		pixelpart_vortex_field_get_radial_strength(_effect_ptr, _node_id));
}
