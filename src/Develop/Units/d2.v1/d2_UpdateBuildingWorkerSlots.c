#include <stdio.h>

#include "Develop/Units/d2.v1/d2_gui.h"
extern unsigned char* g_entity_type_table;
#include "Develop/DieGildeAddOn/game/game_data.h"
extern int d2_CurrentWindowId;
extern char str_empty[]; extern int g_6a25b4; extern char g_774724;

void d2_DestroyElement(int id);
int d2_CreateChildWindow(int x, int y, int cx, int cy, int a5, int win);
void d2_CloseWindow(int id);
int d2_AddElementToWindow(int x, int y, int id, int win);
int d2_AddWindowImage(int x, int y, int id, int win, int a5);
void d2_SetLabelText(int id, char* text);
int d2_ShowTxt(int x, int y, char* text, int win);
void d2_SetElementValue(int id, ...);
void d2_SetElementEnabled(int id, int flag);
void d2_SetForm(int screen, int flag);
void d2_AddDisplayCounter(int key, int amount);
void ResetDisplayCounters(void);
void d3snd_PlayObjectClickSound(char* entity);
float gm_GetEntityHealthRatio(char* entity);
int gm_MapEntityToCategorySlot(int key);
void gm_FormatEntityTitleAndName(int id, int a, int b, char* out);
void he_AssignActionSlot(char* obj, int a, int id, int b);
int d2_GetEntityGearIcons(char* entity, int* out);
void sv_ClearObjectSelection(void);
void d2_DrawSkillBar(int a, int b, char* entity, int c, int d);

