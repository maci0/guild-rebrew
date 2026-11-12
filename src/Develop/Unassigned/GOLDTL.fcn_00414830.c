#include "Develop/Units/d3/d3_camera.h"
typedef struct {
	float x;
	float y;
	float z;
	char pad[0x44];
} P414830;

typedef P414830* (__cdecl* Corners414830)(char* obj, char* m, char* p);

typedef struct {
	char pad[0x1f0];
	Corners414830 get;
} Vtbl414830;

void __cdecl fcn_00438100(char* obj, char* cam, int force);
void __cdecl fcn_00414830(float* lo, float* hi, char* entity);

/* ADDRESS: GOLDTL 0x00414830 */
void __cdecl fcn_00414830(float* lo, float* hi, char* entity)
{
	P414830* p;
	Vtbl414830* vt;
	char* child;
	int i;

	if (*(char**) (entity + 0x1cc) == 0) {
		return;
	}
	if ((*(unsigned char*) (entity + 0x216) & 0x20) == 0) {
		fcn_00438100(entity, g_6b8014, 0);
	}
	vt = (Vtbl414830*) (*(char**) (*(char**) (entity + 0x1cc) + 0x318));
	p = vt->get(entity, *(char**) (entity + 0x1cc), *(char**) (entity + 0x1ec) + 8);
	if (p != 0) {
		for (i = 8; i != 0; p++, i--) {
			*lo = (*lo < p->x) ? *lo : p->x;
			lo[1] = (p->y > lo[1]) ? lo[1] : p->y;
			lo[2] = (p->z > lo[2]) ? lo[2] : p->z;
			*hi = (*hi > p->x) ? *hi : p->x;
			hi[1] = (p->y < hi[1]) ? hi[1] : p->y;
			hi[2] = (p->z < hi[2]) ? hi[2] : p->z;
		}
	}
	for (child = *(char**) (entity + 0x200); child != 0; child = *(char**) (child + 0x1f4)) {
		fcn_00414830(lo, hi, child);
	}
}
