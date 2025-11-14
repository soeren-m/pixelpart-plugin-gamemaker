enum PixelpartNodeType
{
	GROUP_NODE = 0,
	PARTICLE_EMITTER = 1,
	ATTRACTION_FIELD = 2,
	ACCELERATION_FIELD = 3,
	VECTOR_FIELD = 4,
	NOISE_FIELD = 5,
	DRAG_FIELD = 6,
	LINE_COLLIDER = 7,
	PLANE_COLLIDER = 8,
	DIRECTIONAL_LIGHT_SOURCE = 9,
	POINT_LIGHT_SOURCE = 10,
	SPOT_LIGHT_SOURCE = 11
}

function pixelpart_create_node(_effect_ptr, _node_id)
{
	var _node_type = pixelpart_node_get_type(_effect_ptr, _node_id);

	switch (_node_type)
	{
		case PixelpartNodeType.GROUP_NODE:
			return new PixelpartGroupNode(_effect_ptr, _node_id);
		case PixelpartNodeType.PARTICLE_EMITTER:
			return new PixelpartParticleEmitter(_effect_ptr, _node_id);
		case PixelpartNodeType.ATTRACTION_FIELD:
			return new PixelpartAttractionField(_effect_ptr, _node_id);
		case PixelpartNodeType.ACCELERATION_FIELD:
			return new PixelpartAccelerationField(_effect_ptr, _node_id);
		case PixelpartNodeType.VECTOR_FIELD:
			return new PixelpartVectorField(_effect_ptr, _node_id);
		case PixelpartNodeType.NOISE_FIELD:
			return new PixelpartNoiseField(_effect_ptr, _node_id);
		case PixelpartNodeType.DRAG_FIELD:
			return new PixelpartDragField(_effect_ptr, _node_id);
		case PixelpartNodeType.LINE_COLLIDER:
			return new PixelpartLineCollider(_effect_ptr, _node_id);
		case PixelpartNodeType.PLANE_COLLIDER:
			return new PixelpartPlaneCollider(_effect_ptr, _node_id);
		case PixelpartNodeType.DIRECTIONAL_LIGHT_SOURCE:
			return new PixelpartDirectionalLightSource(_effect_ptr, _node_id);
		case PixelpartNodeType.POINT_LIGHT_SOURCE:
			return new PixelpartPointLightSource(_effect_ptr, _node_id);
		case PixelpartNodeType.SPOT_LIGHT_SOURCE:
			return new PixelpartSpotLightSource(_effect_ptr, _node_id);
		default:
			return undefined;
	}
}
