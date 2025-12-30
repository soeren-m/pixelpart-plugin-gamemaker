package net.pixelpart;

import java.lang.String;
import java.nio.ByteBuffer;

public class MainActivity {
	// Init
	public static native double JNIpixelpartinit();
	public static native double JNIpixelpartshutdown();

	// Error
	public static native String JNIpixelpartlasterror();

	// Effect runtime
	public static native String JNIpixelpartloadeffect(String data, double size, double particleCapacity);
	public static native double JNIpixelpartdeleteeffect(String runtimePtr);
	public static native double JNIpixelpartseteffectscale(String runtimePtr, double scaleX, double scaleY);
	public static native double JNIpixelpartseteffecttransform(String runtimePtr, double x, double y);
	public static native double JNIpixelpartadvanceeffect(String runtimePtr, ByteBuffer paramBufferPtr);
	public static native double JNIpixelpartrestarteffect(String runtimePtr, double clear);
	public static native double JNIpixelpartreseedeffect(String runtimePtr, double seed);
	public static native double JNIpixelpartgeteffecttime(String runtimePtr);
	public static native double JNIpixelpartiseffectfinished(String runtimePtr);
	public static native double JNIpixelpartiseffect3d(String runtimePtr);
	public static native double JNIpixelpartgeteffectnodecount(String runtimePtr);
	public static native double JNIpixelpartgeteffectparticletypecount(String runtimePtr);
	public static native double JNIpixelpartgeteffectparticleruntimeinstancecount(String runtimePtr);
	public static native double JNIpixelpartgeteffectparticleruntimeinstances(String runtimePtr, ByteBuffer instanceBufferPtr);
	public static native double JNIpixelpartgeteffectparticlecount(String runtimePtr, double particleEmitterId, double particleTypeId);
	public static native double JNIpixelpartspawnparticles(String runtimePtr, double particleEmitterId, double particleTypeId, double count);

	// Resources
	public static native double JNIpixelpartgetimageresourcecount(String runtimePtr);
	public static native double JNIpixelpartgetimageresourceid(String runtimePtr, double index, ByteBuffer resourceIdBufferPtr, double resourceIdBufferSize);
	public static native double JNIpixelpartgetimageresourcewidth(String runtimePtr, String resourceId);
	public static native double JNIpixelpartgetimageresourceheight(String runtimePtr, String resourceId);
	public static native double JNIpixelpartgetimageresourcechannels(String runtimePtr, String resourceId);
	public static native double JNIpixelpartgetimageresourcecolorspace(String runtimePtr, String resourceId);
	public static native double JNIpixelpartgetimageresourcedatasize(String runtimePtr, String resourceId);
	public static native double JNIpixelpartgetimageresourcedata(String runtimePtr, String resourceId, ByteBuffer imageDataBufferPtr);

	// Rendering
	public static native double JNIpixelpartgetsortedparticleruntimeinstances(String runtimePtr, ByteBuffer indexBufferPtr);
	public static native double JNIpixelpartconstructparticlegeometry(String runtimePtr, double particleEmitterId, double particleTypeId, ByteBuffer bufferSizeBufferPtr);
	public static native double JNIpixelpartgenerateparticlevertexdata(String runtimePtr, double particleEmitterId, double particleTypeId, ByteBuffer vertexBufferPtr);

