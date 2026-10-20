int __cdecl fcn_0041e440();
int __cdecl fcn_00437270();
int __cdecl fcn_004372d0();
int __cdecl fcn_00437840();
int __cdecl fcn_004385e0();
int __cdecl fcn_00440f70();
int __cdecl fcn_00441400();
int __cdecl fcn_00441050();
int __cdecl fcn_00441df0(int);
float __cdecl fcn_004424c0();
int __cdecl fcn_00437160();
int __cdecl fcn_00450cb0();
int __cdecl fcn_00450e90();
int __cdecl fcn_00451df0();
int __cdecl fcn_00452bc0();
int __cdecl fcn_00456e50();
int __cdecl fcn_00458bf0();
int __cdecl fcn_00459530();

/* ADDRESS: GOLDTL 0x0043ad20 */
void __cdecl fcn_0043ad20(int a0, int a1)
{
	int v3;
	int v4;
	int v10;
	int v11;
	int* v12;
	int v15;
	int v16;
	int obj;
	char* vt;
	int p6;

	v3 = *(int*) 0x6b86d4;
	if (*(int*) 0x6b86d4 <= -1) {
		v3 = 0;
		*(int*) 0x6b86d4 = 0;
	}
	if (*(char*) 0x6b8018 && !v3 && *(int*) 0x6b8014) {
		v10 = 3;
		*(int*) 0x6b86d4 = 1;
		obj = *(int*) 0x6b5de0;
		vt = (char*) *(int*) 0x6b5de0;
		(*(int (__stdcall**) (int, int, int, int, int, int, int)) (vt + 0x90))(obj, 1, 0x1042570, 3, *(int*) 0x6b805c, 0x3f800000, 0);
		*(int*) 0x1043294 = 0;
		*(int*) 0x10432a0 = 0x501502f9;
		v4 = 0;
		if (*(int*) 0x6b8300) {
			v4 = fcn_00441050(*(int*) 0x6b8300);
		}
		*(int*) 0x1043028 = 0;
		fcn_00450cb0(*(int*) 0x6b8014, (*(int*) 0x1052bd0 & 0x1c) != 0);
		if (*(int*) 0x1052bd0 & 0x1c) {
			fcn_00456e50();
		}
		if (*(int*) 0x6b8300) {
			if (*(char*) 0x6b8060 && *(char*) 0x6b8061) {
				v15 = fcn_004424c0(*(int*) 0x6b8300, *(int*) 0x6b8014 + 0x4c, *(int*) 0x6b8014 + 0x18c);
				if (*(float*) 0x104329c <= *(float*) &v15) {
					fcn_00437840(*(float*) 0x10425fc, *(float*) 0x104329c);
				} else {
					fcn_00437840((*(float*) 0x6628a0 - (*(float*) 0x104329c - *(float*) &v15) / *(float*) 0x104329c) * *(float*) 0x10425fc, *(float*) &v15);
				}
			}
			(*(int (__stdcall**) (int, int, int)) (vt + 200))(obj, 0x24, *(int*) 0x1042ce4);
			(*(int (__stdcall**) (int, int, int)) (vt + 200))(obj, 0x25, *(int*) 0x1042a14);
		}
		fcn_00441050();
		(*(int (__stdcall**) (int, int, int)) (vt + 200))(obj, 0x8b, -1);
		fcn_00437160(*(char*) 0x6b8060, *(int*) 0x6b805c, 1);
		if (*(int*) 0x6b89c0) {
			fcn_00459530(*(int*) 0x6b89c0);
		}
		if (*(int*) 0x6b8300) {
			fcn_00441400(*(int*) 0x6b8300);
		}
		*(int*) 0x6b8054 = 0;
		*(int*) 0x6b8050 = 0;
		(*(int (__stdcall**) (int, int, int)) (vt + 200))(obj, 0x89, 1);
		for (v3 = *(int*) 0x6b86ec; v3; v3 = *(int*) (v3 + 0x1f0)) {
			fcn_004385e0(v3, 0);
		}
		if (*(int*) 0x1043028) {
			fcn_00451df0(*(int*) 0x1043028);
		}
		v12 = (int*) *(int*) 0x6b8068;
		while (v12) {
			(*(int (__stdcall**) (int, int, int)) (vt + 0x94))(obj, 0x100, v12[1]);
			p6 = *(unsigned char*) ((int) v12 + 0x1e);
			if (0 <= v12[6]) {
				fcn_00450e90(v12[4], v12[5], *(int*) (*v12 + 0x1cc) + 0x280, 0, 0);
			} else {
				fcn_00450e90(v12[4], v12[5], *(int*) (*v12 + 0x1cc) + 0x280, 0x1040cc0, 0x1040c80);
			}
			do {
				v3 = v12[3];
				(*(int (__stdcall**) (int, int, int)) (vt + 0xf4))(obj, 0, *(int*) (v3 + 0x50));
				fcn_004372d0((int) (signed char) v12[7], (*(unsigned char*) (v3 + 0x54) & 1) * 2 | (p6 & 1), v12[8], (*(unsigned char*) (v3 + 0x54) >> 3) & 1, (p6 >> 1) & 1);
				if (!(*(unsigned char*) (v3 + 0x54) & 8) && ((unsigned int) v12[6] >> 0x1b & 1) != (unsigned int) (v10 == 2)) {
					v10 = (~v12[6] & 0x8000000U | 0x10000000) >> 0x1b;
					(*(int (__stdcall**) (int, int, int)) (vt + 200))(obj, 0x16, v10);
				}
				(*(int (__stdcall**) (int, int)) ((char*) *(int*) v12[2] + 0xc))(v12[2], v12[6] & 0x7ffffff);
				v12 = (int*) v12[9];
			} while (v12);
		}
		(*(int (__stdcall**) (int, int, int)) (vt + 200))(obj, 0x16, (*(char*) 0x6b7ffe == 0) * 2 + 1);
		(*(int (__stdcall**) (int, int, int)) (vt + 200))(obj, 0x89, 0);
		if (*(int*) 0x1052bd0 & 0x1c) {
			fcn_00458bf0(*(int*) 0x6b8014);
		}
		if (*(int*) 0x6b8300) {
			fcn_00440f70(*(int*) 0x6b8300, v4);
		}
		fcn_0041e440(0x6b8064);
		*(int*) 0x6b8068 = 0;
		fcn_00452bc0();
		fcn_00437270();
		if (*(float*) 0x10432a0 == *(float*) 0x662c94) {
			*(int*) 0x10432a0 = 0;
		}
		*(int*) 0x6b8044 = *(int*) 0x1052bac;
		*(int*) 0x6b802c = *(int*) 0x1042a08;
		*(int*) 0x6b803c = *(int*) 0x1042a00;
		*(int*) 0x6b8030 = *(int*) 0x10432a8;
		*(int*) 0x6b86d4 -= 1;
		*(int*) 0x6b8040 = *(int*) 0x1042a04;
		*(int*) 0x6b8034 = 0;
		*(int*) 0x6b8038 = *(int*) 0x1052bb0;
	}
	return;
}
