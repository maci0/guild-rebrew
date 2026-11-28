#include "Develop/DieGildeAddOn/game/game_data.h"
extern int g_675310, g_67530c, g_774658, g_774650, d2_SuppressOverlay, d3_CameraHorizontalIndex, d3_CameraVerticalStep;
extern unsigned int g_6a2520;
void __cdecl sv_ResetSelectionState(void); void __cdecl sv_ClearObjectSelection(void);
void __cdecl init_LoadObjektScene(int);
void __cdecl d3_SelectSceneContext(int, int);
void __cdecl d3_InitUniverse(int);
void __cdecl d3_UpdateBuildingView(void*, int);
void __cdecl d3_SetupInteriorScene(void*, void*);
void __cdecl d3_SetNodePosition(void*, void*);
void __cdecl d3_SetObjectRotation(void*, void*);
void __cdecl d2_ClearStatusTextSlots(void);
void* __cdecl evt_FindScriptById(int);
void __cdecl evt_RequestScriptExit(void*);
void __cdecl evt_WaitForScriptExit(int);
void __cdecl d3_DeinitUniverse(int);
void* __cdecl fcn_00502cd0(int, int, int, int, int);
void __cdecl d2_RunDefaultBuildingInterior(void*);
void __cdecl d2_RunFriedhofKapelleMenu(void*);
void __cdecl d2_RunUpgradeTechTreeHud(void*);
void __cdecl d2_RunWorkshopBookHud(void*);
void __cdecl d2_RunWacheInteriorHud(void*);
void __cdecl d2_RunMineInteriorHud(void*);
void __cdecl d2_RunGildeInfoHud(void*);
void __cdecl d2_RunFriedhofInteriorHud(void*);
void __cdecl d2_RunFriedhofSeanceMenu(void*);
void __cdecl d2_RunContactMenu(void*);
void __cdecl d2_RunFortuneTellerHud(void*);
void __cdecl d2_RunTheaterInteriorHud(void*);

/* Saves the current render/scene state, notifies the game of the incoming
 * message id, dispatches it to its handler and then restores the state. */
