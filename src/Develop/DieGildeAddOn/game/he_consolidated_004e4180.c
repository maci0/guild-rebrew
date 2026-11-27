void __cdecl msx_StartMusicIfAllowed(char*);
int __cdecl gm_ResolveEntityById(void** dynamic, void** existing, void** static_ptr, int entity_id);
void __cdecl fcn_004e4230(void*, int);
void __cdecl fcn_004e4730(char*);
void __cdecl cut_WaitTicks(int);
void __cdecl cm_RequestCopyEntityData(int, int, int, int);
void __cdecl cut_FadeToBlack(void);
void __cdecl cut_CleanupCutscene(void);
void __cdecl msx_RestoreMusicIfAllowed(void);
#include "Develop/DieGildeAddOn/game/building_prototype.h"
#include "Develop/DieGildeAddOn/game/event_callbacks.h"
extern int g_772f3c;
extern unsigned char* g_7746c4;
extern unsigned char* g_7746c8;
extern int* cut_ActiveCutscene;
extern int g_77250c;
extern unsigned char* g_772f50;
extern unsigned char* lpGebaeudePROT;
extern int g_6b8058;
extern int g_772f48;
extern char init_SceneContextIndices[];
extern signed char g_7f3b00[];
extern char g_1043695[];
extern int d2_ScreenHeight;
extern int g_1040494;
extern char g_67d67c[];

int __cdecl fcn_00476970(int);
void __cdecl fcn_00473150(unsigned char*);
void __cdecl fcn_004730c0(int, int, int, int, char*, int, int);
int __cdecl fcn_00502cd0(int, int, int, int);
int __cdecl fcn_00505370(unsigned char*);
void __cdecl init_LoadGebaeudeScene(int);
void __cdecl fcn_00510c90(int);
void __cdecl d3_SelectSceneContext(int, int);
void __cdecl d3_UpdateBuildingView(unsigned char*, unsigned int);
void __cdecl fcn_0043aa30(char);

/* ADDRESS: GOLDTL 0x004e4180 */
void __cdecl fcn_004e4180(char* event)
{
	int* m;
	void* dyn;
	int fallback;
	int i;

	m = (int*) event;
	fallback = 0;
	msx_StartMusicIfAllowed(0);
	gm_ResolveEntityById(&dyn, 0, 0, m[5]);
	if (dyn != 0) {
		fcn_004e4230(dyn, 0x17);
	} else {
		fallback = 1;
		fcn_004e4730("ob_SALON.ed3");
	}
	cut_WaitTicks(5);
	for (i = 0; i < 4; i++) {
		if (m[14 + i] != -1) {
			cm_RequestCopyEntityData(m[13], m[14 + i], 0xa, 1);
			cm_RequestCopyEntityData(m[14 + i], m[13], 0xa, 1);
		}
	}
	if (fallback) {
		cut_FadeToBlack();
		cut_CleanupCutscene();
	}
	msx_RestoreMusicIfAllowed();
}

/* ADDRESS: GOLDTL 0x004e4230 */
void __cdecl fcn_004e4230(unsigned char* entity, unsigned int sceneId)
{
	int flags;

	if (g_772f3c) {
		return;
	}
	if ((g_7746c4 == entity && *(unsigned short*) (entity + 0x29) == sceneId) ||
	    (g_7746c8 == entity && *(unsigned short*) (entity + 0x29) == sceneId)) {
		if (*((unsigned char*) cut_ActiveCutscene + 0x26) & 0x20) {
			fcn_00476970(g_77250c);
		}
		if (g_772f50) {
			fcn_00473150(g_772f50);
			g_772f50 = 0;
			fcn_004730c0(0, 0, g_1040494, d2_ScreenHeight, g_67d67c, 0x5a, 0xa);
		}
	}
	else {
		if (fcn_00502cd0(*(int*) (entity + 0x5d), 1, 0, sceneId)) {
			if (!fcn_00505370(entity)) {
				if (init_SceneContextIndices[sceneId] != -2) {
					if (init_SceneContextIndices[sceneId] == -1 ||
					    g_1043695[init_SceneContextIndices[sceneId] * 0x3dc]) {
						fcn_00510c90(sceneId);
					}
					d3_SelectSceneContext(init_SceneContextIndices[sceneId], 0);
					d3_UpdateBuildingView(entity, sceneId);
				}
			}
			else {
				if (g_7f3b00[((BUILDING_PROTOTYPE*)lpGebaeudePROT)[*entity].category]) {
					if (g_7f3b00[((BUILDING_PROTOTYPE*)lpGebaeudePROT)[*entity].category] == -1 ||
					    g_1043695[g_7f3b00[((BUILDING_PROTOTYPE*)lpGebaeudePROT)[*entity].category] * 0x3dc]) {
						init_LoadGebaeudeScene(((BUILDING_PROTOTYPE*)lpGebaeudePROT)[*entity].category);
					}
					d3_SelectSceneContext(g_7f3b00[((BUILDING_PROTOTYPE*)lpGebaeudePROT)[*entity].category], 0);
					d3_UpdateBuildingView(entity, 0xfd);
				}
			}
		}
		flags = g_6b8058;
		if (flags) {
			g_772f48 = flags;
			fcn_0043aa30(flags & 0xfd);
			g_772f48 &= 0xfffffffd;
		}
		if (*((unsigned char*) cut_ActiveCutscene + 0x26) & 0x20) {
			fcn_00476970(g_77250c);
		}
		if (g_772f50) {
			fcn_00473150(g_772f50);
			g_772f50 = 0;
			fcn_004730c0(0, 0, g_1040494, d2_ScreenHeight, g_67d67c, 0x5a, 0xa);
		}
	}
}
