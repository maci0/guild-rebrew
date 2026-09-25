typedef struct {
	int f0;
	int key;
	char pad8[0x14];
} fcn_004b3db0_entry;
// SIZE 0x1c

extern fcn_004b3db0_entry g_680bd0[48];

int __cdecl fcn_004b3cb0(int);
int __cdecl fcn_004b3b80(int);

// FUNCTION: GOLDTL 0x4b3db0
// SIZE: 85

int __cdecl fcn_004b3db0(int key)
{
	int n;
	int pick;
	int i;
	int seen;

	n = fcn_004b3cb0(key);
	if (n > 0) {
		pick = fcn_004b3b80(n);
		for (i = 0, seen = 0; i < 48; i++) {
			if (g_680bd0[i].key == key)
				seen++;
			if (seen > pick)
				return g_680bd0[i].f0;
		}
	}
	return 0xff;
}
