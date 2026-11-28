#include <stdio.h>
#include <string.h>
#include "Develop/DieGildeAddOn/game/object_prototype.h"
#include "Develop/DieGildeAddOn/game/client_timer.h"
#include "Develop/Units/d3/client_scene_loader.h"

extern int d3_CurrentContextIndex;
extern char* lpObjektePROT;
extern char gm_InWorldHud;
extern int g_774670;
extern int d2_ScreenHeight;
extern int g_1040494;
extern int main_LoopFlags;
extern char gm_ClientModeFlags;
extern char init_SceneContextIndices[];
extern char d3_Universes[];
extern void* ch_CharacterSlots[];
extern int d3_ActiveScene;
extern int d3_CurrentFloor;
extern float d3_ZeroVec4[];
extern char s_67d67c[];
extern char s_6a1c1c[];
extern char s_6a1c30[];
extern char s_68b0f4[];
extern char s_675908[];
extern char s_68b1e0[];

int __cdecl main_RunFrameLoop(void*, int);
void __cdecl d2_ReleaseOverlaySprite(char*);
void __cdecl d3_SelectSceneContext(int, int);
char __cdecl d3_LoadScene(const char*, void*, SCENE_PROGRESS);
void __cdecl gv_Free3Fields(int*);
int __cdecl d3sm_GetSceneSuperMap(char*);
void __cdecl d3sm_Rebuild(char*, int);
char __cdecl d3_TraverseSceneObjects(int, void*, int, void (__cdecl*)(void));
int __cdecl CompareVector3WithinTolerance(float*, float*, float);
char* __cdecl d3_FindSceneObject(char*, int, char*, char*);
char* __cdecl ch_SelectRandomDummy(void);
void __cdecl d3_TransformPoint(char*, float*, float*);
void __cdecl ch_SetPosition(char*, float*, int);
#include "Develop/DieGildeAddOn/game/ch_ground.h"
int __cdecl d3_FindFreeSceneContext(void);
void __cdecl ReportClientMessage(const char*);
int __cdecl d3_ResolveSceneObjectProtoId(char*);
void __cdecl d3_InitBuildingSceneAnimRates(char*);
void __cdecl d2_UpdateProgressOverlay(int, int, int);
void __cdecl gm_AdvanceGameClock(void);
char* __cdecl d2_StartScreenFade(int, int, int, int, int, int, int);

/* ADDRESS: GOLDTL 0x00510c90 */
/* ADDRESS: GOLDDE 0x004fb960 */
void __cdecl init_LoadObjektScene(int objectTypeIndex)
{
	char path[0x100];
	char buf[0x10];
	int saved;
	int progress;
	int paused;
	int type;
	int slot;
	char* name;
	char* obj;
	char* found;
	void** p;

	saved = d3_CurrentContextIndex;
	name = ((char *)&((OBJECT_PROTOTYPE *)lpObjektePROT)[objectTypeIndex]);
	progress = 0;
	paused = 0;
	if (gm_InWorldHud && g_774670 <= 0) {
		unsigned int flags;
		unsigned char* ch;

		flags = (main_LoopFlags & 0xfffffff7) | 0x100080;
		ch = (unsigned char*) d2_StartScreenFade(0, 0, g_1040494, d2_ScreenHeight, s_67d67c, 0x32, 1);
		while ((*ch & 4) == 0) {
			main_RunFrameLoop(0, flags);
		}
		d2_ReleaseOverlaySprite((char*) ch);
		progress = (int) d2_UpdateProgressOverlay;
	}
	if ((gm_ClientModeFlags & 8) && !tb_IsCallbackPaused((TIMER_CALLBACK) gm_AdvanceGameClock)) {
		tb_SetCallbackPaused((TIMER_CALLBACK) gm_AdvanceGameClock, 1);
		paused = 1;
	}
	if (init_SceneContextIndices[objectTypeIndex] == -1) {
		type = d3_FindFreeSceneContext();
		if (type == -1) {
			ReportClientMessage(s_6a1c30);
		}
		d3_SelectSceneContext(type, 0);
		sprintf(path, s_6a1c1c, name + 1);
		strupr(path);
		if (d3_LoadScene(path, 0, (SCENE_PROGRESS) progress)) {
			d3_SelectSceneContext(d3_CurrentContextIndex, 0);
			d3_TraverseSceneObjects(d3_ActiveScene, 0, 0x1e0, (void (__cdecl*)(void)) d3_ResolveSceneObjectProtoId);
			d3_TraverseSceneObjects(d3_ActiveScene, 0, 6, (void (__cdecl*)(void)) d3_InitBuildingSceneAnimRates);
			init_SceneContextIndices[objectTypeIndex] = (char) type;
			d3_SelectSceneContext(saved, 0);
		}
	} else {
		type = (signed char) init_SceneContextIndices[objectTypeIndex];
		if (d3_Universes[type * 0xf7 * 4 + 0x3d5] != 0) {
			slot = type * 0xf7;
			d3_SelectSceneContext(type, 0);
			sprintf(path, s_6a1c1c, name + 1);
			strupr(path);
			if (d3_LoadScene(path, 0, (SCENE_PROGRESS) progress)) {
				d3_SelectSceneContext(d3_CurrentContextIndex, 0);
				gv_Free3Fields((int*) *(int*) (d3_ActiveScene + 0xb0));
				*(int*) (d3_ActiveScene + 0xb0) = 0;
				d3sm_GetSceneSuperMap((char*) d3_ActiveScene);
				d3sm_Rebuild((char*) *(int*) (d3_ActiveScene + 0xb0), d3_CurrentFloor);
				d3_TraverseSceneObjects(d3_ActiveScene, 0, 0x1e0, (void (__cdecl*)(void)) d3_ResolveSceneObjectProtoId);
				d3_TraverseSceneObjects(d3_ActiveScene, 0, 6, (void (__cdecl*)(void)) d3_InitBuildingSceneAnimRates);
				p = ch_CharacterSlots;
				do {
					obj = (char*) *p;
					if (obj != 0
					    && *(int*) (obj + 0x88) == (int) (d3_Universes + slot * 4)) {
						if (CompareVector3WithinTolerance((float*) (obj + 0x38), d3_ZeroVec4, 0.5f) != 0) {
							if ((*(int*) (obj + 0x124) != 0
							     && (found = d3_FindSceneObject(0, 0x100, 0, s_68b0f4)) != 0)
							    || (found = ch_SelectRandomDummy()) != 0
							    || ((found = d3_FindSceneObject(0, 0x100, 0, s_675908)) != 0
							        || (found = d3_FindSceneObject(0, 0x100, 0, s_68b1e0)) != 0)) {
								d3_TransformPoint(found, (float*) (found + 0x4c), (float*) buf);
								ch_SetPosition(obj, (float*) buf, 1);
							}
						} else {
							ch_SetPosition(obj, (float*) (obj + 0x38), 1);
							ch_PlaceOnGround(obj, 1);
						}
					}
					p++;
				} while ((int) p < 0x14d0c20);
				d3_Universes[(signed char) init_SceneContextIndices[objectTypeIndex] * 0x3dc + 0x3d5] = 0;
				d3_SelectSceneContext(saved, 0);
			}
		}
	}
	if ((gm_ClientModeFlags & 8) && paused) {
		tb_SetCallbackPaused((TIMER_CALLBACK) gm_AdvanceGameClock, 0);
	}
}
