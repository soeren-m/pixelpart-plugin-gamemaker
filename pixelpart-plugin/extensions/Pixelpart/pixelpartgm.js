function pixelpartjs_copy_to_native_buffer(arrayBuffer) {
	const nativeBufferPtr = Module._malloc(arrayBuffer.byteLength);
	Module.HEAPU8.set(new Uint8Array(arrayBuffer), nativeBufferPtr);

	return nativeBufferPtr;
}
function pixelpartjs_copy_from_native_buffer(arrayBuffer, nativeBufferPtr) {
	new Uint8Array(arrayBuffer).set(
		Module.HEAPU8.subarray(nativeBufferPtr, nativeBufferPtr + arrayBuffer.byteLength));
}

// Init
function pixelpart_init() {
	return Module._pixelpart_init();
}
function pixelpart_shutdown() {
	return Module._pixelpart_shutdown();
}

// Error
function pixelpart_last_error() {
	return Module.UTF8ToString(Module._pixelpart_last_error());
}

// Effect runtime
function pixelpart_load_effect_resource(data, size) {
	const dataCStr = Module._malloc(size + 1);
	Module.stringToUTF8(data, dataCStr, size + 1);

	const result = Module.UTF8ToString(Module._pixelpart_load_effect_resource(dataCStr, size));
	Module._free(dataCStr);

	return result;
}
function pixelpart_delete_effect_resource(resourcePtr) {
	const resourceCStr = Module.stringToNewUTF8(resourcePtr);
	const result = Module._pixelpart_delete_effect_resource(resourceCStr);
	Module._free(resourceCStr);

	return result;
}
function pixelpart_create_effect(resourcePtr) {
	const resourceCStr = Module.stringToNewUTF8(resourcePtr);
	const result = Module.UTF8ToString(Module._pixelpart_create_effect(resourceCStr));
	Module._free(resourceCStr);

	return result;
}
function pixelpart_delete_effect(runtimePtr) {
	const runtimeCStr = Module.stringToNewUTF8(runtimePtr);
	const result = Module._pixelpart_delete_effect(runtimeCStr);
	Module._free(runtimeCStr);

	return result;
}
function pixelpart_set_effect_scale(runtimePtr, scaleX, scaleY) {
	const runtimeCStr = Module.stringToNewUTF8(runtimePtr);
	const result = Module._pixelpart_set_effect_scale(runtimeCStr, scaleX, scaleY);
	Module._free(runtimeCStr);

	return result;
}
function pixelpart_set_effect_transform(runtimePtr, x, y, rotation) {
	const runtimeCStr = Module.stringToNewUTF8(runtimePtr);
	const result = Module._pixelpart_set_effect_transform(runtimeCStr, x, y, rotation);
	Module._free(runtimeCStr);

	return result;
}
function pixelpart_select_effect_lod_for_camera(runtimePtr, cameraPositionX, cameraPositionY) {
	const runtimeCStr = Module.stringToNewUTF8(runtimePtr);
	const result = Module._pixelpart_select_effect_lod_for_camera(runtimeCStr, cameraPositionX, cameraPositionY);
	Module._free(runtimeCStr);

	return result;
}
function pixelpart_advance_effect(runtimePtr, paramBufferPtr) {
	const runtimeCStr = Module.stringToNewUTF8(runtimePtr);
	const nativeParamBufferPtr = pixelpartjs_copy_to_native_buffer(paramBufferPtr);
	const result = Module._pixelpart_advance_effect(runtimeCStr, nativeParamBufferPtr);
	Module._free(nativeParamBufferPtr);
	Module._free(runtimeCStr);

	return result;
}
function pixelpart_restart_effect(runtimePtr, clear) {
	const runtimeCStr = Module.stringToNewUTF8(runtimePtr);
	const result = Module._pixelpart_restart_effect(runtimeCStr, clear);
	Module._free(runtimeCStr);

	return result;
}
function pixelpart_reseed_effect(runtimePtr, seed) {
	const runtimeCStr = Module.stringToNewUTF8(runtimePtr);
	const result = Module._pixelpart_reseed_effect(runtimeCStr, seed);
	Module._free(runtimeCStr);

	return result;
}
function pixelpart_get_effect_time(runtimePtr) {
	const runtimeCStr = Module.stringToNewUTF8(runtimePtr);
	const result = Module._pixelpart_get_effect_time(runtimeCStr);
	Module._free(runtimeCStr);

	return result;
}
function pixelpart_is_effect_finished(runtimePtr) {
	const runtimeCStr = Module.stringToNewUTF8(runtimePtr);
	const result = Module._pixelpart_is_effect_finished(runtimeCStr);
	Module._free(runtimeCStr);

	return result;
}
function pixelpart_is_effect_3d(runtimePtr) {
	const runtimeCStr = Module.stringToNewUTF8(runtimePtr);
	const result = Module._pixelpart_is_effect_3d(runtimeCStr);
	Module._free(runtimeCStr);

	return result;
}
function pixelpart_get_effect_node_count(runtimePtr) {
	const runtimeCStr = Module.stringToNewUTF8(runtimePtr);
	const result = Module._pixelpart_get_effect_node_count(runtimeCStr);
	Module._free(runtimeCStr);

	return result;
}
function pixelpart_get_effect_particle_type_count(runtimePtr) {
	const runtimeCStr = Module.stringToNewUTF8(runtimePtr);
	const result = Module._pixelpart_get_effect_particle_type_count(runtimeCStr);
	Module._free(runtimeCStr);

	return result;
}
function pixelpart_get_effect_particle_runtime_instance_count(runtimePtr) {
	const runtimeCStr = Module.stringToNewUTF8(runtimePtr);
	const result = Module._pixelpart_get_effect_particle_runtime_instance_count(runtimeCStr);
	Module._free(runtimeCStr);

	return result;
}
function pixelpart_get_effect_particle_runtime_instances(runtimePtr, instanceBufferPtr) {
	const runtimeCStr = Module.stringToNewUTF8(runtimePtr);
	const nativeInstanceBufferPtr = Module._malloc(instanceBufferPtr.byteLength);
	const result = Module._pixelpart_get_effect_particle_runtime_instances(runtimeCStr, nativeInstanceBufferPtr);
	pixelpartjs_copy_from_native_buffer(instanceBufferPtr, nativeInstanceBufferPtr);
	Module._free(nativeInstanceBufferPtr);
	Module._free(runtimeCStr);

	return result;
}
function pixelpart_get_effect_particle_count(runtimePtr, particleEmitterId, particleTypeId) {
	const runtimeCStr = Module.stringToNewUTF8(runtimePtr);
	const result = Module._pixelpart_get_effect_particle_count(runtimeCStr, particleEmitterId, particleTypeId);
	Module._free(runtimeCStr);

	return result;
}
function pixelpart_spawn_particles(runtimePtr, particleEmitterId, particleTypeId, count) {
	const runtimeCStr = Module.stringToNewUTF8(runtimePtr);
	const result = Module._pixelpart_spawn_particles(runtimeCStr, particleEmitterId, particleTypeId, count);
	Module._free(runtimeCStr);

	return result;
}

// Resources
function pixelpart_get_image_resource_count(runtimePtr) {
	const runtimeCStr = Module.stringToNewUTF8(runtimePtr);
	const result = Module._pixelpart_get_image_resource_count(runtimeCStr);
	Module._free(runtimeCStr);

	return result;
}
function pixelpart_get_image_resource_id(runtimePtr, index) {
	const runtimeCStr = Module.stringToNewUTF8(runtimePtr);
	const result = Module.UTF8ToString(Module._pixelpart_get_image_resource_id(runtimeCStr, index));
	Module._free(runtimeCStr);

	return result;
}
function pixelpart_get_image_resource_width(runtimePtr, resourceId) {
	const runtimeCStr = Module.stringToNewUTF8(runtimePtr);
	const resourceIdCStr = Module.stringToNewUTF8(resourceId);
	const result = Module._pixelpart_get_image_resource_width(runtimeCStr, resourceIdCStr);
	Module._free(runtimeCStr);
	Module._free(resourceIdCStr);

	return result;
}
function pixelpart_get_image_resource_height(runtimePtr, resourceId) {
	const runtimeCStr = Module.stringToNewUTF8(runtimePtr);
	const resourceIdCStr = Module.stringToNewUTF8(resourceId);
	const result = Module._pixelpart_get_image_resource_height(runtimeCStr, resourceIdCStr);
	Module._free(runtimeCStr);
	Module._free(resourceIdCStr);

	return result;
}
function pixelpart_get_image_resource_channels(runtimePtr, resourceId) {
	const runtimeCStr = Module.stringToNewUTF8(runtimePtr);
	const resourceIdCStr = Module.stringToNewUTF8(resourceId);
	const result = Module._pixelpart_get_image_resource_channels(runtimeCStr, resourceIdCStr);
	Module._free(runtimeCStr);
	Module._free(resourceIdCStr);

	return result;
}
function pixelpart_get_image_resource_color_space(runtimePtr, resourceId) {
	const runtimeCStr = Module.stringToNewUTF8(runtimePtr);
	const resourceIdCStr = Module.stringToNewUTF8(resourceId);
	const result = Module._pixelpart_get_image_resource_color_space(runtimeCStr, resourceIdCStr);
	Module._free(runtimeCStr);
	Module._free(resourceIdCStr);

	return result;
}
function pixelpart_get_image_resource_data_size(runtimePtr, resourceId) {
	const runtimeCStr = Module.stringToNewUTF8(runtimePtr);
	const resourceIdCStr = Module.stringToNewUTF8(resourceId);
	const result = Module._pixelpart_get_image_resource_data_size(runtimeCStr, resourceIdCStr);
	Module._free(runtimeCStr);
	Module._free(resourceIdCStr);

	return result;
}
function pixelpart_get_image_resource_data(runtimePtr, resourceId, imageDataBufferPtr) {
	const runtimeCStr = Module.stringToNewUTF8(runtimePtr);
	const resourceIdCStr = Module.stringToNewUTF8(resourceId);
	const nativeDataBufferPtr = Module._malloc(imageDataBufferPtr.byteLength);
	const result = Module._pixelpart_get_image_resource_data(runtimeCStr, resourceIdCStr, nativeDataBufferPtr);
	pixelpartjs_copy_from_native_buffer(imageDataBufferPtr, nativeDataBufferPtr);
	Module._free(nativeDataBufferPtr);
	Module._free(runtimeCStr);
	Module._free(resourceIdCStr);

	return result;
}

// Rendering
function pixelpart_get_sorted_particle_runtime_instances(runtimePtr, indexBufferPtr) {
	const runtimeCStr = Module.stringToNewUTF8(runtimePtr);
	const nativeIndexBufferPtr = Module._malloc(indexBufferPtr.byteLength);
	const result = Module._pixelpart_get_sorted_particle_runtime_instances(runtimeCStr, nativeIndexBufferPtr);
	pixelpartjs_copy_from_native_buffer(indexBufferPtr, nativeIndexBufferPtr);
	Module._free(nativeIndexBufferPtr);
	Module._free(runtimeCStr);

	return result;
}
function pixelpart_construct_particle_geometry(runtimePtr, particleEmitterId, particleTypeId, bufferSizeBufferPtr) {
	const runtimeCStr = Module.stringToNewUTF8(runtimePtr);
	const nativeBufferSizeBufferPtr = Module._malloc(bufferSizeBufferPtr.byteLength);
	const result = Module._pixelpart_construct_particle_geometry(runtimeCStr, particleEmitterId, particleTypeId, nativeBufferSizeBufferPtr);
	pixelpartjs_copy_from_native_buffer(bufferSizeBufferPtr, nativeBufferSizeBufferPtr);
	Module._free(nativeBufferSizeBufferPtr);
	Module._free(runtimeCStr);

	return result;
}
function pixelpart_generate_particle_vertex_data(runtimePtr, particleEmitterId, particleTypeId, vertexBufferPtr) {
	const runtimeCStr = Module.stringToNewUTF8(runtimePtr);
	const nativeVertexBufferPtr = Module._malloc(vertexBufferPtr.byteLength);
	const result = Module._pixelpart_generate_particle_vertex_data(runtimeCStr, particleEmitterId, particleTypeId, nativeVertexBufferPtr);
	pixelpartjs_copy_from_native_buffer(vertexBufferPtr, nativeVertexBufferPtr);
	Module._free(nativeVertexBufferPtr);
	Module._free(runtimeCStr);

	return result;
}

