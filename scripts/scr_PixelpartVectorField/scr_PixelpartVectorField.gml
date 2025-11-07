enum PixelpartVectorFieldFilter
{
	NONE = 0,
	LINEAR = 1
}

function PixelpartVectorField(_effect_ptr, _node_id) : PixelpartForceField(_effect_ptr, _node_id) constructor
{
	tightness = new PixelpartAnimatedPropertyFloat(
		ptr(pixelpart_vector_field_get_tightness(_effect_ptr, _node_id)));

	static set_vector_filter = function(_filter)
	{
		pixelpart_vector_field_set_vector_field_filter(effect_ptr, node_id, _filter);
	}
	static get_vector_filter = function()
	{
		return pixelpart_vector_field_get_vector_field_filter(effect_ptr, node_id);
	}
}
