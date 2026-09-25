typedef struct Stat {
	int v[8];
	int(__cdecl* check)(int a, int kind, int* out);
} Stat;
// SIZE 0x24

int __cdecl fcn_004f4830(int a, Stat* st);

// FUNCTION: GOLD 0x4a8a50
// SIZE: 128
// FUNCTION: GOLDTL 0x4a8b70
// SIZE: 122
int __cdecl fcn_004a8b70(int a1, int a2, char* x, int a4, char* out)
{
	Stat st;

	if (fcn_004f4830(*(int*) (x + 4), &st) && st.check(a2, st.v[0] & 0xff, (int*) &x)) {
		if ((int) x != st.v[6] && (int) x >= st.v[1] && (int) x <= st.v[2]) {
			out[0] = 0x11;
			*(int*) (out + 4) = st.v[0] & 0xff;
			*(int*) (out + 8) = (int) x;
			return 1;
		}
	}
	return 0;
}
