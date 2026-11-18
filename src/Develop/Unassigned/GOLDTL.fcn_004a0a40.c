// SIZE 0x29
typedef struct Unit {
	unsigned short id;
	unsigned char kind;
	char pad3[5];
	unsigned char hp;
	unsigned char busy;
	unsigned short level;
	char padc[0x14];
	float need;
	char pad24[0x164 - 0x24];
	unsigned char locked;
} Unit;

char* __cdecl gm_LookupEntityRecordById(int id);
int __cdecl fcn_0047dd60(char* e);
char* __cdecl fcn_005463a0(int, int, int, int, int);
int __cdecl fcn_004a4410(float* s1, float* s2, int idx, char* e, int a5, int a6, int a7);

/* ADDRESS: GOLDTL 0x004a0a40 */
int __cdecl ai_ScoreBerufsausbildung(float* s1, float* s2, int idx, char* actor, int flag, int a6, int a7)
{
	char* other;
	Unit* unit;
	Unit* best;
	int i;
	int eligible;

	if (flag != 0) {
		*s1 = -1.0e30f;
		*s2 = -1.0e30f;
		return 0;
	}
	if (actor[2] != 5) {
		other = gm_LookupEntityRecordById(*(int*) (actor + 0x5c));
		if (other != 0) {
			if (other[2] == 5) {
				return 0;
			}
			if (other[9] == 0 && fcn_0047dd60(other) != 0) {
				return 0;
			}
		}
	}
	best = 0;
	for (i = 0; i < 5; i++) {
		unit = (Unit*) gm_LookupEntityRecordById(((int*) (actor + 0x68))[i]);
		if (unit != 0 && unit->hp > 0 && unit->level + 4 >= unit->need && unit->locked == 0 && fcn_005463a0(2, 2, unit->id, 0, 0x5e) == 0) {
			if (best == 0 || unit->level > best->level) {
				best = unit;
			}
		}
	}
	if (best == 0) {
		return 0;
	}
	*s1 = 0;
	*s2 = 0;
	fcn_004a4410(s1, s2, idx, actor, 0, a6, a7);
	eligible = best->level + 4 >= best->need;
	*s1 *= eligible;
	*s2 *= eligible;
	return 1;
}
