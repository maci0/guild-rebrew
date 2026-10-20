/* Project a walk order to screen cells and build the path buffer. */

struct path_421350 {
	int n;
	int max;
	unsigned char* cells;
};

char* __cdecl fcn_00402610(int);
int __cdecl fcn_0045b990(float*, float*, int*, int*, float*);
int __cdecl fcn_0045b7e0(int, int, int, int*, int*);
char __cdecl fcn_00407e30(char*, float*, float*, int, int, int*, int*, int, int);
unsigned short __cdecl fcn_00421350(struct path_421350*, char*, int, int, int, int, int);
void __cdecl fcn_0041ddd0(int);
int __cdecl fcn_0041db70(int, char*);
int __cdecl fcn_00407760(char*, void*, char*, void*);

/* ADDRESS: GOLDTL 0x004090d0 */
unsigned int __cdecl fcn_004090d0(int a0)
{
	int v1;
	int v2;
	char* v4;
	int v6;
	int v8;
	int v10;
	int v11;
	unsigned int v12;
	int v13;
	int v14;
	char v9[4];
	short v3;

	v2 = a0;
	v1 = *(int*) (a0 + 0x14);
	v4 = fcn_00402610(v1);
	v6 = *(int*) (*(int*) (a0 + 0x14) + 0x34);
	if (!fcn_0045b990((float*) v4, (float*) (v6 + 0x4c), &a0, &v10, (float*) v9)) {
		return 0;
	}
	v6 = *(int*) (*(int*) (a0 + 0x110) + 0x34);
	if (!fcn_0045b990((float*) v4, (float*) (v6 + 0x4c), (int*) &v12, &v11,
	                 (float*) v9)) {
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
	fcn_00407e30(v4, (float*) (*(int*) (v1 + 0x34) + 0x4c),
	             (float*) (v2 + 0x144), v12, v11, &v14, &v13, 4, 0);
	v12 = v14;
	v11 = v13;
	*(int*) 0x14d0c28 = 0x14cfc20;
	*(int*) 0x14d0c24 = 0x200;
	v3 = fcn_00421350((struct path_421350*) 0x14d0c20, v4, a0, v10, v14, v13,
	                  *(char*) (v1 + 0x240));
	if (v3 == -1) {
		return 0;
	}
	if (*(int*) (v2 + 0xf4)) {
		fcn_0041ddd0(*(int*) (v2 + 0xf4));
		*(int*) (v2 + 0xf4) = 0;
	}
	v6 = fcn_0041db70(*(int*) 0x14d0c20 * 2, (char*) 0x675ad8);
	*(int*) (v2 + 0xf4) = v6;
	if (v6 == 0) {
		__asm { int 3 }
	}
	*(int*) (v2 + 0xf0) =
	    fcn_00407760((char*) v1, (void*) 0x14d0c20, (char*) *(int*) (v2 + 0xf4),
	                 v4);
	v1 = *(int*) (v2 + 0x110);
	*(int*) (v2 + 0xf8) = 0;
	*(int*) (v2 + 0xfc) = 0xffffffff;
	*(int*) (v2 + 0x134) = *(int*) (*(int*) (v1 + 0x34) + 0x4c);
	*(int*) (v2 + 0x138) = *(int*) (*(int*) (v1 + 0x34) + 0x50);
	*(int*) (v2 + 0x13c) = *(int*) (*(int*) (v1 + 0x34) + 0x54);
	return 1;
}
