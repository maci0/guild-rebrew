#include "Develop/Units/d3/d3_camera.h"

typedef struct Vec3 {
	float x;
	float y;
	float z;
} Vec3;

extern float g_fc5348;
extern float g_fc2944;
extern float d3_ProjectionDist, d3_ProjectionScaleY, d3_ViewportCenterX, g_1052bc8;
extern int g_1042570, g_1042574, d3_ViewportRight, d3_ViewportBottom;

void __cdecl d3_TransformPointToView(char* object, char* camera, float* position, float* out);
void __cdecl d3_TransformPointToRef(char*, char*, Vec3*, Vec3*);
void __cdecl d3_UpdateObjectCameraTransform(char* object, char* parent, int force);

#if defined(REBREW_GOLD)

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
		d3_TransformPointToView(e, d3_ActiveCamera, (float*) (e + 0x4c), v);
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

#else

/* Projects an object's bounds into screen space and fills a left/top/right/
 * bottom rectangle. */
/* ADDRESS: GOLDTL 0x00443e10 */
char __cdecl d3_GetObjectScreenRect(char* obj, int* rc)
{
	float p[4];
	float t;
	float sx;
	float sy;
	float d;
	char* cam;
	char* sub;
	char* list;
	float* rec;
	unsigned char b;
	int i;
	int ix;
	int iy;

	if (rc == 0 || obj == 0) {
		return 0;
	}
	if (*(int*) (obj + 0x218) == 0) {
		d3_TransformPointToRef(obj, d3_ActiveCamera, (Vec3*) (obj + 0x4c), (Vec3*) p);
		t = 1.0f / p[2];
		sx = p[0] * d3_ProjectionDist * t + d3_ViewportCenterX;
		sy = p[1] * d3_ProjectionScaleY * t + g_1052bc8;
		d = *(float*) (obj + 0x68) * d3_ProjectionDist * 0.5f * t;
		rc[0] = (int) (sx - d);
		rc[2] = (int) (sx + d);
		rc[1] = (int) (sy - d);
		rc[3] = (int) (sy + d);
		return 1;
	}
	if (*(int*) (obj + 0x1ec) == 0) {
		return 0;
	}
	if (*(unsigned char*) (*(int*) (obj + 0x1ec) + 0x163d) & 0x40) {
		return 0;
	}
	sub = *(char**) (obj + 0x1cc);
	if (sub == 0) {
		return 0;
	}
	if (*(int*) (sub + 0x318) == 0) {
		return 0;
	}
	b = *(unsigned char*) (obj + 0x214) & 0x20;
	cam = b != 0 ? (char*) 0 : d3_ActiveCamera;
	d3_UpdateObjectCameraTransform(obj, cam, 0);
	list = (char*) ((int (__cdecl*) (char*, char*, char*)) (*(int**) (sub + 0x318))[0x7c])(obj, sub, *(char**) (obj + 0x1ec) + 0x48);
	rc[1] = 0x10000;
	rc[0] = 0x10000;
	rc[3] = -0x10000;
	rc[2] = -0x10000;
	rec = (float*) (list + 4);
	i = 8;
	do {
		t = 1.0f / rec[1];
		ix = (int) (d3_ProjectionDist * rec[-1] * t + d3_ViewportCenterX);
		rc[0] = rc[0] < ix ? rc[0] : ix;
		rc[2] = rc[2] > ix ? rc[2] : ix;
		iy = (int) (d3_ProjectionScaleY * rec[0] * t + g_1052bc8);
		rc[1] = rc[1] < iy ? rc[1] : iy;
		rc[3] = rc[3] > iy ? rc[3] : iy;
		rec += 0x14;
	} while (--i != 0);
	rc[0] = rc[0] > g_1042570 ? rc[0] : g_1042570;
	rc[2] = rc[2] < d3_ViewportRight - 1 ? rc[2] : d3_ViewportRight - 1;
	rc[1] = rc[1] > g_1042574 ? rc[1] : g_1042574;
	rc[3] = rc[3] < d3_ViewportBottom - 1 ? rc[3] : d3_ViewportBottom - 1;
	return 1;
}

#endif
