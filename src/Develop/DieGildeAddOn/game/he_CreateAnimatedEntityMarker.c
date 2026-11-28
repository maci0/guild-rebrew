#include <string.h>
typedef struct {
	unsigned char r;
	unsigned char g;
	unsigned char f0 : 1;
	unsigned char f1 : 7;
	unsigned char x;
} COLOR546590;

typedef struct {
	unsigned char b0;
	unsigned char f0 : 1;
	unsigned char r0 : 1;
	unsigned char f2 : 1;
	unsigned char f3 : 1;
	unsigned char f4 : 1;
	unsigned char r1 : 3;
	unsigned char pad2[6];
	unsigned char r2 : 1;
	unsigned char e : 1;
	unsigned char r3 : 6;
	unsigned char pad9[3];
} FLAGS546590;

typedef struct {
	int id;
	float pos[3];
	float f10;
	float rot[3];
	char pad20[0x38];
} FRAME546590;

extern float d3_ZeroVec4[4];

void __cdecl d3_TransformPoint(char* object, float* in, float* out);
int __cdecl d3_GetObjectVerticalBounds(char* e, float* lo, float* hi);
char* __cdecl d3_CreateSceneModelObject(int parent, float* pos, float* dir, char* name);
void __cdecl d3_ChangeObjectTransparency(char* a, char* b, COLOR546590 c);
void __cdecl d3_SetObjectColorRgb(char* p, unsigned char r, unsigned char g, unsigned char b);
int __cdecl d3_CreateObjectAnimation(char* obj, FLAGS546590 fl, int n, FRAME546590* frames);
int __cdecl he_ArrangeEntityMarkers(char* entity);

/* ADDRESS: GOLDTL 0x00546590 */
char* __cdecl he_CreateAnimatedEntityMarker(char* effectState, char* name, char* entity)
{
	FRAME546590 frames[2];
	FLAGS546590 flags;
	COLOR546590 color;
	float pos[4];
	float lo;
	float hi;
	char* obj;

	d3_TransformPoint(entity, (float*) (entity + 0x4c), pos);
	d3_GetObjectVerticalBounds(entity, &lo, &hi);
	pos[1] = hi;
	obj = d3_CreateSceneModelObject(0, pos, d3_ZeroVec4, name);
	*(char**) (effectState + 0xc) = obj;
	*(char**) (effectState + 8) = entity;
	if (obj != 0) {
		obj[0x214] &= 0x7f;
		obj[0x216] |= 3;
		obj[0x217] &= 0xfe;
		*(int*) (obj + 0x220) = 5;
		*(int*) &color = 0;
		color.f1 = 0;
		color.f0 = 1;
		color.r = 0x80;
		d3_ChangeObjectTransparency(obj, *(char**) (obj + 0x1cc), color);
		d3_SetObjectColorRgb(obj, 0xc0, 0xa0, 0x80);
		memset(&flags, 0, sizeof(flags));
		flags.e = 1;
		frames[0].id = 0x8c0;
		frames[0].rot[0] = 0.0f;
		frames[0].rot[1] = 0.0f;
		frames[0].rot[2] = 0.0f;
		frames[0].pos[0] = 0.0f;
		frames[0].pos[1] = 0.0f;
		frames[0].pos[2] = 0.0f;
		frames[1].pos[0] = 0.0f;
		frames[1].pos[1] = 0.0f;
		frames[1].pos[2] = 0.0f;
		frames[1].rot[0] = 0.0f;
		frames[1].rot[1] = 201.061935f;
		frames[1].rot[2] = 0.0f;
		d3_CreateObjectAnimation(obj, flags, 2, frames);
		he_ArrangeEntityMarkers(entity);
	}
	return obj;
}