	// Effect input
	public static native double JNIpixelpartgeteffectinputcount(String runtimePtr);
	public static native double JNIpixelpartgeteffectinputs(String runtimePtr, ByteBuffer idBufferPtr, ByteBuffer typeBufferPtr, ByteBuffer nameBufferPtr);
	public static native double JNIpixelpartseteffectinputbool(String runtimePtr, double inputId, double value);
	public static native double JNIpixelpartseteffectinputint(String runtimePtr, double inputId, double value);
	public static native double JNIpixelpartseteffectinputfloat(String runtimePtr, double inputId, double value);
	public static native double JNIpixelpartseteffectinputfloat2(String runtimePtr, double inputId, ByteBuffer valueBufferPtr);
	public static native double JNIpixelpartseteffectinputfloat3(String runtimePtr, double inputId, ByteBuffer valueBufferPtr);
	public static native double JNIpixelpartseteffectinputfloat4(String runtimePtr, double inputId, ByteBuffer valueBufferPtr);
	public static native double JNIpixelpartgeteffectinputbool(String runtimePtr, double inputId);
	public static native double JNIpixelpartgeteffectinputint(String runtimePtr, double inputId);
	public static native double JNIpixelpartgeteffectinputfloat(String runtimePtr, double inputId);
	public static native double JNIpixelpartgeteffectinputfloat2(String runtimePtr, double inputId, ByteBuffer valueBufferPtr);
	public static native double JNIpixelpartgeteffectinputfloat3(String runtimePtr, double inputId, ByteBuffer valueBufferPtr);
	public static native double JNIpixelpartgeteffectinputfloat4(String runtimePtr, double inputId, ByteBuffer valueBufferPtr);

	// Trigger
	public static native double JNIpixelpartgettriggercount(String runtimePtr);
	public static native double JNIpixelpartgettriggers(String runtimePtr, ByteBuffer idBufferPtr, ByteBuffer nameBufferPtr);
	public static native double JNIpixelpartactivatetrigger(String runtimePtr, double triggerId);
	public static native double JNIpixelpartistriggeractivated(String runtimePtr, double triggerId);

	// Node
	public static native double JNIpixelpartfindnode(String runtimePtr, String bufferPtr);
	public static native double JNIpixelpartfindnodebyindex(String runtimePtr, double nodeIndex);
	public static native double JNIpixelpartnodeexists(String runtimePtr, double nodeId);
	public static native double JNIpixelpartnodegettype(String runtimePtr, double nodeId);
	public static native String JNIpixelpartnodegetname(String runtimePtr, double nodeId);
	public static native double JNIpixelpartnodegetparentid(String runtimePtr, double nodeId);
	public static native double JNIpixelpartnodesetstart(String runtimePtr, double nodeId, double value);
	public static native double JNIpixelpartnodesetduration(String runtimePtr, double nodeId, double value);
	public static native double JNIpixelpartnodesetrepeat(String runtimePtr, double nodeId, double value);
	public static native double JNIpixelpartnodegetstart(String runtimePtr, double nodeId);
	public static native double JNIpixelpartnodegetduration(String runtimePtr, double nodeId);
	public static native double JNIpixelpartnodeisrepeating(String runtimePtr, double nodeId);
	public static native double JNIpixelpartnodeisactive(String runtimePtr, double nodeId);
	public static native double JNIpixelpartnodegetlocaltime(String runtimePtr, double nodeId);
	public static native String JNIpixelpartnodegetposition(String runtimePtr, double nodeId);
	public static native String JNIpixelpartnodegetrotation(String runtimePtr, double nodeId);
	public static native String JNIpixelpartnodegetscale(String runtimePtr, double nodeId);

