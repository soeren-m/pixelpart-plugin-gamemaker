varying vec2 v_vTextureCoord;
varying vec4 v_vColour;

void main()
{
	gl_FragColor = v_vColour * texture2D(gm_BaseTexture, v_vTextureCoord);
}
