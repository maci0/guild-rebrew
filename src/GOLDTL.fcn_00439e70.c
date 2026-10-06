typedef struct
{
	int v[6];
} fcn_00439e70_Rec;
// SIZE 0x18

typedef struct
{
	float f;
	int n;
	char pad08[0x38 - 0x8];
} fcn_00439e70_Lvl;
// SIZE 0x38

typedef struct
{
	char pad000[0x30];
	fcn_00439e70_Lvl lvl[7];
} fcn_00439e70_Anim;
// SIZE 0x1b8

typedef struct
{
	char pad000[0x9c];
	fcn_00439e70_Rec rec[10];
} fcn_00439e70_Obj;
// SIZE 0x18c

void __cdecl fcn_00438d70(char* o, int a, int b, int c);
void __cdecl fcn_00438ba0(char* o, int a, int b, int c);

// FUNCTION: GOLDTL 0x439e70
void __cdecl fcn_00439e70(char* o)
{
	int i;
	unsigned int j;

	for (i = 0; i < 10; i++) {
		((fcn_00439e70_Obj*) o)->rec[i].v[0] = 0;
		((fcn_00439e70_Obj*) o)->rec[i].v[1] = 0;
		((fcn_00439e70_Obj*) o)->rec[i].v[2] = 0;
		((fcn_00439e70_Obj*) o)->rec[i].v[3] = 0;
		((fcn_00439e70_Obj*) o)->rec[i].v[4] = 0;
		((fcn_00439e70_Obj*) o)->rec[i].v[5] = 0;
	}
	*(int*) (o + 0x1f8) = 0;
	*(int*) (o + 0x1f4) = 0;
	*(int*) (o + 0x200) = 0;
	*(int*) (o + 0x1fc) = 0;
	*(int*) (o + 0x210) = 0;
	o[0x215] &= 0x78;
	o[0x216] &= 0xf0;
	o[0x214] = (o[0x214] & 8) | 0x95;
	o[0x217] &= 0xf3;
	*(int*) (o + 0x218) = 1;
	*(int*) (o + 0x220) = 0;
	*(int*) (o + 0x224) = 0;
	*(int*) (o + 0x40) = 0;
	*(int*) (o + 0x1d0) = 0;
	*(int*) (o + 0x1d4) = 0;
	*(int*) (o + 0x44) = 0;
	if (*(char**) (o + 0x1e8) != 0) {
		*(int*) (*(char**) (o + 0x1e8) + 0x19c) = 15;
		*(float*) (*(char**) (o + 0x1e8) + 0x198) = 0.3f;
		*(int*) (*(char**) (o + 0x1e8) + 0x1a4) = 0;
		for (j = 0; j < 7; j++) {
			(*(fcn_00439e70_Anim**) (o + 0x1e8))->lvl[j].n = 15;
			(*(fcn_00439e70_Anim**) (o + 0x1e8))->lvl[j].f = 0.3f;
		}
	}
	*(int*) (o + 0x6c) = 0;
	*(int*) (o + 0x70) = 0;
	*(int*) (o + 0x74) = 0;
	*(int*) (o + 0x78) = 0;
	*(int*) (o + 0x7c) = 0;
	*(int*) (o + 0x80) = 0;
	fcn_00438d70(o, 0, 0, 0);
	fcn_00438ba0(o, 0, 0, 0);
}
