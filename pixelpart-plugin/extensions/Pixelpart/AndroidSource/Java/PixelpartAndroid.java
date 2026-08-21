package ${YYAndroidPackageName};

import java.lang.String;
import java.nio.ByteBuffer;

import ${YYAndroidPackageName}.R;
import com.yoyogames.runner.RunnerJNILib;

import static net.pixelpart.MainActivity.*;

public class PixelpartAndroid {
	// Init
	public double pixelpart_init() {
		return JNIpixelpartinit();
	}
	public double pixelpart_shutdown() {
		return JNIpixelpartshutdown();
	}

	// Error
	public String pixelpart_last_error() {
		return JNIpixelpartlasterror();
	}

	// Effect runtime
	public String pixelpart_load_effect_resource(String data, double size) {
		return JNIpixelpartloadeffectresource(data, size);
	}
	public double pixelpart_delete_effect_resource(String resourcePtr) {
		return JNIpixelpartdeleteeffectresource(resourcePtr);
	}
	public String pixelpart_create_effect(String resourcePtr) {
		return JNIpixelpartcreateeffect(resourcePtr);
	}
	public double pixelpart_delete_effect(String runtimePtr) {
		return JNIpixelpartdeleteeffect(runtimePtr);
	}
	public double pixelpart_set_effect_scale(String runtimePtr, double scaleX, double scaleY) {
		return JNIpixelpartseteffectscale(runtimePtr, scaleX, scaleY);
	}
	public double pixelpart_set_effect_transform(String runtimePtr, double x, double y) {
		return JNIpixelpartseteffecttransform(runtimePtr, x, y);
	}
	public double pixelpart_advance_effect(String runtimePtr, ByteBuffer paramBufferPtr) {
		return JNIpixelpartadvanceeffect(runtimePtr, paramBufferPtr);
	}
	public double pixelpart_restart_effect(String runtimePtr, double clear) {
		return JNIpixelpartrestarteffect(runtimePtr, clear);
	}
	public double pixelpart_reseed_effect(String runtimePtr, double seed) {
		return JNIpixelpartreseedeffect(runtimePtr, seed);
	}
	public double pixelpart_get_effect_time(String runtimePtr) {
		return JNIpixelpartgeteffecttime(runtimePtr);
	}
	public double pixelpart_is_effect_finished(String runtimePtr) {
		return JNIpixelpartiseffectfinished(runtimePtr);
	}
	public double pixelpart_is_effect_3d(String runtimePtr) {
		return JNIpixelpartiseffect3d(runtimePtr);
	}
	public double pixelpart_get_effect_node_count(String runtimePtr) {
		return JNIpixelpartgeteffectnodecount(runtimePtr);
	}
	public double pixelpart_get_effect_particle_type_count(String runtimePtr) {
		return JNIpixelpartgeteffectparticletypecount(runtimePtr);
	}
	public double pixelpart_get_effect_particle_runtime_instance_count(String runtimePtr) {
		return JNIpixelpartgeteffectparticleruntimeinstancecount(runtimePtr);
	}
	public double pixelpart_get_effect_particle_runtime_instances(String runtimePtr, ByteBuffer instanceBufferPtr) {
		return JNIpixelpartgeteffectparticleruntimeinstances(runtimePtr, instanceBufferPtr);
	}
	public double pixelpart_get_effect_particle_count(String runtimePtr, double particleEmitterId, double particleTypeId) {
		return JNIpixelpartgeteffectparticlecount(runtimePtr, particleEmitterId, particleTypeId);
	}
	public double pixelpart_spawn_particles(String runtimePtr, double particleEmitterId, double particleTypeId, double count) {
		return JNIpixelpartspawnparticles(runtimePtr, particleEmitterId, particleTypeId, count);
	}

	// Resources
	public double pixelpart_get_image_resource_count(String runtimePtr) {
		return JNIpixelpartgetimageresourcecount(runtimePtr);
	}
	public String pixelpart_get_image_resource_id(String runtimePtr, double index) {
		return JNIpixelpartgetimageresourceid(runtimePtr, index);
	}
	public double pixelpart_get_image_resource_width(String runtimePtr, String resourceId) {
		return JNIpixelpartgetimageresourcewidth(runtimePtr, resourceId);
	}
	public double pixelpart_get_image_resource_height(String runtimePtr, String resourceId) {
		return JNIpixelpartgetimageresourceheight(runtimePtr, resourceId);
	}
	public double pixelpart_get_image_resource_channels(String runtimePtr, String resourceId) {
		return JNIpixelpartgetimageresourcechannels(runtimePtr, resourceId);
	}
	public double pixelpart_get_image_resource_color_space(String runtimePtr, String resourceId) {
		return JNIpixelpartgetimageresourcecolorspace(runtimePtr, resourceId);
	}
	public double pixelpart_get_image_resource_data_size(String runtimePtr, String resourceId) {
		return JNIpixelpartgetimageresourcedatasize(runtimePtr, resourceId);
	}
	public double pixelpart_get_image_resource_data(String runtimePtr, String resourceId, ByteBuffer imageDataBufferPtr) {
		return JNIpixelpartgetimageresourcedata(runtimePtr, resourceId, imageDataBufferPtr);
	}

	// Rendering
	public double pixelpart_get_sorted_particle_runtime_instances(String runtimePtr, ByteBuffer indexBufferPtr) {
		return JNIpixelpartgetsortedparticleruntimeinstances(runtimePtr, indexBufferPtr);
	}
	public double pixelpart_construct_particle_geometry(String runtimePtr, double particleEmitterId, double particleTypeId, ByteBuffer bufferSizeBufferPtr) {
		return JNIpixelpartconstructparticlegeometry(runtimePtr, particleEmitterId, particleTypeId, bufferSizeBufferPtr);
	}
	public double pixelpart_generate_particle_vertex_data(String runtimePtr, double particleEmitterId, double particleTypeId, ByteBuffer vertexBufferPtr) {
		return JNIpixelpartgenerateparticlevertexdata(runtimePtr, particleEmitterId, particleTypeId, vertexBufferPtr);
	}

