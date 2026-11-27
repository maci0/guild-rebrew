extern char g_14cf736;
#include "Develop/DieGildeAddOn/game/game_data.h"
extern short g_7725c4;
extern char* g_7746b4;
extern int g_7ea360;
extern int g_67a370;



void __cdecl fcn_004cf180(void);
void __cdecl sb_PlayVoice(int, char*, int, int, int, int, int);
void __cdecl cut_PlayHitReaction(int);
char __cdecl d3sm_RaycastScreenPoint(int, int, int, int*, int*);
char __cdecl d3_GridPointToWorld(int, int, int, char*);
void __cdecl d3_SpawnBombObject(char*);
void __cdecl io_ClearInputButtonFlags(int);

void __cdecl gm_HandleCannonAimInput(void)
{
	int a;
	int b;
	char buf[16];
	int p;

	fcn_004cf180();
	if (g_14cf736 != 0) {
		g_7725c4 = 0x21;
		if (g_14ce8d8 != 0) {
			sb_PlayVoice(0, "schuss_s", 1, 0x3f, 0x7f, 0, 0);
			if ((*(int*)&g_7746b4) != 0) {
				cut_PlayHitReaction((*(int*)&g_7746b4));
			}
			g_7ea360 = 0;
		}
		if (g_14ce8e0 != 0) {
			p = *(int*) (((char*)g_67a370) + 0xb0);
			if (d3sm_RaycastScreenPoint(p, d2_MouseX, d2_MouseY, &b, &a) != 0 &&
			    d3_GridPointToWorld(p, b, a, buf) != 0) {
				d3_SpawnBombObject(buf);
			}
			io_ClearInputButtonFlags(0x10);
		}
	}
}
