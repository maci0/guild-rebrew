// FUNCTION: GOLDTL 0x0041f8f0
// SIZE: 75
// FUNCTION: GOLD 0x00423660
// SIZE: 75

#include <stdlib.h>
#include <string.h>

typedef struct Node Node;

// SIZE 0x8
struct Node {
	Node* next;
	Node* prev;
};

extern Node* g_6b6f84;

Node* __cdecl fcn_0041f8f0(void)
{
	Node* n;
	Node* p;

	n = (Node*) malloc(0x148);
	if (n != 0) {
		memset(n, 0, 0x148);
		if (g_6b6f84 != 0) {
			p = g_6b6f84;
			while (p->prev != 0) {
				p = p->prev;
			}
			p->prev = n;
			n->next = p;
		} else {
			g_6b6f84 = n;
		}
	}
	return n;
}
