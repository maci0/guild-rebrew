/* gm_RemoveLinkedNodeById — removes a linked-list node by id. */

#include <stddef.h>

// FUNCTION: SERVER 0x10016680

extern int g_query_limit; /* 0x10035450 */

void __cdecl gm_FreeObjectListRecursive(void* children);
void __cdecl gm_NoopRet2(void* node);

/* LinkedNode lifted to game_structs.h: the gm_RemoveObjectByType twin named
 * the +0x00 word `id` and this copy named it `active`; the callers fix both
 * words (this one matches the +0x02 entity id, ByType the +0x00 type). */
#include "game_structs.h"

/* Removes the node whose id equals b from the list headed by *a.
 * Returns 0 on success, -1 if the list is empty, -2 if the id is
 * not found. Also decrements the global query limit counter. */
int __cdecl gm_RemoveLinkedNodeById(int a, int b, int c)
{
	LinkedNode** head;
	LinkedNode* node;
	LinkedNode* prev;
	int index;

	head = (LinkedNode**) a;
	node = *head;
	prev = NULL;
	if (node == NULL)
		return -1;
	index = 0;

	while (node != NULL && node->entity_id != b) {
		prev = node;
		node = node->next;
		index++;
	}
	if (node == NULL)
		return -2;

	if (node->children != NULL)
		gm_FreeObjectListRecursive(&node->children);
	gm_NoopRet2(node);
	if (index == 0)
		*head = node->next;
	else
		prev->next = node->next;
	node->type = 0;
	g_query_limit--;
	return 0;
}
