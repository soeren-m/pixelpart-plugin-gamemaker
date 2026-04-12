function PixelpartEffectEventCollection(_effect_ptr) constructor
{
	if _effect_ptr == ""
	{
		events = {};
		return;
	}

	var _event_count = pixelpart_get_effect_event_count(_effect_ptr);
	var _id_buffer = buffer_create(_event_count * 4, buffer_fixed, 4);
	var _name_buffer = buffer_create(_event_count * 1024, buffer_fixed, 1);

	pixelpart_get_effect_events(_effect_ptr,
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

	events = {};

	for (var _event_index = 0; _event_index < _event_count; _event_index++)
	{
		var _event_id = buffer_read(_id_buffer, buffer_u32);
		var _event_name = buffer_read(os_browser == browser_not_a_browser ? _name_buffer : _name_buffer_copy, buffer_string);

		events[$ _event_id] = _event_name;
	}

	buffer_delete(_id_buffer);
	buffer_delete(_name_buffer);

	if !is_undefined(_name_buffer_copy)
	{
		buffer_delete(_name_buffer_copy);
	}

	static get_event_name = function(_id)
	{
		if !struct_exists(events, _id)
		{
			show_debug_message("[Pixelpart] Unknown event id \"{0}\"", _id);
			return undefined;
		}

		return events[$ _id];
	}
}
