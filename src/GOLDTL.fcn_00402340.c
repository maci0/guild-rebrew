// GLOBAL: GOLD 0x5f10f8
extern int g_675170;
// GLOBAL: GOLD 0x14eaae0
extern char g_1552000[];
// FUNCTION: GOLD 0x00401e70
// SIZE: 37
// FUNCTION: GOLDTL 0x402340
// SIZE: 37

extern int (__stdcall *g_662350)(int, int, int, int, int, int);

void __cdecl fcn_00402340(int a1, int a2)
{
	int h;

	h = g_675170;
	if (h != -1) {
		g_662350(h, a1, a2, 0, (int) g_1552000, 0x10);
	}
}
