#import "PixelpartiOS.h"

#include "Common.cpp"
#include "Buffer.cpp"
#include "BuiltInMaterial.cpp"
#include "Init.cpp"
#include "Error.cpp"
#include "EffectRuntime.cpp"
#include "Rendering.cpp"
#include "Resources.cpp"
#include "EffectInput.cpp"
#include "EffectTrigger.cpp"
#include "EffectEvent.cpp"
#include "Node.cpp"
#include "ParticleEmitter.cpp"
#include "ForceField.cpp"
#include "Collider.cpp"
#include "LightSource.cpp"
#include "ParticleType.cpp"
#include "StaticPropertyBool.cpp"
#include "StaticPropertyFloat.cpp"
#include "StaticPropertyFloat2.cpp"
#include "StaticPropertyFloat3.cpp"
#include "StaticPropertyFloat4.cpp"
#include "StaticPropertyInt.cpp"
#include "AnimatedPropertyFloat.cpp"
#include "AnimatedPropertyFloat2.cpp"
#include "AnimatedPropertyFloat3.cpp"
#include "AnimatedPropertyFloat4.cpp"

@implementation PixelpartiOS

- (void) Init {

}

// Init
- (double)pixelpart_init {
	return pixelpart_init();
}
- (double)pixelpart_shutdown {
	return pixelpart_shutdown();
}

// Error
- (NSString*)pixelpart_last_error {
	return [NSString stringWithUTF8String:pixelpart_last_error()];
}

// Effect runtime
- (NSString*)pixelpart_load_effect_resource:(char*)data size:(double)size {
	return [NSString stringWithUTF8String:pixelpart_load_effect_resource(data, size)];
}
- (double)pixelpart_delete_effect_resource:(char*)resourcePtr {
	return pixelpart_delete_effect_resource(resourcePtr);
}
- (NSString*)pixelpart_create_effect:(char*)resourcePtr {
	return [NSString stringWithUTF8String:pixelpart_create_effect(resourcePtr)];
}
- (double)pixelpart_delete_effect:(char*)runtimePtr {
	return pixelpart_delete_effect(runtimePtr);
}
- (double)pixelpart_set_effect_scale:(char*)runtimePtr scaleX:(double)scaleX scaleY:(double)scaleY {
	return pixelpart_set_effect_scale(runtimePtr, scaleX, scaleY);
}
- (double)pixelpart_set_effect_transform:(char*)runtimePtr x:(double)x y:(double)y {
	return pixelpart_set_effect_transform(runtimePtr, x, y);
}
- (double)pixelpart_advance_effect:(char*)runtimePtr paramBufferPtr:(char*)paramBufferPtr {
	return pixelpart_advance_effect(runtimePtr, paramBufferPtr);
}
- (double)pixelpart_restart_effect:(char*)runtimePtr clear:(double)clear {
	return pixelpart_restart_effect(runtimePtr, clear);
}
- (double)pixelpart_reseed_effect:(char*)runtimePtr seed:(double)seed {
	return pixelpart_reseed_effect(runtimePtr, seed);
}
- (double)pixelpart_get_effect_time:(char*)runtimePtr {
	return pixelpart_get_effect_time(runtimePtr);
}
- (double)pixelpart_is_effect_finished:(char*)runtimePtr {
	return pixelpart_is_effect_finished(runtimePtr);
}
- (double)pixelpart_is_effect_3d:(char*)runtimePtr {
	return pixelpart_is_effect_3d(runtimePtr);
}
- (double)pixelpart_get_effect_node_count:(char*)runtimePtr {
	return pixelpart_get_effect_node_count(runtimePtr);
}
- (double)pixelpart_get_effect_particle_type_count:(char*)runtimePtr {
	return pixelpart_get_effect_particle_type_count(runtimePtr);
}
- (double)pixelpart_get_effect_particle_runtime_instance_count:(char*)runtimePtr {
	return pixelpart_get_effect_particle_runtime_instance_count(runtimePtr);
}
- (double)pixelpart_get_effect_particle_runtime_instances:(char*)runtimePtr instanceBufferPtr:(char*)instanceBufferPtr {
	return pixelpart_get_effect_particle_runtime_instances(runtimePtr, instanceBufferPtr);
}
- (double)pixelpart_get_effect_particle_count:(char*)runtimePtr particleEmitterId:(double)particleEmitterId particleTypeId:(double)particleTypeId {
	return pixelpart_get_effect_particle_count(runtimePtr, particleEmitterId, particleTypeId);
}
- (double)pixelpart_spawn_particles:(char*)runtimePtr particleEmitterId:(double)particleEmitterId particleTypeId:(double)particleTypeId count:(double)count {
	return pixelpart_spawn_particles(runtimePtr, particleEmitterId, particleTypeId, count);
}

// Resources
- (double)pixelpart_get_image_resource_count:(char*)runtimePtr {
	return pixelpart_get_image_resource_count(runtimePtr);
}
- (NSString*)pixelpart_get_image_resource_id:(char*)runtimePtr index:(double)index {
	return [NSString stringWithUTF8String:pixelpart_get_image_resource_id(runtimePtr, index)];
}
- (double)pixelpart_get_image_resource_width:(char*)runtimePtr resourceId:(char*)resourceId {
	return pixelpart_get_image_resource_width(runtimePtr, resourceId);
}
- (double)pixelpart_get_image_resource_height:(char*)runtimePtr resourceId:(char*)resourceId {
	return pixelpart_get_image_resource_height(runtimePtr, resourceId);
}
- (double)pixelpart_get_image_resource_channels:(char*)runtimePtr resourceId:(char*)resourceId {
	return pixelpart_get_image_resource_channels(runtimePtr, resourceId);
}
- (double)pixelpart_get_image_resource_color_space:(char*)runtimePtr resourceId:(char*)resourceId {
	return pixelpart_get_image_resource_color_space(runtimePtr, resourceId);
}
- (double)pixelpart_get_image_resource_data_size:(char*)runtimePtr resourceId:(char*)resourceId {
	return pixelpart_get_image_resource_data_size(runtimePtr, resourceId);
}
- (double)pixelpart_get_image_resource_data:(char*)runtimePtr resourceId:(char*)resourceId imageDataBufferPtr:(char*)imageDataBufferPtr {
	return pixelpart_get_image_resource_data(runtimePtr, resourceId, imageDataBufferPtr);
}

// Rendering
- (double)pixelpart_get_sorted_particle_runtime_instances:(char*)runtimePtr indexBufferPtr:(char*)indexBufferPtr {
	return pixelpart_get_sorted_particle_runtime_instances(runtimePtr, indexBufferPtr);
}
- (double)pixelpart_construct_particle_geometry:(char*)runtimePtr particleEmitterId:(double)particleEmitterId particleTypeId:(double)particleTypeId bufferSizeBufferPtr:(char*)bufferSizeBufferPtr {
	return pixelpart_construct_particle_geometry(runtimePtr, particleEmitterId, particleTypeId, bufferSizeBufferPtr);
}
- (double)pixelpart_generate_particle_vertex_data:(char*)runtimePtr particleEmitterId:(double)particleEmitterId particleTypeId:(double)particleTypeId vertexBufferPtr:(char*)vertexBufferPtr {
	return pixelpart_generate_particle_vertex_data(runtimePtr, particleEmitterId, particleTypeId, vertexBufferPtr);
}

