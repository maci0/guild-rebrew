#include <string.h>
#pragma intrinsic(memset)
extern char g_6b5c60;
extern int g_772560;
extern int g_1038580;
extern int g_772528;
extern int d2_CurrentWindowId;
#include "Develop/DieGildeAddOn/game/game_data.h"
extern float g_6628a8;
extern int g_67d3a0;
extern int g_6b7fdc;
#include "Develop/Units/d2.v1/d2_gui.h"
extern int g_1040494;
extern char s_67d268[];
extern char s_67d774[];
extern char s_67d474[];
extern char s_67d798[];
extern char* txt_TextEntries[];

void* __cdecl vfs_Tfopen(const char* name, const char* mode, int root);
int __cdecl vfs_ReadData(char* buf, int size, int count, void* stream);
int __cdecl vfs_fseek(void* f, int off, int whence);
void __cdecl CloseVfsStream(void* f);
int __cdecl fcn_00465950(const char* name);
void __cdecl d2_AddRefcount(int a0);
int __cdecl fcn_0046f100(int a, int b, int c, int d, int e, int f);
int __cdecl fcn_0046e940(int a, int b, int c, int d, int e);
void __cdecl d2_SetBackgroundTexture(const char* name, int win);
int __cdecl fcn_0046f740(int a, int b, int c, int d);
int __cdecl fcn_00467480(int a, int b, int c, int d, int e, int f);
int __cdecl fcn_004677e0(int a, int b, int c, int d, int e, int f,
	int g, int h);
int __cdecl txt_FindEntryIndex(const char* name);
int __cdecl fcn_0046fac0(int a, int b, int c, int d);
void __cdecl fcn_00469c40(int x, int y, int slot);
int __cdecl sprintf(char*, const char*, ...);
char* __cdecl strcpy(char*, const char*);
char* __cdecl strcat(char*, const char*);
int __cdecl strcmp(const char*, const char*);

