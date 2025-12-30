/// @desc Float property animated with keyframes and affected by effect inputs.
/// Scene objects of an effect like particle emitters and force fields have properties that change over time
/// and are affected by effect inputs. Such properties are represented by one of the PixelpartAnimatedProperty classes,
/// depending on the type of the property.
/// @param {string} _property_ptr Property pointer
function PixelpartAnimatedPropertyFloat(_property_ptr) constructor
{
	property_ptr = _property_ptr;

	/// @desc Return the (interpolated) value of the animation property at time "_position".
	/// @param {real} _position Time between 0 and 1
	/// @returns {real} Value of the property
	static at = function(_position)
	{
		return pixelpart_animated_property_float_at(property_ptr, _position);
	}

	/// @desc Add a keyframe at time "_position" with value "_value".
	/// @param {real} _position Time between 0 and 1
	/// @param {real} _value Value of the property at the given time
	static add_keyframe = function(_position, _value)
	{
		pixelpart_animated_property_float_add_keyframe(property_ptr, _position, _value);
	}

	/// @desc Remove the keyframe with the given index from the animation.
	/// @param {real} _index Index to remove
	static remove_keyframe = function(_index)
	{
		pixelpart_animated_property_float_remove_keyframe(property_ptr, _index);
	}

	/// @desc Change the value of the keyframe with the given index.
	/// @param {real} _index Keyframe index
	/// @param {real} _value New value
	static set_keyframe_value = function(_index, _value)
	{
		pixelpart_animated_property_float_set_keyframe_value(property_ptr, _index, _value);
	}

	/// @desc Move the time of the keyframe with the given index to "_position".
	/// @param {real} _index Keyframe index
	/// @param {real} _position New time between 0 and 1
	static set_keyframe_position = function(_index, _position)
	{
		pixelpart_animated_property_float_set_keyframe_position(property_ptr, _index, _position);
	}

	/// @desc Remove all keyframes from the animation.
	static clear_keyframes = function()
	{
		pixelpart_animated_property_float_clear_keyframes(property_ptr);
	}

	/// @desc Return the number of keyframes.
	/// @returns {real} Number of keyframes
	static keyframe_count = function()
	{
		return pixelpart_animated_property_float_keyframe_count(property_ptr);
	}

	/// @desc Return the value of the keyframe with the given index.
	/// @param {real} _index Keyframe index
	/// @returns {real} Keyframe value
	static keyframe_value = function(_index)
	{
		return pixelpart_animated_property_float_keyframe_value(property_ptr, _index);
	}

	/// @desc Return the index of the keyframe closest to time "_position".
	/// @param {real} _position Time between 0 and 1
	/// @param {real} _epsilon Maximum differerence in time to consider to keyframes at the same time
	/// @returns {real} Keyframe index
	static keyframe_index = function(_position, _epsilon)
	{
		return pixelpart_animated_property_float_keyframe_index(property_ptr, _position, _epsilon);
	}

	/// @desc Set interpolation applied to the animation curve.
	/// @param {real} _method Interpolation method
	static set_keyframe_interpolation = function(_method)
	{
		pixelpart_animated_property_float_set_keyframe_interpolation(property_ptr, _method);
	}

	/// @desc Return interpolation applied to the animation curve.
	/// @returns {real} Interpolation method
	static get_keyframe_interpolation = function()
	{
		return pixelpart_animated_property_float_get_keyframe_interpolation(property_ptr);
	}

	/// @desc Enable an adaptive cache, which resizes itself automatically if the number of keyframes increases or decreases a lot.
	static enable_adaptive_cache = function()
	{
		pixelpart_animated_property_float_enable_adaptive_cache(property_ptr);
	}

	/// @desc Enable a fixed cache with the given size, which only stores up to "_size" different values.
	/// @param {real} _size Cache size
	static enable_fixed_cache = function(_size)
	{
		pixelpart_animated_property_float_enable_fixed_cache(property_ptr, _size);
	}
}
