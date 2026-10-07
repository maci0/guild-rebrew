// FUNCTION: GOLD 0x0040e750
// FUNCTION: GOLDTL 0x0040f660

extern char* g_6b7ebc;
extern char* g_6b7e98;
extern int g_6b5cbc;
extern int g_6b5cc0;
int __cdecl fcn_00414d20(int a, int b, int c, int d, int e, int f, int g, int h);
void __cdecl fcn_00425bf0(char* g, int h, const char* msg);

int __cdecl fcn_0040f660(int* a1, int* a2, int* a3, int* a4, int* a5, int* a6, int* a7)
{
	if (g_6b7ebc != 0 && *(void**) (g_6b7ebc + 0x44) == (void*) fcn_0040f660) {
		if (g_6b5cbc == 0 && g_6b5cc0 == 0) {
			return 0;
		}
		*(void**) (g_6b7e98 + 0xc60) = (void*) fcn_0040f660;
		return 0;
	}
	if (*(int*) (g_6b7e98 + 0xc84) == 1) {
		*(void**) (g_6b7e98 + 0xc60) = (void*) fcn_0040f660;
	}
	if (!fcn_00414d20(*a1 / 17, 6, *a2, *a3, *a4, *a5, *a6, *a7)) {
		fcn_00425bf0(g_6b7e98, *(int*) (g_6b7e98 + 0x118), "call failed");
	}
	return 1;
}
