typedef struct Seg {
	int id;
	int next;
	int owner;
	char padc[8];
	int want;
	char pad18[0xc];
	int busy;
	int stock;
	int cap;
	char pad30[0xc];
	int flags;
} Seg;
// SIZE 0x40

typedef struct Ware {
	unsigned short id;
	char pad2[0x1a];
	int unit;
} Ware;

extern Seg g_100b0c0[];
extern int g_100b0a8;
extern unsigned char g_773d75;
extern int g_773d78;

int __cdecl fcn_0050dfd0(char* pkt, int item_id);
int __cdecl gm_GetMsgField(char* pkt, Ware* q);
float __cdecl fcn_0050bb50(int id, unsigned char k);
float __cdecl fcn_0050b980(int id, int pct);
char* __cdecl fcn_00503d10(int id);
Ware* __cdecl fcn_00502cd0(int, int, int, int);

// FUNCTION: GOLD 0x0047ec10
// SIZE: 315
// FUNCTION: GOLDTL 0x0047e0e0
// SIZE: 315
void __cdecl fcn_0047e0e0(int a1, char* pkt)
{
	float ratio;
	char* town;
	Ware* w;
	int want;
	int i;

	for (i = 0; i < g_100b0a8; i++) {
		if ((g_100b0c0[i].flags & 0x20) == 0 && (g_100b0c0[i].flags & 0x200) == 0 && g_100b0c0[i].busy == 0 && g_100b0c0[i].stock < fcn_0050dfd0(pkt, g_100b0c0[i].id) / 4) {
			ratio = fcn_0050bb50(g_100b0c0[i].id, g_773d75) / fcn_0050b980(g_100b0c0[i].id, 100);
			if (ratio < 0.8f) {
				g_100b0c0[i].owner = 0;
				want = (int) ((1.0f - ratio) * g_100b0c0[i].cap);
				g_100b0c0[i].want = want;
				if (want >= g_100b0c0[i].cap) {
					want = g_100b0c0[i].cap;
				}
				g_100b0c0[i].want = want;
				town = fcn_00503d10(g_100b0c0[i].id);
				if (town != 0) {
					w = fcn_00502cd0(*(int*) (town + 0x14), 1, 0, g_100b0c0[i].id);
					if (w != 0) {
						if (gm_GetMsgField(town, w) - (int) ((unsigned int) (fcn_0050dfd0(town, w->id) * w->unit) >> 2) >= 5) {
							g_100b0c0[i].owner = g_773d78;
						}
					}
				}
			}
		}
	}
}