// Built-in material
- (double)pixelpart_get_builtin_material_parameter_count:(char*)materialName {
	return pixelpart_get_builtin_material_parameter_count(materialName);
}
- (double)pixelpart_get_builtin_material_parameters:(char*)materialName idBufferPtr:(char*)idBufferPtr nameBufferPtr:(char*)nameBufferPtr {
	return pixelpart_get_builtin_material_parameters(materialName, idBufferPtr, nameBufferPtr);
}

// Effect input
- (double)pixelpart_get_effect_input_count:(char*)runtimePtr {
	return pixelpart_get_effect_input_count(runtimePtr);
}
- (double)pixelpart_get_effect_inputs:(char*)runtimePtr idBufferPtr:(char*)idBufferPtr typeBufferPtr:(char*)typeBufferPtr nameBufferPtr:(char*)nameBufferPtr {
	return pixelpart_get_effect_inputs(runtimePtr, idBufferPtr, typeBufferPtr, nameBufferPtr);
}
- (double)pixelpart_set_effect_input_bool:(char*)runtimePtr inputId:(double)inputId value:(double)value {
	return pixelpart_set_effect_input_bool(runtimePtr, inputId, value);
}
- (double)pixelpart_set_effect_input_int:(char*)runtimePtr inputId:(double)inputId value:(double)value {
	return pixelpart_set_effect_input_int(runtimePtr, inputId, value);
}
- (double)pixelpart_set_effect_input_float:(char*)runtimePtr inputId:(double)inputId value:(double)value {
	return pixelpart_set_effect_input_float(runtimePtr, inputId, value);
}
- (double)pixelpart_set_effect_input_float2:(char*)runtimePtr inputId:(double)inputId valueBufferPtr:(char*)valueBufferPtr {
	return pixelpart_set_effect_input_float2(runtimePtr, inputId, valueBufferPtr);
}
- (double)pixelpart_set_effect_input_float3:(char*)runtimePtr inputId:(double)inputId valueBufferPtr:(char*)valueBufferPtr {
	return pixelpart_set_effect_input_float3(runtimePtr, inputId, valueBufferPtr);
}
- (double)pixelpart_set_effect_input_float4:(char*)runtimePtr inputId:(double)inputId valueBufferPtr:(char*)valueBufferPtr {
	return pixelpart_set_effect_input_float4(runtimePtr, inputId, valueBufferPtr);
}
- (double)pixelpart_get_effect_input_bool:(char*)runtimePtr inputId:(double)inputId {
	return pixelpart_get_effect_input_bool(runtimePtr, inputId);
}
- (double)pixelpart_get_effect_input_int:(char*)runtimePtr inputId:(double)inputId {
	return pixelpart_get_effect_input_int(runtimePtr, inputId);
}
- (double)pixelpart_get_effect_input_float:(char*)runtimePtr inputId:(double)inputId {
	return pixelpart_get_effect_input_float(runtimePtr, inputId);
}
- (double)pixelpart_get_effect_input_float2:(char*)runtimePtr inputId:(double)inputId valueBufferPtr:(char*)valueBufferPtr {
	return pixelpart_get_effect_input_float2(runtimePtr, inputId, valueBufferPtr);
}
- (double)pixelpart_get_effect_input_float3:(char*)runtimePtr inputId:(double)inputId valueBufferPtr:(char*)valueBufferPtr {
	return pixelpart_get_effect_input_float3(runtimePtr, inputId, valueBufferPtr);
}
- (double)pixelpart_get_effect_input_float4:(char*)runtimePtr inputId:(double)inputId valueBufferPtr:(char*)valueBufferPtr {
	return pixelpart_get_effect_input_float4(runtimePtr, inputId, valueBufferPtr);
}

// Effect trigger
- (double)pixelpart_get_effect_trigger_count:(char*)runtimePtr {
	return pixelpart_get_effect_trigger_count(runtimePtr);
}
- (double)pixelpart_get_effect_triggers:(char*)runtimePtr idBufferPtr:(char*)idBufferPtr nameBufferPtr:(char*)nameBufferPtr {
	return pixelpart_get_effect_triggers(runtimePtr, idBufferPtr, nameBufferPtr);
}
- (double)pixelpart_activate_effect_trigger:(char*)runtimePtr triggerId:(double)triggerId {
	return pixelpart_activate_effect_trigger(runtimePtr, triggerId);
}
- (double)pixelpart_is_effect_trigger_activated:(char*)runtimePtr triggerId:(double)triggerId {
	return pixelpart_is_effect_trigger_activated(runtimePtr, triggerId);
}

// Effect event
- (double)pixelpart_get_effect_event_count:(char*)runtimePtr {
	return pixelpart_get_effect_event_count(runtimePtr);
}
- (double)pixelpart_get_effect_events:(char*)runtimePtr idBufferPtr:(char*)idBufferPtr nameBufferPtr:(char*)nameBufferPtr {
	return pixelpart_get_effect_events(runtimePtr, idBufferPtr, nameBufferPtr);
}
- (double)pixelpart_get_invoked_effect_events:(char*)runtimePtr idBufferPtr:(char*)idBufferPtr {
	return pixelpart_get_invoked_effect_events(runtimePtr, idBufferPtr);
}

// Node
- (double)pixelpart_find_node:(char*)runtimePtr bufferPtr:(char*)bufferPtr {
	return pixelpart_find_node(runtimePtr, bufferPtr);
}
- (double)pixelpart_find_node_by_index:(char*)runtimePtr nodeIndex:(double)nodeIndex {
	return pixelpart_find_node_by_index(runtimePtr, nodeIndex);
}
- (double)pixelpart_node_exists:(char*)runtimePtr nodeId:(double)nodeId {
	return pixelpart_node_exists(runtimePtr, nodeId);
}
- (double)pixelpart_node_get_type:(char*)runtimePtr nodeId:(double)nodeId {
	return pixelpart_node_get_type(runtimePtr, nodeId);
}
- (NSString*)pixelpart_node_get_name:(char*)runtimePtr nodeId:(double)nodeId {
	return [NSString stringWithUTF8String:pixelpart_node_get_name(runtimePtr, nodeId)];
}
- (double)pixelpart_node_get_parent_id:(char*)runtimePtr nodeId:(double)nodeId {
	return pixelpart_node_get_parent_id(runtimePtr, nodeId);
}
- (double)pixelpart_node_set_start:(char*)runtimePtr nodeId:(double)nodeId value:(double)value {
	return pixelpart_node_set_start(runtimePtr, nodeId, value);
}
- (double)pixelpart_node_set_duration:(char*)runtimePtr nodeId:(double)nodeId value:(double)value {
	return pixelpart_node_set_duration(runtimePtr, nodeId, value);
}
- (double)pixelpart_node_set_repeat:(char*)runtimePtr nodeId:(double)nodeId value:(double)value {
	return pixelpart_node_set_repeat(runtimePtr, nodeId, value);
}
- (double)pixelpart_node_get_start:(char*)runtimePtr nodeId:(double)nodeId {
	return pixelpart_node_get_start(runtimePtr, nodeId);
}
- (double)pixelpart_node_get_duration:(char*)runtimePtr nodeId:(double)nodeId {
	return pixelpart_node_get_duration(runtimePtr, nodeId);
}
- (double)pixelpart_node_is_repeating:(char*)runtimePtr nodeId:(double)nodeId {
	return pixelpart_node_is_repeating(runtimePtr, nodeId);
}
- (double)pixelpart_node_is_active:(char*)runtimePtr nodeId:(double)nodeId {
	return pixelpart_node_is_active(runtimePtr, nodeId);
}
- (double)pixelpart_node_get_local_time:(char*)runtimePtr nodeId:(double)nodeId {
	return pixelpart_node_get_local_time(runtimePtr, nodeId);
}
- (NSString*)pixelpart_node_get_position:(char*)runtimePtr nodeId:(double)nodeId {
	return [NSString stringWithUTF8String:pixelpart_node_get_position(runtimePtr, nodeId)];
}
- (NSString*)pixelpart_node_get_rotation:(char*)runtimePtr nodeId:(double)nodeId {
	return [NSString stringWithUTF8String:pixelpart_node_get_rotation(runtimePtr, nodeId)];
}
- (NSString*)pixelpart_node_get_scale:(char*)runtimePtr nodeId:(double)nodeId {
	return [NSString stringWithUTF8String:pixelpart_node_get_scale(runtimePtr, nodeId)];
}

