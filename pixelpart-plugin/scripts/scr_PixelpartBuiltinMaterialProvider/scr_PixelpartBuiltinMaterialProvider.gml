function PixelpartBuiltinMaterialProvider() constructor
{
	builtin_material_parameter_ids =
	{
		MainTexture: 0,
		ColorBlendMode: 10,
		Emission: 20,
		Roughness: 21,
		Metallic: 22,
		SpriteSheetRowNumber: 30,
		SpriteSheetColumnNumber: 31,
		SpriteSheetOrigin: 32,
		SpriteAnimationNumFrames: 33,
		SpriteAnimationStartFrame: 34,
		SpriteAnimationDuration: 35,
		SpriteAnimationLoop: 36,
		SoftParticles: 40,
		SoftParticleTransition: 41,
		DistanceFade: 42,
		DistanceFadeTransition: 43
	};

	sprite_unlit_parameter_names =
	[
		"MainTexture",
		"Emission",
		"ColorBlendMode",
		"SpriteSheetRowNumber",
		"SpriteSheetColumnNumber",
		"SpriteSheetOrigin",
		"SpriteAnimationNumFrames",
		"SpriteAnimationStartFrame",
		"SpriteAnimationDuration",
		"SpriteAnimationLoop",
		"SoftParticles",
		"SoftParticleTransition",
		"DistanceFade",
		"DistanceFadeTransition"
	];
	sprite_lit_parameter_names =
	[
		"MainTexture",
		"Emission",
		"Roughness",
		"Metallic",
		"ColorBlendMode",
		"SpriteSheetRowNumber",
		"SpriteSheetColumnNumber",
		"SpriteSheetOrigin",
		"SpriteAnimationNumFrames",
		"SpriteAnimationStartFrame",
		"SpriteAnimationDuration",
		"SpriteAnimationLoop",
		"SoftParticles",
		"SoftParticleTransition",
		"DistanceFade",
		"DistanceFadeTransition"
	];
	trail_unlit_parameter_names =
	[
		"MainTexture",
		"Emission",
		"ColorBlendMode",
		"SoftParticles",
		"SoftParticleTransition",
		"DistanceFade",
		"DistanceFadeTransition"
	];
	trail_lit_parameter_names =
	[
		"MainTexture",
		"Emission",
		"Roughness",
		"Metallic",
		"ColorBlendMode",
		"SoftParticles",
		"SoftParticleTransition",
		"DistanceFade",
		"DistanceFadeTransition"
	];

	builtin_materials = {};

	static cleanup = function()
	{
		var _keys = variable_struct_get_names(builtin_materials);
		for (var _index = array_length(_keys) - 1; _index >= 0; _index--)
		{
			var _mat = builtin_materials[$ _keys[_index]];
			ds_map_destroy(_mat.parameter_ids);
		}

		delete builtin_materials;
	}

	static add_material = function(_name, _shader, _blend_mode, _lighting_mode, _parameter_list)
	{
		var _parameter_ids = ds_map_create();
		for (var _index = 0; _index < array_length(_parameter_list); _index++)
		{
			var _param_name = _parameter_list[_index];
			var _param_uniform_name = "u_" + _param_name;

			if variable_struct_exists(builtin_material_parameter_ids, _param_name)
			{
				var _param_id = builtin_material_parameter_ids[$ _param_name];
				ds_map_add(_parameter_ids, string(_param_id), _param_uniform_name);
			}
			else
			{
				show_debug_message("[Pixelpart] Unknown material parameter \"{0}\" in shader \"{1}\"",
					_param_name, _name);
			}
		}

		builtin_materials[$ _name] = new PixelpartMaterialDescriptor(
			_shader, _blend_mode, _lighting_mode, _parameter_ids);
	}

	add_material("SpriteUnlitAlpha", sha_PixelpartSpriteUnlit,
		PixelpartBlendMode.NORMAL, PixelpartLightingMode.UNLIT, sprite_unlit_parameter_names);
	add_material("SpriteUnlitAdditive", sha_PixelpartSpriteUnlit,
		PixelpartBlendMode.ADDITIVE, PixelpartLightingMode.UNLIT, sprite_unlit_parameter_names);
	add_material("TrailUnlitAlpha", sha_PixelpartTrailUnlit,
		PixelpartBlendMode.NORMAL, PixelpartLightingMode.UNLIT, trail_unlit_parameter_names);
	add_material("TrailUnlitAdditive", sha_PixelpartTrailUnlit,
		PixelpartBlendMode.ADDITIVE, PixelpartLightingMode.UNLIT, trail_unlit_parameter_names);
}
