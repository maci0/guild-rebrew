// FUNCTION: GOLDTL 0x45cfa0
// SIZE: 160
// total = 0 is assigned twice: the reference stores the zero both before
// and after the callback test.

typedef struct Rec045cfa0 {
	char pad0[0x40];
	int level;
	char pad44[0x54 - 0x44];
	unsigned char flags;
	char pad55[0x70 - 0x55];
} Rec045cfa0;
// SIZE 0x70

typedef void(__cdecl* Progress045cfa0)(int stage, int done, int total);

extern Rec045cfa0* g_104049c;
extern unsigned int g_10404a0;
extern int g_6b8af0;

void __cdecl fcn_0045ce90(Rec045cfa0* r);

void __cdecl fcn_0045cfa0(Progress045cfa0 cb)
{
	Rec045cfa0* r;
	unsigned int i;
	int done;
	int total;

	total = 0;
	if (cb != 0) {
		total = 0;
		for (i = 0; i < g_10404a0; i++) {
			if (g_104049c[i].level > 0 && (g_104049c[i].flags & 2) == 0) {
				total++;
			}
		}
	}
	done = 0;
	r = g_104049c;
	for (i = 0; i < g_10404a0; i++, r++) {
		if (r->level > 0 && (r->flags & 2) == 0) {
			fcn_0045ce90(r);
			if (cb != 0) {
				cb(1, done, total);
			}
			done++;
		}
	}
	g_6b8af0 = 0;
}
