typedef void (__cdecl* Cb5a80d0a)(int a0, int a1, int a2, int a3);
typedef void (__cdecl* Cb5a80d0b)(int a0, int a1, int a2, int a3);

int __cdecl gm_CanEnterGebaeude(unsigned char* a0);
void __cdecl fcn_00530510(void);
void __cdecl sv_ClearObjectSelection(void);
int __cdecl init_AllocateGebaeudeSceneSlot(unsigned char* a0);
void __cdecl fcn_004c3170(unsigned char* b);
int __cdecl main_RunFrameLoop(int a0, int a1);
void __cdecl init_LoadGebaeudeScene(int a0);
int __cdecl fcn_00502cd0(int a0, int a1, int a2, int a3, int a4);
int __cdecl d3_SelectSceneContext(int a0, int a1);
void __cdecl fcn_0043aa30(int a0);
void __cdecl fcn_005167c0(unsigned char* a0, int a1);
void __cdecl fcn_00516c50(int a0, unsigned char* a1);
int __cdecl gm_GetBuildingTypeCategory(int a0);
void __cdecl fcn_00438b40(char* p, int* v);
void __cdecl d3_SetObjectRotation(int a0, int a1);
int __cdecl CompareVector3WithinTolerance(float* a, float* b, float eps);
void __cdecl fcn_0058f700(int a0);
void* __cdecl evt_FindScriptById(int a1);
void __cdecl evt_RequestScriptExit(void* p);
void __cdecl fcn_005312d0(int a0);
void __cdecl fcn_004c34d0(void);
void __cdecl fcn_00516ed0(int a0);
void __cdecl fcn_0043a9c0(int a0);
void __cdecl fcn_00516f60(void);
void __cdecl fcn_0059c800(int a0);
void __cdecl fcn_0059c9a0(int a0);
void __cdecl fcn_004bd1a0(int a0);
void __cdecl fcn_0059cb40(int a0);
void __cdecl fcn_0059de00(int a0);
void __cdecl fcn_0059e390(int a0);
void __cdecl d2_RunFriedhofActions(int a0);
void __cdecl fcn_005e69f0(int a0);
#include "Develop/DieGildeAddOn/game/game_data.h"
extern int g_774658, d3_CameraHorizontalIndex, d3_CameraVerticalStep, d2_SuppressOverlay, g_67530c, g_675310;
/* ADDRESS: GOLDTL 0x005a80d0 */
void __cdecl fcn_005a80d0(unsigned char* a0)
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

	buildingPtr = a0;
	id = -1;
	n = gm_CanEnterGebaeude(a0);
	if (n == 0) {
		*(int*) &g_7e2700 = 0;
		return;
	}
	g_774658 = g_774650 + 1;
	a0 = (unsigned char*) *(int*) &d3_CurrentContextIndex;
	*(int*) 0x6a2520 = 0;
	fcn_00530510();
	sv_ClearObjectSelection();
	s0 = *(int*) &g_7e3a40;
	s1 = *(int*) &g_7e3a44;
	s2 = *(int*) &g_7e3a48;
	s3 = *(int*) &d3_CameraTargetRotation;
	s4 = *(int*) &g_7e3a54;
	s5 = *(int*) &g_7e3a58;
	*(int*) 0x6752a8 = *(int*) 0x6aada0;
	*(int*) 0x6752ac = *(int*) 0x6aada4;
	*(unsigned char*) 0x6752b0 = *(unsigned char*) 0x6aada8;
	n = init_AllocateGebaeudeSceneSlot(buildingPtr);
	w = n * 0x3dc;
	*(int*) (w + 0x1043378) = *(int*) 0x1043378;
	if (n != 0) {
		fcn_004c3170(buildingPtr);
		if (n == -1 || *(char*) (w + 0x1043695) != 0) {
			d2_SuppressOverlay = 1;
			main_RunFrameLoop(0, 0x603c7);
			main_RunFrameLoop(0, 0x603c7);
			init_LoadGebaeudeScene(*buildingPtr);
			d2_SuppressOverlay = 0;
		}
		*(int*) &g_7746c8 = (int) buildingPtr;
		*(int*) &g_6791c8 = *(int*) (buildingPtr + 1);
		g_67530c = *(int*) (buildingPtr + 1);
		p = (unsigned char*) fcn_00502cd0(*(int*) (buildingPtr + 0x5d), 2, 6, 0, 0xfd);
		if (p == 0) {
			p = (unsigned char*) fcn_00502cd0(*(int*) (buildingPtr + 0x5d), 2, 6, 4, 2);
		}
		g_675310 = *(int*) (p + 2);
		d3_SelectSceneContext(n, 0);
		fcn_0043aa30(3);
		if (*(int*) &g_6b8300 != 0) {
			if (*(unsigned char*) 0x77666a == 2) {
				*(unsigned char*) (*(int*) &g_6b8300 + 0x8036) = (*(unsigned char*) (*(int*) &g_6b8300 + 0x8036) & 0xe7) | 4;
			} else {
				*(unsigned char*) (*(int*) &g_6b8300 + 0x8036) = (*(unsigned char*) (*(int*) &g_6b8300 + 0x8036) & 0xeb) | 8;
			}
		}
		fcn_005167c0((unsigned char*) *(int*) &g_7746c8, *(unsigned short*) p);
		fcn_00516c50(*(int*) &g_7746c8, p);
		if (*(int*) &g_67a370 != 0) {
			v10 = *(int*) (*(int*) &g_67a370 + 0x3c8);
			if (v10 != 0 && *(int*) (v10 + 0x210) != 0) {
				(*(Cb5a80d0a*) (v10 + 0x210))(*(int*) &g_67a370, 4, v10 + 0x214, 0);
			}
		}
		id = *(int*) &evt_LastGfxScriptId;
		if (*(unsigned short*) (buildingPtr + 0x27) == *(unsigned short*) &g_774970) {
			fcn_00438b40((char*) *(int*) &d3_ActiveCamera, (int*) (*(int*) &d3_ActiveCamera + 0x5c));
			v10 = *(int*) &d3_ActiveCamera + 0x90;
			v11 = *(int*) &d3_ActiveCamera;
			d3_SetObjectRotation(v11, v10);
		} else {
			v10 = gm_GetBuildingTypeCategory(*buildingPtr);
			c = *buildingPtr;
			rec = *(int*) &lpGebaeudePROT + c + c * 0x24c;
			if (v10 != 2) {
				if (*(char*) rec == 0x1c) {
					fcn_00438b40((char*) *(int*) &d3_ActiveCamera, (int*) (*(int*) &d3_ActiveCamera + 0x5c));
					v10 = *(int*) &d3_ActiveCamera + 0x90;
					d3_SetObjectRotation(*(int*) &d3_ActiveCamera, v10);
				} else if (CompareVector3WithinTolerance((float*) (*(int*) &d3_ActiveCamera + 0x114), (float*) &g_662d70, 0.1f) == 0
				           && CompareVector3WithinTolerance((float*) (*(int*) &d3_ActiveCamera + 0x120), (float*) &g_662d70, 0.1f) == 0) {
					fcn_00438b40((char*) *(int*) &d3_ActiveCamera, (int*) (*(int*) &d3_ActiveCamera + 0x114));
					v10 = *(int*) &d3_ActiveCamera + 0x120;
					d3_SetObjectRotation(*(int*) &d3_ActiveCamera, v10);
				}
			} else if (CompareVector3WithinTolerance((float*) (*(int*) &d3_ActiveCamera + 0x114), (float*) &g_662d70, 0.1f) == 0
			           && CompareVector3WithinTolerance((float*) (*(int*) &d3_ActiveCamera + 0x120), (float*) &g_662d70, 0.1f) == 0) {
				fcn_00438b40((char*) *(int*) &d3_ActiveCamera, (int*) (*(int*) &d3_ActiveCamera + 0x114));
				v10 = *(int*) &d3_ActiveCamera + 0x120;
				d3_SetObjectRotation(*(int*) &d3_ActiveCamera, v10);
			}
		}
		*(int*) &g_7e3a40 = *(int*) (*(int*) &d3_ActiveCamera + 0x4c);
		*(int*) &g_7e3a44 = *(int*) (*(int*) &d3_ActiveCamera + 0x50);
		*(int*) &g_7e3a48 = *(int*) (*(int*) &d3_ActiveCamera + 0x54);
		*(int*) &d3_CameraTargetRotation = *(int*) (*(int*) &d3_ActiveCamera + 0x84);
		*(int*) &g_7e3a54 = *(int*) (*(int*) &d3_ActiveCamera + 0x88);
		*(int*) &g_7e3a58 = *(int*) (*(int*) &d3_ActiveCamera + 0x8c);
		d3_CameraHorizontalIndex = 0;
		d3_CameraVerticalStep = 0;
	}
	switch (*buildingPtr) {
	case 0x1e:
		fcn_0059c9a0(*(int*) &g_7746c8);
		fcn_004bd1a0(*(int*) (buildingPtr + 0x71));
		break;
	case 0x1f:
		fcn_0059cb40(*(int*) &g_7746c8);
		break;
	case 0x20:
		fcn_0059c800(*(int*) &g_7746c8);
		break;
	case 0x27:
		fcn_0059de00(*(int*) &g_7746c8);
		break;
	case 0x47:
		fcn_0059e390(*(int*) &g_7746c8);
		break;
	case 0x48:
	case 0x49:
	case 0x4a:
		d2_RunFriedhofActions(*(int*) &g_7746c8);
		break;
	case 0x4e:
	case 0x4f:
	case 0x50:
		fcn_005e69f0(*(int*) &g_7746c8);
		break;
	default:
		fcn_0058f700(0);
		break;
	}
	if (n != -1) {
		*(int*) (w + 0x1043378) = 0;
		*(int*) 0x6b89c0 = 0;
	}
	fcn_00530510();
	sv_ClearObjectSelection();
	d3_CameraHorizontalIndex = 0;
	d3_CameraVerticalStep = 0;
	if (id != -1) {
		p = (unsigned char*) evt_FindScriptById(id);
		if (p != 0) {
			evt_RequestScriptExit(p);
			fcn_005312d0(*(int*) (p + 0x100));
		}
	}
	if (*(int*) &g_67a370 != 0) {
		n = *(int*) (*(int*) &g_67a370 + 0x3c8);
		if (n != 0 && *(int*) (n + 0x294) != 0) {
			(*(Cb5a80d0b*) (n + 0x294))(*(int*) &g_67a370, 5, n + 0x298, 0);
		}
	}
	if (*(int*) &evt_LastGfxScriptId != -1) {
		fcn_005312d0(*(int*) &evt_LastGfxScriptId);
	}
	fcn_004c34d0();
	fcn_00516ed0(*(int*) &g_7746c8);
	fcn_0043a9c0(3);
	d3_SelectSceneContext((int) a0, 0);
	*(int*) &g_7ea360 = 0;
	*(int*) &g_7746c8 = 0;
	*(int*) &g_6791c8 = 0;
	g_67530c = -1;
	g_675310 = -1;
	fcn_00516f60();
	*(int*) &g_7e3a40 = s0;
	*(int*) &g_7e3a44 = s1;
	*(int*) &g_7e3a48 = s2;
	*(int*) &d3_CameraTargetRotation = s3;
	*(int*) &g_7e3a54 = s4;
	*(int*) &g_7e3a58 = s5;
}
