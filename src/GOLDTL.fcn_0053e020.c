int __cdecl fcn_004432d0();
int __cdecl fcn_004693b0();
int __cdecl fcn_00469470();
int __cdecl fcn_00469510();
int __cdecl fcn_004695a0();
int __cdecl fcn_00469630();
int __cdecl fcn_00470820();
int __cdecl fcn_00471af0();
int __cdecl fcn_00471b60();
int __cdecl fcn_00471e30();
int __cdecl fcn_00472250();
int __cdecl fcn_004727a0();
int __cdecl fcn_004730c0();
int __cdecl fcn_00473150();
int __cdecl fcn_004e4470();
int __cdecl fcn_004e44f0();
int __cdecl fcn_004fdec0();
int __cdecl fcn_00506d50();
int __cdecl fcn_00519190();
int __cdecl fcn_005268c0();
int __cdecl fcn_005373e0();
int __cdecl fcn_0053c560();
int __cdecl fcn_0053cd40();
int __cdecl fcn_0053d490();
int __cdecl fcn_0053e8a0();


/* ADDRESS: GOLDTL 0x0053e020 */

int __cdecl fcn_0053e020(void)
{
	int v12;
	int v13;
	int v1;
	int v2;
	int v3;
	int v4;
	int v5;
	int v6;
	int v7;
	int v8;
	int r;
	unsigned int* v10;
	char v11[8];

	v12 = 0;
	v1 = 0;
	v13 = -1;
	v2 = fcn_00470820(0, 0, 0x68116c);
	fcn_00471b60(v2);
	fcn_004727a0(v2, 0);
	v3 = fcn_00519190(0x1ac5, 0x1ac7, 0x1ac8, 0x1ac9, 0x1aca);
	v4 = fcn_00472250(v2, 0, v3);
	v5 = fcn_00472250(v2, 0, v3 + 1);
	v6 = fcn_00472250(v2, 0, v3 + 2);
	v3 = fcn_00472250(v2, 0, v3 + 3);
	if (*(unsigned char*) 0x6a375c > 1) {
		v13 = fcn_00472250(v2, 0, fcn_00519190(0x681164, 2, 0x1acb));
	}
	if (*(int*) 0x776700 > -1) {
		*(int*) 0x776700 = -1;
	}
	v7 = fcn_004693b0(4, v4, v5, v6, v3);
	if (*(int*) 0x776700 != -1) {
		v8 = *(int*) 0x776700 + 1;
	} else {
		v8 = 0;
	}
	fcn_004695a0(v7, v8);
	fcn_00469470(v7, fcn_00472250(v2, 0, fcn_00519190(0x7e)));
	for (;;) {
		if (fcn_005373e0(0x53e020, 0xc6) == 0) {
			break;
		}
		fcn_00469630(v7);
		r = *(int*) 0x100f1dc;
		if (*(int*) 0x14ce8e0 || *(unsigned char*) 0x14cf950 == 1 || r == 1) {
			*(int*) 0x774654 = 1;
		}
		if (r == 2 || v1) {
			v1 = 0;
			if (*(int*) 0x67d370 == v4) {
				*(unsigned char*) 0x6a3440 = 0xff;
			} else if (*(int*) 0x67d370 == v5) {
				*(unsigned char*) 0x6a3440 = 1;
			} else if (*(int*) 0x67d370 == v6) {
				*(unsigned char*) 0x6a3440 = 2;
			} else if (*(int*) 0x67d370 == v3) {
				*(unsigned char*) 0x6a3440 = 3;
			} else if (*(int*) 0x67d370 == v13) {
				*(unsigned char*) 0x6a3440 = 5;
			}
			r = *(signed char*) 0x6a3440;
			*(int*) 0x776700 = r;
			if (r != -1) {
				v8 = r + 1;
			} else {
				v8 = 0;
			}
			fcn_004695a0(v7, v8);
			fcn_00471af0(v2, 0);
			*(int*) 0x7e46ac = 0x12d6;
			*(int*) 0x68bfb8 = 0x12d6;
			fcn_004e44f0(fcn_004e4470(0x6a4040));
			v12 = fcn_0053d490(0xc6, 0);
			if (v12 != 0) {
				r = fcn_0053e8a0(0);
				if (r == 1) {
					*(int*) 0x7725c8 = r;
					*(int*) 0x6a37f8 = fcn_005268c0(*(int*) 0x14abf04, 0);
					if (fcn_0053c560(0) == 0) {
						fcn_004432d0(0, 0);
						v12 = 0;
						v1 = 1;
					}
				} else if (r == 0) {
					if (fcn_0053cd40(0xc6) != 0) {
						v10 = (unsigned int*) fcn_00506d50(v11, *(unsigned char*) 0x7e23e3);
						*(int*) 0x7e2430 = (int) *v10;
						*(unsigned char*) 0x7e2434 = (unsigned char) (*(unsigned short*) &v10[1]);
						*(int*) 0x7e2468 = fcn_004fdec0(0x6a3db4) + 0x639;
					} else {
						fcn_004432d0(0, 0);
						v12 = 0;
						v1 = 1;
					}
				} else if (r == -1) {
					v12 = 0;
					v1 = 1;
				}
			} else {
				*(int*) 0x7e46ac = 0x12d6;
				*(int*) 0x68bfb8 = 0x12d6;
				fcn_004e44f0(fcn_004e4470(0x6a4024));
			}
			fcn_00471af0(v2, 1);
			if (v12 != 0) {
				if (*(unsigned char*) 0x6a375c >= 1) {
					*(int*) 0x7747b0 |= 8;
				}
				*(int*) 0x774654 = 1;
				v12 = 1;
			}
		} else {
			v1 = 0;
			if (r == 1) {
				*(int*) 0x774654 = r;
			}
		}
	}
	fcn_00469510(v7);
	fcn_00471e30(v2);
	if (v12 != 0) {
		v3 = fcn_004730c0(0, 0, *(int*) 0x1040494, *(int*) 0x1040490, 0x67d67c, 100, 1);
		*(int*) 0x7e46ac = 0x12d6;
		*(int*) 0x68bfb8 = 0x12d6;
		fcn_004e44f0(fcn_004e4470(0x6a4060));
		if (v3 != 0) {
			fcn_00473150(v3);
			return v12;
		}
	} else {
		*(int*) 0x7e46ac = 0x12d6;
		*(int*) 0x68bfb8 = 0x12d6;
		fcn_004e44f0(fcn_004e4470(0x6a4024));
	}
	return v12;
}