	// Particle emitter
	public static native double JNIpixelpartparticleemittersetshape(String runtimePtr, double emitterId, double shape);
	public static native double JNIpixelpartparticleemittergetshape(String runtimePtr, double emitterId);
	public static native double JNIpixelpartparticleemitteraddshapepoint(String runtimePtr, double emitterId, ByteBuffer valueBufferPtr);
	public static native double JNIpixelpartparticleemitterremoveshapepoint(String runtimePtr, double emitterId, double index);
	public static native double JNIpixelpartparticleemittersetshapepoint(String runtimePtr, double emitterId, double index, ByteBuffer valueBufferPtr);
	public static native double JNIpixelpartparticleemittergetshapepoint(String runtimePtr, double emitterId, double index, ByteBuffer valueBufferPtr);
	public static native double JNIpixelpartparticleemittergetshapepointcount(String runtimePtr, double emitterId);
	public static native double JNIpixelpartparticleemittersetdistribution(String runtimePtr, double emitterId, double mode);
	public static native double JNIpixelpartparticleemittergetdistribution(String runtimePtr, double emitterId);
	public static native double JNIpixelpartparticleemittersetgridorder(String runtimePtr, double emitterId, double mode);
	public static native double JNIpixelpartparticleemittergetgridorder(String runtimePtr, double emitterId);
	public static native double JNIpixelpartparticleemittersetgridsize(String runtimePtr, double emitterId, ByteBuffer valueBufferPtr);
	public static native double JNIpixelpartparticleemittergetgridsizex(String runtimePtr, double emitterId);
	public static native double JNIpixelpartparticleemittergetgridsizey(String runtimePtr, double emitterId);
	public static native double JNIpixelpartparticleemittergetgridsizez(String runtimePtr, double emitterId);
	public static native double JNIpixelpartparticleemittersetemissionmode(String runtimePtr, double emitterId, double mode);
	public static native double JNIpixelpartparticleemittergetemissionmode(String runtimePtr, double emitterId);
	public static native double JNIpixelpartparticleemittersetdirectionmode(String runtimePtr, double emitterId, double mode);
	public static native double JNIpixelpartparticleemittergetdirectionmode(String runtimePtr, double emitterId);
	public static native String JNIpixelpartparticleemittergetdirection(String runtimePtr, double emitterId);
	public static native String JNIpixelpartparticleemittergetspread(String runtimePtr, double emitterId);

	// Force field
	public static native double JNIpixelpartforcefieldsetinfinite(String runtimePtr, double forceFieldId, double mode);
	public static native double JNIpixelpartforcefieldisinfinite(String runtimePtr, double forceFieldId);
	public static native String JNIpixelpartforcefieldgetstrength(String runtimePtr, double forceFieldId);
	public static native String JNIpixelpartaccelerationfieldgetaccelerationdirection(String runtimePtr, double forceFieldId);
	public static native String JNIpixelpartaccelerationfieldgetaccelerationdirectionvariance(String runtimePtr, double forceFieldId);
	public static native String JNIpixelpartaccelerationfieldgetaccelerationstrengthvariance(String runtimePtr, double forceFieldId);
	public static native double JNIpixelpartaccelerationfieldsetaccelerationgridsize(String runtimePtr, double forceFieldId, ByteBuffer valueBufferPtr);
	public static native double JNIpixelpartaccelerationfieldgetaccelerationgridsizex(String runtimePtr, double forceFieldId);
	public static native double JNIpixelpartaccelerationfieldgetaccelerationgridsizey(String runtimePtr, double forceFieldId);
	public static native double JNIpixelpartaccelerationfieldgetaccelerationgridsizez(String runtimePtr, double forceFieldId);
	public static native double JNIpixelpartvectorfieldsetvectorfieldfilter(String runtimePtr, double forceFieldId, double filter);
	public static native double JNIpixelpartvectorfieldgetvectorfieldfilter(String runtimePtr, double forceFieldId);
	public static native String JNIpixelpartvectorfieldgettightness(String runtimePtr, double forceFieldId);
	public static native String JNIpixelpartnoisefieldgetnoiseoctaves(String runtimePtr, double forceFieldId);
	public static native String JNIpixelpartnoisefieldgetnoisefrequency(String runtimePtr, double forceFieldId);
	public static native String JNIpixelpartnoisefieldgetnoisepersistence(String runtimePtr, double forceFieldId);
	public static native String JNIpixelpartnoisefieldgetnoiselacunarity(String runtimePtr, double forceFieldId);
	public static native double JNIpixelpartnoisefieldsetnoiseanimated(String runtimePtr, double forceFieldId, double animated);
	public static native double JNIpixelpartnoisefieldisnoiseanimated(String runtimePtr, double forceFieldId);
	public static native String JNIpixelpartnoisefieldgetnoiseanimationtimescale(String runtimePtr, double forceFieldId);
	public static native String JNIpixelpartnoisefieldgetnoiseanimationtimebase(String runtimePtr, double forceFieldId);
	public static native String JNIpixelpartdragfieldgetvelocityinfluence(String runtimePtr, double forceFieldId);
	public static native String JNIpixelpartdragfieldgetsizeinfluence(String runtimePtr, double forceFieldId);

