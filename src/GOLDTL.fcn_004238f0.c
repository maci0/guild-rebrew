// GLOBAL: GOLDTL 0x6b7d7c
extern int g_6b7d7c;
// GLOBAL: GOLD 0x63319c
extern int g_6b7d7c;
// FUNCTION: GOLD 0x00427390
// SIZE: 40
// FUNCTION: GOLDTL 0x4238f0
// SIZE: 40

void __cdecl fcn_0042aa20(int, int);

void __cdecl fcn_004238f0(int* p, int a2)
{
	if (*(int*) ((char*)&g_6b7d7c) == 0) {
		return;
	}
	if (p == 0) {
		return;
	}
	*(int*) ((char*) p + 0xc) = a2;
	fcn_0042aa20(*(int*) p, a2);
}