// Built-in material
function pixelpart_get_builtin_material_parameter_count(materialName) {
	const nameCStr = Module.stringToNewUTF8(materialName);
	const result = Module._pixelpart_get_builtin_material_parameter_count(nameCStr);
	Module._free(nameCStr);

	return result;
}
function pixelpart_get_builtin_material_parameters(materialName, idBufferPtr, nameBufferPtr) {
	const nameCStr = Module.stringToNewUTF8(materialName);
	const nativeIdBufferPtr = Module._malloc(idBufferPtr.byteLength);
	const nativeNameBufferPtr = Module._malloc(nameBufferPtr.byteLength);
	const result = Module._pixelpart_get_builtin_material_parameters(nameCStr, nativeIdBufferPtr, nativeNameBufferPtr);
	pixelpartjs_copy_from_native_buffer(idBufferPtr, nativeIdBufferPtr);
	pixelpartjs_copy_from_native_buffer(nameBufferPtr, nativeNameBufferPtr);
	Module._free(nativeNameBufferPtr);
	Module._free(nativeIdBufferPtr);
	Module._free(nameCStr);

	return result;
}

// Effect input
function pixelpart_get_effect_input_count(runtimePtr) {
	const runtimeCStr = Module.stringToNewUTF8(runtimePtr);
	const result = Module._pixelpart_get_effect_input_count(runtimeCStr);
	Module._free(runtimeCStr);

	return result;
}
function pixelpart_get_effect_inputs(runtimePtr, idBufferPtr, typeBufferPtr, nameBufferPtr) {
	const runtimeCStr = Module.stringToNewUTF8(runtimePtr);
	const nativeIdBufferPtr = Module._malloc(idBufferPtr.byteLength);
	const nativeTypeBufferPtr = Module._malloc(typeBufferPtr.byteLength);
	const nativeNameBufferPtr = Module._malloc(nameBufferPtr.byteLength);
	const result = Module._pixelpart_get_effect_inputs(runtimeCStr, nativeIdBufferPtr, nativeTypeBufferPtr, nativeNameBufferPtr);
	pixelpartjs_copy_from_native_buffer(idBufferPtr, nativeIdBufferPtr);
	pixelpartjs_copy_from_native_buffer(typeBufferPtr, nativeTypeBufferPtr);
	pixelpartjs_copy_from_native_buffer(nameBufferPtr, nativeNameBufferPtr);
	Module._free(nativeNameBufferPtr);
	Module._free(nativeTypeBufferPtr);
	Module._free(nativeIdBufferPtr);
	Module._free(runtimeCStr);

	return result;
}
function pixelpart_set_effect_input_bool(runtimePtr, inputId, value) {
	const runtimeCStr = Module.stringToNewUTF8(runtimePtr);
	const result = Module._pixelpart_set_effect_input_bool(runtimeCStr, inputId, value);
	Module._free(runtimeCStr);

	return result;
}
function pixelpart_set_effect_input_int(runtimePtr, inputId, value) {
	const runtimeCStr = Module.stringToNewUTF8(runtimePtr);
	const result = Module._pixelpart_set_effect_input_int(runtimeCStr, inputId, value);
	Module._free(runtimeCStr);

	return result;
}
function pixelpart_set_effect_input_float(runtimePtr, inputId, value) {
	const runtimeCStr = Module.stringToNewUTF8(runtimePtr);
	const result = Module._pixelpart_set_effect_input_float(runtimeCStr, inputId, value);
	Module._free(runtimeCStr);

	return result;
}
function pixelpart_set_effect_input_float2(runtimePtr, inputId, valueBufferPtr) {
	const runtimeCStr = Module.stringToNewUTF8(runtimePtr);
	const nativeValueBufferPtr = pixelpartjs_copy_to_native_buffer(valueBufferPtr);
	const result = Module._pixelpart_set_effect_input_float2(runtimeCStr, inputId, nativeValueBufferPtr);
	Module._free(nativeValueBufferPtr);
	Module._free(runtimeCStr);

	return result;
}
function pixelpart_set_effect_input_float3(runtimePtr, inputId, valueBufferPtr) {
	const runtimeCStr = Module.stringToNewUTF8(runtimePtr);
	const nativeValueBufferPtr = pixelpartjs_copy_to_native_buffer(valueBufferPtr);
	const result = Module._pixelpart_set_effect_input_float3(runtimeCStr, inputId, nativeValueBufferPtr);
	Module._free(nativeValueBufferPtr);
	Module._free(runtimeCStr);

	return result;
}
function pixelpart_set_effect_input_float4(runtimePtr, inputId, valueBufferPtr) {
	const runtimeCStr = Module.stringToNewUTF8(runtimePtr);
	const nativeValueBufferPtr = pixelpartjs_copy_to_native_buffer(valueBufferPtr);
	const result = Module._pixelpart_set_effect_input_float4(runtimeCStr, inputId, nativeValueBufferPtr);
	Module._free(nativeValueBufferPtr);
	Module._free(runtimeCStr);

	return result;
}
function pixelpart_get_effect_input_bool(runtimePtr, inputId) {
	const runtimeCStr = Module.stringToNewUTF8(runtimePtr);
	const result = Module._pixelpart_get_effect_input_bool(runtimeCStr, inputId);
	Module._free(runtimeCStr);

	return result;
}
function pixelpart_get_effect_input_int(runtimePtr, inputId) {
	const runtimeCStr = Module.stringToNewUTF8(runtimePtr);
	const result = Module._pixelpart_get_effect_input_int(runtimeCStr, inputId);
	Module._free(runtimeCStr);

	return result;
}
function pixelpart_get_effect_input_float(runtimePtr, inputId) {
	const runtimeCStr = Module.stringToNewUTF8(runtimePtr);
	const result = Module._pixelpart_get_effect_input_float(runtimeCStr, inputId);
	Module._free(runtimeCStr);

	return result;
}
function pixelpart_get_effect_input_float2(runtimePtr, inputId, valueBufferPtr) {
	const runtimeCStr = Module.stringToNewUTF8(runtimePtr);
	const nativeValueBufferPtr = Module._malloc(valueBufferPtr.byteLength);
	const result = Module._pixelpart_get_effect_input_float2(runtimeCStr, inputId, nativeValueBufferPtr);
	pixelpartjs_copy_from_native_buffer(valueBufferPtr, nativeValueBufferPtr);
	Module._free(nativeValueBufferPtr);
	Module._free(runtimeCStr);

	return result;
}
function pixelpart_get_effect_input_float3(runtimePtr, inputId, valueBufferPtr) {
	const runtimeCStr = Module.stringToNewUTF8(runtimePtr);
	const nativeValueBufferPtr = Module._malloc(valueBufferPtr.byteLength);
	const result = Module._pixelpart_get_effect_input_float3(runtimeCStr, inputId, nativeValueBufferPtr);
	pixelpartjs_copy_from_native_buffer(valueBufferPtr, nativeValueBufferPtr);
	Module._free(nativeValueBufferPtr);
	Module._free(runtimeCStr);

	return result;
}
function pixelpart_get_effect_input_float4(runtimePtr, inputId, valueBufferPtr) {
	const runtimeCStr = Module.stringToNewUTF8(runtimePtr);
	const nativeValueBufferPtr = Module._malloc(valueBufferPtr.byteLength);
	const result = Module._pixelpart_get_effect_input_float4(runtimeCStr, inputId, nativeValueBufferPtr);
	pixelpartjs_copy_from_native_buffer(valueBufferPtr, nativeValueBufferPtr);
	Module._free(nativeValueBufferPtr);
	Module._free(runtimeCStr);

	return result;
}

// Effect trigger
function pixelpart_get_effect_trigger_count(runtimePtr) {
	const runtimeCStr = Module.stringToNewUTF8(runtimePtr);
	const result = Module._pixelpart_get_effect_trigger_count(runtimeCStr);
	Module._free(runtimeCStr);

	return result;
}
function pixelpart_get_effect_triggers(runtimePtr, idBufferPtr, nameBufferPtr) {
	const runtimeCStr = Module.stringToNewUTF8(runtimePtr);
	const nativeIdBufferPtr = Module._malloc(idBufferPtr.byteLength);
	const nativeNameBufferPtr = Module._malloc(nameBufferPtr.byteLength);
	const result = Module._pixelpart_get_effect_triggers(runtimeCStr, nativeIdBufferPtr, nativeNameBufferPtr);
	pixelpartjs_copy_from_native_buffer(idBufferPtr, nativeIdBufferPtr);
	pixelpartjs_copy_from_native_buffer(nameBufferPtr, nativeNameBufferPtr);
	Module._free(nativeNameBufferPtr);
	Module._free(nativeIdBufferPtr);
	Module._free(runtimeCStr);

	return result;
}
function pixelpart_activate_effect_trigger(runtimePtr, triggerId) {
	const runtimeCStr = Module.stringToNewUTF8(runtimePtr);
	const result = Module._pixelpart_activate_effect_trigger(runtimeCStr, triggerId);
	Module._free(runtimeCStr);

	return result;
}
function pixelpart_is_effect_trigger_activated(runtimePtr, triggerId) {
	const runtimeCStr = Module.stringToNewUTF8(runtimePtr);
	const result = Module._pixelpart_is_effect_trigger_activated(runtimeCStr, triggerId);
	Module._free(runtimeCStr);

	return result;
}

// Effect event
function pixelpart_get_effect_event_count(runtimePtr) {
	const runtimeCStr = Module.stringToNewUTF8(runtimePtr);
	const result = Module._pixelpart_get_effect_event_count(runtimeCStr);
	Module._free(runtimeCStr);

	return result;
}
function pixelpart_get_effect_events(runtimePtr, idBufferPtr, nameBufferPtr) {
	const runtimeCStr = Module.stringToNewUTF8(runtimePtr);
	const nativeIdBufferPtr = Module._malloc(idBufferPtr.byteLength);
	const nativeNameBufferPtr = Module._malloc(nameBufferPtr.byteLength);
	const result = Module._pixelpart_get_effect_events(runtimeCStr, nativeIdBufferPtr, nativeNameBufferPtr);
	pixelpartjs_copy_from_native_buffer(idBufferPtr, nativeIdBufferPtr);
	pixelpartjs_copy_from_native_buffer(nameBufferPtr, nativeNameBufferPtr);
	Module._free(nativeNameBufferPtr);
	Module._free(nativeIdBufferPtr);
	Module._free(runtimeCStr);

	return result;
}
function pixelpart_get_invoked_effect_events(runtimePtr, idBufferPtr) {
	const runtimeCStr = Module.stringToNewUTF8(runtimePtr);
	const nativeIdBufferPtr = Module._malloc(idBufferPtr.byteLength);
	const result = Module._pixelpart_get_invoked_effect_events(runtimeCStr, nativeIdBufferPtr);
	pixelpartjs_copy_from_native_buffer(idBufferPtr, nativeIdBufferPtr);
	Module._free(nativeIdBufferPtr);
	Module._free(runtimeCStr);

	return result;
}

