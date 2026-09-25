// FUNCTION: GOLD 0x00474190
// SIZE: 66

extern char g_00fb1020[]; /* 0x00fb1020 */

void __cdecl fcn_00472fc0(int id);

void __cdecl fcn_00474190(int k)
{
	int j;

	for (j = 0; j < *(int*) (g_00fb1020 + k * 0x2ac + 0x184); j++) {
		fcn_00472fc0(((int*) (g_00fb1020 + k * 0x2ac + 4))[j]);
	}
}
