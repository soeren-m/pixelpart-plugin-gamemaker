function pixelpart_buffer_peek_string(_buffer, _offset)
{
	if os_browser == browser_not_a_browser
	{
		return buffer_peek(_buffer, _offset, buffer_string);
	}
	else
	{
		var _buffer_size = buffer_get_size(_buffer);
		var _tmp_buffer = buffer_create(_buffer_size, buffer_fixed, 1);
		buffer_copy(_buffer, 0, _buffer_size, _tmp_buffer, 0);

		var _result = buffer_peek(_tmp_buffer, _offset, buffer_string);
		buffer_delete(_tmp_buffer);

		return _result;
	}
}
