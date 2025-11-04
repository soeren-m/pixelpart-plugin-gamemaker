function PixelpartLightSource(_effect_ptr, _node_id) : PixelpartNode(_effect_ptr, _node_id) constructor
{
	attenuation = new PixelpartAnimatedPropertyFloat(
		ptr(pixelpart_light_source_get_attenuation(_effect_ptr, _node_id)));
	color = new PixelpartAnimatedPropertyFloat4(
		ptr(pixelpart_light_source_get_color(_effect_ptr, _node_id)));
	intensity = new PixelpartAnimatedPropertyFloat(
		ptr(pixelpart_light_source_get_intensity(_effect_ptr, _node_id)));
}