#pragma pack(push, 1)
typedef struct Rec {
	char type;
	char pad1[0x21];
	unsigned int cap;
	unsigned short weight[4];
	char pad2e[8];
	unsigned short div;
	char pad38[9];
} Rec;
// SIZE 0x41
#pragma pack(pop)

typedef struct Node {
	int id;
	int links[4];
	char pad14[0x10];
	float value;
	float sum;
	float base;
	float price;
	float slope;
} Node;

typedef struct Seg {
	int id;
	int next;
	char pad8[0x14];
	float price;
	char pad20[0x20];
} Seg;
// SIZE 0x40

extern char* g_99ec10;
extern Seg g_100b0c0[];
extern unsigned char g_773d75;

float __cdecl fcn_0050bb50(int id, unsigned char k);
float __cdecl fcn_0050b840(int id);

/* ADDRESS: GOLD 0x00487030 */
/* ADDRESS: GOLDTL 0x00486500 */
void __cdecl fcn_00486500(Node* n)
{
	Seg* s;
	int i;

	if (!(n->value > -10000000000.0)) {
		n->sum = 0;
		for (i = 0; i < 4; i++) {
			if (n->links[i] >= 0) {
				s = &g_100b0c0[n->links[i]];
				if (!(s->price > -10000000000.0)) {
					if (s->next != -1) {
						s->price = fcn_0050bb50(s->id, g_773d75) * 0.9;
					} else {
						s->price = fcn_0050bb50(s->id, g_773d75);
					}
				}
				n->sum += ((Rec*)g_99ec10)[n->id].weight[i] * s->price;
			}
		}
		n->sum = n->sum / ((Rec*)g_99ec10)[n->id].div;
		n->base = fcn_0050b840(n->id);
		n->value = n->base + n->sum;
		n->price = fcn_0050bb50(n->id, g_773d75);
		n->slope = (n->price - n->value) / ((Rec*)g_99ec10)[n->id].cap;
	}
}
