extern char* g_6b7ebc;
extern char* g_6b7e98;
extern int g_6b5cbc;
extern int g_6b5cc0;

void __cdecl fcn_00414d20(int, int, int, int, int, int, int, int);

// FUNCTION: GOLDTL 0x40f720

/* Script command: forwards its seven arguments to fcn_00414d20, the first
 * divided by 14; while the script is suspended it re-arms itself. */
int __cdecl fcn_0040f720(int* a1, int* a2, int* a3, int* a4, int* a5, int* a6, int* a7)
{
	if (g_6b7ebc != 0 && *(int (__cdecl**)()) (g_6b7ebc + 0x44) == (int (__cdecl*)()) fcn_0040f720) {
		if (g_6b5cbc == 0 && g_6b5cc0 == 0) {
			return 0;
		}
		*(int (__cdecl**)()) (g_6b7e98 + 0xc60) = (int (__cdecl*)()) fcn_0040f720;
		return 0;
	}
	if (*(int*) (g_6b7e98 + 0xc84) == 1) {
		*(int (__cdecl**)()) (g_6b7e98 + 0xc60) = (int (__cdecl*)()) fcn_0040f720;
	}
	fcn_00414d20(*a1 / 14, 6, *a2, *a3, *a4, *a5, *a6, *a7);
	return 1;
}