	// Built-in material
	public double pixelpart_get_builtin_material_parameter_count(String materialName) {
		return JNIpixelpartgetbuiltinmaterialparametercount(materialName);
	}
	public double pixelpart_get_builtin_material_parameters(String materialName, ByteBuffer idBufferPtr, ByteBuffer nameBufferPtr) {
		return JNIpixelpartgetbuiltinmaterialparameters(materialName, idBufferPtr, nameBufferPtr);
	}

	// Effect input
	public double pixelpart_get_effect_input_count(String runtimePtr) {
		return JNIpixelpartgeteffectinputcount(runtimePtr);
	}
	public double pixelpart_get_effect_inputs(String runtimePtr, ByteBuffer idBufferPtr, ByteBuffer typeBufferPtr, ByteBuffer nameBufferPtr) {
		return JNIpixelpartgeteffectinputs(runtimePtr, idBufferPtr, typeBufferPtr, nameBufferPtr);
	}
	public double pixelpart_set_effect_input_bool(String runtimePtr, double inputId, double value) {
		return JNIpixelpartseteffectinputbool(runtimePtr, inputId, value);
	}
	public double pixelpart_set_effect_input_int(String runtimePtr, double inputId, double value) {
		return JNIpixelpartseteffectinputint(runtimePtr, inputId, value);
	}
	public double pixelpart_set_effect_input_float(String runtimePtr, double inputId, double value) {
		return JNIpixelpartseteffectinputfloat(runtimePtr, inputId, value);
	}
	public double pixelpart_set_effect_input_float2(String runtimePtr, double inputId, ByteBuffer valueBufferPtr) {
		return JNIpixelpartseteffectinputfloat2(runtimePtr, inputId, valueBufferPtr);
	}
	public double pixelpart_set_effect_input_float3(String runtimePtr, double inputId, ByteBuffer valueBufferPtr) {
		return JNIpixelpartseteffectinputfloat3(runtimePtr, inputId, valueBufferPtr);
	}
	public double pixelpart_set_effect_input_float4(String runtimePtr, double inputId, ByteBuffer valueBufferPtr) {
		return JNIpixelpartseteffectinputfloat4(runtimePtr, inputId, valueBufferPtr);
	}
	public double pixelpart_get_effect_input_bool(String runtimePtr, double inputId) {
		return JNIpixelpartgeteffectinputbool(runtimePtr, inputId);
	}
	public double pixelpart_get_effect_input_int(String runtimePtr, double inputId) {
		return JNIpixelpartgeteffectinputint(runtimePtr, inputId);
	}
	public double pixelpart_get_effect_input_float(String runtimePtr, double inputId) {
		return JNIpixelpartgeteffectinputfloat(runtimePtr, inputId);
	}
	public double pixelpart_get_effect_input_float2(String runtimePtr, double inputId, ByteBuffer valueBufferPtr) {
		return JNIpixelpartgeteffectinputfloat2(runtimePtr, inputId, valueBufferPtr);
	}
	public double pixelpart_get_effect_input_float3(String runtimePtr, double inputId, ByteBuffer valueBufferPtr) {
		return JNIpixelpartgeteffectinputfloat3(runtimePtr, inputId, valueBufferPtr);
	}
	public double pixelpart_get_effect_input_float4(String runtimePtr, double inputId, ByteBuffer valueBufferPtr) {
		return JNIpixelpartgeteffectinputfloat4(runtimePtr, inputId, valueBufferPtr);
	}

	// Effect trigger
	public double pixelpart_get_effect_trigger_count(String runtimePtr) {
		return JNIpixelpartgeteffecttriggercount(runtimePtr);
	}
	public double pixelpart_get_effect_triggers(String runtimePtr, ByteBuffer idBufferPtr, ByteBuffer nameBufferPtr) {
		return JNIpixelpartgeteffecttriggers(runtimePtr, idBufferPtr, nameBufferPtr);
	}
	public double pixelpart_activate_effect_trigger(String runtimePtr, double triggerId) {
		return JNIpixelpartactivateeffecttrigger(runtimePtr, triggerId);
	}
	public double pixelpart_is_effect_trigger_activated(String runtimePtr, double triggerId) {
		return JNIpixelpartiseffecttriggeractivated(runtimePtr, triggerId);
	}

	// Effect event
	public double pixelpart_get_effect_event_count(String runtimePtr) {
		return JNIpixelpartgeteffecteventcount(runtimePtr);
	}
	public double pixelpart_get_effect_events(String runtimePtr, ByteBuffer idBufferPtr, ByteBuffer nameBufferPtr) {
		return JNIpixelpartgeteffectevents(runtimePtr, idBufferPtr, nameBufferPtr);
	}
	public double pixelpart_get_invoked_effect_events(String runtimePtr, ByteBuffer idBufferPtr) {
		return JNIpixelpartgetinvokedeffectevents(runtimePtr, idBufferPtr);
	}

	// Node
	public double pixelpart_find_node(String runtimePtr, String name) {
		return JNIpixelpartfindnode(runtimePtr, name);
	}
	public double pixelpart_find_node_by_index(String runtimePtr, double nodeIndex) {
		return JNIpixelpartfindnodebyindex(runtimePtr, nodeIndex);
	}
	public double pixelpart_node_exists(String runtimePtr, double nodeId) {
		return JNIpixelpartnodeexists(runtimePtr, nodeId);
	}
	public double pixelpart_node_get_type(String runtimePtr, double nodeId) {
		return JNIpixelpartnodegettype(runtimePtr, nodeId);
	}
	public String pixelpart_node_get_name(String runtimePtr, double nodeId) {
		return JNIpixelpartnodegetname(runtimePtr, nodeId);
	}
	public double pixelpart_node_get_parent_id(String runtimePtr, double nodeId) {
		return JNIpixelpartnodegetparentid(runtimePtr, nodeId);
	}
	public double pixelpart_node_set_start(String runtimePtr, double nodeId, double value) {
		return JNIpixelpartnodesetstart(runtimePtr, nodeId, value);
	}
	public double pixelpart_node_set_duration(String runtimePtr, double nodeId, double value) {
		return JNIpixelpartnodesetduration(runtimePtr, nodeId, value);
	}
	public double pixelpart_node_set_repeat(String runtimePtr, double nodeId, double value) {
		return JNIpixelpartnodesetrepeat(runtimePtr, nodeId, value);
	}
	public double pixelpart_node_get_start(String runtimePtr, double nodeId) {
		return JNIpixelpartnodegetstart(runtimePtr, nodeId);
	}
	public double pixelpart_node_get_duration(String runtimePtr, double nodeId) {
		return JNIpixelpartnodegetduration(runtimePtr, nodeId);
	}
	public double pixelpart_node_is_repeating(String runtimePtr, double nodeId) {
		return JNIpixelpartnodeisrepeating(runtimePtr, nodeId);
	}
	public double pixelpart_node_is_active(String runtimePtr, double nodeId) {
		return JNIpixelpartnodeisactive(runtimePtr, nodeId);
	}
	public double pixelpart_node_get_local_time(String runtimePtr, double nodeId) {
		return JNIpixelpartnodegetlocaltime(runtimePtr, nodeId);
	}
	public String pixelpart_node_get_position(String runtimePtr, double nodeId) {
		return JNIpixelpartnodegetposition(runtimePtr, nodeId);
	}
	public String pixelpart_node_get_rotation(String runtimePtr, double nodeId) {
		return JNIpixelpartnodegetrotation(runtimePtr, nodeId);
	}
	public String pixelpart_node_get_scale(String runtimePtr, double nodeId) {
		return JNIpixelpartnodegetscale(runtimePtr, nodeId);
	}

