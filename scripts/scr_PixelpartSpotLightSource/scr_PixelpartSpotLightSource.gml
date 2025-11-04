function PixelpartSpotLightSource(_effect_ptr, _node_id) : PixelpartLightSource(_effect_ptr, _node_id) constructor
{
	spot_angle = new PixelpartAnimatedPropertyFloat(
		ptr(pixelpart_spot_light_source_get_spot_angle(_effect_ptr, _node_id)));
	spot_angle_attenuation = new PixelpartAnimatedPropertyFloat(
		ptr(pixelpart_spot_light_source_get_spot_angle_attenuation(_effect_ptr, _node_id)));
}