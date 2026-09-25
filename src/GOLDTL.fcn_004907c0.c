typedef struct Stat {
	int v[9];
} Stat;
// SIZE 0x24

void __cdecl fcn_004f4830(int a, Stat* buf);

// FUNCTION: GOLD 0x4911f0
// SIZE: 212
// FUNCTION: GOLDTL 0x4907c0
// SIZE: 212
int __cdecl fcn_004907c0(char* e, int a2, int* out)
{
	Stat st;

	fcn_004f4830(2, &st);
	if (e[0xc] == 0 && st.v[6] == 1) {
		if (*(float*) (e + 0x1d0) < 0.4f) {
			*out = 2;
		} else {
			*out = 0;
		}
		return 1;
	}
	if (e[0xc] == 1 && st.v[6] == 0) {
		if (*(float*) (e + 0x1d0) < 0.4f) {
			*out = 2;
		} else {
			*out = 1;
		}
		return 1;
	}
	if (st.v[6] == 2 && *(float*) (e + 0x1d0) > 0.8f) {
		*out = (e[0xc] != 0);
		return 1;
	}
	return 0;
}
