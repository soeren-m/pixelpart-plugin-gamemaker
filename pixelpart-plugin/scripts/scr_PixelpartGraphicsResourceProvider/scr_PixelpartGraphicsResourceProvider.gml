function PixelpartGraphicsResourceProvider() constructor
{
	loaded = false;
	sprites = ds_map_create();

	static cleanup = function()
	{
		clear();
		ds_map_destroy(sprites);
	}

	static load = function(_effect_ptr)
	{
		// Clear old resources
		clear();

		var _resource_id_buffer = buffer_create(2048, buffer_fixed, 1);

		// Load images
		var _image_resource_count = pixelpart_get_image_resource_count(_effect_ptr);

		for (var _resource_index = 0; _resource_index < _image_resource_count; _resource_index += 1)
		{
			buffer_seek(_resource_id_buffer, buffer_seek_start, 0);
			pixelpart_get_image_resource_id(_effect_ptr, _resource_index,
				buffer_get_address(_resource_id_buffer),
				buffer_get_size(_resource_id_buffer));
			var _resource_id = buffer_read(_resource_id_buffer, buffer_string);

			var _image_width = pixelpart_get_image_resource_width(_effect_ptr, _resource_id);
			var _image_height = pixelpart_get_image_resource_height(_effect_ptr, _resource_id);
			var _image_channels = pixelpart_get_image_resource_channels(_effect_ptr, _resource_id);
			var _image_color_space = pixelpart_get_image_resource_color_space(_effect_ptr, _resource_id);

			var _image_data_size = pixelpart_get_image_resource_data_size(_effect_ptr, _resource_id);
			var _image_data_buffer = buffer_create(_image_data_size, buffer_fixed, 1);
			pixelpart_get_image_resource_data(_effect_ptr, _resource_id,
				buffer_get_address(_image_data_buffer));

			// Create surface from image data
			var _texture_surface = surface_create(_image_width, _image_height);
			buffer_set_surface(_image_data_buffer, _texture_surface, 0);

			// Create sprite from surface
			if (surface_exists(_texture_surface))
			{
				var _sprite = sprite_create_from_surface(_texture_surface,
					0, 0, _image_width, _image_height, false, false, 0, 0);
				ds_map_add(sprites, _resource_id, _sprite);

				surface_free(_texture_surface);
			}

			buffer_delete(_image_data_buffer);
		}

		buffer_delete(_resource_id_buffer);

		loaded = true;
	}

	static clear = function()
	{
		for (var _resource_id = ds_map_find_first(sprites); !is_undefined(_resource_id); _resource_id = ds_map_find_next(sprites, _resource_id))
		{
			sprite_delete(sprites[? _resource_id]);
		}

		ds_map_clear(sprites);
	}

	static find_sprite = function(_resource_id)
	{
		return sprites[? _resource_id];
	}
}
