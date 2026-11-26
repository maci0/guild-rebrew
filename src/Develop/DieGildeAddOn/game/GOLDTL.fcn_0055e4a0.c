extern char s_6a6310[];
extern char s_6a6318[];
extern char s_6a632c[];
extern char s_6a6340[];
extern char s_6a6354[];
extern char s_6a6368[];
extern char s_68b1e0[];
extern char g_868060[];
extern int d3_CurrentContextIndex;
extern int g_774650;
extern unsigned char* g_7746c8;
extern int g_7e35c0[];
/* building prototype row (0x24d bytes); only the leading type byte is read here. */
typedef struct {
	unsigned char type;
	char pad1[0x24c];
} GebProt_55e4a0;
extern unsigned char* lpGebaeudePROT;
extern char* g_1043370[];
#include "GOLDTL.fcn_0055e4a0_gconf.h"
#include "Develop/DieGildeAddOn/game/building_prototype.h"
void* __cdecl gm_StartFilteredEntitySearch(int a, ...);
char* __cdecl gm_FindRecordById(int id);
int __cdecl d3_SelectSceneContext(int a, int b);
char __cdecl fcn_0045b990(char* map, float* out, int* x, int* y, float* z);
int __cdecl cm_RequestMoveObjekt(int a, int b, int c);
int __cdecl cm_RequestChangeBits(int a, int b, int c, int d, int e);
void __cdecl cm_RequestWalkOnPath(int who, int x, int y, int id);
void __cdecl cm_RequestChrMoveToUniverse(int a, int b, int c, char* name);
void __cdecl cm_SendCancelCharacterActions(unsigned int h);
int __cdecl ch_StartMovement(int who, int key, int target, int name, int mode, char* text);
int __cdecl fcn_004c5620(int state, void* ev);
int __cdecl gm_IsWarehouse(unsigned char* rec);
int __cdecl init_AllocateGebaeudeSceneSlot(unsigned char* rec);
void __cdecl io_FormatTextBuffer(char* text, int format, ...);
int __cdecl ch_IsEntityNearBuildingDoor(char* a, unsigned char* b);
char* __cdecl he_PickRandomSceneObject(char* o);
void __cdecl fcn_0055d6e0(char* a, char* b);
int __cdecl he_MessageBoxQuickjump(int id, int arg, char* text1, unsigned char flags,
	int value, int x, int y, char* name, char* text2);

