#include <math.h>
#include <string.h>
#include "Develop/DieGildeAddOn/game/building_prototype.h"
#include "Develop/DieGildeAddOn/game/entity_record.h"
extern unsigned char* lpGebaeudePROT;
typedef struct { unsigned char kind; unsigned char unknown01[0x24c]; } Building560290;
extern float g_696540[];
extern float g_696550[];
extern double g_6629c8;
extern double g_662908;
extern int gm_GameTime;
extern int g_7f4c04;
extern unsigned char g_773d75;

int __cdecl gm_GetSeason(int*);
void __cdecl gm_AddTime(int, int, int, int);
void* __cdecl gm_StartFilteredEntitySearch(int, int, int);
void __cdecl d3_TransformPoint(int, int, float*);
void* __cdecl gm_FindNextFilteredEntity(void);
int __cdecl gm_LookupEntityRecordById(int);
void __cdecl cm_SendCancelCharacterActions(int);
void __cdecl ch_StartMovement(int, int, int, int, int, char*);
int __cdecl gm_IsEntityAtBuilding(int, int);
void __cdecl fcn_00529160(int, int, int, int);
int __cdecl fcn_00502cd0(int, int, ...);
int __cdecl gm_GetBuildingTechEffect(unsigned char*, int, int);
int __cdecl gm_RandomMod(unsigned short);
int __cdecl gm_eval_SlotVoll(char*, int, int);
char* __cdecl fcn_0050dc90(unsigned char*);
int __cdecl cm_SendSellObjekt(int, int, int, int, unsigned char, int);
void __cdecl io_FormatTextBuffer(char*, int, ...);
void __cdecl he_MessageBoxQuickjump(int, int, char*, int, int, int, int, int, char*);
void __cdecl he_FreeAction(char*);

/* One step of the building placement state machine: validate the current
 * cell, pick the nearest matching entity or neighbour, place the icon and
 * advance the state. */
