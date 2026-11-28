


#include "Develop/DieGildeAddOn/loadsave/g_774a78.h"

void __cdecl m_FreeTracked(void*);

extern struct Node* hp_ProdEntryList;

/* ADDRESS: GOLDDE 0x00596690 */
int __cdecl hp_RemoveProdEntry(int id)
{
	Node* prev;
	Node* node;

	prev = 0;
	for (node = hp_ProdEntryList; node != 0; node = node->next) {
		if (node->id == id) {
			break;
		}
		prev = node;
	}
	if (node == 0) {
		return -1;
	}
	if (prev != 0) {
		prev->next = node->next;
	} else {
		hp_ProdEntryList = node->next;
	}
	m_FreeTracked(node);
	return 0;
}
