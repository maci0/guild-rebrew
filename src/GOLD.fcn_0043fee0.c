// FUNCTION: GOLD 0x43fee0
// The b + (a + s) grouping keeps s on the FPU stack across both compares.

// SIZE 0x1
typedef struct State {
	unsigned char lo : 2;
	unsigned char st : 3;
	unsigned char hi : 3;
} State;

char __cdecl fcn_0043fee0(char* a, char* b, int unused, int n)
{
	float t;
	float s;
	char r;
	char prev;

	if (((State*) (a + 0x1c70))->st != 0) {
		return ((State*) (a + 0x1c70))->st;
	}
	if (*(int*) (a + 0x24) == 0) {
		return 0;
	}
	t = *(float*) (b + 0x4c) / *(float*) (a + 0xa0);
	s = (40.0f - n) * 0.4f;
	if (t > *(float*) (b + 0x48) + (*(float*) (a + 0x1c68) + s)) {
		r = 4;
	} else if (t > *(float*) (b + 0x48) + (*(float*) (a + 0x1c64) + s)) {
		r = 2;
	} else {
		r = 1;
	}
	prev = b[0x5f];
	if (prev != 0 && prev != -1 && r != prev) {
		b[0x61] = r;
		if (++*(int*) (b + 0x58) <= 8) {
			return prev;
		}
	}
	*(int*) (b + 0x58) = 0;
	return r;
}
