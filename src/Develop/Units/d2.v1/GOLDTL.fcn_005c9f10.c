int __cdecl d2_AddWindowValueGauge();
int __cdecl d2_AddElementToWindow();
#include "d2_gui.h"
extern char g_679060[];
int __cdecl d2_SetElementEnabled();
float __cdecl gm_CalcEntityFavor(unsigned int, unsigned int, unsigned int);
int __cdecl io_FormatTextBuffer();
int __cdecl fcn_005c9090();
int __cdecl fcn_005cf720();

extern char * g_1015ea0; extern char * g_772500; extern int d2_CurrentWindowId; extern unsigned short g_774970;
/* ADDRESS: GOLDTL 0x005c9f10 */
int __cdecl fcn_005c9f10(int a0, int a1, int a2, int a3, int a4, unsigned short* a5)
{
	char v1;
	int v2;
	unsigned short* v3;
	int v4;
	int v5;
	int v6;
	int v10;
	int v11;
	int v12;
	int* v15;
	int v17;
	char caption[256];

	if (a1 != 1 && a1 != 2 && a1 != 3) {
		if (a1 != 4 && a1 != 5 && a1 != 6) {
			if (a1 != 8) {
				v4 = 0;
				goto label_5ca044;
			}
			*(int*) (a4 + 0x10) = 0x12f;
			*(int*) (a4 + 0xb8) = 0x12f;
			*(int*) (a4 + 0x48) = 0x65;
			*(int*) (a4 + 0x14) = 0;
			*(int*) (a4 + 0x4c) = 0;
			*(int*) (a4 + 0x80) = 0xca;
			*(int*) (a4 + 0xf0) = 0x65;
			*(int*) (a4 + 0x84) = 0x80;
			*(int*) (a4 + 0xf4) = 0x100;
		} else {
			*(int*) (a4 + 0x10) = 0xca;
			*(int*) (a4 + 0xf0) = 0xca;
			*(int*) (a4 + 0x48) = 0x65;
			*(int*) (a4 + 0x4c) = 0x80;
			*(int*) (a4 + 0x84) = 0x80;
			*(int*) (a4 + 0x80) = 0x12f;
			*(int*) (a4 + 0xb8) = 0;
			*(int*) (a4 + 0x128) = 0x194;
			*(int*) (a4 + 0x14) = 0;
			*(int*) (a4 + 0xf4) = 0x100;
			*(int*) (a4 + 300) = 0x100;
		}
	} else {
		*(int*) (a4 + 0x80) = 0x65;
		*(int*) (a4 + 0x10) = 0xca;
		*(int*) (a4 + 0x48) = 0xca;
		*(int*) (a4 + 0xb8) = 0x12f;
		*(int*) (a4 + 0x14) = 0;
		*(int*) (a4 + 0x4c) = 0x80;
		*(int*) (a4 + 0x84) = 0x100;
	}
	*(int*) (a4 + 0xbc) = 0x100;
	v4 = 1;
label_5ca044:
	v17 = 0;
	if (a3 < 1) {
		return 0;
	}
	v15 = (int*) (a4 + 0x18);
	do {
		if (!v4) {
			return 0;
		}
		v6 = v15[-2] + 0x65;
		v10 = v15[-1] + 0x23;
		v11 = v6 - (int) *(short*) ((int) g_772500 + 0x1ebd8) / 2;
		v5 = d2_AddElementToWindow(v11, v10, 0x5da, d2_CurrentWindowId);
		v15[-5] = v5;
		v2 = v15[-6];
		v15[-4] = -1;
		if (v2) {
			v1 = *(char*) (v2 + 2);
			if (v1 == 6 || v1 == 7 || v1 == 5) {
				d2_AddElementToWindow(v11 - 0x20, v10, *(unsigned int*) (v2 + 0x54), d2_CurrentWindowId);
			}
			v5 = d2_AddElementToWindow(((v6 - (int) *(short*) ((int) g_772500 + 0x50 + *(int*) (v15[-6] + 0x18c) * 0x54) / 2) - 3), v10 + 1, *(int*) (v15[-6] + 0x18c), d2_CurrentWindowId);
			*v15 = v5;
			d2_AddElementToWindow(v11 + 3, v10 + 3, v15[1], d2_CurrentWindowId);
			if (v15[2]) {
				d2_AddElementToWindow(v11 + 3, (int) *(short*) ((int) g_772500 + 0x1ebda) + -0x13 + v10, v15[2], d2_CurrentWindowId);
			}
			if (v15[3]) {
				d2_AddElementToWindow((int) *(short*) ((int) g_772500 + 0x1ebd8) + -0x10 + v11, v10 + 3, v15[3], d2_CurrentWindowId);
			}
			d2_AddElementToWindow((int) *(short*) ((int) g_772500 + 0x1ebd8) + -0x10 + v11, (int) *(short*) ((int) g_772500 + 0x1ebda) + -0x13 + v10, v15[4], d2_CurrentWindowId);
			if (a1 == 8) {
				v12 = *(int*) &((unsigned short*) v15[-6])[0xe6];
				if (v12 & 0x1000) {
					v12 = 0x26;
				} else if (v12 & 0x2000) {
					v12 = 0x27;
				} else if (v12 & 0x800) {
					v12 = 0x25;
				} else if (v12 & 0x400) {
					v12 = 0x24;
				} else {
					v12 = -(unsigned int) ((v12 & 0x200) != 0) & 0x23;
				}
				io_FormatTextBuffer(caption, 0x6ac96c, *(unsigned short*) v15[-6]);
				fcn_005c9090(caption, v6, v15[-1], 0xca, 0x56);
				io_FormatTextBuffer(caption, "%s", (-(unsigned int) (*(char*) (v15[-6] + 9) != 0) & 0x28) + 0x253 + v12);
				fcn_005c9090(caption, v6, v15[-1] + 0xf, 0xca, 0x56);
			} else {
				v3 = (unsigned short*) v15[-6];
				io_FormatTextBuffer(caption, 0x6ac964, (-(unsigned int) (*(char*) ((int) v3 + 9) != 0) & 10) + 0x114 + (unsigned int) *(unsigned char*) ((int) v3 + 0xd), *v3);
				fcn_005c9090(caption, v6, v15[-1], 0xca, 0x56);
				io_FormatTextBuffer(caption, 0x6ac95c, *(unsigned short*) v15[-6]);
				fcn_005c9090(caption, v6, v15[-1] + 0xf, 0xca, 0x56);
			}
			v3 = a5;
			if ((unsigned short*) v15[-6] != a5 && *(char*) &((unsigned short*) v15[-6])[1] != 6) {
				v5 = d2_AddWindowValueGauge(v6 - 0x23, (int) *(short*) ((int) g_772500 + 0x1ebda) + 5 + v10, 0x40, 0, 100, 0x75, 0x442, d2_CurrentWindowId);
				v15[-4] = v5;
				if (*(char*) &((unsigned short*) v15[-6])[1] != 7) {
					v5 = (int) gm_CalcEntityFavor(*v3, *(unsigned short*) v15[-6], 1);
					d2_SetElementValue(v15[-4], 0, 100, v5);
				} else {
					d2_SetElementValue(v5, 0, 100, 0);
				}
				d2_SetElementEnabled(v15[-4], 1);
				((D2_CONTROL_TL*) ((int) g_1015ea0))[v15[-4]].value_05c = 1;
			}
			if (v3 != 0 && *(char*) &v3[1] == 6 && *(int*) (v15[-6] + 0x210) == *(int*) &v3[2]) {
				d2_AddElementToWindow((int) *(short*) ((int) g_772500 + 0x1ebd8) + v11, v10, 0x6d3, d2_CurrentWindowId);
			}
			if (a2 == 0 || fcn_005cf720(g_774970, *(unsigned short*) v15[-6], a2, 0) != 0) {
				((D2_CONTROL_TL*) ((int) g_1015ea0))[v15[-5]].value_05c = 1;
				((D2_CONTROL_TL*) ((int) g_1015ea0))[v15[-5]].flags_1d0 = 3;
				*(int*) (&((D2_CONTROL_TL*) ((int) g_1015ea0))[v15[-5]].associated_object) = v15[-6];
			}
		} else {
			d2_AddElementToWindow((v6 - (int) *(short*) ((int) g_772500 + 0x1a2ac) / 2) - 3, v10 + 1, 0x4fb, d2_CurrentWindowId);
			io_FormatTextBuffer(caption, "%s", v15[-3] + 0x253);
			fcn_005c9090(caption, v6, v15[-1], 0xca, 0x56);
			((D2_CONTROL_TL*) ((int) g_1015ea0))[v15[-5]].value_05c = 1;
			*(int*) (&((D2_CONTROL_TL*) ((int) g_1015ea0))[v15[-5]].associated_object) = 0;
			d2_SetElementEnabled(v15[-5], 0);
		}
		v17 += 1;
		v15 = &v15[0xe];
	} while (v17 < a3);
	return 0;
}
