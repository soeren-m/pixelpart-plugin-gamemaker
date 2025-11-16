// Keyframe interpolation types.
enum PixelpartInterpolationType
{
	// Values change abruptly between keyframes.
	OFF = 0,

	// Values are interpolated linearly.
	LINEAR = 1,

	// Values are interpolated with Spline interpolation producing smooth transitions.
	SPLINE = 2,

	// Values are interpolated with Bezier interpolation producing smooth transitions.
	BEZIER = 3
}
