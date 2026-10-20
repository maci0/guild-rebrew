int __cdecl fcn_00469c30(int x, int y, int a3);
int __cdecl fcn_00469c40(int x, int y, int win);
int __cdecl fcn_0046f740(int x, int y, int a3, int win);
int __cdecl fcn_00470820(int a0, int a1, char* text);
void __cdecl fcn_00471d80(int k, int flags);
void __cdecl fcn_00471af0(int k, int flag);
int __cdecl fcn_004727a0(int k, int i);
int __cdecl fcn_00472380();
void __cdecl fcn_00468b80(int id, int value);
void __cdecl fcn_00468bb0(int slot, int n, ...);
int __cdecl fcn_004677e0(int x, int y, int a3, int a4, int a5, int a6, int a7, int win);
float __cdecl fcn_005e8860(int a0);

/* ADDRESS: GOLDTL 0x005893d0 */
void __cdecl fcn_005893d0(int w, int a1)
{
	int width;
	int height;
	int half;
	int v;
	int id;
	int id2;

	width = *(int*) 0x1040494;
	height = *(int*) 0x1040490;
	half = (height - (width >> 4) * 9) >> 1;
	v = height - half;
	if (width == 0x320) {
		id = 0x7cb;
		id2 = 0x7ce;
	} else if (width == 0x400) {
		id = 0x7cc;
		id2 = 0x7cf;
	} else {
		id = 0x7cd;
		id2 = 0x7d0;
	}
	*(int*) (w + 0xd4) = fcn_00469c30(0, 0, id);
	*(int*) (w + 0xd8) = fcn_00469c30(0,
	    *(int*) 0x1040490
	    - (int) *(short*) (*(int*) 0x772500 + 0x52 + id2 * 0x54), id2);
	*(int*) (w + 0xa4) = fcn_00470820(0, 0, (char*) 0x6a94e8);
	fcn_00471d80(*(int*) (w + 0xa4), 1);
	fcn_004727a0(*(int*) (w + 0xa4), 0);
	fcn_00469c40(*(int*) (0x1015f44 + *(int*) 0x772514 * 0x3cc), v - 0x19,
	    *(int*) (0x10161bc + *(int*) 0x772514 * 0x3cc));
	fcn_004727a0(*(int*) (w + 0xa4), 2);
	*(int*) (w + 0xb8) = fcn_0046f740(0x59, 0xf, 0x7d5, *(int*) 0x772514);
	*(int*) (*(int*) 0x1015ea0 + 0x5c + *(int*) (w + 0xb8) * 0x2f4) = 1;
	*(int*) (*(int*) 0x1015ea0 + 0x1d0 + *(int*) (w + 0xb8) * 0x2f4) = 3;
	*(int*) (w + 0xbc) = fcn_0046f740(0x9b, 0xf, 0x7d4, *(int*) 0x772514);
	*(int*) (*(int*) 0x1015ea0 + 0x5c + *(int*) (w + 0xbc) * 0x2f4) = 1;
	*(int*) (*(int*) 0x1015ea0 + 0x1d0 + *(int*) (w + 0xbc) * 0x2f4) = 3;
	fcn_004727a0(*(int*) (w + 0xa4), 1);
	*(int*) (w + 0xb0) = fcn_004677e0(0x140, 0x14, 100, 0, 100, 0x7b, 0x82,
	    *(int*) 0x772514);
	fcn_00472380(*(int*) (w + 0xb0), 0, 4, *(int*) 0x9a9214, 1);
	fcn_00468b80(*(int*) (w + 0xb0), *(int*) 0x14b54a4);
	fcn_00468bb0(*(int*) (w + 0xb0), 5, *(int*) 0x14b54ac,
	    *(int*) 0x14b54b0, *(int*) 0x14b54b4, *(int*) 0x14b54b8,
	    *(int*) 0x14b54bc);
	*(int*) (w + 0xb4) = fcn_004677e0(0x140, 0x32, 100, 0, 100, 0x7b, 0x82,
	    *(int*) 0x772514);
	fcn_00472380(*(int*) (w + 0xb4), 0, 100, *(int*) 0x9a9218, 1);
	fcn_00468b80(*(int*) (w + 0xb4), *(int*) 0x14b54a8);
	*(int*) (w + 0xc8) = fcn_0046f740(0x14, 0x17, 0x7d3, *(int*) 0x772514);
	*(int*) (*(int*) 0x1015ea0 + 0x5c + *(int*) (w + 0xc8) * 0x2f4) = 1;
	*(int*) (*(int*) 0x1015ea0 + 0x1d0 + *(int*) (w + 0xc8) * 0x2f4) = 3;
	*(int*) (w + 0xcc) = fcn_0046f740(0x56, 0x17, 0x7d1, *(int*) 0x772514);
	*(int*) (*(int*) 0x1015ea0 + 0x5c + *(int*) (w + 0xcc) * 0x2f4) = 1;
	*(int*) (*(int*) 0x1015ea0 + 0x1d0 + *(int*) (w + 0xcc) * 0x2f4) = 3;
	*(int*) (w + 0xd0) = fcn_0046f740(0x98, 0x17, 0x7d2, *(int*) 0x772514);
	*(int*) (*(int*) 0x1015ea0 + 0x5c + *(int*) (w + 0xd0) * 0x2f4) = 1;
	*(int*) (*(int*) 0x1015ea0 + 0x1d0 + *(int*) (w + 0xd0) * 0x2f4) = 3;
	*(int*) (w + 0xc0) = fcn_00470820(0, 0, (char*) 0x6a94c8);
	fcn_00471d80(*(int*) (w + 0xc0), 1);
	fcn_004727a0(*(int*) (w + 0xc0), 0);
	fcn_00469c40(*(int*) (0x1015f44 + *(int*) 0x772514 * 0x3cc), half - 0x4b,
	    *(int*) (0x10161bc + *(int*) 0x772514 * 0x3cc));
	fcn_004727a0(*(int*) (w + 0xc0), 1);
	*(int*) (w + 0xa8) = fcn_004677e0(0x96, 0xb, 200, 0, 100, 0x75, 0x4c2,
	    *(int*) 0x772514);
	fcn_00472380(*(int*) (w + 0xa8), 0, 100,
	    (int) (fcn_005e8860(1) * *(float*) 0x662cf8));
	fcn_00468b80(*(int*) (w + 0xa8), *(int*) 0x14b5498);
	*(int*) (w + 0xac) = fcn_004677e0(0x96, 0x1f, 200, 0, 100, 0x75, 0x4c2,
	    *(int*) 0x772514);
	fcn_00472380(*(int*) (w + 0xac), 0, 100,
	    (int) (fcn_005e8860(1) * *(float*) 0x662cf8));
	fcn_00468b80(*(int*) (w + 0xac), *(int*) 0x14b549c);
	*(int*) (w + 0xc4) = fcn_004677e0(0x96, 0x33, 200, 0, 100, 0x75, 0x4c2,
	    *(int*) 0x772514);
	fcn_00472380(*(int*) (w + 0xc4), 0, 100,
	    (int) (*(float*) (a1 + *(int*) (w + 0xa0) * 4 + 8)
		* *(float*) 0x662cf8));
	fcn_00468b80(*(int*) (w + 0xc4), *(int*) 0x14b54a0);
	*(int*) (w + 0x74) = fcn_00470820(0, 0, (char*) 0x6a94a8);
	fcn_00471d80(*(int*) (w + 0x74), 3);
	fcn_00471af0(*(int*) (w + 0x74), 0);
	*(int*) (w + 0x70) = *(int*) 0x6b7fac;
}
