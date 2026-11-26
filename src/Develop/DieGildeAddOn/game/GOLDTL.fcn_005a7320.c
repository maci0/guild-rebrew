


extern char* g_7746c4;
#include "Develop/DieGildeAddOn/game/game_data.h"
#include "client_dialog_state.h"
#include "Develop/Units/d3/d3_camera.h"
extern float g_7e3a40[3];
extern float d3_CameraTargetRotation[3];
extern char g_6a30d4[];

short* __cdecl fcn_00502cd0(int, int, int, int);
short* __cdecl gm_NextEntityQueryMatch(void);
void __cdecl fcn_00438b40(char*, char*);
void __cdecl d3_SetObjectRotation(char*, char*);
void __cdecl sb_PlayVoice(int, char*, int, int, int, int, int);

void __cdecl gm_ChangeBuildingRoom(int n, short v)
{
	short* r;
	int i;

	if (n != -1) {
		r = fcn_00502cd0(*(int*) (g_7746c4 + 0x5d), 1, 4, 2);
		if (r == 0) {
			return;
		}
		for (i = 1; i < n; i++) {
			r = gm_NextEntityQueryMatch();
			if (r == 0) {
				return;
			}
		}
		*(short*) (g_7746c4 + 0x29) = *r;
	}
	else {
		*(short*) (g_7746c4 + 0x29) = v;
	}
	g_774654 = g_774650 - g_774658 + 1;
	fcn_00438b40(d3_ActiveCamera, ((char*)g_7e3a40));
	d3_SetObjectRotation(d3_ActiveCamera, ((char*)d3_CameraTargetRotation));
	d3_CameraHorizontalIndex = 0;
	d3_CameraVerticalStep = 0;
	sb_PlayVoice(g_7747c8, g_6a30d4, 1, 0x3f, 0x7f, 0, 0);
}