// Particle emitter
- (double)pixelpart_particle_emitter_set_shape:(char*)runtimePtr emitterId:(double)emitterId shape:(double)shape {
	return pixelpart_particle_emitter_set_shape(runtimePtr, emitterId, shape);
}
- (double)pixelpart_particle_emitter_get_shape:(char*)runtimePtr emitterId:(double)emitterId {
	return pixelpart_particle_emitter_get_shape(runtimePtr, emitterId);
}
- (double)pixelpart_particle_emitter_add_shape_point:(char*)runtimePtr emitterId:(double)emitterId valueBufferPtr:(char*)valueBufferPtr {
	return pixelpart_particle_emitter_add_shape_point(runtimePtr, emitterId, valueBufferPtr);
}
- (double)pixelpart_particle_emitter_remove_shape_point:(char*)runtimePtr emitterId:(double)emitterId index:(double)index {
	return pixelpart_particle_emitter_remove_shape_point(runtimePtr, emitterId, index);
}
- (double)pixelpart_particle_emitter_set_shape_point:(char*)runtimePtr emitterId:(double)emitterId index:(double)index valueBufferPtr:(char*)valueBufferPtr {
	return pixelpart_particle_emitter_set_shape_point(runtimePtr, emitterId, index, valueBufferPtr);
}
- (double)pixelpart_particle_emitter_get_shape_point:(char*)runtimePtr emitterId:(double)emitterId index:(double)index valueBufferPtr:(char*)valueBufferPtr {
	return pixelpart_particle_emitter_get_shape_point(runtimePtr, emitterId, index, valueBufferPtr);
}
- (double)pixelpart_particle_emitter_get_shape_point_count:(char*)runtimePtr emitterId:(double)emitterId {
	return pixelpart_particle_emitter_get_shape_point_count(runtimePtr, emitterId);
}
- (double)pixelpart_particle_emitter_set_distribution:(char*)runtimePtr emitterId:(double)emitterId mode:(double)mode {
	return pixelpart_particle_emitter_set_distribution(runtimePtr, emitterId, mode);
}
- (double)pixelpart_particle_emitter_get_distribution:(char*)runtimePtr emitterId:(double)emitterId {
	return pixelpart_particle_emitter_get_distribution(runtimePtr, emitterId);
}
- (double)pixelpart_particle_emitter_set_grid_order:(char*)runtimePtr emitterId:(double)emitterId mode:(double)mode {
	return pixelpart_particle_emitter_set_grid_order(runtimePtr, emitterId, mode);
}
- (double)pixelpart_particle_emitter_get_grid_order:(char*)runtimePtr emitterId:(double)emitterId {
	return pixelpart_particle_emitter_get_grid_order(runtimePtr, emitterId);
}
- (double)pixelpart_particle_emitter_set_grid_size:(char*)runtimePtr emitterId:(double)emitterId valueBufferPtr:(char*)valueBufferPtr {
	return pixelpart_particle_emitter_set_grid_size(runtimePtr, emitterId, valueBufferPtr);
}
- (double)pixelpart_particle_emitter_get_grid_size_x:(char*)runtimePtr emitterId:(double)emitterId {
	return pixelpart_particle_emitter_get_grid_size_x(runtimePtr, emitterId);
}
- (double)pixelpart_particle_emitter_get_grid_size_y:(char*)runtimePtr emitterId:(double)emitterId {
	return pixelpart_particle_emitter_get_grid_size_y(runtimePtr, emitterId);
}
- (double)pixelpart_particle_emitter_get_grid_size_z:(char*)runtimePtr emitterId:(double)emitterId {
	return pixelpart_particle_emitter_get_grid_size_z(runtimePtr, emitterId);
}
- (double)pixelpart_particle_emitter_set_emission_mode:(char*)runtimePtr emitterId:(double)emitterId mode:(double)mode {
	return pixelpart_particle_emitter_set_emission_mode(runtimePtr, emitterId, mode);
}
- (double)pixelpart_particle_emitter_get_emission_mode:(char*)runtimePtr emitterId:(double)emitterId {
	return pixelpart_particle_emitter_get_emission_mode(runtimePtr, emitterId);
}
- (double)pixelpart_particle_emitter_set_direction_mode:(char*)runtimePtr emitterId:(double)emitterId mode:(double)mode {
	return pixelpart_particle_emitter_set_direction_mode(runtimePtr, emitterId, mode);
}
- (double)pixelpart_particle_emitter_get_direction_mode:(char*)runtimePtr emitterId:(double)emitterId {
	return pixelpart_particle_emitter_get_direction_mode(runtimePtr, emitterId);
}
- (NSString*)pixelpart_particle_emitter_get_direction:(char*)runtimePtr emitterId:(double)emitterId {
	return [NSString stringWithUTF8String:pixelpart_particle_emitter_get_direction(runtimePtr, emitterId)];
}
- (NSString*)pixelpart_particle_emitter_get_spread:(char*)runtimePtr emitterId:(double)emitterId {
	return [NSString stringWithUTF8String:pixelpart_particle_emitter_get_spread(runtimePtr, emitterId)];
}

