// FUNCTION: GOLD 0x004f3a30
// FUNCTION: GOLDTL 0x004f5e20

#pragma pack(1)
// SIZE 0x2d
typedef struct {
	int id;
	char pad4[0x16 - 4];
	int target;
	short count;
	unsigned char kind;
	char pad1d[0x21 - 0x1d];
	int arg;
	int state;
	char pad29[0x2d - 0x29];
} Order;
#pragma pack()

// SIZE 0x8
#include "client_types.h"
typedef Pair_99f800 Pair;

// SIZE 0x21c
typedef struct {
	unsigned short id;
	unsigned char type;
	char pad3;
	int owner;
	char pad8[0x21c - 8];
} Obj;

extern Rec2d_9a3800 g_9a3800[512];
extern Pair_99f800 g_99f800[0x800];
extern char g_7f4ca0[];

char* __cdecl fcn_00508e40(int id);
void __cdecl fcn_004c5870(int id, int v);
void __cdecl fcn_005b2a00(char* o, char* p);

int __cdecl fcn_004f5e20(int target, int max)
{
	int n;
	char* p;
	int flag[8];
	char* who[8];
	char* q;
	int m;
	int j;
	int k;
	int r;

	n = 0;
	p = fcn_00508e40(target);
	m = 0;
	if (p != 0) {
		for (k = 0; k < 768 && m < 8; k++) {
			if ((((Obj*)g_7f4ca0)[k].type == 6 || ((Obj*)g_7f4ca0)[k].type == 7) && ((Obj*)g_7f4ca0)[k].owner != target) {
				flag[m] = 0;
				who[m] = (char*) &((Obj*)g_7f4ca0)[k];
				m++;
			}
		}
	}
	for (j = 0; j < 512 && n < max; j++) {
		if (((Order*)g_9a3800)[j].target == target && ((Order*)g_9a3800)[j].state == 1) {
			for (k = 0; k < 2048; k++) {
				for (r = 0; r < m; r++) {
					if (g_99f800[k].owner == *(int*) (who[r] + 4) && g_99f800[k].key == ((Order*)g_9a3800)[j].id) {
						flag[r] = 1;
					}
				}
			}
			fcn_004c5870(((Order*)g_9a3800)[j].id, 1);
			n++;
		}
	}
	for (r = 0; r < m; r++) {
		if (flag[r] != 0) {
			fcn_005b2a00(who[r], p);
		}
	}
	return n;
}
