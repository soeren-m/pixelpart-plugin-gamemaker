function PixelpartEffectResource() constructor
{
	data_buffer = -1;

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