


#include "g_774a78.h"

void __cdecl m_FreeTracked(void*);

extern struct Node* g_774a78;

int __cdecl fcn_005b1c90(int id)
{
	Node* prev;
	Node* n;

	prev = 0;
	for (n = g_774a78; n != 0; n = n->next) {
		if (n->id == id) {
			break;
		}
		prev = n;
	}
	if (n == 0) {
		return -1;
	}
	if (prev != 0) {
		prev->next = n->next;
	} else {
		g_774a78 = n->next;
	}
	m_FreeTracked(n);
	return 0;
}
