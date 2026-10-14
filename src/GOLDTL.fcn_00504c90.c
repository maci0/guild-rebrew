


#include <math.h>

// SIZE 0x10
typedef struct {
	float x;
	float y;
	float z;
	float w;
} Vec4;

extern unsigned char* g_868050;

unsigned char* __cdecl gm_StartFilteredEntitySearch(int mode, int kind);
unsigned char* __cdecl gm_AddObjekt(void);
int __cdecl gm_CheckEntityType(unsigned char* e);
int __cdecl fcn_00505340(unsigned char* e);
void __cdecl fcn_00455350(char* view, char* pos, Vec4* out);

unsigned char* __cdecl fcn_00504c90(unsigned char* me, int kind)
{
	float best_d;
	Vec4 a;
	Vec4 b;
	unsigned char* best;
	unsigned char* e;
	unsigned char* rec;
	float dx;
	float dy;
	float dz;
	float d;

	best = 0;
	best_d = 1.0e8f;
	if (me == 0 || *(char**) (me + 0x61) == 0) {
		return 0;
	}
	for (e = gm_StartFilteredEntitySearch(1, 6); e != 0; e = gm_AddObjekt()) {
		rec = g_868050 + *e * 589;
		if (!gm_CheckEntityType(e) && !fcn_00505340(e) && *(char**) (e + 0x61) != 0 && e != me && *rec == kind) {
			fcn_00455350(*(char**) (e + 0x61), *(char**) (e + 0x61) + 0x4c, &a);
			fcn_00455350(*(char**) (me + 0x61), *(char**) (me + 0x61) + 0x4c, &b);
			dx = a.x - b.x;
			dy = a.y - b.y;
			dz = a.z - b.z;
			d = (float) sqrt(dx * dx + dy * dy + dz * dz);
			if (d < best_d) {
				best_d = d;
				best = e;
			}
		}
	}
	return best;
}
