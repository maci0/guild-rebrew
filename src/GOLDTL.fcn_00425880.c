// FUNCTION: GOLDTL 0x00425880

extern void* g_6b7d80;
extern void* g_6b7d84;
void __cdecl fcn_00425810(void);
void __cdecl fcn_0042a6a0(void* p);
void __cdecl fcn_0041ddd0(void* p);
void __cdecl fcn_00422100(void);

void __cdecl fcn_00425880(void)
{
	fcn_00425810();
	if (g_6b7d80 != 0) {
		fcn_0042a6a0(g_6b7d80);
		g_6b7d80 = 0;
	}
	if (g_6b7d84 != 0) {
		fcn_0041ddd0(g_6b7d84);
		g_6b7d84 = 0;
	}
	fcn_00422100();
}
