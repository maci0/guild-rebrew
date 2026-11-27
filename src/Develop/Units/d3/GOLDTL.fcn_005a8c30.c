#include "Develop/Units/d3/d3_camera.h"

extern int g_7746a0;
extern int g_7746c4;
extern int g_774650;
extern int g_774658;
extern float g_7e3a40;
extern float g_7e3a44;
extern float g_7e3a48;
extern float d3_CameraTargetRotation;
extern float g_7e3a54;
extern float g_7e3a58;
extern int g_6791c8;
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

	g_7746c4 = (int) object;
	g_6791c8 = *(int*) (object + 1);
	g_774658 = g_774650 + 1;
	previous = g_7746a0;
	v.saveA[0] = g_7e3a40;
	v.saveA[1] = g_7e3a44;
	v.saveA[2] = g_7e3a48;
	v.saveB[0] = d3_CameraTargetRotation;
	v.saveB[1] = g_7e3a54;
	v.saveB[2] = g_7e3a58;
	d3_SetObjectVisible((char*) previous, 0);
	v.offset[0] = *(float*) (g_7746a0 + 0x4c) - *(float*) (d3_ActiveCamera + 0x4c);
	v.offset[1] = *(float*) (g_7746a0 + 0x50) - *(float*) (d3_ActiveCamera + 0x50);
	v.offset[2] = *(float*) (g_7746a0 + 0x54) - *(float*) (d3_ActiveCamera + 0x54);
	d3_NormalizeVector(v.offset);
	v.offset[0] *= g_dbl_665fb8;
	v.offset[1] *= g_dbl_665fb8;
	v.offset[2] *= g_dbl_665fb8;
	v.target[0] = *(float*) (g_7746a0 + 0x4c) - v.offset[0];
	v.target[1] = *(float*) (g_7746a0 + 0x50) - v.offset[1];
	v.target[2] = *(float*) (g_7746a0 + 0x54) - v.offset[2];
	*(int*) (g_7746a0 + 0x94) = *(int*) (d3_ActiveCamera + 0x88);
	d3_AnimateObjectTransform(d3_ActiveCamera, v.target, (char*) g_7746a0 + 0x90, g_6a256c, 8);
	do {
		if (!main_RunFrameLoop(0, 0x67fff)) {
			break;
		}
	} while (d3_CameraAnimating);
	camera = d3_ActiveCamera;
	g_7e3a40 = *(float*) (camera + 0x4c);
	g_7e3a44 = *(float*) (camera + 0x50);
	g_7e3a48 = *(float*) (camera + 0x54);
	d3_CameraTargetRotation = *(float*) (camera + 0x84);
	g_7e3a54 = *(float*) (camera + 0x88);
	g_7e3a58 = *(float*) (camera + 0x8c);
	d2_RunDefaultBuildingInterior(0);
	g_7e3a40 = v.saveA[0];
	g_7e3a44 = v.saveA[1];
	g_7e3a48 = v.saveA[2];
	g_6791c8 = 0;
	d3_CameraTargetRotation = v.saveB[0];
	g_7e3a54 = v.saveB[1];
	g_7e3a58 = v.saveB[2];
	d3_AnimateCameraToStoredTransform();
	d3_SetObjectVisible((char*) previous, 1);
}