// Force field
- (double)pixelpart_force_field_set_infinite:(char*)runtimePtr forceFieldId:(double)forceFieldId mode:(double)mode {
	return pixelpart_force_field_set_infinite(runtimePtr, forceFieldId, mode);
}
- (double)pixelpart_force_field_is_infinite:(char*)runtimePtr forceFieldId:(double)forceFieldId {
	return pixelpart_force_field_is_infinite(runtimePtr, forceFieldId);
}
- (NSString*)pixelpart_force_field_get_strength:(char*)runtimePtr forceFieldId:(double)forceFieldId {
	return [NSString stringWithUTF8String:pixelpart_force_field_get_strength(runtimePtr, forceFieldId)];
}
- (NSString*)pixelpart_attraction_field_get_falloff_power:(char*)runtimePtr forceFieldId:(double)forceFieldId {
	return [NSString stringWithUTF8String:pixelpart_attraction_field_get_falloff_power(runtimePtr, forceFieldId)];
}
- (NSString*)pixelpart_acceleration_field_get_acceleration_direction:(char*)runtimePtr forceFieldId:(double)forceFieldId {
	return [NSString stringWithUTF8String:pixelpart_acceleration_field_get_acceleration_direction(runtimePtr, forceFieldId)];
}
- (NSString*)pixelpart_acceleration_field_get_acceleration_direction_variance:(char*)runtimePtr forceFieldId:(double)forceFieldId {
	return [NSString stringWithUTF8String:pixelpart_acceleration_field_get_acceleration_direction_variance(runtimePtr, forceFieldId)];
}
- (NSString*)pixelpart_acceleration_field_get_acceleration_strength_variance:(char*)runtimePtr forceFieldId:(double)forceFieldId {
	return [NSString stringWithUTF8String:pixelpart_acceleration_field_get_acceleration_strength_variance(runtimePtr, forceFieldId)];
}
- (double)pixelpart_acceleration_field_set_acceleration_grid_size:(char*)runtimePtr forceFieldId:(double)forceFieldId valueBufferPtr:(char*)valueBufferPtr {
	return pixelpart_acceleration_field_set_acceleration_grid_size(runtimePtr, forceFieldId, valueBufferPtr);
}
- (double)pixelpart_acceleration_field_get_acceleration_grid_size_x:(char*)runtimePtr forceFieldId:(double)forceFieldId {
	return pixelpart_acceleration_field_get_acceleration_grid_size_x(runtimePtr, forceFieldId);
}
- (double)pixelpart_acceleration_field_get_acceleration_grid_size_y:(char*)runtimePtr forceFieldId:(double)forceFieldId {
	return pixelpart_acceleration_field_get_acceleration_grid_size_y(runtimePtr, forceFieldId);
}
- (double)pixelpart_acceleration_field_get_acceleration_grid_size_z:(char*)runtimePtr forceFieldId:(double)forceFieldId {
	return pixelpart_acceleration_field_get_acceleration_grid_size_z(runtimePtr, forceFieldId);
}
- (double)pixelpart_vector_field_set_vector_field_filter:(char*)runtimePtr forceFieldId:(double)forceFieldId filter:(double)filter {
	return pixelpart_vector_field_set_vector_field_filter(runtimePtr, forceFieldId, filter);
}
- (double)pixelpart_vector_field_get_vector_field_filter:(char*)runtimePtr forceFieldId:(double)forceFieldId {
	return pixelpart_vector_field_get_vector_field_filter(runtimePtr, forceFieldId);
}
- (NSString*)pixelpart_vector_field_get_tightness:(char*)runtimePtr forceFieldId:(double)forceFieldId {
	return [NSString stringWithUTF8String:pixelpart_vector_field_get_tightness(runtimePtr, forceFieldId)];
}
- (NSString*)pixelpart_noise_field_get_noise_octaves:(char*)runtimePtr forceFieldId:(double)forceFieldId {
	return [NSString stringWithUTF8String:pixelpart_noise_field_get_noise_octaves(runtimePtr, forceFieldId)];
}
- (NSString*)pixelpart_noise_field_get_noise_frequency:(char*)runtimePtr forceFieldId:(double)forceFieldId {
	return [NSString stringWithUTF8String:pixelpart_noise_field_get_noise_frequency(runtimePtr, forceFieldId)];
}
- (NSString*)pixelpart_noise_field_get_noise_persistence:(char*)runtimePtr forceFieldId:(double)forceFieldId {
	return [NSString stringWithUTF8String:pixelpart_noise_field_get_noise_persistence(runtimePtr, forceFieldId)];
}
- (NSString*)pixelpart_noise_field_get_noise_lacunarity:(char*)runtimePtr forceFieldId:(double)forceFieldId {
	return [NSString stringWithUTF8String:pixelpart_noise_field_get_noise_lacunarity(runtimePtr, forceFieldId)];
}
- (double)pixelpart_noise_field_set_noise_animated:(char*)runtimePtr forceFieldId:(double)forceFieldId animated:(double)animated {
	return pixelpart_noise_field_set_noise_animated(runtimePtr, forceFieldId, animated);
}
- (double)pixelpart_noise_field_is_noise_animated:(char*)runtimePtr forceFieldId:(double)forceFieldId {
	return pixelpart_noise_field_is_noise_animated(runtimePtr, forceFieldId);
}
- (NSString*)pixelpart_noise_field_get_noise_animation_time_scale:(char*)runtimePtr forceFieldId:(double)forceFieldId {
	return [NSString stringWithUTF8String:pixelpart_noise_field_get_noise_animation_time_scale(runtimePtr, forceFieldId)];
}
- (NSString*)pixelpart_noise_field_get_noise_animation_time_base:(char*)runtimePtr forceFieldId:(double)forceFieldId {
	return [NSString stringWithUTF8String:pixelpart_noise_field_get_noise_animation_time_base(runtimePtr, forceFieldId)];
}
- (NSString*)pixelpart_drag_field_get_velocity_influence:(char*)runtimePtr forceFieldId:(double)forceFieldId {
	return [NSString stringWithUTF8String:pixelpart_drag_field_get_velocity_influence(runtimePtr, forceFieldId)];
}
- (NSString*)pixelpart_drag_field_get_size_influence:(char*)runtimePtr forceFieldId:(double)forceFieldId {
	return [NSString stringWithUTF8String:pixelpart_drag_field_get_size_influence(runtimePtr, forceFieldId)];
}

// Collider
- (NSString*)pixelpart_collider_get_kill_on_contact:(char*)runtimePtr colliderId:(double)colliderId {
	return [NSString stringWithUTF8String:pixelpart_collider_get_kill_on_contact(runtimePtr, colliderId)];
}
- (NSString*)pixelpart_collider_get_bounce:(char*)runtimePtr colliderId:(double)colliderId {
	return [NSString stringWithUTF8String:pixelpart_collider_get_bounce(runtimePtr, colliderId)];
}
- (NSString*)pixelpart_collider_get_friction:(char*)runtimePtr colliderId:(double)colliderId {
	return [NSString stringWithUTF8String:pixelpart_collider_get_friction(runtimePtr, colliderId)];
}
- (double)pixelpart_line_collider_add_point:(char*)runtimePtr colliderId:(double)colliderId valueBufferPtr:(char*)valueBufferPtr {
	return pixelpart_line_collider_add_point(runtimePtr, colliderId, valueBufferPtr);
}
- (double)pixelpart_line_collider_set_point:(char*)runtimePtr colliderId:(double)colliderId index:(double)index valueBufferPtr:(char*)valueBufferPtr {
	return pixelpart_line_collider_set_point(runtimePtr, colliderId, index, valueBufferPtr);
}
- (double)pixelpart_line_collider_remove_point:(char*)runtimePtr colliderId:(double)colliderId index:(double)index {
	return pixelpart_line_collider_remove_point(runtimePtr, colliderId, index);
}
- (double)pixelpart_line_collider_get_point:(char*)runtimePtr colliderId:(double)colliderId index:(double)index valueBufferPtr:(char*)valueBufferPtr {
	return pixelpart_line_collider_get_point(runtimePtr, colliderId, index, valueBufferPtr);
}
- (double)pixelpart_line_collider_get_point_count:(char*)runtimePtr colliderId:(double)colliderId {
	return pixelpart_line_collider_get_point_count(runtimePtr, colliderId);
}

