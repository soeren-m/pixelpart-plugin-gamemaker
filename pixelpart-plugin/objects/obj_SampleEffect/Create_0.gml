event_inherited();

finished_event.subscribe(function()
{
	show_debug_message("Effect finished");
});
effect_event.subscribe(function(_event)
{
	show_debug_message("Effect event \"{0}\" invoked (id={1})",
		_event.event_name, _event.event_id);
});

var _particle_type = get_particle_type_at_index(0);
var _particle_type_index = 0;
while !is_undefined(_particle_type)
{
	show_debug_message("Particle type \"{0}\": id={1} parent_id={2}",
		_particle_type.get_name(), _particle_type.get_id(), _particle_type.get_parent_id());

	_particle_type_index++;
	_particle_type = get_particle_type_at_index(_particle_type_index);
}

var _node = get_node_at_index(0);
var _node_index = 0;
while !is_undefined(_node)
{
	var _typestr = "Node";
	switch (_node.get_type())
	{
		case PixelpartNodeType.GROUP_NODE:
			_typestr = "GroupNode";
			break;
		case PixelpartNodeType.PARTICLE_EMITTER:
			_typestr = "ParticleEmitter";
			break;
		case PixelpartNodeType.ATTRACTION_FIELD:
			_typestr = "AttractionField";
			break;
		case PixelpartNodeType.ACCELERATION_FIELD:
			_typestr = "AccelerationField";
			break;
		case PixelpartNodeType.VECTOR_FIELD:
			_typestr = "VectorField";
			break;
		case PixelpartNodeType.NOISE_FIELD:
			_typestr = "NoiseField";
			break;
		case PixelpartNodeType.DRAG_FIELD:
			_typestr = "DragField";
			break;
		case PixelpartNodeType.LINE_COLLIDER:
			_typestr = "LineCollider";
			break;
		case PixelpartNodeType.PLANE_COLLIDER:
			_typestr = "PlaneCollider";
			break;
		case PixelpartNodeType.DIRECTIONAL_LIGHT_SOURCE:
			_typestr = "DirectionalLightSource";
			break;
		case PixelpartNodeType.POINT_LIGHT_SOURCE:
			_typestr = "PointLightSource";
			break;
		case PixelpartNodeType.SPOT_LIGHT_SOURCE:
			_typestr = "SpotLightSource";
			break;
		default:
			_typestr = "Node";
			break;
	}

	show_debug_message("Node \"{0}\": id={1} parent_id={2} type={3}",
		_node.get_name(), _node.get_id(), _node.get_parent_id(), _typestr);

	_node_index++;
	_node = get_node_at_index(_node_index);
}