/* ADDRESS: GOLDTL 0x00529890 */
void __cdecl d2_UpdateBuildingWorkerSlots(char* building)
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
	int out[8];
	int v15;
	unsigned int v16;
	char v8[256];
	char v9[120];

	if (g_6a25b4 != -1) {
		v12 = (char*) (g_entity_type_table + (unsigned int) (unsigned char) *building * 0x24d);
		d2_SetForm(g_6a25b4, 1);
		ResetDisplayCounters();
		v13 = (int*) 0x7e30cc;
		do {
			if (v13[1] != 0xffff) {
				v3 = v13[1] * 0x21c;
				if (!*(int*) (v3 + 0x7f4e24) || !*(char*) (v3 + 0x7f4ca8)) {
					if (v13[-1] != -1) {
						d2_DestroyElement(v13[-1]);
						v13[-1] = -1;
					}
					if (*v13 != -1) {
						d2_DestroyElement(*v13);
						*v13 = -1;
					}
					d2_DestroyElement(v13[-3]);
					v13[-3] = -1;
					d2_DestroyElement(v13[2]);
					v13[2] = -1;
					d2_DestroyElement(v13[-2]);
					v13[-2] = -1;
					if (v13[3] != -1) {
						d2_CloseWindow(v13[3]);
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
			if (*(char**) (v11 + 7) == building && *(int*) (v11 + 0x1f) && v11[-0x15d]) {
				if (!(unsigned char) g_774724) {
					if ((*v11 != v12[0x22f] && *v11 != v12[0x230]) || v11[-1]) {
						goto label_529c64;
					}
				}
				else if ((unsigned char) g_774724 == 1) {
					v6 = gm_MapEntityToCategorySlot((unsigned char) *v11);
					if (v11[-1] || (v6 != 10 && v6 != 0xb && v6 != 0xc)) {
						goto label_529c64;
					}
				}
				v6 = 0;
				v13 = (int*) 0x7e30d0;
				do {
					if (*v13 == v3) {
						if (v6 < 0x20) {
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
				gm_FormatEntityTitleAndName(v3, 1, 1, v8);
				d2_SetForm(g_6a25b4, 1);
				v5 = v6 * 0x4e;
				v6 *= 0x28;
				v4 = d2_AddElementToWindow(6, v5, 0x5dc, d2_CurrentWindowId);
				v16 = *(unsigned int*) (v11 + 0x27);
				*(unsigned int*) (v6 + 0x7e30c4) = v4;
				v16 = d2_AddElementToWindow(8, v5 + 0x11, v16, d2_CurrentWindowId);
				*(unsigned int*) (v6 + 0x7e30c0) = v16;
				v15 = d2_ShowTxt(0, v5 + 4, str_empty, d2_CurrentWindowId);
				*(int*) (v6 + 0x7e30d4) = v15;
				*(unsigned int*) (((char*)&((D2_CONTROL_TL*)d2_Controls)[v15].value_06c)) = 1;
				*(unsigned int*) (&((D2_CONTROL_TL*)d2_Controls)
					[*(int*) (v6 + 0x7e30d4)].width) = 0x5f;
				*(unsigned int*) (&((D2_CONTROL_TL*)d2_Controls)
					[*(int*) (v6 + 0x7e30c0)].value_058) = 1;
				*(char**) (&((D2_CONTROL_TL*)d2_Controls)
					[*(int*) (v6 + 0x7e30c0)].associated_object) = &v11[-0x165];
				if (*(int*) (v6 + 0x7e30d8) != -1) {
					d2_CloseWindow(*(int*) (v6 + 0x7e30d8));
					*(unsigned int*) (v6 + 0x7e30d8) = 0xffffffff;
				}
				*(int*) (v6 + 0x7e30d0) = v3;
				*(unsigned int*) (v6 + 0x7e30dc) = 0;
				v1 = *v12;
				if (v1 == 0x10 || v1 == 0x13 || v1 == 0x04) {
					d2_SetForm(g_6a25b4, 1);
					v16 = d2_CreateChildWindow(6, v5 + 0x3f, 0x50, 0xf, 0,
						d2_CurrentWindowId);
					*(unsigned int*) (v6 + 0x7e30d8) = v16;
					d2_AddElementToWindow(4, 1, 0x5df, d2_CurrentWindowId);
					d2_DrawSkillBar(0x10, 4,
						(char*) (*(int*) (v6 + 0x7e30d0) * 0x21c
							+ 0x7f4ca0), 2, 0x4f1);
					d2_AddElementToWindow(0x28, 1, 0x5e0, d2_CurrentWindowId);
					d2_DrawSkillBar(0x34, 4,
						(char*) (*(int*) (v6 + 0x7e30d0) * 0x21c
							+ 0x7f4ca0), 3, 0x4f1);
				}
				v16 = *(unsigned int*) (v6 + 0x7e30c0);
				d2_SetElementValue(v16, v11[0x23] != '\0');
			}
label_529c64:
			v11 = &v11[0x21c];
			v3 += 1;
		} while ((int) v11 < 0x85a205);
		v2 = (unsigned char*) building;
		v13 = (int*) 0x7e30d0;
		do {
			if (*(int*) 0x100f1dc != -1) {
				v3 = *v13;
				if (v3 == 0xffff) {
					goto label_529d30;
				}
				if (d2_CurrentElementId == v13[-4]) {
					if (*(int*) (((char*)&((D2_CONTROL_TL*)d2_Controls)[v13[-4]].value_038))) {
						*(char*) (v3 * 0x21c + 0x7f4e28) = 1;
						d3snd_PlayObjectClickSound((char*) (v3 * 0x21c + 0x7f4ca0));
					}
					else {
						*(char*) (v3 * 0x21c + 0x7f4e28) = 0;
					}
				}
			}
			if (*v13 == 0xffff) {
				goto label_529d30;
			}
			v3 = *v13 * 0x21c;
			if (*(int*) (*(int*) (v3 + 0x7f4e24) + 0x2c)
				!= *(int*) &v2[1]
				|| (*(int*) (v3 + 0x7f4e68) & 0x800)
				|| *(char*) (v3 + 0x7f4e20) == 0x14) {
label_529d30:
				d2_SetElementEnabled(v13[-4], 0);
			}
			else {
				d2_SetElementEnabled(v13[-4], 1);
			}
			v13 = &v13[10];
		} while ((int) v13 < 0x7e35d0);
		v3 = 0x28;
		v13 = (int*) 0x7e30c8;
		do {
			if (v13[2] != 0xffff) {
				if (!(*(char*) (v13[2] * 0x21c + 0x7f4e28))) {
					d2_SetElementValue(v13[-2], 0);
				} else {
					d2_AddDisplayCounter(*(unsigned int*) (&((D2_CONTROL_TL*)d2_Controls)
						[v13[-2]].value_008), 1);
					d2_SetElementValue(v13[-2], 1);
				}
				if (*v13 != -1) {
					d2_DestroyElement(*v13);
					*v13 = -1;
				}
				if (v13[1] != -1) {
					d2_DestroyElement(v13[1]);
					v13[1] = -1;
				}
				d2_SetForm(g_6a25b4, 1);
				if (v13[3] != -1) {
					v16 = (unsigned int) (gm_GetEntityHealthRatio(
						(char*) (v13[2] * 0x21c + 0x7f4ca0))
						* *(double*) 0x662c38);
					sprintf(v9, "%s %i%%",
						(char*) (v13[2] * 0x21c + 0x7f4cd0), v16);
					d2_SetLabelText(v13[3], v9);
					*(unsigned int*) (&((D2_CONTROL_TL*)d2_Controls)
						[v13[3]].width) = 0x5f;
				}
				v5 = d2_GetEntityGearIcons((char*) (v13[2] * 0x21c + 0x7f4ca0),
					out);
				if (v5) {
					v15 = -1;
					if (2 <= v5) {
						v15 = out[1];
					}
					v6 = out[0];
					if (v6 != -1) {
						v5 = *v13;
						if (v5 == -1) {
							if (v6 >= 0xdf && v6 <= 0x3bb) {
								v6 = d2_AddWindowImage(0x38, v3 - 0x18,
									v6, d2_CurrentWindowId, -2);
							}
							else {
								v6 = d2_AddElementToWindow(0x38, v3 - 0x18,
									v6, d2_CurrentWindowId);
							}
						}
						else {
							if (v6 == *(int*) (&((D2_CONTROL_TL*)d2_Controls)
								[v5].value_008)) {
								goto label_529f4c;
							}
							d2_DestroyElement(v5);
							*v13 = -1;
							if (v6 >= 0xdf && v6 <= 0x3bb) {
								v6 = d2_AddWindowImage(0x38, v3 - 0x18,
									v6, d2_CurrentWindowId, -2);
							}
							else {
								v6 = d2_AddElementToWindow(0x38, v3 - 0x18,
									v6, d2_CurrentWindowId);
							}
						}
						*v13 = v6;
					}
label_529f4c:
					if (v15 != -1) {
						v6 = v13[1];
						if (v6 != -1) {
							if (v15 == *(int*) (&((D2_CONTROL_TL*)d2_Controls)
								[v6].value_008)) {
								goto label_529fe5;
							}
							d2_DestroyElement(v6);
							v13[1] = -1;
							if (v15 != 0) {
								v6 = d2_AddWindowImage(0x38, v3, v15,
									d2_CurrentWindowId, -2);
							}
							else {
								v6 = d2_AddElementToWindow(0x38, v3, 0,
									d2_CurrentWindowId);
							}
						} else {
							if (v15 >= 0xdf && v15 <= 0x3bb) {
								v6 = d2_AddWindowImage(0x38, v3, v15,
									d2_CurrentWindowId, -2);
							}
							else {
								v6 = d2_AddElementToWindow(0x38, v3, v15,
									d2_CurrentWindowId);
							}
						}
						v13[1] = v6;
					}
				}
			}
label_529fe5:
			v2 = (unsigned char*) building;
			v3 += 0x4e;
			v13 = &v13[10];
		} while (v3 < 0x9e8);
		v13 = (int*) 0x7e30d0;
		do {
			if (*v13 != 0xffff) {
				v7 = (unsigned int) (*(char*) (*v13 * 0x21c
					+ 0x7f4e28) != '\0');
				v13[4] = v7;
				*(unsigned int*) (((char*)&((D2_CONTROL_TL*)d2_Controls)[v13[-4]].value_038)) = v7;
				*(unsigned int*) (((char*)&((D2_CONTROL_TL*)d2_Controls)[v13[-4]].value_03c)) = v7;
			}
			v13 = &v13[10];
		} while ((int) v13 < 0x7e35d0);
		if (*(int*) 0x100f1dc == 0x51d) {
			v14 = (unsigned int*) 0x7e30d0;
			do {
				if (v14[4]) {
					he_AssignActionSlot(building, 0, *v14, 0);
				}
				v14 = &v14[10];
			} while ((int) v14 < 0x7e35d0);
			sv_ClearObjectSelection();
		}
		if (*(int*) 0x7ea360
			&& !*(char*) (*(int*) 0x7ea360 + 0x188)) {
			*(int*) 0x7ea360 = 0;
		}
	}
	return;
}
