#include "Develop/DieGildeAddOn/game/entity_record.h"

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

typedef struct View {
	char pad0[0x4c];
	Vec3 pos;
	char pad58[0x84 - 0x58];
	Vec3 rot;
	char pad90[0x18c - 0x90];
	float mat[16];
} View;

typedef struct Save {
	char pad0[0x8c];
	Vec3 pos;
	int pad98;
	Vec3 rot;
} Save;

#pragma pack(push, 1)
typedef struct Ent {
	char pad0[0x61];
	char* obj;
} Ent;
#pragma pack(pop)

typedef struct House {
	char pad0[0x21c];
} House;
// SIZE 0x21c

#include "Develop/Units/d3/d3_camera.h"
extern float d3_UnitAxisVectors[3];
#include "Develop/DieGildeAddOn/game/game_data.h"
extern float d3_SavedCameraPos[3];
extern float d3_CameraTargetRotation[3];
#include "Develop/DieGildeAddOn/game/game_player.h"
extern char gm_EntitySlotTable[];
extern char* d2_SelectedBuilding;
extern char* d3_FocusedEntityObject;

int __cdecl d3_GetObjectVerticalBounds(char* e, float* lo, float* hi);
float* __stdcall D3DXMatrixTranspose(float* out, float* in);
void __cdecl d3_TransformPoint(char* src, char* pos, Vec3* out);
float __cdecl d3_SampleAverageTerrainHeight(Vec3* p);
void __cdecl d3_FreeObjectAnimation(View* v);
void __cdecl d3_SetNodePosition(View* v, Vec3* p);
void __cdecl d3_SetObjectRotation(View* v, Vec3* r);
#include "Develop/DieGildeAddOn/game/spiel.h"

void __cdecl d3_SnapCameraToEntity(Ent* entity)
{
	Vec4 q;
	Vec3 rot;
	float lo;
	float hi;
	Vec4 off;
	Vec4 p;
	float m[16];
	Vec4 d;
	float r;
	float h;
	float h2;
	float a;
	float b;
	float c;
	char* obj;
	Save* s;

	obj = entity->obj;
	d3_GetObjectVerticalBounds(obj, &lo, &hi);
	D3DXMatrixTranspose(m, ((View*)d3_ActiveCamera)->mat);
	a = d3_UnitAxisVectors[0] * -600.0f;
	b = d3_UnitAxisVectors[1] * -600.0f;
	c = d3_UnitAxisVectors[2] * -600.0f;
	off.x = a * m[0] + b * m[4] + c * m[8];
	off.y = a * m[1] + b * m[5] + c * m[9];
	off.z = a * m[2] + b * m[6] + c * m[10];
	d3_TransformPoint(obj, obj + 0x4c, (Vec3*) &p);
	q.x = p.x + off.x;
	q.y = p.y + off.y;
	q.z = p.z + off.z;
	h = d3_SampleAverageTerrainHeight((Vec3*) &q);
	q.y = ((g_6a2560 - g_6a2558) * d3_CameraHeightFraction + g_6a2558) + h;
	d.y = q.y - p.y;
	d3_GetObjectVerticalBounds(obj, &lo, &hi);
	r = off.y / ((hi - lo) * 0.5f + d.y);
	q.x = (float)(q.x - (r * off.x - off.x * 1.8));
	q.z = (float)(q.z - (r * off.z - off.z * 1.8));
	*(int*) &rot.x = *(int*) &((View*)d3_ActiveCamera)->rot.x;
	*(int*) &rot.y = *(int*) &((View*)d3_ActiveCamera)->rot.y;
	*(int*) &rot.z = *(int*) &((View*)d3_ActiveCamera)->rot.z;
	d3_FreeObjectAnimation((View*)d3_ActiveCamera);
	d3_ActiveCameraAnimation = 0;
	d3_CameraAnimating = 0;
	h2 = d3_SampleAverageTerrainHeight((Vec3*) &q);
	q.y = ((g_6a2560 - g_6a2558) * d3_CameraHeightFraction + g_6a2558) + h2;
	d3_CameraTargetRotation[0] = rot.x;
	d3_CameraTargetRotation[1] = rot.y;
	d3_CameraTargetRotation[2] = rot.z;
	d3_SavedCameraPos[0] = q.x;
	d3_SavedCameraPos[1] = q.y;
	d3_SavedCameraPos[2] = q.z;
	d3_SetNodePosition((View*)d3_ActiveCamera, (Vec3*) &q);
	d3_SetObjectRotation((View*)d3_ActiveCamera, &rot);
	s = (Save*) gm_GetEntityTableEntry((char*) (((House *)&((ENTITY_RECORD_VIEW *)gm_EntitySlotTable)[gm_LocalPlayerSlot])));
	if (s != 0) {
		*(int*) &s->pos.x = *(int*) &q.x;
		*(int*) &s->pos.y = *(int*) &q.y;
		*(int*) &s->pos.z = *(int*) &q.z;
		*(int*) &s->rot.x = *(int*) &rot.x;
		*(int*) &s->rot.y = *(int*) &rot.y;
		*(int*) &s->rot.z = *(int*) &rot.z;
	}
	d2_SelectedBuilding = (char*) entity;
	d3_FocusedEntityObject = entity->obj;
}
