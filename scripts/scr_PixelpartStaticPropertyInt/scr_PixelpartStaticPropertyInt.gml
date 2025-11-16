/// @desc Int property affected by effect inputs.
/// Scene objects of an effect like particle emitters and force fields have properties that do not change over time,
/// but can be affected by effect inputs. Such properties are represented by one of the PixelpartStaticProperty classes.
/// @param {pointer} _property_ptr Property pointer
function PixelpartStaticPropertyInt(_property_ptr) constructor
{
	property_ptr = _property_ptr;

	/// @desc Return value with effect inputs taken into account.
	/// @returns {real} Property value
	static value = function()
	{
		return pixelpart_static_property_int_value(property_ptr);
	}

	/// @desc Set base value (effect inputs not taken into account).
	/// @param {real} _value Property value
	static set_base_value = function(_value)
	{
		pixelpart_static_property_int_set_base_value(property_ptr, _value);
	}

	/// @desc Return base value (effect inputs not taken into account).
	/// @returns {array} Property value
	static get_base_value = function()
	{
		return pixelpart_static_property_int_get_base_value(property_ptr);
	}
}
