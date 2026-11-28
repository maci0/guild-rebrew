// Hermite blend. The parentheses around the first two terms keep c2 from
// evaluating the third product first.

/* ADDRESS: GOLDTL 0x004517e0 */
/* ADDRESS: GOLDDE 0x004473c0 */
float __cdecl d3_EvalHermiteSpline(float p0, float p1, float m0, float m1, float t)
{
	float t2;
	float t3;

	t2 = t * t;
	t3 = t * t2;
	return (p0 * (2.0f * t3 - 3.0f * t2 + 1.0f) + p1 * (3.0f * t2 - 2.0f * t3))
		+ m0 * (t3 - 2.0f * t2 + t) + m1 * (t3 - t2);
}
