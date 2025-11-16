/// @desc Force field that simulates drag.
/// Drag fields slow down particles mimicking the effects of drag.
/// @param {pointer} _effect_ptr Pointer to internal effect runtime object
/// @param {real} _node_id Node ID
function PixelpartDragField(_effect_ptr, _node_id) : PixelpartForceField(_effect_ptr, _node_id) constructor
{
	// How strongly the drag force is influenced by the particle velocity.
	velocity_influence = new PixelpartStaticPropertyFloat(
		ptr(pixelpart_drag_field_get_velocity_influence(_effect_ptr, _node_id)));

	// How strongly the drag force is influenced by the particle size.
	size_influence = new PixelpartStaticPropertyFloat(
		ptr(pixelpart_drag_field_get_size_influence(_effect_ptr, _node_id)));
}
