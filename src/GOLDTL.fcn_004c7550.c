// FUNCTION: GOLD 0x004c69c0
// SIZE: 86
// FUNCTION: GOLDTL 0x4c7550
// SIZE: 86

char* __cdecl fcn_00508e40(int);

int __cdecl fcn_004c7550(char* a1)
{
	int i;
	char* e;
	int v;

	if (*(int*) (a1 + 0x10) == -1) {
		return 1;
	}
	for (i = 0; i < 0x10; i++) {
		e = fcn_00508e40(*(int*) (a1 + 0x14 + i * 4));
		if (e != 0 && (e[2] == 6 || e[2] == 7)) {
			v = *(int*) (e + 0x20c);
			if (v != -1 && v != *(int*) (a1 + 0x10)) {
				return 1;
			}
		}
	}
	return 0;
}
