/// @desc Event that can be subscribed to with a callback function.
function PixelpartEvent() constructor
{
	listeners = {};
	next_listener_id = 0;

	/// @desc Subscribe to the event.
	/// @param {function} _fn Function to call when event is invoked
	/// @returns {real} Subscription ID, can be used to unsubscribe
	static subscribe = function(_fn)
	{
		var _listener_id = next_listener_id;
		next_listener_id++;

		listeners[$ _listener_id] = _fn;

		return _listener_id;
	}

	/// @desc Unsubscribe from the event.
	/// @param {real} _listener_id Subscription ID
	static unsubscribe = function(_listener_id)
	{
		if (struct_exists(listeners, _listener_id))
		{
			struct_remove(listeners, _listener_id);
		}
	}

	/// @desc Invoke the event.
	/// @param {any*} _args Event arguments
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
