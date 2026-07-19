/// @desc Force field that accelerates particles towards or away from its center.
/// Attraction fields are spherical force fields that pull particles towards their center.
/// You can also make them repel particles by setting a negative strength value.
/// @param {string} _effect_ptr Pointer to internal effect runtime object
/// @param {real} _node_id Node ID
function PixelpartAttractionField(_effect_ptr, _node_id) : PixelpartForceField(_effect_ptr, _node_id) constructor
{
	// How the strength of the force field decreases based on the distance to the center.
	falloff_power = new PixelpartAnimatedPropertyFloat(
		pixelpart_attraction_field_get_falloff_power(_effect_ptr, _node_id));
}
