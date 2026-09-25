extern float g_6628a8;

// FUNCTION: GOLDTL 0x4356c0
// SIZE: 69
char* __cdecl fcn_004356c0(char* a)
{
	float best;
	char* res;
	char* e;
	int i;

	best = g_6628a8;
	res = 0;
	if (a[0x4a0] != 0) {
		e = a + 0x460;
		for (i = 3; i != 0; i--) {
			if (*(int*) (e + 0x28) != 0 && *(float*) e > best) {
				best = *(float*) e;
				res = e - 0x40;
			}
			e -= 0x7c;
		}
	}
	return res;
}
