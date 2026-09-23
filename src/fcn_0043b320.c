// GLOBAL: GOLDTL 0x1042a08
extern int g_1042a08;
// GLOBAL: GOLDTL 0x10432a8
extern int g_10432a8;
// GLOBAL: GOLDTL 0x1042a04
extern int g_1042a04;
// GLOBAL: GOLDTL 0x1052bac
extern int g_1052bac;
// FUNCTION: GOLDTL 0x43b320
// SIZE: 59

void __cdecl fcn_0043ad20(void*, void*);
void __cdecl fcn_0043b170(void*, void*, int, int);

void __cdecl fcn_0043b320(void* a1, void* a2, int a3)
{
	fcn_0043ad20(a1, a2);
	g_1042a08 = 0;
	g_10432a8 = 0;
	g_1042a04 = 0;
	g_1052bac = 0;
	fcn_0043b170(a1, a2, a3, 1);
}
