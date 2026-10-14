extern float g_6628a0;
extern float g_6628a8;

/* ADDRESS: GOLD 0x004fc7a0 */
/* ADDRESS: GOLDTL 0x004fef00 */
int __cdecl fcn_004fef00(char* p)
{
	float v;
	float s;
	float t;
	int n;

	n = 0;
	s = *(float*) (p + 0x14);
	for (v = *(float*) (p + 0x1c); v > g_6628a0; v = v - s + s / v) {
		n++;
	}
	t = *(float*) (p + 0x20) - *(unsigned short*) (p + 0xa);
	if (!(t > g_6628a8)) {
		t = g_6628a8;
	}
	return (int) (*(unsigned short*) (p + 0xa) + n + t);
}
