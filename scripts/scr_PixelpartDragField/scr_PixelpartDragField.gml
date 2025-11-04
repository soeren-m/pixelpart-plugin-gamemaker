function PixelpartDragField(_effect_ptr, _node_id) : PixelpartForceField(_effect_ptr, _node_id) constructor
{
	velocity_influence = new PixelpartStaticPropertyFloat(
		ptr(pixelpart_drag_field_get_velocity_influence(_effect_ptr, _node_id)));
	size_influence = new PixelpartStaticPropertyFloat(
		ptr(pixelpart_drag_field_get_size_influence(_effect_ptr, _node_id)));
}