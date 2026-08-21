#include <jni.h>
#include <string>

#include "Common.cpp"
#include "Buffer.cpp"
#include "BuiltInMaterial.cpp"
#include "Init.cpp"
#include "Error.cpp"
#include "EffectRuntime.cpp"
#include "Rendering.cpp"
#include "Resources.cpp"
#include "EffectEvent.cpp"
#include "EffectInput.cpp"
#include "EffectTrigger.cpp"
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

char* toBufferPtr(JNIEnv* env, jobject obj) {
	return static_cast<char*>(env->GetDirectBufferAddress(obj));
}

std::string toStdString(JNIEnv* env, jstring str) {
	std::size_t length = env->GetStringUTFLength(str);
	const char* cstr = env->GetStringUTFChars(str, nullptr);

	std::string result(cstr, length);
	env->ReleaseStringUTFChars(str, cstr);

	return result;
}
jstring toJavaString(JNIEnv* env, const char* str) {
	return env->NewStringUTF(str);
}

extern "C" {
// Init
JNIEXPORT jdouble JNICALL Java_net_pixelpart_MainActivity_JNIpixelpartinit(JNIEnv* env, jclass cl) {
	return pixelpart_init();
}
JNIEXPORT jdouble JNICALL Java_net_pixelpart_MainActivity_JNIpixelpartshutdown(JNIEnv* env, jclass cl) {
	return pixelpart_shutdown();
}

// Error
JNIEXPORT jstring JNICALL Java_net_pixelpart_MainActivity_JNIpixelpartlasterror(JNIEnv* env, jclass cl) {
	return toJavaString(env, pixelpart_last_error());
}

// Effect runtime
JNIEXPORT jstring JNICALL Java_net_pixelpart_MainActivity_JNIpixelpartloadeffectresource(JNIEnv* env, jclass cl, jstring arg0, jdouble arg1) {
	return toJavaString(env, pixelpart_load_effect_resource(toStdString(env, arg0).data(), arg1));
}
JNIEXPORT jdouble JNICALL Java_net_pixelpart_MainActivity_JNIpixelpartdeleteeffectresource(JNIEnv* env, jclass cl, jstring arg0) {
	return pixelpart_delete_effect_resource(toStdString(env, arg0).data());
}
JNIEXPORT jstring JNICALL Java_net_pixelpart_MainActivity_JNIpixelpartcreateeffect(JNIEnv* env, jclass cl, jstring arg0) {
	return toJavaString(env, pixelpart_create_effect(toStdString(env, arg0).data()));
}
JNIEXPORT jdouble JNICALL Java_net_pixelpart_MainActivity_JNIpixelpartdeleteeffect(JNIEnv* env, jclass cl, jstring arg0) {
	return pixelpart_delete_effect(toStdString(env, arg0).data());
}
JNIEXPORT jdouble JNICALL Java_net_pixelpart_MainActivity_JNIpixelpartseteffectscale(JNIEnv* env, jclass cl, jstring arg0, jdouble arg1, jdouble arg2) {
	return pixelpart_set_effect_scale(toStdString(env, arg0).data(), arg1, arg2);
}
JNIEXPORT jdouble JNICALL Java_net_pixelpart_MainActivity_JNIpixelpartseteffecttransform(JNIEnv* env, jclass cl, jstring arg0, jdouble arg1, jdouble arg2) {
	return pixelpart_set_effect_transform(toStdString(env, arg0).data(), arg1, arg2);
}
JNIEXPORT jdouble JNICALL Java_net_pixelpart_MainActivity_JNIpixelpartadvanceeffect(JNIEnv* env, jclass cl, jstring arg0, jobject arg1) {
	return pixelpart_advance_effect(toStdString(env, arg0).data(), toBufferPtr(env, arg1));
}
JNIEXPORT jdouble JNICALL Java_net_pixelpart_MainActivity_JNIpixelpartrestarteffect(JNIEnv* env, jclass cl, jstring arg0, jdouble arg1) {
	return pixelpart_restart_effect(toStdString(env, arg0).data(), arg1);
}
JNIEXPORT jdouble JNICALL Java_net_pixelpart_MainActivity_JNIpixelpartreseedeffect(JNIEnv* env, jclass cl, jstring arg0, jdouble arg1) {
	return pixelpart_reseed_effect(toStdString(env, arg0).data(), arg1);
}
JNIEXPORT jdouble JNICALL Java_net_pixelpart_MainActivity_JNIpixelpartgeteffecttime(JNIEnv* env, jclass cl, jstring arg0) {
	return pixelpart_get_effect_time(toStdString(env, arg0).data());
}
JNIEXPORT jdouble JNICALL Java_net_pixelpart_MainActivity_JNIpixelpartiseffectfinished(JNIEnv* env, jclass cl, jstring arg0) {
	return pixelpart_is_effect_finished(toStdString(env, arg0).data());
}
JNIEXPORT jdouble JNICALL Java_net_pixelpart_MainActivity_JNIpixelpartiseffect3d(JNIEnv* env, jclass cl, jstring arg0) {
	return pixelpart_is_effect_3d(toStdString(env, arg0).data());
}
JNIEXPORT jdouble JNICALL Java_net_pixelpart_MainActivity_JNIpixelpartgeteffectnodecount(JNIEnv* env, jclass cl, jstring arg0) {
	return pixelpart_get_effect_node_count(toStdString(env, arg0).data());
}
JNIEXPORT jdouble JNICALL Java_net_pixelpart_MainActivity_JNIpixelpartgeteffectparticletypecount(JNIEnv* env, jclass cl, jstring arg0) {
	return pixelpart_get_effect_particle_type_count(toStdString(env, arg0).data());
}
JNIEXPORT jdouble JNICALL Java_net_pixelpart_MainActivity_JNIpixelpartgeteffectparticleruntimeinstancecount(JNIEnv* env, jclass cl, jstring arg0) {
	return pixelpart_get_effect_particle_runtime_instance_count(toStdString(env, arg0).data());
}
JNIEXPORT jdouble JNICALL Java_net_pixelpart_MainActivity_JNIpixelpartgeteffectparticleruntimeinstances(JNIEnv* env, jclass cl, jstring arg0, jobject arg1) {
	return pixelpart_get_effect_particle_runtime_instances(toStdString(env, arg0).data(), toBufferPtr(env, arg1));
}
JNIEXPORT jdouble JNICALL Java_net_pixelpart_MainActivity_JNIpixelpartgeteffectparticlecount(JNIEnv* env, jclass cl, jstring arg0, jdouble arg1, jdouble arg2) {
	return pixelpart_get_effect_particle_count(toStdString(env, arg0).data(), arg1, arg2);
}
JNIEXPORT jdouble JNICALL Java_net_pixelpart_MainActivity_JNIpixelpartspawnparticles(JNIEnv* env, jclass cl, jstring arg0, jdouble arg1, jdouble arg2, jdouble arg3) {
	return pixelpart_spawn_particles(toStdString(env, arg0).data(), arg1, arg2, arg3);
}

// Resources
JNIEXPORT jdouble JNICALL Java_net_pixelpart_MainActivity_JNIpixelpartgetimageresourcecount(JNIEnv* env, jclass cl, jstring arg0) {
	return pixelpart_get_image_resource_count(toStdString(env, arg0).data());
}
JNIEXPORT jstring JNICALL Java_net_pixelpart_MainActivity_JNIpixelpartgetimageresourceid(JNIEnv* env, jclass cl, jstring arg0, jdouble arg1) {
	return toJavaString(env, pixelpart_get_image_resource_id(toStdString(env, arg0).data(), arg1));
}
JNIEXPORT jdouble JNICALL Java_net_pixelpart_MainActivity_JNIpixelpartgetimageresourcewidth(JNIEnv* env, jclass cl, jstring arg0, jstring arg1) {
	return pixelpart_get_image_resource_width(toStdString(env, arg0).data(), toStdString(env, arg1).data());
}
JNIEXPORT jdouble JNICALL Java_net_pixelpart_MainActivity_JNIpixelpartgetimageresourceheight(JNIEnv* env, jclass cl, jstring arg0, jstring arg1) {
	return pixelpart_get_image_resource_height(toStdString(env, arg0).data(), toStdString(env, arg1).data());
}
JNIEXPORT jdouble JNICALL Java_net_pixelpart_MainActivity_JNIpixelpartgetimageresourcechannels(JNIEnv* env, jclass cl, jstring arg0, jstring arg1) {
	return pixelpart_get_image_resource_channels(toStdString(env, arg0).data(), toStdString(env, arg1).data());
}
JNIEXPORT jdouble JNICALL Java_net_pixelpart_MainActivity_JNIpixelpartgetimageresourcecolorspace(JNIEnv* env, jclass cl, jstring arg0, jstring arg1) {
	return pixelpart_get_image_resource_color_space(toStdString(env, arg0).data(), toStdString(env, arg1).data());
}
JNIEXPORT jdouble JNICALL Java_net_pixelpart_MainActivity_JNIpixelpartgetimageresourcedatasize(JNIEnv* env, jclass cl, jstring arg0, jstring arg1) {
	return pixelpart_get_image_resource_data_size(toStdString(env, arg0).data(), toStdString(env, arg1).data());
}
JNIEXPORT jdouble JNICALL Java_net_pixelpart_MainActivity_JNIpixelpartgetimageresourcedata(JNIEnv* env, jclass cl, jstring arg0, jstring arg1, jobject arg2) {
	return pixelpart_get_image_resource_data(toStdString(env, arg0).data(), toStdString(env, arg1).data(), toBufferPtr(env, arg2));
}

// Rendering
JNIEXPORT jdouble JNICALL Java_net_pixelpart_MainActivity_JNIpixelpartgetsortedparticleruntimeinstances(JNIEnv* env, jclass cl, jstring arg0, jobject arg1) {
	return pixelpart_get_sorted_particle_runtime_instances(toStdString(env, arg0).data(), toBufferPtr(env, arg1));
}
JNIEXPORT jdouble JNICALL Java_net_pixelpart_MainActivity_JNIpixelpartconstructparticlegeometry(JNIEnv* env, jclass cl, jstring arg0, jdouble arg1, jdouble arg2, jobject arg3) {
	return pixelpart_construct_particle_geometry(toStdString(env, arg0).data(), arg1, arg2, toBufferPtr(env, arg3));
}
JNIEXPORT jdouble JNICALL Java_net_pixelpart_MainActivity_JNIpixelpartgenerateparticlevertexdata(JNIEnv* env, jclass cl, jstring arg0, jdouble arg1, jdouble arg2, jobject arg3) {
	return pixelpart_generate_particle_vertex_data(toStdString(env, arg0).data(), arg1, arg2, toBufferPtr(env, arg3));
}

// Built-in material
JNIEXPORT jdouble JNICALL Java_net_pixelpart_MainActivity_JNIpixelpartgetbuiltinmaterialparametercount(JNIEnv* env, jclass cl, jstring arg0) {
	return pixelpart_get_builtin_material_parameter_count(toStdString(env, arg0).data());
}
JNIEXPORT jdouble JNICALL Java_net_pixelpart_MainActivity_JNIpixelpartgetbuiltinmaterialparameters(JNIEnv* env, jclass cl, jstring arg0, jobject arg1, jobject arg2) {
	return pixelpart_get_builtin_material_parameters(toStdString(env, arg0).data(), toBufferPtr(env, arg1), toBufferPtr(env, arg2));
}

// Effect input
JNIEXPORT jdouble JNICALL Java_net_pixelpart_MainActivity_JNIpixelpartgeteffectinputcount(JNIEnv* env, jclass cl, jstring arg0) {
	return pixelpart_get_effect_input_count(toStdString(env, arg0).data());
}
JNIEXPORT jdouble JNICALL Java_net_pixelpart_MainActivity_JNIpixelpartgeteffectinputs(JNIEnv* env, jclass cl, jstring arg0, jobject arg1, jobject arg2, jobject arg3) {
	return pixelpart_get_effect_inputs(toStdString(env, arg0).data(), toBufferPtr(env, arg1), toBufferPtr(env, arg2), toBufferPtr(env, arg3));
}
JNIEXPORT jdouble JNICALL Java_net_pixelpart_MainActivity_JNIpixelpartseteffectinputbool(JNIEnv* env, jclass cl, jstring arg0, jdouble arg1, jdouble arg2) {
	return pixelpart_set_effect_input_bool(toStdString(env, arg0).data(), arg1, arg2);
}
JNIEXPORT jdouble JNICALL Java_net_pixelpart_MainActivity_JNIpixelpartseteffectinputint(JNIEnv* env, jclass cl, jstring arg0, jdouble arg1, jdouble arg2) {
	return pixelpart_set_effect_input_int(toStdString(env, arg0).data(), arg1, arg2);
}
JNIEXPORT jdouble JNICALL Java_net_pixelpart_MainActivity_JNIpixelpartseteffectinputfloat(JNIEnv* env, jclass cl, jstring arg0, jdouble arg1, jdouble arg2) {
	return pixelpart_set_effect_input_float(toStdString(env, arg0).data(), arg1, arg2);
}
JNIEXPORT jdouble JNICALL Java_net_pixelpart_MainActivity_JNIpixelpartseteffectinputfloat2(JNIEnv* env, jclass cl, jstring arg0, jdouble arg1, jobject arg2) {
	return pixelpart_set_effect_input_float2(toStdString(env, arg0).data(), arg1, toBufferPtr(env, arg2));
}
JNIEXPORT jdouble JNICALL Java_net_pixelpart_MainActivity_JNIpixelpartseteffectinputfloat3(JNIEnv* env, jclass cl, jstring arg0, jdouble arg1, jobject arg2) {
	return pixelpart_set_effect_input_float3(toStdString(env, arg0).data(), arg1, toBufferPtr(env, arg2));
}
JNIEXPORT jdouble JNICALL Java_net_pixelpart_MainActivity_JNIpixelpartseteffectinputfloat4(JNIEnv* env, jclass cl, jstring arg0, jdouble arg1, jobject arg2) {
	return pixelpart_set_effect_input_float4(toStdString(env, arg0).data(), arg1, toBufferPtr(env, arg2));
}
JNIEXPORT jdouble JNICALL Java_net_pixelpart_MainActivity_JNIpixelpartgeteffectinputbool(JNIEnv* env, jclass cl, jstring arg0, jdouble arg1) {
	return pixelpart_get_effect_input_bool(toStdString(env, arg0).data(), arg1);
}
JNIEXPORT jdouble JNICALL Java_net_pixelpart_MainActivity_JNIpixelpartgeteffectinputint(JNIEnv* env, jclass cl, jstring arg0, jdouble arg1) {
	return pixelpart_get_effect_input_int(toStdString(env, arg0).data(), arg1);
}
JNIEXPORT jdouble JNICALL Java_net_pixelpart_MainActivity_JNIpixelpartgeteffectinputfloat(JNIEnv* env, jclass cl, jstring arg0, jdouble arg1) {
	return pixelpart_get_effect_input_float(toStdString(env, arg0).data(), arg1);
}
JNIEXPORT jdouble JNICALL Java_net_pixelpart_MainActivity_JNIpixelpartgeteffectinputfloat2(JNIEnv* env, jclass cl, jstring arg0, jdouble arg1, jobject arg2) {
	return pixelpart_get_effect_input_float2(toStdString(env, arg0).data(), arg1, toBufferPtr(env, arg2));
}
JNIEXPORT jdouble JNICALL Java_net_pixelpart_MainActivity_JNIpixelpartgeteffectinputfloat3(JNIEnv* env, jclass cl, jstring arg0, jdouble arg1, jobject arg2) {
	return pixelpart_get_effect_input_float3(toStdString(env, arg0).data(), arg1, toBufferPtr(env, arg2));
}
JNIEXPORT jdouble JNICALL Java_net_pixelpart_MainActivity_JNIpixelpartgeteffectinputfloat4(JNIEnv* env, jclass cl, jstring arg0, jdouble arg1, jobject arg2) {
	return pixelpart_get_effect_input_float4(toStdString(env, arg0).data(), arg1, toBufferPtr(env, arg2));
}

// Effect trigger
JNIEXPORT jdouble JNICALL Java_net_pixelpart_MainActivity_JNIpixelpartgeteffecttriggercount(JNIEnv* env, jclass cl, jstring arg0) {
	return pixelpart_get_effect_trigger_count(toStdString(env, arg0).data());
}
JNIEXPORT jdouble JNICALL Java_net_pixelpart_MainActivity_JNIpixelpartgeteffecttriggers(JNIEnv* env, jclass cl, jstring arg0, jobject arg1, jobject arg2) {
	return pixelpart_get_effect_triggers(toStdString(env, arg0).data(), toBufferPtr(env, arg1), toBufferPtr(env, arg2));
}
JNIEXPORT jdouble JNICALL Java_net_pixelpart_MainActivity_JNIpixelpartactivateeffecttrigger(JNIEnv* env, jclass cl, jstring arg0, jdouble arg1) {
	return pixelpart_activate_effect_trigger(toStdString(env, arg0).data(), arg1);
}
JNIEXPORT jdouble JNICALL Java_net_pixelpart_MainActivity_JNIpixelpartiseffecttriggeractivated(JNIEnv* env, jclass cl, jstring arg0, jdouble arg1) {
	return pixelpart_is_effect_trigger_activated(toStdString(env, arg0).data(), arg1);
}

// Effect event
JNIEXPORT jdouble JNICALL Java_net_pixelpart_MainActivity_JNIpixelpartgeteffecteventcount(JNIEnv* env, jclass cl, jstring arg0) {
	return pixelpart_get_effect_event_count(toStdString(env, arg0).data());
}
JNIEXPORT jdouble JNICALL Java_net_pixelpart_MainActivity_JNIpixelpartgeteffectevents(JNIEnv* env, jclass cl, jstring arg0, jobject arg1, jobject arg2) {
	return pixelpart_get_effect_events(toStdString(env, arg0).data(), toBufferPtr(env, arg1), toBufferPtr(env, arg2));
}
JNIEXPORT jdouble JNICALL Java_net_pixelpart_MainActivity_JNIpixelpartgetinvokedeffectevents(JNIEnv* env, jclass cl, jstring arg0, jobject arg1) {
	return pixelpart_get_invoked_effect_events(toStdString(env, arg0).data(), toBufferPtr(env, arg1));
}

// Node
JNIEXPORT jdouble JNICALL Java_net_pixelpart_MainActivity_JNIpixelpartfindnode(JNIEnv* env, jclass cl, jstring arg0, jstring arg1) {
	return pixelpart_find_node(toStdString(env, arg0).data(), toStdString(env, arg1).data());
}
JNIEXPORT jdouble JNICALL Java_net_pixelpart_MainActivity_JNIpixelpartfindnodebyindex(JNIEnv* env, jclass cl, jstring arg0, jdouble arg1) {
	return pixelpart_find_node_by_index(toStdString(env, arg0).data(), arg1);
}
JNIEXPORT jdouble JNICALL Java_net_pixelpart_MainActivity_JNIpixelpartnodeexists(JNIEnv* env, jclass cl, jstring arg0, jdouble arg1) {
	return pixelpart_node_exists(toStdString(env, arg0).data(), arg1);
}
JNIEXPORT jdouble JNICALL Java_net_pixelpart_MainActivity_JNIpixelpartnodegettype(JNIEnv* env, jclass cl, jstring arg0, jdouble arg1) {
	return pixelpart_node_get_type(toStdString(env, arg0).data(), arg1);
}
JNIEXPORT jstring JNICALL Java_net_pixelpart_MainActivity_JNIpixelpartnodegetname(JNIEnv* env, jclass cl, jstring arg0, jdouble arg1) {
	return toJavaString(env, pixelpart_node_get_name(toStdString(env, arg0).data(), arg1));
}
JNIEXPORT jdouble JNICALL Java_net_pixelpart_MainActivity_JNIpixelpartnodegetparentid(JNIEnv* env, jclass cl, jstring arg0, jdouble arg1) {
	return pixelpart_node_get_parent_id(toStdString(env, arg0).data(), arg1);
}
JNIEXPORT jdouble JNICALL Java_net_pixelpart_MainActivity_JNIpixelpartnodesetstart(JNIEnv* env, jclass cl, jstring arg0, jdouble arg1, jdouble arg2) {
	return pixelpart_node_set_start(toStdString(env, arg0).data(), arg1, arg2);
}
JNIEXPORT jdouble JNICALL Java_net_pixelpart_MainActivity_JNIpixelpartnodesetduration(JNIEnv* env, jclass cl, jstring arg0, jdouble arg1, jdouble arg2) {
	return pixelpart_node_set_duration(toStdString(env, arg0).data(), arg1, arg2);
}
JNIEXPORT jdouble JNICALL Java_net_pixelpart_MainActivity_JNIpixelpartnodesetrepeat(JNIEnv* env, jclass cl, jstring arg0, jdouble arg1, jdouble arg2) {
	return pixelpart_node_set_repeat(toStdString(env, arg0).data(), arg1, arg2);
}
JNIEXPORT jdouble JNICALL Java_net_pixelpart_MainActivity_JNIpixelpartnodegetstart(JNIEnv* env, jclass cl, jstring arg0, jdouble arg1) {
	return pixelpart_node_get_start(toStdString(env, arg0).data(), arg1);
}
JNIEXPORT jdouble JNICALL Java_net_pixelpart_MainActivity_JNIpixelpartnodegetduration(JNIEnv* env, jclass cl, jstring arg0, jdouble arg1) {
	return pixelpart_node_get_duration(toStdString(env, arg0).data(), arg1);
}
JNIEXPORT jdouble JNICALL Java_net_pixelpart_MainActivity_JNIpixelpartnodeisrepeating(JNIEnv* env, jclass cl, jstring arg0, jdouble arg1) {
	return pixelpart_node_is_repeating(toStdString(env, arg0).data(), arg1);
}
JNIEXPORT jdouble JNICALL Java_net_pixelpart_MainActivity_JNIpixelpartnodeisactive(JNIEnv* env, jclass cl, jstring arg0, jdouble arg1) {
	return pixelpart_node_is_active(toStdString(env, arg0).data(), arg1);
}
JNIEXPORT jdouble JNICALL Java_net_pixelpart_MainActivity_JNIpixelpartnodegetlocaltime(JNIEnv* env, jclass cl, jstring arg0, jdouble arg1) {
	return pixelpart_node_get_local_time(toStdString(env, arg0).data(), arg1);
}
JNIEXPORT jstring JNICALL Java_net_pixelpart_MainActivity_JNIpixelpartnodegetposition(JNIEnv* env, jclass cl, jstring arg0, jdouble arg1) {
	return toJavaString(env, pixelpart_node_get_position(toStdString(env, arg0).data(), arg1));
}
JNIEXPORT jstring JNICALL Java_net_pixelpart_MainActivity_JNIpixelpartnodegetrotation(JNIEnv* env, jclass cl, jstring arg0, jdouble arg1) {
	return toJavaString(env, pixelpart_node_get_rotation(toStdString(env, arg0).data(), arg1));
}
JNIEXPORT jstring JNICALL Java_net_pixelpart_MainActivity_JNIpixelpartnodegetscale(JNIEnv* env, jclass cl, jstring arg0, jdouble arg1) {
	return toJavaString(env, pixelpart_node_get_scale(toStdString(env, arg0).data(), arg1));
}

// Particle emitter
JNIEXPORT jdouble JNICALL Java_net_pixelpart_MainActivity_JNIpixelpartparticleemittersetshape(JNIEnv* env, jclass cl, jstring arg0, jdouble arg1, jdouble arg2) {
	return pixelpart_particle_emitter_set_shape(toStdString(env, arg0).data(), arg1, arg2);
}
JNIEXPORT jdouble JNICALL Java_net_pixelpart_MainActivity_JNIpixelpartparticleemittergetshape(JNIEnv* env, jclass cl, jstring arg0, jdouble arg1) {
	return pixelpart_particle_emitter_get_shape(toStdString(env, arg0).data(), arg1);
}
JNIEXPORT jdouble JNICALL Java_net_pixelpart_MainActivity_JNIpixelpartparticleemitteraddshapepoint(JNIEnv* env, jclass cl, jstring arg0, jdouble arg1, jobject arg2) {
	return pixelpart_particle_emitter_add_shape_point(toStdString(env, arg0).data(), arg1, toBufferPtr(env, arg2));
}
JNIEXPORT jdouble JNICALL Java_net_pixelpart_MainActivity_JNIpixelpartparticleemitterremoveshapepoint(JNIEnv* env, jclass cl, jstring arg0, jdouble arg1, jdouble arg2) {
	return pixelpart_particle_emitter_remove_shape_point(toStdString(env, arg0).data(), arg1, arg2);
}
JNIEXPORT jdouble JNICALL Java_net_pixelpart_MainActivity_JNIpixelpartparticleemittersetshapepoint(JNIEnv* env, jclass cl, jstring arg0, jdouble arg1, jdouble arg2, jobject arg3) {
	return pixelpart_particle_emitter_set_shape_point(toStdString(env, arg0).data(), arg1, arg2, toBufferPtr(env, arg3));
}
JNIEXPORT jdouble JNICALL Java_net_pixelpart_MainActivity_JNIpixelpartparticleemittergetshapepoint(JNIEnv* env, jclass cl, jstring arg0, jdouble arg1, jdouble arg2, jobject arg3) {
	return pixelpart_particle_emitter_get_shape_point(toStdString(env, arg0).data(), arg1, arg2, toBufferPtr(env, arg3));
}
JNIEXPORT jdouble JNICALL Java_net_pixelpart_MainActivity_JNIpixelpartparticleemittergetshapepointcount(JNIEnv* env, jclass cl, jstring arg0, jdouble arg1) {
	return pixelpart_particle_emitter_get_shape_point_count(toStdString(env, arg0).data(), arg1);
}
JNIEXPORT jdouble JNICALL Java_net_pixelpart_MainActivity_JNIpixelpartparticleemittersetdistribution(JNIEnv* env, jclass cl, jstring arg0, jdouble arg1, jdouble arg2) {
	return pixelpart_particle_emitter_set_distribution(toStdString(env, arg0).data(), arg1, arg2);
}
JNIEXPORT jdouble JNICALL Java_net_pixelpart_MainActivity_JNIpixelpartparticleemittergetdistribution(JNIEnv* env, jclass cl, jstring arg0, jdouble arg1) {
	return pixelpart_particle_emitter_get_distribution(toStdString(env, arg0).data(), arg1);
}
JNIEXPORT jdouble JNICALL Java_net_pixelpart_MainActivity_JNIpixelpartparticleemittersetgridorder(JNIEnv* env, jclass cl, jstring arg0, jdouble arg1, jdouble arg2) {
	return pixelpart_particle_emitter_set_grid_order(toStdString(env, arg0).data(), arg1, arg2);
}
JNIEXPORT jdouble JNICALL Java_net_pixelpart_MainActivity_JNIpixelpartparticleemittergetgridorder(JNIEnv* env, jclass cl, jstring arg0, jdouble arg1) {
	return pixelpart_particle_emitter_get_grid_order(toStdString(env, arg0).data(), arg1);
}
JNIEXPORT jdouble JNICALL Java_net_pixelpart_MainActivity_JNIpixelpartparticleemittersetgridsize(JNIEnv* env, jclass cl, jstring arg0, jdouble arg1, jobject arg2) {
	return pixelpart_particle_emitter_set_grid_size(toStdString(env, arg0).data(), arg1, toBufferPtr(env, arg2));
}
JNIEXPORT jdouble JNICALL Java_net_pixelpart_MainActivity_JNIpixelpartparticleemittergetgridsizex(JNIEnv* env, jclass cl, jstring arg0, jdouble arg1) {
	return pixelpart_particle_emitter_get_grid_size_x(toStdString(env, arg0).data(), arg1);
}
JNIEXPORT jdouble JNICALL Java_net_pixelpart_MainActivity_JNIpixelpartparticleemittergetgridsizey(JNIEnv* env, jclass cl, jstring arg0, jdouble arg1) {
	return pixelpart_particle_emitter_get_grid_size_y(toStdString(env, arg0).data(), arg1);
}
JNIEXPORT jdouble JNICALL Java_net_pixelpart_MainActivity_JNIpixelpartparticleemittergetgridsizez(JNIEnv* env, jclass cl, jstring arg0, jdouble arg1) {
	return pixelpart_particle_emitter_get_grid_size_z(toStdString(env, arg0).data(), arg1);
}
JNIEXPORT jdouble JNICALL Java_net_pixelpart_MainActivity_JNIpixelpartparticleemittersetemissionmode(JNIEnv* env, jclass cl, jstring arg0, jdouble arg1, jdouble arg2) {
	return pixelpart_particle_emitter_set_emission_mode(toStdString(env, arg0).data(), arg1, arg2);
}
JNIEXPORT jdouble JNICALL Java_net_pixelpart_MainActivity_JNIpixelpartparticleemittergetemissionmode(JNIEnv* env, jclass cl, jstring arg0, jdouble arg1) {
	return pixelpart_particle_emitter_get_emission_mode(toStdString(env, arg0).data(), arg1);
}
JNIEXPORT jdouble JNICALL Java_net_pixelpart_MainActivity_JNIpixelpartparticleemittersetdirectionmode(JNIEnv* env, jclass cl, jstring arg0, jdouble arg1, jdouble arg2) {
	return pixelpart_particle_emitter_set_direction_mode(toStdString(env, arg0).data(), arg1, arg2);
}
JNIEXPORT jdouble JNICALL Java_net_pixelpart_MainActivity_JNIpixelpartparticleemittergetdirectionmode(JNIEnv* env, jclass cl, jstring arg0, jdouble arg1) {
	return pixelpart_particle_emitter_get_direction_mode(toStdString(env, arg0).data(), arg1);
}
JNIEXPORT jstring JNICALL Java_net_pixelpart_MainActivity_JNIpixelpartparticleemittergetdirection(JNIEnv* env, jclass cl, jstring arg0, jdouble arg1) {
	return toJavaString(env, pixelpart_particle_emitter_get_direction(toStdString(env, arg0).data(), arg1));
}
JNIEXPORT jstring JNICALL Java_net_pixelpart_MainActivity_JNIpixelpartparticleemittergetspread(JNIEnv* env, jclass cl, jstring arg0, jdouble arg1) {
	return toJavaString(env, pixelpart_particle_emitter_get_spread(toStdString(env, arg0).data(), arg1));
}

// Force field
JNIEXPORT jdouble JNICALL Java_net_pixelpart_MainActivity_JNIpixelpartforcefieldsetinfinite(JNIEnv* env, jclass cl, jstring arg0, jdouble arg1, jdouble arg2) {
	return pixelpart_force_field_set_infinite(toStdString(env, arg0).data(), arg1, arg2);
}
JNIEXPORT jdouble JNICALL Java_net_pixelpart_MainActivity_JNIpixelpartforcefieldisinfinite(JNIEnv* env, jclass cl, jstring arg0, jdouble arg1) {
	return pixelpart_force_field_is_infinite(toStdString(env, arg0).data(), arg1);
}
JNIEXPORT jstring JNICALL Java_net_pixelpart_MainActivity_JNIpixelpartforcefieldgetstrength(JNIEnv* env, jclass cl, jstring arg0, jdouble arg1) {
	return toJavaString(env, pixelpart_force_field_get_strength(toStdString(env, arg0).data(), arg1));
}
JNIEXPORT jstring JNICALL Java_net_pixelpart_MainActivity_JNIpixelpartattractionfieldgetfalloffpower(JNIEnv* env, jclass cl, jstring arg0, jdouble arg1) {
	return toJavaString(env, pixelpart_attraction_field_get_falloff_power(toStdString(env, arg0).data(), arg1));
}
JNIEXPORT jstring JNICALL Java_net_pixelpart_MainActivity_JNIpixelpartaccelerationfieldgetaccelerationdirection(JNIEnv* env, jclass cl, jstring arg0, jdouble arg1) {
	return toJavaString(env, pixelpart_acceleration_field_get_acceleration_direction(toStdString(env, arg0).data(), arg1));
}
JNIEXPORT jstring JNICALL Java_net_pixelpart_MainActivity_JNIpixelpartaccelerationfieldgetaccelerationdirectionvariance(JNIEnv* env, jclass cl, jstring arg0, jdouble arg1) {
	return toJavaString(env, pixelpart_acceleration_field_get_acceleration_direction_variance(toStdString(env, arg0).data(), arg1));
}
JNIEXPORT jstring JNICALL Java_net_pixelpart_MainActivity_JNIpixelpartaccelerationfieldgetaccelerationstrengthvariance(JNIEnv* env, jclass cl, jstring arg0, jdouble arg1) {
	return toJavaString(env, pixelpart_acceleration_field_get_acceleration_strength_variance(toStdString(env, arg0).data(), arg1));
}
JNIEXPORT jdouble JNICALL Java_net_pixelpart_MainActivity_JNIpixelpartaccelerationfieldsetaccelerationgridsize(JNIEnv* env, jclass cl, jstring arg0, jdouble arg1, jobject arg2) {
	return pixelpart_acceleration_field_set_acceleration_grid_size(toStdString(env, arg0).data(), arg1, toBufferPtr(env, arg2));
}
JNIEXPORT jdouble JNICALL Java_net_pixelpart_MainActivity_JNIpixelpartaccelerationfieldgetaccelerationgridsizex(JNIEnv* env, jclass cl, jstring arg0, jdouble arg1) {
	return pixelpart_acceleration_field_get_acceleration_grid_size_x(toStdString(env, arg0).data(), arg1);
}
JNIEXPORT jdouble JNICALL Java_net_pixelpart_MainActivity_JNIpixelpartaccelerationfieldgetaccelerationgridsizey(JNIEnv* env, jclass cl, jstring arg0, jdouble arg1) {
	return pixelpart_acceleration_field_get_acceleration_grid_size_y(toStdString(env, arg0).data(), arg1);
}
JNIEXPORT jdouble JNICALL Java_net_pixelpart_MainActivity_JNIpixelpartaccelerationfieldgetaccelerationgridsizez(JNIEnv* env, jclass cl, jstring arg0, jdouble arg1) {
	return pixelpart_acceleration_field_get_acceleration_grid_size_z(toStdString(env, arg0).data(), arg1);
}
JNIEXPORT jdouble JNICALL Java_net_pixelpart_MainActivity_JNIpixelpartvectorfieldsetvectorfieldfilter(JNIEnv* env, jclass cl, jstring arg0, jdouble arg1, jdouble arg2) {
	return pixelpart_vector_field_set_vector_field_filter(toStdString(env, arg0).data(), arg1, arg2);
}
JNIEXPORT jdouble JNICALL Java_net_pixelpart_MainActivity_JNIpixelpartvectorfieldgetvectorfieldfilter(JNIEnv* env, jclass cl, jstring arg0, jdouble arg1) {
	return pixelpart_vector_field_get_vector_field_filter(toStdString(env, arg0).data(), arg1);
}
JNIEXPORT jstring JNICALL Java_net_pixelpart_MainActivity_JNIpixelpartvectorfieldgettightness(JNIEnv* env, jclass cl, jstring arg0, jdouble arg1) {
	return toJavaString(env, pixelpart_vector_field_get_tightness(toStdString(env, arg0).data(), arg1));
}
JNIEXPORT jstring JNICALL Java_net_pixelpart_MainActivity_JNIpixelpartnoisefieldgetnoiseoctaves(JNIEnv* env, jclass cl, jstring arg0, jdouble arg1) {
	return toJavaString(env, pixelpart_noise_field_get_noise_octaves(toStdString(env, arg0).data(), arg1));
}
JNIEXPORT jstring JNICALL Java_net_pixelpart_MainActivity_JNIpixelpartnoisefieldgetnoisefrequency(JNIEnv* env, jclass cl, jstring arg0, jdouble arg1) {
	return toJavaString(env, pixelpart_noise_field_get_noise_frequency(toStdString(env, arg0).data(), arg1));
}
JNIEXPORT jstring JNICALL Java_net_pixelpart_MainActivity_JNIpixelpartnoisefieldgetnoisepersistence(JNIEnv* env, jclass cl, jstring arg0, jdouble arg1) {
	return toJavaString(env, pixelpart_noise_field_get_noise_persistence(toStdString(env, arg0).data(), arg1));
}
JNIEXPORT jstring JNICALL Java_net_pixelpart_MainActivity_JNIpixelpartnoisefieldgetnoiselacunarity(JNIEnv* env, jclass cl, jstring arg0, jdouble arg1) {
	return toJavaString(env, pixelpart_noise_field_get_noise_lacunarity(toStdString(env, arg0).data(), arg1));
}
JNIEXPORT jdouble JNICALL Java_net_pixelpart_MainActivity_JNIpixelpartnoisefieldsetnoiseanimated(JNIEnv* env, jclass cl, jstring arg0, jdouble arg1, jdouble arg2) {
	return pixelpart_noise_field_set_noise_animated(toStdString(env, arg0).data(), arg1, arg2);
}
JNIEXPORT jdouble JNICALL Java_net_pixelpart_MainActivity_JNIpixelpartnoisefieldisnoiseanimated(JNIEnv* env, jclass cl, jstring arg0, jdouble arg1) {
	return pixelpart_noise_field_is_noise_animated(toStdString(env, arg0).data(), arg1);
}
JNIEXPORT jstring JNICALL Java_net_pixelpart_MainActivity_JNIpixelpartnoisefieldgetnoiseanimationtimescale(JNIEnv* env, jclass cl, jstring arg0, jdouble arg1) {
	return toJavaString(env, pixelpart_noise_field_get_noise_animation_time_scale(toStdString(env, arg0).data(), arg1));
}
JNIEXPORT jstring JNICALL Java_net_pixelpart_MainActivity_JNIpixelpartnoisefieldgetnoiseanimationtimebase(JNIEnv* env, jclass cl, jstring arg0, jdouble arg1) {
	return toJavaString(env, pixelpart_noise_field_get_noise_animation_time_base(toStdString(env, arg0).data(), arg1));
}
JNIEXPORT jstring JNICALL Java_net_pixelpart_MainActivity_JNIpixelpartdragfieldgetvelocityinfluence(JNIEnv* env, jclass cl, jstring arg0, jdouble arg1) {
	return toJavaString(env, pixelpart_drag_field_get_velocity_influence(toStdString(env, arg0).data(), arg1));
}
JNIEXPORT jstring JNICALL Java_net_pixelpart_MainActivity_JNIpixelpartdragfieldgetsizeinfluence(JNIEnv* env, jclass cl, jstring arg0, jdouble arg1) {
	return toJavaString(env, pixelpart_drag_field_get_size_influence(toStdString(env, arg0).data(), arg1));
}

// Collider
JNIEXPORT jstring JNICALL Java_net_pixelpart_MainActivity_JNIpixelpartcollidergetkilloncontact(JNIEnv* env, jclass cl, jstring arg0, jdouble arg1) {
	return toJavaString(env, pixelpart_collider_get_kill_on_contact(toStdString(env, arg0).data(), arg1));
}
JNIEXPORT jstring JNICALL Java_net_pixelpart_MainActivity_JNIpixelpartcollidergetbounce(JNIEnv* env, jclass cl, jstring arg0, jdouble arg1) {
	return toJavaString(env, pixelpart_collider_get_bounce(toStdString(env, arg0).data(), arg1));
}
JNIEXPORT jstring JNICALL Java_net_pixelpart_MainActivity_JNIpixelpartcollidergetfriction(JNIEnv* env, jclass cl, jstring arg0, jdouble arg1) {
	return toJavaString(env, pixelpart_collider_get_friction(toStdString(env, arg0).data(), arg1));
}
JNIEXPORT jdouble JNICALL Java_net_pixelpart_MainActivity_JNIpixelpartlinecollideraddpoint(JNIEnv* env, jclass cl, jstring arg0, jdouble arg1, jobject arg2) {
	return pixelpart_line_collider_add_point(toStdString(env, arg0).data(), arg1, toBufferPtr(env, arg2));
}
JNIEXPORT jdouble JNICALL Java_net_pixelpart_MainActivity_JNIpixelpartlinecollidersetpoint(JNIEnv* env, jclass cl, jstring arg0, jdouble arg1, jdouble arg2, jobject arg3) {
	return pixelpart_line_collider_set_point(toStdString(env, arg0).data(), arg1, arg2, toBufferPtr(env, arg3));
}
JNIEXPORT jdouble JNICALL Java_net_pixelpart_MainActivity_JNIpixelpartlinecolliderremovepoint(JNIEnv* env, jclass cl, jstring arg0, jdouble arg1, jdouble arg2) {
	return pixelpart_line_collider_remove_point(toStdString(env, arg0).data(), arg1, arg2);
}
JNIEXPORT jdouble JNICALL Java_net_pixelpart_MainActivity_JNIpixelpartlinecollidergetpoint(JNIEnv* env, jclass cl, jstring arg0, jdouble arg1, jdouble arg2, jobject arg3) {
	return pixelpart_line_collider_get_point(toStdString(env, arg0).data(), arg1, arg2, toBufferPtr(env, arg3));
}
JNIEXPORT jdouble JNICALL Java_net_pixelpart_MainActivity_JNIpixelpartlinecollidergetpointcount(JNIEnv* env, jclass cl, jstring arg0, jdouble arg1) {
	return pixelpart_line_collider_get_point_count(toStdString(env, arg0).data(), arg1);
}

// Light source
JNIEXPORT jstring JNICALL Java_net_pixelpart_MainActivity_JNIpixelpartlightsourcegetattenuation(JNIEnv* env, jclass cl, jstring arg0, jdouble arg1) {
	return toJavaString(env, pixelpart_light_source_get_attenuation(toStdString(env, arg0).data(), arg1));
}
JNIEXPORT jstring JNICALL Java_net_pixelpart_MainActivity_JNIpixelpartlightsourcegetcolor(JNIEnv* env, jclass cl, jstring arg0, jdouble arg1) {
	return toJavaString(env, pixelpart_light_source_get_color(toStdString(env, arg0).data(), arg1));
}
JNIEXPORT jstring JNICALL Java_net_pixelpart_MainActivity_JNIpixelpartlightsourcegetintensity(JNIEnv* env, jclass cl, jstring arg0, jdouble arg1) {
	return toJavaString(env, pixelpart_light_source_get_intensity(toStdString(env, arg0).data(), arg1));
}
JNIEXPORT jstring JNICALL Java_net_pixelpart_MainActivity_JNIpixelpartspotlightsourcegetspotangle(JNIEnv* env, jclass cl, jstring arg0, jdouble arg1) {
	return toJavaString(env, pixelpart_spot_light_source_get_spot_angle(toStdString(env, arg0).data(), arg1));
}
JNIEXPORT jstring JNICALL Java_net_pixelpart_MainActivity_JNIpixelpartspotlightsourcegetspotangleattenuation(JNIEnv* env, jclass cl, jstring arg0, jdouble arg1) {
	return toJavaString(env, pixelpart_spot_light_source_get_spot_angle_attenuation(toStdString(env, arg0).data(), arg1));
}

// Particle type
JNIEXPORT jdouble JNICALL Java_net_pixelpart_MainActivity_JNIpixelpartfindparticletype(JNIEnv* env, jclass cl, jstring arg0, jstring arg1) {
	return pixelpart_find_particle_type(toStdString(env, arg0).data(), toStdString(env, arg1).data());
}
JNIEXPORT jdouble JNICALL Java_net_pixelpart_MainActivity_JNIpixelpartfindparticletypebyindex(JNIEnv* env, jclass cl, jstring arg0, jdouble arg1) {
	return pixelpart_find_particle_type_by_index(toStdString(env, arg0).data(), arg1);
}
JNIEXPORT jdouble JNICALL Java_net_pixelpart_MainActivity_JNIpixelpartparticletypeexists(JNIEnv* env, jclass cl, jstring arg0, jdouble arg1) {
	return pixelpart_particle_type_exists(toStdString(env, arg0).data(), arg1);
}
JNIEXPORT jdouble JNICALL Java_net_pixelpart_MainActivity_JNIpixelpartparticletypegetindex(JNIEnv* env, jclass cl, jstring arg0, jdouble arg1) {
	return pixelpart_particle_type_get_index(toStdString(env, arg0).data(), arg1);
}
JNIEXPORT jdouble JNICALL Java_net_pixelpart_MainActivity_JNIpixelpartparticletypegetparentid(JNIEnv* env, jclass cl, jstring arg0, jdouble arg1) {
	return pixelpart_particle_type_get_parent_id(toStdString(env, arg0).data(), arg1);
}
JNIEXPORT jstring JNICALL Java_net_pixelpart_MainActivity_JNIpixelpartparticletypegetname(JNIEnv* env, jclass cl, jstring arg0, jdouble arg1) {
	return toJavaString(env, pixelpart_particle_type_get_name(toStdString(env, arg0).data(), arg1));
}
JNIEXPORT jdouble JNICALL Java_net_pixelpart_MainActivity_JNIpixelpartparticletypesetpositionrelative(JNIEnv* env, jclass cl, jstring arg0, jdouble arg1, jdouble arg2) {
	return pixelpart_particle_type_set_position_relative(toStdString(env, arg0).data(), arg1, arg2);
}
JNIEXPORT jdouble JNICALL Java_net_pixelpart_MainActivity_JNIpixelpartparticletypeispositionrelative(JNIEnv* env, jclass cl, jstring arg0, jdouble arg1) {
	return pixelpart_particle_type_is_position_relative(toStdString(env, arg0).data(), arg1);
}
JNIEXPORT jdouble JNICALL Java_net_pixelpart_MainActivity_JNIpixelpartparticletypesetrotationmode(JNIEnv* env, jclass cl, jstring arg0, jdouble arg1, jdouble arg2) {
	return pixelpart_particle_type_set_rotation_mode(toStdString(env, arg0).data(), arg1, arg2);
}
JNIEXPORT jdouble JNICALL Java_net_pixelpart_MainActivity_JNIpixelpartparticletypegetrotationmode(JNIEnv* env, jclass cl, jstring arg0, jdouble arg1) {
	return pixelpart_particle_type_get_rotation_mode(toStdString(env, arg0).data(), arg1);
}
JNIEXPORT jdouble JNICALL Java_net_pixelpart_MainActivity_JNIpixelpartparticletypesetalignmentmode(JNIEnv* env, jclass cl, jstring arg0, jdouble arg1, jdouble arg2) {
	return pixelpart_particle_type_set_alignment_mode(toStdString(env, arg0).data(), arg1, arg2);
}
JNIEXPORT jdouble JNICALL Java_net_pixelpart_MainActivity_JNIpixelpartparticletypegetalignmentmode(JNIEnv* env, jclass cl, jstring arg0, jdouble arg1) {
	return pixelpart_particle_type_get_alignment_mode(toStdString(env, arg0).data(), arg1);
}
JNIEXPORT jstring JNICALL Java_net_pixelpart_MainActivity_JNIpixelpartparticletypegetpivot(JNIEnv* env, jclass cl, jstring arg0, jdouble arg1) {
	return toJavaString(env, pixelpart_particle_type_get_pivot(toStdString(env, arg0).data(), arg1));
}
JNIEXPORT jstring JNICALL Java_net_pixelpart_MainActivity_JNIpixelpartparticletypegetmotionpathforce(JNIEnv* env, jclass cl, jstring arg0, jdouble arg1) {
	return toJavaString(env, pixelpart_particle_type_get_motion_path_force(toStdString(env, arg0).data(), arg1));
}
JNIEXPORT jdouble JNICALL Java_net_pixelpart_MainActivity_JNIpixelpartparticletypesetvisible(JNIEnv* env, jclass cl, jstring arg0, jdouble arg1, jdouble arg2) {
	return pixelpart_particle_type_set_visible(toStdString(env, arg0).data(), arg1, arg2);
}
JNIEXPORT jdouble JNICALL Java_net_pixelpart_MainActivity_JNIpixelpartparticletypeisvisible(JNIEnv* env, jclass cl, jstring arg0, jdouble arg1) {
	return pixelpart_particle_type_is_visible(toStdString(env, arg0).data(), arg1);
}
JNIEXPORT jdouble JNICALL Java_net_pixelpart_MainActivity_JNIpixelpartparticletypesetlayer(JNIEnv* env, jclass cl, jstring arg0, jdouble arg1, jdouble arg2) {
	return pixelpart_particle_type_set_layer(toStdString(env, arg0).data(), arg1, arg2);
}
JNIEXPORT jdouble JNICALL Java_net_pixelpart_MainActivity_JNIpixelpartparticletypegetlayer(JNIEnv* env, jclass cl, jstring arg0, jdouble arg1) {
	return pixelpart_particle_type_get_layer(toStdString(env, arg0).data(), arg1);
}
JNIEXPORT jstring JNICALL Java_net_pixelpart_MainActivity_JNIpixelpartparticletypegetmaterialid(JNIEnv* env, jclass cl, jstring arg0, jdouble arg1) {
	return toJavaString(env, pixelpart_particle_type_get_material_id(toStdString(env, arg0).data(), arg1));
}
JNIEXPORT jdouble JNICALL Java_net_pixelpart_MainActivity_JNIpixelpartparticletypeismaterialbuiltin(JNIEnv* env, jclass cl, jstring arg0, jdouble arg1) {
	return pixelpart_particle_type_is_material_builtin(toStdString(env, arg0).data(), arg1);
}
JNIEXPORT jdouble JNICALL Java_net_pixelpart_MainActivity_JNIpixelpartparticletypegetmaterialparametercount(JNIEnv* env, jclass cl, jstring arg0, jdouble arg1) {
	return pixelpart_particle_type_get_material_parameter_count(toStdString(env, arg0).data(), arg1);
}
JNIEXPORT jdouble JNICALL Java_net_pixelpart_MainActivity_JNIpixelpartparticletypegetmaterialparameterids(JNIEnv* env, jclass cl, jstring arg0, jdouble arg1, jobject arg2) {
	return pixelpart_particle_type_get_material_parameter_ids(toStdString(env, arg0).data(), arg1, toBufferPtr(env, arg2));
}
JNIEXPORT jdouble JNICALL Java_net_pixelpart_MainActivity_JNIpixelpartparticletypegetmaterialparametertype(JNIEnv* env, jclass cl, jstring arg0, jdouble arg1, jdouble arg2) {
	return pixelpart_particle_type_get_material_parameter_type(toStdString(env, arg0).data(), arg1, arg2);
}
JNIEXPORT jdouble JNICALL Java_net_pixelpart_MainActivity_JNIpixelpartparticletypegetmaterialparametervalue(JNIEnv* env, jclass cl, jstring arg0, jdouble arg1, jdouble arg2, jobject arg3) {
	return pixelpart_particle_type_get_material_parameter_value(toStdString(env, arg0).data(), arg1, arg2, toBufferPtr(env, arg3));
}
JNIEXPORT jdouble JNICALL Java_net_pixelpart_MainActivity_JNIpixelpartparticletypegetrenderer(JNIEnv* env, jclass cl, jstring arg0, jdouble arg1) {
	return pixelpart_particle_type_get_renderer(toStdString(env, arg0).data(), arg1);
}
JNIEXPORT jstring JNICALL Java_net_pixelpart_MainActivity_JNIpixelpartparticletypegetmeshrenderermeshresourceid(JNIEnv* env, jclass cl, jstring arg0, jdouble arg1) {
	return toJavaString(env, pixelpart_particle_type_get_mesh_renderer_mesh_resource_id(toStdString(env, arg0).data(), arg1));
}
JNIEXPORT jstring JNICALL Java_net_pixelpart_MainActivity_JNIpixelpartparticletypegetcount(JNIEnv* env, jclass cl, jstring arg0, jdouble arg1) {
	return toJavaString(env, pixelpart_particle_type_get_count(toStdString(env, arg0).data(), arg1));
}
JNIEXPORT jstring JNICALL Java_net_pixelpart_MainActivity_JNIpixelpartparticletypegetlifespan(JNIEnv* env, jclass cl, jstring arg0, jdouble arg1) {
	return toJavaString(env, pixelpart_particle_type_get_lifespan(toStdString(env, arg0).data(), arg1));
}
JNIEXPORT jstring JNICALL Java_net_pixelpart_MainActivity_JNIpixelpartparticletypegetinitialsize(JNIEnv* env, jclass cl, jstring arg0, jdouble arg1) {
	return toJavaString(env, pixelpart_particle_type_get_initial_size(toStdString(env, arg0).data(), arg1));
}
JNIEXPORT jstring JNICALL Java_net_pixelpart_MainActivity_JNIpixelpartparticletypegetinitialrotation(JNIEnv* env, jclass cl, jstring arg0, jdouble arg1) {
	return toJavaString(env, pixelpart_particle_type_get_initial_rotation(toStdString(env, arg0).data(), arg1));
}
JNIEXPORT jstring JNICALL Java_net_pixelpart_MainActivity_JNIpixelpartparticletypegetinitialvelocity(JNIEnv* env, jclass cl, jstring arg0, jdouble arg1) {
	return toJavaString(env, pixelpart_particle_type_get_initial_velocity(toStdString(env, arg0).data(), arg1));
}
JNIEXPORT jstring JNICALL Java_net_pixelpart_MainActivity_JNIpixelpartparticletypegetinheritedvelocity(JNIEnv* env, jclass cl, jstring arg0, jdouble arg1) {
	return toJavaString(env, pixelpart_particle_type_get_inherited_velocity(toStdString(env, arg0).data(), arg1));
}
JNIEXPORT jstring JNICALL Java_net_pixelpart_MainActivity_JNIpixelpartparticletypegetinitialopacity(JNIEnv* env, jclass cl, jstring arg0, jdouble arg1) {
	return toJavaString(env, pixelpart_particle_type_get_initial_opacity(toStdString(env, arg0).data(), arg1));
}
JNIEXPORT jstring JNICALL Java_net_pixelpart_MainActivity_JNIpixelpartparticletypegetmotionpath(JNIEnv* env, jclass cl, jstring arg0, jdouble arg1) {
	return toJavaString(env, pixelpart_particle_type_get_motion_path(toStdString(env, arg0).data(), arg1));
}
JNIEXPORT jstring JNICALL Java_net_pixelpart_MainActivity_JNIpixelpartparticletypegetsize(JNIEnv* env, jclass cl, jstring arg0, jdouble arg1) {
	return toJavaString(env, pixelpart_particle_type_get_size(toStdString(env, arg0).data(), arg1));
}
JNIEXPORT jstring JNICALL Java_net_pixelpart_MainActivity_JNIpixelpartparticletypegetstretch(JNIEnv* env, jclass cl, jstring arg0, jdouble arg1) {
	return toJavaString(env, pixelpart_particle_type_get_stretch(toStdString(env, arg0).data(), arg1));
}
JNIEXPORT jstring JNICALL Java_net_pixelpart_MainActivity_JNIpixelpartparticletypegetphysicalsize(JNIEnv* env, jclass cl, jstring arg0, jdouble arg1) {
	return toJavaString(env, pixelpart_particle_type_get_physical_size(toStdString(env, arg0).data(), arg1));
}
JNIEXPORT jstring JNICALL Java_net_pixelpart_MainActivity_JNIpixelpartparticletypegetrotation(JNIEnv* env, jclass cl, jstring arg0, jdouble arg1) {
	return toJavaString(env, pixelpart_particle_type_get_rotation(toStdString(env, arg0).data(), arg1));
}
JNIEXPORT jstring JNICALL Java_net_pixelpart_MainActivity_JNIpixelpartparticletypegetrotationbyspeed(JNIEnv* env, jclass cl, jstring arg0, jdouble arg1) {
	return toJavaString(env, pixelpart_particle_type_get_rotation_by_speed(toStdString(env, arg0).data(), arg1));
}
JNIEXPORT jstring JNICALL Java_net_pixelpart_MainActivity_JNIpixelpartparticletypegetacceleration(JNIEnv* env, jclass cl, jstring arg0, jdouble arg1) {
	return toJavaString(env, pixelpart_particle_type_get_acceleration(toStdString(env, arg0).data(), arg1));
}
JNIEXPORT jstring JNICALL Java_net_pixelpart_MainActivity_JNIpixelpartparticletypegetradialacceleration(JNIEnv* env, jclass cl, jstring arg0, jdouble arg1) {
	return toJavaString(env, pixelpart_particle_type_get_radial_acceleration(toStdString(env, arg0).data(), arg1));
}
JNIEXPORT jstring JNICALL Java_net_pixelpart_MainActivity_JNIpixelpartparticletypegetweight(JNIEnv* env, jclass cl, jstring arg0, jdouble arg1) {
	return toJavaString(env, pixelpart_particle_type_get_weight(toStdString(env, arg0).data(), arg1));
}
JNIEXPORT jstring JNICALL Java_net_pixelpart_MainActivity_JNIpixelpartparticletypegetbounce(JNIEnv* env, jclass cl, jstring arg0, jdouble arg1) {
	return toJavaString(env, pixelpart_particle_type_get_bounce(toStdString(env, arg0).data(), arg1));
}
JNIEXPORT jstring JNICALL Java_net_pixelpart_MainActivity_JNIpixelpartparticletypegetfriction(JNIEnv* env, jclass cl, jstring arg0, jdouble arg1) {
	return toJavaString(env, pixelpart_particle_type_get_friction(toStdString(env, arg0).data(), arg1));
}
JNIEXPORT jstring JNICALL Java_net_pixelpart_MainActivity_JNIpixelpartparticletypegetcolor(JNIEnv* env, jclass cl, jstring arg0, jdouble arg1) {
	return toJavaString(env, pixelpart_particle_type_get_color(toStdString(env, arg0).data(), arg1));
}
JNIEXPORT jstring JNICALL Java_net_pixelpart_MainActivity_JNIpixelpartparticletypegetopacity(JNIEnv* env, jclass cl, jstring arg0, jdouble arg1) {
	return toJavaString(env, pixelpart_particle_type_get_opacity(toStdString(env, arg0).data(), arg1));
}
JNIEXPORT jstring JNICALL Java_net_pixelpart_MainActivity_JNIpixelpartparticletypegetlifespanvariance(JNIEnv* env, jclass cl, jstring arg0, jdouble arg1) {
	return toJavaString(env, pixelpart_particle_type_get_lifespan_variance(toStdString(env, arg0).data(), arg1));
}
JNIEXPORT jstring JNICALL Java_net_pixelpart_MainActivity_JNIpixelpartparticletypegetsizevariance(JNIEnv* env, jclass cl, jstring arg0, jdouble arg1) {
	return toJavaString(env, pixelpart_particle_type_get_size_variance(toStdString(env, arg0).data(), arg1));
}
JNIEXPORT jstring JNICALL Java_net_pixelpart_MainActivity_JNIpixelpartparticletypegetrotationvariance(JNIEnv* env, jclass cl, jstring arg0, jdouble arg1) {
	return toJavaString(env, pixelpart_particle_type_get_rotation_variance(toStdString(env, arg0).data(), arg1));
}
JNIEXPORT jstring JNICALL Java_net_pixelpart_MainActivity_JNIpixelpartparticletypegetangularvelocityvariance(JNIEnv* env, jclass cl, jstring arg0, jdouble arg1) {
	return toJavaString(env, pixelpart_particle_type_get_angular_velocity_variance(toStdString(env, arg0).data(), arg1));
}
JNIEXPORT jstring JNICALL Java_net_pixelpart_MainActivity_JNIpixelpartparticletypegetvelocityvariance(JNIEnv* env, jclass cl, jstring arg0, jdouble arg1) {
	return toJavaString(env, pixelpart_particle_type_get_velocity_variance(toStdString(env, arg0).data(), arg1));
}
JNIEXPORT jstring JNICALL Java_net_pixelpart_MainActivity_JNIpixelpartparticletypegetcolorvariance(JNIEnv* env, jclass cl, jstring arg0, jdouble arg1) {
	return toJavaString(env, pixelpart_particle_type_get_color_variance(toStdString(env, arg0).data(), arg1));
}
JNIEXPORT jstring JNICALL Java_net_pixelpart_MainActivity_JNIpixelpartparticletypegetopacityvariance(JNIEnv* env, jclass cl, jstring arg0, jdouble arg1) {
	return toJavaString(env, pixelpart_particle_type_get_opacity_variance(toStdString(env, arg0).data(), arg1));
}

// Static property
JNIEXPORT jdouble JNICALL Java_net_pixelpart_MainActivity_JNIpixelpartstaticpropertyboolvalue(JNIEnv* env, jclass cl, jstring arg0) {
	return pixelpart_static_property_bool_value(toStdString(env, arg0).data());
}
JNIEXPORT jdouble JNICALL Java_net_pixelpart_MainActivity_JNIpixelpartstaticpropertyboolsetbasevalue(JNIEnv* env, jclass cl, jstring arg0, jdouble arg1) {
	return pixelpart_static_property_bool_set_base_value(toStdString(env, arg0).data(), arg1);
}
JNIEXPORT jdouble JNICALL Java_net_pixelpart_MainActivity_JNIpixelpartstaticpropertyboolgetbasevalue(JNIEnv* env, jclass cl, jstring arg0) {
	return pixelpart_static_property_bool_get_base_value(toStdString(env, arg0).data());
}
JNIEXPORT jdouble JNICALL Java_net_pixelpart_MainActivity_JNIpixelpartstaticpropertyintvalue(JNIEnv* env, jclass cl, jstring arg0) {
	return pixelpart_static_property_int_value(toStdString(env, arg0).data());
}
JNIEXPORT jdouble JNICALL Java_net_pixelpart_MainActivity_JNIpixelpartstaticpropertyintsetbasevalue(JNIEnv* env, jclass cl, jstring arg0, jdouble arg1) {
	return pixelpart_static_property_int_set_base_value(toStdString(env, arg0).data(), arg1);
}
JNIEXPORT jdouble JNICALL Java_net_pixelpart_MainActivity_JNIpixelpartstaticpropertyintgetbasevalue(JNIEnv* env, jclass cl, jstring arg0) {
	return pixelpart_static_property_int_get_base_value(toStdString(env, arg0).data());
}
JNIEXPORT jdouble JNICALL Java_net_pixelpart_MainActivity_JNIpixelpartstaticpropertyfloatvalue(JNIEnv* env, jclass cl, jstring arg0) {
	return pixelpart_static_property_float_value(toStdString(env, arg0).data());
}
JNIEXPORT jdouble JNICALL Java_net_pixelpart_MainActivity_JNIpixelpartstaticpropertyfloatsetbasevalue(JNIEnv* env, jclass cl, jstring arg0, jdouble arg1) {
	return pixelpart_static_property_float_set_base_value(toStdString(env, arg0).data(), arg1);
}
JNIEXPORT jdouble JNICALL Java_net_pixelpart_MainActivity_JNIpixelpartstaticpropertyfloatgetbasevalue(JNIEnv* env, jclass cl, jstring arg0) {
	return pixelpart_static_property_float_get_base_value(toStdString(env, arg0).data());
}
JNIEXPORT jdouble JNICALL Java_net_pixelpart_MainActivity_JNIpixelpartstaticpropertyfloat2value(JNIEnv* env, jclass cl, jstring arg0, jobject arg1) {
	return pixelpart_static_property_float2_value(toStdString(env, arg0).data(), toBufferPtr(env, arg1));
}
JNIEXPORT jdouble JNICALL Java_net_pixelpart_MainActivity_JNIpixelpartstaticpropertyfloat2setbasevalue(JNIEnv* env, jclass cl, jstring arg0, jobject arg1) {
	return pixelpart_static_property_float2_set_base_value(toStdString(env, arg0).data(), toBufferPtr(env, arg1));
}
JNIEXPORT jdouble JNICALL Java_net_pixelpart_MainActivity_JNIpixelpartstaticpropertyfloat2getbasevalue(JNIEnv* env, jclass cl, jstring arg0, jobject arg1) {
	return pixelpart_static_property_float2_get_base_value(toStdString(env, arg0).data(), toBufferPtr(env, arg1));
}
JNIEXPORT jdouble JNICALL Java_net_pixelpart_MainActivity_JNIpixelpartstaticpropertyfloat3value(JNIEnv* env, jclass cl, jstring arg0, jobject arg1) {
	return pixelpart_static_property_float3_value(toStdString(env, arg0).data(), toBufferPtr(env, arg1));
}
JNIEXPORT jdouble JNICALL Java_net_pixelpart_MainActivity_JNIpixelpartstaticpropertyfloat3setbasevalue(JNIEnv* env, jclass cl, jstring arg0, jobject arg1) {
	return pixelpart_static_property_float3_set_base_value(toStdString(env, arg0).data(), toBufferPtr(env, arg1));
}
JNIEXPORT jdouble JNICALL Java_net_pixelpart_MainActivity_JNIpixelpartstaticpropertyfloat3getbasevalue(JNIEnv* env, jclass cl, jstring arg0, jobject arg1) {
	return pixelpart_static_property_float3_get_base_value(toStdString(env, arg0).data(), toBufferPtr(env, arg1));
}
JNIEXPORT jdouble JNICALL Java_net_pixelpart_MainActivity_JNIpixelpartstaticpropertyfloat4value(JNIEnv* env, jclass cl, jstring arg0, jobject arg1) {
	return pixelpart_static_property_float4_value(toStdString(env, arg0).data(), toBufferPtr(env, arg1));
}
JNIEXPORT jdouble JNICALL Java_net_pixelpart_MainActivity_JNIpixelpartstaticpropertyfloat4setbasevalue(JNIEnv* env, jclass cl, jstring arg0, jobject arg1) {
	return pixelpart_static_property_float4_set_base_value(toStdString(env, arg0).data(), toBufferPtr(env, arg1));
}
JNIEXPORT jdouble JNICALL Java_net_pixelpart_MainActivity_JNIpixelpartstaticpropertyfloat4getbasevalue(JNIEnv* env, jclass cl, jstring arg0, jobject arg1) {
	return pixelpart_static_property_float4_get_base_value(toStdString(env, arg0).data(), toBufferPtr(env, arg1));
}

// Animated property
JNIEXPORT jdouble JNICALL Java_net_pixelpart_MainActivity_JNIpixelpartanimatedpropertyfloatat(JNIEnv* env, jclass cl, jstring arg0, jdouble arg1) {
	return pixelpart_animated_property_float_at(toStdString(env, arg0).data(), arg1);
}
JNIEXPORT jdouble JNICALL Java_net_pixelpart_MainActivity_JNIpixelpartanimatedpropertyfloataddkeyframe(JNIEnv* env, jclass cl, jstring arg0, jdouble arg1, jdouble arg2) {
	return pixelpart_animated_property_float_add_keyframe(toStdString(env, arg0).data(), arg1, arg2);
}
JNIEXPORT jdouble JNICALL Java_net_pixelpart_MainActivity_JNIpixelpartanimatedpropertyfloatremovekeyframe(JNIEnv* env, jclass cl, jstring arg0, jdouble arg1) {
	return pixelpart_animated_property_float_remove_keyframe(toStdString(env, arg0).data(), arg1);
}
JNIEXPORT jdouble JNICALL Java_net_pixelpart_MainActivity_JNIpixelpartanimatedpropertyfloatsetkeyframevalue(JNIEnv* env, jclass cl, jstring arg0, jdouble arg1, jdouble arg2) {
	return pixelpart_animated_property_float_set_keyframe_value(toStdString(env, arg0).data(), arg1, arg2);
}
JNIEXPORT jdouble JNICALL Java_net_pixelpart_MainActivity_JNIpixelpartanimatedpropertyfloatsetkeyframeposition(JNIEnv* env, jclass cl, jstring arg0, jdouble arg1, jdouble arg2) {
	return pixelpart_animated_property_float_set_keyframe_position(toStdString(env, arg0).data(), arg1, arg2);
}
JNIEXPORT jdouble JNICALL Java_net_pixelpart_MainActivity_JNIpixelpartanimatedpropertyfloatclearkeyframes(JNIEnv* env, jclass cl, jstring arg0) {
	return pixelpart_animated_property_float_clear_keyframes(toStdString(env, arg0).data());
}
JNIEXPORT jdouble JNICALL Java_net_pixelpart_MainActivity_JNIpixelpartanimatedpropertyfloatkeyframecount(JNIEnv* env, jclass cl, jstring arg0) {
	return pixelpart_animated_property_float_keyframe_count(toStdString(env, arg0).data());
}
JNIEXPORT jdouble JNICALL Java_net_pixelpart_MainActivity_JNIpixelpartanimatedpropertyfloatkeyframevalue(JNIEnv* env, jclass cl, jstring arg0, jdouble arg1) {
	return pixelpart_animated_property_float_keyframe_value(toStdString(env, arg0).data(), arg1);
}
JNIEXPORT jdouble JNICALL Java_net_pixelpart_MainActivity_JNIpixelpartanimatedpropertyfloatkeyframeindex(JNIEnv* env, jclass cl, jstring arg0, jdouble arg1, jdouble arg2) {
	return pixelpart_animated_property_float_keyframe_index(toStdString(env, arg0).data(), arg1, arg2);
}
JNIEXPORT jdouble JNICALL Java_net_pixelpart_MainActivity_JNIpixelpartanimatedpropertyfloatsetkeyframeinterpolation(JNIEnv* env, jclass cl, jstring arg0, jdouble arg1) {
	return pixelpart_animated_property_float_set_keyframe_interpolation(toStdString(env, arg0).data(), arg1);
}
JNIEXPORT jdouble JNICALL Java_net_pixelpart_MainActivity_JNIpixelpartanimatedpropertyfloatgetkeyframeinterpolation(JNIEnv* env, jclass cl, jstring arg0) {
	return pixelpart_animated_property_float_get_keyframe_interpolation(toStdString(env, arg0).data());
}
JNIEXPORT jdouble JNICALL Java_net_pixelpart_MainActivity_JNIpixelpartanimatedpropertyfloat2at(JNIEnv* env, jclass cl, jstring arg0, jdouble arg1, jobject arg2) {
	return pixelpart_animated_property_float2_at(toStdString(env, arg0).data(), arg1, toBufferPtr(env, arg2));
}
JNIEXPORT jdouble JNICALL Java_net_pixelpart_MainActivity_JNIpixelpartanimatedpropertyfloat2addkeyframe(JNIEnv* env, jclass cl, jstring arg0, jdouble arg1, jobject arg2) {
	return pixelpart_animated_property_float2_add_keyframe(toStdString(env, arg0).data(), arg1, toBufferPtr(env, arg2));
}
JNIEXPORT jdouble JNICALL Java_net_pixelpart_MainActivity_JNIpixelpartanimatedpropertyfloat2removekeyframe(JNIEnv* env, jclass cl, jstring arg0, jdouble arg1) {
	return pixelpart_animated_property_float2_remove_keyframe(toStdString(env, arg0).data(), arg1);
}
JNIEXPORT jdouble JNICALL Java_net_pixelpart_MainActivity_JNIpixelpartanimatedpropertyfloat2setkeyframevalue(JNIEnv* env, jclass cl, jstring arg0, jdouble arg1, jobject arg2) {
	return pixelpart_animated_property_float2_set_keyframe_value(toStdString(env, arg0).data(), arg1, toBufferPtr(env, arg2));
}
JNIEXPORT jdouble JNICALL Java_net_pixelpart_MainActivity_JNIpixelpartanimatedpropertyfloat2setkeyframeposition(JNIEnv* env, jclass cl, jstring arg0, jdouble arg1, jdouble arg2) {
	return pixelpart_animated_property_float2_set_keyframe_position(toStdString(env, arg0).data(), arg1, arg2);
}
JNIEXPORT jdouble JNICALL Java_net_pixelpart_MainActivity_JNIpixelpartanimatedpropertyfloat2clearkeyframes(JNIEnv* env, jclass cl, jstring arg0) {
	return pixelpart_animated_property_float2_clear_keyframes(toStdString(env, arg0).data());
}
JNIEXPORT jdouble JNICALL Java_net_pixelpart_MainActivity_JNIpixelpartanimatedpropertyfloat2keyframecount(JNIEnv* env, jclass cl, jstring arg0) {
	return pixelpart_animated_property_float2_keyframe_count(toStdString(env, arg0).data());
}
JNIEXPORT jdouble JNICALL Java_net_pixelpart_MainActivity_JNIpixelpartanimatedpropertyfloat2keyframevalue(JNIEnv* env, jclass cl, jstring arg0, jdouble arg1, jobject arg2) {
	return pixelpart_animated_property_float2_keyframe_value(toStdString(env, arg0).data(), arg1, toBufferPtr(env, arg2));
}
JNIEXPORT jdouble JNICALL Java_net_pixelpart_MainActivity_JNIpixelpartanimatedpropertyfloat2keyframeindex(JNIEnv* env, jclass cl, jstring arg0, jdouble arg1, jdouble arg2) {
	return pixelpart_animated_property_float2_keyframe_index(toStdString(env, arg0).data(), arg1, arg2);
}
JNIEXPORT jdouble JNICALL Java_net_pixelpart_MainActivity_JNIpixelpartanimatedpropertyfloat2setkeyframeinterpolation(JNIEnv* env, jclass cl, jstring arg0, jdouble arg1) {
	return pixelpart_animated_property_float2_set_keyframe_interpolation(toStdString(env, arg0).data(), arg1);
}
JNIEXPORT jdouble JNICALL Java_net_pixelpart_MainActivity_JNIpixelpartanimatedpropertyfloat2getkeyframeinterpolation(JNIEnv* env, jclass cl, jstring arg0) {
	return pixelpart_animated_property_float2_get_keyframe_interpolation(toStdString(env, arg0).data());
}
JNIEXPORT jdouble JNICALL Java_net_pixelpart_MainActivity_JNIpixelpartanimatedpropertyfloat3at(JNIEnv* env, jclass cl, jstring arg0, jdouble arg1, jobject arg2) {
	return pixelpart_animated_property_float3_at(toStdString(env, arg0).data(), arg1, toBufferPtr(env, arg2));
}
JNIEXPORT jdouble JNICALL Java_net_pixelpart_MainActivity_JNIpixelpartanimatedpropertyfloat3addkeyframe(JNIEnv* env, jclass cl, jstring arg0, jdouble arg1, jobject arg2) {
	return pixelpart_animated_property_float3_add_keyframe(toStdString(env, arg0).data(), arg1, toBufferPtr(env, arg2));
}
JNIEXPORT jdouble JNICALL Java_net_pixelpart_MainActivity_JNIpixelpartanimatedpropertyfloat3removekeyframe(JNIEnv* env, jclass cl, jstring arg0, jdouble arg1) {
	return pixelpart_animated_property_float3_remove_keyframe(toStdString(env, arg0).data(), arg1);
}
JNIEXPORT jdouble JNICALL Java_net_pixelpart_MainActivity_JNIpixelpartanimatedpropertyfloat3setkeyframevalue(JNIEnv* env, jclass cl, jstring arg0, jdouble arg1, jobject arg2) {
	return pixelpart_animated_property_float3_set_keyframe_value(toStdString(env, arg0).data(), arg1, toBufferPtr(env, arg2));
}
JNIEXPORT jdouble JNICALL Java_net_pixelpart_MainActivity_JNIpixelpartanimatedpropertyfloat3setkeyframeposition(JNIEnv* env, jclass cl, jstring arg0, jdouble arg1, jdouble arg2) {
	return pixelpart_animated_property_float3_set_keyframe_position(toStdString(env, arg0).data(), arg1, arg2);
}
JNIEXPORT jdouble JNICALL Java_net_pixelpart_MainActivity_JNIpixelpartanimatedpropertyfloat3clearkeyframes(JNIEnv* env, jclass cl, jstring arg0) {
	return pixelpart_animated_property_float3_clear_keyframes(toStdString(env, arg0).data());
}
JNIEXPORT jdouble JNICALL Java_net_pixelpart_MainActivity_JNIpixelpartanimatedpropertyfloat3keyframecount(JNIEnv* env, jclass cl, jstring arg0) {
	return pixelpart_animated_property_float3_keyframe_count(toStdString(env, arg0).data());
}
JNIEXPORT jdouble JNICALL Java_net_pixelpart_MainActivity_JNIpixelpartanimatedpropertyfloat3keyframevalue(JNIEnv* env, jclass cl, jstring arg0, jdouble arg1, jobject arg2) {
	return pixelpart_animated_property_float3_keyframe_value(toStdString(env, arg0).data(), arg1, toBufferPtr(env, arg2));
}
JNIEXPORT jdouble JNICALL Java_net_pixelpart_MainActivity_JNIpixelpartanimatedpropertyfloat3keyframeindex(JNIEnv* env, jclass cl, jstring arg0, jdouble arg1, jdouble arg2) {
	return pixelpart_animated_property_float3_keyframe_index(toStdString(env, arg0).data(), arg1, arg2);
}
JNIEXPORT jdouble JNICALL Java_net_pixelpart_MainActivity_JNIpixelpartanimatedpropertyfloat3setkeyframeinterpolation(JNIEnv* env, jclass cl, jstring arg0, jdouble arg1) {
	return pixelpart_animated_property_float3_set_keyframe_interpolation(toStdString(env, arg0).data(), arg1);
}
JNIEXPORT jdouble JNICALL Java_net_pixelpart_MainActivity_JNIpixelpartanimatedpropertyfloat3getkeyframeinterpolation(JNIEnv* env, jclass cl, jstring arg0) {
	return pixelpart_animated_property_float3_get_keyframe_interpolation(toStdString(env, arg0).data());
}
JNIEXPORT jdouble JNICALL Java_net_pixelpart_MainActivity_JNIpixelpartanimatedpropertyfloat4at(JNIEnv* env, jclass cl, jstring arg0, jdouble arg1, jobject arg2) {
	return pixelpart_animated_property_float4_at(toStdString(env, arg0).data(), arg1, toBufferPtr(env, arg2));
}
JNIEXPORT jdouble JNICALL Java_net_pixelpart_MainActivity_JNIpixelpartanimatedpropertyfloat4addkeyframe(JNIEnv* env, jclass cl, jstring arg0, jdouble arg1, jobject arg2) {
	return pixelpart_animated_property_float4_add_keyframe(toStdString(env, arg0).data(), arg1, toBufferPtr(env, arg2));
}
JNIEXPORT jdouble JNICALL Java_net_pixelpart_MainActivity_JNIpixelpartanimatedpropertyfloat4removekeyframe(JNIEnv* env, jclass cl, jstring arg0, jdouble arg1) {
	return pixelpart_animated_property_float4_remove_keyframe(toStdString(env, arg0).data(), arg1);
}
JNIEXPORT jdouble JNICALL Java_net_pixelpart_MainActivity_JNIpixelpartanimatedpropertyfloat4setkeyframevalue(JNIEnv* env, jclass cl, jstring arg0, jdouble arg1, jobject arg2) {
	return pixelpart_animated_property_float4_set_keyframe_value(toStdString(env, arg0).data(), arg1, toBufferPtr(env, arg2));
}
JNIEXPORT jdouble JNICALL Java_net_pixelpart_MainActivity_JNIpixelpartanimatedpropertyfloat4setkeyframeposition(JNIEnv* env, jclass cl, jstring arg0, jdouble arg1, jdouble arg2) {
	return pixelpart_animated_property_float4_set_keyframe_position(toStdString(env, arg0).data(), arg1, arg2);
}
JNIEXPORT jdouble JNICALL Java_net_pixelpart_MainActivity_JNIpixelpartanimatedpropertyfloat4clearkeyframes(JNIEnv* env, jclass cl, jstring arg0) {
	return pixelpart_animated_property_float4_clear_keyframes(toStdString(env, arg0).data());
}
JNIEXPORT jdouble JNICALL Java_net_pixelpart_MainActivity_JNIpixelpartanimatedpropertyfloat4keyframecount(JNIEnv* env, jclass cl, jstring arg0) {
	return pixelpart_animated_property_float4_keyframe_count(toStdString(env, arg0).data());
}
JNIEXPORT jdouble JNICALL Java_net_pixelpart_MainActivity_JNIpixelpartanimatedpropertyfloat4keyframevalue(JNIEnv* env, jclass cl, jstring arg0, jdouble arg1, jobject arg2) {
	return pixelpart_animated_property_float4_keyframe_value(toStdString(env, arg0).data(), arg1, toBufferPtr(env, arg2));
}
JNIEXPORT jdouble JNICALL Java_net_pixelpart_MainActivity_JNIpixelpartanimatedpropertyfloat4keyframeindex(JNIEnv* env, jclass cl, jstring arg0, jdouble arg1, jdouble arg2) {
	return pixelpart_animated_property_float4_keyframe_index(toStdString(env, arg0).data(), arg1, arg2);
}
JNIEXPORT jdouble JNICALL Java_net_pixelpart_MainActivity_JNIpixelpartanimatedpropertyfloat4setkeyframeinterpolation(JNIEnv* env, jclass cl, jstring arg0, jdouble arg1) {
	return pixelpart_animated_property_float4_set_keyframe_interpolation(toStdString(env, arg0).data(), arg1);
}
JNIEXPORT jdouble JNICALL Java_net_pixelpart_MainActivity_JNIpixelpartanimatedpropertyfloat4getkeyframeinterpolation(JNIEnv* env, jclass cl, jstring arg0) {
	return pixelpart_animated_property_float4_get_keyframe_interpolation(toStdString(env, arg0).data());
}
}
