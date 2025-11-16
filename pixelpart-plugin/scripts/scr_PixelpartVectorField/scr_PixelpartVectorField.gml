// Filtering techniques.
enum PixelpartVectorFieldFilter
{
	NONE = 0,
	LINEAR = 1
}

/// @desc Force field that accelerates particles in the direction of a predefined grid of vectors.
/// A particle in the field follows the vector specified in the vector field at that location.
/// @param {pointer} _effect_ptr Pointer to internal effect runtime object
/// @param {real} _node_id Node ID
function PixelpartVectorField(_effect_ptr, _node_id) : PixelpartForceField(_effect_ptr, _node_id) constructor
{
	// How directly particles follow the vectors in the force field.
	// If set to 0, the field applies forces to the particles over time.
	// If set to 1, particles follow the vectors in the force field directly.
	tightness = new PixelpartAnimatedPropertyFloat(
		ptr(pixelpart_vector_field_get_tightness(_effect_ptr, _node_id)));

	/// @desc Set how velocity values are interpolated between the cells of the vector field.
	/// @param {real} _filter Filtering algorithm to use
	static set_vector_filter = function(_filter)
	{
		pixelpart_vector_field_set_vector_field_filter(effect_ptr, node_id, _filter);
	}

	/// @desc How velocity values are interpolated between the cells of the vector field.
	/// @returns {real} Filtering algorithm used
	static get_vector_filter = function()
	{
		return pixelpart_vector_field_get_vector_field_filter(effect_ptr, node_id);
	}
}
