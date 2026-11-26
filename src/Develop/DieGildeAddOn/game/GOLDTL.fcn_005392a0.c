#include "client_types.h"
extern pos14_7f4c00 gm_GameTime;
extern unsigned short g_7f4c04;
extern int g_7f4c06;



int sprintf(char*, const char*, ...);
void __cdecl d3_SelectSceneContext(int, int);
void __cdecl fcn_00442e30(void);
void __cdecl fcn_00514120(char*);
void __cdecl ls_SaveGame(char*, char*, int);
void __cdecl gm_KillAllSpieler(void);
void __cdecl gm_ResetAllEntities(void);
void __cdecl gm_CleanupObjectEntities(void);
void __cdecl fcn_00510930(void);
int __cdecl fcn_0051e070(void);
#include "client_scene_loader.h"

void __cdecl main_LoadCitySelectionScene(char* name, int net)
{
	char path[0x104];

	d3_SelectSceneContext(0, 0);
	fcn_00442e30();
	fcn_00514120(name);
	if (net != 0) {
		sprintf(path, "%s/%s.NET", "gamedata/cities", name);
	} else {
		sprintf(path, "%s/%s.CTY", "gamedata/cities", name);
	}
	(*(int*)&gm_GameTime) = 0;
	(*(short*)&g_7f4c04) = 6;
	g_7f4c06 = 0;
	ls_SaveGame(path, "city", 2);
	gm_KillAllSpieler();
	gm_ResetAllEntities();
	gm_CleanupObjectEntities();
	fcn_00510930();
	d3_SelectSceneContext(0, 0);
	fcn_00442e30();
	if (fcn_0051e070() == 0) {
		d3_LoadScene("scenes/*ChooseCity.ed3", 0, 0);
	} else {
		d3_LoadScene("scenes/*ChooseCity_Europa.ed3", 0, 0);
	}
}
