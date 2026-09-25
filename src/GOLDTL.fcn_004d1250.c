// FUNCTION: GOLD 0x004d0200
// SIZE: 199
// FUNCTION: GOLDTL 0x4d1250
// SIZE: 199

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

extern char* g_67a370;

void __cdecl fcn_00455350(char*, char*, float*);
char __cdecl fcn_0045b990(int, float*, int*, int*, int*);
ent2c* __cdecl fcn_004ceac0(char*, char*);
int __cdecl fcn_004c67c0(int, ent2c*);

int __cdecl fcn_004d1250(char* rec, char* e, char* obj)
{
	float v[4];
	ent2c l;
	ent2c* r;
	int h;
	int x;
	int y;
	int z;

	h = *(int*) (g_67a370 + 0xb0);
	if (obj == 0 || e == 0 || rec == 0)
		return -1;
	fcn_00455350(obj, obj + 0x4c, v);
	if (fcn_0045b990(h, v, &x, &y, &z) == 0)
		return -1;
	r = fcn_004ceac0(rec, e);
	if (r == 0)
		return -1;
	r->fc = 0;
	l = *r;
	l.id = *(int*) (e + 4);
	l.f4 = 3;
	*(int*) l.name = x;
	*(int*) (l.name + 4) = y;
	return fcn_004c67c0(*(int*) (rec + 0x10), &l);
}
