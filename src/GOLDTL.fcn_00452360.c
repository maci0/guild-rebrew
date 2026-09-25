typedef int(__stdcall* FnVB)(void* self, int len, int usage, int fvf, int pool, void** out);

extern void** g_6b5de0;
extern int g_6b8710;
extern int g_6b8714;
extern int g_67bc4c;
extern void* g_104095c;
extern int g_6b8718;

// FUNCTION: GOLDTL 0x452360
// SIZE: 55
void __cdecl fcn_00452360(void)
{
	((FnVB) ((void**) *g_6b5de0)[0x5c / 4])(g_6b5de0, g_6b8714 * g_67bc4c, 0x248, g_6b8710, 0, &g_104095c);
	g_6b8718 = 0;
}
