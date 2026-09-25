// FUNCTION: GOLD 0x53f0a0
// SIZE: 82
// FUNCTION: GOLDTL 0x00546de0
// SIZE: 82

extern int g_7749d4;
extern unsigned char g_77e980[];
extern void (__cdecl* g_7dc440[])(unsigned char*);

void __cdecl fcn_00546be0(unsigned char*);

void __cdecl fcn_00546de0(void)
{
	int i;
	unsigned char* p;

	for (i = 0; i <= g_7749d4 && i < 0x400; i++) {
		p = g_77e980 + i * 0x14c;
		if (*p != 0 && (p[0x78] & 0x10) != 0 && *p < 0xa7) {
			fcn_00546be0(p);
			g_7dc440[*p](p);
		}
	}
}