	// Collider
	public static native String JNIpixelpartcollidergetkilloncontact(String runtimePtr, double colliderId);
	public static native String JNIpixelpartcollidergetbounce(String runtimePtr, double colliderId);
	public static native String JNIpixelpartcollidergetfriction(String runtimePtr, double colliderId);
	public static native double JNIpixelpartlinecollideraddpoint(String runtimePtr, double colliderId, ByteBuffer valueBufferPtr);
	public static native double JNIpixelpartlinecollidersetpoint(String runtimePtr, double colliderId, double index, ByteBuffer valueBufferPtr);
	public static native double JNIpixelpartlinecolliderremovepoint(String runtimePtr, double colliderId, double index);
	public static native double JNIpixelpartlinecollidergetpoint(String runtimePtr, double colliderId, double index, ByteBuffer valueBufferPtr);
	public static native double JNIpixelpartlinecollidergetpointcount(String runtimePtr, double colliderId);

	// Light source
	public static native String JNIpixelpartlightsourcegetattenuation(String runtimePtr, double lightSourceId);
	public static native String JNIpixelpartlightsourcegetcolor(String runtimePtr, double lightSourceId);
	public static native String JNIpixelpartlightsourcegetintensity(String runtimePtr, double lightSourceId);
	public static native String JNIpixelpartspotlightsourcegetspotangle(String runtimePtr, double lightSourceId);
	public static native String JNIpixelpartspotlightsourcegetspotangleattenuation(String runtimePtr, double lightSourceId);