	// Particle emitter
	public double pixelpart_particle_emitter_set_shape(String runtimePtr, double emitterId, double shape) {
		return JNIpixelpartparticleemittersetshape(runtimePtr, emitterId, shape);
	}
	public double pixelpart_particle_emitter_get_shape(String runtimePtr, double emitterId) {
		return JNIpixelpartparticleemittergetshape(runtimePtr, emitterId);
	}
	public double pixelpart_particle_emitter_add_shape_point(String runtimePtr, double emitterId, ByteBuffer valueBufferPtr) {
		return JNIpixelpartparticleemitteraddshapepoint(runtimePtr, emitterId, valueBufferPtr);
	}
	public double pixelpart_particle_emitter_remove_shape_point(String runtimePtr, double emitterId, double index) {
		return JNIpixelpartparticleemitterremoveshapepoint(runtimePtr, emitterId, index);
	}
	public double pixelpart_particle_emitter_set_shape_point(String runtimePtr, double emitterId, double index, ByteBuffer valueBufferPtr) {
		return JNIpixelpartparticleemittersetshapepoint(runtimePtr, emitterId, index, valueBufferPtr);
	}
	public double pixelpart_particle_emitter_get_shape_point(String runtimePtr, double emitterId, double index, ByteBuffer valueBufferPtr) {
		return JNIpixelpartparticleemittergetshapepoint(runtimePtr, emitterId, index, valueBufferPtr);
	}
	public double pixelpart_particle_emitter_get_shape_point_count(String runtimePtr, double emitterId) {
		return JNIpixelpartparticleemittergetshapepointcount(runtimePtr, emitterId);
	}
	public double pixelpart_particle_emitter_set_distribution(String runtimePtr, double emitterId, double mode) {
		return JNIpixelpartparticleemittersetdistribution(runtimePtr, emitterId, mode);
	}
	public double pixelpart_particle_emitter_get_distribution(String runtimePtr, double emitterId) {
		return JNIpixelpartparticleemittergetdistribution(runtimePtr, emitterId);
	}
	public double pixelpart_particle_emitter_set_grid_order(String runtimePtr, double emitterId, double mode) {
		return JNIpixelpartparticleemittersetgridorder(runtimePtr, emitterId, mode);
	}
	public double pixelpart_particle_emitter_get_grid_order(String runtimePtr, double emitterId) {
		return JNIpixelpartparticleemittergetgridorder(runtimePtr, emitterId);
	}
	public double pixelpart_particle_emitter_set_grid_size(String runtimePtr, double emitterId, ByteBuffer valueBufferPtr) {
		return JNIpixelpartparticleemittersetgridsize(runtimePtr, emitterId, valueBufferPtr);
	}
	public double pixelpart_particle_emitter_get_grid_size_x(String runtimePtr, double emitterId) {
		return JNIpixelpartparticleemittergetgridsizex(runtimePtr, emitterId);
	}
	public double pixelpart_particle_emitter_get_grid_size_y(String runtimePtr, double emitterId) {
		return JNIpixelpartparticleemittergetgridsizey(runtimePtr, emitterId);
	}
	public double pixelpart_particle_emitter_get_grid_size_z(String runtimePtr, double emitterId) {
		return JNIpixelpartparticleemittergetgridsizez(runtimePtr, emitterId);
	}
	public double pixelpart_particle_emitter_set_emission_mode(String runtimePtr, double emitterId, double mode) {
		return JNIpixelpartparticleemittersetemissionmode(runtimePtr, emitterId, mode);
	}
	public double pixelpart_particle_emitter_get_emission_mode(String runtimePtr, double emitterId) {
		return JNIpixelpartparticleemittergetemissionmode(runtimePtr, emitterId);
	}
	public double pixelpart_particle_emitter_set_direction_mode(String runtimePtr, double emitterId, double mode) {
		return JNIpixelpartparticleemittersetdirectionmode(runtimePtr, emitterId, mode);
	}
	public double pixelpart_particle_emitter_get_direction_mode(String runtimePtr, double emitterId) {
		return JNIpixelpartparticleemittergetdirectionmode(runtimePtr, emitterId);
	}
	public String pixelpart_particle_emitter_get_direction(String runtimePtr, double emitterId) {
		return JNIpixelpartparticleemittergetdirection(runtimePtr, emitterId);
	}
	public String pixelpart_particle_emitter_get_spread(String runtimePtr, double emitterId) {
		return JNIpixelpartparticleemittergetspread(runtimePtr, emitterId);
	}

