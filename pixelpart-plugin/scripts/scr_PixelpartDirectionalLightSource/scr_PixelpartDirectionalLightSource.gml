/// @desc Light source with light coming from a specific direction.
/// Direction lights mimic light sources that are very far away and consequently contain light rays of almost parallel direction.
/// Such light sources are useful to simulate sunlight, for example.
/// The direction is determined by the node's orientation property.
/// @param {pointer} _effect_ptr Pointer to internal effect runtime object
/// @param {real} _node_id Node ID
function PixelpartDirectionalLightSource(_effect_ptr, _node_id) : PixelpartLightSource(_effect_ptr, _node_id) constructor
{

}
