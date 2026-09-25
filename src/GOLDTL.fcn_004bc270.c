// FUNCTION: GOLDTL 0x4bc270
// SIZE: 123

typedef struct {
	char* obj;
	int f4;
	int f8;
	int fc;
	float pos[3];
} slot1c;
// SIZE 0x1c

extern char g_6813e8[];

int __cdecl fcn_004bc7f0(float*);
char* __cdecl fcn_00403b90(char*, float*);
void __cdecl fcn_0040c120(char*, int, int);

void __cdecl fcn_004bc270(slot1c* s)
{
	float v[4];

	if (fcn_004bc7f0(v) == 0)
		return;
	s->obj = fcn_00403b90(g_6813e8, v);
	if (s->obj == 0)
		return;
	*(float*) (s->obj + 0x1a0) = 1.0f;
	s->pos[0] = v[0];
	s->pos[1] = v[1];
	s->pos[2] = v[2];
	s->f4 = 0;
	*(int*) (s->obj + 4) = 2;
	*(int*) (*(char**) (s->obj + 0x34) + 0x224) = 0;
	fcn_0040c120(s->obj, 0x38, 1);
}
