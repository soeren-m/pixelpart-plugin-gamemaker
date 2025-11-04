function PixelpartCollider(_effect_ptr, _node_id) : PixelpartNode(_effect_ptr, _node_id) constructor
{
	kill_on_contact = new PixelpartStaticPropertyBool(
		ptr(pixelpart_collider_get_kill_on_contact(_effect_ptr, _node_id)));
	bounce = new PixelpartAnimatedPropertyFloat(
		ptr(pixelpart_collider_get_bounce(_effect_ptr, _node_id)));
	friction = new PixelpartAnimatedPropertyFloat(
		ptr(pixelpart_collider_get_friction(_effect_ptr, _node_id)));
}