


// SIZE 0xc
typedef struct {
	float x;
	float y;
	float z;
} Vec3;

// SIZE 0x10
typedef struct {
	float x;
	float y;
	float z;
	float w;
} Vec4;

// SIZE 0x90
typedef struct {
	char pad0[0x4c];
	Vec3 pos;
	char pad58[0x84 - 0x58];
	Vec3 rot;
} View;

#include "Develop/DieGildeAddOn/game/game_data.h"
#include "Develop/Units/d3/d3_camera.h"
extern float g_774694;
extern float g_6a255c;
extern float g_6a2564;
extern float d3_SavedCameraPos[3];
extern float d3_SavedCameraPosY;
extern float d3_SavedCameraPosZ;
extern float d3_CameraTargetRotation[3];
extern float d3_CameraTargetRotY;
extern float d3_CameraTargetRotZ;

float __cdecl d3_SampleAverageTerrainHeight(Vec3* p);
void __cdecl d3_SetNodePosition(View* v, Vec4* p);
void __cdecl d3_SetObjectRotation(View* v, Vec3* r);

void __cdecl d3_SetCameraHeightFraction(float t)
{
	float h;
	Vec4 p;
	Vec3 r;

	if (d3_CurrentContextIndex == 0) {
		d3_CameraHeightFraction = t;
		g_774694 = t;
		h = d3_SampleAverageTerrainHeight(&((View*)d3_ActiveCamera)->pos);
		p.x = ((View*)d3_ActiveCamera)->pos.x;
		p.y = ((View*)d3_ActiveCamera)->pos.y;
		p.z = ((View*)d3_ActiveCamera)->pos.z;
		p.y = (g_6a2560 - g_6a2558) * d3_CameraHeightFraction + g_6a2558 + h;
		d3_SetNodePosition(((View*)d3_ActiveCamera), &p);
		r.x = ((View*)d3_ActiveCamera)->rot.x;
		r.y = ((View*)d3_ActiveCamera)->rot.y;
		r.z = ((View*)d3_ActiveCamera)->rot.z;
		r.x = (g_6a2564 - g_6a255c) * g_774694 + g_6a255c;
		d3_SetObjectRotation(((View*)d3_ActiveCamera), &r);
		(*(float*)d3_CameraTargetRotation) = ((View*)d3_ActiveCamera)->rot.x;
		d3_CameraTargetRotY = ((View*)d3_ActiveCamera)->rot.y;
		d3_CameraTargetRotZ = ((View*)d3_ActiveCamera)->rot.z;
		(*(float*)d3_SavedCameraPos) = ((View*)d3_ActiveCamera)->pos.x;
		d3_SavedCameraPosY = ((View*)d3_ActiveCamera)->pos.y;
		d3_SavedCameraPosZ = ((View*)d3_ActiveCamera)->pos.z;
	}
}