	// Particle type
	public static native double JNIpixelpartfindparticletype(String runtimePtr, String bufferPtr);
	public static native double JNIpixelpartfindparticletypebyindex(String runtimePtr, double particleTypeIndex);
	public static native double JNIpixelpartparticletypeexists(String runtimePtr, double particleTypeId);
	public static native double JNIpixelpartparticletypegetindex(String runtimePtr, double particleTypeId);
	public static native double JNIpixelpartparticletypegetparentid(String runtimePtr, double particleTypeId);
	public static native String JNIpixelpartparticletypegetname(String runtimePtr, double particleTypeId);
	public static native double JNIpixelpartparticletypesetpositionrelative(String runtimePtr, double particleTypeId, double relative);
	public static native double JNIpixelpartparticletypeispositionrelative(String runtimePtr, double particleTypeId);
	public static native double JNIpixelpartparticletypesetrotationmode(String runtimePtr, double particleTypeId, double mode);
	public static native double JNIpixelpartparticletypegetrotationmode(String runtimePtr, double particleTypeId);
	public static native double JNIpixelpartparticletypesetalignmentmode(String runtimePtr, double particleTypeId, double mode);
	public static native double JNIpixelpartparticletypegetalignmentmode(String runtimePtr, double particleTypeId);
	public static native String JNIpixelpartparticletypegetpivot(String runtimePtr, double particleTypeId);
	public static native String JNIpixelpartparticletypegetmotionpathforce(String runtimePtr, double particleTypeId);
	public static native double JNIpixelpartparticletypesetvisible(String runtimePtr, double particleTypeId, double visible);
	public static native double JNIpixelpartparticletypeisvisible(String runtimePtr, double particleTypeId);
	public static native double JNIpixelpartparticletypesetlayer(String runtimePtr, double particleTypeId, double layer);
	public static native double JNIpixelpartparticletypegetlayer(String runtimePtr, double particleTypeId);
	public static native double JNIpixelpartparticletypegetmaterialid(String runtimePtr, double particleTypeId, ByteBuffer bufferPtr, double bufferSize);
	public static native double JNIpixelpartparticletypeismaterialbuiltin(String runtimePtr, double particleTypeId);
	public static native double JNIpixelpartparticletypegetmaterialparametercount(String runtimePtr, double particleTypeId);
	public static native double JNIpixelpartparticletypegetmaterialparameterids(String runtimePtr, double particleTypeId, ByteBuffer parameterIdBufferPtr);
	public static native double JNIpixelpartparticletypegetmaterialparametertype(String runtimePtr, double particleTypeId, double parameterId);
	public static native double JNIpixelpartparticletypegetmaterialparametervalue(String runtimePtr, double particleTypeId, double parameterId, ByteBuffer resultBufferPtr);
	public static native double JNIpixelpartparticletypegetrenderer(String runtimePtr, double particleTypeId);
	public static native String JNIpixelpartparticletypegetmeshrenderermeshresourceid(String runtimePtr, double particleTypeId);
	public static native String JNIpixelpartparticletypegetcount(String runtimePtr, double particleTypeId);
	public static native String JNIpixelpartparticletypegetlifespan(String runtimePtr, double particleTypeId);
	public static native String JNIpixelpartparticletypegetinitialsize(String runtimePtr, double particleTypeId);
	public static native String JNIpixelpartparticletypegetinitialrotation(String runtimePtr, double particleTypeId);
	public static native String JNIpixelpartparticletypegetinitialvelocity(String runtimePtr, double particleTypeId);
	public static native String JNIpixelpartparticletypegetinheritedvelocity(String runtimePtr, double particleTypeId);
	public static native String JNIpixelpartparticletypegetinitialopacity(String runtimePtr, double particleTypeId);
	public static native String JNIpixelpartparticletypegetmotionpath(String runtimePtr, double particleTypeId);
	public static native String JNIpixelpartparticletypegetsize(String runtimePtr, double particleTypeId);
	public static native String JNIpixelpartparticletypegetstretch(String runtimePtr, double particleTypeId);
	public static native String JNIpixelpartparticletypegetphysicalsize(String runtimePtr, double particleTypeId);
	public static native String JNIpixelpartparticletypegetrotation(String runtimePtr, double particleTypeId);
	public static native String JNIpixelpartparticletypegetrotationbyspeed(String runtimePtr, double particleTypeId);
	public static native String JNIpixelpartparticletypegetacceleration(String runtimePtr, double particleTypeId);
	public static native String JNIpixelpartparticletypegetradialacceleration(String runtimePtr, double particleTypeId);
	public static native String JNIpixelpartparticletypegetweight(String runtimePtr, double particleTypeId);
	public static native String JNIpixelpartparticletypegetbounce(String runtimePtr, double particleTypeId);
	public static native String JNIpixelpartparticletypegetfriction(String runtimePtr, double particleTypeId);
	public static native String JNIpixelpartparticletypegetcolor(String runtimePtr, double particleTypeId);
	public static native String JNIpixelpartparticletypegetopacity(String runtimePtr, double particleTypeId);
	public static native String JNIpixelpartparticletypegetlifespanvariance(String runtimePtr, double particleTypeId);
	public static native String JNIpixelpartparticletypegetsizevariance(String runtimePtr, double particleTypeId);
	public static native String JNIpixelpartparticletypegetrotationvariance(String runtimePtr, double particleTypeId);
	public static native String JNIpixelpartparticletypegetangularvelocityvariance(String runtimePtr, double particleTypeId);
	public static native String JNIpixelpartparticletypegetvelocityvariance(String runtimePtr, double particleTypeId);
	public static native String JNIpixelpartparticletypegetcolorvariance(String runtimePtr, double particleTypeId);
	public static native String JNIpixelpartparticletypegetopacityvariance(String runtimePtr, double particleTypeId);

