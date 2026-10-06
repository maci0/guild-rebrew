typedef struct Rec {
	char type;
	char rest[0x40];
} Rec;
// SIZE 0x41

typedef struct Node {
	int id;
	int links[4];
	char pad14[0x54 - 0x14];
	int flags;
} Node;
// SIZE 0x58

extern char* g_99ec10;
#include "client_types.h"
extern Seg g_100b0c0[];
extern entry_100d0c0 g_100d0c0[];

// FUNCTION: GOLDTL 0x487d80
void __cdecl fcn_00487d80(int* ca, int* cb, Node* n)
{
	int i;
	Seg* s;

	if (!(n->flags & 1)) {
		if (((Rec*)g_99ec10)[n->id].type == 0x17 || ((Rec*)g_99ec10)[n->id].type == 0x25) {
			(*ca)++;
		} else {
			(*cb)++;
		}
		n->flags |= 1;
	}
	for (i = 0; i < 4; i++) {
		if (n->links[i] < 0) {
			continue;
		}
		s = &g_100b0c0[n->links[i]];
		if (!(s->flags & 1)) {
			if (((Rec*)g_99ec10)[s->id].type == 0x17 || ((Rec*)g_99ec10)[s->id].type == 0x25) {
				(*ca)++;
			} else {
				(*cb)++;
			}
			s->flags |= 1;
			if (s->next != -1) {
				((Node*)g_100d0c0)[s->next].flags |= 1;
			}
		}
		if (s->next != -1) {
			fcn_00487d80(ca, cb, &((Node*)g_100d0c0)[s->next]);
		}
	}
}