	// Force field
	public double pixelpart_force_field_set_infinite(String runtimePtr, double forceFieldId, double mode) {
		return JNIpixelpartforcefieldsetinfinite(runtimePtr, forceFieldId, mode);
	}
	public double pixelpart_force_field_is_infinite(String runtimePtr, double forceFieldId) {
		return JNIpixelpartforcefieldisinfinite(runtimePtr, forceFieldId);
	}
	public String pixelpart_force_field_get_strength(String runtimePtr, double forceFieldId) {
		return JNIpixelpartforcefieldgetstrength(runtimePtr, forceFieldId);
	}
	public String pixelpart_attraction_field_get_falloff_power(String runtimePtr, double forceFieldId) {
		return JNIpixelpartattractionfieldgetfalloffpower(runtimePtr, forceFieldId);
	}
	public String pixelpart_acceleration_field_get_acceleration_direction(String runtimePtr, double forceFieldId) {
		return JNIpixelpartaccelerationfieldgetaccelerationdirection(runtimePtr, forceFieldId);
	}
	public String pixelpart_acceleration_field_get_acceleration_direction_variance(String runtimePtr, double forceFieldId) {
		return JNIpixelpartaccelerationfieldgetaccelerationdirectionvariance(runtimePtr, forceFieldId);
	}
	public String pixelpart_acceleration_field_get_acceleration_strength_variance(String runtimePtr, double forceFieldId) {
		return JNIpixelpartaccelerationfieldgetaccelerationstrengthvariance(runtimePtr, forceFieldId);
	}
	public double pixelpart_acceleration_field_set_acceleration_grid_size(String runtimePtr, double forceFieldId, ByteBuffer valueBufferPtr) {
		return JNIpixelpartaccelerationfieldsetaccelerationgridsize(runtimePtr, forceFieldId, valueBufferPtr);
	}
	public double pixelpart_acceleration_field_get_acceleration_grid_size_x(String runtimePtr, double forceFieldId) {
		return JNIpixelpartaccelerationfieldgetaccelerationgridsizex(runtimePtr, forceFieldId);
	}
	public double pixelpart_acceleration_field_get_acceleration_grid_size_y(String runtimePtr, double forceFieldId) {
		return JNIpixelpartaccelerationfieldgetaccelerationgridsizey(runtimePtr, forceFieldId);
	}
	public double pixelpart_acceleration_field_get_acceleration_grid_size_z(String runtimePtr, double forceFieldId) {
		return JNIpixelpartaccelerationfieldgetaccelerationgridsizez(runtimePtr, forceFieldId);
	}
	public double pixelpart_vector_field_set_vector_field_filter(String runtimePtr, double forceFieldId, double filter) {
		return JNIpixelpartvectorfieldsetvectorfieldfilter(runtimePtr, forceFieldId, filter);
	}
	public double pixelpart_vector_field_get_vector_field_filter(String runtimePtr, double forceFieldId) {
		return JNIpixelpartvectorfieldgetvectorfieldfilter(runtimePtr, forceFieldId);
	}
	public String pixelpart_vector_field_get_tightness(String runtimePtr, double forceFieldId) {
		return JNIpixelpartvectorfieldgettightness(runtimePtr, forceFieldId);
	}
	public String pixelpart_noise_field_get_noise_octaves(String runtimePtr, double forceFieldId) {
		return JNIpixelpartnoisefieldgetnoiseoctaves(runtimePtr, forceFieldId);
	}
	public String pixelpart_noise_field_get_noise_frequency(String runtimePtr, double forceFieldId) {
		return JNIpixelpartnoisefieldgetnoisefrequency(runtimePtr, forceFieldId);
	}
	public String pixelpart_noise_field_get_noise_persistence(String runtimePtr, double forceFieldId) {
		return JNIpixelpartnoisefieldgetnoisepersistence(runtimePtr, forceFieldId);
	}
	public String pixelpart_noise_field_get_noise_lacunarity(String runtimePtr, double forceFieldId) {
		return JNIpixelpartnoisefieldgetnoiselacunarity(runtimePtr, forceFieldId);
	}
	public double pixelpart_noise_field_set_noise_animated(String runtimePtr, double forceFieldId, double animated) {
		return JNIpixelpartnoisefieldsetnoiseanimated(runtimePtr, forceFieldId, animated);
	}
	public double pixelpart_noise_field_is_noise_animated(String runtimePtr, double forceFieldId) {
		return JNIpixelpartnoisefieldisnoiseanimated(runtimePtr, forceFieldId);
	}
	public String pixelpart_noise_field_get_noise_animation_time_scale(String runtimePtr, double forceFieldId) {
		return JNIpixelpartnoisefieldgetnoiseanimationtimescale(runtimePtr, forceFieldId);
	}
	public String pixelpart_noise_field_get_noise_animation_time_base(String runtimePtr, double forceFieldId) {
		return JNIpixelpartnoisefieldgetnoiseanimationtimebase(runtimePtr, forceFieldId);
	}
	public String pixelpart_drag_field_get_velocity_influence(String runtimePtr, double forceFieldId) {
		return JNIpixelpartdragfieldgetvelocityinfluence(runtimePtr, forceFieldId);
	}
	public String pixelpart_drag_field_get_size_influence(String runtimePtr, double forceFieldId) {
		return JNIpixelpartdragfieldgetsizeinfluence(runtimePtr, forceFieldId);
	}

	// Collider
	public String pixelpart_collider_get_kill_on_contact(String runtimePtr, double colliderId) {
		return JNIpixelpartcollidergetkilloncontact(runtimePtr, colliderId);
	}
	public String pixelpart_collider_get_bounce(String runtimePtr, double colliderId) {
		return JNIpixelpartcollidergetbounce(runtimePtr, colliderId);
	}
	public String pixelpart_collider_get_friction(String runtimePtr, double colliderId) {
		return JNIpixelpartcollidergetfriction(runtimePtr, colliderId);
	}
	public double pixelpart_line_collider_add_point(String runtimePtr, double colliderId, ByteBuffer valueBufferPtr) {
		return JNIpixelpartlinecollideraddpoint(runtimePtr, colliderId, valueBufferPtr);
	}
	public double pixelpart_line_collider_set_point(String runtimePtr, double colliderId, double index, ByteBuffer valueBufferPtr) {
		return JNIpixelpartlinecollidersetpoint(runtimePtr, colliderId, index, valueBufferPtr);
	}
	public double pixelpart_line_collider_remove_point(String runtimePtr, double colliderId, double index) {
		return JNIpixelpartlinecolliderremovepoint(runtimePtr, colliderId, index);
	}
	public double pixelpart_line_collider_get_point(String runtimePtr, double colliderId, double index, ByteBuffer valueBufferPtr) {
		return JNIpixelpartlinecollidergetpoint(runtimePtr, colliderId, index, valueBufferPtr);
	}
	public double pixelpart_line_collider_get_point_count(String runtimePtr, double colliderId) {
		return JNIpixelpartlinecollidergetpointcount(runtimePtr, colliderId);
	}

