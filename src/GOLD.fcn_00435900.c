extern float g_5eb788;

// FUNCTION: GOLD 0x435900
char* __cdecl fcn_00435900(char* a)
{
	float best;
	char* res;
	char* e;
	int i;

	best = g_5eb788;
	res = 0;
	if (a[0x194] != 0) {
		e = a + 0x154;
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
