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
} PREDIGT_ENTITY;

typedef struct
{
	char pad0[0x18];
	int side;
	char pad1c[8];
} PREDIGT_LAW_STAT;

typedef struct
{
	int count;
	int total;
	char* who;
} PREDIGT_RESULT;

extern PREDIGT_ENTITY gm_EntitySlotTable[];
extern char gm_ActiveTownIndex;

void __cdecl gm_FindRichestEntity(int* a, int* b);
float __cdecl gm_GetEntitySkill(PREDIGT_ENTITY* e, int k);
int __cdecl gm_GetLawEntry(int idx, PREDIGT_LAW_STAT* dst);
int __cdecl gm_GetBuildingTechEffect(char* a, int b, int c);
float __cdecl gm_RandomFloat01(void);
int __cdecl gm_WalkEntityChain(unsigned short id);
void __cdecl cm_RequestTransferCurrencyNoKill(int, int, char, int);
void __cdecl cm_RequestChangeFloat(int a1, int a2, float a3);
float __cdecl gm_CalcSkillDuelScore(PREDIGT_ENTITY* a, PREDIGT_ENTITY* b, int k);
void __cdecl cm_RequestCopyEntityData(int a1, int a2, int a3, int a4);

/* ADDRESS: GOLDTL 0x004fd4f0 */
int __cdecl gm_ApplyPredigtCollection(char* building, PREDIGT_RESULT* out)
{
	float mult;
	int count;
	int total;
	float sign;
	int base;
	int n;
	PREDIGT_LAW_STAT st;
	PREDIGT_ENTITY* me;
	PREDIGT_ENTITY* ent;
	float v;
	float fb;
	float r;
	int i;
	int amt;

	total = 0;
	count = 0;
	gm_FindRichestEntity((int*) &mult, &base);
	if (*(unsigned short*) (building + 0x27) == 0xffff)
		return 0;
	me = &gm_EntitySlotTable[*(unsigned short*) (building + 0x27)];
	gm_GetEntitySkill(me, 4);
	gm_GetLawEntry(2, &st);
	mult = gm_GetBuildingTechEffect(building, 9, 1) * 0.0125f + 1.0f;
	for (i = 0; i < 768; i++) {
		ent = &gm_EntitySlotTable[i];
		if (ent->id == 0xffff || ent->kind == 6 || ent->kind == 7 || ent->kind == 8 || ent->kind >= 10)
			continue;
		if (ent->h == me->h)
			continue;
		r = ent->rank * 0.25f;
		if (ent->side == me->side) {
			v = r * mult;
			sign = 0.05f;
		} else {
			if (st.side == 2)
				v = r * mult * 0.8;
			else if (me->side == st.side)
				v = r * mult * 0.7;
			else
				v = r * mult * 0.6;
			sign = -0.05f;
		}
		if (!(gm_RandomFloat01() * 2.0f <= v))
			continue;
		fb = (float) base;
		amt = (int) ((MAX(gm_WalkEntityChain(ent->id) / fb * 160.0f, 0.0f) + 160.0f) * v);
		total += amt;
		cm_RequestTransferCurrencyNoKill(-1, ent->h, gm_ActiveTownIndex, amt);
		count++;
		if (ent->mood < 0.95f && ent->mood > 0.05f)
			cm_RequestChangeFloat(ent->h, 0x1d0, sign);
		if (out->who != 0) {
			n = (int) (gm_CalcSkillDuelScore(me, ent, 4) * 10.0f + 1.0f);
			cm_RequestCopyEntityData(*(int*) (out->who + 4), ent->h, n, 1);
		}
	}
	out->count = count;
	out->total = total;
	return 1;
}
