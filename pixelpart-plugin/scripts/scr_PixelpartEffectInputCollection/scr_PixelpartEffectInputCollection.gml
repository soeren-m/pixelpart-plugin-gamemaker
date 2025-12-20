function PixelpartEffectInputCollection(_effect_ptr) constructor
{
	if _effect_ptr == pointer_null
	{
		effect_inputs = {};
		return;
	}

	var _input_count = pixelpart_get_effect_input_count(_effect_ptr);
	var _id_buffer = buffer_create(_input_count * 4, buffer_fixed, 4);
	var _type_buffer = buffer_create(_input_count * 4, buffer_fixed, 4);
	var _name_buffer = buffer_create(_input_count * 1024, buffer_fixed, 1);

	pixelpart_get_effect_inputs(_effect_ptr,
		buffer_get_address(_id_buffer),
		buffer_get_address(_type_buffer),
		buffer_get_address(_name_buffer));

	effect_inputs = {};

	for (var _input_index = 0; _input_index < _input_count; _input_index++)
	{
		var _input_id = buffer_read(_id_buffer, buffer_u32);
		var _input_name = buffer_read(_name_buffer, buffer_string);

		effect_inputs[$ _input_name] = _input_id;
	}

	buffer_delete(_id_buffer);
	buffer_delete(_type_buffer);
	buffer_delete(_name_buffer);

	static get_input_id = function(_name)
	{
		if !struct_exists(effect_inputs, _name)
		{
			show_debug_message("[Pixelpart] Unknown effect input \"{0}\"", _name);
			return -1;
		}

		return effect_inputs[$ _name];
	}
}
