// SIZE 0x20
typedef struct Plan {
	int x0;
	float level;
	char pad8[0xc];
	int c;
	int a;
	int b;
} Plan;

// SIZE 0x110
typedef struct Unit {
	unsigned short id;
	char pad2[0x1a];
	float bonus;
	char pad20[4];
	int base;
	char pad28[0xe4];
	float mood;
} Unit;

unsigned int __cdecl gm_CalcTrialTortureRounds(Plan* p);
Unit* __cdecl gm_LookupEntityRecordById(int id);
float __cdecl gm_CalcEntityFavor(unsigned int a0, unsigned int a1, unsigned int a2);
unsigned short __cdecl gm_RandomMod(int n);

/* ADDRESS: GOLDTL 0x00493640 */
/* ADDRESS: GOLDDE 0x00482490 */
int __cdecl ai_ShouldConfessTrialTorture(Plan* trial)
{
	unsigned int rounds;
	Unit* accused;
	Unit* judge;
	Unit* plaintiff;
	float stamina;
	float r;
	float threshold;
	float d1;
	float d2;

	if (trial->level <= 3.0f) {
		return 0;
	}
	if (trial->level >= 18.0f) {
		return 1;
	}
	rounds = gm_CalcTrialTortureRounds(trial);
	accused = gm_LookupEntityRecordById(trial->a);
	judge = gm_LookupEntityRecordById(trial->b);
	plaintiff = gm_LookupEntityRecordById(trial->c);
	stamina = accused->base + accused->bonus;
	r = accused->mood - 2.0f;
	if (r > 0.66f) {
		threshold = (float)(rounds * 190);
	} else if (r > 0.33f) {
		threshold = (float)(rounds * 90);
	} else {
		threshold = (float)(rounds * 70);
	}
	if (threshold > stamina) {
		return 1;
	}
	d1 = gm_CalcEntityFavor(accused->id, judge->id, 1) * 0.01f;
	d2 = gm_CalcEntityFavor(plaintiff->id, judge->id, 1) * 0.01f;
	if (d1 * 1.1f > d2 * 0.9f && d1 < d2) {
		return 0;
	}
	return gm_RandomMod(2);
}
