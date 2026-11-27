

#include <math.h>

#define MAXV(a, b) ((a) > (b) ? (a) : (b))
#define MINV(a, b) ((b) < (a) ? (b) : (a))

#include "Develop/Units/d3/d3_camera.h"
extern float g_662d40[3];
extern float g_6a2558;
extern float g_6a2560;
extern float d3_CameraHeightFraction;
extern int g_6a256c;
extern int d3_ActiveCameraAnimation;
extern int d3_CameraAnimating;

int __cdecl d3_GetObjectVerticalBounds(char* e, float* lo, float* hi);
float* __stdcall D3DXMatrixTranspose(float*, const float*);
void __cdecl d3_TransformPoint(char*, char*, float*);
float __cdecl d3_SampleAverageTerrainHeight(float* p);
void __cdecl d3_FreeObjectAnimation(char* cam);
void __cdecl d3_AnimateObjectTransform(char* cam, float* a, float* b, int d, int e);

void __cdecl d3_AnimateCameraToObject(char* entity)
{
	float lo;
	float hi;
	float w[4];
	float r[4];
	float t[3];
	float p[4];
	float m[16];
	float offsetX;
	float offsetY;
	float offsetZ;
	float dir[4];
	float dy;
	float h;
	float dx;
	float dz;
	float len;
	float n;
	char* cam;

	d3_GetObjectVerticalBounds(entity, &lo, &hi);
	D3DXMatrixTranspose(m, (float*) ((char*) d3_ActiveCamera + 0x18c));
	offsetX = g_662d40[0] * -600.0f;
	offsetY = g_662d40[1] * -600.0f;
	offsetZ = g_662d40[2] * -600.0f;
	r[0] = m[8] * offsetZ + m[4] * offsetY + m[0] * offsetX;
	r[1] = m[9] * offsetZ + m[5] * offsetY + m[1] * offsetX;
	r[2] = m[10] * offsetZ + m[6] * offsetY + m[2] * offsetX;
	d3_TransformPoint(entity, entity + 0x4c, p);
	w[0] = p[0] + r[0];
	w[1] = p[1] + r[1];
	w[2] = p[2] + r[2];
	h = d3_SampleAverageTerrainHeight(w);
	w[1] = h + ((g_6a2560 - g_6a2558) * d3_CameraHeightFraction + g_6a2558);
	dir[1] = w[1] - p[1];
	d3_GetObjectVerticalBounds(entity, &lo, &hi);
	n = r[1] / ((hi - lo) * 0.5f + dir[1]);
	w[0] = (float)(w[0] - (n * r[0] - r[0] * 1.8));
	w[2] = (float)(w[2] - (n * r[2] - r[2] * 1.8));
	cam = (char*) d3_ActiveCamera;
	t[0] = *(float*) (cam + 0x84);
	t[1] = *(float*) (cam + 0x88);
	t[2] = *(float*) (cam + 0x8c);
	d3_FreeObjectAnimation(cam);
	d3_ActiveCameraAnimation = 0;
	d3_CameraAnimating = 0;
	h = d3_SampleAverageTerrainHeight(w);
	w[1] = h + ((g_6a2560 - g_6a2558) * d3_CameraHeightFraction + g_6a2558);
	cam = (char*) d3_ActiveCamera;
	dx = w[0] - *(float*) (cam + 0x4c);
	dy = w[1] - *(float*) (cam + 0x50);
	dz = w[2] - *(float*) (cam + 0x54);
	n = (float) g_6a256c;
	len = (float) sqrt(dz * dz + dy * dy + dx * dx) * n * 0.0005f;
	d3_AnimateObjectTransform(cam, w, t, (int) MINV(MAXV(n, len), (float) (g_6a256c * 3)), 0x68);
}
