// FUNCTION: GOLD 0x004d02d0
// SIZE: 161
// FUNCTION: GOLDTL 0x4d1320
// SIZE: 161

#include <string.h>

typedef struct {
	int id;
	int f4;
	int f8;
	char fc;
	char padd[3];
	char name[0x10];
	int f20;
	int f24;
	int f28;
} ent2c;
// SIZE 0x2c

extern int g_67a370;

void __cdecl fcn_004ce610(char*);
void __cdecl fcn_00455350(char*, char*, float*);
char __cdecl fcn_0045b990(int, float*, int*, int*, int*);
ent2c* __cdecl fcn_004ceac0(char*, char*);

int __cdecl fcn_004d1320(char* rec, char* e, char* obj)
{
	float v[4];
	ent2c* r;
	int h;
	int a;
	int b;
	int c;

	h = *(int*) (((char*)g_67a370) + 0xb0);
	fcn_004ce610(e);
	fcn_00455350(obj, obj + 0x4c, v);
	if (fcn_0045b990(h, v, &c, &a, &b) == 0)
		return 0;
	r = fcn_004ceac0(rec, e);
	r->fc = 0;
	strcpy(r->name, obj);
	r->id = *(int*) (e + 4);
	r->f4 = 4;
	r->f20 = c;
	r->f24 = a;
	return 1;
}