	// Light source
	public String pixelpart_light_source_get_attenuation(String runtimePtr, double lightSourceId) {
		return JNIpixelpartlightsourcegetattenuation(runtimePtr, lightSourceId);
	}
	public String pixelpart_light_source_get_color(String runtimePtr, double lightSourceId) {
		return JNIpixelpartlightsourcegetcolor(runtimePtr, lightSourceId);
	}
	public String pixelpart_light_source_get_intensity(String runtimePtr, double lightSourceId) {
		return JNIpixelpartlightsourcegetintensity(runtimePtr, lightSourceId);
	}
	public String pixelpart_spot_light_source_get_spot_angle(String runtimePtr, double lightSourceId) {
		return JNIpixelpartspotlightsourcegetspotangle(runtimePtr, lightSourceId);
	}
	public String pixelpart_spot_light_source_get_spot_angle_attenuation(String runtimePtr, double lightSourceId) {
		return JNIpixelpartspotlightsourcegetspotangleattenuation(runtimePtr, lightSourceId);
	}

	// Particle type
	public double pixelpart_find_particle_type(String runtimePtr, String name) {
		return JNIpixelpartfindparticletype(runtimePtr, name);
	}
	public double pixelpart_find_particle_type_by_index(String runtimePtr, double particleTypeIndex) {
		return JNIpixelpartfindparticletypebyindex(runtimePtr, particleTypeIndex);
	}
	public double pixelpart_particle_type_exists(String runtimePtr, double particleTypeId) {
		return JNIpixelpartparticletypeexists(runtimePtr, particleTypeId);
	}
	public double pixelpart_particle_type_get_index(String runtimePtr, double particleTypeId) {
		return JNIpixelpartparticletypegetindex(runtimePtr, particleTypeId);
	}
	public double pixelpart_particle_type_get_parent_id(String runtimePtr, double particleTypeId) {
		return JNIpixelpartparticletypegetparentid(runtimePtr, particleTypeId);
	}
	public String pixelpart_particle_type_get_name(String runtimePtr, double particleTypeId) {
		return JNIpixelpartparticletypegetname(runtimePtr, particleTypeId);
	}
	public double pixelpart_particle_type_set_position_relative(String runtimePtr, double particleTypeId, double relative) {
		return JNIpixelpartparticletypesetpositionrelative(runtimePtr, particleTypeId, relative);
	}
	public double pixelpart_particle_type_is_position_relative(String runtimePtr, double particleTypeId) {
		return JNIpixelpartparticletypeispositionrelative(runtimePtr, particleTypeId);
	}
	public double pixelpart_particle_type_set_rotation_mode(String runtimePtr, double particleTypeId, double mode) {
		return JNIpixelpartparticletypesetrotationmode(runtimePtr, particleTypeId, mode);
	}
	public double pixelpart_particle_type_get_rotation_mode(String runtimePtr, double particleTypeId) {
		return JNIpixelpartparticletypegetrotationmode(runtimePtr, particleTypeId);
	}
	public double pixelpart_particle_type_set_alignment_mode(String runtimePtr, double particleTypeId, double mode) {
		return JNIpixelpartparticletypesetalignmentmode(runtimePtr, particleTypeId, mode);
	}
	public double pixelpart_particle_type_get_alignment_mode(String runtimePtr, double particleTypeId) {
		return JNIpixelpartparticletypegetalignmentmode(runtimePtr, particleTypeId);
	}
	public String pixelpart_particle_type_get_pivot(String runtimePtr, double particleTypeId) {
		return JNIpixelpartparticletypegetpivot(runtimePtr, particleTypeId);
	}
	public String pixelpart_particle_type_get_motion_path_force(String runtimePtr, double particleTypeId) {
		return JNIpixelpartparticletypegetmotionpathforce(runtimePtr, particleTypeId);
	}
	public double pixelpart_particle_type_set_visible(String runtimePtr, double particleTypeId, double visible) {
		return JNIpixelpartparticletypesetvisible(runtimePtr, particleTypeId, visible);
	}
	public double pixelpart_particle_type_is_visible(String runtimePtr, double particleTypeId) {
		return JNIpixelpartparticletypeisvisible(runtimePtr, particleTypeId);
	}
	public double pixelpart_particle_type_set_layer(String runtimePtr, double particleTypeId, double layer) {
		return JNIpixelpartparticletypesetlayer(runtimePtr, particleTypeId, layer);
	}
	public double pixelpart_particle_type_get_layer(String runtimePtr, double particleTypeId) {
		return JNIpixelpartparticletypegetlayer(runtimePtr, particleTypeId);
	}
	public String pixelpart_particle_type_get_material_id(String runtimePtr, double particleTypeId) {
		return JNIpixelpartparticletypegetmaterialid(runtimePtr, particleTypeId);
	}
	public double pixelpart_particle_type_is_material_builtin(String runtimePtr, double particleTypeId) {
		return JNIpixelpartparticletypeismaterialbuiltin(runtimePtr, particleTypeId);
	}
	public double pixelpart_particle_type_get_material_parameter_count(String runtimePtr, double particleTypeId) {
		return JNIpixelpartparticletypegetmaterialparametercount(runtimePtr, particleTypeId);
	}
	public double pixelpart_particle_type_get_material_parameter_ids(String runtimePtr, double particleTypeId, ByteBuffer parameterIdBufferPtr) {
		return JNIpixelpartparticletypegetmaterialparameterids(runtimePtr, particleTypeId, parameterIdBufferPtr);
	}
	public double pixelpart_particle_type_get_material_parameter_type(String runtimePtr, double particleTypeId, double parameterId) {
		return JNIpixelpartparticletypegetmaterialparametertype(runtimePtr, particleTypeId, parameterId);
	}
	public double pixelpart_particle_type_get_material_parameter_value(String runtimePtr, double particleTypeId, double parameterId, ByteBuffer resultBufferPtr) {
		return JNIpixelpartparticletypegetmaterialparametervalue(runtimePtr, particleTypeId, parameterId, resultBufferPtr);
	}
	public double pixelpart_particle_type_get_renderer(String runtimePtr, double particleTypeId) {
		return JNIpixelpartparticletypegetrenderer(runtimePtr, particleTypeId);
	}
	public String pixelpart_particle_type_get_mesh_renderer_mesh_resource_id(String runtimePtr, double particleTypeId) {
		return JNIpixelpartparticletypegetmeshrenderermeshresourceid(runtimePtr, particleTypeId);
	}
	public String pixelpart_particle_type_get_count(String runtimePtr, double particleTypeId) {
		return JNIpixelpartparticletypegetcount(runtimePtr, particleTypeId);
	}
	public String pixelpart_particle_type_get_lifespan(String runtimePtr, double particleTypeId) {
		return JNIpixelpartparticletypegetlifespan(runtimePtr, particleTypeId);
	}
	public String pixelpart_particle_type_get_initial_size(String runtimePtr, double particleTypeId) {
		return JNIpixelpartparticletypegetinitialsize(runtimePtr, particleTypeId);
	}
	public String pixelpart_particle_type_get_initial_rotation(String runtimePtr, double particleTypeId) {
		return JNIpixelpartparticletypegetinitialrotation(runtimePtr, particleTypeId);
	}
	public String pixelpart_particle_type_get_initial_velocity(String runtimePtr, double particleTypeId) {
		return JNIpixelpartparticletypegetinitialvelocity(runtimePtr, particleTypeId);
	}
	public String pixelpart_particle_type_get_inherited_velocity(String runtimePtr, double particleTypeId) {
		return JNIpixelpartparticletypegetinheritedvelocity(runtimePtr, particleTypeId);
	}
	public String pixelpart_particle_type_get_initial_opacity(String runtimePtr, double particleTypeId) {
		return JNIpixelpartparticletypegetinitialopacity(runtimePtr, particleTypeId);
	}
	public String pixelpart_particle_type_get_motion_path(String runtimePtr, double particleTypeId) {
		return JNIpixelpartparticletypegetmotionpath(runtimePtr, particleTypeId);
	}
	public String pixelpart_particle_type_get_size(String runtimePtr, double particleTypeId) {
		return JNIpixelpartparticletypegetsize(runtimePtr, particleTypeId);
	}
	public String pixelpart_particle_type_get_stretch(String runtimePtr, double particleTypeId) {
		return JNIpixelpartparticletypegetstretch(runtimePtr, particleTypeId);
	}
	public String pixelpart_particle_type_get_physical_size(String runtimePtr, double particleTypeId) {
		return JNIpixelpartparticletypegetphysicalsize(runtimePtr, particleTypeId);
	}
	public String pixelpart_particle_type_get_rotation(String runtimePtr, double particleTypeId) {
		return JNIpixelpartparticletypegetrotation(runtimePtr, particleTypeId);
	}
	public String pixelpart_particle_type_get_rotation_by_speed(String runtimePtr, double particleTypeId) {
		return JNIpixelpartparticletypegetrotationbyspeed(runtimePtr, particleTypeId);
	}
	public String pixelpart_particle_type_get_acceleration(String runtimePtr, double particleTypeId) {
		return JNIpixelpartparticletypegetacceleration(runtimePtr, particleTypeId);
	}
	public String pixelpart_particle_type_get_radial_acceleration(String runtimePtr, double particleTypeId) {
		return JNIpixelpartparticletypegetradialacceleration(runtimePtr, particleTypeId);
	}
	public String pixelpart_particle_type_get_weight(String runtimePtr, double particleTypeId) {
		return JNIpixelpartparticletypegetweight(runtimePtr, particleTypeId);
	}
	public String pixelpart_particle_type_get_bounce(String runtimePtr, double particleTypeId) {
		return JNIpixelpartparticletypegetbounce(runtimePtr, particleTypeId);
	}
	public String pixelpart_particle_type_get_friction(String runtimePtr, double particleTypeId) {
		return JNIpixelpartparticletypegetfriction(runtimePtr, particleTypeId);
	}
	public String pixelpart_particle_type_get_color(String runtimePtr, double particleTypeId) {
		return JNIpixelpartparticletypegetcolor(runtimePtr, particleTypeId);
	}
	public String pixelpart_particle_type_get_opacity(String runtimePtr, double particleTypeId) {
		return JNIpixelpartparticletypegetopacity(runtimePtr, particleTypeId);
	}
	public String pixelpart_particle_type_get_lifespan_variance(String runtimePtr, double particleTypeId) {
		return JNIpixelpartparticletypegetlifespanvariance(runtimePtr, particleTypeId);
	}
	public String pixelpart_particle_type_get_size_variance(String runtimePtr, double particleTypeId) {
		return JNIpixelpartparticletypegetsizevariance(runtimePtr, particleTypeId);
	}
	public String pixelpart_particle_type_get_rotation_variance(String runtimePtr, double particleTypeId) {
		return JNIpixelpartparticletypegetrotationvariance(runtimePtr, particleTypeId);
	}
	public String pixelpart_particle_type_get_angular_velocity_variance(String runtimePtr, double particleTypeId) {
		return JNIpixelpartparticletypegetangularvelocityvariance(runtimePtr, particleTypeId);
	}
	public String pixelpart_particle_type_get_velocity_variance(String runtimePtr, double particleTypeId) {
		return JNIpixelpartparticletypegetvelocityvariance(runtimePtr, particleTypeId);
	}
	public String pixelpart_particle_type_get_color_variance(String runtimePtr, double particleTypeId) {
		return JNIpixelpartparticletypegetcolorvariance(runtimePtr, particleTypeId);
	}
	public String pixelpart_particle_type_get_opacity_variance(String runtimePtr, double particleTypeId) {
		return JNIpixelpartparticletypegetopacityvariance(runtimePtr, particleTypeId);
	}