// Node
function pixelpart_find_node(runtimePtr, name) {
	const runtimeCStr = Module.stringToNewUTF8(runtimePtr);
	const nameCStr = Module.stringToNewUTF8(name);
	const result = Module._pixelpart_find_node(runtimeCStr, nameCStr);
	Module._free(nameCStr);
	Module._free(runtimeCStr);

	return result;
}
function pixelpart_find_node_by_index(runtimePtr, nodeIndex) {
	const runtimeCStr = Module.stringToNewUTF8(runtimePtr);
	const result = Module._pixelpart_find_node_by_index(runtimeCStr, nodeIndex);
	Module._free(runtimeCStr);

	return result;
}
function pixelpart_node_exists(runtimePtr, nodeId) {
	const runtimeCStr = Module.stringToNewUTF8(runtimePtr);
	const result = Module._pixelpart_node_exists(runtimeCStr, nodeId);
	Module._free(runtimeCStr);

	return result;
}
function pixelpart_node_get_type(runtimePtr, nodeId) {
	const runtimeCStr = Module.stringToNewUTF8(runtimePtr);
	const result = Module._pixelpart_node_get_type(runtimeCStr, nodeId);
	Module._free(runtimeCStr);

	return result;
}
function pixelpart_node_get_name(runtimePtr, nodeId) {
	const runtimeCStr = Module.stringToNewUTF8(runtimePtr);
	const result = Module.UTF8ToString(Module._pixelpart_node_get_name(runtimeCStr, nodeId));
	Module._free(runtimeCStr);

	return result;
}
function pixelpart_node_get_parent_id(runtimePtr, nodeId) {
	const runtimeCStr = Module.stringToNewUTF8(runtimePtr);
	const result = Module._pixelpart_node_get_parent_id(runtimeCStr, nodeId);
	Module._free(runtimeCStr);

	return result;
}
function pixelpart_node_set_lifetime_start(runtimePtr, nodeId, value) {
	const runtimeCStr = Module.stringToNewUTF8(runtimePtr);
	const result = Module._pixelpart_node_set_lifetime_start(runtimeCStr, nodeId, value);
	Module._free(runtimeCStr);

	return result;
}
function pixelpart_node_set_lifetime_duration(runtimePtr, nodeId, value) {
	const runtimeCStr = Module.stringToNewUTF8(runtimePtr);
	const result = Module._pixelpart_node_set_lifetime_duration(runtimeCStr, nodeId, value);
	Module._free(runtimeCStr);

	return result;
}
function pixelpart_node_set_repeat(runtimePtr, nodeId, value) {
	const runtimeCStr = Module.stringToNewUTF8(runtimePtr);
	const result = Module._pixelpart_node_set_repeat(runtimeCStr, nodeId, value);
	Module._free(runtimeCStr);

	return result;
}
function pixelpart_node_get_lifetime_start(runtimePtr, nodeId) {
	const runtimeCStr = Module.stringToNewUTF8(runtimePtr);
	const result = Module._pixelpart_node_get_lifetime_start(runtimeCStr, nodeId);
	Module._free(runtimeCStr);

	return result;
}
function pixelpart_node_get_lifetime_duration(runtimePtr, nodeId) {
	const runtimeCStr = Module.stringToNewUTF8(runtimePtr);
	const result = Module._pixelpart_node_get_lifetime_duration(runtimeCStr, nodeId);
	Module._free(runtimeCStr);

	return result;
}
function pixelpart_node_is_repeating(runtimePtr, nodeId) {
	const runtimeCStr = Module.stringToNewUTF8(runtimePtr);
	const result = Module._pixelpart_node_is_repeating(runtimeCStr, nodeId);
	Module._free(runtimeCStr);

	return result;
}
function pixelpart_node_is_active(runtimePtr, nodeId) {
	const runtimeCStr = Module.stringToNewUTF8(runtimePtr);
	const result = Module._pixelpart_node_is_active(runtimeCStr, nodeId);
	Module._free(runtimeCStr);

	return result;
}
function pixelpart_node_get_local_time(runtimePtr, nodeId) {
	const runtimeCStr = Module.stringToNewUTF8(runtimePtr);
	const result = Module._pixelpart_node_get_local_time(runtimeCStr, nodeId);
	Module._free(runtimeCStr);

	return result;
}
function pixelpart_node_get_position(runtimePtr, nodeId) {
	const runtimeCStr = Module.stringToNewUTF8(runtimePtr);
	const result = Module.UTF8ToString(Module._pixelpart_node_get_position(runtimeCStr, nodeId));
	Module._free(runtimeCStr);

	return result;
}
function pixelpart_node_get_rotation(runtimePtr, nodeId) {
	const runtimeCStr = Module.stringToNewUTF8(runtimePtr);
	const result = Module.UTF8ToString(Module._pixelpart_node_get_rotation(runtimeCStr, nodeId));
	Module._free(runtimeCStr);

	return result;
}
function pixelpart_node_get_scale(runtimePtr, nodeId) {
	const runtimeCStr = Module.stringToNewUTF8(runtimePtr);
	const result = Module.UTF8ToString(Module._pixelpart_node_get_scale(runtimeCStr, nodeId));
	Module._free(runtimeCStr);

	return result;
}

// Particle emitter
function pixelpart_particle_emitter_set_shape(runtimePtr, emitterId, shape) {
	const runtimeCStr = Module.stringToNewUTF8(runtimePtr);
	const result = Module._pixelpart_particle_emitter_set_shape(runtimeCStr, emitterId, shape);
	Module._free(runtimeCStr);

	return result;
}
function pixelpart_particle_emitter_get_shape(runtimePtr, emitterId) {
	const runtimeCStr = Module.stringToNewUTF8(runtimePtr);
	const result = Module._pixelpart_particle_emitter_get_shape(runtimeCStr, emitterId);
	Module._free(runtimeCStr);

	return result;
}
function pixelpart_particle_emitter_add_shape_point(runtimePtr, emitterId, valueBufferPtr) {
	const runtimeCStr = Module.stringToNewUTF8(runtimePtr);
	const nativeValueBufferPtr = pixelpartjs_copy_to_native_buffer(valueBufferPtr);
	const result = Module._pixelpart_particle_emitter_add_shape_point(runtimeCStr, emitterId, nativeValueBufferPtr);
	Module._free(nativeValueBufferPtr);
	Module._free(runtimeCStr);

	return result;
}
function pixelpart_particle_emitter_remove_shape_point(runtimePtr, emitterId, index) {
	const runtimeCStr = Module.stringToNewUTF8(runtimePtr);
	const result = Module._pixelpart_particle_emitter_remove_shape_point(runtimeCStr, emitterId, index);
	Module._free(runtimeCStr);

	return result;
}
function pixelpart_particle_emitter_set_shape_point(runtimePtr, emitterId, index, valueBufferPtr) {
	const runtimeCStr = Module.stringToNewUTF8(runtimePtr);
	const nativeValueBufferPtr = pixelpartjs_copy_to_native_buffer(valueBufferPtr);
	const result = Module._pixelpart_particle_emitter_set_shape_point(runtimeCStr, emitterId, index, nativeValueBufferPtr);
	Module._free(nativeValueBufferPtr);
	Module._free(runtimeCStr);

	return result;
}
function pixelpart_particle_emitter_get_shape_point(runtimePtr, emitterId, index, valueBufferPtr) {
	const runtimeCStr = Module.stringToNewUTF8(runtimePtr);
	const nativeValueBufferPtr = Module._malloc(valueBufferPtr.byteLength);
	const result = Module._pixelpart_particle_emitter_get_shape_point(runtimeCStr, emitterId, index, nativeValueBufferPtr);
	pixelpartjs_copy_from_native_buffer(valueBufferPtr, nativeValueBufferPtr);
	Module._free(nativeValueBufferPtr);
	Module._free(runtimeCStr);

	return result;
}
function pixelpart_particle_emitter_get_shape_point_count(runtimePtr, emitterId) {
	const runtimeCStr = Module.stringToNewUTF8(runtimePtr);
	const result = Module._pixelpart_particle_emitter_get_shape_point_count(runtimeCStr, emitterId);
	Module._free(runtimeCStr);

	return result;
}
function pixelpart_particle_emitter_set_distribution(runtimePtr, emitterId, mode) {
	const runtimeCStr = Module.stringToNewUTF8(runtimePtr);
	const result = Module._pixelpart_particle_emitter_set_distribution(runtimeCStr, emitterId, mode);
	Module._free(runtimeCStr);

	return result;
}
function pixelpart_particle_emitter_get_distribution(runtimePtr, emitterId) {
	const runtimeCStr = Module.stringToNewUTF8(runtimePtr);
	const result = Module._pixelpart_particle_emitter_get_distribution(runtimeCStr, emitterId);
	Module._free(runtimeCStr);

	return result;
}
function pixelpart_particle_emitter_set_grid_order(runtimePtr, emitterId, mode) {
	const runtimeCStr = Module.stringToNewUTF8(runtimePtr);
	const result = Module._pixelpart_particle_emitter_set_grid_order(runtimeCStr, emitterId, mode);
	Module._free(runtimeCStr);

	return result;
}
function pixelpart_particle_emitter_get_grid_order(runtimePtr, emitterId) {
	const runtimeCStr = Module.stringToNewUTF8(runtimePtr);
	const result = Module._pixelpart_particle_emitter_get_grid_order(runtimeCStr, emitterId);
	Module._free(runtimeCStr);

	return result;
}
function pixelpart_particle_emitter_set_grid_size(runtimePtr, emitterId, valueBufferPtr) {
	const runtimeCStr = Module.stringToNewUTF8(runtimePtr);
	const nativeValueBufferPtr = pixelpartjs_copy_to_native_buffer(valueBufferPtr);
	const result = Module._pixelpart_particle_emitter_set_grid_size(runtimeCStr, emitterId, nativeValueBufferPtr);
	Module._free(nativeValueBufferPtr);
	Module._free(runtimeCStr);

	return result;
}
function pixelpart_particle_emitter_get_grid_size_x(runtimePtr, emitterId) {
	const runtimeCStr = Module.stringToNewUTF8(runtimePtr);
	const result = Module._pixelpart_particle_emitter_get_grid_size_x(runtimeCStr, emitterId);
	Module._free(runtimeCStr);

	return result;
}
function pixelpart_particle_emitter_get_grid_size_y(runtimePtr, emitterId) {
	const runtimeCStr = Module.stringToNewUTF8(runtimePtr);
	const result = Module._pixelpart_particle_emitter_get_grid_size_y(runtimeCStr, emitterId);
	Module._free(runtimeCStr);

	return result;
}
function pixelpart_particle_emitter_get_grid_size_z(runtimePtr, emitterId) {
	const runtimeCStr = Module.stringToNewUTF8(runtimePtr);
	const result = Module._pixelpart_particle_emitter_get_grid_size_z(runtimeCStr, emitterId);
	Module._free(runtimeCStr);

	return result;
}
function pixelpart_particle_emitter_set_emission_mode(runtimePtr, emitterId, mode) {
	const runtimeCStr = Module.stringToNewUTF8(runtimePtr);
	const result = Module._pixelpart_particle_emitter_set_emission_mode(runtimeCStr, emitterId, mode);
	Module._free(runtimeCStr);

	return result;
}
function pixelpart_particle_emitter_get_emission_mode(runtimePtr, emitterId) {
	const runtimeCStr = Module.stringToNewUTF8(runtimePtr);
	const result = Module._pixelpart_particle_emitter_get_emission_mode(runtimeCStr, emitterId);
	Module._free(runtimeCStr);

	return result;
}
function pixelpart_particle_emitter_set_direction_mode(runtimePtr, emitterId, mode) {
	const runtimeCStr = Module.stringToNewUTF8(runtimePtr);
	const result = Module._pixelpart_particle_emitter_set_direction_mode(runtimeCStr, emitterId, mode);
	Module._free(runtimeCStr);

	return result;
}
function pixelpart_particle_emitter_get_direction_mode(runtimePtr, emitterId) {
	const runtimeCStr = Module.stringToNewUTF8(runtimePtr);
	const result = Module._pixelpart_particle_emitter_get_direction_mode(runtimeCStr, emitterId);
	Module._free(runtimeCStr);

	return result;
}
function pixelpart_particle_emitter_get_direction(runtimePtr, emitterId) {
	const runtimeCStr = Module.stringToNewUTF8(runtimePtr);
	const result = Module.UTF8ToString(Module._pixelpart_particle_emitter_get_direction(runtimeCStr, emitterId));
	Module._free(runtimeCStr);

	return result;
}
function pixelpart_particle_emitter_get_spread(runtimePtr, emitterId) {
	const runtimeCStr = Module.stringToNewUTF8(runtimePtr);
	const result = Module.UTF8ToString(Module._pixelpart_particle_emitter_get_spread(runtimeCStr, emitterId));
	Module._free(runtimeCStr);

	return result;
}

