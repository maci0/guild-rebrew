// FUNCTION: GOLD 0x004c3eb0
// FUNCTION: GOLDTL 0x4c4820

extern unsigned int g_aed320;
extern unsigned char g_aed2a4;
extern unsigned char g_aed2a5[];

int __cdecl fcn_004c4820(unsigned char kind, int value)
{
	unsigned char* p;

	if (g_aed320 + 5 >= 0x77) {
		return 1;
	}
	p = &g_aed2a5[g_aed320];
	g_aed320 += 5;
	g_aed2a4++;
	p[0] = kind;
	*(int*) (p + 1) = value;
	return 0;
}
