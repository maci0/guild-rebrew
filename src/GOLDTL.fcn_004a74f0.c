// FUNCTION: GOLDTL 0x4a74f0
// SIZE: 167

// SIZE 0x10
typedef struct {
	int a;
	int b;
	int c;
	int d;
} Slot10;

extern Slot10 g_1007ce0[24];

int __cdecl fcn_004a7340(int* ids, int* out, int flag);
int __cdecl fcn_004a7770(int* ids, int zero, int kind, int* found);

int __cdecl fcn_004a74f0(int* ids, int* out, int kind)
{
	int i;
	int n;
	int v;

	if (kind != 0) {
		return 0;
	}
	if (ids[0] < 0 || ids[1] < 0 || ids[2] < 0 || ids[3] < 0 || ids[4] < 0) {
		return 0;
	}
	if (fcn_004a7340(ids, out, 0) == 0) {
		return 0;
	}
	v = g_1007ce0[out[0]].a;
	if (fcn_004a7770(ids, 0, v, &kind) != 2) {
		return 0;
	}
	n = 3;
	for (i = 0; i < 5; i++) {
		v = ids[i];
		if (g_1007ce0[v].a == kind) {
			out[n] = v;
			n++;
			if (n == 5) {
				return 1;
			}
		}
	}
	return 0;
}
