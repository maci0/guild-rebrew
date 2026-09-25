#pragma pack(push, 1)
typedef struct Kind50bec0 {
	char pad0[0x23];
	unsigned short slot[0x40];
	char pad[0x24d - 0xa3];
} Kind50bec0;

typedef struct {
	char kind;
	char pad[0x40];
} Obj50bec0;
#pragma pack(pop)
// SIZE 0x24d, 0x41

extern Kind50bec0* g_868050;
extern Obj50bec0* g_99ec10;

// FUNCTION: GOLDTL 0x0050bec0
// SIZE: 100
int __cdecl fcn_0050bec0(unsigned char* s, int* out)
{
	Kind50bec0* k;
	int n;
	int i;
	int w;

	n = 0;
	k = &g_868050[*s];
	for (i = 0; i < 0x40; i++) {
		if (k->slot[i] == 0) {
			break;
		}
		w = k->slot[i] & 0x7fff;
		if (g_99ec10[w].kind != 0x21) {
			n++;
		}
		if (out != 0) {
			out[n] = w;
		}
	}
	return n;
}