	// Static property
	public static native double JNIpixelpartstaticpropertyboolvalue(String propertyPtr);
	public static native double JNIpixelpartstaticpropertyboolsetbasevalue(String propertyPtr, double value);
	public static native double JNIpixelpartstaticpropertyboolgetbasevalue(String propertyPtr);
	public static native double JNIpixelpartstaticpropertyintvalue(String propertyPtr);
	public static native double JNIpixelpartstaticpropertyintsetbasevalue(String propertyPtr, double value);
	public static native double JNIpixelpartstaticpropertyintgetbasevalue(String propertyPtr);
	public static native double JNIpixelpartstaticpropertyfloatvalue(String propertyPtr);
	public static native double JNIpixelpartstaticpropertyfloatsetbasevalue(String propertyPtr, double value);
	public static native double JNIpixelpartstaticpropertyfloatgetbasevalue(String propertyPtr);
	public static native double JNIpixelpartstaticpropertyfloat2value(String propertyPtr, ByteBuffer valueBufferPtr);
	public static native double JNIpixelpartstaticpropertyfloat2setbasevalue(String propertyPtr, ByteBuffer valueBufferPtr);
	public static native double JNIpixelpartstaticpropertyfloat2getbasevalue(String propertyPtr, ByteBuffer valueBufferPtr);
	public static native double JNIpixelpartstaticpropertyfloat3value(String propertyPtr, ByteBuffer valueBufferPtr);
	public static native double JNIpixelpartstaticpropertyfloat3setbasevalue(String propertyPtr, ByteBuffer valueBufferPtr);
	public static native double JNIpixelpartstaticpropertyfloat3getbasevalue(String propertyPtr, ByteBuffer valueBufferPtr);
	public static native double JNIpixelpartstaticpropertyfloat4value(String propertyPtr, ByteBuffer valueBufferPtr);
	public static native double JNIpixelpartstaticpropertyfloat4setbasevalue(String propertyPtr, ByteBuffer valueBufferPtr);
	public static native double JNIpixelpartstaticpropertyfloat4getbasevalue(String propertyPtr, ByteBuffer valueBufferPtr);

