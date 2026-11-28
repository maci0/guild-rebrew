/*
 * Kugel flight state machine, one step per frame.
 *
 * The handle at self+0xb8 resolves to a map slot; self+0x27 of that object
 * gives the slot index and 0x7f4ca0 + index * 0x21c is the map entry, unless
 * it is the current-entry pointer at 0x773da8.
 *
 * State word at self+0x70: negative unlinks the instance, 0 arms state 1,
 * 1 lets the ball start and sets the flight counters, 2 waits until both
 * counters have drained and then restarts. The two counters at self+0x14 and
 * self+0x18 weight the travel time; the ball position at self+0xb0 is summed
 * until it turns positive, and a negative socket test repeats the loop.
 */
#include "Develop/DieGildeAddOn/game/object_prototype.h"
#include "Develop/client_types.h"
#include "Develop/DieGildeAddOn/game/entity_record.h"
void __cdecl gm_ResolveEntityById(void*, void*, int, int);
void __cdecl he_AssignActionSlot(char*, int, int, int);
void __cdecl he_FreeAction(char*);
int __cdecl gm_GetBuildingTechEffect(char*, int, int);
void __cdecl cm_RequestCopyEntityData(int, int, int, int);
double __cdecl gm_CalcAvgEntityFavor(int, int, char*);
int __cdecl gm_CalcElapsedWorkMinutes(char*, char*, int);
char* __cdecl fcn_00502cd0(int, int, int, int);
void __cdecl io_FormatTextBuffer(char*, int, ...);
void __cdecl he_MessageBoxQuickjump(int, int, char*, int, int, int, int, int, char*);
int __cdecl gm_CompareGameTime(char*, char*);
void __cdecl gm_AddTime(char*, int, int, int);
void __cdecl cm_SendSellObjekt(int, int, int, int, unsigned char, int);

extern char gm_EntitySlotTable[];
extern char gm_GameTime[];
extern char* gm_CityEntity;
extern unsigned char gm_ActiveTownIndex;
extern char* lpObjektePROT;
extern double g_6629c8;
extern double g_662908;

