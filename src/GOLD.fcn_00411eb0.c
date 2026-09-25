// FUNCTION: GOLD 0x411eb0
// SIZE: 334

#include <math.h>

// SIZE 0x50
typedef struct {
	float x;
	float y;
	float z;
	char pad[0x44];
} P411eb0;

// SIZE 0x10
typedef struct {
	float x;
	float y;
	float z;
	float w;
} P411eb0c;

typedef P411eb0* (__cdecl* Corners411eb0)(char* obj, char* m, char* p);

extern float g_6628a8;
void __cdecl fcn_00439870(char* obj, char* cam, int flag);

char __cdecl fcn_00411eb0(char* obj, char* cam, float* center, float* radius)
{
	char r;
	char* m;
	P411eb0* p;
	P411eb0* q;
	P411eb0c c;
	float d;
	float dx;
	float dy;
	float dz;
	int i;

	r = 0;
	if (obj != 0 && (center != 0 || radius != 0) && *(int*) (*(char**) (obj + 0x1ec) + 0x104) != 0) {
		m = *(char**) (obj + 0x1ec) + 0xf4;
		fcn_00439870(obj, cam, 0);
		p = (*(Corners411eb0*) (*(char**) (m + 0x10) + 0x1f4))(obj, m, *(char**) (obj + 0x1ec) + 8);
		if (p != 0) {
			c.x = p[0].x;
			c.y = p[0].y;
			c.z = p[0].z;
			q = p + 1;
			for (i = 1; i < 8; i++) {
				c.x += q->x;
				c.y += q->y;
				c.z += q->z;
				q++;
			}
			c.x *= 0.125f;
			c.y *= 0.125f;
			c.z *= 0.125f;
			c.w = g_6628a8;
			for (i = 0; i < 8; i++) {
				dx = c.x - p[i].x;
				dy = c.y - p[i].y;
				dz = c.z - p[i].z;
				d = dz * dz + dy * dy + dx * dx;
				if (!(c.w > d)) {
					c.w = d;
				}
			}
			r = 1;
			c.w = (float) sqrt(c.w);
			if (radius != 0) {
				*radius = c.w;
			}
			if (center != 0) {
				center[0] = c.x;
				center[1] = c.y;
				center[2] = c.z;
			}
		}
	}
	return r;
}