	// Animated property
	public static native double JNIpixelpartanimatedpropertyfloatat(String propertyPtr, double position);
	public static native double JNIpixelpartanimatedpropertyfloataddkeyframe(String propertyPtr, double position, double value);
	public static native double JNIpixelpartanimatedpropertyfloatremovekeyframe(String propertyPtr, double index);
	public static native double JNIpixelpartanimatedpropertyfloatsetkeyframevalue(String propertyPtr, double index, double value);
	public static native double JNIpixelpartanimatedpropertyfloatsetkeyframeposition(String propertyPtr, double index, double position);
	public static native double JNIpixelpartanimatedpropertyfloatclearkeyframes(String propertyPtr);
	public static native double JNIpixelpartanimatedpropertyfloatkeyframecount(String propertyPtr);
	public static native double JNIpixelpartanimatedpropertyfloatkeyframevalue(String propertyPtr, double index);
	public static native double JNIpixelpartanimatedpropertyfloatkeyframeindex(String propertyPtr, double position, double epsilon);
	public static native double JNIpixelpartanimatedpropertyfloatsetkeyframeinterpolation(String propertyPtr, double method);
	public static native double JNIpixelpartanimatedpropertyfloatgetkeyframeinterpolation(String propertyPtr);
	public static native double JNIpixelpartanimatedpropertyfloatenableadaptivecache(String propertyPtr);
	public static native double JNIpixelpartanimatedpropertyfloatenablefixedcache(String propertyPtr, double size);
	public static native double JNIpixelpartanimatedpropertyfloat2at(String propertyPtr, double position, ByteBuffer valueBufferPtr);
	public static native double JNIpixelpartanimatedpropertyfloat2addkeyframe(String propertyPtr, double position, ByteBuffer valueBufferPtr);
	public static native double JNIpixelpartanimatedpropertyfloat2removekeyframe(String propertyPtr, double index);
	public static native double JNIpixelpartanimatedpropertyfloat2setkeyframevalue(String propertyPtr, double index, ByteBuffer valueBufferPtr);
	public static native double JNIpixelpartanimatedpropertyfloat2setkeyframeposition(String propertyPtr, double index, double position);
	public static native double JNIpixelpartanimatedpropertyfloat2clearkeyframes(String propertyPtr);
	public static native double JNIpixelpartanimatedpropertyfloat2keyframecount(String propertyPtr);
	public static native double JNIpixelpartanimatedpropertyfloat2keyframevalue(String propertyPtr, double index, ByteBuffer valueBufferPtr);
	public static native double JNIpixelpartanimatedpropertyfloat2keyframeindex(String propertyPtr, double position, double epsilon);
	public static native double JNIpixelpartanimatedpropertyfloat2setkeyframeinterpolation(String propertyPtr, double method);
	public static native double JNIpixelpartanimatedpropertyfloat2getkeyframeinterpolation(String propertyPtr);
	public static native double JNIpixelpartanimatedpropertyfloat2enableadaptivecache(String propertyPtr);
	public static native double JNIpixelpartanimatedpropertyfloat2enablefixedcache(String propertyPtr, double size);
	public static native double JNIpixelpartanimatedpropertyfloat3at(String propertyPtr, double position, ByteBuffer valueBufferPtr);
	public static native double JNIpixelpartanimatedpropertyfloat3addkeyframe(String propertyPtr, double position, ByteBuffer valueBufferPtr);
	public static native double JNIpixelpartanimatedpropertyfloat3removekeyframe(String propertyPtr, double index);
	public static native double JNIpixelpartanimatedpropertyfloat3setkeyframevalue(String propertyPtr, double index, ByteBuffer valueBufferPtr);
	public static native double JNIpixelpartanimatedpropertyfloat3setkeyframeposition(String propertyPtr, double index, double position);
	public static native double JNIpixelpartanimatedpropertyfloat3clearkeyframes(String propertyPtr);
	public static native double JNIpixelpartanimatedpropertyfloat3keyframecount(String propertyPtr);
	public static native double JNIpixelpartanimatedpropertyfloat3keyframevalue(String propertyPtr, double index, ByteBuffer valueBufferPtr);
	public static native double JNIpixelpartanimatedpropertyfloat3keyframeindex(String propertyPtr, double position, double epsilon);
	public static native double JNIpixelpartanimatedpropertyfloat3setkeyframeinterpolation(String propertyPtr, double method);
	public static native double JNIpixelpartanimatedpropertyfloat3getkeyframeinterpolation(String propertyPtr);
	public static native double JNIpixelpartanimatedpropertyfloat3enableadaptivecache(String propertyPtr);
	public static native double JNIpixelpartanimatedpropertyfloat3enablefixedcache(String propertyPtr, double size);
	public static native double JNIpixelpartanimatedpropertyfloat4at(String propertyPtr, double position, ByteBuffer valueBufferPtr);
	public static native double JNIpixelpartanimatedpropertyfloat4addkeyframe(String propertyPtr, double position, ByteBuffer valueBufferPtr);
	public static native double JNIpixelpartanimatedpropertyfloat4removekeyframe(String propertyPtr, double index);
	public static native double JNIpixelpartanimatedpropertyfloat4setkeyframevalue(String propertyPtr, double index, ByteBuffer valueBufferPtr);
	public static native double JNIpixelpartanimatedpropertyfloat4setkeyframeposition(String propertyPtr, double index, double position);
	public static native double JNIpixelpartanimatedpropertyfloat4clearkeyframes(String propertyPtr);
	public static native double JNIpixelpartanimatedpropertyfloat4keyframecount(String propertyPtr);
	public static native double JNIpixelpartanimatedpropertyfloat4keyframevalue(String propertyPtr, double index, ByteBuffer valueBufferPtr);
	public static native double JNIpixelpartanimatedpropertyfloat4keyframeindex(String propertyPtr, double position, double epsilon);
	public static native double JNIpixelpartanimatedpropertyfloat4setkeyframeinterpolation(String propertyPtr, double method);
	public static native double JNIpixelpartanimatedpropertyfloat4getkeyframeinterpolation(String propertyPtr);
	public static native double JNIpixelpartanimatedpropertyfloat4enableadaptivecache(String propertyPtr);
	public static native double JNIpixelpartanimatedpropertyfloat4enablefixedcache(String propertyPtr, double size);

	static {
		System.loadLibrary("pixelpart");
	}
}
