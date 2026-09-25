// FUNCTION: GOLD 0x004e6600
// SIZE: 79
// FUNCTION: GOLDTL 0x4e81c0
// SIZE: 79

int __cdecl fcn_004e7b70(int, int*, int*);
int __cdecl fcn_004e8240(int, int, int, int, int);

int __cdecl fcn_004e81c0(int a1, int a2)
{
	int l0[6];
	int l1[6];

	if (fcn_004e7b70(a1, l1, l0) == 0) {
		return -1;
	}
	if (a2 == 0) {
		return -1;
	}
	return fcn_004e8240(l0[0], a1, a2, 2, 1);
}
