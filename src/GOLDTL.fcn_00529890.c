#include <stdio.h>

extern char* g_1015ea0;
extern unsigned char* g_entity_type_table;
extern int g_67d370;
extern int g_772514;
extern char g_6b5c60[];

void fcn_0046b2b0(int id);
int fcn_0046f100(int x, int y, int cx, int cy, int a5, int win);
void fcn_0046f280(int id);
int fcn_0046f740(int x, int y, int id, int win);
int fcn_0046f7e0(int x, int y, int id, int win, int a5);
void fcn_0046f940(int id, char* text);
int d2_ShowTxt(int x, int y, char* text, int win);
void d2_SetElementValue(int id, ...);
void fcn_00472640(int id, int flag);
void fcn_004727a0(int screen, int flag);
void fcn_00473690(int key, int amount);
void ResetDisplayCounters(void);
void fcn_004c3540(char* entity);
float fcn_004ff040(char* entity);
int fcn_00507c30(int key);
void fcn_00517c00(int id, int a, int b, char* out);
void fcn_00529160(char* obj, int a, int id, int b);
int fcn_00529800(char* entity, int* out);
void fcn_0052ae70(void);
void fcn_00534210(int a, int b, char* entity, int c, int d);

/* ADDRESS: GOLDTL 0x00529890 */
void __cdecl fcn_00529890(char* a0)
{
	unsigned char* v2;
	char* v11;
	char* v12;
	int* v13;
	unsigned int* v14;
	char v1;
	int v3;
	unsigned int v4;
	int v5;
	int v6;
	unsigned int v7;
	int out[3];
	int v15;
	unsigned int v16;
	char v8[256];
	char v9[128];

	if (*(int*) 0x6a25b4 != -1) {
		v12 = (char*) (g_entity_type_table + (unsigned int) *a0 * 0x24d);
		fcn_004727a0(*(int*) 0x6a25b4, 1);
		ResetDisplayCounters();
		v13 = (int*) 0x7e30cc;
		do {
			if (v13[1] != -1) {
				v3 = v13[1] * 0x21c;
				if (!*(int*) (v3 + 0x7f4e24) || !*(char*) (v3 + 0x7f4ca8)) {
					if (v13[-1] != -1) {
						fcn_0046b2b0(v13[-1]);
						v13[-1] = -1;
					}
					if (*v13 != -1) {
						fcn_0046b2b0(*v13);
						*v13 = -1;
					}
					fcn_0046b2b0(v13[-3]);
					v13[-3] = -1;
					fcn_0046b2b0(v13[2]);
					v13[2] = -1;
					fcn_0046b2b0(v13[-2]);
					v13[-2] = -1;
					if (v13[3] != -1) {
						fcn_0046f280(v13[3]);
					}
					v13[3] = -1;
					v13[1] = 0xffff;
				}
			}
			v13 = &v13[10];
		} while ((int) v13 < 0x7e35cc);
		v3 = 0;
		v11 = (char*) 0x7f4e05;
		do {
			if (*(char**) (v11 + 7) == a0 && *(int*) (v11 + 0x1f) && v11[-0x15d]) {
				if (*(unsigned char*) 0x774724) {
					if (*(unsigned char*) 0x774724 != 1
						|| (v6 = fcn_00507c30(*v11), !v11[-1]
							&& (v6 == 10 || v6 == 0xb || v6 == 0xc))) {
label_529a17:
						v6 = 0;
						v13 = (int*) 0x7e30d0;
						do {
							if (*v13 == v3) {
								if (v6 <= 0x1f) {
									goto label_529c64;
								}
								break;
							}
							v13 = &v13[10];
							v6 += 1;
						} while ((int) v13 < 0x7e35d0);
						v6 = 0;
						v13 = (int*) 0x7e30d0;
						do {
							if (*v13 == 0xffff) {
								break;
							}
							v13 = &v13[10];
							v6 += 1;
						} while ((int) v13 < 0x7e35d0);
						if (0x20 < v6) {
							break;
						}
						fcn_00517c00(v3, 1, 1, v8);
						fcn_004727a0(*(int*) 0x6a25b4, 1);
						v5 = v6 * 0x4e;
						v6 *= 0x28;
						v4 = fcn_0046f740(6, v5, 0x5dc, g_772514);
						v16 = *(unsigned int*) (v11 + 0x27);
						*(unsigned int*) (v6 + 0x7e30c4) = v4;
						v16 = fcn_0046f740(8, v5 + 0x11, v16, g_772514);
						*(unsigned int*) (v6 + 0x7e30c0) = v16;
						v15 = d2_ShowTxt(0, v5 + 4, g_6b5c60, g_772514);
						*(int*) (v6 + 0x7e30d4) = v15;
						*(unsigned int*) (g_1015ea0 + 0x6c + v15 * 0x2f4) = 1;
						*(unsigned int*) (g_1015ea0 + 0x18
							+ *(int*) (v6 + 0x7e30d4) * 0x2f4) = 0x5f;
						*(unsigned int*) (g_1015ea0 + 0x58
							+ *(int*) (v6 + 0x7e30c0) * 0x2f4) = 1;
						*(char**) (g_1015ea0 + 0x2f0
							+ *(int*) (v6 + 0x7e30c0) * 0x2f4) = &v11[-0x165];
						if (*(int*) (v6 + 0x7e30d8) != -1) {
							fcn_0046f280(*(int*) (v6 + 0x7e30d8));
							*(unsigned int*) (v6 + 0x7e30d8) = 0xffffffff;
						}
						*(int*) (v6 + 0x7e30d0) = v3;
						*(unsigned int*) (v6 + 0x7e30dc) = 0;
						v1 = *v12;
						if (v1 == 0x10 || v1 == 0x13 || v1 == 0x04) {
							fcn_004727a0(*(int*) 0x6a25b4, 1);
							v16 = fcn_0046f100(6, v5 + 0x3f, 0x50, 0xf, 0,
								g_772514);
							*(unsigned int*) (v6 + 0x7e30d8) = v16;
							fcn_0046f740(4, 1, 0x5df, g_772514);
							fcn_00534210(0x10, 4,
								(char*) (*(int*) (v6 + 0x7e30d0) * 0x21c
									+ 0x7f4ca0), 2, 0x4f1);
							fcn_0046f740(0x28, 1, 0x5e0, g_772514);
							fcn_00534210(0x34, 4,
								(char*) (*(int*) (v6 + 0x7e30d0) * 0x21c
									+ 0x7f4ca0), 3, 0x4f1);
						}
						v16 = *(unsigned int*) (v6 + 0x7e30c0);
						d2_SetElementValue(v16, v11[0x23] != '\0');
					}
				}
				else if ((*v11 == v12[0x22f] || *v11 == v12[0x230])
					&& !v11[-1]) {
					goto label_529a17;
				}
			}
label_529c64:
			v11 = &v11[0x21c];
			v3 += 1;
		} while ((int) v11 < 0x85a205);
		v2 = (unsigned char*) a0;
		v13 = (int*) 0x7e30d0;
		do {
			if (*(int*) 0x100f1dc != -1) {
				v3 = *v13;
				if (v3 != 0xffff) {
					if (g_67d370 == v13[-4]) {
						if (*(int*) (g_1015ea0 + 0x38 + v13[-4] * 0x2f4)) {
							*(char*) (v3 * 0x21c + 0x7f4e28) = 1;
							fcn_004c3540((char*) (v3 * 0x21c + 0x7f4ca0));
						}
						else {
							*(char*) (v3 * 0x21c + 0x7f4e28) = 0;
						}
					}
					goto label_529cf0;
				}
label_529d30:
				v3 = v13[-4];
				v16 = 0;
			}
			else {
label_529cf0:
				if (*v13 == 0xffff) {
					goto label_529d30;
				}
				v3 = *v13 * 0x21c;
				if (*(int*) (*(int*) (v3 + 0x7f4e24) + 0x2c)
					!= *(int*) &v2[1]
					|| (*(unsigned int*) (v3 + 0x7f4e68) & 0x800)
					|| *(char*) (v3 + 0x7f4e20) == 0x14) {
					goto label_529d30;
				}
				v3 = v13[-4];
				v16 = 1;
			}
			fcn_00472640(v3, v16);
			v13 = &v13[10];
		} while ((int) v13 < 0x7e35d0);
		v3 = 0x28;
		v13 = (int*) 0x7e30c8;
		do {
			if (v13[2] != 0xffff) {
				if (*(char*) (v13[2] * 0x21c + 0x7f4e28)) {
					fcn_00473690(*(unsigned int*) (g_1015ea0 + 8
						+ v13[-2] * 0x2f4), 1);
					d2_SetElementValue(v13[-2], 1);
				}
				else {
					d2_SetElementValue(v13[-2], 0);
				}
				if (*v13 != -1) {
					fcn_0046b2b0(*v13);
					*v13 = -1;
				}
				if (v13[1] != -1) {
					fcn_0046b2b0(v13[1]);
					v13[1] = -1;
				}
				fcn_004727a0(*(int*) 0x6a25b4, 1);
				if (v13[3] != -1) {
					v16 = (unsigned int) (fcn_004ff040(
						(char*) (v13[2] * 0x21c + 0x7f4ca0))
						* *(double*) 0x662c38);
					sprintf(v9, "%s %i%%",
						(char*) (v13[2] * 0x21c + 0x7f4cd0), v16);
					fcn_0046f940(v13[3], v9);
					*(unsigned int*) (g_1015ea0 + 0x18
						+ v13[3] * 0x2f4) = 0x5f;
				}
				v5 = fcn_00529800((char*) (v13[2] * 0x21c + 0x7f4ca0),
					out);
				v6 = out[0];
				if (v5) {
					v15 = -1;
					if (2 <= v5) {
						v15 = out[1];
					}
					if (out[0] != -1) {
						v5 = *v13;
						if (v5 != -1) {
							if (out[0] == *(int*) (g_1015ea0 + 8
								+ v5 * 0x2f4)) {
								goto label_529f4c;
							}
							fcn_0046b2b0(v5);
							*v13 = -1;
							if (out[0] >= 0xdf && out[0] <= 0x3bb) {
								v6 = fcn_0046f7e0(0x38, v3 - 0x18,
									out[0], g_772514, -2);
							}
							else {
								v6 = fcn_0046f740(0x38, v3 - 0x18,
									v6, g_772514);
							}
						}
						else if (out[0] >= 0xdf && out[0] <= 0x3bb) {
							v6 = fcn_0046f7e0(0x38, v3 - 0x18,
								out[0], g_772514, -2);
						}
						else {
							v6 = fcn_0046f740(0x38, v3 - 0x18,
								v6, g_772514);
						}
						*v13 = v6;
					}
label_529f4c:
					if (v15 != -1) {
						v6 = v13[1];
						if (v6 != -1) {
							if (v15 == *(int*) (g_1015ea0 + 8
								+ v6 * 0x2f4)) {
								goto label_529fe5;
							}
							fcn_0046b2b0(v6);
							v13[1] = -1;
							if (v15 >= 0xdf && v15 <= 0x3bb) {
								v6 = fcn_0046f7e0(0x38, v3, v15,
									g_772514, -2);
							}
							else {
								v6 = fcn_0046f740(0x38, v3, v15,
									g_772514);
							}
						}
						else if (v15 >= 0xdf && v15 <= 0x3bb) {
							v6 = fcn_0046f7e0(0x38, v3, v15,
								g_772514, -2);
						}
						else {
							v6 = fcn_0046f740(0x38, v3, v15,
								g_772514);
						}
						v13[1] = v6;
					}
				}
			}
label_529fe5:
			v2 = (unsigned char*) a0;
			v3 += 0x4e;
			v13 = &v13[10];
		} while (v3 < 0x9e8);
		v13 = (int*) 0x7e30d0;
		do {
			if (*v13 != 0xffff) {
				v7 = (unsigned int) (*(char*) (*v13 * 0x21c
					+ 0x7f4e28) != '\0');
				v13[4] = v7;
				*(unsigned int*) (g_1015ea0 + 0x38 + v13[-4] * 0x2f4) = v7;
				*(unsigned int*) (g_1015ea0 + 0x3c + v13[-4] * 0x2f4) = v7;
			}
			v13 = &v13[10];
		} while ((int) v13 < 0x7e35d0);
		if (*(int*) 0x100f1dc == 0x51d) {
			v14 = (unsigned int*) 0x7e30d0;
			do {
				if (v14[4]) {
					fcn_00529160(a0, 0, *v14, 0);
				}
				v14 = &v14[10];
			} while ((int) v14 < 0x7e35d0);
			fcn_0052ae70();
		}
		if (*(int*) 0x7ea360
			&& !*(char*) (*(int*) 0x7ea360 + 0x188)) {
			*(int*) 0x7ea360 = 0;
		}
	}
	return;
}
