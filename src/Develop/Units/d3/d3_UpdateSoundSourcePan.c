#include <math.h>

#include "Develop/Units/d3/d3_camera.h"
extern float d3_UnitAxisVectors[3];

float* __stdcall D3DXMatrixTranspose(float*, const float*);
void __cdecl d3_TransformPoint(char*, char*, float*);
float __cdecl d3_SignedPlanarAngle(float*, float*);
void __cdecl sb_SetVoicePan(void*, int);


/* Pans a sound source by the angle between the camera's forward axis and
 * the direction to the emitting object. */
/* ADDRESS: GOLDTL 0x00418fb0 */
void __cdecl d3_UpdateSoundSourcePan(char* src)
{
	float pos[4];
	float fwd[4];
	float dir[4];
	float m[16];

	if (src == 0 || *(char**) (src + 0x38) == 0 || *(void**) (src + 0x34) == 0) {
		return;
	}
	D3DXMatrixTranspose(m, (float*) (((char*)d3_ActiveCamera) + 0x18c));
	fwd[0] = d3_UnitAxisVectors[0] * m[0] + d3_UnitAxisVectors[1] * m[4] + d3_UnitAxisVectors[2] * m[8];
	fwd[1] = d3_UnitAxisVectors[0] * m[1] + d3_UnitAxisVectors[1] * m[5] + d3_UnitAxisVectors[2] * m[9];
	fwd[2] = d3_UnitAxisVectors[0] * m[2] + d3_UnitAxisVectors[1] * m[6] + d3_UnitAxisVectors[2] * m[10];
	d3_TransformPoint(*(char**) (src + 0x38), *(char**) (src + 0x38) + 0x4c, pos);
	dir[0] = pos[0] - *(float*) (((char*)d3_ActiveCamera) + 0x4c);
	dir[1] = pos[1] - *(float*) (((char*)d3_ActiveCamera) + 0x50);
	dir[2] = pos[2] - *(float*) (((char*)d3_ActiveCamera) + 0x54);
	sb_SetVoicePan(*(void**) (src + 0x34), (int) (sin(d3_SignedPlanarAngle(dir, fwd)) * 63.5 + 63.0));
}
