#include <math.h>
#include "Develop/Units/d3/d3_camera.h"

/* The effect node's world matrix sits at 0x18c; the three terms of each
   rotated component pick one matrix column out of it. */
struct node98 {
	char pad0[0x18c];
	float m[16];
};

extern float d3_UnitAxisVectors[3];
extern float g_662b08;

extern void __cdecl d3_SetObjectRotation(void*, float*);
extern void __cdecl d3_SetNodePosition(void*, float*);
extern void __cdecl d3_NormalizeVector(float*);
extern float __cdecl d3_WrapYawDelta(int, int);
extern void* __cdecl d3_GetDefaultParticleColor(void);
extern void __stdcall D3DXMatrixTranspose(float*, float*);
extern int __cdecl d2_GetControlValue(int);
extern void __cdecl d3_UpdateCannonAimMatrices(char*);

/* ADDRESS: GOLDTL 0x00587a50 */
/* ADDRESS: GOLDDE 0x0056d710 */
void __cdecl d3_UpdateCannonAimCamera(char* o)
{
	float f;
	float d1;
	float z;
	int iv;
	double iv_scale;
	float u;
	float s;
	float v[8];
	float a[3];
	float m[16];
	void* c;
	int i;

	a[1] = *(float*) (o + 0x14);
	a[2] = 0.0f;
	a[0] = 0.0f;
	d3_SetObjectRotation(*(void**) (o + 0x98), a);

	v[4] = *(float*) (o + 0x10);
	v[5] = 0.0f;
	v[6] = 0.0f;
	for (i = 0; i < 3; i++) {
		d3_SetObjectRotation(*(void**) (o + 0x8c + i * 4), v + 4);
	}

	v[4] = 0.0f;
	v[5] = 0.0f;
	v[6] = 0.0f;
	v[7] = 0.0f;

	c = d3_GetDefaultParticleColor();
	D3DXMatrixTranspose(m, ((struct node98*) *(void**) (o + 0x98))->m);
	v[2] = 0.0f;
	v[4] = 0.0f;
	v[3] = d3_WrapYawDelta((int) d3_UnitAxisVectors, (int) c) - g_662b08 -
	       *(float*) (o + 0x14);
	d3_SetObjectRotation(*(void**) (o + 0x9c), v + 2);

	if (*(int*) (o + 0x7c) == 0) {
		d3_UpdateCannonAimMatrices(o);
	}

	v[0] = d3_UnitAxisVectors[0] * ((struct node98*) *(void**) (o + 0x98))->m[0] +
	       (d3_UnitAxisVectors[1] * ((struct node98*) *(void**) (o + 0x98))->m[4] +
	        d3_UnitAxisVectors[2] * ((struct node98*) *(void**) (o + 0x98))->m[8]);
	v[1] = d3_UnitAxisVectors[0] * ((struct node98*) *(void**) (o + 0x98))->m[1] +
	       (d3_UnitAxisVectors[1] * ((struct node98*) *(void**) (o + 0x98))->m[5] +
	        d3_UnitAxisVectors[2] * ((struct node98*) *(void**) (o + 0x98))->m[9]);
	v[2] = d3_UnitAxisVectors[0] * ((struct node98*) *(void**) (o + 0x98))->m[2] +
	       (d3_UnitAxisVectors[1] * ((struct node98*) *(void**) (o + 0x98))->m[6] +
	        d3_UnitAxisVectors[2] * ((struct node98*) *(void**) (o + 0x98))->m[10]);
	d3_NormalizeVector(v);

	v[4] = *(float*) o - v[0] * 30.0f;
	v[5] = *(float*) (o + 4) - v[1] * 30.0f + 20.0f;
	v[6] = *(float*) (o + 8) - (float) (v[2] * 30.0f);
	v[0] = *(float*) (o + 0x10);
	v[1] = *(float*) (o + 0x14);
	v[2] = *(float*) (o + 0x18);

	d1 = (v[0] - -0.61086524f) / ((double) 0.7853982f - (double) -0.61086524f);
	f = (v[0] - -0.2617994f) / ((double) 0.7853982f - (double) -0.2617994f);
	iv = d2_GetControlValue(*(int*) (o + 0xb4));
	iv_scale = (float) iv * 0.01f;
	s = (0.5f - 0.25f * iv_scale) * f * *(float*) (o + 0x20) + d1;
	s = s * 30.0f + v[5];
	u = 1.0f - *(float*) (o + 0x20);
	u = 0.3f * sqrt(u) + 0.7f * u;
	u = u + iv_scale * *(float*) (o + 0x20) * 0.5f;
	v[0] = u * 0.61086524f * f + -0.61086524f;
	z = *(float*) (o + 0x2c);
	u = iv_scale * f * 0.5f + 1.0f;
	u = (u * 1450.0f * f + 50.0f) * *(float*) (o + 0x20);

	v[5] = u * *(float*) (o + 0x28) + s;
	v[4] = v[4] + u * *(float*) (o + 0x24);
	v[6] = v[6] + u * z;
	d3_SetNodePosition(d3_ActiveCamera, v + 4);
	d3_SetObjectRotation(d3_ActiveCamera, v);

	if (*(int*) (o + 0x7c) == 0) {
		d3_UpdateCannonAimMatrices(o);
		if (*(int*) (o + 0x7c) == 0) {
			goto tail;
		}
	}
	if (*(unsigned int*) (o + 0x78) + 0x54 > *(unsigned int*) (o + 0x6c)) {
		if (*(unsigned int*) (o + 0x78) + 4 > *(unsigned int*) (o + 0x6c)) {
			f = (float) (unsigned int) (*(unsigned int*) (o + 0x6c) -
						    *(unsigned int*) (o + 0x78)) *
			    0.25f;
		} else {
			u = 1.0f - (float) (unsigned int) (*(unsigned int*) (o + 0x6c) -
							   *(unsigned int*) (o + 0x78) - 4) *
					0.0125f;
			f = u * u;
		}
		v[1] = 0.0f;
		v[0] = *(float*) (o + 0x24);
		v[2] = *(float*) (o + 0x2c);
		d3_NormalizeVector(v);
		u = 1.0f;
		if (*(float*) (o + 0x10) > 0.0f) {
			u = 1.0f - *(float*) (o + 0x10) / 0.7853982f;
		}
		u = u * f * 50.0f;
		v[0] = *(float*) o - u * v[0];
		v[1] = *(float*) (o + 4) - u * v[1];
		v[2] = *(float*) (o + 8) - u * v[2];
		d3_SetNodePosition(*(void**) (o + 0x98), v);
		v[4] = -70.0f + u * d3_UnitAxisVectors[0];
		v[5] = -50.0f + u * d3_UnitAxisVectors[1];
		v[6] = 120.0f + u * d3_UnitAxisVectors[2];
		d3_SetNodePosition(*(void**) (o + 0x9c), v + 4);
		return;
	}
	*(int*) (o + 0x7c) = 0;
	*(int*) (o + 0x78) = 0;
	d3_SetNodePosition(*(void**) (o + 0x9c), (float*) 0x665f28);
tail:
	d3_SetNodePosition(*(void**) (o + 0x98), (float*) o);
}
