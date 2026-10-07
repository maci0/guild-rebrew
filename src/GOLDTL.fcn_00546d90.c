// FUNCTION: GOLD 0x53f050
// FUNCTION: GOLDTL 0x00546d90

extern int g_7749d8;
extern unsigned char* g_7d1980[];
extern void (__cdecl* g_7dc440[])(unsigned char*);

void __cdecl fcn_00546be0(unsigned char*);

void __cdecl fcn_00546d90(void)
{
	int i;
	unsigned char* p;

	for (i = 0; i <= g_7749d8 && i < 0x100; i++) {
		p = g_7d1980[i];
		if (p != 0 && *p < 0xa7) {
			fcn_00546be0(p);
			g_7dc440[*p](p);
		}
	}
}
