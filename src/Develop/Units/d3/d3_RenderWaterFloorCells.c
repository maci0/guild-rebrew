

#include "Develop/Units/d8_vesa/d3d_device_view.h"












// SIZE 0x1f4
typedef struct Cell {
	char pad[0x1ee];
	char on;
	char pad2[5];
} Cell;

#include "Develop/Units/d3/d3_camera.h"

extern volatile int gm_GameTicks;

float* __stdcall fcn_005ec410(float*, float, float, float);
float* __stdcall fcn_005eb970(float*, float*, float*);
void __cdecl d3_UpdateAnimatedFloorMaterials(int, int, int);
void __cdecl d3_RenderFloorCellWater(char*, Cell*);

/* ADDRESS: GOLDDE 0x00439930 */
void __cdecl d3_RenderWaterFloorCells(char* o, char flag)
{
	float m[16];
	Cell (*cells)[8];
	int a;
	int b;

	fcn_005ec410(m, *(float*) (o + 0x50) - *(float*) (((char*)d3_ActiveCamera) + 0x4c), *(float*) (o + 0x54) - *(float*) (((char*)d3_ActiveCamera) + 0x50),
	             *(float*) (o + 0x58) - *(float*) (((char*)d3_ActiveCamera) + 0x54));
	fcn_005eb970(m, m, (float*) (((char*)d3_ActiveCamera) + 0x18c));
	((D3D_DEVICE_VIEW*)g_6b5de0)->vtbl->SetTransform(((D3D_DEVICE_VIEW*)g_6b5de0), 0x100, m);
	if (flag != 0) {
		d3_UpdateAnimatedFloorMaterials(gm_GameTicks, *(unsigned char*) (o + 0x8035), *(int*) (o + 0x7da0));
	}
	cells = (Cell (*)[8]) (o + 0xa0);
	for (a = 0; a < 8; a++) {
		for (b = 0; b < 8; b++) {
			if (cells[a][b].on != 0) {
				d3_RenderFloorCellWater(o, &cells[a][b]);
			}
		}
	}
	((D3D_DEVICE_VIEW*)g_6b5de0)->vtbl->SetRenderState(((D3D_DEVICE_VIEW*)g_6b5de0), 0x2f, 0x10);
}
