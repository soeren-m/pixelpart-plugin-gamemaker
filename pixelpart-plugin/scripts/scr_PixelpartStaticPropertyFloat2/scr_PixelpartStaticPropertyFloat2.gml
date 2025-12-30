/// @desc Float2 property affected by effect inputs.
/// Scene objects of an effect like particle emitters and force fields have properties that do not change over time,
/// but can be affected by effect inputs. Such properties are represented by one of the PixelpartStaticProperty classes.
/// @param {string} _property_ptr Property pointer
function PixelpartStaticPropertyFloat2(_property_ptr) constructor
{
	property_ptr = _property_ptr;

	/// @desc Return value with effect inputs taken into account.
	/// @returns {array} Property value (x, y)
	static value = function()
	{
		var _result_buffer = buffer_create(2 * 8, buffer_fixed, 8);
		pixelpart_static_property_float2_value(property_ptr,
			buffer_get_address(_result_buffer));
		var _x = buffer_read(_result_buffer, buffer_f64);
		var _y = buffer_read(_result_buffer, buffer_f64);
		buffer_delete(_result_buffer);

		return [_x, _y];
	}

	/// @desc Set base value (effect inputs not taken into account).
	/// @param {real} _x X component of property value
	/// @param {real} _y Y component of property value
	static set_base_value = function(_x, _y)
	{
		var _param_buffer = buffer_create(2 * 8, buffer_fixed, 8);
		buffer_write(_param_buffer, buffer_f64, _x);
		buffer_write(_param_buffer, buffer_f64, _y);
		pixelpart_static_property_float2_set_base_value(property_ptr,
			buffer_get_address(_param_buffer));
		buffer_delete(_param_buffer);
	}

	/// @desc Return base value (effect inputs not taken into account).
	/// @returns {array} Property value (x, y)
	static get_base_value = function()
	{
		var _result_buffer = buffer_create(2 * 8, buffer_fixed, 8);
		pixelpart_static_property_float2_get_base_value(property_ptr,
			buffer_get_address(_result_buffer));
		var _x = buffer_read(_result_buffer, buffer_f64);
		var _y = buffer_read(_result_buffer, buffer_f64);
		buffer_delete(_result_buffer);

		return [_x, _y];
	}
}
