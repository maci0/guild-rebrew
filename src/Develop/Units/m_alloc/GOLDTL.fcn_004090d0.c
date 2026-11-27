/* Project a walk order to screen cells and build the path buffer. */

struct path_421350 {
	int n;
	int max;
	unsigned char* cells;
};

char* __cdecl d3sm_GetObjectSuperMap(int);
char __cdecl fcn_0045b990(float*, float*, int*, int*, float*);
int __cdecl fcn_0045b7e0(int, int, int, int*, int*);
char __cdecl ch_FindWalkableCell(char*, float*, float*, int, int, int*, int*, int, int);
unsigned short __cdecl FindPath(struct path_421350*, char*, int, int, int, int, int);
void __cdecl m_FreeTracked(int);
int __cdecl m_alloc(int, char*);
int __cdecl ch_DownsamplePath(char*, void*, char*, void*);

/* ADDRESS: GOLDTL 0x004090d0 */
unsigned int __cdecl fcn_004090d0(int self)
{
	int a0;
	int v1;
	char* v4;
	int v6;
	int v8;
	int v10;
	int v11;
	unsigned int v12;
	int v13;
	int v14;
	char v9[4];
	short pathResult;

	v1 = *(int*) (self + 0x14);
	v4 = d3sm_GetObjectSuperMap(v1);
	if (!fcn_0045b990((float*) v4,
	                  (float*) (*(int*) (*(int*) (self + 0x14) + 0x34) + 0x4c),
	                  &a0, &v10, (float*) v9)) {
		return 0;
	}
	if (!fcn_0045b990((float*) v4,
	                  (float*) (*(int*) (*(int*) (self + 0x110) + 0x34) + 0x4c),
	                  (int*) &v12, &v11, (float*) v9)) {
		return 0;
	}
	if (a0 < 1) {
		a0 = 1;
	} else {
		v8 = *(int*) (v4 + 0x20) - 2;
		if (a0 > v8) {
			a0 = v8;
		}
	}
	if (v10 < 1) {
		v10 = 1;
	} else {
		v8 = *(int*) (v4 + 0x20) - 2;
		if (v10 > v8) {
			v10 = v8;
		}
	}
	fcn_0045b7e0((int) v4, a0, v10, &v14, &v13);
	a0 = v14;
	v10 = v13;
	ch_FindWalkableCell(v4, (float*) (*(int*) (v1 + 0x34) + 0x4c),
	             (float*) (self + 0x144), v12, v11, &v14, &v13, 4, 0);
	v12 = v14;
	v11 = v13;
	*(int*) 0x14d0c28 = 0x14cfc20;
	*(int*) 0x14d0c24 = 0x200;
	pathResult = FindPath((struct path_421350*) 0x14d0c20, v4, a0, v10, v14, v13,
	                  *(unsigned char*) (v1 + 0x240));
	if (pathResult == -1) {
		return 0;
	}
	if (*(int*) (self + 0xf4)) {
		m_FreeTracked(*(int*) (self + 0xf4));
		*(int*) (self + 0xf4) = 0;
	}
	v6 = m_alloc(*(int*) 0x14d0c20 * 2, (char*) 0x675ad8);
	*(int*) (self + 0xf4) = v6;
	if (v6 == 0) {
		__asm { int 3 }
	}
	*(int*) (self + 0xf0) =
	    ch_DownsamplePath((char*) v1, (void*) 0x14d0c20, (char*) *(int*) (self + 0xf4),
	                 v4);
	v1 = *(int*) (self + 0x110);
	*(int*) (self + 0xf8) = 0;
	*(int*) (self + 0xfc) = 0xffffffff;
	*(int*) (self + 0x134) = *(int*) (*(int*) (v1 + 0x34) + 0x4c);
	*(int*) (self + 0x138) = *(int*) (*(int*) (v1 + 0x34) + 0x50);
	*(int*) (self + 0x13c) = *(int*) (*(int*) (v1 + 0x34) + 0x54);
	return 1;
}
