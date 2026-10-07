extern char g_85ab90[];
// FUNCTION: GOLD 0x004ffbf0
// FUNCTION: GOLDTL 0x00502780

float __cdecl fcn_005025a0(int, int);

float __cdecl fcn_00502780(int a, int id)
{
	int i;

	for (i = 0; i < 0x55; i++) {
		if (*(unsigned short*) (g_85ab90 + a * 0x2a90 + i * 0x80) == id) {
			return fcn_005025a0(a, i);
		}
	}
	return -1.0f;
}
