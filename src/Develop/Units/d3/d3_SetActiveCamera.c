#include "Develop/Units/d3/d3_camera.h"



void __cdecl d3_InvalidateSceneRenderCache(unsigned char);

void __cdecl d3_SetActiveCamera(char* camera)
{
	if (camera == d3_ActiveCamera) {
		return;
	}
	if (*(int*) (camera + 0x218) != 3) {
		return;
	}
	d3_ActiveCamera = camera;
	d3_InvalidateSceneRenderCache(0);
}
