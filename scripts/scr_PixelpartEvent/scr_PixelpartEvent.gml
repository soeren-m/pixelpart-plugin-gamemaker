function PixelpartEvent() constructor
{
	listeners = {};
	next_listener_id = 0;

	static subscribe = function(_fn)
	{
		var _listener_id = next_listener_id;
		next_listener_id++;

		listeners[$ _listener_id] = _fn;

		return _listener_id;
	}

	static unsubscribe = function(_listener_id)
	{
		if (struct_exists(listeners, _listener_id))
		{
			struct_remove(listeners, _listener_id);
		}
	}

	static invoke = function(_args)
	{
		var _listener_ids = variable_struct_get_names(listeners);
		for (var _index = 0; _index < array_length(_listener_ids); _index++)
		{
			var _listener_id = _listener_ids[_index];
			var _listener = listeners[$ _listener_id];

			_listener(_args);
		}
	}
}
