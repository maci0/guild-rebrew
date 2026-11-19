#include <math.h>
#include "client_data.h"









extern float g_6628a0;
extern float g_6628a8;

void* __cdecl gm_StartFilteredEntitySearch(int, ...);
unsigned char* __cdecl fcn_00504c90(unsigned char*, int);
void __cdecl fcn_00546190(char*);
void __cdecl d3_TransformPoint(char*, float*, float*);

/* ADDRESS: GOLDTL 0x0056ce70 */
void __cdecl fcn_0056ce70(char* obj)
{
	float posA[4];
	float posB[4];
	double d;
	pos14_7f4c00* p;
	int i;
	char* a;
	char* b;
	unsigned char* e;
	unsigned char* target;

	for (i = 0; i < 0x10; i++) {
		*(int*) (obj + 0xb8 + i * 4) = -1;
	}
	p = (pos14_7f4c00*) (obj + 0x52);
	*p = gm_GameTime;



	p = (pos14_7f4c00*) (obj + 0x60);
	*p = gm_GameTime;



	*(char*) (obj + 0xb4) = 0;
	e = gm_StartFilteredEntitySearch(1, 1, *(int*) (obj + 0xac));
	if (e == 0) {
		fcn_00546190(obj);
		return;
	}
	target = fcn_00504c90(e, 3);
	if (target != 0) {
		a = *(char**) (e + 0x61);
		d3_TransformPoint(a, (float*) (a + 0x4c), posA);
		b = *(char**) (target + 0x61);
		d3_TransformPoint(b, (float*) (b + 0x4c), posB);
		d = sqrt((double) ((posA[2] - posB[2]) * (posA[2] - posB[2])
			+ (posA[1] - posB[1]) * (posA[1] - posB[1])
			+ (posA[0] - posB[0]) * (posA[0] - posB[0]))) * 0.001;
	} else {
		d = g_6628a0;
	}
	if (d > 1.5) {
		d = 1.5;
	}
	d *= *(int*) (obj + 0xb0);
	*(int*) (obj + 0x84) = -1;
	*(int*) (obj + 0xb0) = (int) d;
}
