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
extern volatile int tb_TimerPaused;
#include "Develop/DieGildeAddOn/game/game_data.h"
extern int g_6a99e8;
extern int g_774668;
extern int main_LoopFlags;
extern char g_6a2574[4];
extern char g_14cf70f;
extern char* d2_VisitedBuilding;
extern unsigned char* d2_InteriorBuilding;
#include "Develop/DieGildeAddOn/game/game_player.h"
extern char gm_EntitySlotTable[];
extern float g_774694;
extern float d3_SavedCameraPos[3];
extern float d3_SavedCameraPosY;
extern float d3_SavedCameraPosZ;
extern float d3_CameraTargetRotation[3];
extern float d3_CameraTargetRotY;
extern float d3_CameraTargetRotZ;
extern short io_ActiveCursorX;
extern int g_1040494;
extern int d2_ScreenHeight;

int __cdecl d3_PanCameraFromInput(void);
void __cdecl d3_UpdateCameraFromMouse(void);
void __cdecl d3_AdjustCameraHeight(void);
#include "Develop/DieGildeAddOn/game/spiel.h"
void __cdecl io_SetMouseCursorPos(int a, int b);

int __cdecl d3_UpdateCameraController(void)
{
	char* p;

	if (((View*)d3_ActiveCamera) != 0 && tb_TimerPaused == 0) {
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
			if (g_774668 != 0 && g_774650 == g_774658 && (*(int*)&d2_VisitedBuilding) == 0 && (*(int*)&d2_InteriorBuilding) == 0) {
				p = (char*) gm_GetEntityTableEntry((char*) (((Rec *)&((ENTITY_RECORD_VIEW *)gm_EntitySlotTable)[gm_LocalPlayerSlot])));
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
			(*(int*)&d3_CameraTargetRotY) = ((View*)d3_ActiveCamera)->ry;
			(*(int*)&d3_CameraTargetRotZ) = ((View*)d3_ActiveCamera)->rz;
			(*(int*)d3_SavedCameraPos) = ((View*)d3_ActiveCamera)->x;
			(*(int*)&d3_SavedCameraPosY) = ((View*)d3_ActiveCamera)->y;
			(*(int*)&d3_SavedCameraPosZ) = ((View*)d3_ActiveCamera)->z;
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
		io_SetMouseCursorPos(io_ActiveCursorX, io_ActiveCursorX);
	}
	return 0;
}
