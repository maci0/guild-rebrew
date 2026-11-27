#include "Develop/Units/d3/d3_camera.h"

extern float g_fc5348;
extern float g_fc2944;

void __cdecl fcn_00458b10(char* object, char* camera, float* position, float* out);
void __cdecl d3_UpdateObjectCameraTransform(char* object, char* parent, int force);

/* ADDRESS: GOLD 0x004486e0 */
unsigned char __cdecl d3_GetObjectScreenRect(char* e, int* rect)
{
	float v[4];
	float inv;
	float x;
	float y;
	float r;
	char* d;
	char* owner;
	char* camera;
	float* p;
	float* pts;
	int n;
	int px;
	int py;
	int x0;
	int x1;
	int y0;
	int y1;
	int t;

	if (rect == 0 || e == 0) {
		return 0;
	}
	if (*(int*) (e + 0x218) == 0) {
		fcn_00458b10(e, d3_ActiveCamera, (float*) (e + 0x4c), v);
		inv = 1.0f / v[2];
		x = g_fc5348 * v[0] * inv + *(float*) 0xfe75fc;
		y = g_fc2944 * v[1] * inv + *(float*) 0xfe7604;
		r = g_fc5348 * *(float*) (e + 0x68) * inv * 0.5f;
		rect[0] = (int) (x - r);
		rect[2] = (int) (r + x);
		rect[1] = (int) (y - r);
		rect[3] = (int) (r + y);
		return 1;
	}
	d = *(char**) (e + 0x1ec);
	if (d == 0 || (d[0x96d] & 0x40) != 0) {
		return 0;
	}
	owner = *(char**) (e + 0x1cc);
	if (owner == 0 || *(int*) (owner + 0x10) == 0) {
		return 0;
	}
	camera = d3_ActiveCamera;
	d3_UpdateObjectCameraTransform(e, (e[0x210] & 0x80) ? 0 : camera, 0);
	pts = (float*) (*(int (__cdecl **)(char*, char*, char*)) (*(char**) (owner + 0x10) + 0x1f4))(e, owner, *(char**) (e + 0x1ec) + 0x48);
	rect[1] = 0x10000;
	rect[0] = 0x10000;
	rect[3] = -0x10000;
	rect[2] = -0x10000;
	p = pts + 1;
	n = 8;
	do {
		inv = 1.0f / p[1];
		px = (int) (g_fc5348 * p[-1] * inv + *(float*) 0xfe75fc);
		x0 = rect[0] < px ? rect[0] : px;
		rect[0] = x0;
		x1 = rect[2] > px ? rect[2] : px;
		rect[2] = x1;
		py = (int) (g_fc2944 * p[0] * inv + *(float*) 0xfe7604);
		y0 = rect[1] < py ? rect[1] : py;
		rect[1] = y0;
		y1 = rect[3] > py ? rect[3] : py;
		rect[3] = y1;
		p += 0x14;
	} while (--n);
	t = *(int*) 0xfc2930;
	if (x0 > t)
		t = x0;
	rect[0] = t;
	t = *(int*) 0xfc2938 - 1;
	if (x1 < t)
		t = x1;
	rect[2] = t;
	y0 = y0 > *(int*) 0xfc2934 ? y0 : *(int*) 0xfc2934;
	rect[1] = y0;
	t = *(int*) 0xfc293c - 1;
	y1 = y1 < t ? y1 : t;
	rect[3] = y1;
	return 1;
}
