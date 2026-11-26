


// SIZE 0x8
typedef struct {
	void* fn;
	int arg;
} Mode59a2;

extern char g_14cf950;
#include "Develop/Units/d3/d3_camera.h"
#include "Develop/DieGildeAddOn/game/game_data.h"
extern int g_7e35c0[];

void __cdecl d2_RunWorldHudLoop(void);
void __cdecl fcn_0057e880(int, int, int, int);
#include "client_scene_transform.h"
void __cdecl d3_AnimateObjectTransform(char*, float*, float*, int, int);

void __cdecl d3_HandleCameraLevelKey(void)
{
	float v[3];
	float x;

	if (g_14cf950 == '1' && d3_ActiveCamera != 0 && ((Mode59a2*)g_7e35c0)[g_774650].fn == (void*) d2_RunWorldHudLoop) {
		fcn_0057e880(0x16, 0, 0, 0);
		x = *(float*) (d3_ActiveCamera + 0x84);
		v[0] = x;
		v[1] = 0;
		x = *(float*) (d3_ActiveCamera + 0x8c);
		v[2] = x;
		if (CompareVector3WithinTolerance(v, (float*) (d3_ActiveCamera + 0x84), 0.1f) == 0) {
			d3_AnimateObjectTransform(d3_ActiveCamera, (float*) (d3_ActiveCamera + 0x4c), v, 0x1e, 0x28);
		}
	}
}
