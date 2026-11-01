void __cdecl fcn_00433780(void*);
char* __cdecl fcn_00449ac0(char*, char*);
void* __cdecl vfs_Tfopen(const char*, const char*, void*);
int __cdecl fcn_004011f0(void*, void*);
char* __cdecl m_alloc(int, char*);
int __cdecl fcn_00401500(void*, int, void**);
void __cdecl ReportClientMessage(const char*);
void __cdecl CloseVfsStream(void*);

typedef struct {
	int a;
	int b;
	int c;
} T4321a0;
int __cdecl fcn_004321a0(T4321a0, int, int, int, int);

/* ADDRESS: GOLDTL 0x0044c460 */
char* __cdecl d3_LoadObjectAnim(char* path, char* object, char loop)
{
	char* r;
	void* h;
	char* p;
	int hdr;
	int n;
	int i;

	r = 0;
	if (*(char**) (object + 0x1d0)) {
		fcn_00433780(object);
	}
	p = fcn_00449ac0(path, (char*) 0x67b044);
	if ((p && *(int*) (object + 0x218) == 4) || *(int*) (object + 0x218) == 3) {
		h = vfs_Tfopen(p, (char*) 0x6750e8, *(void**) 0x6b7fdc);
		fcn_004011f0(h, &hdr);
		if (hdr == 0x3a610001) {
			r = m_alloc(0x44, (char*) 0x67b034);
			fcn_004011f0(h, r);
			fcn_004011f0(h, r + 0x2c);
			((unsigned char*) r)[0x2d] &= 0xdf;
			((unsigned char*) r)[0x34] =
				((((unsigned char*) r)[0x34] ^ ((unsigned char) loop << 1)) & 2)
				^ ((unsigned char*) r)[0x34];
			n = fcn_00401500(h, 0x58, (void**) (r + 0x40));
			if (n != *(int*) r) {
				ReportClientMessage((char*) 0x67aff4);
			}
			*(int*) (*(char**) (r + 0x40) + (*(int*) r - 1) * 0x58) =
				*(int*) (*(char**) (r + 0x40) + (*(int*) r - 2) * 0x58);
			*(int*) (r + 0x14) = *(int*) (object + 0x4c);
			*(int*) (r + 0x18) = *(int*) (object + 0x50);
			*(int*) (r + 0x1c) = *(int*) (object + 0x54);
			*(int*) (r + 0x20) = *(int*) (object + 0x84);
			*(int*) (r + 0x24) = *(int*) (object + 0x88);
			*(int*) (r + 0x28) = *(int*) (object + 0x8c);
			for (i = 0; i < *(int*) r; i++) {
				*(int*) (*(char**) (r + 0x40) + i * 0x58) *= 3;
			}
			if (((unsigned char*) r)[0x2d] & 2) {
				n = *(int*) r;
				i = n - 1;
				*(int*) (r + 4) = i;
				*(int*) (r + 0xc) =
					*(int*) (*(char**) (r + 0x40) + i * 0x58) - 1;
				*(int*) (r + 8) =
					fcn_004321a0(*(T4321a0*) (r + 0x2c), i, 0, i, n);
			}
			else {
				*(int*) (r + 8) = 1;
				*(int*) (r + 4) = 0;
				*(int*) (r + 0xc) = 0;
			}
		}
		CloseVfsStream(h);
	}
	*(char**) (object + 0x1d0) = r;
	*(int*) (object + 0x40) = *(int*) 0x6b7fac;
	return r;
}
