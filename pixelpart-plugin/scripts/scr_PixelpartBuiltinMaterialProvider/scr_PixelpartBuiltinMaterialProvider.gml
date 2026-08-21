function PixelpartBuiltinMaterialProvider() constructor
{
	builtin_materials = {};

	static cleanup = function()
	{
		var _keys = variable_struct_get_names(builtin_materials);
		for (var _index = array_length(_keys) - 1; _index >= 0; _index--)
		{
			var _mat = builtin_materials[$ _keys[_index]];
			ds_map_destroy(_mat.parameter_names);
		}

		delete builtin_materials;
	}

	static add_material = function(_name, _shader, _blend_mode, _lighting_mode)
	{
		var _param_count = pixelpart_get_builtin_material_parameter_count(_name);
		if _param_count < 0
		{
			show_debug_message("[Pixelpart] Failed to get material parameters for shader \"{0}\"",
				_name);

			return;
		}

		var _param_id_buffer = buffer_create(_param_count * 4, buffer_fixed, 4);
		var _param_name_buffer = buffer_create(_param_count * 256, buffer_fixed, 1);

		pixelpart_get_builtin_material_parameters(_name,
			buffer_get_address(_param_id_buffer),
			buffer_get_address(_param_name_buffer));

		// For some reason this is needed for HTML5...
		var _param_name_buffer_copy = undefined
		if os_browser != browser_not_a_browser
		{
			var _param_name_buffer_size = buffer_get_size(_param_name_buffer);
			_param_name_buffer_copy = buffer_create(_param_name_buffer_size, buffer_fixed, 1);
			buffer_copy(_param_name_buffer, 0, _param_name_buffer_size, _param_name_buffer_copy, 0);
		}

		var _param_ids = ds_map_create();

		for (var _param_index = 0; _param_index < _param_count; _param_index++)
		{
			var _param_id = buffer_read(_param_id_buffer, buffer_u32);
			var _param_name = buffer_read(os_browser == browser_not_a_browser ? _param_name_buffer : _param_name_buffer_copy, buffer_string);
			var _param_uniform_name = "u_" + _param_name;

			ds_map_add(_param_ids, string(_param_id), _param_uniform_name);
		}

		buffer_delete(_param_id_buffer);
		buffer_delete(_param_name_buffer);

		if !is_undefined(_param_name_buffer_copy)
		{
			buffer_delete(_param_name_buffer_copy);
		}

		builtin_materials[$ _name] = new PixelpartMaterialDescriptor(
			_shader, _blend_mode, _lighting_mode, _param_ids);
	}

	add_material("SpriteUnlitAlpha", sha_PixelpartSpriteUnlit, PixelpartBlendMode.ALPHA, PixelpartLightingMode.UNLIT);
	add_material("SpriteUnlitAdditive", sha_PixelpartSpriteUnlit, PixelpartBlendMode.ADDITIVE, PixelpartLightingMode.UNLIT);
	add_material("TrailUnlitAlpha", sha_PixelpartTrailUnlit, PixelpartBlendMode.ALPHA, PixelpartLightingMode.UNLIT);
	add_material("TrailUnlitAdditive", sha_PixelpartTrailUnlit, PixelpartBlendMode.ADDITIVE, PixelpartLightingMode.UNLIT);
}
