


extern int g_67a370;
#include "Develop/Units/d3/d3_camera.h"

void __cdecl d3_InvalidateSubTreeFlags(char*, int);
void __cdecl d3_InvalidateSceneRenderCache(unsigned char);
void __cdecl d3_BuildEulerRotationMatrix(float*, char*);
void __cdecl d3_TraverseSceneObjects(int, char*, int, void*);
void __cdecl d3_ClearAuxSlotState(void);

void __cdecl d3_SetObjectRotation(char* o, int* v)
{
	float n[4];
	float* p;

	d3_InvalidateSubTreeFlags(o, 1);
	p = (float*) (o + 0x84);
	*(int*) p = v[0];
	*(int*) (o + 0x88) = v[1];
	*(int*) (o + 0x8c) = v[2];
	if (*(int*) (o + 0x218) != 3) {
		d3_BuildEulerRotationMatrix(p, o + 0x18c);
		d3_TraverseSceneObjects(g_67a370, o, 0xc0, d3_ClearAuxSlotState);
		return;
	}
	if (o == ((char*)d3_ActiveCamera)) {
		d3_InvalidateSceneRenderCache(0);
	}
	n[0] = -p[0];
	n[1] = -*(float*) (o + 0x88);
	n[2] = -*(float*) (o + 0x8c);
	d3_BuildEulerRotationMatrix(n, o + 0x18c);
}
