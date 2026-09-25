typedef struct Rec {
	char type;
	char rest[0x40];
} Rec;
// SIZE 0x41

typedef struct Slot {
	int id;
	int a;
	int b;
	char* item;
} Slot;

typedef struct Counts {
	int total;
	int blocked;
	int free;
} Counts;

typedef struct Def {
	char pad0[0x10];
	int mask;
} Def;

extern Rec* g_99ec10;

Def* __cdecl fcn_005c61e0(int id);
int __cdecl fcn_005c6270(char* e, int id);

// FUNCTION: GOLD 0x004a5760
// SIZE: 358
// FUNCTION: GOLDTL 0x004a51d0
// SIZE: 358
void __cdecl fcn_004a51d0(char* e, int n, Slot* slots, Counts* cnt)
{
	char* it;
	Def* d;
	int i;

	for (i = 0; i < n; i++) {
		slots[i].b = -1;
		slots[i].a = 0;
	}
	cnt->blocked = 0;
	cnt->free = 0;
	cnt->total = 0;
	for (it = *(char**) (e + 0x178); it != 0; it = *(char**) (it + 0x3f)) {
		if (g_99ec10[*(unsigned short*) it].type == 9) {
			continue;
		}
		cnt->total++;
		for (i = 0; i < n; i++) {
			if (*(unsigned short*) it == slots[i].id) {
				d = fcn_005c61e0(*(unsigned short*) it);
				if (d == 0) {
					slots[i].a = -1;
					cnt->blocked++;
					slots[i].item = 0;
					slots[i].b = -1;
				} else if ((d->mask & *(int*) (e + 0x1ec)) == 0 && fcn_005c6270(e, *(unsigned short*) it) == 0) {
					cnt->free++;
					slots[i].a = *(int*) (it + 0xe);
					slots[i].b = *(int*) (it + 2);
					slots[i].item = it;
				} else {
					slots[i].a = -1;
					cnt->blocked++;
					slots[i].b = *(int*) (it + 2);
					slots[i].item = it;
				}
				break;
			}
		}
	}
	for (i = 0; i < n; i++) {
		if (slots[i].b == -1) {
			d = fcn_005c61e0(slots[i].id);
			if (d != 0 && (d->mask & *(int*) (e + 0x1ec)) != 0) {
				cnt->blocked++;
			}
		}
	}
}
