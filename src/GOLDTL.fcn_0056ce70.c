#include <math.h>

typedef struct Res_7f4c00 {
	int a;
	int b;
	int c;
	short d;
	short pad;
} Res_7f4c00;

extern Res_7f4c00 g_7f4c00;
extern float g_6628a0;
extern float g_6628a8;

void* __cdecl fcn_00503fe0(int, ...);
unsigned char* __cdecl fcn_00504c90(unsigned char*, int);
void __cdecl fcn_00546190(char*);
void __cdecl fcn_00455350(char*, float*, float*);

/* ADDRESS: GOLDTL 0x0056ce70 */
void __cdecl fcn_0056ce70(char* obj)
{
	float v1[4];
	float v2[4];
	double d;
	Res_7f4c00* p;
	int i;
	char* a;
	char* b;
	unsigned char* e;
	unsigned char* target;

	for (i = 0; i < 0x10; i++) {
		*(int*) (obj + 0xb8 + i * 4) = -1;
	}
	p = (Res_7f4c00*) (obj + 0x52);
	p->a = g_7f4c00.a;
	p->b = g_7f4c00.b;
	p->c = g_7f4c00.c;
	p->d = g_7f4c00.d;
	p = (Res_7f4c00*) (obj + 0x60);
	p->a = g_7f4c00.a;
	p->b = g_7f4c00.b;
	p->c = g_7f4c00.c;
	p->d = g_7f4c00.d;
	*(char*) (obj + 0xb4) = 0;
	e = fcn_00503fe0(1, 1, *(int*) (obj + 0xac));
	if (e == 0) {
		fcn_00546190(obj);
		return;
	}
	target = fcn_00504c90(e, 3);
	if (target == 0) {
		d = (double) g_6628a0;
	} else {
		a = *(char**) (e + 0x61);
		b = *(char**) (target + 0x61);
		fcn_00455350(a, (float*) (a + 0x4c), v1);
		fcn_00455350(b, (float*) (b + 0x4c), v2);
		d = sqrt((double) ((v1[2] - v2[2]) * (v1[2] - v2[2])
			+ (v1[1] - v2[1]) * (v1[1] - v2[1])
			+ (v1[0] - v2[0]) * (v1[0] - v2[0]))) * 0.001;
		if (d > 1.5) {
			d = 1.5;
		}
	}
	*(int*) (obj + 0xb0) = (int) (d * *(int*) (obj + 0xb0));
	*(int*) (obj + 0x84) = -1;
}
