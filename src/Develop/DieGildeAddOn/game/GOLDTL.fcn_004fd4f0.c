#define MAX(a, b) ((a) > (b) ? (a) : (b))

// SIZE 0x21c
typedef struct
{
	unsigned short id;
	unsigned char kind;
	char pad3;
	int h;
	char pad8[4];
	unsigned char side;
	char padd[0x1b0 - 0xd];
	unsigned char rank;
	char pad1b1[0x1d0 - 0x1b1];
	float mood;
	char pad1d4[0x21c - 0x1d4];
} fcn_004fd4f0_Ent;

typedef struct
{
	char pad0[0x18];
	int side;
	char pad1c[8];
} fcn_004fd4f0_Stat;

typedef struct
{
	int count;
	int total;
	char* who;
} fcn_004fd4f0_Out;

extern fcn_004fd4f0_Ent g_7f4ca0[];
extern char g_773d75;

void __cdecl fcn_004fd400(int* a, int* b);
float __cdecl gm_GetEntitySkill(fcn_004fd4f0_Ent* e, int k);
int __cdecl fcn_004f4830(int idx, fcn_004fd4f0_Stat* dst);
int __cdecl fcn_0050c710(char* a, int b, int c);
double __cdecl gm_RandomFloat01(void);
int __cdecl gm_WalkEntityChain(unsigned short id);
void __cdecl fcn_004c51a0(int, int, char, int);
void __cdecl fcn_004c5480(int a1, int a2, float a3);
float __cdecl fcn_00507e70(fcn_004fd4f0_Ent* a, fcn_004fd4f0_Ent* b, int k);
void __cdecl fcn_004c54c0(int a1, int a2, int a3, int a4);

/* ADDRESS: GOLDTL 0x004fd4f0 */
int __cdecl fcn_004fd4f0(char* a1, fcn_004fd4f0_Out* out)
{
	float mult;
	int count;
	int total;
	float sign;
	int base;
	int n;
	fcn_004fd4f0_Stat st;
	fcn_004fd4f0_Ent* me;
	fcn_004fd4f0_Ent* ent;
	float v;
	float fb;
	int amt;

	total = 0;
	count = 0;
	fcn_004fd400((int*) &mult, &base);
	if (*(unsigned short*) (a1 + 0x27) == 0xffff)
		return 0;
	me = &g_7f4ca0[*(unsigned short*) (a1 + 0x27)];
	gm_GetEntitySkill(me, 4);
	fcn_004f4830(2, &st);
	mult = fcn_0050c710(a1, 9, 1) * 0.0125f + 1.0f;
	for (ent = g_7f4ca0; ent < g_7f4ca0 + 768; ent++) {
		if (ent->id == 0xffff || ent->kind == 6 || ent->kind == 7 || ent->kind == 8 || ent->kind >= 10)
			continue;
		if (ent->h == me->h)
			continue;
		if (ent->side == me->side) {
			v = ent->rank * 0.25f * mult;
			sign = 0.05f;
		} else {
			if (st.side == 2)
				v = ent->rank * 0.25f * mult * 0.8;
			else if (me->side == st.side)
				v = ent->rank * 0.25f * mult * 0.7;
			else
				v = ent->rank * 0.25f * mult * 0.6;
			sign = -0.05f;
		}
		if (gm_RandomFloat01() * 2.0 > v)
			continue;
		fb = (float) base;
		amt = (int) ((MAX(gm_WalkEntityChain(ent->id) / fb * 160.0f, 0.0f) + 160.0f) * v);
		total += amt;
		fcn_004c51a0(-1, ent->h, g_773d75, amt);
		count++;
		if (ent->mood < 0.95f && ent->mood > 0.05f)
			fcn_004c5480(ent->h, 0x1d0, sign);
		if (out->who != 0)
			fcn_004c54c0(*(int*) (out->who + 4), ent->h, (int) (fcn_00507e70(me, ent, 4) * 10.0f + 1.0f), 1);
	}
	out->count = count;
	out->total = total;
	return 1;
}
