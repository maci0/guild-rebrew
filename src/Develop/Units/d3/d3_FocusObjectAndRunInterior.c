#include "Develop/Units/d3/d3_camera.h"

extern int sv_ClickedObjekt;
extern int d2_VisitedBuilding;
extern int g_774650;
extern int g_774658;
extern float d3_SavedCameraPos;
extern float d3_SavedCameraPosY;
extern float d3_SavedCameraPosZ;
extern float d3_CameraTargetRotation;
extern float d3_CameraTargetRotY;
extern float d3_CameraTargetRotZ;
extern int evt_ActiveContextId;
extern int g_6a256c;
extern int d3_CameraAnimating;
extern double g_dbl_665fb8;

void __cdecl d3_SetObjectVisible(char* object, int flag);
void __cdecl d3_NormalizeVector(float* vector);
void __cdecl d3_AnimateObjectTransform(char* camera, float* position, char* view, int limit, int mode);
int __cdecl main_RunFrameLoop(int a, int b);
void __cdecl d2_RunDefaultBuildingInterior(int flag);
void __cdecl d3_AnimateCameraToStoredTransform(void);

struct CAMERA_SAVE {
	float offset[4];
	float target[4];
	float saveA[4];
	float saveB[3];
};

/* ADDRESS: GOLDTL 0x005a8c30 */
void __cdecl d3_FocusObjectAndRunInterior(char* object)
{
	struct CAMERA_SAVE v;
	char* camera;
	int previous;

	d2_VisitedBuilding = (int) object;
	evt_ActiveContextId = *(int*) (object + 1);
	g_774658 = g_774650 + 1;
	previous = sv_ClickedObjekt;
	v.saveA[0] = d3_SavedCameraPos;
	v.saveA[1] = d3_SavedCameraPosY;
	v.saveA[2] = d3_SavedCameraPosZ;
	v.saveB[0] = d3_CameraTargetRotation;
	v.saveB[1] = d3_CameraTargetRotY;
	v.saveB[2] = d3_CameraTargetRotZ;
	d3_SetObjectVisible((char*) previous, 0);
	v.offset[0] = *(float*) (sv_ClickedObjekt + 0x4c) - *(float*) (d3_ActiveCamera + 0x4c);
	v.offset[1] = *(float*) (sv_ClickedObjekt + 0x50) - *(float*) (d3_ActiveCamera + 0x50);
	v.offset[2] = *(float*) (sv_ClickedObjekt + 0x54) - *(float*) (d3_ActiveCamera + 0x54);
	d3_NormalizeVector(v.offset);
	v.offset[0] *= g_dbl_665fb8;
	v.offset[1] *= g_dbl_665fb8;
	v.offset[2] *= g_dbl_665fb8;
	v.target[0] = *(float*) (sv_ClickedObjekt + 0x4c) - v.offset[0];
	v.target[1] = *(float*) (sv_ClickedObjekt + 0x50) - v.offset[1];
	v.target[2] = *(float*) (sv_ClickedObjekt + 0x54) - v.offset[2];
	*(int*) (sv_ClickedObjekt + 0x94) = *(int*) (d3_ActiveCamera + 0x88);
	d3_AnimateObjectTransform(d3_ActiveCamera, v.target, (char*) sv_ClickedObjekt + 0x90, g_6a256c, 8);
	do {
		if (!main_RunFrameLoop(0, 0x67fff)) {
			break;
		}
	} while (d3_CameraAnimating);
	camera = d3_ActiveCamera;
	d3_SavedCameraPos = *(float*) (camera + 0x4c);
	d3_SavedCameraPosY = *(float*) (camera + 0x50);
	d3_SavedCameraPosZ = *(float*) (camera + 0x54);
	d3_CameraTargetRotation = *(float*) (camera + 0x84);
	d3_CameraTargetRotY = *(float*) (camera + 0x88);
	d3_CameraTargetRotZ = *(float*) (camera + 0x8c);
	d2_RunDefaultBuildingInterior(0);
	d3_SavedCameraPos = v.saveA[0];
	d3_SavedCameraPosY = v.saveA[1];
	d3_SavedCameraPosZ = v.saveA[2];
	evt_ActiveContextId = 0;
	d3_CameraTargetRotation = v.saveB[0];
	d3_CameraTargetRotY = v.saveB[1];
	d3_CameraTargetRotZ = v.saveB[2];
	d3_AnimateCameraToStoredTransform();
	d3_SetObjectVisible((char*) previous, 1);
}
