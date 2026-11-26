#include <string.h>

#include "Develop/DieGildeAddOn/game/game_data.h"
extern int main_LoopFlags;
extern char* g_7e2704;
extern char* g_7e2708;
extern char g_7e2714[];
extern char* lpGebaeudePROT;

/* SIZE 0x24d: building prototype row of lpGebaeudePROT */
typedef struct {
	unsigned char type;
	char rest[0x24c];
} BldProt_526920;
#include "Develop/DieGildeAddOn/game/game_player.h"
extern char* g_7746c4;
extern char* g_7746c8;
extern char* g_7746cc;
#include "client_dialog_state.h"
extern char g_7f4e51[];
extern char g_7f4ca4[];
extern char g_1043690[];

char* __cdecl fcn_00502cd0(int a0, int a1, int a2, int a3);
int __cdecl gm_CheckEntityType(void* p);
int __cdecl gm_IsWarehouse(void* p);
int __cdecl init_EnsureObjektSceneContext(void* p);
void __cdecl init_LoadObjektScene(int id);
void __cdecl main_ExitToFrameHandler(void* p);

/* ADDRESS: GOLDTL 0x00526920 */
void __cdecl fcn_00526920(char* buildingRecord, int a1, char* a2)
{
	char* hit;
	char* old;
	int saved;
	BldProt_526920* row;
	int n;

	hit = 0;
	if (g_7e2700 != 0) {
		return;
	}
	if ((main_LoopFlags & 0x10000) != 0) {
		return;
	}
	if (g_774970 != 0xffff && g_7f4e51[(int) g_774970 * 540] != 0) {
		row = &((BldProt_526920*) lpGebaeudePROT)[(unsigned char) *buildingRecord];
		if (row->type != 6 && (row->type != 4 || *(int*) (buildingRecord + 0x65) != *(int*) (g_7f4ca4 + (int) g_774970 * 540))) {
			return;
		}
	}
	if (g_7746c4 != 0) {
		hit = g_7746c4;
	} else if (g_7746c8 != 0) {
		hit = g_7746c8;
	}
	g_7e2704 = buildingRecord;
	g_7e2708 = fcn_00502cd0(*(int*) (buildingRecord + 0x5d), 1, 1, a1);
	if (*buildingRecord == 0x47) {
		g_7e2708 = fcn_00502cd0(*(int*) (buildingRecord + 0x5d), 1, 0, 0xfd);
	}
	strcpy(g_7e2714, a2);
	g_7e2700 = 1;
	if (g_7e2708 != 0 && *(unsigned short*) g_7e2708 != 0) {
		if (g_7e2708 != g_7746cc) {
			if (buildingRecord == hit) {
				if (gm_CheckEntityType(hit) != 0) {
					*(unsigned short*) (buildingRecord + 0x29) = *(unsigned short*) g_7e2708;
					if (g_7746cc != 0) {
						g_774654 = g_774650 - g_774658 + 1;
						return;
					}
					g_774654 = g_774650 - g_774658;
					return;
				}
			}
			*(unsigned short*) (buildingRecord + 0x29) = *(unsigned short*) g_7e2708;
			old = g_7746cc;
			saved = g_774670;
			if (gm_CheckEntityType(buildingRecord) == 0 && gm_IsWarehouse(buildingRecord) == 0) {
				g_7746cc = g_7e2708;
				g_7e2700 = 0;
				g_774670 = 0;
				n = init_EnsureObjektSceneContext(g_7e2708);
				if (g_1043690[n * 988 + 5] != 0) {
					init_LoadObjektScene(*(unsigned short*) g_7e2708);
				}
				g_7746cc = old;
				g_7e2700 = 1;
				g_774670 = saved;
			}
			main_ExitToFrameHandler((void*) 0x59a340);
			return;
		}
		if (g_774650 > g_774658) {
			g_774654 = g_774650 - g_774658;
			return;
		}
		g_7e2700 = 0;
		return;
	}
	if (hit == buildingRecord && g_7746c8 == 0) {
		g_7e2700 = 0;
		return;
	}
	main_ExitToFrameHandler((void*) 0x59a340);
}
unsigned char _dpad_7e2708[88];