// Light source
- (NSString*)pixelpart_light_source_get_attenuation:(char*)runtimePtr lightSourceId:(double)lightSourceId {
	return [NSString stringWithUTF8String:pixelpart_light_source_get_attenuation(runtimePtr, lightSourceId)];
}
- (NSString*)pixelpart_light_source_get_color:(char*)runtimePtr lightSourceId:(double)lightSourceId {
	return [NSString stringWithUTF8String:pixelpart_light_source_get_color(runtimePtr, lightSourceId)];
}
- (NSString*)pixelpart_light_source_get_intensity:(char*)runtimePtr lightSourceId:(double)lightSourceId {
	return [NSString stringWithUTF8String:pixelpart_light_source_get_intensity(runtimePtr, lightSourceId)];
}
- (NSString*)pixelpart_spot_light_source_get_spot_angle:(char*)runtimePtr lightSourceId:(double)lightSourceId {
	return [NSString stringWithUTF8String:pixelpart_spot_light_source_get_spot_angle(runtimePtr, lightSourceId)];
}
- (NSString*)pixelpart_spot_light_source_get_spot_angle_attenuation:(char*)runtimePtr lightSourceId:(double)lightSourceId {
	return [NSString stringWithUTF8String:pixelpart_spot_light_source_get_spot_angle_attenuation(runtimePtr, lightSourceId)];
}

