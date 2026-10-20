typedef struct Vtbl61d1be
{
	char pad[0x10];
	int (__cdecl* fn10)(void*);
} Vtbl61d1be;

typedef struct Obj61d1be
{
	Vtbl61d1be* vtbl;
} Obj61d1be;

#pragma optimize("y", off)

/* ADDRESS: GOLDTL 0x0061d1be */
int __cdecl fcn_0061d1be(Obj61d1be* obj, int* arr)
{
	unsigned n;
	unsigned i;
	int j;
	int k;
	int* p;
	int* q;

	n = obj->vtbl->fn10(obj);
	for (i = 0; i < n; i++) {
		p = arr + i * 3;
		k = p[1];
		if (p[0] == p[1]) {
			k = p[0];
		} else if (p[0] == p[2] || p[1] == p[2]) {
			if (p[0] == p[1] || p[0] == p[2]) {
				k = p[0];
			}
		}
		if (k != -1) {
			q = arr + k * 3;
			j = 3;
			do {
				if (*p == k) {
					*p = -1;
				}
				if (*q == (int) i) {
					*q = -1;
				}
				p++;
				q++;
			} while (--j);
		}
	}
	return 0;
}
