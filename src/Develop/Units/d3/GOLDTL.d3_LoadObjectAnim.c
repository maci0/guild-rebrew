void __cdecl fcn_00433780(void*);
char* __cdecl fcn_00449ac0(char*, char*);
void* __cdecl fcn_0042ff50(const char*, const char*, void*);
int __cdecl fcn_004011f0(void*, void*);
char* __cdecl m_alloc(int, char*);
int __cdecl fcn_00401500(void*, int, void**);
void __cdecl fcn_0041d9e0(const char*);
void __cdecl fcn_00430580(void*);

typedef struct {
	int a;
	int b;
	int c;
} T4321a0;
int __cdecl fcn_004321a0(T4321a0, int, int, int, int);

/* ADDRESS: GOLDTL 0x0044c460 */
void* __cdecl d3_LoadObjectAnim(int a0, char* obj, char* a1, char a3)
{
	char* r;
	char* h;
	char* p;
	char* items;
	int hdr;
	int n;
	int i;
	T4321a0 t;

	r = 0;
	if (*(char**) (obj + 0x1d0)) {
		fcn_00433780(obj);
	}
	p = fcn_00449ac0(a1, (char*) 0x67b044);
	if ((p && *(int*) (obj + 0x218) == 4) || *(int*) (obj + 0x218) == 3) {
		h = fcn_0042ff50(p, (char*) 0x6750e8, *(void**) 0x6b7fdc);
		hdr = a0;
		fcn_004011f0(h, &hdr);
		if (hdr == 0x3a610001) {
			r = m_alloc(0x44, (char*) 0x67b034);
			fcn_004011f0(h, r);
			fcn_004011f0(h, r + 0x2c);
			((unsigned char*) r)[0x2d] &= 0xdf;
			((unsigned char*) r)[0x34] =
				((((unsigned char) a3 + (unsigned char) a3) ^ ((unsigned char*) r)[0x34]) & 2)
				^ ((unsigned char*) r)[0x34];
			n = fcn_00401500(h, 0x58, (void**) (r + 0x40));
			if (n != *(int*) r) {
				fcn_0041d9e0((char*) 0x67aff4);
			}
			items = *(char**) (r + 0x40);
			*(int*) (items + (*(int*) r - 1) * 0x58) =
				*(int*) (items + (*(int*) r - 2) * 0x58);
			*(int*) (r + 0x14) = *(int*) (obj + 0x4c);
			*(int*) (r + 0x18) = *(int*) (obj + 0x50);
			*(int*) (r + 0x1c) = *(int*) (obj + 0x54);
			*(int*) (r + 0x20) = *(int*) (obj + 0x84);
			*(int*) (r + 0x24) = *(int*) (obj + 0x88);
			*(int*) (r + 0x28) = *(int*) (obj + 0x8c);
			for (i = 0; i < *(int*) r; i++) {
				*(int*) (items + i * 0x58) *= 3;
			}
			if (((unsigned char*) r)[0x2d] & 2) {
				n = *(int*) r;
				i = n - 1;
				t.a = *(int*) (r + 0x2c);
				t.b = *(int*) (r + 0x30);
				t.c = *(int*) (r + 0x34);
				*(int*) (r + 4) = i;
				*(int*) (r + 0xc) =
					*(int*) (items + i * 0x58) - 1;
				*(int*) (r + 8) = fcn_004321a0(t, i, 0, i, n);
			}
			else {
				*(int*) (r + 8) = 1;
				*(int*) (r + 4) = 0;
				*(int*) (r + 0xc) = 0;
			}
		}
		fcn_00430580(h);
	}
	*(char**) (obj + 0x1d0) = r;
	*(int*) (obj + 0x40) = *(int*) 0x6b7fac;
	return r;
}
