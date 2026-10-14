


int __cdecl fcn_004fe470(int, int, int, int, int);

int __cdecl fcn_004ca930(char* a1, char* a2)
{
	int v;

	v = fcn_004fe470(*(int*) (a1 + 0x10), *(int*) (a1 + 0x14), *(int*) (a1 + 0x18), 0, 0);
	if (v == 0) {
		return 1;
	}
	if (a2 != 0) {
		a2[0] = 2;
		a2[1] = 7;
		*(int*) (a2 + 6) = v;
	}
	return 0;
}
