

#include "Develop/Units/d3/d3_camera.h"
extern float d3_SavedCameraPos[3];
extern float d3_SavedCameraPosY;
extern float d3_SavedCameraPosZ;
extern float d3_CameraTargetRotation[3];
extern float d3_CameraTargetRotY;
extern float d3_CameraTargetRotZ;
#include "Develop/DieGildeAddOn/game/game_data.h"

int __cdecl d3_AnimateObjectToTransform(char* a, float b, float c, float d, float e, float f, float g, int h, int i);

/* ADDRESS: GOLDDE 0x005161b0 */
void __cdecl d3_AnimateCameraToStoredTransform(void)
{
	d3_AnimateObjectToTransform(d3_ActiveCamera, d3_SavedCameraPos[0], d3_SavedCameraPosY, d3_SavedCameraPosZ, d3_CameraTargetRotation[0], d3_CameraTargetRotY, d3_CameraTargetRotZ, g_6a256c, 8);
}
