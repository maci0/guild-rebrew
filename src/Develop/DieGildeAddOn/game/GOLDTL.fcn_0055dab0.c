#include <string.h>
#include "Develop/DieGildeAddOn/game/building_prototype.h"
typedef struct Level {
	unsigned char kind;
	char pad1[0x24c];
} Level;
/* SIZE 0x24d */

typedef struct Slot21c {
	char pad0[2];
	unsigned char kind;
	char pad3;
	int id;
	char pad8[0x214];
} Slot21c;
/* SIZE 0x21c */

typedef struct Handler {
	void(__cdecl* fn)(void*, int);
	int arg;
} Handler;
/* SIZE 8 */

extern unsigned char* lpGebaeudePROT;
extern char g_868060[];
extern Slot21c g_7f4ca0[];
extern int g_7e35c0[][2];
extern int g_774650;
extern char* g_7746c8;
extern int d3_CurrentContextIndex;

char* __cdecl gm_StartFilteredEntitySearch(int, int, int);
char* __cdecl gm_FindRecordById(int);
void __cdecl fcn_0055d6e0(char*, char*);
void __cdecl cm_SendCancelCharacterActions(int);
void __cdecl ch_StartMovement(int, int, int, int, int, char*);
int __cdecl cm_RequestMoveObjekt(int, int, int);
int __cdecl gm_IsWarehouse(char*);
void __cdecl fcn_004c5d20(int, int);
int __cdecl ch_IsEntityNearBuildingDoor(char*, char*);
void __cdecl io_FormatTextBuffer(char*, int, ...);
void __cdecl he_MessageBoxQuickjump(int, int, char*, int, int, int, int, int, char*);
int __cdecl fcn_004c5620(int, char*);
void __cdecl d3_SelectSceneContext(int, int);
void __cdecl fcn_005ba910(void*, int);

/* ADDRESS: GOLDTL 0x0055dab0 */
void __cdecl he_StepTransportCarrier(char* e)
{
	char* s44;
	char* b;
	char* c;
	char* r;
	BUILDING_PROTOTYPE* lv;
	int saved;
	int code;
	char text[0x104];
	char msg[0x400];

	s44 = gm_StartFilteredEntitySearch(1, 0, 0x44);
	gm_StartFilteredEntitySearch(1, 0, 0x45);
	b = gm_StartFilteredEntitySearch(1, 1, *(int*) (e + 0xb0));
	c = gm_StartFilteredEntitySearch(1, 1, *(int*) (e + 0xb4));
	saved = d3_CurrentContextIndex;
	r = gm_FindRecordById(*(int*) (e + 0xac));
	if (r == 0) {
		return;
	}
	fcn_0055d6e0(e, r);
	if (e[0xd0] == 0) {
		cm_SendCancelCharacterActions(*(int*) (r + 2));
		if (!gm_IsWarehouse(b)) {
			fcn_004c5d20(*(int*) (r + 2), 1);
		}
		ch_StartMovement(*(int*) (r + 2), *(int*) (c + 1), -1, 0, 0, "Trans");
		if (!gm_IsWarehouse(b)) {
			*(int*) (e + 0xec) = cm_RequestMoveObjekt(*(int*) (s44 + 1), *(int*) (b + 1), *(int*) (r + 2));
		}
		e[0xd0] = 1;
	} else if (ch_IsEntityNearBuildingDoor(r, c)) {
		*(int*) (e + 0xec) = cm_RequestMoveObjekt(*(int*) (c + 1), *(int*) (s44 + 1), *(int*) (r + 2));
		if (*(unsigned char*) c == 0x47) {
			io_FormatTextBuffer(msg, 0x1c3b, 1, 0x1c39, g_868060 + *(int*) (c + 0x65) * 0x2f4);
			if ((g_7e35c0[g_774650][0] != 0x5ba910 || g_7746c8 != c) &&
			    !(r[0x20] & 1) && e[0xf2] == 0) {
				he_MessageBoxQuickjump(g_7f4ca0[*(unsigned short*) (e + 8)].id, *(int*) (r + 2), msg, 0,
				    0x609, *(int*) (c + 1), -1, 0, "_NACHRICHTEN_HS_60");
			}
		} else if (*(unsigned char*) b == 0x47) {
			io_FormatTextBuffer(msg, 0x1c3d, 1, 0x1c39, g_868060 + *(int*) (b + 0x65) * 0x2f4,
			    *(unsigned short*) (c + 0x27), c);
			if ((g_7e35c0[g_774650][0] != 0x5ba910 || g_7746c8 != c) &&
			    !(r[0x20] & 1) && e[0xf2] == 0) {
				he_MessageBoxQuickjump(g_7f4ca0[*(unsigned short*) (e + 8)].id, *(int*) (r + 2), msg, 0,
				    0x609, *(int*) (c + 1), -1, 0, "_NACHRICHTEN_HS_59");
			}
		} else {
			lv = &((BUILDING_PROTOTYPE*)lpGebaeudePROT)[*(unsigned char*) c];
			code = 0x609;
			if (*(unsigned char*) c == 0x1e) {
				memcpy(text, "_NACHRICHTEN_HS_58", 0x13);
			} else if (*(unsigned char*) c == 0x1f) {
				memcpy(text, "_NACHRICHTEN_HS_57", 0x13);
			} else if (*(unsigned char*) c == 0x20) {
				memcpy(text, "_NACHRICHTEN_HS_56", 0x13);
			} else {
				text[0] = 0;
			}
			if (lv->category != 0x1d && lv->category != 0x1f) {
				io_FormatTextBuffer(msg, 0x1c3f, 1, 0x1c39, *(unsigned short*) (c + 0x27), c);
			} else {
				code = 0x608;
				if (gm_IsWarehouse(c)) {
					io_FormatTextBuffer(msg, 0x1c43);
				} else {
					io_FormatTextBuffer(msg, 0x1c44, c);
				}
			}
			if ((g_7e35c0[g_774650][0] != 0x5ba910 || g_7746c8 != c) &&
			    !(r[0x20] & 1) && e[0xf2] == 0) {
				if (text[0] != 0) {
					he_MessageBoxQuickjump(g_7f4ca0[*(unsigned short*) (e + 8)].id, *(int*) (r + 2),
					    msg, 0, code, *(int*) (c + 1), -1, 0, text);
				} else {
					he_MessageBoxQuickjump(g_7f4ca0[*(unsigned short*) (e + 8)].id, *(int*) (r + 2),
					    msg, 0, code, *(int*) (c + 1), -1, 0, 0);
				}
			}
		}
		*(int*) (e + 0x84) = fcn_004c5620(3, e);
	}
	d3_SelectSceneContext(saved, 1);
}
