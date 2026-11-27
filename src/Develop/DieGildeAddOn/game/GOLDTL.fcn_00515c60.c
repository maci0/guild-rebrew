#include "Develop/DieGildeAddOn/game/building_prototype.h"
#include "game_data.h"
extern int g_699b10;
extern void* g_6b7fdc;
extern char g_6790c8[];
#include "Develop/DieGildeAddOn/game/game_data.h"
#include "Develop/DieGildeAddOn/game/object_prototype.h"
int __cdecl fcn_0050dc90(void*);
int __cdecl gm_CheckEntityType(void*);
int __cdecl fcn_0064d41a(char*, char*, ...);
int __cdecl vfs_LookupPath(char*, int, char*);
int __cdecl evt_LoadScript(char*);
int __cdecl evt_FindScriptById(int);
void __cdecl evt_RequestScriptExit(int);
void __cdecl fcn_00428340(int, int, int, int);
/* ADDRESS: GOLDTL 0x00515c60 */
void __cdecl evt_StartShopIntroScript(unsigned char* building, unsigned char* visitor)
{
	int zv[2];
	char v7[48];
	char path[260];
	int v9;
	int v8;
	int v3;
	int* p;
	int r;

	zv[0] = 0;
	v9 = 0;
	v8 = 0;
	v3 = fcn_0050dc90(building);
	p = (int*) ch_ContextCharacters;
loop:
	if (v9) {
		goto found;
	}
	v8 = *p;
	if (v8 && v8 == v3) {
		v9 = v8;
	}
	p++;
	if ((int) p < (int) (ch_ContextCharacters + 32)) {
		goto loop;
	}
	if (!v9) {
		return;
	}
found:
	if (*(unsigned char*) (v9 + 8) <= 1) {
		return;
	}
	if (visitor && *(int*) (*(int*) (v9 + 0x184) + 0x30) != *(int*) (visitor + 2)) {
		return;
	}
	if (gm_CheckEntityType(building)) {
		v3 = (int) &((BUILDING_PROTOTYPE*)lpGebaeudePROT)[*building];
		goto fmt;
	}
	else {
		v3 = (int) ((char *)&((OBJECT_PROTOTYPE *)lpObjektePROT)[*(unsigned short*) visitor]);
		if (!v3) {
			v3 = zv[0];
fmt:
			v3++;
			fcn_0064d41a(path, (char*) 0x6a1f54, g_6790c8, v3, v3);
		}
		else {
			v3++;
			fcn_0064d41a(path, (char*) 0x6a1f54, g_6790c8, v3, v3);
		}
	}
	r = vfs_LookupPath(path, (int) g_6b7fdc, (char*) &zv[1]);
	if (!r) {
		return;
	}
	fcn_0064d41a(v7, g_68b0d8, *(int*) (v8 + 4));
	r = evt_LoadScript(path);
	if (r) {
		v3 = *(int*) (*(int*) (v8 + 0x184) + 0x28);
		if (v3 != -1) {
			v3 = evt_FindScriptById(v3);
			if (v3) {
				evt_RequestScriptExit(v3);
			}
		}
		fcn_00428340(r, 2, *(int*) (v8 + 0x184), 0x4c3800);
		*(int*) (r + 0xc94) = *(int*) (v8 + 0x184);
		*(int*) (*(int*) (v8 + 0x184) + 0x28) = *(int*) (r + 0x100);
		g_699b10 = *(int*) (r + 0x100);
	}
	else {
		g_699b10 = -1;
	}
}
