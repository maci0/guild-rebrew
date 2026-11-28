extern float flt_1_0;
extern float flt_0_0;

/* ADDRESS: GOLDTL 0x004fef00 */
/* ADDRESS: GOLDDE 0x004ea980 */
int __cdecl gm_EstimateEntityDeathAge(char* p)
{
	float v;
	float s;
	float t;
	int n;

	n = 0;
	s = *(float*) (p + 0x14);
	for (v = *(float*) (p + 0x1c); v > flt_1_0; v = v - s + s / v) {
		n++;
	}
	t = *(float*) (p + 0x20) - *(unsigned short*) (p + 0xa);
	if (!(t > flt_0_0)) {
		t = flt_0_0;
	}
	return (int) (*(unsigned short*) (p + 0xa) + n + t);
}