	// Static property
	public double pixelpart_static_property_bool_value(String propertyPtr) {
		return JNIpixelpartstaticpropertyboolvalue(propertyPtr);
	}
	public double pixelpart_static_property_bool_set_base_value(String propertyPtr, double value) {
		return JNIpixelpartstaticpropertyboolsetbasevalue(propertyPtr, value);
	}
	public double pixelpart_static_property_bool_get_base_value(String propertyPtr) {
		return JNIpixelpartstaticpropertyboolgetbasevalue(propertyPtr);
	}
	public double pixelpart_static_property_int_value(String propertyPtr) {
		return JNIpixelpartstaticpropertyintvalue(propertyPtr);
	}
	public double pixelpart_static_property_int_set_base_value(String propertyPtr, double value) {
		return JNIpixelpartstaticpropertyintsetbasevalue(propertyPtr, value);
	}
	public double pixelpart_static_property_int_get_base_value(String propertyPtr) {
		return JNIpixelpartstaticpropertyintgetbasevalue(propertyPtr);
	}
	public double pixelpart_static_property_float_value(String propertyPtr) {
		return JNIpixelpartstaticpropertyfloatvalue(propertyPtr);
	}
	public double pixelpart_static_property_float_set_base_value(String propertyPtr, double value) {
		return JNIpixelpartstaticpropertyfloatsetbasevalue(propertyPtr, value);
	}
	public double pixelpart_static_property_float_get_base_value(String propertyPtr) {
		return JNIpixelpartstaticpropertyfloatgetbasevalue(propertyPtr);
	}
	public double pixelpart_static_property_float2_value(String propertyPtr, ByteBuffer valueBufferPtr) {
		return JNIpixelpartstaticpropertyfloat2value(propertyPtr, valueBufferPtr);
	}
	public double pixelpart_static_property_float2_set_base_value(String propertyPtr, ByteBuffer valueBufferPtr) {
		return JNIpixelpartstaticpropertyfloat2setbasevalue(propertyPtr, valueBufferPtr);
	}
	public double pixelpart_static_property_float2_get_base_value(String propertyPtr, ByteBuffer valueBufferPtr) {
		return JNIpixelpartstaticpropertyfloat2getbasevalue(propertyPtr, valueBufferPtr);
	}
	public double pixelpart_static_property_float3_value(String propertyPtr, ByteBuffer valueBufferPtr) {
		return JNIpixelpartstaticpropertyfloat3value(propertyPtr, valueBufferPtr);
	}
	public double pixelpart_static_property_float3_set_base_value(String propertyPtr, ByteBuffer valueBufferPtr) {
		return JNIpixelpartstaticpropertyfloat3setbasevalue(propertyPtr, valueBufferPtr);
	}
	public double pixelpart_static_property_float3_get_base_value(String propertyPtr, ByteBuffer valueBufferPtr) {
		return JNIpixelpartstaticpropertyfloat3getbasevalue(propertyPtr, valueBufferPtr);
	}
	public double pixelpart_static_property_float4_value(String propertyPtr, ByteBuffer valueBufferPtr) {
		return JNIpixelpartstaticpropertyfloat4value(propertyPtr, valueBufferPtr);
	}
	public double pixelpart_static_property_float4_set_base_value(String propertyPtr, ByteBuffer valueBufferPtr) {
		return JNIpixelpartstaticpropertyfloat4setbasevalue(propertyPtr, valueBufferPtr);
	}
	public double pixelpart_static_property_float4_get_base_value(String propertyPtr, ByteBuffer valueBufferPtr) {
		return JNIpixelpartstaticpropertyfloat4getbasevalue(propertyPtr, valueBufferPtr);
	}

