// FUNCTION: GOLD 0x004bbe70
// SIZE: 144
// FUNCTION: GOLDTL 0x4bc380
// SIZE: 144

typedef struct {
	char* obj;
	int f4;
	int f8;
	int fc;
	float pos[3];
} slot1c;
// SIZE 0x1c

extern char g_681414[];
extern char g_68140c[];

char* __cdecl fcn_004bca30(char*);
void __cdecl fcn_00455350(char*, char*, float*);
char* __cdecl fcn_00403b90(char*, float*);
void __cdecl fcn_0040c120(char*, int, int);

void __cdecl fcn_004bc380(slot1c* s)
{
	float v[4];
	char* o;

	o = fcn_004bca30(g_681414);
	if (o == 0)
		return;
	fcn_00455350(o, o + 0x4c, v);
	s->obj = fcn_00403b90(g_68140c, v);
	if (s->obj == 0)
		return;
	*(float*) (s->obj + 0x1a0) = 1.5f;
	s->pos[0] = v[0];
	s->pos[1] = v[1];
	s->pos[2] = v[2];
	s->f4 = 3;
	*(int*) (s->obj + 4) = 2;
	*(int*) (*(char**) (s->obj + 0x34) + 0x224) = 0;
	fcn_0040c120(s->obj, 0x38, 1);
}
