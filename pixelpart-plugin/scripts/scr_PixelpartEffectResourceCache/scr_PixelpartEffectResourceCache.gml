function pixelpart_cache_load(_filepath)
{
	// Avoid error "illegal to use empty names"
	if _filepath == ""
	{
		return new PixelpartEffectResource();
	}

	var _cache = pixelpart_cache_get();

	if (!variable_struct_exists(_cache, _filepath))
	{
		// Load from disk
		var _effect_resource = new PixelpartEffectResource();
		_effect_resource.load(_filepath);

		// Store in cache
		_cache[$ _filepath] =
		{
			data: _effect_resource,
			ref_count: 0,
			unused_since: -1
		};
	}

	// Load from cache and increase ref count
	var _entry = _cache[$ _filepath];
	_entry.ref_count++;
	_entry.unused_since = -1;

	return _entry.data;
}

function pixelpart_cache_release(_filepath)
{
	var _cache = pixelpart_cache_get();
	if (!variable_struct_exists(_cache, _filepath))
	{
		return;
	}

	var _entry = _cache[$ _filepath];

	// Decrease ref count
	_entry.ref_count--;
	if (_entry.ref_count <= 0)
	{
		_entry.unused_since = current_time;
	}

	// Cleanup cache
	pixelpart_cache_cleanup();
}

function pixelpart_cache_cleanup()
{
	var _timeout = 10000;
	var _cache = pixelpart_cache_get();
	var _cache_keys = variable_struct_get_names(_cache);

	var _remove_list = [];
	for (var _ci = array_length(_cache_keys) - 1; _ci >= 0; _ci--)
	{
		var _key = _cache_keys[_ci];
		var _entry = _cache[$ _key];

		if (_entry.ref_count <= 0 && current_time - _entry.unused_since > _timeout)
		{
			_entry.data.cleanup();
			delete _entry.data;

			array_push(_remove_list, _key);
		}
	}

	for (var _index = 0; _index < array_length(_remove_list); _index++)
	{
		variable_struct_remove(_cache, _remove_list[_index]);
	}
}

function pixelpart_cache_get()
{
	static cache = {};

	return cache;
}
