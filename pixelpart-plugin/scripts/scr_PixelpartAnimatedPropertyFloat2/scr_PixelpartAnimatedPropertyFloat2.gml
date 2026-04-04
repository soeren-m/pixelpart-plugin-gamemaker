/// @desc Float2 property animated with keyframes and affected by effect inputs.
/// Scene objects of an effect like particle emitters and force fields have properties that change over time
/// and are affected by effect inputs. Such properties are represented by one of the PixelpartAnimatedProperty classes,
/// depending on the type of the property.
/// @param {string} _property_ptr Property pointer
function PixelpartAnimatedPropertyFloat2(_property_ptr) constructor
{
	property_ptr = _property_ptr;

	/// @desc Return the (interpolated) value of the animation property at time "_position".
	/// @param {real} _position Time between 0 and 1
	/// @returns {array} Value (x, y) of the property
	static at = function(_position)
	{
		var _result_buffer = buffer_create(2 * 8, buffer_fixed, 8);
		pixelpart_animated_property_float2_at(property_ptr, _position,
			buffer_get_address(_result_buffer));
		var _x = buffer_read(_result_buffer, buffer_f64);
		var _y = buffer_read(_result_buffer, buffer_f64);
		buffer_delete(_result_buffer);

		return [_x, _y];
	}

	/// @desc Add a keyframe at time "_position" with value "_value".
	/// @param {real} _position Time between 0 and 1
	/// @param {real} _x X value of the property at the given time
	/// @param {real} _y Y value of the property at the given time
	static add_keyframe = function(_position, _x, _y)
	{
		var _param_buffer = buffer_create(2 * 8, buffer_fixed, 8);
		buffer_write(_param_buffer, buffer_f64, _x);
		buffer_write(_param_buffer, buffer_f64, _y);
		pixelpart_animated_property_float2_add_keyframe(property_ptr, _position,
			buffer_get_address(_param_buffer));
		buffer_delete(_param_buffer);
	}

	/// @desc Remove the keyframe with the given index from the animation.
	/// @param {real} _index Index to remove
	static remove_keyframe = function(_index)
	{
		pixelpart_animated_property_float2_remove_keyframe(property_ptr, _index);
	}

	/// @desc Change the value of the keyframe with the given index.
	/// @param {real} _index Keyframe index
	/// @param {real} _x New X value
	/// @param {real} _y New Y value
	static set_keyframe_value = function(_index, _x, _y)
	{
		var _param_buffer = buffer_create(2 * 8, buffer_fixed, 8);
		buffer_write(_param_buffer, buffer_f64, _x);
		buffer_write(_param_buffer, buffer_f64, _y);
		pixelpart_animated_property_float2_set_keyframe_value(property_ptr, _index,
			buffer_get_address(_param_buffer));
		buffer_delete(_param_buffer);
	}

	/// @desc Move the time of the keyframe with the given index to "_position".
	/// @param {real} _index Keyframe index
	/// @param {real} _position New time between 0 and 1
	static set_keyframe_position = function(_index, _position)
	{
		pixelpart_animated_property_float2_set_keyframe_position(property_ptr, _index, _position);
	}

	/// @desc Remove all keyframes from the animation.
	static clear_keyframes = function()
	{
		pixelpart_animated_property_float2_clear_keyframes(property_ptr);
	}

	/// @desc Return the number of keyframes.
	/// @returns {real} Number of keyframes
	static keyframe_count = function()
	{
		return pixelpart_animated_property_float2_keyframe_count(property_ptr);
	}

	/// @desc Return the value of the keyframe with the given index.
	/// @param {real} _index Keyframe index
	/// @returns {array} Keyframe value (x, y)
	static keyframe_value = function(_index)
	{
		var _result_buffer = buffer_create(2 * 8, buffer_fixed, 8);
		pixelpart_animated_property_float2_keyframe_value(property_ptr, _index,
			buffer_get_address(_result_buffer));
		var _x = buffer_read(_result_buffer, buffer_f64);
		var _y = buffer_read(_result_buffer, buffer_f64);
		buffer_delete(_result_buffer);

		return [_x, _y];
	}

	/// @desc Return the index of the keyframe closest to time "_position".
	/// @param {real} _position Time between 0 and 1
	/// @param {real} _epsilon Maximum differerence in time to consider to keyframes at the same time
	/// @returns {real} Keyframe index
	static keyframe_index = function(_position, _epsilon)
	{
		return pixelpart_animated_property_float2_keyframe_index(property_ptr, _position, _epsilon);
	}

	/// @desc Set interpolation applied to the animation curve.
	/// @param {real} _method Interpolation method
	static set_keyframe_interpolation = function(_method)
	{
		pixelpart_animated_property_float2_set_keyframe_interpolation(property_ptr, _method);
	}

	/// @desc Return interpolation applied to the animation curve.
	/// @returns {real} Interpolation method
	static get_keyframe_interpolation = function()
	{
		return pixelpart_animated_property_float2_get_keyframe_interpolation(property_ptr);
	}
}