// Force field
function pixelpart_force_field_set_infinite(runtimePtr, forceFieldId, mode) {
	const runtimeCStr = Module.stringToNewUTF8(runtimePtr);
	const result = Module._pixelpart_force_field_set_infinite(runtimeCStr, forceFieldId, mode);
	Module._free(runtimeCStr);

	return result;
}
function pixelpart_force_field_is_infinite(runtimePtr, forceFieldId) {
	const runtimeCStr = Module.stringToNewUTF8(runtimePtr);
	const result = Module._pixelpart_force_field_is_infinite(runtimeCStr, forceFieldId);
	Module._free(runtimeCStr);

	return result;
}
function pixelpart_force_field_get_strength(runtimePtr, forceFieldId) {
	const runtimeCStr = Module.stringToNewUTF8(runtimePtr);
	const result = Module.UTF8ToString(Module._pixelpart_force_field_get_strength(runtimeCStr, forceFieldId));
	Module._free(runtimeCStr);

	return result;
}
function pixelpart_attraction_field_get_falloff_power(runtimePtr, forceFieldId) {
	const runtimeCStr = Module.stringToNewUTF8(runtimePtr);
	const result = Module.UTF8ToString(Module._pixelpart_attraction_field_get_falloff_power(runtimeCStr, forceFieldId));
	Module._free(runtimeCStr);

	return result;
}
function pixelpart_acceleration_field_get_acceleration_direction(runtimePtr, forceFieldId) {
	const runtimeCStr = Module.stringToNewUTF8(runtimePtr);
	const result = Module.UTF8ToString(Module._pixelpart_acceleration_field_get_acceleration_direction(runtimeCStr, forceFieldId));
	Module._free(runtimeCStr);

	return result;
}
function pixelpart_acceleration_field_get_acceleration_direction_variance(runtimePtr, forceFieldId) {
	const runtimeCStr = Module.stringToNewUTF8(runtimePtr);
	const result = Module.UTF8ToString(Module._pixelpart_acceleration_field_get_acceleration_direction_variance(runtimeCStr, forceFieldId));
	Module._free(runtimeCStr);

	return result;
}
function pixelpart_acceleration_field_get_acceleration_strength_variance(runtimePtr, forceFieldId) {
	const runtimeCStr = Module.stringToNewUTF8(runtimePtr);
	const result = Module.UTF8ToString(Module._pixelpart_acceleration_field_get_acceleration_strength_variance(runtimeCStr, forceFieldId));
	Module._free(runtimeCStr);

	return result;
}
function pixelpart_acceleration_field_set_acceleration_grid_size(runtimePtr, forceFieldId, valueBufferPtr) {
	const runtimeCStr = Module.stringToNewUTF8(runtimePtr);
	const nativeValueBufferPtr = pixelpartjs_copy_to_native_buffer(valueBufferPtr);
	const result = Module._pixelpart_acceleration_field_set_acceleration_grid_size(runtimeCStr, forceFieldId, nativeValueBufferPtr);
	Module._free(nativeValueBufferPtr);
	Module._free(runtimeCStr);

	return result;
}
function pixelpart_acceleration_field_get_acceleration_grid_size_x(runtimePtr, forceFieldId) {
	const runtimeCStr = Module.stringToNewUTF8(runtimePtr);
	const result = Module._pixelpart_acceleration_field_get_acceleration_grid_size_x(runtimeCStr, forceFieldId);
	Module._free(runtimeCStr);

	return result;
}
function pixelpart_acceleration_field_get_acceleration_grid_size_y(runtimePtr, forceFieldId) {
	const runtimeCStr = Module.stringToNewUTF8(runtimePtr);
	const result = Module._pixelpart_acceleration_field_get_acceleration_grid_size_y(runtimeCStr, forceFieldId);
	Module._free(runtimeCStr);

	return result;
}
function pixelpart_acceleration_field_get_acceleration_grid_size_z(runtimePtr, forceFieldId) {
	const runtimeCStr = Module.stringToNewUTF8(runtimePtr);
	const result = Module._pixelpart_acceleration_field_get_acceleration_grid_size_z(runtimeCStr, forceFieldId);
	Module._free(runtimeCStr);

	return result;
}
function pixelpart_vector_field_set_vector_field_filter(runtimePtr, forceFieldId, filter) {
	const runtimeCStr = Module.stringToNewUTF8(runtimePtr);
	const result = Module._pixelpart_vector_field_set_vector_field_filter(runtimeCStr, forceFieldId, filter);
	Module._free(runtimeCStr);

	return result;
}
function pixelpart_vector_field_get_vector_field_filter(runtimePtr, forceFieldId) {
	const runtimeCStr = Module.stringToNewUTF8(runtimePtr);
	const result = Module._pixelpart_vector_field_get_vector_field_filter(runtimeCStr, forceFieldId);
	Module._free(runtimeCStr);

	return result;
}
function pixelpart_vector_field_get_tightness(runtimePtr, forceFieldId) {
	const runtimeCStr = Module.stringToNewUTF8(runtimePtr);
	const result = Module.UTF8ToString(Module._pixelpart_vector_field_get_tightness(runtimeCStr, forceFieldId));
	Module._free(runtimeCStr);

	return result;
}
function pixelpart_noise_field_get_noise_octaves(runtimePtr, forceFieldId) {
	const runtimeCStr = Module.stringToNewUTF8(runtimePtr);
	const result = Module.UTF8ToString(Module._pixelpart_noise_field_get_noise_octaves(runtimeCStr, forceFieldId));
	Module._free(runtimeCStr);

	return result;
}
function pixelpart_noise_field_get_noise_frequency(runtimePtr, forceFieldId) {
	const runtimeCStr = Module.stringToNewUTF8(runtimePtr);
	const result = Module.UTF8ToString(Module._pixelpart_noise_field_get_noise_frequency(runtimeCStr, forceFieldId));
	Module._free(runtimeCStr);

	return result;
}
function pixelpart_noise_field_get_noise_persistence(runtimePtr, forceFieldId) {
	const runtimeCStr = Module.stringToNewUTF8(runtimePtr);
	const result = Module.UTF8ToString(Module._pixelpart_noise_field_get_noise_persistence(runtimeCStr, forceFieldId));
	Module._free(runtimeCStr);

	return result;
}
function pixelpart_noise_field_get_noise_lacunarity(runtimePtr, forceFieldId) {
	const runtimeCStr = Module.stringToNewUTF8(runtimePtr);
	const result = Module.UTF8ToString(Module._pixelpart_noise_field_get_noise_lacunarity(runtimeCStr, forceFieldId));
	Module._free(runtimeCStr);

	return result;
}
function pixelpart_noise_field_set_noise_animated(runtimePtr, forceFieldId, animated) {
	const runtimeCStr = Module.stringToNewUTF8(runtimePtr);
	const result = Module._pixelpart_noise_field_set_noise_animated(runtimeCStr, forceFieldId, animated);
	Module._free(runtimeCStr);

	return result;
}
function pixelpart_noise_field_is_noise_animated(runtimePtr, forceFieldId) {
	const runtimeCStr = Module.stringToNewUTF8(runtimePtr);
	const result = Module._pixelpart_noise_field_is_noise_animated(runtimeCStr, forceFieldId);
	Module._free(runtimeCStr);

	return result;
}
function pixelpart_noise_field_get_noise_animation_time_scale(runtimePtr, forceFieldId) {
	const runtimeCStr = Module.stringToNewUTF8(runtimePtr);
	const result = Module.UTF8ToString(Module._pixelpart_noise_field_get_noise_animation_time_scale(runtimeCStr, forceFieldId));
	Module._free(runtimeCStr);

	return result;
}
function pixelpart_noise_field_get_noise_animation_time_base(runtimePtr, forceFieldId) {
	const runtimeCStr = Module.stringToNewUTF8(runtimePtr);
	const result = Module.UTF8ToString(Module._pixelpart_noise_field_get_noise_animation_time_base(runtimeCStr, forceFieldId));
	Module._free(runtimeCStr);

	return result;
}
function pixelpart_drag_field_get_velocity_influence(runtimePtr, forceFieldId) {
	const runtimeCStr = Module.stringToNewUTF8(runtimePtr);
	const result = Module.UTF8ToString(Module._pixelpart_drag_field_get_velocity_influence(runtimeCStr, forceFieldId));
	Module._free(runtimeCStr);

	return result;
}
function pixelpart_drag_field_get_size_influence(runtimePtr, forceFieldId) {
	const runtimeCStr = Module.stringToNewUTF8(runtimePtr);
	const result = Module.UTF8ToString(Module._pixelpart_drag_field_get_size_influence(runtimeCStr, forceFieldId));
	Module._free(runtimeCStr);

	return result;
}
function pixelpart_vortex_field_get_tangential_strength(runtimePtr, forceFieldId) {
	const runtimeCStr = Module.stringToNewUTF8(runtimePtr);
	const result = Module.UTF8ToString(Module._pixelpart_vortex_field_get_tangential_strength(runtimeCStr, forceFieldId));
	Module._free(runtimeCStr);

	return result;
}
function pixelpart_vortex_field_get_radial_strength(runtimePtr, forceFieldId) {
	const runtimeCStr = Module.stringToNewUTF8(runtimePtr);
	const result = Module.UTF8ToString(Module._pixelpart_vortex_field_get_radial_strength(runtimeCStr, forceFieldId));
	Module._free(runtimeCStr);

	return result;
}

