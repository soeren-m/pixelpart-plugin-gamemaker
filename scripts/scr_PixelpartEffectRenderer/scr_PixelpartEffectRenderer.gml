function PixelpartEffectRenderer(_effect_ptr) constructor
{
	effect_ptr = _effect_ptr;

	graphics_resource_provider = new PixelpartGraphicsResourceProvider();

	runtime_instance_count = pixelpart_get_effect_particle_runtime_instance_count(effect_ptr);
	runtime_instance_buffer = buffer_create(runtime_instance_count * 2 * 4, buffer_fixed, 4);
	sorted_runtime_instance_buffer = buffer_create(runtime_instance_count * 4, buffer_fixed, 4);

	pixelpart_get_effect_particle_runtime_instances(effect_ptr, buffer_get_address(runtime_instance_buffer));

	// Create renderer for every particle runtime instance (particle emitter + type)
	particle_renderers = array_create(runtime_instance_count);
	for (var _runtime_index = 0; _runtime_index < runtime_instance_count; _runtime_index += 1)
	{
		var _emitter_id = buffer_peek(runtime_instance_buffer, _runtime_index * 2 * 4, buffer_u32);
		var _type_id = buffer_peek(runtime_instance_buffer, (_runtime_index * 2 + 1) * 4, buffer_u32);

		particle_renderers[_runtime_index] = new PixelpartParticleRenderer(effect_ptr,
			_emitter_id, _type_id, graphics_resource_provider);
	}

	static cleanup = function()
	{
		buffer_delete(runtime_instance_buffer);
		runtime_instance_buffer = -1;

		buffer_delete(sorted_runtime_instance_buffer);
		sorted_runtime_instance_buffer = -1;

		for (var _runtime_index = 0; _runtime_index < runtime_instance_count; _runtime_index += 1)
		{
			particle_renderers[_runtime_index].cleanup();
			delete particle_renderers[_runtime_index];
		}

		graphics_resource_provider.cleanup();
		delete graphics_resource_provider;
	}

	static render = function()
	{
		// Load resources (textures) if not already loaded
		if !graphics_resource_provider.loaded
		{
			graphics_resource_provider.load(effect_ptr);
		}

		if runtime_instance_count == 0
		{
			return;
		}

		// Sort by layer
		pixelpart_get_sorted_particle_runtime_instances(effect_ptr, buffer_get_address(sorted_runtime_instance_buffer))

		// Render sorted layers
		for (var _index = 0; _index < runtime_instance_count; _index += 1)
		{
			var _runtime_index =
				buffer_peek(sorted_runtime_instance_buffer, _index * 4, buffer_u32);

			particle_renderers[_runtime_index].render();
		}
	}
}