typedef struct HitObj {
	int f0;
	char pad4[0xc];
	int f10;
	int f14;
	int f18;
	int f1c;
	char pad20[0x10];
	int f30;
	int f34;
	char pad38[0x10];
	int f48;
	int f4c;
	char* f50;
	char pad54[0x34];
	int f88;
} HitObj;
/* SIZE 0x8c */

extern int g_67d388;
extern HitObj** g_772540;
extern char* g_1015ea0;

/* ADDRESS: GOLDTL 0x0046ac40 */
int __cdecl fcn_0046ac40(int a0, int a1)
{
	HitObj* o;
	int n;
	int hit;

	g_67d388 = -1;
	for (n = 0x3ff; n >= 0; n--) {
		hit = 0;
		o = g_772540[n];
		if (o == 0) {
			continue;
		}
		if (o->f50 != 0) {
			hit = *(int*) (o->f50 + 0x198);
		}
		if (a0 < o->f10 || a0 > o->f10 + o->f18) {
			continue;
		}
		if (a1 < o->f14 || a1 > o->f14 + o->f1c) {
			continue;
		}
		if (hit != 0) {
			continue;
		}
		if (a1 < o->f30 || a1 > o->f34) {
			continue;
		}
		if (o->f4c != 0 || o->f48 != 0) {
			continue;
		}
		if (*(int*) (g_1015ea0 + o->f0 * 0x2f4 + 0x20) != 0x40) {
			continue;
		}
		g_67d388 = o->f88;
		break;
	}
	return g_67d388;
}