/* ADDRESS: GOLDTL 0x00470820 */
int __cdecl fcn_00470820(int a0, int a1, char* formName)
{
	char v22[256];
	char formPath[256];
	char v23[8];
	int v40;
	int formCount;
	int v25;
	int* v26;
	int v27;
	int v28;
	int v29;
	int v30;
	int v31;
	int* v32;
	int* v33;
	int v34;
	int v35;
	int* v36;
	int v37;
	int v38;
	int* v39;
	int v41;
	int v42;
	int v43;
	int v44;
	int v45;
	int v5;
	int v6;
	int v7;
	int v8;
	int v9;
	int v13;
	int v15;
	int* v10;
	int v11;
	int v12;
	int v17;
	int v16;
	int v18;
	int v19;
	int v20;
	int v3;
	int i;
	int* p;
	int* q;
	int* r;
	int* s;
	int* t;
	char* d;
	char* c;
	char ch;

	formPath[0] = g_6b5c60;
	memset(formPath + 1, 0, 255);

	strcpy(formPath, formName);
	if (!g_772560) {
		strcpy(formPath, s_67d268);
		strcat(formPath, formName);
		strcat(formPath, ".form");
	}
	v15 = (int) vfs_Tfopen(formPath, (char*) 0x6750e8, g_6b7fdc);
	if (!v15) {
		sprintf(v22, s_67d774, formName);
		return -1;
	}
	vfs_ReadData(v23, 1, 4, (void*) v15);
	v40 = (signed char) v23[3] - 0x30;
	v23[4] = 0;
	if (v40 == 2) {
		vfs_ReadData((char*) &formCount, 4, 1, (void*) v15);
		vfs_ReadData((char*) 0x711a80, 0x101c, formCount, (void*) v15);
	} else {
		v40 = 0;
		vfs_fseek((void*) v15, 0, 0);
		vfs_ReadData((char*) &formCount, 4, 1, (void*) v15);
		vfs_ReadData((char*) 0x6b8b00, 0xed4, formCount, (void*) v15);
	}
	CloseVfsStream((void*) v15);
	v35 = 1;
	if (g_1038580) {
		v15 = 0x1038580;
		do {
			if (v15 >= 0x1040604)
				return -1;
			v26 = (int*) (v15 + 700);
			v15 += 700;
			v35++;
		} while (*(int*) v26);
		if (v35 >= 0x30)
			return -1;
	}
	v44 = 0;
	v15 = v35 * 700;
	*(int*) (v15 + 0x10382d4) = g_772528 - 1;
	if (formCount > 0) {
		v39 = (int*) 0x6b8b00;
		v36 = (int*) 0x712950;
		v43 = v35 * 0xaf;
		v32 = (int*) (v35 * 700 + 0x1038144);
		v44 = 0;
		do {
			v13 = v40;
			v10 = v39;
			v26 = (int*) ((char*) v36 - 0xed0);
			if (v40) {
				v33 = v26;
				if (v40 == 2) {
					if (*(int*) v36) {
						v45 = *(int*) ((*(int*) v36 + v43) * 4 + 0x1038140);
						v42 = v45 * 0x3cc + 0x1015f40;
						v11 = fcn_0046f100(
							(short) ((short) *v26
							- *(short*) (v42 + 4)),
							(short) (*((short*) v36 - 0x767)
							- *(short*) (v42 + 8)),
							(short) v36[-0x3b3],
							(short) *((short*) v36 - 0x765),
							v36[-0x3b2], v45);
					} else {
						v11 = fcn_0046e940(
							(short) *v26,
							(short) *((short*) v36 - 0x767),
							(short) v36[-0x3b3],
							(short) *((short*) v36 - 0x765),
							v36[-0x3b2]);
					}
					v8 = 0;
					*v32 = v11;
					if ((char) v36[0x1f])
						d2_SetBackgroundTexture((char*) &v36[0x1f],
							d2_CurrentWindowId);
					v11 = d2_CurrentWindowId * 0x3cc;
					if ((*(unsigned char*) (v11 + 0x1015f54) & 1)
						&& *(float*) ((char*) v36 + 0xbc)
						== g_6628a8)
						*(unsigned int*) (v11 + 0x10162e4) =
							0x3f266666;
					else
						*(int*) (v11 + 0x10162e4) =
							*(int*) ((char*) v36 + 0xbc);
				}
			} else {
				v33 = v39;
				v26 = v10;
				if (v39[0x3a5]) {
					v45 = *(int*) ((v39[0x3a5]
						+ v43) * 4 + 0x1038140);
					v42 = v45 * 0x3cc + 0x1015f40;
					v11 = fcn_0046f100(
						(short) ((short) *v39
						- *(short*) (v42 + 4)),
						(short) (*((short*) v39 + 1)
						- *(short*) (v42 + 8)),
						(short) v39[1],
						(short) *((short*) v39 + 3),
						v39[2], v45);
					*v32 = v11;
				} else {
					v11 = v39[2];
					v5 = *((short*) v39 + 3);
					v8 = v39[1];
					v6 = *((short*) v39 + 1);
					v7 = *v39;
					*v32 = fcn_0046e940(
						(short) v7, (short) v6,
						(short) v8, (short) v5, v11);
				}
			}
			v41 = *v32 * 0x3cc + 0x1015f40;
			if (v13 == 2) {
				if (*(char*) ((char*) v26 + 0xe90))
					p = (int*) ((char*) v26 + 0xe90);
				else
					p = (int*) s_67d474;
				v12 = fcn_00465950((char*) p);
				*(unsigned int*) (v41 + 0x28c) = v12;
				if (*(char*) ((char*) v26 + 0xed4)) {
					v12 = fcn_00465950(
						(char*) v26 + 0xed4);
					*(unsigned int*) (v41 + 0x398) =
						v12;
					d2_AddRefcount(v12);
				}
				v13 = v26[0x3c6];
				v5 = *(short*) ((char*) v26 + 0xf16);
				*(int*) (v41 + 0x18) =
					(short) v26[0x3c5];
				*(int*) (v41 + 0x20) = (short) v13;
				v6 = *(short*) ((char*) v26 + 0xf1a);
				*(int*) (v41 + 0x1c) = (int) v5;
				*(int*) (v41 + 0x24) = (int) v6;
				if (*(unsigned char*) (v41 + 0x14) & 4) {
					v13 = fcn_00465950(
						(char*) v26 + 0xf90);
					*(int*) (v41 + 0x288) = v13;
					if (v13 == -1)
						*(unsigned int*) (v41 + 0x288)
							= g_67d3a0;
				}
			}
			v38 = 0;
			*(int*) (&((D2_CONTROL_TL*)g_1015ea0)[*(int*) (*(int*) v32 * 0x3cc + 0x10161bc)].value_050)

 = v15 + 0x1038140;
			v34 = *v32;
			v13 = v33[0x33];
			*(int*) (v15 + 0x10382c4) =
				*(int*) (v15 + 0x10382c4) + 1;
			if ((short) v13 >= 1) {
				q = (int*) ((char*) v33 + 0xc);
				v19 = (int*) ((char*) v33 + 0x190);
				t = (int*) ((char*) v33 + 0xd90);
				do {
					if (t[-0x330] <= 0x3f) {
						v12 = fcn_00465950((char*) v19);
						v13 = fcn_0046f740((short) *q,
							(short) q[0x18], v12, v34);
						if (*t == 0x12) {
							*(unsigned int*) (&((D2_CONTROL_TL*)g_1015ea0)[v13].value_058)
 = 1;
							*(unsigned int*) (&((D2_CONTROL_TL*)g_1015ea0)[v13].value_05c)
 = 0;
						}
						if (*t == 8) {
							*(unsigned int*) (&((D2_CONTROL_TL*)g_1015ea0)[v13].value_058)
 = 0;
							*(unsigned int*) (&((D2_CONTROL_TL*)g_1015ea0)[v13].value_05c)
 = 1;
						}
						*(int*) (&((D2_CONTROL_TL*)g_1015ea0)[v13].value_050)
 =
							v15 + 0x1038140;
					}
					if (t[-0x330] == 0x43) {
						if (strcmp((char*) v19,
							&g_6b5c60) != 0) {
							v13 = txt_FindEntryIndex(
								(char*) v19);
							if (v13 != -1) {
								v12 = fcn_0046fac0(
									(short) *q,
									(short) q[0x18],
									*(int*) (v13 * 4
										+ 0x14a5320),
									v34);
								v13 = v12 * 0x2f4;
								*(unsigned int*) (&((D2_CONTROL_TL*)(g_1015ea0 + v13))->value_008) =
									txt_FindEntryIndex(
									(char*) v19);
								*(int*) (&((D2_CONTROL_TL*)(g_1015ea0 + v13))->value_050) =
									v15 + 0x1038140;
							}
						}
					} else if (t[-0x330] == 0x41) {
						v37 = *t & 0xff;
						v13 = fcn_00467480(
							(short) *q,
							(short) q[0x18],
							*(unsigned char*) ((char*) t + 1),
							*(unsigned char*) ((char*) t + 2),
							v37, v34);
						*(int*) (&((D2_CONTROL_TL*)g_1015ea0)[v13].value_050) =
							v15 + 0x1038140;
					} else if (t[-0x330] == 0x45) {
						v37 = *t & 0xff;
						v12 = fcn_00465950(
							(char*) v19);
						v13 = fcn_004677e0(
							(short) *q,
							(short) q[0x18],
							*(unsigned char*) ((char*) v33
								+ v38 + 0xf1c),
							0, 100, v12,
							v37, v34);
						*(int*) (&((D2_CONTROL_TL*)g_1015ea0)[v13].value_050) =
							v15 + 0x1038140;
					}
					t++;
					v38++;
					q = (int*) ((char*) q + 2);
					v19 = (int*) ((char*) v19 + 0x40);
				} while (v38 < (short) v33[0x33]);
			}
			if (*(char*) ((char*) v33 + 0xe50)) {
				v13 = txt_FindEntryIndex(
					(char*) v33 + 0xe50);
				if (v13 != -1) {
					p = (int*) *(char**) (v13 * 4
						+ 0x14a5320);
					d = *(char**) (v41 + 0x3c);
					do {
						ch = *(char*) p;
						p = (int*) ((char*) p + 1);
						*d = ch;
						d++;
					} while (ch);
				}
				*(int*) (v41 + 0x250) = v13;
			} else {
				*(unsigned int*) (v41 + 0x250) = 0xffffffff;
			}
			if (!v40) {
				v5 = *(short*) ((char*) v33 + 0xe9e);
				v11 = v33[0x3a8];
				*(int*) (v41 + 0x18) = (short) v33[0x3a7];
				*(int*) (v41 + 0x1c) = (int) v5;
				v5 = *(short*) ((char*) v33 + 0xea2);
				*(int*) (v41 + 0x20) = (short) v11;
				*(int*) (v41 + 0x24) = (int) v5;
				if (*(short*) ((char*) v33 + 0xe90))
					v11 = *(short*) ((char*) v33 + 0xe90);
				else
					v11 = fcn_00465950(s_67d474);
				v8 = v33[0x3a6];
				*(int*) (v41 + 0x28c) = v11;
				if (v8 > 0)
					*(int*) (v41 + 0x398) = v8;
			}
			v44++;
			v32++;
			v36 += 0x407;
			v39 += 0x3b5;
		} while (v44 < formCount);
	}
	v13 = v35;
	*(unsigned int*) (v15 + 0x10382d0) = 1;
	*(unsigned int*) (v15 + 0x10382dc) = 1;
	*(unsigned int*) (v15 + 0x10382e0) = 1;
	*(int*) (v15 + 0x1038140) = v35;
	g_772534 = v35;
	g_772560 = 0;
	strcpy((char*) (v15 + 0x1038374), formName);
	v41 = *(int*) (v15 + 0x1038144) * 0x3cc + 0x1015f40;
	if (a0 || a1)
		fcn_00469c40(a0, a1,
			*(int*) (v41 + 0x27c));
	if (*(int*) (v41 + 4) + *(int*) (v41 + 0xc)
		> g_1040494)
		fcn_00469c40(g_1040494 - *(int*) (v41 + 0xc),
			*(int*) (v41 + 8),
			*(int*) (v41 + 0x27c));
	return v13;
}
