extern char* g_1015ea0;
extern int g_14ce8e0;
extern char g_14cf950;
extern float g_14ce880;
extern int d2_CurrentElementId;
extern int d3_CameraAnimating;
int d3_ActiveCameraAnimation = 0;
extern char* d3_ActiveCamera;
extern float g_7e3a40[3];
extern float d3_CameraTargetRotation[3];
extern int* g_7e2a9c;
extern char* g_7e2aa0;
extern int g_7ea360;
extern unsigned char g_7f4e51[];
extern char* g_item_def_table;
#include "Develop/DieGildeAddOn/game/game_player.h"
extern int g_774650;
#include "client_dialog_state.h"
extern int g_774658;
extern int g_77465c;
extern int d3_CameraHorizontalIndex;
extern int d3_CameraVerticalStep;
extern char* g_7746a8;
extern int g_7746b8;
extern char* g_7746c4;
extern unsigned char* g_7746c8;
extern char* g_7746cc;
extern int g_7746d4;
extern int g_7746d8;
extern int g_7746dc;
extern int g_7746f0;
extern char g_7746f4;
extern char* g_7747a0;
extern char* g_7747a4;
extern char* g_7747b8;
extern int g_7747c8;
extern unsigned char** g_7749e4;
extern char g_7749e8;
#include "Develop/Units/d2.v1/d2_gui.h"
void __cdecl io_ClearInputState(void);
void __cdecl io_ClearMouseAndKeyState(void);
void __cdecl io_ClearInputButtonFlags(unsigned char mask);
void __cdecl sb_PlayVoice(char*, char*, int, int, int, int, int);
void __cdecl d3_FreeObjectAnimation(void*);
void __cdecl d3_SetNodePosition(char*, float*);
void __cdecl d3_SetObjectRotation(char*, float*);
int __cdecl CompareVector3WithinTolerance(float*, float*, float);
void __cdecl gm_UpdateAmbientAnimals(void);
int* __cdecl gm_SetupEntityQuery(char*);
int __cdecl gm_GetEntityUiFlags(int, void*, void*, int);
void __cdecl d3_UpdateCameraAtScreenEdges(void);
void __cdecl d3_AnimateCameraToStoredTransform(void);
void __cdecl d2_UpdateSelectionPanels(void);
void __cdecl sv_ResetSelectionState(void);
void __cdecl d2_ClearStatusTextSlots(void);
void __cdecl d2_HighlightSelectedControl(int);
void __cdecl d2_StepTutorialStateMachine(void);
int __cdecl d2_DispatchTutorialEvent(int, int, int, int);
void __cdecl d2_HandleEntityChooser(void);
void __cdecl gm_ChangeBuildingRoom(int, int);

