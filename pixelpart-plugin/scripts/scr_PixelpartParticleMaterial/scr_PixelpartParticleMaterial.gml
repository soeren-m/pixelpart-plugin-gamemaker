enum PixelpartMaterialParameterType
{
	INT = 0,
	FLOAT = 1,
	FLOAT2 = 2,
	FLOAT3 = 3,
	FLOAT4 = 4,
	BOOL = 5,
	ENUM = 6,
	COLOR = 7,
	CURVE = 8,
	GRADIENT = 9,
	RESOURCE_IMAGE = 10
}

function PixelpartParticleMaterial(_effect_ptr, _emitter_id, _type_id, _material_desc, _graphics_resource_provider) constructor
{
	effect_ptr = _effect_ptr;
	emitter_id = _emitter_id;
	type_id = _type_id;
	material_desc = _material_desc;

	mat_parameter_count = pixelpart_particle_type_get_material_parameter_count(effect_ptr, type_id);
	mat_parameter_ids = array_create(mat_parameter_count);

	// Get material parameter ids
	var _mat_parameter_id_buffer = buffer_create(mat_parameter_count * 4, buffer_fixed, 4);
	pixelpart_particle_type_get_material_parameter_ids(effect_ptr, type_id,
		buffer_get_address(_mat_parameter_id_buffer));

	for (var _index = 0; _index < mat_parameter_count; _index++)
	{
		mat_parameter_ids[_index] = buffer_read(_mat_parameter_id_buffer, buffer_u32);
	}

	buffer_delete(_mat_parameter_id_buffer);

	parameter_value_buffer = buffer_create(2048, buffer_fixed, 1);
	texture_resource_id = "";

	prev_blendenable = true;
	prev_blendmode = bm_normal;

	static cleanup = function()
	{
		buffer_delete(parameter_value_buffer);
	}

	static apply = function()
	{
		// Set shader
		shader_set(material_desc.shader);

		// Apply parameters
		for (var _index = 0; _index < mat_parameter_count; _index++)
		{
			apply_parameter(mat_parameter_ids[_index]);
		}

		prev_blendenable = gpu_get_blendenable();
		prev_blendmode = gpu_get_blendmode();

		// Apply blend mode
		switch (material_desc.blend_mode)
		{
			case PixelpartBlendMode.OFF:
				gpu_set_blendenable(false);
				break;
			case PixelpartBlendMode.ALPHA:
				gpu_set_blendenable(true);
				gpu_set_blendmode(bm_normal);
				break;
			case PixelpartBlendMode.ADDITIVE:
				gpu_set_blendenable(true);
				gpu_set_blendmode(bm_add);
				break;
			case PixelpartBlendMode.SUBTRACTIVE:
				gpu_set_blendenable(true);
				gpu_set_blendmode(bm_subtract);
				break;
			default:
				break;
		}
	}

	static reset = function()
	{
		// Reset blend mode
		gpu_set_blendmode(prev_blendmode);
		gpu_set_blendenable(prev_blendenable);

		// Reset shader
		shader_reset();
	}

	static apply_parameter = function(_param_id)
	{
		var _param_name = material_desc.parameter_names[? string(_param_id)];
		if is_undefined(_param_name)
		{
			// Parameter not found
			return;
		}

		var _param_type = pixelpart_particle_type_get_material_parameter_type(effect_ptr, type_id, _param_id);

		// Get value of material parameter
		pixelpart_particle_type_get_material_parameter_value(effect_ptr, type_id, _param_id,
			buffer_get_address(parameter_value_buffer));

		// Get uniform handle for parameter
		var _uniform = shader_get_uniform(material_desc.shader, _param_name);

		// Set uniform to parameter value
		switch (_param_type)
		{
			case PixelpartMaterialParameterType.INT:
			case PixelpartMaterialParameterType.ENUM:
				shader_set_uniform_i(_uniform,
					buffer_peek(parameter_value_buffer, 0, buffer_s32));
				break;
			case PixelpartMaterialParameterType.FLOAT:
				shader_set_uniform_f(_uniform,
					buffer_peek(parameter_value_buffer, 0, buffer_f64));
				break;
			case PixelpartMaterialParameterType.FLOAT2:
				shader_set_uniform_f(_uniform,
					buffer_peek(parameter_value_buffer, 0, buffer_f64),
					buffer_peek(parameter_value_buffer, 8, buffer_f64));
				break;
			case PixelpartMaterialParameterType.FLOAT3:
				shader_set_uniform_f(_uniform,
					buffer_peek(parameter_value_buffer, 0, buffer_f64),
					buffer_peek(parameter_value_buffer, 8, buffer_f64),
					buffer_peek(parameter_value_buffer, 16, buffer_f64));
				break;
			case PixelpartMaterialParameterType.FLOAT4:
			case PixelpartMaterialParameterType.COLOR:
				shader_set_uniform_f(_uniform,
					buffer_peek(parameter_value_buffer, 0, buffer_f64),
					buffer_peek(parameter_value_buffer, 8, buffer_f64),
					buffer_peek(parameter_value_buffer, 16, buffer_f64),
					buffer_peek(parameter_value_buffer, 24, buffer_f64));
				break;
			case PixelpartMaterialParameterType.BOOL:
				shader_set_uniform_i(_uniform,
					buffer_peek(parameter_value_buffer, 0, buffer_bool));
				break;
			case PixelpartMaterialParameterType.RESOURCE_IMAGE:
				texture_resource_id = pixelpart_buffer_peek_string(parameter_value_buffer, 0);
				break;
			default:
				break;
		}
	}
}
