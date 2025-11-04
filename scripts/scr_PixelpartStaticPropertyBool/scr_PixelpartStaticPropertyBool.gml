function PixelpartStaticPropertyBool(_property_ptr) constructor
{
	property_ptr = _property_ptr;

	static value = function()
	{
		return pixelpart_static_property_bool_value(property_ptr);
	}

	static set_base_value = function(_value)
	{
		pixelpart_static_property_bool_set_base_value(property_ptr, _value);
	}
	static get_base_value = function()
	{
		return pixelpart_static_property_bool_get_base_value(property_ptr);
	}
}