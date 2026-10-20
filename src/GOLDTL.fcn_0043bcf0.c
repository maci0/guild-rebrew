typedef struct {
	int (*f0)(void);
	int (*f1)(void);
	int (__stdcall* release)(void*);
} fcn_0043bcf0_vtbl;
/* SIZE 0xc */

void __cdecl fcn_0045bfb0(int);
void __cdecl fcn_0041ddd0(void*);

/* ADDRESS: GOLDTL 0x0043bcf0 */
void __cdecl fcn_0043bcf0(int a)
{
	char* e;
	char* q;
	char* s;
	int* p;
	int i;
	int j;
	int k;

	for (i = 0; i < 8; i++) {
		if (*(int*) (a + 0x30 + i * 4) != 0) {
			fcn_0045bfb0(*(int*) (a + 0x30 + i * 4));
		}
	}
	q = (char*) a + 0x258;
	for (i = 0; i < 8; i++) {
		e = q;
		for (j = 0; j < 8; j++) {
			if (*(char*) (e + 4) != 0) {
				fcn_0041ddd0((void*) *(int*) e);
				*(int*) e = 0;
				fcn_0041ddd0((void*) *(int*) (e - 4));
				*(int*) (e - 4) = 0;
				p = (int*) *(int*) (e - 0x18);
				if (p != 0) {
					*(int*) 0x14ce728 = ((fcn_0043bcf0_vtbl*) *p)->release(p);
					*(int*) (e - 0x18) = 0;
				}
				p = (int*) *(int*) (e - 0x14);
				if (p != 0) {
					*(int*) 0x14ce728 = ((fcn_0043bcf0_vtbl*) *p)->release(p);
					*(int*) (e - 0x14) = 0;
				}
			}
			s = e - 0x1a0;
			for (k = 0; k < 8; k++) {
				p = (int*) *(int*) (s - 4);
				if (p != 0) {
					*(int*) 0x14ce728 = ((fcn_0043bcf0_vtbl*) *p)->release(p);
					*(int*) (s - 4) = 0;
				}
				p = (int*) *(int*) s;
				if (p != 0) {
					*(int*) 0x14ce728 = ((fcn_0043bcf0_vtbl*) *p)->release(p);
					*(int*) s = 0;
				}
				if (*(int*) (s - 0x14) != 0) {
					fcn_0041ddd0((void*) *(int*) (s - 0x14));
					*(int*) (s - 0x14) = 0;
				}
				if (*(int*) (s - 0x10) != 0) {
					fcn_0041ddd0((void*) *(int*) (s - 0x10));
					*(int*) (s - 0x10) = 0;
				}
				if (*(int*) (s - 0xc) != 0) {
					fcn_0041ddd0((void*) *(int*) (s - 0xc));
					*(int*) (s - 0xc) = 0;
				}
				if (*(int*) (s - 8) != 0) {
					fcn_0041ddd0((void*) *(int*) (s - 8));
					*(int*) (s - 8) = 0;
				}
				if (*(int*) (s - 0x18) != 0) {
					fcn_0041ddd0((void*) *(int*) (s - 0x18));
					*(int*) (s - 0x18) = 0;
				}
				s += 0x34;
			}
			e += 0x1f4;
		}
		q = e;
	}
	if (*(int*) (a + 0x10) != 0) {
		fcn_0041ddd0((void*) *(int*) (a + 0x10));
		*(int*) (a + 0x10) = 0;
	}
	if (*(int*) (a + 0x14) != 0) {
		fcn_0041ddd0((void*) *(int*) (a + 0x14));
		*(int*) (a + 0x14) = 0;
	}
	if (*(int*) (a + 0x18) != 0) {
		fcn_0041ddd0((void*) *(int*) (a + 0x18));
		*(int*) (a + 0x18) = 0;
	}
	if (*(int*) (a + 0x1c) != 0) {
		fcn_0041ddd0((void*) *(int*) (a + 0x1c));
		*(int*) (a + 0x1c) = 0;
	}
	if (*(int*) (a + 0x20) != 0) {
		fcn_0041ddd0((void*) *(int*) (a + 0x20));
		*(int*) (a + 0x20) = 0;
	}
	if (*(int*) (a + 0x7da0) != 0) {
		for (i = 0; i < *(unsigned char*) (a + 0x8035); i++) {
			fcn_0045bfb0(*(int*) (*(int*) (a + 0x7da0) + i * 0x158));
		}
		fcn_0041ddd0((void*) *(int*) (a + 0x7da0));
		*(int*) (a + 0x7da0) = 0;
	}
	for (i = 0; i < 3; i++) {
		if (*(int*) (a + 0x24 + i * 4) != 0) {
			fcn_0041ddd0((void*) *(int*) (a + 0x24 + i * 4));
			*(int*) (a + 0x24 + i * 4) = 0;
		}
	}
	fcn_0041ddd0((void*) a);
}
