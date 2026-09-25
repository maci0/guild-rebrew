extern char* g_6b7e98;
// GLOBAL: GOLD 0x5f28a4
extern char g_676924[];
// FUNCTION: GOLD 0x0040e6f0
// SIZE: 84
// FUNCTION: GOLDTL 0x40f600
// SIZE: 84

int __cdecl fcn_00414d20(int, int, int, int);
void __cdecl fcn_00425bf0(void*, int, char*);

int __cdecl fcn_0040f600(int* a1, int* a2, int* a3)
{
	if (fcn_00414d20(*a1 / 17, 2, *a2, *a3) == 0) {
		fcn_00425bf0(g_6b7e98, *(int*) ((char*) g_6b7e98 + 0x118), g_676924);
	}
	return 1;
}
