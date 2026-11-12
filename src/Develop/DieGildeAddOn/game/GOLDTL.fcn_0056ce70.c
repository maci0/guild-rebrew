#include <math.h>
#include "client_data.h"









extern float g_6628a0;
extern float g_6628a8;

void* __cdecl gm_StartFilteredEntitySearch(int, ...);
unsigned char* __cdecl fcn_00504c90(unsigned char*, int);
void __cdecl fcn_00546190(char*);
void __cdecl fcn_00455350(char*, float*, float*);

/* ADDRESS: GOLDTL 0x0056ce70 */
void __cdecl fcn_0056ce70(char* obj)
{
	float v1[4];
	float v2[4];
	float d;
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
	*p = g_7f4c00;



	p = (pos14_7f4c00*) (obj + 0x60);
	*p = g_7f4c00;



	*(char*) (obj + 0xb4) = 0;
	e = gm_StartFilteredEntitySearch(1, 1, *(int*) (obj + 0xac));
	if (e == 0) {
		fcn_00546190(obj);
		return;
	}
	target = fcn_00504c90(e, 3);
	if (target != 0) {
		a = *(char**) (e + 0x61);
		fcn_00455350(a, (float*) (a + 0x4c), v1);
		b = *(char**) (target + 0x61);
		fcn_00455350(b, (float*) (b + 0x4c), v2);
		d = sqrt((double) ((v1[2] - v2[2]) * (v1[2] - v2[2])
			+ (v1[1] - v2[1]) * (v1[1] - v2[1])
			+ (v1[0] - v2[0]) * (v1[0] - v2[0]))) * 0.001;
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
