extern unsigned char g_773d75;

unsigned char* __cdecl gm_StartFilteredEntitySearch(int, int, int);
unsigned char* __cdecl gm_AddObjekt(void);
int __cdecl fcn_00504bd0(int);
unsigned short __cdecl fcn_0042e410(unsigned short);
char* __cdecl fcn_00502cd0(int, int, int, ...);
char* __cdecl gm_NextEntityQueryMatch(void);
void __cdecl fcn_004c51f0(int, int, int, int, unsigned char, int);

// FUNCTION: GOLDTL 0x4bac00
// SIZE: 294

int __cdecl fcn_004bac00(unsigned short* a1, int* a2, float a3)
{
	char* arr[12];
	unsigned char* it;
	char* c;
	char* q;
	char* s;
	int n;
	int m;
	int k;
	int i;
	int v;

	n = 0;
	for (it = gm_StartFilteredEntitySearch(1, 3, *a1); it != 0 && n < 8; it = gm_AddObjekt()) {
		k = fcn_00504bd0(it[0]);
		if (k == 1 || k == 2)
			arr[n++] = (char*) it;
	}
	if (n == 0)
		goto fail;
	m = 0;
	c = arr[fcn_0042e410(n)];
	*a2 = *(int*) (c + 1);
	q = fcn_00502cd0(*(int*) (c + 0x5d), 2, 6, 0, 0x2a);
	if (q == 0)
		goto fail;
	for (s = fcn_00502cd0(*(int*) (q + 0x14), 1, 5); s != 0 && m < 12; s = gm_NextEntityQueryMatch())
		arr[m++] = s;
	if (m != 0) {
		for (i = 0; i < m; i++) {
			s = arr[i];
			k = *(int*) (s + 0xe);
			if (k > 1) {
				v = (int) (k * a3);
				if (v < 1)
					v = 1;
				fcn_004c51f0(-1, *(int*) (q + 2), *(unsigned short*) s, v, g_773d75, 0);
			}
		}
		return 1;
	}
fail:
	return 0;
}
