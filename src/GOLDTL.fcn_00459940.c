// FUNCTION: GOLDTL 0x459940
// SIZE: 55

void __cdecl fcn_00459940(char* a1, char* a2, float a3)
{
	if (a1 != 0 && a2 != 0) {
		if (a3 != *(float*) 0x6628a8) {
			*(float*) (a2 + 8) = a3 * *(float*) 0x662dc4;
		} else {
			*(int*) (a2 + 8) = 0;
		}
	}
}
