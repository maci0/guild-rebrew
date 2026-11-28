#include "Develop/DieGildeAddOn/game/entity_record.h"
#include "Develop/DieGildeAddOn/game/client_data.h"
#include "game_data.h"
extern char* g_774a68;
#include "Develop/DieGildeAddOn/game/game_data.h"
extern float g_6ab3e0;
extern char* g_1043370;
extern char* g_77255c;
unsigned char* __cdecl gm_StartFilteredEntitySearch(int, ...);
unsigned char* __cdecl gm_FindNextFilteredEntity(void);
void __cdecl d3_TransformPoint(char*, float*, float*);
int __cdecl d3sm_SampleHeight(float*, float*, int*, int*, float*);
int __cdecl d2_AddElementToWindow(int, int, int, int);
void __cdecl d2_ProjectMapCoordToScreen(char*, int, int);
void __cdecl d2_FormatPriceText(int, int);
void __cdecl d2_PositionControl(int, int, int);
int __cdecl gm_IsActionAllowedForEntity(unsigned short*, int*, unsigned char*);
char* __cdecl d3_FindSceneObject(int, int, int, char*);
void __cdecl d3_SelectSceneContext(int, int);
void __cdecl d2_UpdateWindowScroll(int);

typedef struct ScrollSlot {
	int handle;	/* 0x00 */
	char* ent;	/* 0x04 */
	int x;		/* 0x08 */
	int y;		/* 0x0c */
	float fx;	/* 0x10 */
	float fy;	/* 0x14 */
} ScrollSlot;

