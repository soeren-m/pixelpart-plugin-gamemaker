/// @desc Resource for a Pixelpart effect that is contained in a ppfx file.
function PixelpartEffectResource() constructor
{
	// Internal pointer to effect resource.
	resource_ptr = "";

	/// @desc Import data from a ppfx file.
	/// @param {string} _filepath File to import
	static load = function(_filepath)
	{
		if resource_ptr != ""
		{
			show_debug_message("[Pixelpart] Effect resource is already loaded");
			return;
		}

		// Load file into memory
		var _data_buffer = buffer_load(_filepath);
		if !buffer_exists(_data_buffer)
		{
			show_debug_message("[Pixelpart] Failed to read effect resource file");
			return;
		}

		resource_ptr = pixelpart_load_effect_resource(
			buffer_peek(_data_buffer, 0, buffer_string),
			buffer_get_size(_data_buffer));

		buffer_delete(_data_buffer);

		if resource_ptr == ""
		{
			show_debug_message("[Pixelpart] Failed to load effect with error: {0}",
				pixelpart_last_error());
		}
	}

	/// @desc Release the loaded effect.
	static cleanup = function()
	{
		if resource_ptr == ""
		{
			show_debug_message("[Pixelpart] Effect resource has not been loaded");
			return;
		}

		pixelpart_delete_effect_resource(resource_ptr);
		resource_ptr = "";
	}
}
