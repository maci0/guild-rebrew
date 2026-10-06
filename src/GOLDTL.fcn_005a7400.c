// FUNCTION: GOLD 0x59e2c0
// FUNCTION: GOLDTL 0x005a7400

// SIZE 0x8
typedef struct {
	int key;
	unsigned char lo;
	unsigned char hi;
	short pad;
} Range;

extern Range g_6aa0b0[];
extern unsigned char* g_868050;
extern unsigned short g_7f4c04;

int __cdecl fcn_005a7400(unsigned char* p, int* lo, int* hi)
{
	unsigned char* t;
	int i;

	t = g_868050 + *p * 589;
	for (i = 0; g_6aa0b0[i].key != 0; i++) {
		if (*t == g_6aa0b0[i].key) {
			if (lo != 0) {
				*lo = g_6aa0b0[i].lo;
			}
			if (hi != 0) {
				*hi = g_6aa0b0[i].hi;
			}
			if (g_7f4c04 >= (unsigned short) g_6aa0b0[i].lo &&
			    g_7f4c04 < (unsigned short) g_6aa0b0[i].hi) {
				return 1;
			}
			return 0;
		}
	}
	return 1;
}
