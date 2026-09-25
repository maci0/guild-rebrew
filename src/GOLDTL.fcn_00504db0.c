#include <math.h>

unsigned char* __cdecl gm_StartFilteredEntitySearch(int, ...);
unsigned char* __cdecl gm_AddObjekt(void);
int __cdecl gm_CheckEntityType(unsigned char* geb);
int __cdecl fcn_00505340(unsigned char* geb);

// FUNCTION: GOLDTL 0x00504db0
// SIZE: 181
unsigned char* __cdecl fcn_00504db0(unsigned char* self, int kind)
{
	float best;
	unsigned char* r;
	unsigned char* e;
	float* a;
	float* b;
	float dx;
	float dy;
	float dz;
	float d;

	best = 1e8f;
	r = 0;
	for (e = gm_StartFilteredEntitySearch(1, 6); e != 0; e = gm_AddObjekt()) {
		if (gm_CheckEntityType(e) != 0) {
			continue;
		}
		if (fcn_00505340(e) != 0) {
			continue;
		}
		a = *(float**) (e + 0x61);
		if (a == 0 || e == self || *e != kind || *(unsigned short*) (e + 0x27) != 0xffff) {
			continue;
		}
		b = *(float**) (self + 0x61);
		dx = a[0x13] - b[0x13];
		dy = a[0x14] - b[0x14];
		dz = a[0x15] - b[0x15];
		d = (float) sqrt(dz * dz + dy * dy + dx * dx);
		if (d < best) {
			best = d;
			r = e;
		}
	}
	return r;
}