/* ADDRESS: GOLDTL 0x0055e4a0 */
void __cdecl he_StepTransportEntry(char* ev)
{
	char buf[1024];
	char key[260];
	float position[4];
	char v10[4];
	int n7;
	unsigned int cellY;
	unsigned int cellX;
	char* v6;
	char* v7;
	unsigned char* v8;
	char* e;
	char* p;
	unsigned int v4;
	BUILDING_PROTOTYPE * prot;
	char* idx;

	v6 = (char*) gm_StartFilteredEntitySearch(1, 0, 0x44);
	gm_StartFilteredEntitySearch(1, 0, 0x45);
	v7 = (char*) gm_StartFilteredEntitySearch(1, 1, *(unsigned int*) (ev + 0xb0));
	v8 = (unsigned char*) gm_StartFilteredEntitySearch(1, 1, *(unsigned int*) (ev + 0xb4));
	v4 = d3_CurrentContextIndex;
	e = gm_FindRecordById(*(int*) (ev + 0xac));
	if (!e) {
		return;
	}
	fcn_0055d6e0(ev, e);
	if (!*(char*) (ev + 0xd0)) {
		cm_SendCancelCharacterActions(*(unsigned int*) (e + 2));
		ch_StartMovement(*(unsigned int*) (e + 2), *(unsigned int*) (v8 + 1),
			0xffffffff, 0, 1, s_6a6310);
		*(unsigned int*) (ev + 0xec) = cm_RequestMoveObjekt(*(int*) (v6 + 1),
			*(int*) (v7 + 1), *(int*) (e + 2));
		*(char*) (ev + 0xd0) = 1;
	}
	else if (ch_IsEntityNearBuildingDoor(e, v8)) {
		*(unsigned int*) (ev + 0xec) = cm_RequestMoveObjekt(*(int*) (v8 + 1),
			*(int*) (v6 + 1), *(int*) (e + 2));
		cm_RequestChrMoveToUniverse(*(int*) (e + 2), *(int*) (v8 + 1), 0xffffffff, s_68b1e0);
		n7 = init_AllocateGebaeudeSceneSlot(v8);
		d3_SelectSceneContext(n7, 1);
		if (he_PickRandomSceneObject(0)) {
			idx = g_1043370[n7 * 247];
			if (idx != 0 && fcn_0045b990(idx, position, (int*) &cellX, (int*) &cellY, (float*) v10)) {
				cm_RequestWalkOnPath(*(int*) (e + 2), cellX, cellY, n7);
			}
		}
		cm_RequestChangeBits(*(int*) (e + 2), 0x13, 1, 0, 0x40);
		if (*(char*) v8 == 0x47) {
			io_FormatTextBuffer(buf, 0x1c3b, 1, 0x1c39,
				*(int*) (v8 + 0x65) * 0x2f4 + (int) g_868060);
			if ((*(int*) ((char*) g_7e35c0 + g_774650 * 8) != 0x5ba910
				|| g_7746c8 != v8) && !(*(unsigned char*) (e + 0x20) & 1)
				&& !*(char*) (ev + 0xf2)) {
				he_MessageBoxQuickjump(
					*(int*) ((char*) g_slot_table + 4
						+ *(unsigned short*) (ev + 8) * 0x21c),
					*(int*) (e + 2), buf, 0, 0x609, *(int*) (v8 + 1), -1, 0,
					s_6a6368);
			}
		}
		else if (*v7 == 0x47) {
			io_FormatTextBuffer(buf, 0x1c3d, 1, 0x1c39,
				*(int*) (v7 + 0x65) * 0x2f4 + (int) g_868060,
				*(unsigned short*) (v8 + 0x27), v8);
			if ((*(int*) ((char*) g_7e35c0 + g_774650 * 8) != 0x5ba910
				|| g_7746c8 != v8) && !(*(unsigned char*) (e + 0x20) & 1)
				&& !*(char*) (ev + 0xf2)) {
				he_MessageBoxQuickjump(
					*(int*) ((char*) g_slot_table + 4
						+ *(unsigned short*) (ev + 8) * 0x21c),
					*(int*) (e + 2), buf, 0, 0x609, *(int*) (v8 + 1), -1, 0,
					s_6a6354);
			}
		}
		else {
			prot = &((BUILDING_PROTOTYPE *) lpGebaeudePROT)[*(unsigned char*) v8];
			if (*(char*) v8 == 0x1e) {
				*(unsigned int*) (key + 0) = *(unsigned int*) (s_6a6340 + 0);
				*(unsigned int*) (key + 4) = *(unsigned int*) (s_6a6340 + 4);
				*(unsigned int*) (key + 8) = *(unsigned int*) (s_6a6340 + 8);
				*(unsigned int*) (key + 12) = *(unsigned int*) (s_6a6340 + 12);
				*(unsigned short*) (key + 16) = *(unsigned short*) (s_6a6340 + 16);
				key[18] = s_6a6340[18];
			}
			else if (*(char*) v8 == 0x1f) {
				*(unsigned int*) (key + 0) = *(unsigned int*) (s_6a632c + 0);
				*(unsigned int*) (key + 4) = *(unsigned int*) (s_6a632c + 4);
				*(unsigned int*) (key + 8) = *(unsigned int*) (s_6a632c + 8);
				*(unsigned int*) (key + 12) = *(unsigned int*) (s_6a632c + 12);
				*(unsigned short*) (key + 16) = *(unsigned short*) (s_6a632c + 16);
				key[18] = s_6a632c[18];
			}
			else if (*(char*) v8 == 0x20) {
				*(unsigned int*) (key + 0) = *(unsigned int*) (s_6a6318 + 0);
				*(unsigned int*) (key + 4) = *(unsigned int*) (s_6a6318 + 4);
				*(unsigned int*) (key + 8) = *(unsigned int*) (s_6a6318 + 8);
				*(unsigned int*) (key + 12) = *(unsigned int*) (s_6a6318 + 12);
				*(unsigned short*) (key + 16) = *(unsigned short*) (s_6a6318 + 16);
				key[18] = s_6a6318[18];
			}
			else {
				key[0] = 0;
			}
			if (prot->category != 0x1d && prot->category != 0x1f) {
				io_FormatTextBuffer(buf, 0x1c3f, 1, 0x1c39,
					*(unsigned short*) (v8 + 0x27), v8);
			}
			else if (gm_IsWarehouse(v8)) {
				io_FormatTextBuffer(buf, 0x1c43);
			}
			else {
				io_FormatTextBuffer(buf, 0x1c44, v8);
			}
			if ((*(int*) ((char*) g_7e35c0 + g_774650 * 8) != 0x5ba910
				|| g_7746c8 != v8) && !(*(unsigned char*) (e + 0x20) & 1)
				&& !*(char*) (ev + 0xf2)) {
				if (key[0]) {
					he_MessageBoxQuickjump(
						*(int*) ((char*) g_slot_table + 4
							+ *(unsigned short*) (ev + 8) * 0x21c),
						*(int*) (e + 2), buf, 0, 0x609, *(int*) (v8 + 1),
						-1, 0, key);
				}
				else {
					he_MessageBoxQuickjump(
						*(int*) ((char*) g_slot_table + 4
							+ *(unsigned short*) (ev + 8) * 0x21c),
						*(int*) (e + 2), buf, 0, 0x609, *(int*) (v8 + 1),
						-1, 0, 0);
				}
			}
		}
		*(unsigned int*) (ev + 0x84) = fcn_004c5620(3, ev);
	}
	else if (*(char*) (ev + 0xd0) && *(int*) (ev + 0xd4) > 0x10
		&& (p = *(char**) (e + 0x3b)) != 0 && *(int*) (p + 0x128) == 0) {
		ch_StartMovement(*(unsigned int*) (e + 2), *(unsigned int*) (v8 + 1),
			0xffffffff, 0, 1, s_6a6310);
		*(int*) (ev + 0xd4) = 0;
	}
	d3_SelectSceneContext(v4, 1);
}
