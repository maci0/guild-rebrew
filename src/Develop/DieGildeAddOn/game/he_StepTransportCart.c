
// Transport event step: on the first call starts the transport (flag
// +0xd0); afterwards, once the carrier arrived (within 100 units of +0xd8)
// or +0xd4 ran past 6, files the arrival message and schedules the next
// step (+0x84).

typedef struct Level {
	unsigned char kind;
	char pad1[0x24c];
} Level;
// SIZE 0x24d

typedef struct Slot21c {
	char pad0[2];
	unsigned char kind;
	char pad3;
	int id;
	char pad8[0x214];
} Slot21c;
// SIZE 0x21c

typedef struct Handler {
	void(__cdecl* fn)(void*, int);
	int arg;
} Handler;
// SIZE 8

extern unsigned char* lpGebaeudePROT;
extern int d3_CurrentContextIndex;
extern Slot21c gm_EntitySlotTable[];
extern int main_FrameHandlerStack[];
extern int g_774650;
extern char* d2_VisitedBuilding;
extern unsigned short* sv_SelectedBuilding;

char* __cdecl gm_StartFilteredEntitySearch(int, ...);
char* __cdecl gm_FindRecordById(int);
void __cdecl he_ApplyTransportSpeedModifiers(char* e, char* r);
void __cdecl cm_SendCancelCharacterActions(int);
void __cdecl ch_StartMovement(int, int, int, int, int, char*);
int __cdecl cm_RequestMoveObjekt(int, int, int);
#include "Develop/Units/d3/client_scene_transform.h"
int __cdecl gm_IsWarehouse(char*);
void __cdecl cm_SendCreateAction0x38(int, int);
int __cdecl cm_RequestChangeBits(int, int, int, int, int);
void __cdecl io_FormatTextBuffer(char*, int, ...);
char* __cdecl gm_FindBuildingPrimarySlot(char*);
void __cdecl he_MessageBoxQuickjump(int, int, char*, int, int, int, int, int, char*);
int __cdecl cm_SendSetHE(int, char*);
void __cdecl d3_SelectSceneContext(int, int);
void __cdecl d2_RunTradeInventoryPanel(void*, int);

void __cdecl he_StepTransportCart(char* e)
{
	char* s44;
	Level* lv;
	int saved;
	char buf[0x400];
	char* b;
	char* c;
	char* r;
	char* o;
	char* h;
	unsigned char k;
	unsigned short w;

	s44 = gm_StartFilteredEntitySearch(1, 0, 0x44);
	gm_StartFilteredEntitySearch(1, 0, 0x45);
	b = gm_StartFilteredEntitySearch(1, 1, *(int*) (e + 0xb0));
	lv = (Level*) (lpGebaeudePROT + *(unsigned char*) b * sizeof(Level));
	c = gm_StartFilteredEntitySearch(1, 1, *(int*) (e + 0xb4));
	saved = d3_CurrentContextIndex;
	r = gm_FindRecordById(*(int*) (e + 0xac));
	if (r == 0) {
		return;
	}
	he_ApplyTransportSpeedModifiers(e, r);
	if (e[0xd0] == 0) {
		cm_SendCancelCharacterActions(*(int*) (r + 2));
		ch_StartMovement(*(int*) (r + 2), *(int*) (c + 1), -1, 0, 1, "Trans");
		*(int*) (e + 0xec) = cm_RequestMoveObjekt(*(int*) (s44 + 1), *(int*) (b + 1), *(int*) (r + 2));
		e[0xd0] = 1;
	} else {
		o = *(char**) (r + 0x3b);
		if (o != 0 && *(int*) (o + 0x128) == 0 &&
		    ((*(int*) (o + 0x88) == 0x10432c0 && CompareVector3WithinTolerance((float*) (*(char**) (o + 0x34) + 0x4c), (float*) (e + 0xd8), 100.0f)) ||
		     *(int*) (e + 0xd4) > 6)) {
			if (!gm_IsWarehouse(c)) {
				*(int*) (e + 0xec) = cm_RequestMoveObjekt(*(int*) (c + 1), *(int*) (s44 + 1), *(int*) (r + 2));
				cm_SendCreateAction0x38(*(int*) (r + 2), 0);
			}
			cm_RequestChangeBits(*(int*) (r + 2), 0x13, 1, 0, 0x40);
			if (gm_IsWarehouse(c)) {
				io_FormatTextBuffer(buf, 0x1c43);
			} else if (lv->kind != 0x1d && lv->kind != 0x1f) {
				io_FormatTextBuffer(buf, 0x1c41, 1, 0x1c39, b, *(unsigned short*) (c + 0x27), c);
			} else if (gm_IsWarehouse(c)) {
				io_FormatTextBuffer(buf, 0x1c43);
			} else {
				io_FormatTextBuffer(buf, 0x1c44, c);
			}
			k = gm_EntitySlotTable[*(unsigned short*) (e + 8)].kind;
			if (k == 6 || k == 7) {
				if (((Handler*) main_FrameHandlerStack)[g_774650].fn == d2_RunTradeInventoryPanel) {
					if (d2_VisitedBuilding == c) {
						goto done;
					}
					if (gm_IsWarehouse(c) && sv_SelectedBuilding != 0) {
						w = *sv_SelectedBuilding;
						if ((w >= 0x92 && w <= 0x97) || w == 0x2db) {
							goto done;
						}
					}
				}
				if (!(r[0x20] & 1) && e[0xf2] == 0) {
					h = gm_FindBuildingPrimarySlot(c);
					if (h != 0) {
						he_MessageBoxQuickjump(gm_EntitySlotTable[*(unsigned short*) (e + 8)].id, *(int*) (r + 2), buf, 0, 0x608,
						             *(int*) (c + 1), *(int*) (h + 2), 0, 0);
					} else {
						he_MessageBoxQuickjump(gm_EntitySlotTable[*(unsigned short*) (e + 8)].id, *(int*) (r + 2), buf, 0, 0x608,
						             *(int*) (c + 1), -1, 0, 0);
					}
				}
			}
		done:
			*(int*) (e + 0x84) = cm_SendSetHE(3, e);
		}
	}
	d3_SelectSceneContext(saved, 1);
}
