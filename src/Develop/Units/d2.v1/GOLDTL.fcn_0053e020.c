extern int g_7e2468;
extern int g_774654;
extern int g_7725c8;
extern int g_68bfb8;
extern int g_67d370;
extern int g_14ce8e0;
extern int g_1040494;
extern int g_1040490;
int __cdecl fcn_004432d0();
int __cdecl d2_CreateRadioGroup();
int __cdecl fcn_00469470();
int __cdecl fcn_00469510();
int __cdecl d2_SelectRadioGroup();
int __cdecl d2_UpdateRadioGroup();
int __cdecl fcn_00470820();
int __cdecl fcn_00471af0();
int __cdecl fcn_00471b60();
int __cdecl fcn_00471e30();
int __cdecl fcn_00472250();
int __cdecl d2_SetForm();
int __cdecl fcn_004730c0();
int __cdecl fcn_00473150();
int __cdecl fcn_004e4470();
int __cdecl fcn_004e44f0();
int __cdecl fcn_004fdec0();
int __cdecl fcn_00506d50();
int __cdecl io_AppendText();
int __cdecl fcn_005268c0();
int __cdecl fcn_005373e0();
int __cdecl fcn_0053c560();
int __cdecl fcn_0053cd40();
int __cdecl fcn_0053d490();
int __cdecl fcn_0053e8a0();


#include "Develop/DieGildeAddOn/game/game_data.h"
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
	d2_SetForm(v2, 0);
	v3 = io_AppendText(0x1ac5, 0x1ac7, 0x1ac8, 0x1ac9, 0x1aca);
	v4 = fcn_00472250(v2, 0, v3);
	v5 = fcn_00472250(v2, 0, v3 + 1);
	v6 = fcn_00472250(v2, 0, v3 + 2);
	v3 = fcn_00472250(v2, 0, v3 + 3);
	if (*(unsigned char*) &g_6a375c > 1) {
		v13 = fcn_00472250(v2, 0, io_AppendText(0x681164, 2, 0x1acb));
	}
	if (*(int*) 0x776700 <= -1) {
		*(int*) 0x776700 = -1;
	}
	v7 = d2_CreateRadioGroup(4, v4, v5, v6, v3);
	if (*(int*) 0x776700 != -1) {
		v8 = *(int*) 0x776700 + 1;
	} else {
		v8 = 0;
	}
	d2_SelectRadioGroup(v7, v8);
	fcn_00469470(v7, fcn_00472250(v2, 0, io_AppendText(0x7e)));
	for (;;) {
		if (fcn_005373e0((int)fcn_0053e020, 0xc6) == 0) {
			break;
		}
		d2_UpdateRadioGroup(v7);
		r = *(int*) &g_100f1dc;
		if (g_14ce8e0 || *(unsigned char*) &g_14cf950 == 1 || r == 1) {
			g_774654 = 1;
		}
		if (r == 2 || v1) {
			v1 = 0;
			if (g_67d370 == v4) {
				*(unsigned char*) &g_6a3440 = 0xff;
			} else if (g_67d370 == v5) {
				*(unsigned char*) &g_6a3440 = 1;
			} else if (g_67d370 == v6) {
				*(unsigned char*) &g_6a3440 = 2;
			} else if (g_67d370 == v3) {
				*(unsigned char*) &g_6a3440 = 3;
			} else if (g_67d370 == v13) {
				*(unsigned char*) &g_6a3440 = 5;
			}
			r = *(signed char*) &g_6a3440;
			*(int*) 0x776700 = r;
			if (r != -1) {
				v8 = r + 1;
			} else {
				v8 = 0;
			}
			d2_SelectRadioGroup(v7, v8);
			fcn_00471af0(v2, 0);
			*(int*) &g_7e46ac = 0x12d6;
			g_68bfb8 = 0x12d6;
			fcn_004e44f0(fcn_004e4470(0x6a4040));
			v12 = fcn_0053d490(0xc6, 0);
			if (v12 != 0) {
				r = fcn_0053e8a0(0);
				if (r == 1) {
					g_7725c8 = r;
					*(int*) 0x6a37f8 = fcn_005268c0(*(int*) 0x14abf04, 0);
					if (fcn_0053c560(0) == 0) {
						fcn_004432d0(0, 0);
						v1 = 1;
					}
				} else if (r == 0) {
					if (fcn_0053cd40(0xc6) != 0) {
						v10 = (unsigned int*) fcn_00506d50(v11, *(unsigned char*) 0x7e23e3);
						*(int*) 0x7e2430 = (int) *v10;
						*(unsigned char*) 0x7e2434 = (unsigned char) (*(unsigned short*) &v10[1]);
						g_7e2468 = fcn_004fdec0(0x6a3db4) + 0x639;
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
				*(int*) &g_7e46ac = 0x12d6;
				g_68bfb8 = 0x12d6;
				fcn_004e44f0(fcn_004e4470(0x6a4024));
			}
			fcn_00471af0(v2, 1);
			if (v12 != 0) {
				if (*(unsigned char*) &g_6a375c >= 1) {
					*(int*) &g_7747b0 |= 8;
				}
				g_774654 = 1;
				v12 = 1;
			}
		} else {
			v1 = 0;
			if (r == 1) {
				g_774654 = r;
			}
		}
	}
	fcn_00469510(v7);
	fcn_00471e30(v2);
	if (v12 != 0) {
		v3 = fcn_004730c0(0, 0, g_1040494, g_1040490, 0x67d67c, 100, 1);
		*(int*) &g_7e46ac = 0x12d6;
		g_68bfb8 = 0x12d6;
		fcn_004e44f0(fcn_004e4470(0x6a4060));
		if (v3 != 0) {
			fcn_00473150(v3);
			return v12;
		}
	} else {
		*(int*) &g_7e46ac = 0x12d6;
		g_68bfb8 = 0x12d6;
		fcn_004e44f0(fcn_004e4470(0x6a4024));
	}
	return v12;
}
