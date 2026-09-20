/* gm_FreeObjectListRecursive — unlink and dispose every node of the object
 * linked list rooted at *head (each node is a 0x43-byte pool slot).
 * Recursively frees each node's child list (offset 0x14) first, then hands
 * the node to gm_NoopRet2 (a free stub). Returns -1 on an empty list. */

// FUNCTION: SERVER 0x10016710

#include <stdlib.h>

/* This 0x43-byte node is the LinkedNode layout of game_structs.h (the two
 * remove helpers and this TU spell it; this copy had `active/id/child`).
 * It is spelled here as LinkedNode directly. */
#include "game_structs.h"

void __cdecl gm_NoopRet2(void* node);

int __cdecl gm_FreeObjectListRecursive(LinkedNode** head)
{
	LinkedNode* node;

	if (head == NULL)
		return 0;
	node = *head;
	if (node == NULL)
		return -1;
	do {
		*head = node->next;
		if (node->children != NULL)
			gm_FreeObjectListRecursive((LinkedNode**) &node->children);
		gm_NoopRet2(node);
		node = *head;
	} while (node != NULL);
	return 0;
}
