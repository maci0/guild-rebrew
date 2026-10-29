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

char* __cdecl fcn_00508e40(int id);
int __cdecl fcn_0047dd60(char* e);
char* __cdecl fcn_005463a0(int, int, int, int, int);
int __cdecl fcn_004a4410(float* s1, float* s2, int idx, char* e, int a5, int a6, int a7);

/* ADDRESS: GOLDTL 0x004a0a40 */
int __cdecl fcn_004a0a40(float* s1, float* s2, int idx, char* e, int flag, int a6, int a7)
{
	char* o;
	Unit* t;
	Unit* best;
	int i;
	int m;

	if (flag != 0) {
		*s1 = -1.0e30f;
		*s2 = -1.0e30f;
		return 0;
	}
	if (e[2] != 5) {
		o = fcn_00508e40(*(int*) (e + 0x5c));
		if (o != 0) {
			if (o[2] == 5) {
				return 0;
			}
			if (o[9] == 0 && fcn_0047dd60(o) != 0) {
				return 0;
			}
		}
	}
	best = 0;
	for (i = 0; i < 5; i++) {
		t = (Unit*) fcn_00508e40(((int*) (e + 0x68))[i]);
		if (t != 0 && t->hp > 0 && t->level + 4 >= t->need && t->locked == 0 && fcn_005463a0(2, 2, t->id, 0, 0x5e) == 0) {
			if (best == 0 || t->level > best->level) {
				best = t;
			}
		}
	}
	if (best == 0) {
		return 0;
	}
	*s1 = 0;
	*s2 = 0;
	fcn_004a4410(s1, s2, idx, e, 0, a6, a7);
	m = best->level + 4 >= best->need;
	*s1 *= m;
	*s2 *= m;
	return 1;
}
