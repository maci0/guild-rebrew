// FUNCTION: GOLDTL 0x004f5f30
// SIZE: 258

#pragma pack(1)
// SIZE 0x2d
typedef struct {
	int id;
	char pad4[0x2d - 4];
} Order;
#pragma pack()

// SIZE 0x8
typedef struct {
	int owner;
	int key;
} Pair;

// SIZE 0x21c
typedef struct {
	unsigned short id;
	unsigned char type;
	char pad3;
	int owner;
	char pad8[0x21c - 8];
} Obj;

extern Order g_9a3800[];
extern Pair g_99f800[];
extern Obj g_7f4ca0[];

char* __cdecl fcn_00508e40(int id);
void __cdecl fcn_004c5870(int id, int v);
void __cdecl fcn_005b2a00(char* o, char* p);

int __cdecl fcn_004f5f30(int target, int count, int* ids)
{
	int n;
	int flag[8];
	char* who[8];
	char* p;
	int m;
	int i;
	int j;
	int k;
	int r;
	int id;
	int found;

	n = 0;
	p = fcn_00508e40(target);
	m = 0;
	if (p != 0) {
		for (k = 0; k < 768 && m < 8; k++) {
			if ((g_7f4ca0[k].type == 6 || g_7f4ca0[k].type == 7) && g_7f4ca0[k].owner != target) {
				flag[m] = 0;
				who[m] = (char*) &g_7f4ca0[k];
				m++;
			}
		}
	}
	for (i = 0; i < count; i++) {
		id = ids[i];
		found = 0;
		for (j = 0; j < 512; j++) {
			if (g_9a3800[j].id == id) {
				found = 1;
				break;
			}
		}
		if (found) {
			for (k = 0; k < 2048; k++) {
				for (r = 0; r < m; r++) {
					if (g_99f800[k].owner == *(int*) (who[r] + 4) && g_99f800[k].key == id) {
						flag[r] = 1;
					}
				}
			}
			fcn_004c5870(id, 1);
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
