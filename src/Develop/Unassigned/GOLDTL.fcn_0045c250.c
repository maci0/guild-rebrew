/* ADDRESS: GOLDTL 0x0045c250 */
int __cdecl fcn_0045c250(float a, float b, float c, float d)
{
	float t;

	if (a > b) {
		t = a;
		a = b;
		b = t;
	}
	return (int) ((b - a) / c * d + a + 0.5);
}