// Particle type
- (double)pixelpart_find_particle_type:(char*)runtimePtr bufferPtr:(char*)bufferPtr {
	return pixelpart_find_particle_type(runtimePtr, bufferPtr);
}
- (double)pixelpart_find_particle_type_by_index:(char*)runtimePtr particleTypeIndex:(double)particleTypeIndex {
	return pixelpart_find_particle_type_by_index(runtimePtr, particleTypeIndex);
}
- (double)pixelpart_particle_type_exists:(char*)runtimePtr particleTypeId:(double)particleTypeId {
	return pixelpart_particle_type_exists(runtimePtr, particleTypeId);
}
- (double)pixelpart_particle_type_get_index:(char*)runtimePtr particleTypeId:(double)particleTypeId {
	return pixelpart_particle_type_get_index(runtimePtr, particleTypeId);
}
- (double)pixelpart_particle_type_get_parent_id:(char*)runtimePtr particleTypeId:(double)particleTypeId {
	return pixelpart_particle_type_get_parent_id(runtimePtr, particleTypeId);
}
- (NSString*)pixelpart_particle_type_get_name:(char*)runtimePtr particleTypeId:(double)particleTypeId {
	return [NSString stringWithUTF8String:pixelpart_particle_type_get_name(runtimePtr, particleTypeId)];
}
- (double)pixelpart_particle_type_set_position_relative:(char*)runtimePtr particleTypeId:(double)particleTypeId relative:(double)relative {
	return pixelpart_particle_type_set_position_relative(runtimePtr, particleTypeId, relative);
}
- (double)pixelpart_particle_type_is_position_relative:(char*)runtimePtr particleTypeId:(double)particleTypeId {
	return pixelpart_particle_type_is_position_relative(runtimePtr, particleTypeId);
}
- (double)pixelpart_particle_type_set_rotation_mode:(char*)runtimePtr particleTypeId:(double)particleTypeId mode:(double)mode {
	return pixelpart_particle_type_set_rotation_mode(runtimePtr, particleTypeId, mode);
}
- (double)pixelpart_particle_type_get_rotation_mode:(char*)runtimePtr particleTypeId:(double)particleTypeId {
	return pixelpart_particle_type_get_rotation_mode(runtimePtr, particleTypeId);
}
- (double)pixelpart_particle_type_set_alignment_mode:(char*)runtimePtr particleTypeId:(double)particleTypeId mode:(double)mode {
	return pixelpart_particle_type_set_alignment_mode(runtimePtr, particleTypeId, mode);
}
- (double)pixelpart_particle_type_get_alignment_mode:(char*)runtimePtr particleTypeId:(double)particleTypeId {
	return pixelpart_particle_type_get_alignment_mode(runtimePtr, particleTypeId);
}
- (NSString*)pixelpart_particle_type_get_pivot:(char*)runtimePtr particleTypeId:(double)particleTypeId {
	return [NSString stringWithUTF8String:pixelpart_particle_type_get_pivot(runtimePtr, particleTypeId)];
}
- (NSString*)pixelpart_particle_type_get_motion_path_force:(char*)runtimePtr particleTypeId:(double)particleTypeId {
	return [NSString stringWithUTF8String:pixelpart_particle_type_get_motion_path_force(runtimePtr, particleTypeId)];
}
- (double)pixelpart_particle_type_set_visible:(char*)runtimePtr particleTypeId:(double)particleTypeId visible:(double)visible {
	return pixelpart_particle_type_set_visible(runtimePtr, particleTypeId, visible);
}
- (double)pixelpart_particle_type_is_visible:(char*)runtimePtr particleTypeId:(double)particleTypeId {
	return pixelpart_particle_type_is_visible(runtimePtr, particleTypeId);
}
- (double)pixelpart_particle_type_set_layer:(char*)runtimePtr particleTypeId:(double)particleTypeId layer:(double)layer {
	return pixelpart_particle_type_set_layer(runtimePtr, particleTypeId, layer);
}
- (double)pixelpart_particle_type_get_layer:(char*)runtimePtr particleTypeId:(double)particleTypeId {
	return pixelpart_particle_type_get_layer(runtimePtr, particleTypeId);
}
- (NSString*)pixelpart_particle_type_get_material_id:(char*)runtimePtr particleTypeId:(double)particleTypeId {
	return [NSString stringWithUTF8String:pixelpart_particle_type_get_material_id(runtimePtr, particleTypeId)];
}
- (double)pixelpart_particle_type_is_material_builtin:(char*)runtimePtr particleTypeId:(double)particleTypeId {
	return pixelpart_particle_type_is_material_builtin(runtimePtr, particleTypeId);
}
- (double)pixelpart_particle_type_get_material_parameter_count:(char*)runtimePtr particleTypeId:(double)particleTypeId {
	return pixelpart_particle_type_get_material_parameter_count(runtimePtr, particleTypeId);
}
- (double)pixelpart_particle_type_get_material_parameter_ids:(char*)runtimePtr particleTypeId:(double)particleTypeId parameterIdBufferPtr:(char*)parameterIdBufferPtr {
	return pixelpart_particle_type_get_material_parameter_ids(runtimePtr, particleTypeId, parameterIdBufferPtr);
}
- (double)pixelpart_particle_type_get_material_parameter_type:(char*)runtimePtr particleTypeId:(double)particleTypeId parameterId:(double)parameterId {
	return pixelpart_particle_type_get_material_parameter_type(runtimePtr, particleTypeId, parameterId);
}
- (double)pixelpart_particle_type_get_material_parameter_value:(char*)runtimePtr particleTypeId:(double)particleTypeId parameterId:(double)parameterId resultBufferPtr:(char*)resultBufferPtr {
	return pixelpart_particle_type_get_material_parameter_value(runtimePtr, particleTypeId, parameterId, resultBufferPtr);
}
- (double)pixelpart_particle_type_get_renderer:(char*)runtimePtr particleTypeId:(double)particleTypeId {
	return pixelpart_particle_type_get_renderer(runtimePtr, particleTypeId);
}
- (NSString*)pixelpart_particle_type_get_mesh_renderer_mesh_resource_id:(char*)runtimePtr particleTypeId:(double)particleTypeId {
	return [NSString stringWithUTF8String:pixelpart_particle_type_get_mesh_renderer_mesh_resource_id(runtimePtr, particleTypeId)];
}
- (NSString*)pixelpart_particle_type_get_count:(char*)runtimePtr particleTypeId:(double)particleTypeId {
	return [NSString stringWithUTF8String:pixelpart_particle_type_get_count(runtimePtr, particleTypeId)];
}
- (NSString*)pixelpart_particle_type_get_lifespan:(char*)runtimePtr particleTypeId:(double)particleTypeId {
	return [NSString stringWithUTF8String:pixelpart_particle_type_get_lifespan(runtimePtr, particleTypeId)];
}
- (NSString*)pixelpart_particle_type_get_initial_size:(char*)runtimePtr particleTypeId:(double)particleTypeId {
	return [NSString stringWithUTF8String:pixelpart_particle_type_get_initial_size(runtimePtr, particleTypeId)];
}
- (NSString*)pixelpart_particle_type_get_initial_rotation:(char*)runtimePtr particleTypeId:(double)particleTypeId {
	return [NSString stringWithUTF8String:pixelpart_particle_type_get_initial_rotation(runtimePtr, particleTypeId)];
}
- (NSString*)pixelpart_particle_type_get_initial_velocity:(char*)runtimePtr particleTypeId:(double)particleTypeId {
	return [NSString stringWithUTF8String:pixelpart_particle_type_get_initial_velocity(runtimePtr, particleTypeId)];
}
- (NSString*)pixelpart_particle_type_get_inherited_velocity:(char*)runtimePtr particleTypeId:(double)particleTypeId {
	return [NSString stringWithUTF8String:pixelpart_particle_type_get_inherited_velocity(runtimePtr, particleTypeId)];
}
- (NSString*)pixelpart_particle_type_get_initial_opacity:(char*)runtimePtr particleTypeId:(double)particleTypeId {
	return [NSString stringWithUTF8String:pixelpart_particle_type_get_initial_opacity(runtimePtr, particleTypeId)];
}
- (NSString*)pixelpart_particle_type_get_motion_path:(char*)runtimePtr particleTypeId:(double)particleTypeId {
	return [NSString stringWithUTF8String:pixelpart_particle_type_get_motion_path(runtimePtr, particleTypeId)];
}
- (NSString*)pixelpart_particle_type_get_size:(char*)runtimePtr particleTypeId:(double)particleTypeId {
	return [NSString stringWithUTF8String:pixelpart_particle_type_get_size(runtimePtr, particleTypeId)];
}
- (NSString*)pixelpart_particle_type_get_stretch:(char*)runtimePtr particleTypeId:(double)particleTypeId {
	return [NSString stringWithUTF8String:pixelpart_particle_type_get_stretch(runtimePtr, particleTypeId)];
}
- (NSString*)pixelpart_particle_type_get_physical_size:(char*)runtimePtr particleTypeId:(double)particleTypeId {
	return [NSString stringWithUTF8String:pixelpart_particle_type_get_physical_size(runtimePtr, particleTypeId)];
}
- (NSString*)pixelpart_particle_type_get_rotation:(char*)runtimePtr particleTypeId:(double)particleTypeId {
	return [NSString stringWithUTF8String:pixelpart_particle_type_get_rotation(runtimePtr, particleTypeId)];
}
- (NSString*)pixelpart_particle_type_get_rotation_by_speed:(char*)runtimePtr particleTypeId:(double)particleTypeId {
	return [NSString stringWithUTF8String:pixelpart_particle_type_get_rotation_by_speed(runtimePtr, particleTypeId)];
}
- (NSString*)pixelpart_particle_type_get_acceleration:(char*)runtimePtr particleTypeId:(double)particleTypeId {
	return [NSString stringWithUTF8String:pixelpart_particle_type_get_acceleration(runtimePtr, particleTypeId)];
}
- (NSString*)pixelpart_particle_type_get_radial_acceleration:(char*)runtimePtr particleTypeId:(double)particleTypeId {
	return [NSString stringWithUTF8String:pixelpart_particle_type_get_radial_acceleration(runtimePtr, particleTypeId)];
}
- (NSString*)pixelpart_particle_type_get_weight:(char*)runtimePtr particleTypeId:(double)particleTypeId {
	return [NSString stringWithUTF8String:pixelpart_particle_type_get_weight(runtimePtr, particleTypeId)];
}
- (NSString*)pixelpart_particle_type_get_bounce:(char*)runtimePtr particleTypeId:(double)particleTypeId {
	return [NSString stringWithUTF8String:pixelpart_particle_type_get_bounce(runtimePtr, particleTypeId)];
}
- (NSString*)pixelpart_particle_type_get_friction:(char*)runtimePtr particleTypeId:(double)particleTypeId {
	return [NSString stringWithUTF8String:pixelpart_particle_type_get_friction(runtimePtr, particleTypeId)];
}
- (NSString*)pixelpart_particle_type_get_color:(char*)runtimePtr particleTypeId:(double)particleTypeId {
	return [NSString stringWithUTF8String:pixelpart_particle_type_get_color(runtimePtr, particleTypeId)];
}
- (NSString*)pixelpart_particle_type_get_opacity:(char*)runtimePtr particleTypeId:(double)particleTypeId {
	return [NSString stringWithUTF8String:pixelpart_particle_type_get_opacity(runtimePtr, particleTypeId)];
}
- (NSString*)pixelpart_particle_type_get_lifespan_variance:(char*)runtimePtr particleTypeId:(double)particleTypeId {
	return [NSString stringWithUTF8String:pixelpart_particle_type_get_lifespan_variance(runtimePtr, particleTypeId)];
}
- (NSString*)pixelpart_particle_type_get_size_variance:(char*)runtimePtr particleTypeId:(double)particleTypeId {
	return [NSString stringWithUTF8String:pixelpart_particle_type_get_size_variance(runtimePtr, particleTypeId)];
}
- (NSString*)pixelpart_particle_type_get_rotation_variance:(char*)runtimePtr particleTypeId:(double)particleTypeId {
	return [NSString stringWithUTF8String:pixelpart_particle_type_get_rotation_variance(runtimePtr, particleTypeId)];
}
- (NSString*)pixelpart_particle_type_get_angular_velocity_variance:(char*)runtimePtr particleTypeId:(double)particleTypeId {
	return [NSString stringWithUTF8String:pixelpart_particle_type_get_angular_velocity_variance(runtimePtr, particleTypeId)];
}
- (NSString*)pixelpart_particle_type_get_velocity_variance:(char*)runtimePtr particleTypeId:(double)particleTypeId {
	return [NSString stringWithUTF8String:pixelpart_particle_type_get_velocity_variance(runtimePtr, particleTypeId)];
}
- (NSString*)pixelpart_particle_type_get_color_variance:(char*)runtimePtr particleTypeId:(double)particleTypeId {
	return [NSString stringWithUTF8String:pixelpart_particle_type_get_color_variance(runtimePtr, particleTypeId)];
}
- (NSString*)pixelpart_particle_type_get_opacity_variance:(char*)runtimePtr particleTypeId:(double)particleTypeId {
	return [NSString stringWithUTF8String:pixelpart_particle_type_get_opacity_variance(runtimePtr, particleTypeId)];
}