// Collider
function pixelpart_collider_get_kill_on_contact(runtimePtr, colliderId) {
	const runtimeCStr = Module.stringToNewUTF8(runtimePtr);
	const result = Module.UTF8ToString(Module._pixelpart_collider_get_kill_on_contact(runtimeCStr, colliderId));
	Module._free(runtimeCStr);

	return result;
}
function pixelpart_collider_get_bounce(runtimePtr, colliderId) {
	const runtimeCStr = Module.stringToNewUTF8(runtimePtr);
	const result = Module.UTF8ToString(Module._pixelpart_collider_get_bounce(runtimeCStr, colliderId));
	Module._free(runtimeCStr);

	return result;
}
function pixelpart_collider_get_friction(runtimePtr, colliderId) {
	const runtimeCStr = Module.stringToNewUTF8(runtimePtr);
	const result = Module.UTF8ToString(Module._pixelpart_collider_get_friction(runtimeCStr, colliderId));
	Module._free(runtimeCStr);

	return result;
}
function pixelpart_line_collider_add_point(runtimePtr, colliderId, valueBufferPtr) {
	const runtimeCStr = Module.stringToNewUTF8(runtimePtr);
	const nativeValueBufferPtr = pixelpartjs_copy_to_native_buffer(valueBufferPtr);
	const result = Module._pixelpart_line_collider_add_point(runtimeCStr, colliderId, nativeValueBufferPtr);
	Module._free(nativeValueBufferPtr);
	Module._free(runtimeCStr);

	return result;
}
function pixelpart_line_collider_set_point(runtimePtr, colliderId, index, valueBufferPtr) {
	const runtimeCStr = Module.stringToNewUTF8(runtimePtr);
	const nativeValueBufferPtr = pixelpartjs_copy_to_native_buffer(valueBufferPtr);
	const result = Module._pixelpart_line_collider_set_point(runtimeCStr, colliderId, index, nativeValueBufferPtr);
	Module._free(nativeValueBufferPtr);
	Module._free(runtimeCStr);

	return result;
}
function pixelpart_line_collider_remove_point(runtimePtr, colliderId, index) {
	const runtimeCStr = Module.stringToNewUTF8(runtimePtr);
	const result = Module._pixelpart_line_collider_remove_point(runtimeCStr, colliderId, index);
	Module._free(runtimeCStr);

	return result;
}
function pixelpart_line_collider_get_point(runtimePtr, colliderId, index, valueBufferPtr) {
	const runtimeCStr = Module.stringToNewUTF8(runtimePtr);
	const nativeValueBufferPtr = Module._malloc(valueBufferPtr.byteLength);
	const result = Module._pixelpart_line_collider_get_point(runtimeCStr, colliderId, index, nativeValueBufferPtr);
	pixelpartjs_copy_from_native_buffer(valueBufferPtr, nativeValueBufferPtr);
	Module._free(nativeValueBufferPtr);
	Module._free(runtimeCStr);

	return result;
}
function pixelpart_line_collider_get_point_count(runtimePtr, colliderId) {
	const runtimeCStr = Module.stringToNewUTF8(runtimePtr);
	const result = Module._pixelpart_line_collider_get_point_count(runtimeCStr, colliderId);
	Module._free(runtimeCStr);

	return result;
}

// Light source
function pixelpart_light_source_get_attenuation(runtimePtr, lightSourceId) {
	const runtimeCStr = Module.stringToNewUTF8(runtimePtr);
	const result = Module.UTF8ToString(Module._pixelpart_light_source_get_attenuation(runtimeCStr, lightSourceId));
	Module._free(runtimeCStr);

	return result;
}
function pixelpart_light_source_get_color(runtimePtr, lightSourceId) {
	const runtimeCStr = Module.stringToNewUTF8(runtimePtr);
	const result = Module.UTF8ToString(Module._pixelpart_light_source_get_color(runtimeCStr, lightSourceId));
	Module._free(runtimeCStr);

	return result;
}
function pixelpart_light_source_get_intensity(runtimePtr, lightSourceId) {
	const runtimeCStr = Module.stringToNewUTF8(runtimePtr);
	const result = Module.UTF8ToString(Module._pixelpart_light_source_get_intensity(runtimeCStr, lightSourceId));
	Module._free(runtimeCStr);

	return result;
}
function pixelpart_spot_light_source_get_spot_angle(runtimePtr, lightSourceId) {
	const runtimeCStr = Module.stringToNewUTF8(runtimePtr);
	const result = Module.UTF8ToString(Module._pixelpart_spot_light_source_get_spot_angle(runtimeCStr, lightSourceId));
	Module._free(runtimeCStr);

	return result;
}
function pixelpart_spot_light_source_get_spot_angle_attenuation(runtimePtr, lightSourceId) {
	const runtimeCStr = Module.stringToNewUTF8(runtimePtr);
	const result = Module.UTF8ToString(Module._pixelpart_spot_light_source_get_spot_angle_attenuation(runtimeCStr, lightSourceId));
	Module._free(runtimeCStr);

	return result;
}

