


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
extern float g_7e3a40[3];
extern float g_7e3a44;
extern float g_7e3a48;
extern float d3_CameraTargetRotation[3];
extern float g_7e3a54;
extern float g_7e3a58;

float __cdecl fcn_00413d10(Vec3* p);
void __cdecl fcn_00438b40(View* v, Vec4* p);
void __cdecl fcn_00438cb0(View* v, Vec3* r);

void __cdecl fcn_0052ac60(float t)
{
	float h;
	Vec4 p;
	Vec3 r;

	if (d3_CurrentContextIndex == 0) {
		d3_CameraHeightFraction = t;
		g_774694 = t;
		h = fcn_00413d10(&((View*)d3_ActiveCamera)->pos);
		p.x = ((View*)d3_ActiveCamera)->pos.x;
		p.y = ((View*)d3_ActiveCamera)->pos.y;
		p.z = ((View*)d3_ActiveCamera)->pos.z;
		p.y = (g_6a2560 - g_6a2558) * d3_CameraHeightFraction + g_6a2558 + h;
		fcn_00438b40(((View*)d3_ActiveCamera), &p);
		r.x = ((View*)d3_ActiveCamera)->rot.x;
		r.y = ((View*)d3_ActiveCamera)->rot.y;
		r.z = ((View*)d3_ActiveCamera)->rot.z;
		r.x = (g_6a2564 - g_6a255c) * g_774694 + g_6a255c;
		fcn_00438cb0(((View*)d3_ActiveCamera), &r);
		(*(float*)d3_CameraTargetRotation) = ((View*)d3_ActiveCamera)->rot.x;
		g_7e3a54 = ((View*)d3_ActiveCamera)->rot.y;
		g_7e3a58 = ((View*)d3_ActiveCamera)->rot.z;
		(*(float*)g_7e3a40) = ((View*)d3_ActiveCamera)->pos.x;
		g_7e3a44 = ((View*)d3_ActiveCamera)->pos.y;
		g_7e3a48 = ((View*)d3_ActiveCamera)->pos.z;
	}
}
