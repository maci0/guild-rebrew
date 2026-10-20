int __cdecl fcn_0042e410(int);
int __cdecl fcn_0045b990(int, int, int*, int*, int*);
int __cdecl fcn_004c4450(int);
void __cdecl fcn_004c5420(int, int, int, int, int);
int __cdecl fcn_004c6680(int, int, int, int);
int __cdecl fcn_004c6940(int, int, int*);
int __cdecl fcn_004ce610(int);
int __cdecl fcn_004ce680(int);
int __cdecl fcn_004ceac0(int, int);
int __cdecl fcn_004cec00(int, int, int*, int*);
float __cdecl fcn_004cefb0(int, unsigned int);
int __cdecl fcn_004d1020(int, int, int, int, int);
void __cdecl fcn_004e6cb0(int);
int __cdecl fcn_005c6270(int, int);
int __cdecl fcn_0064d228(void);

/* ADDRESS: GOLDTL 0x004d89c0 */
unsigned int __cdecl fcn_004d89c0(int a0, unsigned int a1, int a2)
{
	unsigned int v10[11];
	unsigned int v7;
	unsigned int v3;
	unsigned int v11;
	unsigned int v15;
	unsigned int v19;
	int v4;
	int* v5;
	int v8;
	int v9;
	int i;
	char v2;
	char v16;
	char v17;

	v9 = a2;
	v4 = a1;
	v7 = *(unsigned int*) (*(int*) 0x67a370 + 0xb0);
	v3 = *(unsigned int*) (a2 + 4);
	for (i = 0; i < 11; i++)
		v10[i] = 0;
	v2 = *(char*) (a1 + 0x1c4);
	v10[0] = *(unsigned int*) (a1 + 4);
	v10[1] = 2;
	v16 = 0;
	if (v2 == 1 || v2 == 2 || v2 == 3)
		v16 = 1;
	v15 = v3;
	v5 = (int*) fcn_004ce610(a1);
	{
		int* p;

		p = v5;
		if ((p[0x16] == 1 || p[0x16] == 2)
		    && ((v8 = fcn_004ce680(v4)) != 0
		        && *(int*) (v8 + 0x20) <= 0))
			return 0xffffffff;
		v8 = p[0];
		if (v8 == 0x154 || v8 == 0x156 || v8 == 0x158 || v8 == 0x16e
		    || v8 == 0x172 || v8 == 0 || v8 == 0x176) {
			float ref;
			v9 = *(int*) (v9 + 0x184);
			ref = fcn_004cefb0(v4, *(unsigned int*) (v9 + 0x34));
			if (*(float*) (p + 3) < ref) {
				if (*(int*) (*(int*) (v4 + 0x184) + 0x128) != 0)
					return 0xffffffff;
				if (v16)
					return 0xffffffff;
				v9 = *(int*) (v9 + 0x34);
				if (fcn_0045b990(v7, v9 + 0x4c, &a1, &a2, &a0)
				    == 0)
					return 0xffffffff;
				v9 = fcn_004cec00(a1, a2, &a1, &a2);
				if (v9 == 0)
					return 0xffffffff;
				v7 = fcn_004c6680(
				    *(int*) (*(int*) (v4 + 0x184) + 0x34), a1,
				    a2, 0);
				return v7;
			}
		}
	}
	if (*(int*) (*(int*) (v4 + 0x184) + 0x128) != 0)
		return 0xffffffff;
	v11 = fcn_0042e410(0xff) & 0xffff;
	a1 = *(unsigned char*) (v4 + 0x83);
	v9 = *(int*) (v4 + 0x16c);
	v8 = fcn_0064d228();
	if ((int) v11 <= 0xff - v8)
		v19 = 0;
	else {
		fcn_004e6cb0(*((unsigned char*) v5 + 6)
		    - *((unsigned char*) v5 + 5));
		v19 = fcn_0064d228();
	}
	v11 = (unsigned int) (0xff - v8 < (int) v11);
	if (v9 != 0 && fcn_005c6270(v9, 0x2b9))
		v19 = fcn_0064d228();
	v17 = 1;
	if (*(int*) (*(int*) 0x772f24 + 4) == *(int*) 0x68b79c
	    && v5[0x16] == 0) {
		int base;
		unsigned char* table;

		v9 = 0;
		v8 = 0;
		base = 0x9b0e20;
		table = (unsigned char*) 0x772eb4;
		if (*(unsigned char*) 0x772eb4 != 0) {
			do {
				if (*(int*) (table + 0x34 + v8 * 4) != -1
				    && a0 != base + v8 * 0x35c) {
					v9 = base + v8 * 0x35c;
					break;
				}
				v8++;
			} while (v8 < *(unsigned char*) 0x772eb4);
		}
		v8 = fcn_004ceac0(v9, v9);
		if (*(int*) (v8 + 8) == -1 || fcn_004c4450(*(int*) (v8 + 8))) {
			*(unsigned int*) (v8 + 8) = 0xffffffff;
			if (*(int*) (v8 + 4) == 0) {
				int w;

				w = fcn_004ce680(a2);
				if (w != 0 && *(int*) (w + 0x20) >= 1)
					*(unsigned int*) (v8 + 8) =
					    fcn_004d1020(v9, a2, v4, 0, 0);
			}
		}
	}
	fcn_004c5420(*(unsigned int*) (v4 + 4), 0x1c8, 4, 0x20000000, 0);
	v7 = fcn_004c6940(v4, 2, (int*) v10);
	return v7;
}