#define g_town_flags(t) (((unsigned char*) (t))[4])
#define g_town_dir(t) (*(int*) ((t) + 8))
#define g_town_count(t) (*(int*) ((t) + 0x27a4))
#define g_cur_dir d2_CurrentWindowId
#define g_cur_building g_77255c
#define g_entity_type(t) ((unsigned char*) ((char *)&((ENTITY_RECORD*)g_7f4ca0)[(t)]))
#include "Develop/Units/d2.v1/d2_gui.h"
/* ADDRESS: GOLDTL 0x005b0230 */
void __cdecl d2_BuildCityScrollMap(char* town)
{
	ScrollSlot* slot;
	ScrollSlot tmp;
	unsigned char* ent;
	unsigned char* list;
	unsigned char* next;
	char* obj;
	char* p;
	int* tab;
	int offs[16];
	int tex;
	int base_x;
	int base_y;
	int bld_x;
	int bld_y;
	int dir;
	int mode;
	int handle;
	int count;
	int idx;
	int i;
	int j;
	unsigned char kind_type;
	int kind;
	float pos[4];
	float height;
	unsigned char copied;
	ScrollSlot* candidate;

	tex = (int) g_1043370;
	idx = g_773d75 * 0x2f4;
	base_x = *(int*) (idx + 0x86834c);
	base_y = *(int*) (idx + 0x868350);

	offs[0] = 0;
	offs[1] = -1;
	offs[2] = 1;
	offs[3] = 0;
	offs[4] = 1;
	offs[5] = 0;
	offs[6] = 1;
	offs[7] = 1;
	offs[8] = 0;
	offs[9] = 1;
	offs[10] = -1;
	offs[11] = 1;
	offs[12] = -1;
	offs[13] = 0;
	offs[14] = -1;
	offs[15] = -1;

	slot = (ScrollSlot*) (town + 0xdc);
	for (i = 0x100; i != 0; i--) {
		slot->handle = -1;
		slot->ent = 0;
		slot++;
	}
	for (i = 0; i < 0x80; i++) {
		*(int*) (town + 0x24dc + i * 4) = -1;
	}
	for (i = 0; i < 0x300; i++) {
		*(int*) (town + 0x18dc + i * 4) = -1;
	}
	g_town_count(town) = 0;

	p = (char*) gm_StartFilteredEntitySearch(2, 5, 9, 4, g_774970);
	ent = gm_StartFilteredEntitySearch(1, 6);
	count = 0;
	slot = (ScrollSlot*) (town + 0xdc);
	if (ent != 0) {
		do {
			if (count >= 0x100) {
				break;
			}
			if (*ent != 'D' && *ent != 'E' && !(ent[0x5a] & 1)
			    && (*ent != 'G' || p != 0)) {
				slot->ent = (char*) ent;
				count++;
				slot++;
			}
			ent = gm_FindNextFilteredEntity();
			g_town_count(town) = count;
		} while (ent != 0);
	}

	dir = g_town_dir(town);
	g_cur_dir = dir;
	i = 0;
	slot = (ScrollSlot*) (town + 0xdc);
	if (g_town_count(town) > 0) {
		do {
			obj = slot->ent;
			handle = *(int*) (obj + 0x61);
			if (handle != 0) {
				d3_TransformPoint((char*) handle, (float*) (handle + 0x4c), pos);
				d3sm_SampleHeight((float*) tex, pos, &bld_x, &bld_y, &height);
				slot->x = bld_x;
				slot->y = bld_y;
				d2_ProjectMapCoordToScreen((char*) slot, base_x, base_y);
			} else {
				g_cur_dir = g_town_dir(town);
				g_cur_building = (char*) &g_1015f40[g_cur_dir];
				if (*obj == 'G') {
					bld_x = (int) ((float) *(int*) (tex + 0x20)
					               * (float) offs[2 * (unsigned char) obj[0x34]] * g_6ab3e0 * 0.48f
					               + (float) *(int*) (tex + 0x20) * g_6ab3e0 * 0.5f);
					bld_y = (int) ((float) *(int*) (tex + 0x20)
					               * (float) offs[2 * (unsigned char) obj[0x34] + 1] * g_6ab3e0 * 0.48f
					               + (float) *(int*) (tex + 0x20) * g_6ab3e0 * 0.5f);
				} else {
					bld_x = (int) ((float) *(int*) (tex + 0x20)
					               * (float) offs[2 * (unsigned char) obj[0x34]] * g_6ab3e0 * 0.435f
					               + (float) *(int*) (tex + 0x20) * g_6ab3e0 * 0.5f);
					bld_y = (int) ((float) *(int*) (tex + 0x20)
					               * (float) offs[2 * (unsigned char) obj[0x34] + 1] * g_6ab3e0 * 0.435f
					               + (float) *(int*) (tex + 0x20) * g_6ab3e0 * 0.5f);
				}
				slot->handle = d2_AddElementToWindow(bld_x, bld_y, *obj + 0x47f, dir);
				((D2_CONTROL_TL*) (g_1015ea0))[slot->handle].value_05c = 1;
				((D2_CONTROL_TL*) (g_1015ea0))[slot->handle].flags_1d0 = 0x43;
				((D2_CONTROL_TL*) (g_1015ea0))[slot->handle].value_1cc = 0x56;
				slot->x = bld_x - ((D2_CONTROL_TL*) (g_1015ea0))[slot->handle].width / 2;
				slot->y = bld_y - ((D2_CONTROL_TL*) (g_1015ea0))[slot->handle].height / 2;
				d2_PositionControl(*(int*) (g_cur_building + 4) + bld_x,
				             *(int*) (g_cur_building + 8) + bld_y, slot->handle);
				if (*obj == 'G') {
					p = (char*) (*(int*) (obj + 0x65) * 0x2f4 + 0x868060);
					next = (unsigned char*) ((char*) &((D2_CONTROL_TL*) (g_1015ea0))[slot->handle] + 0xcc);
					do {
						copied = *p++;
						*next++ = copied;
					} while (copied != 0);
				} else {
					d2_FormatPriceText((int) obj,
					             (int) ((char*) &((D2_CONTROL_TL*) g_1015ea0)[slot->handle] + 0xcc));
				}
				kind = *(unsigned short*) (obj + 0x27);
				if (kind != 0xffff) {
					kind_type = g_7f4ca2[kind].kind;
					if (kind_type == 5 || kind_type == 6 || kind_type == 7) {
						d2_AddElementToWindow(bld_x - 8, bld_y - 8,
						             *(int*) ((char *)&((ENTITY_RECORD*)g_7f4ca0)[kind] + 0x54),
						             g_cur_dir);
					}
				}
			}
			i++;
			slot++;
		} while (i < g_town_count(town));
	}

	if (g_town_count(town) > 1) {
		for (i = 0; i < g_town_count(town) - 1; i++) {
			slot = (ScrollSlot*) (town + 0xdc) + i;
			for (j = i + 1; j < g_town_count(town); j++) {
				candidate = (ScrollSlot*) (town + 0xdc) + j;
				if (candidate->y < slot->y) {
					tmp = *slot;
					*slot = *candidate;
					*candidate = tmp;
				}
			}
		}
	}

	dir = g_town_dir(town);
	g_cur_dir = dir;
	g_cur_building = (char*) &g_1015f40[dir];
	for (i = 0; i < 0x10; i++) {
		*(int*) (town + 0x26dc + i * 4) = -1;
	}
	tab = (int*) (town + 0x26dc);
	i = 0;
	if (g_town_count(town) > 0) {
		slot = (ScrollSlot*) (town + 0xdc);
		do {
			if (slot->handle == -1) {
				bld_x = (int) slot->fx;
				bld_y = (int) slot->fy;
				slot->handle = d2_AddElementToWindow(bld_x, bld_y,
				                      (unsigned char) *slot->ent + 0x47f, g_cur_dir);
				((D2_CONTROL_TL*) (g_1015ea0))[slot->handle].value_05c = 1;
				((D2_CONTROL_TL*) (g_1015ea0))[slot->handle].value_1dc = -1;
				((D2_CONTROL_TL*) (g_1015ea0))[slot->handle].value_1e0 = -1;
				((D2_CONTROL_TL*) (g_1015ea0))[slot->handle].flags_1d0 = 0x43;
				((D2_CONTROL_TL*) (g_1015ea0))[slot->handle].value_1cc = 0x56;
				if (*slot->ent == 'G') {
					p = (char*) (*(int*) (slot->ent + 0x65) * 0x2f4 + 0x868060);
					next = (unsigned char*) ((char*) &((D2_CONTROL_TL*) (g_1015ea0))[slot->handle] + 0xcc);
					do {
						copied = *p++;
						*next++ = copied;
					} while (copied != 0);
				} else {
					d2_FormatPriceText((int) slot->ent,
					             (int) ((char*) &((D2_CONTROL_TL*) g_1015ea0)[slot->handle] + 0xcc));
				}
				slot->x = bld_x - ((D2_CONTROL_TL*) (g_1015ea0))[slot->handle].width / 2;
				slot->y = bld_y - ((D2_CONTROL_TL*) (g_1015ea0))[slot->handle].height / 2;
				d2_PositionControl(*(int*) (g_cur_building + 4) + bld_x,
				             *(int*) (g_cur_building + 8) + bld_y, slot->handle);
				if (!gm_IsActionAllowedForEntity((unsigned short*) ((char *)&((ENTITY_RECORD*)g_7f4ca0)[g_774970]),
				                  (int*) (town + 0xc), (unsigned char*) slot->ent)) {
					((D2_CONTROL_TL*) (g_1015ea0))[slot->handle].value_05c = 0;
					((D2_CONTROL_TL*) (g_1015ea0))[slot->handle].flags_1d0 = 0;
				}
			}
			i++;
			slot++;
		} while (i < g_town_count(town));
	}

	i = 0;
	slot = (ScrollSlot*) (town + 0xdc);
	if (g_town_count(town) > 0) {
		do {
			if (slot->handle != -1) {
				kind = *(unsigned short*) (slot->ent + 0x27);
				if (kind != 0xffff) {
					kind_type = g_7f4ca2[kind].kind;
					if (kind_type == 5 || kind_type == 6 || kind_type == 7) {
						d2_AddElementToWindow(slot->x - 8, slot->y - 8,
						             *(int*) ((char *)&((ENTITY_RECORD*)g_7f4ca0)[kind] + 0x54),
						             g_cur_dir);
					}
				}
			}
			i++;
			slot++;
		} while (i < g_town_count(town));
	}

	if (g_town_flags(town) & 4) {
		mode = d3_CurrentContextIndex;
		d3_SelectSceneContext(0, 1);
		g_cur_dir = g_town_dir(town);
		g_cur_building = (char*) &g_1015f40[g_town_dir(town)];
		p = (char*) 0x6a4770;
		while (p < (char*) 0x6a4870) {
			obj = d3_FindSceneObject(0, 0x100, 0, p);
			if (obj != 0) {
				d3_TransformPoint(obj, (float*) (obj + 0x4c), pos);
				d3sm_SampleHeight((float*) tex, pos, &bld_x, &bld_y, &height);
				tmp.x = bld_x;
				tmp.y = bld_y;
				d2_ProjectMapCoordToScreen((char*) &tmp, base_x, base_y);
				bld_x = (int) tmp.fx;
				bld_y = (int) tmp.fy;
				handle = d2_AddElementToWindow(bld_x, bld_y, 0x550, g_cur_dir);
				((D2_CONTROL_TL*) (g_1015ea0))[handle].value_05c = 1;
				((D2_CONTROL_TL*) (g_1015ea0))[handle].flags_1d0 = 0x43;
				((D2_CONTROL_TL*) (g_1015ea0))[handle].value_1cc = 0x56;
				*(int*) (&((D2_CONTROL_TL*) (g_1015ea0))[handle].associated_object) = (int) obj;
				*tab = handle;
				tab++;
			}
			p += 0x20;
		}
		d3_SelectSceneContext(mode, 1);
	}

	if (g_town_flags(town) & 8) {
		g_cur_dir = g_town_dir(town);
		tab = (int*) (town + 0x24dc);
		list = (unsigned char*) g_774a68;
		for (i = 0; i < 0x100; i++) {
			obj = (char*) *(int*) (list + i * 4);
			if (obj != 0) {
				d3_TransformPoint(obj, (float*) (obj + 0x4c), pos);
				d3sm_SampleHeight((float*) tex, pos, &bld_x, &bld_y, &height);
				tmp.x = bld_x;
				tmp.y = bld_y;
				d2_ProjectMapCoordToScreen((char*) &tmp, base_x, base_y);
				bld_x = (int) tmp.fx;
				bld_y = (int) tmp.fy;
				*tab = d2_AddElementToWindow(bld_x, bld_y, 0x54f, g_cur_dir);
				((D2_CONTROL_TL*) (g_1015ea0))[*tab].value_05c = 1;
				((D2_CONTROL_TL*) (g_1015ea0))[*tab].flags_1d0 = 0x43;
			}
			tab++;
		}
	}

	if ((int) g_7746c4) {
		handle = *(int*) ((int) g_7746c4 + 0x61);
	} else if ((int) g_7746c8) {
		handle = *(int*) ((int) g_7746c8 + 0x61);
	} else {
		if ((int) d3_ActiveCamera == 0) {
			return;
		}
		handle = 0;
	}
	if (handle == 0) {
		handle = (int) d3_ActiveCamera;
	}

	d3_TransformPoint((char*) handle, (float*) (handle + 0x4c), pos);
	d3sm_SampleHeight((float*) tex, pos, &bld_x, &bld_y, &height);
	tmp.x = bld_x;
	tmp.y = bld_y;
	d2_ProjectMapCoordToScreen((char*) &tmp, base_x, base_y);
	g_cur_dir = g_town_dir(town);
	g_cur_building = (char*) &g_1015f40[g_town_dir(town)];
	bld_x = (int) tmp.fx - *(int*) (g_cur_building + 0xc) / 2;
	bld_y = (int) tmp.fy - *(int*) (g_cur_building + 0x10) / 2;
	if (bld_x < 0) {
		bld_x = 0;
	}
	if (g_778d24 - 0x200 < bld_x) {
		bld_x = g_778d24 - 0x200;
	}
	if (bld_y < 0) {
		bld_y = 0;
	}
	if (g_778d20 - 0x168 < bld_y) {
		bld_y = g_778d20 - 0x168;
	}
	*(int*) (g_cur_building + 0x268) = bld_x;
	*(int*) (g_cur_building + 0x258) = bld_y;
	d2_UpdateWindowScroll(*(int*) g_cur_building);
}
