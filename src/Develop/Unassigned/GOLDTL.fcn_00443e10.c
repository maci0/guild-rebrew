#include "Develop/Units/d3/d3_camera.h"
extern float g_10432a4, d3_ProjectionScaleY, d3_ViewportCenterX, g_1052bc8;
extern int g_1042570, g_1042574, d3_ViewportRight, d3_ViewportBottom;
typedef struct Vec3 {
	float x;
	float y;
	float z;
} Vec3;

void __cdecl d3_TransformPointToRef(char*, char*, Vec3*, Vec3*);
void __cdecl d3_UpdateObjectCameraTransform(char*, char*, char);

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
		sx = p[0] * g_10432a4 * t + d3_ViewportCenterX;
		sy = p[1] * d3_ProjectionScaleY * t + g_1052bc8;
		d = *(float*) (obj + 0x68) * g_10432a4 * 0.5f * t;
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
		ix = (int) (g_10432a4 * rec[-1] * t + d3_ViewportCenterX);
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
