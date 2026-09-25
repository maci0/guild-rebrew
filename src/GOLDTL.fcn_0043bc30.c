// FUNCTION: GOLDTL 0x43bc30
// SIZE: 189

// SIZE 0x1
typedef struct State {
	unsigned char lo : 2;
	unsigned char st : 3;
	unsigned char hi : 3;
} State;

char __cdecl fcn_0043bc30(char* a, char* b, int unused, int n)
{
	float t;
	float s;
	char r;
	char prev;

	if (((State*) (a + 0x8036))->st != 0) {
		return ((State*) (a + 0x8036))->st;
	}
	if (*(int*) (a + 0x24) == 0) {
		return 0;
	}
	t = *(float*) (b + 0x1dc) / *(float*) (a + 0x60);
	s = (40.0f - n) * 0.4f;
	if (t > *(float*) (a + 0x8028) + *(float*) (b + 0x1d8) + s) {
		r = 4;
	} else if (t > *(float*) (a + 0x8024) + *(float*) (b + 0x1d8) + s) {
		r = 2;
	} else {
		r = 1;
	}
	prev = b[0x1ef];
	if (prev != 0 && prev != -1 && r != prev) {
		b[0x1f0] = r;
		if (++*(int*) (b + 0x1e8) <= 8) {
			return prev;
		}
	}
	*(int*) (b + 0x1e8) = 0;
	return r;
}
