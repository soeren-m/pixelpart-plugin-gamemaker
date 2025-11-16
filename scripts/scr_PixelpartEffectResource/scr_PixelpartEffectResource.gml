/// @desc Resource for a Pixelpart effect that is contained in a ppfx file.
function PixelpartEffectResource() constructor
{
	// Effect data as buffer.
	data_buffer = -1;

	/// @desc Import data from a ppfx file.
	/// @param {string} _filepath File to import
	static load = function(_filepath)
	{
		if buffer_exists(data_buffer)
		{
			show_debug_message("[Pixelpart] Effect resource is already loaded");
			return;
		}

		// Load file into memory
		data_buffer = buffer_load(_filepath);
	}

	/// @desc Release the loaded effect.
	static cleanup = function()
	{
		if !buffer_exists(data_buffer)
		{
			show_debug_message("[Pixelpart] Effect resource has not been loaded");
			return;
		}

		buffer_delete(data_buffer);
		data_buffer = -1;
	}
}
