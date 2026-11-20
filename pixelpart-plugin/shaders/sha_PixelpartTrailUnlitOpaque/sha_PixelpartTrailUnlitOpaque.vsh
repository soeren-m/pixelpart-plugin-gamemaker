attribute vec3 in_Position;
attribute vec4 in_Colour;
attribute vec2 in_TextureCoord;
attribute vec2 in_LifeId;

varying vec2 v_vTextureCoord;
varying vec4 v_vColour;

void main()
{
	vec4 objectSpacePosition = vec4(in_Position.x, in_Position.y, in_Position.z, 1.0);
	gl_Position = gm_Matrices[MATRIX_WORLD_VIEW_PROJECTION] * objectSpacePosition;

	v_vTextureCoord = in_TextureCoord;
	v_vColour = in_Colour;
}