/* ADDRESS: GOLDTL 0x00571240 */
void __cdecl he_RunAbbau(char* self)
{
	char* node;
	float total;
	float prev;
	char* o1;
	char* o2;
	char buf[0x100];
	char* map;
	char* entry;
	char* row;
	char* q;
	int i;
	int n;

	map = 0;
	gm_ResolveEntityById(&node, 0, 0, *(int*) (self + 0xb8));
	if (node == 0) {
		for (i = 0; i < 768; i++) {
			if (*(char**) (((char*)&((ENTITY_RECORD*)gm_EntitySlotTable)[i]) + 0x17c) == self)
				he_AssignActionSlot(0, 0, *(unsigned short*) (((char*)&((ENTITY_RECORD*)gm_EntitySlotTable)[i])), 0);
		}
		he_FreeAction(self);
		return;
	}
	if (*(unsigned short*) (node + 0x27) != 0xffff) {
		row = ((char*)&((ENTITY_RECORD*)gm_EntitySlotTable)[*(unsigned short*) (node + 0x27)]);
		if (row != gm_CityEntity)
			map = row;
	}
	switch (*(int*) (self + 0x70)) {
	case 0:
		*(int*) (self + 0x70) += 1;
		return;
	case 1:
		if (*(int*) (self + 0x14) == 0 && *(int*) (self + 0x18) == 0) {
			*(int*) (self + 0x70) = 2;
			return;
		}
		gm_ResolveEntityById(&node, 0, 0, *(int*) (self + 0xb8));
		total = gm_GetBuildingTechEffect(node, 1, 1) * 0.01 + g_6629c8;
		if (*(unsigned char*) (self + 0xc8) >= 0x3c) {
			for (i = 0; i < 8; i++) {
				if (map == 0)
					goto skip_map;
				if (((int*) (self + 0x8c))[i] != -1) {
					n = *(int*) (node + 0x41);
					if (n != 2)
						cm_RequestCopyEntityData(*(int*) (map + 4), ((int*) (self + 0x8c))[i], 2 - n, 0);
				}
			}
			*(float*) (self + 0xc4) = (float) ((gm_CalcAvgEntityFavor(*(unsigned short*) map, 8, self + 0x8c)
				- g_662908) * 0.25);
skip_map:
			*(unsigned char*) (self + 0xc8) = 0;
		}
		n = gm_CalcElapsedWorkMinutes(self + 0x60, gm_GameTime, 0);
		if (n > 0)
			*(unsigned char*) (self + 0xc8) += n;
		total = total + *(float*) (self + 0xc4);
		if (gm_CompareGameTime(self + 0x52, gm_GameTime) >= 0)
			return;
		do {
			entry = ((char *)&((OBJECT_PROTOTYPE *)lpObjektePROT)[*(unsigned short*) (self + 0xac)]);
			prev = (float) *(int*) (self + 0xb0);
			n = gm_CalcElapsedWorkMinutes(self + 0x60, self + 0x52, 0)
				* (*(int*) (self + 0x18) + *(int*) (self + 0x14) * 2);
			*(int*) (self + 0xb0) = (int) (prev - n * total);
			while (*(int*) (self + 0xb0) <= 0) {
				gm_ResolveEntityById(0, &o1, 0, *(int*) (self + 0xbc));
				q = fcn_00502cd0(*(int*) (o1 + 0x14), 1, 0, *(unsigned short*) (self + 0xac));
				gm_ResolveEntityById(0, &o2, 0, *(int*) (self + 0xc0));
				if (q == 0) {
					io_FormatTextBuffer(buf, 0x1bb7, *(unsigned short*) (self + 0xac) * 2 + 0x9a8, node);
					he_MessageBoxQuickjump(*(int*) (((char*)&((ENTITY_RECORD*)gm_EntitySlotTable)[*(unsigned short*) (self + 8)]) + 4),
						-1, buf, 0, 0x5f1, *(int*) (node + 1), -1, 0, "_NACHRICHTEN_HS_07");
					for (i = 0; i < 768; i++) {
						if (*(char**) (((char*)&((ENTITY_RECORD*)gm_EntitySlotTable)[i]) + 0x17c) == self)
							he_AssignActionSlot(node, 0, *(unsigned short*) (((char*)&((ENTITY_RECORD*)gm_EntitySlotTable)[i])), 0);
					}
					he_FreeAction(self);
					return;
				}
				n = ((OBJECT_PROTOTYPE *)entry)->value_036;
				if (n >= *(int*) (q + 0xe))
					n = *(int*) (q + 0xe);
				cm_SendSellObjekt(*(int*) (self + 0xc0), *(int*) (self + 0xbc), *(unsigned short*) (self + 0xac),
					n, gm_ActiveTownIndex, 0);
				*(int*) (self + 0xb0) += *(int *)&((OBJECT_PROTOTYPE *)entry)->value_022;
				*(float*) (self + 0xb4) = (float) *(int*) (self + 0xb0);
			}
			*(pos14_7f4c00*) (self + 0x60) = *(pos14_7f4c00*) (self + 0x52);
			gm_AddTime(self + 0x52, 0, 0, 5);
		} while (gm_CompareGameTime(self + 0x52, gm_GameTime) < 0);
		return;
	case 2:
		if (*(int*) (self + 0x14) > 0 || *(int*) (self + 0x18) > 0) {
			*(int*) (self + 0x70) = 1;
			return;
		}
		gm_ResolveEntityById(&node, 0, 0, *(int*) (self + 0xb8));
		if (node == 0) {
			*(int*) (self + 0x70) = -1;
			return;
		}
		for (i = 0; i < 768; i++) {
			if (*(char**) (((char*)&((ENTITY_RECORD*)gm_EntitySlotTable)[i]) + 0x17c) == self)
				he_AssignActionSlot(node, 0, *(unsigned short*) (((char*)&((ENTITY_RECORD*)gm_EntitySlotTable)[i])), 0);
		}
		he_FreeAction(self);
		return;
	case -2:
	case -1:
		for (i = 0; i < 768; i++) {
			if (*(char**) (((char*)&((ENTITY_RECORD*)gm_EntitySlotTable)[i]) + 0x17c) == self)
				he_AssignActionSlot(0, 0, *(unsigned short*) (((char*)&((ENTITY_RECORD*)gm_EntitySlotTable)[i])), 0);
		}
		he_FreeAction(self);
		return;
	}
}
