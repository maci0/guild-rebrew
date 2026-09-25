// FUNCTION: GOLDTL 0x4b4fa0
// SIZE: 115
// FUNCTION: GOLD 0x004b4e30
// SIZE: 128

extern double g_6629f8;
extern float g_66414c;

double __cdecl fcn_004fc460(float*);

int __cdecl fcn_004b4fa0(void)
{
	float buf[10];

	if (fcn_004fc460(buf) > g_6629f8)
		return 0;
	if (buf[3] < g_66414c)
		return 0;
	if (buf[1] < g_66414c)
		return 0;
	if (buf[2] < g_66414c)
		return 0;
	return 1;
}
