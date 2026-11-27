#include "Develop/DieGildeAddOn/game/entity_record.h"

// SIZE 0x90
typedef struct {
	char pad0[0x4c];
	int x;
	int y;
	int z;
	char pad58[0x84 - 0x58];
	int rx;
	int ry;
	int rz;
} View;

// SIZE 0x21c
typedef struct {
	char pad0[0x21c];
} Rec;

#include "Develop/Units/d3/d3_camera.h"
extern volatile int g_6b7fc0;
#include "Develop/DieGildeAddOn/game/game_data.h"
extern int g_6a99e8;
extern int g_774668;
extern int main_LoopFlags;
extern char g_6a2574[4];
extern char g_14cf70f;
extern char* g_7746c4;
extern unsigned char* g_7746c8;
#include "Develop/DieGildeAddOn/game/game_player.h"
extern char g_7f4ca0[];
extern float g_774694;
extern float g_7e3a40[3];
extern float g_7e3a44;
extern float g_7e3a48;
extern float d3_CameraTargetRotation[3];
extern float g_7e3a54;
extern float g_7e3a58;
extern short g_14ce8c0;
extern int g_1040494;
extern int d2_ScreenHeight;

int __cdecl d3_PanCameraFromInput(void);
void __cdecl d3_UpdateCameraFromMouse(void);
void __cdecl d3_AdjustCameraHeight(void);
#include "Develop/DieGildeAddOn/game/spiel.h"
void __cdecl fcn_004125c0(int a, int b);

int __cdecl d3_UpdateCameraController(void)
{
	char* p;

	if (((View*)d3_ActiveCamera) != 0 && g_6b7fc0 == 0) {
		if (d3_SelectionBoxActive == 0 && g_6a99e8 == -1) {
			if (g_14ce8e8 == 0) {
				g_774668 = d3_PanCameraFromInput();
			}
			if (!(main_LoopFlags & 0x8000)) {
				d3_UpdateCameraFromMouse();
			}
			if (g_6a2574[0] != 0 && g_14cf70f == 0) {
				d3_AdjustCameraHeight();
			}
			if (g_774668 != 0 && g_774650 == g_774658 && (*(int*)&g_7746c4) == 0 && (*(int*)&g_7746c8) == 0) {
				p = (char*) gm_GetEntityTableEntry((char*) (((Rec *)&((ENTITY_RECORD_VIEW *)g_7f4ca0)[g_774970])));
				if (p != 0) {
					*(int*) (p + 0x8c) = ((View*)d3_ActiveCamera)->x;
					*(int*) (p + 0x90) = ((View*)d3_ActiveCamera)->y;
					*(int*) (p + 0x94) = ((View*)d3_ActiveCamera)->z;
					*(int*) (p + 0x9c) = ((View*)d3_ActiveCamera)->rx;
					*(int*) (p + 0xa0) = ((View*)d3_ActiveCamera)->ry;
					*(int*) (p + 0xa4) = ((View*)d3_ActiveCamera)->rz;
					*(int*) (p + 0x88) = (*(int*)&g_774694);
				}
			}
			(*(int*)d3_CameraTargetRotation) = ((View*)d3_ActiveCamera)->rx;
			(*(int*)&g_7e3a54) = ((View*)d3_ActiveCamera)->ry;
			(*(int*)&g_7e3a58) = ((View*)d3_ActiveCamera)->rz;
			(*(int*)g_7e3a40) = ((View*)d3_ActiveCamera)->x;
			(*(int*)&g_7e3a44) = ((View*)d3_ActiveCamera)->y;
			(*(int*)&g_7e3a48) = ((View*)d3_ActiveCamera)->z;
		}
		return g_774668;
	}
	g_774668 = 0;
	if (g_6772c4 == 0) {
		g_6b5c80 = 0;
		d2_MouseTopBoundary = 0;
		d2_MouseRightBoundary = g_1040494 - 8;
		d2_MouseBottomBoundary = d2_ScreenHeight;
		g_6772c4 = 1;
		fcn_004125c0(g_14ce8c0, g_14ce8c0);
	}
	return 0;
}
