


extern char* d2_VisitedBuilding;
#include "Develop/DieGildeAddOn/game/game_data.h"
#include "Develop/Units/d2.v1/client_dialog_state.h"
#include "Develop/Units/d3/d3_camera.h"
extern float d3_SavedCameraPos[3];
extern float d3_CameraTargetRotation[3];
extern char g_6a30d4[];

short* __cdecl gm_QueryEntities(int, int, int, int);
short* __cdecl gm_NextEntityQueryMatch(void);
void __cdecl d3_SetNodePosition(char*, char*);
void __cdecl d3_SetObjectRotation(char*, char*);
void __cdecl sb_PlayVoice(int, char*, int, int, int, int, int);

void __cdecl gm_ChangeBuildingRoom(int n, short v)
{
	short* r;
	int i;

	if (n != -1) {
		r = gm_QueryEntities(*(int*) (d2_VisitedBuilding + 0x5d), 1, 4, 2);
		if (r == 0) {
			return;
		}
		for (i = 1; i < n; i++) {
			r = gm_NextEntityQueryMatch();
			if (r == 0) {
				return;
			}
		}
		*(short*) (d2_VisitedBuilding + 0x29) = *r;
	}
	else {
		*(short*) (d2_VisitedBuilding + 0x29) = v;
	}
	d2_DialogCloseRequested = g_774650 - g_774658 + 1;
	d3_SetNodePosition(d3_ActiveCamera, ((char*)d3_SavedCameraPos));
	d3_SetObjectRotation(d3_ActiveCamera, ((char*)d3_CameraTargetRotation));
	d3_CameraHorizontalIndex = 0;
	d3_CameraVerticalStep = 0;
	sb_PlayVoice(g_7747c8, g_6a30d4, 1, 0x3f, 0x7f, 0, 0);
}
