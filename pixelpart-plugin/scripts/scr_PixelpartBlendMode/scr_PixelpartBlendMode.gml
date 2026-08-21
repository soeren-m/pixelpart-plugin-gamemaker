// Mode that determines how particles are blended together and are composed with other objects in the effect.
enum PixelpartBlendMode
{
	// Particles are not blended together and occlude each other.
	OFF = 0,

	// Particles are blended together based on their opacity.
	ALPHA = 1,

	// Particle colors are added together.
	ADDITIVE = 2,

	// Particle colors are subtracted from each other.
	SUBTRACTIVE = 3
}
