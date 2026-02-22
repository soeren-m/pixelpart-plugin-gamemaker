function PixelpartTriggerCollection(_effect_ptr) constructor
{
	if _effect_ptr == ""
	{
		triggers = {};
		return;
	}

	var _trigger_count = pixelpart_get_trigger_count(_effect_ptr);
	var _id_buffer = buffer_create(_trigger_count * 4, buffer_fixed, 4);
	var _name_buffer = buffer_create(_trigger_count * 1024, buffer_fixed, 1);

	pixelpart_get_triggers(_effect_ptr,
		buffer_get_address(_id_buffer),
		buffer_get_address(_name_buffer));

	// For some reason this is needed for HTML5...
	var _name_buffer_copy = undefined
	if os_browser != browser_not_a_browser
	{
		var _name_buffer_size = buffer_get_size(_name_buffer);
		_name_buffer_copy = buffer_create(_name_buffer_size, buffer_fixed, 1);
		buffer_copy(_name_buffer, 0, _name_buffer_size, _name_buffer_copy, 0);
	}

	triggers = {};

	for (var _trigger_index = 0; _trigger_index < _trigger_count; _trigger_index++)
	{
		var _trigger_id = buffer_read(_id_buffer, buffer_u32);
		var _trigger_name = buffer_read(os_browser == browser_not_a_browser ? _name_buffer : _name_buffer_copy, buffer_string);

		triggers[$ _trigger_name] = _trigger_id;
	}

	buffer_delete(_id_buffer);
	buffer_delete(_name_buffer);

	if !is_undefined(_name_buffer_copy)
	{
		buffer_delete(_name_buffer_copy);
	}

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
