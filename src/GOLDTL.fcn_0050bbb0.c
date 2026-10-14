extern char g_7f4ca0[];
/* ADDRESS: GOLD 0x00508a50 */
/* ADDRESS: GOLDTL 0x0050bbb0 */

float __cdecl fcn_0050bbb0(int idx)
{
	char* p;
	float v;

	p = g_7f4ca0 + idx * 0x21c;
	if (p == 0) {
		return 1.0f;
	}
	v = *(unsigned char*) (p + 0x80);
	if (v <= 42.0f) {
		return 1.0f;
	}
	return (float) (v * (1.0 / 1008.0) + 1.0);
}
