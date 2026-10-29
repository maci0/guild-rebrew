float __cdecl gm_RandomFloat01(void);

typedef struct
{
	char pad0[0xc];
	void* link0;
	unsigned char f10;
	char pad11[3];
	int f14;
	unsigned char arr0[0x10];
	int f28;
	char pad2c[4];
	void* link1;
	unsigned char f34;
	char pad35[3];
	int f38;
	unsigned char arr1[0x10];
	int f4c;
} Cmd92e50;
// SIZE 0x50

/* ADDRESS: GOLDTL 0x00492e50 */
int __cdecl fcn_00492e50(Cmd92e50* a, char* b)
{
	unsigned char* p;
	int count;
	int sum;
	int sw;
	int v1;
	int v2;
	int extra;
	int i;
	int n;
	float v;
	float t;

	if (*(unsigned char*) (b + 2) != '\n') {
		return 0;
	}
	if (a->link0 == (void*) b) {
		sw = a->f28;
		count = a->f14;
		v1 = a->f10;
		p = a->arr0;
		v2 = a->f34;
		extra = 0;
	} else if (a->link1 == (void*) b) {
		sw = a->f4c;
		count = a->f38;
		v1 = a->f34;
		p = a->arr1;
		v2 = a->f10;
		extra = 1;
	} else {
		return 0;
	}
	count &= 0xff;
	sum = 0;
	for (i = 0; i < v1; i++) {
		sum += p[i];
	}
	switch (sw) {
	case 0:
		return 1;
	case 1:
	case 2:
		n = 0x11 - sum;
		if (n >= 6) {
			return 2;
		}
		if (n != 0) {
			t = (float) n * 0.16666667f * ((1.0f - (float) count * 0.2f) * 0.25f + 1.0f);
			if (gm_RandomFloat01() < t) {
				return 2;
			}
		}
		return 3;
	case 3:
		v = (float) (sum + extra) * 0.05882353f;
		if (v >= 1.0f) {
			return 3;
		}
		n = 6 - count;
		if (!(v - (float) v2 * 3.5f < (float) n)) {
			return 4;
		}
		return 3;
	}
	return 0;
}