/* ADDRESS: GOLDTL 0x00560290 */
void __cdecl fcn_00560290(char* a0)
{
	char name[512];
	char text[1024];
	int win;
	int value;
	char* nearest;
	int rec;
	int i;
	int t;
	char* e;

	win = gm_GetSeason(&gm_GameTime);
	value = g_7f4c04 & 0xffff;
	nearest = 0;
	if ((g_696550[win] <= (float) value || (float) value < g_696540[win]) && *(int*) (a0 + 0x70) != -1 && *(int*) (a0 + 0x70) != -2) {
		gm_AddTime((int) (a0 + 0x52), 0, 5, 0);
		return;
	}
	if (*(unsigned short*) (a0 + 8) != 0xffff && *(int*) (a0 + 0xc) != -1) {
		switch (*(int*) (a0 + 0x70)) {
		case 1: {
			float here[4];
			float nextp[4];
			float best;
			float dx;
			float dy;
			float dz;
			float dist;

			e = (char*) gm_StartFilteredEntitySearch(1, 1, *(unsigned int*) (a0 + 0x10));
			if (!e) {
				goto nearest_failed;
			}
			best = 1.0e8f;
			d3_TransformPoint(*(int*) (e + 0x61), *(int*) (e + 0x61) + 0x4c, here);
			e = (char*) gm_StartFilteredEntitySearch(1, 5, 0xb);
			if (!e) {
				goto nearest_failed;
			}
			do {
				d3_TransformPoint(*(int*) (e + 0x61), *(int*) (e + 0x61) + 0x4c, nextp);
				dx = nextp[0] - here[0];
				dy = nextp[1] - here[1];
				dz = nextp[2] - here[2];
				dist = (float) sqrt(dz * dz + dy * dy + dx * dx);
				if (dist < best) {
					best = dist;
					nearest = e;
				}
				e = (char*) gm_FindNextFilteredEntity();
			} while (e);
			if (!nearest) {
				nearest_failed:
				*(int*) (a0 + 0x70) = -1;
				return;
			}
			*(int*) (a0 + 0xb4) = *(int*) (nearest + 1);
			for (i = 0; i < *(unsigned char*) (a0 + 0xac); i++) {
				if (gm_LookupEntityRecordById(((int*) (a0 + 0x8c))[i])) {
					cm_SendCancelCharacterActions(((int*) (a0 + 0x8c))[i]);
					ch_StartMovement(((int*) (a0 + 0x8c))[i], *(int*) (nearest + 1), -1, 0, 0, (char*) 0x6a6508);
				}
			}
			*(int*) (a0 + 0x70) = *(int*) (a0 + 0x70) + 1;
			return;
		}
		case 2: {
			unsigned char* v9;

			v9 = (unsigned char*) gm_StartFilteredEntitySearch(1, 1, *(unsigned int*) (a0 + 0xb4));
			if (!v9) {
				*(int*) (a0 + 0x70) = -1;
				return;
			}
			for (i = 0; i < *(unsigned char*) (a0 + 0xac); i++) {
				rec = gm_LookupEntityRecordById(((int*) (a0 + 0x8c))[i]);
				if (rec && !gm_IsEntityAtBuilding(rec, (int) v9)) {
					*(int*) (a0 + 0x70) = 2;
					gm_AddTime((int) (a0 + 0x52), 0, 5, 0);
					return;
				}
			}
			*(int*) (a0 + 0x70) = 3;
			gm_AddTime((int) (a0 + 0x52), 0, 10, 0);
			return;
		}
		case 3: {
			int found;

			found = 0;
			e = (char*) gm_StartFilteredEntitySearch(1, 1, *(unsigned int*) (a0 + 0x10));
			if (!e) {
				*(int*) (a0 + 0x70) = -1;
				return;
			}
			for (i = 0; i < *(unsigned char*) (a0 + 0xac); i++) {
				if (gm_LookupEntityRecordById(((int*) (a0 + 0x8c))[i])) {
					found |= 1;
					cm_SendCancelCharacterActions(((int*) (a0 + 0x8c))[i]);
					ch_StartMovement(((int*) (a0 + 0x8c))[i], *(int*) (e + 1), *(int*) (a0 + 0xb0), 0, 0, (char*) 0x6a6508);
				}
			}
			if (found) {
				*(int*) (a0 + 0x70) = 4;
				gm_AddTime((int) (a0 + 0x52), 0, 5, 0);
				return;
			}
			break;
		}
		case 4: {
			double scale;
			char* q;
			unsigned char* v9;
			unsigned short* id;

			v9 = (unsigned char*) gm_StartFilteredEntitySearch(1, 1, *(unsigned int*) (a0 + 0x10));
			if (!v9) {
				break;
			}
			for (i = 0; i < *(unsigned char*) (a0 + 0xac); i++) {
				rec = gm_LookupEntityRecordById(((int*) (a0 + 0x8c))[i]);
				if (rec && !gm_IsEntityAtBuilding(rec, (int) v9)) {
					*(int*) (a0 + 0x70) = 4;
					gm_AddTime((int) (a0 + 0x52), 0, 5, 0);
					return;
				}
			}
			for (i = 0; i < *(unsigned char*) (a0 + 0xac); i++) {
				id = (unsigned short*) gm_LookupEntityRecordById(((int*) (a0 + 0x8c))[i]);
				if (id) {
					fcn_00529160(0, 0, *id, 0);
				}
			}
			q = (char*) fcn_00502cd0(*(int*) (v9 + 0x5d), 2, 6, 0, 0x2a);
			if (!q) {
				break;
			}
			win = gm_GetSeason(&gm_GameTime);
			if (((BUILDING_PROTOTYPE *)lpGebaeudePROT)[*v9].category == 0x20) {
				scale = (double) gm_GetBuildingTechEffect(v9, 0x1e, 1) * *(double*) 0x665eb0 + 1.0;
				t = gm_RandomMod(6) & 0xffff;
				t = (int) ((double) ((t + 9) * *(unsigned char*) (a0 + 0xac)) * scale);
			} else {
				scale = (double) gm_GetBuildingTechEffect(v9, 0xb, 1) * *(double*) 0x665eb0 + 1.0;
				t = gm_RandomMod(6) & 0xffff;
				t = (int) ((double) ((t + 9) * *(unsigned char*) (a0 + 0xac)) * scale);
			}
			if (win == 3 && !(*(v9 + 0x5b) & 0x20)) {
				t = (int) ((double) t * 0.5);
			}
			rec = gm_eval_SlotVoll(q, *(unsigned short*) (a0 + 0xae), t);
			if (!*(unsigned short*) (a0 + 0xae)) {
				break;
			}
			id = (unsigned short*) fcn_0050dc90(v9);
			if (rec) {
				cm_SendSellObjekt(*(int*) (q + 2), -1, *(unsigned short*) (a0 + 0xae), rec, g_773d75, 0);
				io_FormatTextBuffer(text, 0x1802, 0x17fd, v9);
				io_FormatTextBuffer(name, 0x1803, rec, *(unsigned short*) (a0 + 0xae) * 2 + 0x9a8);
				strcat(text, name);
			} else {
				io_FormatTextBuffer(text, 0x1804, 0x17fd, v9);
			}
			if ((((ENTITY_RECORD*) g_7f4ca0)[*(unsigned short*) (a0 + 8)].entity_state == 6
					|| ((ENTITY_RECORD*) g_7f4ca0)[*(unsigned short*) (a0 + 8)].entity_state == 7)
				&& (!id || !(*(unsigned char*) ((int) id + 0x1b4) & 1))) {
				he_MessageBoxQuickjump(((ENTITY_RECORD*) g_7f4ca0)[*(unsigned short*) (a0 + 8)].entity_id, -1, text, 0, 0x5ec,
					*(int*) (v9 + 1), *(int*) (a0 + 0xb0), 0, 0);
			}
			break;
		}
		case -2:
		case -1:
			e = (char*) gm_StartFilteredEntitySearch(1, 1, *(unsigned int*) (a0 + 0x10));
			if (!e) {
				break;
			}
			for (i = 0; i < *(unsigned char*) (a0 + 0xac); i++) {
				if (gm_LookupEntityRecordById(((int*) (a0 + 0x8c))[i])) {
					cm_SendCancelCharacterActions(((int*) (a0 + 0x8c))[i]);
					ch_StartMovement(((int*) (a0 + 0x8c))[i], *(int*) (e + 1), *(int*) (a0 + 0xb0), 0, 0, (char*) 0x6a6508);
				}
			}
			break;
		default:
			return;
		}
	}
	he_FreeAction(a0);
}