// Particle type
function pixelpart_find_particle_type(runtimePtr, name) {
	const runtimeCStr = Module.stringToNewUTF8(runtimePtr);
	const nameCStr = Module.stringToNewUTF8(name);
	const result = Module._pixelpart_find_particle_type(runtimeCStr, nameCStr);
	Module._free(nameCStr);
	Module._free(runtimeCStr);

	return result;
}
function pixelpart_find_particle_type_by_index(runtimePtr, particleTypeIndex) {
	const runtimeCStr = Module.stringToNewUTF8(runtimePtr);
	const result = Module._pixelpart_find_particle_type_by_index(runtimeCStr, particleTypeIndex);
	Module._free(runtimeCStr);

	return result;
}
function pixelpart_particle_type_exists(runtimePtr, particleTypeId) {
	const runtimeCStr = Module.stringToNewUTF8(runtimePtr);
	const result = Module._pixelpart_particle_type_exists(runtimeCStr, particleTypeId);
	Module._free(runtimeCStr);

	return result;
}
function pixelpart_particle_type_get_index(runtimePtr, particleTypeId) {
	const runtimeCStr = Module.stringToNewUTF8(runtimePtr);
	const result = Module._pixelpart_particle_type_get_index(runtimeCStr, particleTypeId);
	Module._free(runtimeCStr);

	return result;
}
function pixelpart_particle_type_get_parent_id(runtimePtr, particleTypeId) {
	const runtimeCStr = Module.stringToNewUTF8(runtimePtr);
	const result = Module._pixelpart_particle_type_get_parent_id(runtimeCStr, particleTypeId);
	Module._free(runtimeCStr);

	return result;
}
function pixelpart_particle_type_get_name(runtimePtr, particleTypeId) {
	const runtimeCStr = Module.stringToNewUTF8(runtimePtr);
	const result = Module.UTF8ToString(Module._pixelpart_particle_type_get_name(runtimeCStr, particleTypeId));
	Module._free(runtimeCStr);

	return result;
}
function pixelpart_particle_type_set_position_relative(runtimePtr, particleTypeId, relative) {
	const runtimeCStr = Module.stringToNewUTF8(runtimePtr);
	const result = Module._pixelpart_particle_type_set_position_relative(runtimeCStr, particleTypeId, relative);
	Module._free(runtimeCStr);

	return result;
}
function pixelpart_particle_type_is_position_relative(runtimePtr, particleTypeId) {
	const runtimeCStr = Module.stringToNewUTF8(runtimePtr);
	const result = Module._pixelpart_particle_type_is_position_relative(runtimeCStr, particleTypeId);
	Module._free(runtimeCStr);

	return result;
}
function pixelpart_particle_type_set_rotation_mode(runtimePtr, particleTypeId, mode) {
	const runtimeCStr = Module.stringToNewUTF8(runtimePtr);
	const result = Module._pixelpart_particle_type_set_rotation_mode(runtimeCStr, particleTypeId, mode);
	Module._free(runtimeCStr);

	return result;
}
function pixelpart_particle_type_get_rotation_mode(runtimePtr, particleTypeId) {
	const runtimeCStr = Module.stringToNewUTF8(runtimePtr);
	const result = Module._pixelpart_particle_type_get_rotation_mode(runtimeCStr, particleTypeId);
	Module._free(runtimeCStr);

	return result;
}
function pixelpart_particle_type_set_alignment_mode(runtimePtr, particleTypeId, mode) {
	const runtimeCStr = Module.stringToNewUTF8(runtimePtr);
	const result = Module._pixelpart_particle_type_set_alignment_mode(runtimeCStr, particleTypeId, mode);
	Module._free(runtimeCStr);

	return result;
}
function pixelpart_particle_type_get_alignment_mode(runtimePtr, particleTypeId) {
	const runtimeCStr = Module.stringToNewUTF8(runtimePtr);
	const result = Module._pixelpart_particle_type_get_alignment_mode(runtimeCStr, particleTypeId);
	Module._free(runtimeCStr);

	return result;
}
function pixelpart_particle_type_get_pivot(runtimePtr, particleTypeId) {
	const runtimeCStr = Module.stringToNewUTF8(runtimePtr);
	const result = Module.UTF8ToString(Module._pixelpart_particle_type_get_pivot(runtimeCStr, particleTypeId));
	Module._free(runtimeCStr);

	return result;
}
function pixelpart_particle_type_get_motion_path_force(runtimePtr, particleTypeId) {
	const runtimeCStr = Module.stringToNewUTF8(runtimePtr);
	const result = Module.UTF8ToString(Module._pixelpart_particle_type_get_motion_path_force(runtimeCStr, particleTypeId));
	Module._free(runtimeCStr);

	return result;
}
function pixelpart_particle_type_set_visible(runtimePtr, particleTypeId, visible) {
	const runtimeCStr = Module.stringToNewUTF8(runtimePtr);
	const result = Module._pixelpart_particle_type_set_visible(runtimeCStr, particleTypeId, visible);
	Module._free(runtimeCStr);

	return result;
}
function pixelpart_particle_type_is_visible(runtimePtr, particleTypeId) {
	const runtimeCStr = Module.stringToNewUTF8(runtimePtr);
	const result = Module._pixelpart_particle_type_is_visible(runtimeCStr, particleTypeId);
	Module._free(runtimeCStr);

	return result;
}
function pixelpart_particle_type_is_visible_at_current_lod(runtimePtr, particleTypeId) {
	const runtimeCStr = Module.stringToNewUTF8(runtimePtr);
	const result = Module._pixelpart_particle_type_is_visible_at_current_lod(runtimeCStr, particleTypeId);
	Module._free(runtimeCStr);

	return result;
}
function pixelpart_particle_type_set_layer(runtimePtr, particleTypeId, layer) {
	const runtimeCStr = Module.stringToNewUTF8(runtimePtr);
	const result = Module._pixelpart_particle_type_set_layer(runtimeCStr, particleTypeId, layer);
	Module._free(runtimeCStr);

	return result;
}
function pixelpart_particle_type_get_layer(runtimePtr, particleTypeId) {
	const runtimeCStr = Module.stringToNewUTF8(runtimePtr);
	const result = Module._pixelpart_particle_type_get_layer(runtimeCStr, particleTypeId);
	Module._free(runtimeCStr);

	return result;
}
function pixelpart_particle_type_get_material_id(runtimePtr, particleTypeId) {
	const runtimeCStr = Module.stringToNewUTF8(runtimePtr);
	const result = Module.UTF8ToString(Module._pixelpart_particle_type_get_material_id(runtimeCStr, particleTypeId));
	Module._free(runtimeCStr);

	return result;
}
function pixelpart_particle_type_is_material_builtin(runtimePtr, particleTypeId) {
	const runtimeCStr = Module.stringToNewUTF8(runtimePtr);
	const result = Module._pixelpart_particle_type_is_material_builtin(runtimeCStr, particleTypeId);
	Module._free(runtimeCStr);

	return result;
}
function pixelpart_particle_type_get_material_parameter_count(runtimePtr, particleTypeId) {
	const runtimeCStr = Module.stringToNewUTF8(runtimePtr);
	const result = Module._pixelpart_particle_type_get_material_parameter_count(runtimeCStr, particleTypeId);
	Module._free(runtimeCStr);

	return result;
}
function pixelpart_particle_type_get_material_parameter_ids(runtimePtr, particleTypeId, parameterIdBufferPtr) {
	const runtimeCStr = Module.stringToNewUTF8(runtimePtr);
	const nativeParameterIdBufferPtr = Module._malloc(parameterIdBufferPtr.byteLength);
	const result = Module._pixelpart_particle_type_get_material_parameter_ids(runtimeCStr, particleTypeId, nativeParameterIdBufferPtr);
	pixelpartjs_copy_from_native_buffer(parameterIdBufferPtr, nativeParameterIdBufferPtr);
	Module._free(nativeParameterIdBufferPtr);
	Module._free(runtimeCStr);

	return result;
}
function pixelpart_particle_type_get_material_parameter_type(runtimePtr, particleTypeId, parameterId) {
	const runtimeCStr = Module.stringToNewUTF8(runtimePtr);
	const result = Module._pixelpart_particle_type_get_material_parameter_type(runtimeCStr, particleTypeId, parameterId);
	Module._free(runtimeCStr);

	return result;
}
function pixelpart_particle_type_get_material_parameter_value(runtimePtr, particleTypeId, parameterId, resultBufferPtr) {
	const runtimeCStr = Module.stringToNewUTF8(runtimePtr);
	const nativeResultBufferPtr = Module._malloc(resultBufferPtr.byteLength);
	const result = Module._pixelpart_particle_type_get_material_parameter_value(runtimeCStr, particleTypeId, parameterId, nativeResultBufferPtr);
	pixelpartjs_copy_from_native_buffer(resultBufferPtr, nativeResultBufferPtr);
	Module._free(nativeResultBufferPtr);
	Module._free(runtimeCStr);

	return result;
}
function pixelpart_particle_type_get_renderer(runtimePtr, particleTypeId) {
	const runtimeCStr = Module.stringToNewUTF8(runtimePtr);
	const result = Module._pixelpart_particle_type_get_renderer(runtimeCStr, particleTypeId);
	Module._free(runtimeCStr);

	return result;
}
function pixelpart_particle_type_get_mesh_renderer_mesh_resource_id(runtimePtr, particleTypeId) {
	const runtimeCStr = Module.stringToNewUTF8(runtimePtr);
	const result = Module.UTF8ToString(Module._pixelpart_particle_type_get_mesh_renderer_mesh_resource_id(runtimeCStr, particleTypeId));
	Module._free(runtimeCStr);

	return result;
}
function pixelpart_particle_type_get_count(runtimePtr, particleTypeId) {
	const runtimeCStr = Module.stringToNewUTF8(runtimePtr);
	const result = Module.UTF8ToString(Module._pixelpart_particle_type_get_count(runtimeCStr, particleTypeId));
	Module._free(runtimeCStr);

	return result;
}
function pixelpart_particle_type_get_lifespan(runtimePtr, particleTypeId) {
	const runtimeCStr = Module.stringToNewUTF8(runtimePtr);
	const result = Module.UTF8ToString(Module._pixelpart_particle_type_get_lifespan(runtimeCStr, particleTypeId));
	Module._free(runtimeCStr);

	return result;
}
function pixelpart_particle_type_get_initial_size(runtimePtr, particleTypeId) {
	const runtimeCStr = Module.stringToNewUTF8(runtimePtr);
	const result = Module.UTF8ToString(Module._pixelpart_particle_type_get_initial_size(runtimeCStr, particleTypeId));
	Module._free(runtimeCStr);

	return result;
}
function pixelpart_particle_type_get_initial_rotation(runtimePtr, particleTypeId) {
	const runtimeCStr = Module.stringToNewUTF8(runtimePtr);
	const result = Module.UTF8ToString(Module._pixelpart_particle_type_get_initial_rotation(runtimeCStr, particleTypeId));
	Module._free(runtimeCStr);

	return result;
}
function pixelpart_particle_type_get_initial_velocity(runtimePtr, particleTypeId) {
	const runtimeCStr = Module.stringToNewUTF8(runtimePtr);
	const result = Module.UTF8ToString(Module._pixelpart_particle_type_get_initial_velocity(runtimeCStr, particleTypeId));
	Module._free(runtimeCStr);

	return result;
}
function pixelpart_particle_type_get_inherited_velocity(runtimePtr, particleTypeId) {
	const runtimeCStr = Module.stringToNewUTF8(runtimePtr);
	const result = Module.UTF8ToString(Module._pixelpart_particle_type_get_inherited_velocity(runtimeCStr, particleTypeId));
	Module._free(runtimeCStr);

	return result;
}
function pixelpart_particle_type_get_initial_opacity(runtimePtr, particleTypeId) {
	const runtimeCStr = Module.stringToNewUTF8(runtimePtr);
	const result = Module.UTF8ToString(Module._pixelpart_particle_type_get_initial_opacity(runtimeCStr, particleTypeId));
	Module._free(runtimeCStr);

	return result;
}
function pixelpart_particle_type_get_motion_path(runtimePtr, particleTypeId) {
	const runtimeCStr = Module.stringToNewUTF8(runtimePtr);
	const result = Module.UTF8ToString(Module._pixelpart_particle_type_get_motion_path(runtimeCStr, particleTypeId));
	Module._free(runtimeCStr);

	return result;
}
function pixelpart_particle_type_get_size(runtimePtr, particleTypeId) {
	const runtimeCStr = Module.stringToNewUTF8(runtimePtr);
	const result = Module.UTF8ToString(Module._pixelpart_particle_type_get_size(runtimeCStr, particleTypeId));
	Module._free(runtimeCStr);

	return result;
}
function pixelpart_particle_type_get_stretch(runtimePtr, particleTypeId) {
	const runtimeCStr = Module.stringToNewUTF8(runtimePtr);
	const result = Module.UTF8ToString(Module._pixelpart_particle_type_get_stretch(runtimeCStr, particleTypeId));
	Module._free(runtimeCStr);

	return result;
}
function pixelpart_particle_type_get_physical_size(runtimePtr, particleTypeId) {
	const runtimeCStr = Module.stringToNewUTF8(runtimePtr);
	const result = Module.UTF8ToString(Module._pixelpart_particle_type_get_physical_size(runtimeCStr, particleTypeId));
	Module._free(runtimeCStr);

	return result;
}
function pixelpart_particle_type_get_rotation(runtimePtr, particleTypeId) {
	const runtimeCStr = Module.stringToNewUTF8(runtimePtr);
	const result = Module.UTF8ToString(Module._pixelpart_particle_type_get_rotation(runtimeCStr, particleTypeId));
	Module._free(runtimeCStr);

	return result;
}
function pixelpart_particle_type_get_rotation_by_speed(runtimePtr, particleTypeId) {
	const runtimeCStr = Module.stringToNewUTF8(runtimePtr);
	const result = Module.UTF8ToString(Module._pixelpart_particle_type_get_rotation_by_speed(runtimeCStr, particleTypeId));
	Module._free(runtimeCStr);

	return result;
}
function pixelpart_particle_type_get_acceleration(runtimePtr, particleTypeId) {
	const runtimeCStr = Module.stringToNewUTF8(runtimePtr);
	const result = Module.UTF8ToString(Module._pixelpart_particle_type_get_acceleration(runtimeCStr, particleTypeId));
	Module._free(runtimeCStr);

	return result;
}
function pixelpart_particle_type_get_radial_acceleration(runtimePtr, particleTypeId) {
	const runtimeCStr = Module.stringToNewUTF8(runtimePtr);
	const result = Module.UTF8ToString(Module._pixelpart_particle_type_get_radial_acceleration(runtimeCStr, particleTypeId));
	Module._free(runtimeCStr);

	return result;
}
function pixelpart_particle_type_get_weight(runtimePtr, particleTypeId) {
	const runtimeCStr = Module.stringToNewUTF8(runtimePtr);
	const result = Module.UTF8ToString(Module._pixelpart_particle_type_get_weight(runtimeCStr, particleTypeId));
	Module._free(runtimeCStr);

	return result;
}
function pixelpart_particle_type_get_bounce(runtimePtr, particleTypeId) {
	const runtimeCStr = Module.stringToNewUTF8(runtimePtr);
	const result = Module.UTF8ToString(Module._pixelpart_particle_type_get_bounce(runtimeCStr, particleTypeId));
	Module._free(runtimeCStr);

	return result;
}
function pixelpart_particle_type_get_friction(runtimePtr, particleTypeId) {
	const runtimeCStr = Module.stringToNewUTF8(runtimePtr);
	const result = Module.UTF8ToString(Module._pixelpart_particle_type_get_friction(runtimeCStr, particleTypeId));
	Module._free(runtimeCStr);

	return result;
}
function pixelpart_particle_type_get_color(runtimePtr, particleTypeId) {
	const runtimeCStr = Module.stringToNewUTF8(runtimePtr);
	const result = Module.UTF8ToString(Module._pixelpart_particle_type_get_color(runtimeCStr, particleTypeId));
	Module._free(runtimeCStr);

	return result;
}
function pixelpart_particle_type_get_opacity(runtimePtr, particleTypeId) {
	const runtimeCStr = Module.stringToNewUTF8(runtimePtr);
	const result = Module.UTF8ToString(Module._pixelpart_particle_type_get_opacity(runtimeCStr, particleTypeId));
	Module._free(runtimeCStr);

	return result;
}
function pixelpart_particle_type_get_lifespan_variance(runtimePtr, particleTypeId) {
	const runtimeCStr = Module.stringToNewUTF8(runtimePtr);
	const result = Module.UTF8ToString(Module._pixelpart_particle_type_get_lifespan_variance(runtimeCStr, particleTypeId));
	Module._free(runtimeCStr);

	return result;
}
function pixelpart_particle_type_get_size_variance(runtimePtr, particleTypeId) {
	const runtimeCStr = Module.stringToNewUTF8(runtimePtr);
	const result = Module.UTF8ToString(Module._pixelpart_particle_type_get_size_variance(runtimeCStr, particleTypeId));
	Module._free(runtimeCStr);

	return result;
}
function pixelpart_particle_type_get_rotation_variance(runtimePtr, particleTypeId) {
	const runtimeCStr = Module.stringToNewUTF8(runtimePtr);
	const result = Module.UTF8ToString(Module._pixelpart_particle_type_get_rotation_variance(runtimeCStr, particleTypeId));
	Module._free(runtimeCStr);

	return result;
}
function pixelpart_particle_type_get_angular_velocity_variance(runtimePtr, particleTypeId) {
	const runtimeCStr = Module.stringToNewUTF8(runtimePtr);
	const result = Module.UTF8ToString(Module._pixelpart_particle_type_get_angular_velocity_variance(runtimeCStr, particleTypeId));
	Module._free(runtimeCStr);

	return result;
}
function pixelpart_particle_type_get_velocity_variance(runtimePtr, particleTypeId) {
	const runtimeCStr = Module.stringToNewUTF8(runtimePtr);
	const result = Module.UTF8ToString(Module._pixelpart_particle_type_get_velocity_variance(runtimeCStr, particleTypeId));
	Module._free(runtimeCStr);

	return result;
}
function pixelpart_particle_type_get_color_variance(runtimePtr, particleTypeId) {
	const runtimeCStr = Module.stringToNewUTF8(runtimePtr);
	const result = Module.UTF8ToString(Module._pixelpart_particle_type_get_color_variance(runtimeCStr, particleTypeId));
	Module._free(runtimeCStr);

	return result;
}
function pixelpart_particle_type_get_opacity_variance(runtimePtr, particleTypeId) {
	const runtimeCStr = Module.stringToNewUTF8(runtimePtr);
	const result = Module.UTF8ToString(Module._pixelpart_particle_type_get_opacity_variance(runtimeCStr, particleTypeId));
	Module._free(runtimeCStr);

	return result;
}

