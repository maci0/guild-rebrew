typedef void (__cdecl* Cb5a80d0a)(int a0, int a1, int a2, int a3);
typedef void (__cdecl* Cb5a80d0b)(int a0, int a1, int a2, int a3);

int __cdecl gm_CanEnterGebaeude(unsigned char* a0);
void __cdecl sv_ResetSelectionState(void);
void __cdecl sv_ClearObjectSelection(void);
int __cdecl init_AllocateGebaeudeSceneSlot(unsigned char* a0);
void __cdecl sb_LoadBuildingVoiceBanks(unsigned char* b);
int __cdecl main_RunFrameLoop(int a0, int a1);
void __cdecl init_LoadGebaeudeScene(int a0);
int __cdecl gm_QueryEntities(int a0, int a1, int a2, int a3, int a4);
int __cdecl d3_SelectSceneContext(int a0, int a1);
void __cdecl d3_InitUniverse(int a0);
void __cdecl d3_UpdateBuildingView(unsigned char* a0, int a1);
void __cdecl d3_SetupInteriorScene(int a0, unsigned char* a1);
int __cdecl gm_GetBuildingTypeCategory(int a0);
void __cdecl d3_SetNodePosition(char* p, int* v);
void __cdecl d3_SetObjectRotation(int a0, int a1);
int __cdecl CompareVector3WithinTolerance(float* a, float* b, float eps);
void __cdecl d2_RunDefaultBuildingInterior(int a0);
void* __cdecl evt_FindScriptById(int a1);
void __cdecl evt_RequestScriptExit(void* p);
void __cdecl evt_WaitForScriptExit(int a0);
void __cdecl d3snd_FreeObjectSoundBanks(void);
void __cdecl d3_CleanupBuildingScene(int a0);
void __cdecl d3_DeinitUniverse(int a0);
void __cdecl d3_ResetWorldSceneState(void);
void __cdecl d2_RunSchmiedeInteriorHud(int a0);
void __cdecl d2_RunHolzfaellerInteriorHud(int a0);
void __cdecl d3_HideSubtreeEntries(int a0);
void __cdecl d2_RunSteinbruchInteriorHud(int a0);
void __cdecl d2_RunRaeuberInteriorHud(int a0);
void __cdecl d2_RunKontorTradeHud(int a0);
void __cdecl d2_RunFriedhofActions(int a0);
void __cdecl d2_RunZigeunerInteriorHud(int a0);
#include "Develop/DieGildeAddOn/game/game_data.h"
extern int g_774658, d3_CameraHorizontalIndex, d3_CameraVerticalStep, d2_SuppressOverlay, g_67530c, g_675310;
/* ADDRESS: GOLDTL 0x005a80d0 */
/* ADDRESS: GOLDDE 0x0058cdd0 */
void __cdecl d2_EnterGebaeudeInterior(unsigned char* building)
{
	unsigned char* buildingPtr;
	int n;
	int id;
	int w;
	int rec;
	int v10;
	int v11;
	int s0;
	int s1;
	int s2;
	int s3;
	int s4;
	int s5;
	unsigned char* p;
	int c;

	buildingPtr = building;
	id = -1;
	n = gm_CanEnterGebaeude(building);
	if (n == 0) {
		*(int*) &d2_InsideBuildingActive = 0;
		return;
	}
	g_774658 = g_774650 + 1;
	building = (unsigned char*) *(int*) &d3_CurrentContextIndex;
	*(int*) 0x6a2520 = 0;
	sv_ResetSelectionState();
	sv_ClearObjectSelection();
	s0 = *(int*) &d3_SavedCameraPos;
	s1 = *(int*) &d3_SavedCameraPosY;
	s2 = *(int*) &d3_SavedCameraPosZ;
	s3 = *(int*) &d3_CameraTargetRotation;
	s4 = *(int*) &d3_CameraTargetRotY;
	s5 = *(int*) &d3_CameraTargetRotZ;
	*(int*) 0x6752a8 = *(int*) 0x6aada0;
	*(int*) 0x6752ac = *(int*) 0x6aada4;
	*(unsigned char*) 0x6752b0 = *(unsigned char*) 0x6aada8;
	n = init_AllocateGebaeudeSceneSlot(buildingPtr);
	w = n * 0x3dc;
	*(int*) (w + 0x1043378) = *(int*) 0x1043378;
	if (n != 0) {
		sb_LoadBuildingVoiceBanks(buildingPtr);
		if (n == -1 || *(char*) (w + 0x1043695) != 0) {
			d2_SuppressOverlay = 1;
			main_RunFrameLoop(0, 0x603c7);
			main_RunFrameLoop(0, 0x603c7);
			init_LoadGebaeudeScene(*buildingPtr);
			d2_SuppressOverlay = 0;
		}
		*(int*) &d2_InteriorBuilding = (int) buildingPtr;
		*(int*) &evt_ActiveContextId = *(int*) (buildingPtr + 1);
		g_67530c = *(int*) (buildingPtr + 1);
		p = (unsigned char*) gm_QueryEntities(*(int*) (buildingPtr + 0x5d), 2, 6, 0, 0xfd);
		if (p == 0) {
			p = (unsigned char*) gm_QueryEntities(*(int*) (buildingPtr + 0x5d), 2, 6, 4, 2);
		}
		g_675310 = *(int*) (p + 2);
		d3_SelectSceneContext(n, 0);
		d3_InitUniverse(3);
		if (*(int*) &d3_CurrentFloor != 0) {
			if (*(unsigned char*) 0x77666a == 2) {
				*(unsigned char*) (*(int*) &d3_CurrentFloor + 0x8036) = (*(unsigned char*) (*(int*) &d3_CurrentFloor + 0x8036) & 0xe7) | 4;
			} else {
				*(unsigned char*) (*(int*) &d3_CurrentFloor + 0x8036) = (*(unsigned char*) (*(int*) &d3_CurrentFloor + 0x8036) & 0xeb) | 8;
			}
		}
		d3_UpdateBuildingView((unsigned char*) *(int*) &d2_InteriorBuilding, *(unsigned short*) p);
		d3_SetupInteriorScene(*(int*) &d2_InteriorBuilding, p);
		if (*(int*) &d3_ActiveScene != 0) {
			v10 = *(int*) (*(int*) &d3_ActiveScene + 0x3c8);
			if (v10 != 0 && *(int*) (v10 + 0x210) != 0) {
				(*(Cb5a80d0a*) (v10 + 0x210))(*(int*) &d3_ActiveScene, 4, v10 + 0x214, 0);
			}
		}
		id = *(int*) &evt_LastGfxScriptId;
		if (*(unsigned short*) (buildingPtr + 0x27) == *(unsigned short*) &gm_LocalPlayerSlot) {
			d3_SetNodePosition((char*) *(int*) &d3_ActiveCamera, (int*) (*(int*) &d3_ActiveCamera + 0x5c));
			v10 = *(int*) &d3_ActiveCamera + 0x90;
			v11 = *(int*) &d3_ActiveCamera;
			d3_SetObjectRotation(v11, v10);
		} else {
			v10 = gm_GetBuildingTypeCategory(*buildingPtr);
			c = *buildingPtr;
			rec = *(int*) &lpGebaeudePROT + c + c * 0x24c;
			if (v10 != 2) {
				if (*(char*) rec == 0x1c) {
					d3_SetNodePosition((char*) *(int*) &d3_ActiveCamera, (int*) (*(int*) &d3_ActiveCamera + 0x5c));
					v10 = *(int*) &d3_ActiveCamera + 0x90;
					d3_SetObjectRotation(*(int*) &d3_ActiveCamera, v10);
				} else if (CompareVector3WithinTolerance((float*) (*(int*) &d3_ActiveCamera + 0x114), (float*) &d3_ZeroVec4, 0.1f) == 0
				           && CompareVector3WithinTolerance((float*) (*(int*) &d3_ActiveCamera + 0x120), (float*) &d3_ZeroVec4, 0.1f) == 0) {
					d3_SetNodePosition((char*) *(int*) &d3_ActiveCamera, (int*) (*(int*) &d3_ActiveCamera + 0x114));
					v10 = *(int*) &d3_ActiveCamera + 0x120;
					d3_SetObjectRotation(*(int*) &d3_ActiveCamera, v10);
				}
			} else if (CompareVector3WithinTolerance((float*) (*(int*) &d3_ActiveCamera + 0x114), (float*) &d3_ZeroVec4, 0.1f) == 0
			           && CompareVector3WithinTolerance((float*) (*(int*) &d3_ActiveCamera + 0x120), (float*) &d3_ZeroVec4, 0.1f) == 0) {
				d3_SetNodePosition((char*) *(int*) &d3_ActiveCamera, (int*) (*(int*) &d3_ActiveCamera + 0x114));
				v10 = *(int*) &d3_ActiveCamera + 0x120;
				d3_SetObjectRotation(*(int*) &d3_ActiveCamera, v10);
			}
		}
		*(int*) &d3_SavedCameraPos = *(int*) (*(int*) &d3_ActiveCamera + 0x4c);
		*(int*) &d3_SavedCameraPosY = *(int*) (*(int*) &d3_ActiveCamera + 0x50);
		*(int*) &d3_SavedCameraPosZ = *(int*) (*(int*) &d3_ActiveCamera + 0x54);
		*(int*) &d3_CameraTargetRotation = *(int*) (*(int*) &d3_ActiveCamera + 0x84);
		*(int*) &d3_CameraTargetRotY = *(int*) (*(int*) &d3_ActiveCamera + 0x88);
		*(int*) &d3_CameraTargetRotZ = *(int*) (*(int*) &d3_ActiveCamera + 0x8c);
		d3_CameraHorizontalIndex = 0;
		d3_CameraVerticalStep = 0;
	}
	switch (*buildingPtr) {
	case 0x1e:
		d2_RunHolzfaellerInteriorHud(*(int*) &d2_InteriorBuilding);
		d3_HideSubtreeEntries(*(int*) (buildingPtr + 0x71));
		break;
	case 0x1f:
		d2_RunSteinbruchInteriorHud(*(int*) &d2_InteriorBuilding);
		break;
	case 0x20:
		d2_RunSchmiedeInteriorHud(*(int*) &d2_InteriorBuilding);
		break;
	case 0x27:
		d2_RunRaeuberInteriorHud(*(int*) &d2_InteriorBuilding);
		break;
	case 0x47:
		d2_RunKontorTradeHud(*(int*) &d2_InteriorBuilding);
		break;
	case 0x48:
	case 0x49:
	case 0x4a:
		d2_RunFriedhofActions(*(int*) &d2_InteriorBuilding);
		break;
	case 0x4e:
	case 0x4f:
	case 0x50:
		d2_RunZigeunerInteriorHud(*(int*) &d2_InteriorBuilding);
		break;
	default:
		d2_RunDefaultBuildingInterior(0);
		break;
	}
	if (n != -1) {
		*(int*) (w + 0x1043378) = 0;
		*(int*) 0x6b89c0 = 0;
	}
	sv_ResetSelectionState();
	sv_ClearObjectSelection();
	d3_CameraHorizontalIndex = 0;
	d3_CameraVerticalStep = 0;
	if (id != -1) {
		p = (unsigned char*) evt_FindScriptById(id);
		if (p != 0) {
			evt_RequestScriptExit(p);
			evt_WaitForScriptExit(*(int*) (p + 0x100));
		}
	}
	if (*(int*) &d3_ActiveScene != 0) {
		n = *(int*) (*(int*) &d3_ActiveScene + 0x3c8);
		if (n != 0 && *(int*) (n + 0x294) != 0) {
			(*(Cb5a80d0b*) (n + 0x294))(*(int*) &d3_ActiveScene, 5, n + 0x298, 0);
		}
	}
	if (*(int*) &evt_LastGfxScriptId != -1) {
		evt_WaitForScriptExit(*(int*) &evt_LastGfxScriptId);
	}
	d3snd_FreeObjectSoundBanks();
	d3_CleanupBuildingScene(*(int*) &d2_InteriorBuilding);
	d3_DeinitUniverse(3);
	d3_SelectSceneContext((int) building, 0);
	*(int*) &d2_SelectedPerson = 0;
	*(int*) &d2_InteriorBuilding = 0;
	*(int*) &evt_ActiveContextId = 0;
	g_67530c = -1;
	g_675310 = -1;
	d3_ResetWorldSceneState();
	*(int*) &d3_SavedCameraPos = s0;
	*(int*) &d3_SavedCameraPosY = s1;
	*(int*) &d3_SavedCameraPosZ = s2;
	*(int*) &d3_CameraTargetRotation = s3;
	*(int*) &d3_CameraTargetRotY = s4;
	*(int*) &d3_CameraTargetRotZ = s5;
}
