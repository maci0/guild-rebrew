#include "Develop/DieGildeAddOn/game/spiel.h"
#include "Develop/DieGildeAddOn/game/building_prototype.h"


#include <string.h>
#pragma intrinsic(strcpy, strcat)

// SIZE 0x21c
typedef struct {
	char pad0[0x1b1];
	unsigned char f1b1;
	char pad1b2[0x6a];
} House5a74;

extern char gm_EntitySlotTable[];
extern unsigned char* lpGebaeudePROT;
#include "Develop/DieGildeAddOn/game/game_player.h"
extern unsigned char gm_ClientModeFlags;
extern char* g_14ad474;
extern unsigned short gm_GameTimeHour;
extern int d2_InsideBuildingActive;


int __cdecl gm_GetEntityUiFlags(int id, unsigned char* store, int a, int b);
int __cdecl gm_IsGebaeudeOpen(unsigned char* p, int* lo, int* hi);
void __cdecl io_FormatTextBuffer(void*, int, ...);
void __cdecl d2_ShowGreenMessageBox(char*, char*, int);

int __cdecl gm_CanEnterGebaeude(unsigned char* p)
{
	int a;
	int b;
	char line[0x80];
	char title[0x80];
	char text[0x400];
	unsigned char* tbl;
	int kind;
	int r;
	int x;
	unsigned short own;

	tbl = (unsigned char*)&((BUILDING_PROTOTYPE*)lpGebaeudePROT)[p[0]];
	kind = gm_GetBuildingTypeCategory(p[0]);
	r = gm_GetEntityUiFlags(gm_LocalPlayerSlot, p, 0, 0);
	if ((*(unsigned short*) (p + 0x5a) & 0x400) != 0) {
		return 0;
	}
	if (((*(signed char*)&gm_ClientModeFlags) & 0x80) == 0) {
		x = ((House5a74*)gm_EntitySlotTable)[gm_LocalPlayerSlot].f1b1;
		if (!(x > 0 && ((((BUILDING_PROTOTYPE*)tbl)->category) == 6 || (((BUILDING_PROTOTYPE*)tbl)->category) == 4)) && (r & 0x200) == 0) {
			own = *(unsigned short*) (p + 0x27);
			if (own != gm_LocalPlayerSlot) {
				if ((r & 1) == 0) {
					return 0;
				}
				if (gm_IsGebaeudeOpen(p, (int*) &a, &b) == 0) {
					strcpy(title, g_14ad474);
					x = a;
					if (((*(int*)&gm_GameTimeHour) & 0xffff) < x) {
						if (kind == 3 || kind == 5) {
							io_FormatTextBuffer(text, 0x2059, p);
						}
						else {
							io_FormatTextBuffer(text, 0x2056, own, p);
						}
					}
					else {
						if (kind == 3 || kind == 5) {
							io_FormatTextBuffer(text, 0x205a, p);
						}
						else {
							io_FormatTextBuffer(text, 0x2057, own, p);
						}
					}
					io_FormatTextBuffer(line, 0x2058, x, b);
					strcat(text, line);
					d2_InsideBuildingActive = 0;
					d2_ShowGreenMessageBox(title, text, 4);
					return 0;
				}
			}
		}
	}
	return 1;
}
