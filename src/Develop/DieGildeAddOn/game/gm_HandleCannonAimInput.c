extern char io_RightShiftKeyDown;
#include "Develop/DieGildeAddOn/game/game_data.h"
extern short d2_CursorStateId;
extern char* sv_HoveredCharacter;
extern int d2_SelectedPerson;
extern int d3_ActiveScene;



void __cdecl cut_UpdateActiveBombs(void);
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

	cut_UpdateActiveBombs();
	if (io_RightShiftKeyDown != 0) {
		d2_CursorStateId = 0x21;
		if (g_14ce8d8 != 0) {
			sb_PlayVoice(0, "schuss_s", 1, 0x3f, 0x7f, 0, 0);
			if ((*(int*)&sv_HoveredCharacter) != 0) {
				cut_PlayHitReaction((*(int*)&sv_HoveredCharacter));
			}
			d2_SelectedPerson = 0;
		}
		if (io_RightButtonReleased != 0) {
			p = *(int*) (((char*)d3_ActiveScene) + 0xb0);
			if (d3sm_RaycastScreenPoint(p, d2_MouseX, d2_MouseY, &b, &a) != 0 &&
			    d3_GridPointToWorld(p, b, a, buf) != 0) {
				d3_SpawnBombObject(buf);
			}
			io_ClearInputButtonFlags(0x10);
		}
	}
}
