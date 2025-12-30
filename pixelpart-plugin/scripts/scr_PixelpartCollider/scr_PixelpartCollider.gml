/// @desc Node particles collide with.
/// When hitting a collider, particles bounce off its surface.
/// @param {string} _effect_ptr Pointer to internal effect runtime object
/// @param {real} _node_id Node ID
function PixelpartCollider(_effect_ptr, _node_id) : PixelpartNode(_effect_ptr, _node_id) constructor
{
	// Whether to kill particles on contact with the collider.
	kill_on_contact = new PixelpartStaticPropertyBool(
		pixelpart_collider_get_kill_on_contact(_effect_ptr, _node_id));

	// How strongly particles bounce back from the collider.
	bounce = new PixelpartAnimatedPropertyFloat(
		pixelpart_collider_get_bounce(_effect_ptr, _node_id));

	// How much particles are slowed down when sliding down the collider.
	friction = new PixelpartAnimatedPropertyFloat(
		pixelpart_collider_get_friction(_effect_ptr, _node_id));
}