// Static property
- (double)pixelpart_static_property_bool_value:(char*)propertyPtr {
	return pixelpart_static_property_bool_value(propertyPtr);
}
- (double)pixelpart_static_property_bool_set_base_value:(char*)propertyPtr value:(double)value {
	return pixelpart_static_property_bool_set_base_value(propertyPtr, value);
}
- (double)pixelpart_static_property_bool_get_base_value:(char*)propertyPtr {
	return pixelpart_static_property_bool_get_base_value(propertyPtr);
}
- (double)pixelpart_static_property_int_value:(char*)propertyPtr {
	return pixelpart_static_property_int_value(propertyPtr);
}
- (double)pixelpart_static_property_int_set_base_value:(char*)propertyPtr value:(double)value {
	return pixelpart_static_property_int_set_base_value(propertyPtr, value);
}
- (double)pixelpart_static_property_int_get_base_value:(char*)propertyPtr {
	return pixelpart_static_property_int_get_base_value(propertyPtr);
}
- (double)pixelpart_static_property_float_value:(char*)propertyPtr {
	return pixelpart_static_property_float_value(propertyPtr);
}
- (double)pixelpart_static_property_float_set_base_value:(char*)propertyPtr value:(double)value {
	return pixelpart_static_property_float_set_base_value(propertyPtr, value);
}
- (double)pixelpart_static_property_float_get_base_value:(char*)propertyPtr {
	return pixelpart_static_property_float_get_base_value(propertyPtr);
}
- (double)pixelpart_static_property_float2_value:(char*)propertyPtr valueBufferPtr:(char*)valueBufferPtr {
	return pixelpart_static_property_float2_value(propertyPtr, valueBufferPtr);
}
- (double)pixelpart_static_property_float2_set_base_value:(char*)propertyPtr valueBufferPtr:(char*)valueBufferPtr {
	return pixelpart_static_property_float2_set_base_value(propertyPtr, valueBufferPtr);
}
- (double)pixelpart_static_property_float2_get_base_value:(char*)propertyPtr valueBufferPtr:(char*)valueBufferPtr {
	return pixelpart_static_property_float2_get_base_value(propertyPtr, valueBufferPtr);
}
- (double)pixelpart_static_property_float3_value:(char*)propertyPtr valueBufferPtr:(char*)valueBufferPtr {
	return pixelpart_static_property_float3_value(propertyPtr, valueBufferPtr);
}
- (double)pixelpart_static_property_float3_set_base_value:(char*)propertyPtr valueBufferPtr:(char*)valueBufferPtr {
	return pixelpart_static_property_float3_set_base_value(propertyPtr, valueBufferPtr);
}
- (double)pixelpart_static_property_float3_get_base_value:(char*)propertyPtr valueBufferPtr:(char*)valueBufferPtr {
	return pixelpart_static_property_float3_get_base_value(propertyPtr, valueBufferPtr);
}
- (double)pixelpart_static_property_float4_value:(char*)propertyPtr valueBufferPtr:(char*)valueBufferPtr {
	return pixelpart_static_property_float4_value(propertyPtr, valueBufferPtr);
}
- (double)pixelpart_static_property_float4_set_base_value:(char*)propertyPtr valueBufferPtr:(char*)valueBufferPtr {
	return pixelpart_static_property_float4_set_base_value(propertyPtr, valueBufferPtr);
}
- (double)pixelpart_static_property_float4_get_base_value:(char*)propertyPtr valueBufferPtr:(char*)valueBufferPtr {
	return pixelpart_static_property_float4_get_base_value(propertyPtr, valueBufferPtr);
}