/* ADDRESS: GOLDTL 0x00533090 */
void __cdecl d2_UpdateBuildingCameraAndUi(unsigned int flags)
{
	char* p;
	char* q;
	char* e;
	char* d;
	char* v4;
	char* v5;
	int* ip;
	int i;
	int v2;

	d = 0;
	if (g_14ce8e0 && (*(int*) (g_774650 * 8 + 0x7e35c0) != 0x59a340 || g_7746f0
	    || g_7e2a9c || g_7ea360 || g_7e2aa0)) {
		sb_PlayVoice(g_7747b8, "MausclickRechts_s_01", 1, 0x3f, 0x7f, 0, 0);
	}
	if (g_7749e4) {
		if (g_14ce8e0 == 0 && g_14cf950 != 0x1c) {
			return;
		}
		if (*g_7749e4 != 0) {
			if (**g_7749e4 == 0x11 || **g_7749e4 == 0x26 || **g_7749e4 == 0x69) {
				g_7749e8 = 1;
			} else if (**g_7749e4 == 0x87) {
				d2_StepTutorialStateMachine();
			} else {
				d2_HighlightSelectedControl(0);
			}
		} else {
			d2_HighlightSelectedControl(0);
		}
		io_ClearInputButtonFlags(0x10);
		if (g_14cf950 != 0x1c) {
			return;
		}
		g_14cf950 = 0;
		return;
	}
	if (g_14ce8e0 != 0 && d2_CurrentElementId != -1) {
		i = 0;
		ip = (int*) 0x77e8c4;
		do {
			if (*ip != -1 && (ip - 1) != 0
			    && d2_CurrentElementId == *(int*) ((char*)&((D2_CONTROL_TL*)g_1015ea0)[*ip])) {
				*(int*) (*(int*) (i * 0xc + 0x77e8c0) + 0x70) = -1;
				g_7749e8 = 0;
				io_ClearInputState();
				break;
			}
			ip += 3;
			i += 1;
		} while ((int) ip < 0x77e984);
	}
	if (flags & 0x800) {
		d2_HandleEntityChooser();
		gm_UpdateAmbientAnimals();
		if (g_14ce8e0 && g_7e2aa0
		    && *(int*) (g_774650 * 8 + 0x7e35c0) == 0x59a340) {
			sv_ResetSelectionState();
			goto done;
		}
		if (g_7746c4 != 0) {
			if (g_7746b8 && g_7746f0 == 0 && g_7746f4 == 0) {
				sb_PlayVoice((char*) g_7747c8, "RaumWechseln_s", 1, 0x3f, 0x7f, 0, 0);
				*(unsigned short*) (g_7746c4 + 0x29) = *(unsigned short*) g_7746b8;
				g_774654 = (g_774650 - g_774658) + 1;
				d3_SetNodePosition(d3_ActiveCamera, g_7e3a40);
				d3_SetObjectRotation(d3_ActiveCamera, d3_CameraTargetRotation);
				d3_CameraHorizontalIndex = 0;
				d3_CameraVerticalStep = 0;
			}
		} else if (g_7746c8 != 0 && g_7746cc != 0 && g_7746b8 != 0
		    && g_7746f0 == 0 && g_7746f4 == 0) {
			g_774654 = (g_774650 - g_774658) + 1;
			d3_SetNodePosition(d3_ActiveCamera, g_7e3a40);
			d3_SetObjectRotation(d3_ActiveCamera, d3_CameraTargetRotation);
			d3_CameraHorizontalIndex = 0;
			d3_CameraVerticalStep = 0;
		}
		if (g_14ce8e0 && (g_7746f4 != 0 || (g_7e2a9c != 0
		    && g_item_def_table[*(unsigned short*) g_7e2a9c * 0x41] == 0x1d))) {
			sv_ResetSelectionState();
			io_ClearInputButtonFlags(0x10);
		}
		if ((g_7746c4 != 0
		    && d2_DispatchTutorialEvent(0x1a, (int) g_7746c4, 0, *(unsigned short*) g_7746cc) == 0)
		    || (g_7746c8 != 0 && d2_DispatchTutorialEvent(0x1c, (int) g_7746c8, 0, 0) == 0)) {
			io_ClearMouseAndKeyState();
		}
		if (g_7746f0 || g_7746f4 || g_14ce8e0 == 0) {
			goto done;
		}
		v2 = 0;
		if (d3_ActiveCameraAnimation) {
			if (g_7746c4 == 0 && g_7746c8 == 0) {
				goto done;
			}
			if (CompareVector3WithinTolerance(&g_14ce880, g_7e3a40, 0.1f)) {
				d3_FreeObjectAnimation(d3_ActiveCamera);
				d3_ActiveCameraAnimation = 0;
				d3_CameraAnimating = 0;
				v2 = 1;
				d3_SetNodePosition(d3_ActiveCamera, g_7e3a40);
				d3_SetObjectRotation(d3_ActiveCamera, d3_CameraTargetRotation);
			} else {
				d3_FreeObjectAnimation(d3_ActiveCamera);
				d3_ActiveCameraAnimation = 0;
				d3_CameraAnimating = 0;
			}
		}
		if (g_774650 <= g_774658 || v2) {
			if (CompareVector3WithinTolerance((float*) (d3_ActiveCamera + 0x84), d3_CameraTargetRotation, 0.1f)
			    || CompareVector3WithinTolerance((float*) (d3_ActiveCamera + 0x4c), g_7e3a40, 0.1f) || v2) {
				if (g_7746c4 == 0 && g_7746c8 == 0 && g_7746cc == 0) {
					if (g_774650 == g_774658 && g_7e2a9c) {
						sv_ResetSelectionState();
					}
					goto done;
				}
				v5 = 0;
				if (g_7746cc != 0) {
					if (g_7746c4 != 0) {
						i = d2_DispatchTutorialEvent(0x1a, (int) g_7746c4, 0,
						    *(unsigned short*) g_7746cc);
						if (i == 1 && g_7f4e51[g_774970 * 0x21c] == 0
						    && g_7746c4 != 0 && *(unsigned short*) g_7746cc == 0xf2) {
							v5 = (char*) gm_SetupEntityQuery(g_7746c4);
						}
					} else if (g_7746c8 != 0) {
						i = d2_DispatchTutorialEvent(0x1c, (int) g_7746c8, 0, 0);
						if (i == 1 && g_7f4e51[g_774970 * 0x21c] == 0
						    && g_7746c8 != 0 && *(unsigned short*) g_7746cc == 0xf2) {
							v5 = (char*) gm_SetupEntityQuery(g_7746c8);
						}
					}
					if (g_7746c4 != 0 && v5 != 0 && v5 != g_7746cc) {
						gm_ChangeBuildingRoom(-1, (int) *(unsigned short*) v5);
					} else {
						g_7746cc = 0;
					}
				} else if (g_7746c8 != 0 || g_7746c4 != 0) {
					g_7746c8 = 0;
					g_7746c4 = 0;
					g_7746cc = 0;
				} else {
					g_7746cc = 0;
				}
				g_774654 = 1;
				if (g_7746c4 != 0 && g_7746cc == 0) {
					g_7746c4 = 0;
				}
				d3_SetNodePosition(d3_ActiveCamera, g_7e3a40);
				d3_SetObjectRotation(d3_ActiveCamera, d3_CameraTargetRotation);
				d3_CameraHorizontalIndex = 0;
				d3_CameraVerticalStep = 0;
				goto done;
			}
			if (g_7746c4 != 0 || g_7746c8 != 0) {
				d3_AnimateCameraToStoredTransform();
			}
		} else {
			g_774654 = 1;
			if (g_77465c < g_774650 - 1) {
				goto done;
			}
			if (g_7746c4 != 0 || g_7746c8 != 0) {
				d3_AnimateCameraToStoredTransform();
			}
			g_77465c = g_774650 - g_774654;
		}
		if (g_7746a8 != 0) {
			e = *(char**) (g_7746a8 + 0x1d4);
			if (e != 0 && *(int*) (e + 0x18c) != 0) {
				(*(void (__cdecl**) (char*, int, char*, int)) (e + 0x18c))
				    (g_7746a8, 3, e + 400, 0);
			}
			g_7746a8 = 0;
		}
		sv_ResetSelectionState();
	}
done:
	if (flags & 0x100) {
		d2_UpdateSelectionPanels();
	}
	v4 = g_7746c4;
	if (v4 == 0) {
		v4 = g_7746c8 != 0 ? g_7746c8 : d;
	}
	if ((flags & 8) && v4 != 0) {
		if (g_7746cc != 0) {
			g_7746dc = gm_GetEntityUiFlags(g_774970, v4, g_7746cc, 0);
		} else {
			g_7746dc = gm_GetEntityUiFlags(g_774970, v4, 0, 0);
		}
		if (*(unsigned short*) (v4 + 0x27) == g_774970 || (g_7746dc & 0x1000)) {
			d3_UpdateCameraAtScreenEdges();
		}
	}
	if (g_7747a0 == v4 && g_7747a4 == g_7746cc && g_7746d4 == 0) {
		return;
	}
	g_7746d8 = gm_GetEntityUiFlags(g_774970, v4, g_7746cc, 0);
	d2_ClearStatusTextSlots();
	g_7747a0 = v4;
	g_7747a4 = g_7746cc;
	g_7746d4 = 0;
}
unsigned char _dpad_7e35c0[1152];