	// Animated property
	public double pixelpart_animated_property_float_at(String propertyPtr, double position) {
		return JNIpixelpartanimatedpropertyfloatat(propertyPtr, position);
	}
	public double pixelpart_animated_property_float_add_keyframe(String propertyPtr, double position, double value) {
		return JNIpixelpartanimatedpropertyfloataddkeyframe(propertyPtr, position, value);
	}
	public double pixelpart_animated_property_float_remove_keyframe(String propertyPtr, double index) {
		return JNIpixelpartanimatedpropertyfloatremovekeyframe(propertyPtr, index);
	}
	public double pixelpart_animated_property_float_set_keyframe_value(String propertyPtr, double index, double value) {
		return JNIpixelpartanimatedpropertyfloatsetkeyframevalue(propertyPtr, index, value);
	}
	public double pixelpart_animated_property_float_set_keyframe_position(String propertyPtr, double index, double position) {
		return JNIpixelpartanimatedpropertyfloatsetkeyframeposition(propertyPtr, index, position);
	}
	public double pixelpart_animated_property_float_clear_keyframes(String propertyPtr) {
		return JNIpixelpartanimatedpropertyfloatclearkeyframes(propertyPtr);
	}
	public double pixelpart_animated_property_float_keyframe_count(String propertyPtr) {
		return JNIpixelpartanimatedpropertyfloatkeyframecount(propertyPtr);
	}
	public double pixelpart_animated_property_float_keyframe_value(String propertyPtr, double index) {
		return JNIpixelpartanimatedpropertyfloatkeyframevalue(propertyPtr, index);
	}
	public double pixelpart_animated_property_float_keyframe_index(String propertyPtr, double position, double epsilon) {
		return JNIpixelpartanimatedpropertyfloatkeyframeindex(propertyPtr, position, epsilon);
	}
	public double pixelpart_animated_property_float_set_keyframe_interpolation(String propertyPtr, double method) {
		return JNIpixelpartanimatedpropertyfloatsetkeyframeinterpolation(propertyPtr, method);
	}
	public double pixelpart_animated_property_float_get_keyframe_interpolation(String propertyPtr) {
		return JNIpixelpartanimatedpropertyfloatgetkeyframeinterpolation(propertyPtr);
	}
	public double pixelpart_animated_property_float2_at(String propertyPtr, double position, ByteBuffer valueBufferPtr) {
		return JNIpixelpartanimatedpropertyfloat2at(propertyPtr, position, valueBufferPtr);
	}
	public double pixelpart_animated_property_float2_add_keyframe(String propertyPtr, double position, ByteBuffer valueBufferPtr) {
		return JNIpixelpartanimatedpropertyfloat2addkeyframe(propertyPtr, position, valueBufferPtr);
	}
	public double pixelpart_animated_property_float2_remove_keyframe(String propertyPtr, double index) {
		return JNIpixelpartanimatedpropertyfloat2removekeyframe(propertyPtr, index);
	}
	public double pixelpart_animated_property_float2_set_keyframe_value(String propertyPtr, double index, ByteBuffer valueBufferPtr) {
		return JNIpixelpartanimatedpropertyfloat2setkeyframevalue(propertyPtr, index, valueBufferPtr);
	}
	public double pixelpart_animated_property_float2_set_keyframe_position(String propertyPtr, double index, double position) {
		return JNIpixelpartanimatedpropertyfloat2setkeyframeposition(propertyPtr, index, position);
	}
	public double pixelpart_animated_property_float2_clear_keyframes(String propertyPtr) {
		return JNIpixelpartanimatedpropertyfloat2clearkeyframes(propertyPtr);
	}
	public double pixelpart_animated_property_float2_keyframe_count(String propertyPtr) {
		return JNIpixelpartanimatedpropertyfloat2keyframecount(propertyPtr);
	}
	public double pixelpart_animated_property_float2_keyframe_value(String propertyPtr, double index, ByteBuffer valueBufferPtr) {
		return JNIpixelpartanimatedpropertyfloat2keyframevalue(propertyPtr, index, valueBufferPtr);
	}
	public double pixelpart_animated_property_float2_keyframe_index(String propertyPtr, double position, double epsilon) {
		return JNIpixelpartanimatedpropertyfloat2keyframeindex(propertyPtr, position, epsilon);
	}
	public double pixelpart_animated_property_float2_set_keyframe_interpolation(String propertyPtr, double method) {
		return JNIpixelpartanimatedpropertyfloat2setkeyframeinterpolation(propertyPtr, method);
	}
	public double pixelpart_animated_property_float2_get_keyframe_interpolation(String propertyPtr) {
		return JNIpixelpartanimatedpropertyfloat2getkeyframeinterpolation(propertyPtr);
	}
	public double pixelpart_animated_property_float3_at(String propertyPtr, double position, ByteBuffer valueBufferPtr) {
		return JNIpixelpartanimatedpropertyfloat3at(propertyPtr, position, valueBufferPtr);
	}
	public double pixelpart_animated_property_float3_add_keyframe(String propertyPtr, double position, ByteBuffer valueBufferPtr) {
		return JNIpixelpartanimatedpropertyfloat3addkeyframe(propertyPtr, position, valueBufferPtr);
	}
	public double pixelpart_animated_property_float3_remove_keyframe(String propertyPtr, double index) {
		return JNIpixelpartanimatedpropertyfloat3removekeyframe(propertyPtr, index);
	}
	public double pixelpart_animated_property_float3_set_keyframe_value(String propertyPtr, double index, ByteBuffer valueBufferPtr) {
		return JNIpixelpartanimatedpropertyfloat3setkeyframevalue(propertyPtr, index, valueBufferPtr);
	}
	public double pixelpart_animated_property_float3_set_keyframe_position(String propertyPtr, double index, double position) {
		return JNIpixelpartanimatedpropertyfloat3setkeyframeposition(propertyPtr, index, position);
	}
	public double pixelpart_animated_property_float3_clear_keyframes(String propertyPtr) {
		return JNIpixelpartanimatedpropertyfloat3clearkeyframes(propertyPtr);
	}
	public double pixelpart_animated_property_float3_keyframe_count(String propertyPtr) {
		return JNIpixelpartanimatedpropertyfloat3keyframecount(propertyPtr);
	}
	public double pixelpart_animated_property_float3_keyframe_value(String propertyPtr, double index, ByteBuffer valueBufferPtr) {
		return JNIpixelpartanimatedpropertyfloat3keyframevalue(propertyPtr, index, valueBufferPtr);
	}
	public double pixelpart_animated_property_float3_keyframe_index(String propertyPtr, double position, double epsilon) {
		return JNIpixelpartanimatedpropertyfloat3keyframeindex(propertyPtr, position, epsilon);
	}
	public double pixelpart_animated_property_float3_set_keyframe_interpolation(String propertyPtr, double method) {
		return JNIpixelpartanimatedpropertyfloat3setkeyframeinterpolation(propertyPtr, method);
	}
	public double pixelpart_animated_property_float3_get_keyframe_interpolation(String propertyPtr) {
		return JNIpixelpartanimatedpropertyfloat3getkeyframeinterpolation(propertyPtr);
	}
	public double pixelpart_animated_property_float4_at(String propertyPtr, double position, ByteBuffer valueBufferPtr) {
		return JNIpixelpartanimatedpropertyfloat4at(propertyPtr, position, valueBufferPtr);
	}
	public double pixelpart_animated_property_float4_add_keyframe(String propertyPtr, double position, ByteBuffer valueBufferPtr) {
		return JNIpixelpartanimatedpropertyfloat4addkeyframe(propertyPtr, position, valueBufferPtr);
	}
	public double pixelpart_animated_property_float4_remove_keyframe(String propertyPtr, double index) {
		return JNIpixelpartanimatedpropertyfloat4removekeyframe(propertyPtr, index);
	}
	public double pixelpart_animated_property_float4_set_keyframe_value(String propertyPtr, double index, ByteBuffer valueBufferPtr) {
		return JNIpixelpartanimatedpropertyfloat4setkeyframevalue(propertyPtr, index, valueBufferPtr);
	}
	public double pixelpart_animated_property_float4_set_keyframe_position(String propertyPtr, double index, double position) {
		return JNIpixelpartanimatedpropertyfloat4setkeyframeposition(propertyPtr, index, position);
	}
	public double pixelpart_animated_property_float4_clear_keyframes(String propertyPtr) {
		return JNIpixelpartanimatedpropertyfloat4clearkeyframes(propertyPtr);
	}
	public double pixelpart_animated_property_float4_keyframe_count(String propertyPtr) {
		return JNIpixelpartanimatedpropertyfloat4keyframecount(propertyPtr);
	}
	public double pixelpart_animated_property_float4_keyframe_value(String propertyPtr, double index, ByteBuffer valueBufferPtr) {
		return JNIpixelpartanimatedpropertyfloat4keyframevalue(propertyPtr, index, valueBufferPtr);
	}
	public double pixelpart_animated_property_float4_keyframe_index(String propertyPtr, double position, double epsilon) {
		return JNIpixelpartanimatedpropertyfloat4keyframeindex(propertyPtr, position, epsilon);
	}
	public double pixelpart_animated_property_float4_set_keyframe_interpolation(String propertyPtr, double method) {
		return JNIpixelpartanimatedpropertyfloat4setkeyframeinterpolation(propertyPtr, method);
	}
	public double pixelpart_animated_property_float4_get_keyframe_interpolation(String propertyPtr) {
		return JNIpixelpartanimatedpropertyfloat4getkeyframeinterpolation(propertyPtr);
	}
}