// Animated property
- (double)pixelpart_animated_property_float_at:(char*)propertyPtr position:(double)position {
	return pixelpart_animated_property_float_at(propertyPtr, position);
}
- (double)pixelpart_animated_property_float_add_keyframe:(char*)propertyPtr position:(double)position value:(double)value {
	return pixelpart_animated_property_float_add_keyframe(propertyPtr, position, value);
}
- (double)pixelpart_animated_property_float_remove_keyframe:(char*)propertyPtr index:(double)index {
	return pixelpart_animated_property_float_remove_keyframe(propertyPtr, index);
}
- (double)pixelpart_animated_property_float_set_keyframe_value:(char*)propertyPtr index:(double)index value:(double)value {
	return pixelpart_animated_property_float_set_keyframe_value(propertyPtr, index, value);
}
- (double)pixelpart_animated_property_float_set_keyframe_position:(char*)propertyPtr index:(double)index position:(double)position {
	return pixelpart_animated_property_float_set_keyframe_position(propertyPtr, index, position);
}
- (double)pixelpart_animated_property_float_clear_keyframes:(char*)propertyPtr {
	return pixelpart_animated_property_float_clear_keyframes(propertyPtr);
}
- (double)pixelpart_animated_property_float_keyframe_count:(char*)propertyPtr {
	return pixelpart_animated_property_float_keyframe_count(propertyPtr);
}
- (double)pixelpart_animated_property_float_keyframe_value:(char*)propertyPtr index:(double)index {
	return pixelpart_animated_property_float_keyframe_value(propertyPtr, index);
}
- (double)pixelpart_animated_property_float_keyframe_index:(char*)propertyPtr position:(double)position epsilon:(double)epsilon {
	return pixelpart_animated_property_float_keyframe_index(propertyPtr, position, epsilon);
}
- (double)pixelpart_animated_property_float_set_keyframe_interpolation:(char*)propertyPtr method:(double)method {
	return pixelpart_animated_property_float_set_keyframe_interpolation(propertyPtr, method);
}
- (double)pixelpart_animated_property_float_get_keyframe_interpolation:(char*)propertyPtr {
	return pixelpart_animated_property_float_get_keyframe_interpolation(propertyPtr);
}
- (double)pixelpart_animated_property_float2_at:(char*)propertyPtr position:(double)position valueBufferPtr:(char*)valueBufferPtr {
	return pixelpart_animated_property_float2_at(propertyPtr, position, valueBufferPtr);
}
- (double)pixelpart_animated_property_float2_add_keyframe:(char*)propertyPtr position:(double)position valueBufferPtr:(char*)valueBufferPtr {
	return pixelpart_animated_property_float2_add_keyframe(propertyPtr, position, valueBufferPtr);
}
- (double)pixelpart_animated_property_float2_remove_keyframe:(char*)propertyPtr index:(double)index {
	return pixelpart_animated_property_float2_remove_keyframe(propertyPtr, index);
}
- (double)pixelpart_animated_property_float2_set_keyframe_value:(char*)propertyPtr index:(double)index valueBufferPtr:(char*)valueBufferPtr {
	return pixelpart_animated_property_float2_set_keyframe_value(propertyPtr, index, valueBufferPtr);
}
- (double)pixelpart_animated_property_float2_set_keyframe_position:(char*)propertyPtr index:(double)index position:(double)position {
	return pixelpart_animated_property_float2_set_keyframe_position(propertyPtr, index, position);
}
- (double)pixelpart_animated_property_float2_clear_keyframes:(char*)propertyPtr {
	return pixelpart_animated_property_float2_clear_keyframes(propertyPtr);
}
- (double)pixelpart_animated_property_float2_keyframe_count:(char*)propertyPtr {
	return pixelpart_animated_property_float2_keyframe_count(propertyPtr);
}
- (double)pixelpart_animated_property_float2_keyframe_value:(char*)propertyPtr index:(double)index valueBufferPtr:(char*)valueBufferPtr {
	return pixelpart_animated_property_float2_keyframe_value(propertyPtr, index, valueBufferPtr);
}
- (double)pixelpart_animated_property_float2_keyframe_index:(char*)propertyPtr position:(double)position epsilon:(double)epsilon {
	return pixelpart_animated_property_float2_keyframe_index(propertyPtr, position, epsilon);
}
- (double)pixelpart_animated_property_float2_set_keyframe_interpolation:(char*)propertyPtr method:(double)method {
	return pixelpart_animated_property_float2_set_keyframe_interpolation(propertyPtr, method);
}
- (double)pixelpart_animated_property_float2_get_keyframe_interpolation:(char*)propertyPtr {
	return pixelpart_animated_property_float2_get_keyframe_interpolation(propertyPtr);
}
- (double)pixelpart_animated_property_float3_at:(char*)propertyPtr position:(double)position valueBufferPtr:(char*)valueBufferPtr {
	return pixelpart_animated_property_float3_at(propertyPtr, position, valueBufferPtr);
}
- (double)pixelpart_animated_property_float3_add_keyframe:(char*)propertyPtr position:(double)position valueBufferPtr:(char*)valueBufferPtr {
	return pixelpart_animated_property_float3_add_keyframe(propertyPtr, position, valueBufferPtr);
}
- (double)pixelpart_animated_property_float3_remove_keyframe:(char*)propertyPtr index:(double)index {
	return pixelpart_animated_property_float3_remove_keyframe(propertyPtr, index);
}
- (double)pixelpart_animated_property_float3_set_keyframe_value:(char*)propertyPtr index:(double)index valueBufferPtr:(char*)valueBufferPtr {
	return pixelpart_animated_property_float3_set_keyframe_value(propertyPtr, index, valueBufferPtr);
}
- (double)pixelpart_animated_property_float3_set_keyframe_position:(char*)propertyPtr index:(double)index position:(double)position {
	return pixelpart_animated_property_float3_set_keyframe_position(propertyPtr, index, position);
}
- (double)pixelpart_animated_property_float3_clear_keyframes:(char*)propertyPtr {
	return pixelpart_animated_property_float3_clear_keyframes(propertyPtr);
}
- (double)pixelpart_animated_property_float3_keyframe_count:(char*)propertyPtr {
	return pixelpart_animated_property_float3_keyframe_count(propertyPtr);
}
- (double)pixelpart_animated_property_float3_keyframe_value:(char*)propertyPtr index:(double)index valueBufferPtr:(char*)valueBufferPtr {
	return pixelpart_animated_property_float3_keyframe_value(propertyPtr, index, valueBufferPtr);
}
- (double)pixelpart_animated_property_float3_keyframe_index:(char*)propertyPtr position:(double)position epsilon:(double)epsilon {
	return pixelpart_animated_property_float3_keyframe_index(propertyPtr, position, epsilon);
}
- (double)pixelpart_animated_property_float3_set_keyframe_interpolation:(char*)propertyPtr method:(double)method {
	return pixelpart_animated_property_float3_set_keyframe_interpolation(propertyPtr, method);
}
- (double)pixelpart_animated_property_float3_get_keyframe_interpolation:(char*)propertyPtr {
	return pixelpart_animated_property_float3_get_keyframe_interpolation(propertyPtr);
}
- (double)pixelpart_animated_property_float4_at:(char*)propertyPtr position:(double)position valueBufferPtr:(char*)valueBufferPtr {
	return pixelpart_animated_property_float4_at(propertyPtr, position, valueBufferPtr);
}
- (double)pixelpart_animated_property_float4_add_keyframe:(char*)propertyPtr position:(double)position valueBufferPtr:(char*)valueBufferPtr {
	return pixelpart_animated_property_float4_add_keyframe(propertyPtr, position, valueBufferPtr);
}
- (double)pixelpart_animated_property_float4_remove_keyframe:(char*)propertyPtr index:(double)index {
	return pixelpart_animated_property_float4_remove_keyframe(propertyPtr, index);
}
- (double)pixelpart_animated_property_float4_set_keyframe_value:(char*)propertyPtr index:(double)index valueBufferPtr:(char*)valueBufferPtr {
	return pixelpart_animated_property_float4_set_keyframe_value(propertyPtr, index, valueBufferPtr);
}
- (double)pixelpart_animated_property_float4_set_keyframe_position:(char*)propertyPtr index:(double)index position:(double)position {
	return pixelpart_animated_property_float4_set_keyframe_position(propertyPtr, index, position);
}
- (double)pixelpart_animated_property_float4_clear_keyframes:(char*)propertyPtr {
	return pixelpart_animated_property_float4_clear_keyframes(propertyPtr);
}
- (double)pixelpart_animated_property_float4_keyframe_count:(char*)propertyPtr {
	return pixelpart_animated_property_float4_keyframe_count(propertyPtr);
}
- (double)pixelpart_animated_property_float4_keyframe_value:(char*)propertyPtr index:(double)index valueBufferPtr:(char*)valueBufferPtr {
	return pixelpart_animated_property_float4_keyframe_value(propertyPtr, index, valueBufferPtr);
}
- (double)pixelpart_animated_property_float4_keyframe_index:(char*)propertyPtr position:(double)position epsilon:(double)epsilon {
	return pixelpart_animated_property_float4_keyframe_index(propertyPtr, position, epsilon);
}
- (double)pixelpart_animated_property_float4_set_keyframe_interpolation:(char*)propertyPtr method:(double)method {
	return pixelpart_animated_property_float4_set_keyframe_interpolation(propertyPtr, method);
}
- (double)pixelpart_animated_property_float4_get_keyframe_interpolation:(char*)propertyPtr {
	return pixelpart_animated_property_float4_get_keyframe_interpolation(propertyPtr);
}

@end
