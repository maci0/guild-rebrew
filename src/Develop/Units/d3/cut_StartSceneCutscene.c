extern int cut_SkipMode;
extern int d3_CurrentFloor;
extern char g_77666a;
extern int* cut_ActiveCutscene;
extern int d2_ScreenSurface;
#include "Develop/client_types.h"
extern pos14_7f4c00 gm_GameTime;
extern int g_772f4c;
extern int evt_ActiveContextId;
extern int d3_ActiveScene;
extern int evt_LastGfxScriptId;
extern int g_68bfc4;
extern unsigned char* g_772f50;
extern int d2_ScreenHeight;
extern int g_1040494;
extern char g_67d67c[];

typedef void(__cdecl* CutsceneUiCallback)(char*, int, char*, int);

int __cdecl d3_FindFreeSceneContext(void);
void __cdecl d3_SelectSceneContext(int, int);
int __cdecl fcn_0064d41a(char*, char*, ...);
#include "Develop/Units/d3/client_scene_loader.h"
void __cdecl d3_SetFloorDetailLevel(char*, int, int);
void __cdecl d2_ClearSurface(int);
int __cdecl gm_GetSeason(int*);
void __cdecl d3_ApplySceneLightingPreset(void);
#include "Develop/Units/d3/d3_d3d.h"
void __cdecl d2_ReleaseOverlaySprite(int);
void __cdecl d2_StartScreenFade(int, int, int, int, char*, int, int);


/* ADDRESS: GOLDTL 0x004e4730 */
void __cdecl cut_StartSceneCutscene(char* sceneName)
{
	char buf[0x80];
	char* ui;
	int n;

	if (cut_SkipMode != 0)
		return;
	{
		int s;

		s = d3_FindFreeSceneContext();
		d3_SelectSceneContext(s, 0);
		fcn_0064d41a(buf, "scenes/*%s", sceneName);
		d3_LoadScene(buf, 0, 0);
		d3_SelectSceneContext(0, 1);
		d3_SelectSceneContext(s, 0);
	}
	if (((char*)d3_CurrentFloor) != 0) {
		if (g_77666a == 0) {
			n = 2;
			((char*)d3_CurrentFloor)[0x8036] = (((char*)d3_CurrentFloor)[0x8036] & 0xeb) | 8;
		} else {
			n = 1;
			((char*)d3_CurrentFloor)[0x8036] = (((char*)d3_CurrentFloor)[0x8036] & 0xe7) | 4;
		}
		d3_SetFloorDetailLevel(((char*)d3_CurrentFloor), n >> 1, 1);
	}
	if ((((char*)cut_ActiveCutscene)[0x26] & 0x20) != 0)
		d2_ClearSurface(d2_ScreenSurface);
	if (gm_GetSeason(&(*(int*)&gm_GameTime)) == 3)
		d3_ApplySceneLightingPreset();
	evt_ActiveContextId = -2;
	g_772f4c++;
	if (((char*)d3_ActiveScene) != 0) {
		ui = *(char**) (((char*)d3_ActiveScene) + 0x3c8);
		if (ui != 0 && *(CutsceneUiCallback*) (ui + 0x210) != 0)
			(*(CutsceneUiCallback*) (ui + 0x210))(((char*)d3_ActiveScene), 4, ui + 0x214, 0);
	}
	g_68bfc4 = evt_LastGfxScriptId;
	d3_PrecacheAllSceneTextures(1);
	if ((*(int*)&g_772f50) != 0) {
		d2_ReleaseOverlaySprite((*(int*)&g_772f50));
		(*(int*)&g_772f50) = 0;
	}
	d2_StartScreenFade(0, 0, g_1040494, d2_ScreenHeight, "BLACK", 0x5a, 0xa);
}
