
// Collects the goods ids of the two id lists (0x100e760, 0x100e720) into the
// segment table, then adds each production record's stock to the matching
// segments. The second list prices its entries by the first list's id at the
// same index.

typedef struct Seg {
	int id;
	int next;
	int x8;
	int xc;
	int x10;
	int x14;
	int x18;
	float price;
	int x20;
	int stock;
	int buy;
	int full;
	int flags;
	int x34;
	int x38;
	int x3c;
} Seg;
// SIZE 0x40

typedef struct Stats {
	int x0;
	int n;
	int x8[16];
	unsigned short x48[16];
	int x68[16];
	int xa8;
	int xac;
	int xb0;
	char* xb4;
} Stats;
// SIZE 0xb8

extern int g_100b0a8;
extern Seg g_100b0c0[];
extern int g_100e720[];
extern int g_100e760[];
extern unsigned char g_773d75;

float __cdecl fcn_0050bb50(int id, unsigned char k);
int __cdecl fcn_0050dfa0(char* b, int id);
int __cdecl gm_eval_SlotVoll(char*, int, int);
char* __cdecl fcn_005463a0(int, int, int, int, int);
char* __cdecl fcn_005462a0(void);
char* __cdecl gm_FindRecordById(int);
int __cdecl fcn_0050de80(char* e, Stats* s);

void __cdecl fcn_00485650(char* a, char* b)
{
	int i;
	int j;
	int k;
	int m;
	int found;
	unsigned short id;
	char* e;
	char* r;
	Stats st;

	for (j = 0; g_100e760[j] != 0; j++) {
		for (i = 0; i < g_100b0a8; i++) {
			if (g_100b0c0[i].id == g_100e760[j]) {
				break;
			}
		}
		if (i >= g_100b0a8) {
			g_100b0c0[g_100b0a8].id = g_100e760[j];
			g_100b0c0[g_100b0a8].next = -1;
			g_100b0c0[g_100b0a8].x8 = 0;
			g_100b0c0[g_100b0a8].x10 = 0;
			g_100b0c0[g_100b0a8].x14 = 0;
			g_100b0c0[g_100b0a8].x18 = 0;
			g_100b0c0[g_100b0a8].price = fcn_0050bb50(g_100e760[j], g_773d75);
			g_100b0c0[g_100b0a8].stock = 0;
			g_100b0c0[g_100b0a8].buy = 0;
			g_100b0c0[g_100b0a8].flags = 0x81;
			g_100b0c0[g_100b0a8].x3c = 0;
			g_100b0c0[g_100b0a8].buy = fcn_0050dfa0(b, g_100e760[j]);
			g_100b0c0[g_100b0a8].full = gm_eval_SlotVoll(b, g_100e760[j], 1000000);
			g_100b0a8++;
		}
	}
	for (j = 0; g_100e720[j] != 0; j++) {
		for (i = 0; i < g_100b0a8; i++) {
			if (g_100b0c0[i].id == g_100e720[j]) {
				break;
			}
		}
		if (i >= g_100b0a8) {
			g_100b0c0[g_100b0a8].id = g_100e720[j];
			g_100b0c0[g_100b0a8].next = -1;
			g_100b0c0[g_100b0a8].x8 = 0;
			g_100b0c0[g_100b0a8].x10 = 0;
			g_100b0c0[g_100b0a8].x14 = 0;
			g_100b0c0[g_100b0a8].x18 = 0;
			g_100b0c0[g_100b0a8].price = fcn_0050bb50(g_100e760[j], g_773d75);
			g_100b0c0[g_100b0a8].stock = 0;
			g_100b0c0[g_100b0a8].buy = 0;
			g_100b0c0[g_100b0a8].flags = 0x81;
			g_100b0c0[g_100b0a8].x3c = 0;
			g_100b0c0[g_100b0a8].buy = fcn_0050dfa0(b, g_100e720[j]);
			g_100b0c0[g_100b0a8].full = gm_eval_SlotVoll(b, g_100e720[j], 1000000);
			g_100b0a8++;
		}
	}
	for (e = fcn_005463a0(2, 0, 0xb, 3, *(int*) (*(char**) (a + 0x16c) + 1)); e != 0; e = fcn_005462a0()) {
		r = gm_FindRecordById(*(int*) (e + 0xac));
		if (r == 0) {
			continue;
		}
		fcn_0050de80(r, &st);
		for (k = 0; k < st.x0; k++) {
			id = st.x48[k];
			if (id == 0) {
				continue;
			}
			found = 0;
			for (m = 0; found == 0 && m < 3; m++) {
				if (((unsigned short*) (e + 0xd0))[m] == id) {
					found = 1;
				}
			}
			if (found == 0) {
				for (i = 0; i < g_100b0a8; i++) {
					if (id == g_100b0c0[i].id) {
						g_100b0c0[i].stock += st.x68[k];
					}
				}
			}
		}
		for (m = 0; m < 3; m++) {
			if (((unsigned short*) (e + 0xd6))[m] != 0) {
				for (i = 0; i < g_100b0a8; i++) {
					if (((unsigned short*) (e + 0xd6))[m] == g_100b0c0[i].id) {
						g_100b0c0[i].stock += ((int*) (e + 0xdc))[m];
					}
				}
			}
		}
	}
}
