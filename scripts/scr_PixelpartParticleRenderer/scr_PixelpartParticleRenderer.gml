function PixelpartParticleRenderer(_effect_ptr, _emitter_id, _type_id, _graphics_resource_provider) constructor
{
	effect_ptr = _effect_ptr;
	emitter_id = _emitter_id;
	type_id = _type_id;
	graphics_resource_provider = _graphics_resource_provider;
	material = new PixelpartParticleMaterial(_effect_ptr, _emitter_id, _type_id, _graphics_resource_provider);

	max_particle_count = 1000;

	// Define vertex format
	vertex_format_begin();
	vertex_format_add_position();
	vertex_format_add_colour();
	vertex_format_add_texcoord();
	vertex_format_add_custom(vertex_type_float3, vertex_usage_texcoord);
	vertex_format_add_custom(vertex_type_float2, vertex_usage_texcoord);
	particle_vertex_format = vertex_format_end();
	particle_vertex_stride = vertex_format_get_info(particle_vertex_format).stride;

	// Create buffer for particle vertex data
	vertex_data_buffer = buffer_create(max_particle_count * particle_vertex_stride * 6, buffer_fixed, 1);
	pixelpart_get_particle_sprite_vertex_data(effect_ptr, emitter_id, type_id, buffer_get_address(vertex_data_buffer));

	// Create vertex buffer
	particle_vertex_buffer = vertex_create_buffer_from_buffer_ext(vertex_data_buffer, particle_vertex_format, 0, max_particle_count * 6);

	static cleanup = function()
	{
		material.cleanup();
		delete material;

		vertex_delete_buffer(particle_vertex_buffer)
		particle_vertex_buffer = -1

		vertex_format_delete(particle_vertex_format)
		particle_vertex_format = -1

		buffer_delete(vertex_data_buffer)
		vertex_data_buffer = -1
	}

	static render = function()
	{
		var _vertex_count =
			pixelpart_prepare_particle_sprite_vertex_data(effect_ptr, emitter_id, type_id);
		if _vertex_count > max_particle_count * 6
		{
			return;
		}

		// Update vertices
		pixelpart_get_particle_sprite_vertex_data(effect_ptr, emitter_id, type_id, buffer_get_address(vertex_data_buffer));
		_update_vertices(_vertex_count);

		// Apply material parameters
		shader_set(sha_PixelpartSpriteUnlitAlpha);
		material.apply_parameters(sha_PixelpartSpriteUnlitAlpha);

		var _sprite = graphics_resource_provider.find_sprite(material.texture_resource_id);
		var _texture = !is_undefined(_sprite) ? sprite_get_texture(_sprite, 0) : -1;

		// Render particles
		vertex_submit_ext(particle_vertex_buffer, pr_trianglelist, _texture, 0, _vertex_count);
		shader_reset();
	}

	static _update_vertices = function(_vertex_count)
	{
		// vertex_update_buffer_from_buffer(particle_vertex_buffer, 0, vertex_data_buffer, 0, _vertex_count * particle_vertex_stride);

		vertex_delete_buffer(particle_vertex_buffer);
		particle_vertex_buffer = vertex_create_buffer_from_buffer_ext(vertex_data_buffer, particle_vertex_format, 0, _vertex_count * 6);
	}
}