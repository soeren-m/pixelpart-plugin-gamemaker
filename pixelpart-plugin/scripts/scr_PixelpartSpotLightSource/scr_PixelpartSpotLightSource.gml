/// @desc Light source similar to a point light but emitted light is restricted to a cone shape.
/// The direction is determined by the node's orientation property.
/// @param {pointer} _effect_ptr Pointer to internal effect runtime object
/// @param {real} _node_id Node ID
function PixelpartSpotLightSource(_effect_ptr, _node_id) : PixelpartLightSource(_effect_ptr, _node_id) constructor
{
	// Width of the light cone in degrees.
	spot_angle = new PixelpartAnimatedPropertyFloat(
		ptr(pixelpart_spot_light_source_get_spot_angle(_effect_ptr, _node_id)));

	// How much the light looses intensity near the edge of the light cone.
	spot_angle_attenuation = new PixelpartAnimatedPropertyFloat(
		ptr(pixelpart_spot_light_source_get_spot_angle_attenuation(_effect_ptr, _node_id)));
}
