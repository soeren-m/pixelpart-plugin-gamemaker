varying vec2 v_vTextureCoord;
varying vec4 v_vColour;
varying float v_vLife;

uniform vec3 u_Emission;
uniform int u_ColorBlendMode;
uniform int u_SpriteSheetRowNumber;
uniform int u_SpriteSheetColumnNumber;
uniform int u_SpriteSheetOrigin;
uniform int u_SpriteAnimationNumFrames;
uniform int u_SpriteAnimationStartFrame;
uniform float u_SpriteAnimationDuration;
uniform bool u_SpriteAnimationLoop;

int pixelpart_Mod(int x, int y)
{
	return x - y * (x / y);
}

vec2 pixelpart_AnimateSprite(vec2 textureCoord, float life)
{
	int animationFrame = u_SpriteAnimationStartFrame;
	animationFrame += u_SpriteAnimationLoop
		? int(mod(life / u_SpriteAnimationDuration * float(u_SpriteAnimationNumFrames), float(u_SpriteAnimationNumFrames)))
		: int(clamp(life / u_SpriteAnimationDuration * float(u_SpriteAnimationNumFrames), 0.0, float(u_SpriteAnimationNumFrames - 1)));
	animationFrame = pixelpart_Mod(animationFrame, u_SpriteSheetRowNumber * u_SpriteSheetColumnNumber);

	vec2 spriteCornerOffset = vec2(
		textureCoord.x / float(u_SpriteSheetRowNumber),
		textureCoord.y / float(u_SpriteSheetColumnNumber));

	if(u_SpriteSheetOrigin == 0)
	{
		return spriteCornerOffset + vec2(
			float(pixelpart_Mod(animationFrame, u_SpriteSheetRowNumber)) / float(u_SpriteSheetRowNumber),
			float(animationFrame / u_SpriteSheetRowNumber) / float(u_SpriteSheetColumnNumber));
	}
	else if(u_SpriteSheetOrigin == 1)
	{
		return spriteCornerOffset + vec2(
			1.0 - float(pixelpart_Mod(animationFrame, u_SpriteSheetRowNumber)) / float(u_SpriteSheetRowNumber) - 1.0 / float(u_SpriteSheetRowNumber),
			float(animationFrame / u_SpriteSheetRowNumber) / float(u_SpriteSheetColumnNumber));
	}
	else if(u_SpriteSheetOrigin == 2)
	{
		return spriteCornerOffset + vec2(
			float(pixelpart_Mod(animationFrame, u_SpriteSheetRowNumber)) / float(u_SpriteSheetRowNumber),
			1.0 - float(animationFrame / u_SpriteSheetRowNumber) / float(u_SpriteSheetColumnNumber) - 1.0 / float(u_SpriteSheetColumnNumber));
	}
	else if(u_SpriteSheetOrigin == 3)
	{
		return spriteCornerOffset + vec2(
			1.0 - float(pixelpart_Mod(animationFrame, u_SpriteSheetRowNumber)) / float(u_SpriteSheetRowNumber) - 1.0 / float(u_SpriteSheetRowNumber),
			1.0 - float(animationFrame / u_SpriteSheetRowNumber) / float(u_SpriteSheetColumnNumber) - 1.0 / float(u_SpriteSheetColumnNumber));
	}

	return textureCoord;
}

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
	vec2 textureCoord = pixelpart_AnimateSprite(v_vTextureCoord, v_vLife);

	vec4 color = texture2D(gm_BaseTexture, textureCoord);
	color = pixelpart_Blend(color, v_vColour);
	color.rgb += u_Emission;

	gl_FragColor = color;
}