// Static property
function pixelpart_static_property_bool_value(propertyPtr) {
	const propertyCStr = Module.stringToNewUTF8(propertyPtr);
	const result = Module._pixelpart_static_property_bool_value(propertyCStr);
	Module._free(propertyCStr);

	return result;
}
function pixelpart_static_property_bool_set_base_value(propertyPtr, value) {
	const propertyCStr = Module.stringToNewUTF8(propertyPtr);
	const result = Module._pixelpart_static_property_bool_set_base_value(propertyCStr, value);
	Module._free(propertyCStr);

	return result;
}
function pixelpart_static_property_bool_get_base_value(propertyPtr) {
	const propertyCStr = Module.stringToNewUTF8(propertyPtr);
	const result = Module._pixelpart_static_property_bool_get_base_value(propertyCStr);
	Module._free(propertyCStr);

	return result;
}
function pixelpart_static_property_int_value(propertyPtr) {
	const propertyCStr = Module.stringToNewUTF8(propertyPtr);
	const result = Module._pixelpart_static_property_int_value(propertyCStr);
	Module._free(propertyCStr);

	return result;
}
function pixelpart_static_property_int_set_base_value(propertyPtr, value) {
	const propertyCStr = Module.stringToNewUTF8(propertyPtr);
	const result = Module._pixelpart_static_property_int_set_base_value(propertyCStr, value);
	Module._free(propertyCStr);

	return result;
}
function pixelpart_static_property_int_get_base_value(propertyPtr) {
	const propertyCStr = Module.stringToNewUTF8(propertyPtr);
	const result = Module._pixelpart_static_property_int_get_base_value(propertyCStr);
	Module._free(propertyCStr);

	return result;
}
function pixelpart_static_property_float_value(propertyPtr) {
	const propertyCStr = Module.stringToNewUTF8(propertyPtr);
	const result = Module._pixelpart_static_property_float_value(propertyCStr);
	Module._free(propertyCStr);

	return result;
}
function pixelpart_static_property_float_set_base_value(propertyPtr, value) {
	const propertyCStr = Module.stringToNewUTF8(propertyPtr);
	const result = Module._pixelpart_static_property_float_set_base_value(propertyCStr, value);
	Module._free(propertyCStr);

	return result;
}
function pixelpart_static_property_float_get_base_value(propertyPtr) {
	const propertyCStr = Module.stringToNewUTF8(propertyPtr);
	const result = Module._pixelpart_static_property_float_get_base_value(propertyCStr);
	Module._free(propertyCStr);

	return result;
}
function pixelpart_static_property_float2_value(propertyPtr, valueBufferPtr) {
	const propertyCStr = Module.stringToNewUTF8(propertyPtr);
	const nativeValueBufferPtr = Module._malloc(valueBufferPtr.byteLength);
	const result = Module._pixelpart_static_property_float2_value(propertyCStr, nativeValueBufferPtr);
	pixelpartjs_copy_from_native_buffer(valueBufferPtr, nativeValueBufferPtr);
	Module._free(nativeValueBufferPtr);
	Module._free(propertyCStr);

	return result;
}
function pixelpart_static_property_float2_set_base_value(propertyPtr, valueBufferPtr) {
	const propertyCStr = Module.stringToNewUTF8(propertyPtr);
	const nativeValueBufferPtr = pixelpartjs_copy_to_native_buffer(valueBufferPtr);
	const result = Module._pixelpart_static_property_float2_set_base_value(propertyCStr, nativeValueBufferPtr);
	Module._free(nativeValueBufferPtr);
	Module._free(propertyCStr);

	return result;
}
function pixelpart_static_property_float2_get_base_value(propertyPtr, valueBufferPtr) {
	const propertyCStr = Module.stringToNewUTF8(propertyPtr);
	const nativeValueBufferPtr = Module._malloc(valueBufferPtr.byteLength);
	const result = Module._pixelpart_static_property_float2_get_base_value(propertyCStr, nativeValueBufferPtr);
	pixelpartjs_copy_from_native_buffer(valueBufferPtr, nativeValueBufferPtr);
	Module._free(nativeValueBufferPtr);
	Module._free(propertyCStr);

	return result;
}
function pixelpart_static_property_float3_value(propertyPtr, valueBufferPtr) {
	const propertyCStr = Module.stringToNewUTF8(propertyPtr);
	const nativeValueBufferPtr = Module._malloc(valueBufferPtr.byteLength);
	const result = Module._pixelpart_static_property_float3_value(propertyCStr, nativeValueBufferPtr);
	pixelpartjs_copy_from_native_buffer(valueBufferPtr, nativeValueBufferPtr);
	Module._free(nativeValueBufferPtr);
	Module._free(propertyCStr);

	return result;
}
function pixelpart_static_property_float3_set_base_value(propertyPtr, valueBufferPtr) {
	const propertyCStr = Module.stringToNewUTF8(propertyPtr);
	const nativeValueBufferPtr = pixelpartjs_copy_to_native_buffer(valueBufferPtr);
	const result = Module._pixelpart_static_property_float3_set_base_value(propertyCStr, nativeValueBufferPtr);
	Module._free(nativeValueBufferPtr);
	Module._free(propertyCStr);

	return result;
}
function pixelpart_static_property_float3_get_base_value(propertyPtr, valueBufferPtr) {
	const propertyCStr = Module.stringToNewUTF8(propertyPtr);
	const nativeValueBufferPtr = Module._malloc(valueBufferPtr.byteLength);
	const result = Module._pixelpart_static_property_float3_get_base_value(propertyCStr, nativeValueBufferPtr);
	pixelpartjs_copy_from_native_buffer(valueBufferPtr, nativeValueBufferPtr);
	Module._free(nativeValueBufferPtr);
	Module._free(propertyCStr);

	return result;
}
function pixelpart_static_property_float4_value(propertyPtr, valueBufferPtr) {
	const propertyCStr = Module.stringToNewUTF8(propertyPtr);
	const nativeValueBufferPtr = Module._malloc(valueBufferPtr.byteLength);
	const result = Module._pixelpart_static_property_float4_value(propertyCStr, nativeValueBufferPtr);
	pixelpartjs_copy_from_native_buffer(valueBufferPtr, nativeValueBufferPtr);
	Module._free(nativeValueBufferPtr);
	Module._free(propertyCStr);

	return result;
}
function pixelpart_static_property_float4_set_base_value(propertyPtr, valueBufferPtr) {
	const propertyCStr = Module.stringToNewUTF8(propertyPtr);
	const nativeValueBufferPtr = pixelpartjs_copy_to_native_buffer(valueBufferPtr);
	const result = Module._pixelpart_static_property_float4_set_base_value(propertyCStr, nativeValueBufferPtr);
	Module._free(nativeValueBufferPtr);
	Module._free(propertyCStr);

	return result;
}
function pixelpart_static_property_float4_get_base_value(propertyPtr, valueBufferPtr) {
	const propertyCStr = Module.stringToNewUTF8(propertyPtr);
	const nativeValueBufferPtr = Module._malloc(valueBufferPtr.byteLength);
	const result = Module._pixelpart_static_property_float4_get_base_value(propertyCStr, nativeValueBufferPtr);
	pixelpartjs_copy_from_native_buffer(valueBufferPtr, nativeValueBufferPtr);
	Module._free(nativeValueBufferPtr);
	Module._free(propertyCStr);

	return result;
}

