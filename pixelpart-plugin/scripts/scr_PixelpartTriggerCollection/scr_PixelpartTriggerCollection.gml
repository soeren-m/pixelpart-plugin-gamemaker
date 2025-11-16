function PixelpartTriggerCollection(_effect_ptr) constructor
{
	var _trigger_count = pixelpart_get_trigger_count(_effect_ptr);
	var _id_buffer = buffer_create(_trigger_count * 4, buffer_fixed, 4);
	var _name_buffer = buffer_create(_trigger_count * 1024, buffer_fixed, 1);

	pixelpart_get_triggers(_effect_ptr,
		buffer_get_address(_id_buffer),
		buffer_get_address(_name_buffer));

	triggers = {};

	for (var _trigger_index = 0; _trigger_index < _trigger_count; _trigger_index++)
	{
		var _trigger_id = buffer_read(_id_buffer, buffer_u32);
		var _trigger_name = buffer_read(_name_buffer, buffer_string);

		triggers[$ _trigger_name] = _trigger_id;
	}

	buffer_delete(_id_buffer);
	buffer_delete(_name_buffer);

	static get_trigger_id = function(_name)
	{
		if !struct_exists(triggers, _name)
		{
			show_debug_message("[Pixelpart] Unknown trigger \"{0}\"", _name);
			return -1;
		}

		return triggers[$ _name];
	}
}
