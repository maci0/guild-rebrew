// FUNCTION: GOLD 0x4cd180
// FUNCTION: GOLDTL 0x4cdd00

int __cdecl fcn_004f0960(int);
int __cdecl fcn_004f09c0(int);

int __cdecl fcn_004cdd00(char* a1, char* a2)
{
	int r;
	int v;

	if (a2 != 0) {
		a2[0] = 2;
		a2[1] = 0;
		*(int*) (a2 + 6) = 0;
	}
	v = *(int*) (a1 + 0x10);
	if (v == 0x6154436e) {
		r = fcn_004f0960(*(int*) (a1 + 0x14));
	} else if (v == 0x6454436e) {
		r = fcn_004f09c0(*(int*) (a1 + 0x14));
	} else {
		return -1;
	}
	if (a2 != 0 && r != 0) {
		*a2 = 1;
	}
	if (r == 0) {
		return -1;
	}
	return 0;
}
