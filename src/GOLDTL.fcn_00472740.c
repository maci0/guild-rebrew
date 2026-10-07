extern char* g_1015ea0;
extern char g_102d280[];

// FUNCTION: GOLDTL 0x472740
void __cdecl fcn_00472740(int i, int v)
{
	*(int*) (g_102d280 + *(int*) (g_1015ea0 + i * 0x2f4 + 0x88) * 0x160) = v;
}
