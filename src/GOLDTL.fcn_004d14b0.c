// FUNCTION: GOLDTL 0x4d14b0
// SIZE: 190

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

char __cdecl fcn_0045b990(int, float*, int*, int*, int*);
int __cdecl fcn_004d31d0(char*, int, int, int, int*, int*);
ent2c* __cdecl fcn_004ceac0(char*, char*);
int __cdecl fcn_004c67c0(int, ent2c*);

int __cdecl fcn_004d14b0(char* rec, char* e)
{
	int a;
	int b;
	ent2c l;
	ent2c* r;
	int c;
	int h;

	h = *(int*) (g_67a370 + 0xb0);
	if (fcn_0045b990(h, (float*) (*(char**) (*(char**) (e + 0x184) + 0x34) + 0x4c), &c, &a, &b) != 0 &&
	    fcn_004d31d0(e, c, a, 8, &c, &a) != 0) {
		r = fcn_004ceac0(rec, e);
		r->fc = 0;
		l = *r;
		l.id = *(int*) (e + 4);
		l.f4 = 7;
		*(int*) l.name = c;
		*(int*) (l.name + 4) = a;
		return fcn_004c67c0(*(int*) (rec + 0x10), &l);
	}
	return -1;
}
