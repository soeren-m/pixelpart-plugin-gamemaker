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

function PixelpartParticleMaterial(_effect_ptr, _emitter_id, _type_id, _graphics_resource_provider) constructor
{
	effect_ptr = _effect_ptr;
	emitter_id = _emitter_id;
	type_id = _type_id;

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

	static cleanup = function()
	{
		buffer_delete(parameter_value_buffer);
	}

	static apply_parameters = function(_shader)
	{
		for (var _index = 0; _index < mat_parameter_count; _index++)
		{
			apply_parameter(_shader, mat_parameter_ids[_index]);
		}
	}

	static apply_parameter = function(_shader, _parameter_id)
	{
		var _parameter_name = ""; // TODO
		var _parameter_type = pixelpart_particle_type_get_material_parameter_type(effect_ptr, type_id, _parameter_id);

		var _uniform = shader_get_uniform(_shader, _parameter_name);

		// Get value of material parameter
		pixelpart_particle_type_get_material_parameter_value(effect_ptr, type_id, _parameter_id,
			buffer_get_address(parameter_value_buffer));

		// Set uniform value
		switch (_parameter_type)
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
				texture_resource_id = buffer_peek(parameter_value_buffer, 0, buffer_string);
				break;
			default:
				break;
		}
	}
}