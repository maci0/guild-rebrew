extern float g_662a94;
// FUNCTION: GOLDTL 0x00502780
// SIZE: 77

float __cdecl fcn_005025a0(int, int);

float __cdecl fcn_00502780(int a, int id)
{
	int i;

	for (i = 0; i < 0x55; i++) {
		if (*(unsigned short*) ((char*) 0x85ab90 + a * 0x2a90 + i * 0x80) == id) {
			return fcn_005025a0(a, i);
		}
	}
	return g_662a94;
}
