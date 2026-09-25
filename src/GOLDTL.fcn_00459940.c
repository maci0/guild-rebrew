// FUNCTION: GOLD 0x45d950
// SIZE: 64
// FUNCTION: GOLDTL 0x459940
// SIZE: 55

extern float g_6628a8;

void __cdecl fcn_00459940(char* a1, char* a2, float a3)
{
	if (a1 != 0 && a2 != 0) {
		if (a3 != g_6628a8) {
			*(float*) (a2 + 8) = a3 * -0.000001f;
		} else {
			*(int*) (a2 + 8) = 0;
		}
	}
}
