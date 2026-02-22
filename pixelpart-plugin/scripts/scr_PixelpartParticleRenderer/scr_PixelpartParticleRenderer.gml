enum PixelpartRendererType
{
	SPRITE = 0,
	TRAIL = 1,
	MESH = 2
}

function PixelpartParticleRenderer(_effect_ptr, _emitter_id, _type_id, _graphics_resource_provider) constructor
{
	effect_ptr = _effect_ptr;
	emitter_id = _emitter_id;
	type_id = _type_id;
	graphics_resource_provider = _graphics_resource_provider;

	var _material_id = pixelpart_particle_type_get_material_id(effect_ptr, type_id);
	var _material_builtin = pixelpart_particle_type_is_material_builtin(effect_ptr, type_id);

	material = undefined;
	if _material_builtin
	{
		if !variable_global_exists("pixelpart_builtin_material_provider")
		{
			show_debug_message("[Pixelpart] Creating built-in material provider");

			global.pixelpart_builtin_material_provider = new PixelpartBuiltinMaterialProvider();
		}

		if variable_struct_exists(global.pixelpart_builtin_material_provider.builtin_materials, _material_id)
		{
			var _material_desc = global.pixelpart_builtin_material_provider.builtin_materials[$ _material_id];

			material = new PixelpartParticleMaterial(_effect_ptr, _emitter_id, _type_id,
				_material_desc, _graphics_resource_provider);
		}
		else
		{
			show_debug_message("[Pixelpart] Built-in material \"{0}\" is not supported", _material_id);
		}
	}
	else
	{
		show_debug_message("[Pixelpart] Custom materials are not supported");
	}

	// Define vertex format
	vertex_format_begin();
	vertex_format_add_position();
	vertex_format_add_colour();
	vertex_format_add_texcoord();
	vertex_format_add_custom(vertex_type_float2, vertex_usage_texcoord); // Particle life and id
	particle_vertex_format = vertex_format_end();
	particle_vertex_stride = vertex_format_get_info(particle_vertex_format).stride;

	// Create buffer for particle vertex data
	vertex_buffer_capacity = 1000 * 6;
	vertex_data_buffer = buffer_create(vertex_buffer_capacity * particle_vertex_stride, buffer_fixed, 1);

	// For some reason, rendering in HTML5 only works if the vertex data is copied into another buffer before rendering...
	if os_browser != browser_not_a_browser
	{
		vertex_data_buffer_copy = buffer_create(vertex_buffer_capacity * particle_vertex_stride, buffer_fixed, 1);
	}

	// Create vertex buffer
	particle_vertex_buffer = vertex_create_buffer_from_buffer_ext(vertex_data_buffer, particle_vertex_format, 0, vertex_buffer_capacity);

	buffer_size_buffer = buffer_create(2 * 4, buffer_fixed, 4);

	static cleanup = function()
	{
		if !is_undefined(material)
		{
			material.cleanup();
			delete material;
			material = undefined;
		}

		vertex_delete_buffer(particle_vertex_buffer);
		particle_vertex_buffer = -1;

		vertex_format_delete(particle_vertex_format);
		particle_vertex_format = -1;

		buffer_delete(vertex_data_buffer);
		vertex_data_buffer = -1;

		if os_browser != browser_not_a_browser
		{
			vertex_delete_buffer(vertex_data_buffer_copy);
			vertex_data_buffer_copy = -1;
		}

		buffer_delete(buffer_size_buffer);
		buffer_size_buffer = -1;
	}

	static render = function()
	{
		// Update vertices in vertex buffer
		var _vertex_count = update_vertices();
		if _vertex_count <= 0
		{
			// Nothing to render
			return;
		}

		if is_undefined(material)
		{
			// No material, don't draw anything
			return;
		}

		// Set shader and apply material properties
		material.apply();

		var _sprite = graphics_resource_provider.find_sprite(material.texture_resource_id);
		var _texture = !is_undefined(_sprite) ? sprite_get_texture(_sprite, 0) : -1;

		var _uvs = sprite_get_uvs(_sprite, 0);
		var _uniformTextureUV = shader_get_uniform(material.material_desc.shader, "u_TextureUV");
		shader_set_uniform_f(_uniformTextureUV, _uvs[0], _uvs[1], _uvs[2], _uvs[3]);

		// Render particles
		vertex_submit_ext(particle_vertex_buffer, pr_trianglelist, _texture, 0, _vertex_count);

		material.reset();
	}

	static update_vertices = function()
	{
		// Construct geometry and get required buffer size
		var _result = pixelpart_construct_particle_geometry(effect_ptr, emitter_id, type_id,
			buffer_get_address(buffer_size_buffer));
		if _result <= 0
		{
			return 0;
		}

		var _vertex_count = buffer_peek(buffer_size_buffer, 0, buffer_u32);

		// Resize vertex data buffer if it's too small
		if _vertex_count > vertex_buffer_capacity
		{
			vertex_buffer_capacity = _vertex_count;
			buffer_resize(vertex_data_buffer, vertex_buffer_capacity * particle_vertex_stride);

			if os_browser != browser_not_a_browser
			{
				buffer_resize(vertex_data_buffer_copy, vertex_buffer_capacity * particle_vertex_stride);
			}
		}

		// Get vertex data and update vertex buffer
		pixelpart_generate_particle_vertex_data(effect_ptr, emitter_id, type_id, buffer_get_address(vertex_data_buffer));

		// For some reason, rendering in HTML5 only works if the vertex data is copied into another buffer before rendering...
		if os_browser != browser_not_a_browser
		{
			buffer_copy(vertex_data_buffer, 0, _vertex_count * particle_vertex_stride, vertex_data_buffer_copy, 0);
		}

		update_vertex_buffer(_vertex_count);

		return _vertex_count;
	}

	static update_vertex_buffer = function(_vertex_count)
	{
		// vertex_update_buffer_from_buffer(particle_vertex_buffer, 0, vertex_data_buffer, 0, _vertex_count * particle_vertex_stride);

		vertex_delete_buffer(particle_vertex_buffer);
		particle_vertex_buffer = vertex_create_buffer_from_buffer_ext(
			os_browser == browser_not_a_browser ? vertex_data_buffer : vertex_data_buffer_copy, particle_vertex_format, 0, _vertex_count);
	}
}
