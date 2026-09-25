// FUNCTION: GOLD 0x004f8140
// SIZE: 115
// FUNCTION: GOLDTL 0x004fa530
// SIZE: 115

extern char g_679060[];

int __cdecl fcn_005dae70(unsigned char* a1, int* a2);
void __cdecl fcn_0051af00(void*, int, ...);

int __cdecl fcn_004fa530(unsigned char* a1, int* a2)
{
	int r;

	r = 2;
	if ((*a2 == 3 || *a2 == 1) && a1[0x166] != 0 && a1[0x166] <= 0x1b) {
		if (*a2 == 3 && a1[2] == 6) {
			return fcn_005dae70(a1, a2);
		}
		if (*a2 == 1 && a1[2] == 6) {
			fcn_0051af00((char*) a2 + 0x14, (int) g_679060, 0x1e23);
			return 2;
		}
	} else {
		r = 1;
	}
	return r;
}
