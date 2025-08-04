varying vec2 v_vTextureCoord;
varying vec4 v_vColour;

uniform vec3 u_Emission;
uniform int u_ColorBlendMode;

vec4 pixelpart_Blend(vec4 colorA, vec4 colorB)
{
	vec4 result = colorA;

	if(u_ColorBlendMode == 0)
	{
		result = colorA * colorB;
	}
	else if(u_ColorBlendMode == 1)
	{
		result.rgb = clamp(colorA.rgb + colorB.rgb, vec3(0.0, 0.0, 0.0), vec3(1.0, 1.0, 1.0));
		result.a = colorA.a * colorB.a;
	}
	else if(u_ColorBlendMode == 2)
	{
		result.rgb = clamp(colorA.rgb - colorB.rgb, vec3(0.0, 0.0, 0.0), vec3(1.0, 1.0, 1.0));
		result.a = colorA.a * colorB.a;
	}
	else if(u_ColorBlendMode == 3)
	{
		result.rgb = abs(colorA.rgb - colorB.rgb);
		result.a = colorA.a * colorB.a;
	}
	else if(u_ColorBlendMode == 4)
	{
		result.rgb = vec3(1.0, 1.0, 1.0) - (vec3(1.0, 1.0, 1.0) - colorA.rgb) * (vec3(1.0, 1.0, 1.0) - colorB.rgb);
		result.a = colorA.a * colorB.a;
	}
	else if(u_ColorBlendMode == 5)
	{
		result.r = (colorA.r < 0.5) ? (2.0 * colorA.r * colorB.r) : (1.0 - 2.0 * (1.0 - colorA.r) * (1.0 - colorB.r));
		result.g = (colorA.g < 0.5) ? (2.0 * colorA.g * colorB.g) : (1.0 - 2.0 * (1.0 - colorA.g) * (1.0 - colorB.g));
		result.b = (colorA.b < 0.5) ? (2.0 * colorA.b * colorB.b) : (1.0 - 2.0 * (1.0 - colorA.b) * (1.0 - colorB.b));
		result.a = colorA.a * colorB.a;
	}
	else if(u_ColorBlendMode == 6)
	{
		result.rgb = max(colorA.rgb, colorB.rgb);
		result.a = colorA.a * colorB.a;
	}
	else if(u_ColorBlendMode == 7)
	{
		result.rgb = min(colorA.rgb, colorB.rgb);
		result.a = colorA.a * colorB.a;
	}
	else if(u_ColorBlendMode == 8)
	{
		result.rgb = colorB.rgb;
		result.a = colorA.a * colorB.a;
	}

	return result;
}

void main()
{
	vec4 color = texture2D(gm_BaseTexture, v_vTextureCoord);
	color = pixelpart_Blend(color, v_vColour);
	color.rgb += u_Emission;

	gl_FragColor = color;
}