// Animated property
function pixelpart_animated_property_float_at(propertyPtr, position) {
	const propertyCStr = Module.stringToNewUTF8(propertyPtr);
	const result = Module._pixelpart_animated_property_float_at(propertyCStr, position);
	Module._free(propertyCStr);

	return result;
}
function pixelpart_animated_property_float_add_keyframe(propertyPtr, position, value) {
	const propertyCStr = Module.stringToNewUTF8(propertyPtr);
	const result = Module._pixelpart_animated_property_float_add_keyframe(propertyCStr, position, value);
	Module._free(propertyCStr);

	return result;
}
function pixelpart_animated_property_float_remove_keyframe(propertyPtr, index) {
	const propertyCStr = Module.stringToNewUTF8(propertyPtr);
	const result = Module._pixelpart_animated_property_float_remove_keyframe(propertyCStr, index);
	Module._free(propertyCStr);

	return result;
}
function pixelpart_animated_property_float_set_keyframe_value(propertyPtr, index, value) {
	const propertyCStr = Module.stringToNewUTF8(propertyPtr);
	const result = Module._pixelpart_animated_property_float_set_keyframe_value(propertyCStr, index, value);
	Module._free(propertyCStr);

	return result;
}
function pixelpart_animated_property_float_set_keyframe_position(propertyPtr, index, position) {
	const propertyCStr = Module.stringToNewUTF8(propertyPtr);
	const result = Module._pixelpart_animated_property_float_set_keyframe_position(propertyCStr, index, position);
	Module._free(propertyCStr);

	return result;
}
function pixelpart_animated_property_float_clear_keyframes(propertyPtr) {
	const propertyCStr = Module.stringToNewUTF8(propertyPtr);
	const result = Module._pixelpart_animated_property_float_clear_keyframes(propertyCStr);
	Module._free(propertyCStr);

	return result;
}
function pixelpart_animated_property_float_keyframe_count(propertyPtr) {
	const propertyCStr = Module.stringToNewUTF8(propertyPtr);
	const result = Module._pixelpart_animated_property_float_keyframe_count(propertyCStr);
	Module._free(propertyCStr);

	return result;
}
function pixelpart_animated_property_float_keyframe_value(propertyPtr, index) {
	const propertyCStr = Module.stringToNewUTF8(propertyPtr);
	const result = Module._pixelpart_animated_property_float_keyframe_value(propertyCStr, index);
	Module._free(propertyCStr);

	return result;
}
function pixelpart_animated_property_float_keyframe_index(propertyPtr, position, epsilon) {
	const propertyCStr = Module.stringToNewUTF8(propertyPtr);
	const result = Module._pixelpart_animated_property_float_keyframe_index(propertyCStr, position, epsilon);
	Module._free(propertyCStr);

	return result;
}
function pixelpart_animated_property_float_set_keyframe_interpolation(propertyPtr, method) {
	const propertyCStr = Module.stringToNewUTF8(propertyPtr);
	const result = Module._pixelpart_animated_property_float_set_keyframe_interpolation(propertyCStr, method);
	Module._free(propertyCStr);

	return result;
}
function pixelpart_animated_property_float_get_keyframe_interpolation(propertyPtr) {
	const propertyCStr = Module.stringToNewUTF8(propertyPtr);
	const result = Module._pixelpart_animated_property_float_get_keyframe_interpolation(propertyCStr);
	Module._free(propertyCStr);

	return result;
}
function pixelpart_animated_property_float2_at(propertyPtr, position, valueBufferPtr) {
	const propertyCStr = Module.stringToNewUTF8(propertyPtr);
	const nativeValueBufferPtr = Module._malloc(valueBufferPtr.byteLength);
	const result = Module._pixelpart_animated_property_float2_at(propertyCStr, position, nativeValueBufferPtr);
	pixelpartjs_copy_from_native_buffer(valueBufferPtr, nativeValueBufferPtr);
	Module._free(nativeValueBufferPtr);
	Module._free(propertyCStr);

	return result;
}
function pixelpart_animated_property_float2_add_keyframe(propertyPtr, position, valueBufferPtr) {
	const propertyCStr = Module.stringToNewUTF8(propertyPtr);
	const nativeValueBufferPtr = pixelpartjs_copy_to_native_buffer(valueBufferPtr);
	const result = Module._pixelpart_animated_property_float2_add_keyframe(propertyCStr, position, nativeValueBufferPtr);
	Module._free(nativeValueBufferPtr);
	Module._free(propertyCStr);

	return result;
}
function pixelpart_animated_property_float2_remove_keyframe(propertyPtr, index) {
	const propertyCStr = Module.stringToNewUTF8(propertyPtr);
	const result = Module._pixelpart_animated_property_float2_remove_keyframe(propertyCStr, index);
	Module._free(propertyCStr);

	return result;
}
function pixelpart_animated_property_float2_set_keyframe_value(propertyPtr, index, valueBufferPtr) {
	const propertyCStr = Module.stringToNewUTF8(propertyPtr);
	const nativeValueBufferPtr = pixelpartjs_copy_to_native_buffer(valueBufferPtr);
	const result = Module._pixelpart_animated_property_float2_set_keyframe_value(propertyCStr, index, nativeValueBufferPtr);
	Module._free(nativeValueBufferPtr);
	Module._free(propertyCStr);

	return result;
}
function pixelpart_animated_property_float2_set_keyframe_position(propertyPtr, index, position) {
	const propertyCStr = Module.stringToNewUTF8(propertyPtr);
	const result = Module._pixelpart_animated_property_float2_set_keyframe_position(propertyCStr, index, position);
	Module._free(propertyCStr);

	return result;
}
function pixelpart_animated_property_float2_clear_keyframes(propertyPtr) {
	const propertyCStr = Module.stringToNewUTF8(propertyPtr);
	const result = Module._pixelpart_animated_property_float2_clear_keyframes(propertyCStr);
	Module._free(propertyCStr);

	return result;
}
function pixelpart_animated_property_float2_keyframe_count(propertyPtr) {
	const propertyCStr = Module.stringToNewUTF8(propertyPtr);
	const result = Module._pixelpart_animated_property_float2_keyframe_count(propertyCStr);
	Module._free(propertyCStr);

	return result;
}
function pixelpart_animated_property_float2_keyframe_value(propertyPtr, index, valueBufferPtr) {
	const propertyCStr = Module.stringToNewUTF8(propertyPtr);
	const nativeValueBufferPtr = Module._malloc(valueBufferPtr.byteLength);
	const result = Module._pixelpart_animated_property_float2_keyframe_value(propertyCStr, index, nativeValueBufferPtr);
	pixelpartjs_copy_from_native_buffer(valueBufferPtr, nativeValueBufferPtr);
	Module._free(nativeValueBufferPtr);
	Module._free(propertyCStr);

	return result;
}
function pixelpart_animated_property_float2_keyframe_index(propertyPtr, position, epsilon) {
	const propertyCStr = Module.stringToNewUTF8(propertyPtr);
	const result = Module._pixelpart_animated_property_float2_keyframe_index(propertyCStr, position, epsilon);
	Module._free(propertyCStr);

	return result;
}
function pixelpart_animated_property_float2_set_keyframe_interpolation(propertyPtr, method) {
	const propertyCStr = Module.stringToNewUTF8(propertyPtr);
	const result = Module._pixelpart_animated_property_float2_set_keyframe_interpolation(propertyCStr, method);
	Module._free(propertyCStr);

	return result;
}
function pixelpart_animated_property_float2_get_keyframe_interpolation(propertyPtr) {
	const propertyCStr = Module.stringToNewUTF8(propertyPtr);
	const result = Module._pixelpart_animated_property_float2_get_keyframe_interpolation(propertyCStr);
	Module._free(propertyCStr);

	return result;
}
function pixelpart_animated_property_float3_at(propertyPtr, position, valueBufferPtr) {
	const propertyCStr = Module.stringToNewUTF8(propertyPtr);
	const nativeValueBufferPtr = Module._malloc(valueBufferPtr.byteLength);
	const result = Module._pixelpart_animated_property_float3_at(propertyCStr, position, nativeValueBufferPtr);
	pixelpartjs_copy_from_native_buffer(valueBufferPtr, nativeValueBufferPtr);
	Module._free(nativeValueBufferPtr);
	Module._free(propertyCStr);

	return result;
}
function pixelpart_animated_property_float3_add_keyframe(propertyPtr, position, valueBufferPtr) {
	const propertyCStr = Module.stringToNewUTF8(propertyPtr);
	const nativeValueBufferPtr = pixelpartjs_copy_to_native_buffer(valueBufferPtr);
	const result = Module._pixelpart_animated_property_float3_add_keyframe(propertyCStr, position, nativeValueBufferPtr);
	Module._free(nativeValueBufferPtr);
	Module._free(propertyCStr);

	return result;
}
function pixelpart_animated_property_float3_remove_keyframe(propertyPtr, index) {
	const propertyCStr = Module.stringToNewUTF8(propertyPtr);
	const result = Module._pixelpart_animated_property_float3_remove_keyframe(propertyCStr, index);
	Module._free(propertyCStr);

	return result;
}
function pixelpart_animated_property_float3_set_keyframe_value(propertyPtr, index, valueBufferPtr) {
	const propertyCStr = Module.stringToNewUTF8(propertyPtr);
	const nativeValueBufferPtr = pixelpartjs_copy_to_native_buffer(valueBufferPtr);
	const result = Module._pixelpart_animated_property_float3_set_keyframe_value(propertyCStr, index, nativeValueBufferPtr);
	Module._free(nativeValueBufferPtr);
	Module._free(propertyCStr);

	return result;
}
function pixelpart_animated_property_float3_set_keyframe_position(propertyPtr, index, position) {
	const propertyCStr = Module.stringToNewUTF8(propertyPtr);
	const result = Module._pixelpart_animated_property_float3_set_keyframe_position(propertyCStr, index, position);
	Module._free(propertyCStr);

	return result;
}
function pixelpart_animated_property_float3_clear_keyframes(propertyPtr) {
	const propertyCStr = Module.stringToNewUTF8(propertyPtr);
	const result = Module._pixelpart_animated_property_float3_clear_keyframes(propertyCStr);
	Module._free(propertyCStr);

	return result;
}
function pixelpart_animated_property_float3_keyframe_count(propertyPtr) {
	const propertyCStr = Module.stringToNewUTF8(propertyPtr);
	const result = Module._pixelpart_animated_property_float3_keyframe_count(propertyCStr);
	Module._free(propertyCStr);

	return result;
}
function pixelpart_animated_property_float3_keyframe_value(propertyPtr, index, valueBufferPtr) {
	const propertyCStr = Module.stringToNewUTF8(propertyPtr);
	const nativeValueBufferPtr = Module._malloc(valueBufferPtr.byteLength);
	const result = Module._pixelpart_animated_property_float3_keyframe_value(propertyCStr, index, nativeValueBufferPtr);
	Module._free(nativeValueBufferPtr);
	Module._free(propertyCStr);

	return result;
}
function pixelpart_animated_property_float3_keyframe_index(propertyPtr, position, epsilon) {
	const propertyCStr = Module.stringToNewUTF8(propertyPtr);
	const result = Module._pixelpart_animated_property_float3_keyframe_index(propertyCStr, position, epsilon);
	Module._free(propertyCStr);

	return result;
}
function pixelpart_animated_property_float3_set_keyframe_interpolation(propertyPtr, method) {
	const propertyCStr = Module.stringToNewUTF8(propertyPtr);
	const result = Module._pixelpart_animated_property_float3_set_keyframe_interpolation(propertyCStr, method);
	Module._free(propertyCStr);

	return result;
}
function pixelpart_animated_property_float3_get_keyframe_interpolation(propertyPtr) {
	const propertyCStr = Module.stringToNewUTF8(propertyPtr);
	const result = Module._pixelpart_animated_property_float3_get_keyframe_interpolation(propertyCStr);
	Module._free(propertyCStr);

	return result;
}
function pixelpart_animated_property_float4_at(propertyPtr, position, valueBufferPtr) {
	const propertyCStr = Module.stringToNewUTF8(propertyPtr);
	const nativeValueBufferPtr = Module._malloc(valueBufferPtr.byteLength);
	const result = Module._pixelpart_animated_property_float4_at(propertyCStr, position, nativeValueBufferPtr);
	pixelpartjs_copy_from_native_buffer(valueBufferPtr, nativeValueBufferPtr);
	Module._free(nativeValueBufferPtr);
	Module._free(propertyCStr);

	return result;
}
function pixelpart_animated_property_float4_add_keyframe(propertyPtr, position, valueBufferPtr) {
	const propertyCStr = Module.stringToNewUTF8(propertyPtr);
	const nativeValueBufferPtr = pixelpartjs_copy_to_native_buffer(valueBufferPtr);
	const result = Module._pixelpart_animated_property_float4_add_keyframe(propertyCStr, position, nativeValueBufferPtr);
	Module._free(nativeValueBufferPtr);
	Module._free(propertyCStr);

	return result;
}
function pixelpart_animated_property_float4_remove_keyframe(propertyPtr, index) {
	const propertyCStr = Module.stringToNewUTF8(propertyPtr);
	const result = Module._pixelpart_animated_property_float4_remove_keyframe(propertyCStr, index);
	Module._free(propertyCStr);

	return result;
}
function pixelpart_animated_property_float4_set_keyframe_value(propertyPtr, index, valueBufferPtr) {
	const propertyCStr = Module.stringToNewUTF8(propertyPtr);
	const nativeValueBufferPtr = pixelpartjs_copy_to_native_buffer(valueBufferPtr);
	const result = Module._pixelpart_animated_property_float4_set_keyframe_value(propertyCStr, index, nativeValueBufferPtr);
	Module._free(nativeValueBufferPtr);
	Module._free(propertyCStr);

	return result;
}
function pixelpart_animated_property_float4_set_keyframe_position(propertyPtr, index, position) {
	const propertyCStr = Module.stringToNewUTF8(propertyPtr);
	const result = Module._pixelpart_animated_property_float4_set_keyframe_position(propertyCStr, index, position);
	Module._free(propertyCStr);

	return result;
}
function pixelpart_animated_property_float4_clear_keyframes(propertyPtr) {
	const propertyCStr = Module.stringToNewUTF8(propertyPtr);
	const result = Module._pixelpart_animated_property_float4_clear_keyframes(propertyCStr);
	Module._free(propertyCStr);

	return result;
}
function pixelpart_animated_property_float4_keyframe_count(propertyPtr) {
	const propertyCStr = Module.stringToNewUTF8(propertyPtr);
	const result = Module._pixelpart_animated_property_float4_keyframe_count(propertyCStr);
	Module._free(propertyCStr);

	return result;
}
function pixelpart_animated_property_float4_keyframe_value(propertyPtr, index, valueBufferPtr) {
	const propertyCStr = Module.stringToNewUTF8(propertyPtr);
	const nativeValueBufferPtr = Module._malloc(valueBufferPtr.byteLength);
	const result = Module._pixelpart_animated_property_float4_keyframe_value(propertyCStr, index, nativeValueBufferPtr);
	pixelpartjs_copy_from_native_buffer(valueBufferPtr, nativeValueBufferPtr);
	Module._free(nativeValueBufferPtr);
	Module._free(propertyCStr);

	return result;
}
function pixelpart_animated_property_float4_keyframe_index(propertyPtr, position, epsilon) {
	const propertyCStr = Module.stringToNewUTF8(propertyPtr);
	const result = Module._pixelpart_animated_property_float4_keyframe_index(propertyCStr, position, epsilon);
	Module._free(propertyCStr);

	return result;
}
function pixelpart_animated_property_float4_set_keyframe_interpolation(propertyPtr, method) {
	const propertyCStr = Module.stringToNewUTF8(propertyPtr);
	const result = Module._pixelpart_animated_property_float4_set_keyframe_interpolation(propertyCStr, method);
	Module._free(propertyCStr);

	return result;
}
function pixelpart_animated_property_float4_get_keyframe_interpolation(propertyPtr) {
	const propertyCStr = Module.stringToNewUTF8(propertyPtr);
	const result = Module._pixelpart_animated_property_float4_get_keyframe_interpolation(propertyCStr);
	Module._free(propertyCStr);

	return result;
}
