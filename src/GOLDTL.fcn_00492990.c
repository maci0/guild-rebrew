// FUNCTION: GOLDTL 0x492990
// SIZE: 80

// SIZE 0x8
typedef struct {
	int a;
	int b;
} fcn_00492990_E;

int __cdecl fcn_00492990(char* p, int a2, int a3)
{
	int* slot;
	int i;
	fcn_00492990_E* t;

	if (a2 == *(int*) (p + 0xc)) {
		slot = (int*) (p + 0x28);
	} else if (a2 == *(int*) (p + 0x30)) {
		slot = (int*) (p + 0x4c);
	} else {
		return 0;
	}
	t = (fcn_00492990_E*) 0x6641a0;
	for (i = 0; i < 9; i++) {
		if (t[i].a == *slot && t[i].b == a3) {
			*slot = t[i].b;
			return 1;
		}
	}
	return 0;
}