/* ADDRESS: GOLDTL 0x005a86a0 */
void __cdecl d2_EnterObjektInterior(void* objMessage)
{
	void* message;
	int save10;
	int save[7];
	char v1;
	char* saved688;
	void* t;
	int sub;

	message = objMessage;
	sub = -1;
	save10 = *(int*) &d3_CurrentContextIndex;
	*(void**) &sv_SelectedBuilding = message;
	*(int*) &evt_ActiveContextId = *(int*) ((char*) message + 2);
	g_675310 = *(int*) ((char*) message + 2);
	g_774658 = g_774650 + 1;
	save[0] = *(int*) &d3_SavedCameraPos;
	save[1] = *(int*) &d3_SavedCameraPosY;
	save[2] = *(int*) &d3_SavedCameraPosZ;
	g_6a2520 = 0;
	save[4] = *(int*) &d3_CameraTargetRotation;
	save[5] = *(int*) &d3_CameraTargetRotY;
	save[6] = *(int*) &d3_CameraTargetRotZ;
	sv_ResetSelectionState();
	sv_ClearObjectSelection();
	v1 = *(char*) (*(unsigned short*) message + (unsigned long)&init_SceneContextIndices);
	if (v1 != (char) 0xfe) {
		if (v1 == (char) 0xff || *(char*) ((int) v1 * 0x3dc + 0x1043695) != 0) {
			d2_SuppressOverlay = 1;
			init_LoadObjektScene(*(unsigned short*) message);
			d2_SuppressOverlay = 0;
		}
		*(unsigned short*) (*(int*) &d2_InteriorBuilding + 0x29) = *(unsigned short*)message;
		d3_SelectSceneContext(*(char*) (*(unsigned short*)message + (unsigned long)&init_SceneContextIndices), 0);
		d3_InitUniverse(3);
		d3_UpdateBuildingView(*(void**) &d2_InteriorBuilding, *(unsigned short*)message);
		d3_SetupInteriorScene(*(void**) &d2_InteriorBuilding, message);
		if (*(void**) &d3_ActiveScene != 0) {
			t = *(void**) ((char*) *(void**) &d3_ActiveScene + 0x3c8);
			if (t != 0 && *(void**) ((char*) t + 0x210) != 0) {
				((void (__cdecl*) (void*, int, void*, void*)) *(void**) ((char*) t + 0x210))
					(*(void**) &d3_ActiveScene, 4, (char*) t + 0x214, 0);
			}
		}
		sub = *(int*) &evt_LastGfxScriptId;
		d3_SetNodePosition(*(void**) &d3_ActiveCamera, (char*) *(void**) &d3_ActiveCamera + 0x5c);
		d3_SetObjectRotation(*(void**) &d3_ActiveCamera, (char*) *(void**) &d3_ActiveCamera + 0x90);
		saved688 = (char*)d3_CameraHorizontalIndex;
		*(int*) &d3_SavedCameraPos = *(int*) ((char*) *(void**) &d3_ActiveCamera + 0x4c);
		*(int*) &d3_SavedCameraPosY = *(int*) ((char*) *(void**) &d3_ActiveCamera + 0x50);
		*(int*) &d3_SavedCameraPosZ = *(int*) ((char*) *(void**) &d3_ActiveCamera + 0x54);
		*(int*) &d3_CameraTargetRotation = *(int*) ((char*) *(void**) &d3_ActiveCamera + 0x84);
		*(int*) &d3_CameraTargetRotY = *(int*) ((char*) *(void**) &d3_ActiveCamera + 0x88);
		*(int*) &d3_CameraTargetRotZ = *(int*) ((char*) *(void**) &d3_ActiveCamera + 0x8c);
		objMessage = *(void**)&d3_CameraVerticalStep;
		*(void**)&d3_CameraHorizontalIndex = 0;
		*(void**)&d3_CameraVerticalStep = 0;
	} else {
		saved688 = objMessage;
	}
	*(char*) &d3snd_AmbientEnabled = 0;
	switch (*(unsigned short*)message) {
	case 0x205:
		d2_RunFriedhofKapelleMenu(*(void**) &d2_InteriorBuilding);
		break;
	case 0x2c:
	case 0x109:
		d2_RunUpgradeTechTreeHud(*(void**) &d2_InteriorBuilding);
		break;
	case 0x2d:
		d2_RunWorkshopBookHud(*(void**) &d2_InteriorBuilding);
		break;
	case 0x33:
		d2_RunWacheInteriorHud(*(void**) &d2_InteriorBuilding);
		break;
	case 0x37:
		d2_RunMineInteriorHud(*(void**) &d2_InteriorBuilding);
		break;
	case 0x107:
		d2_RunGildeInfoHud(*(void**) &d2_InteriorBuilding);
		break;
	case 0x211:
		d2_RunFriedhofInteriorHud(*(void**) &d2_InteriorBuilding);
		break;
	case 0x21b:
		d2_RunFriedhofSeanceMenu(*(void**) &d2_InteriorBuilding);
		break;
	case 0x276:
		d2_RunContactMenu(*(void**) &d2_InteriorBuilding);
		break;
	case 0x27f:
		d2_RunTheaterInteriorHud(*(void**) &d2_InteriorBuilding);
		break;
	case 0x28a:
		d2_RunFortuneTellerHud(*(void**) &d2_InteriorBuilding);
		break;
	default:
		d2_RunDefaultBuildingInterior(message);
		break;
	}
	*(char*) &d3snd_AmbientEnabled = 1;
	sv_ResetSelectionState();
	sv_ClearObjectSelection();
	d2_ClearStatusTextSlots();
	*(void**) &d2_SelectedPerson = 0;
	if (sub != -1) {
		t = evt_FindScriptById(sub);
		if (t != 0) {
			evt_RequestScriptExit(t);
			evt_WaitForScriptExit(*(int*) ((char*) t + 0x100));
		}
	}
	if (*(void**) &d3_ActiveScene != 0) {
		t = *(void**) ((char*) *(void**) &d3_ActiveScene + 0x3c8);
		if (t != 0 && *(void**) ((char*) t + 0x294) != 0) {
			((void (__cdecl*) (void*, int, void*, void*)) *(void**) ((char*) t + 0x294))
				(*(void**) &d3_ActiveScene, 5, (char*) t + 0x298, 0);
		}
	}
	if (*(int*) &evt_LastGfxScriptId != -1) {
		evt_WaitForScriptExit(*(int*) &evt_LastGfxScriptId);
	}
	d3_DeinitUniverse(3);
	d3_SelectSceneContext(save10, 0);
	*(void**) &sv_SelectedBuilding = 0;
	*(unsigned short*) (*(int*) &d2_InteriorBuilding + 0x29) = 0xfd;
	*(int*) &evt_ActiveContextId = 0;
	g_67530c = *(int*) (*(int*) &d2_InteriorBuilding + 1);
	save10 = *(int*) (*(int*) &d2_InteriorBuilding + 0x5d);
	g_675310 = *(int*) ((char*) fcn_00502cd0(save10, 2, 6, 0, 0xfd) + 2);
	g_774658 = g_774650;
	*(void**)&d3_CameraVerticalStep = objMessage;
	*(int*) &d3_SavedCameraPos = save[0];
	*(int*) &d3_SavedCameraPosY = save[1];
	*(int*) &d3_SavedCameraPosZ = save[2];
	*(void**)&d3_CameraHorizontalIndex = saved688;
	*(int*) &d3_CameraTargetRotation = save[4];
	*(int*) &d3_CameraTargetRotY = save[5];
	*(int*) &d3_CameraTargetRotZ = save[6];
}
