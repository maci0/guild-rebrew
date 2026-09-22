/* gm_RemoveObjectByType — removes a linked-list node by type id. */

#include <stddef.h>

// FUNCTION: SERVER 0x100165d0

extern int g_query_limit; /* 0x10035450 */

void __cdecl gm_FreeObjectListRecursive(void* children);
void __cdecl gm_NoopRet2(void* node);

/* LinkedNode lifted to game_structs.h: this copy named the +0x00 word `id`,
 * the gm_RemoveLinkedNodeById twin named +0x02 `id`; the callers fix both
 * words (ByType matches the +0x00 type, ById the +0x02 entity id). */
#include "game_structs.h"

/* Removes the first node whose type id equals b from the list headed by *a.
 * Returns 0 on success, -1 if the list is empty, -2 if the id is not found.
 * Also decrements the global query limit counter. */
int __cdecl gm_RemoveObjectByType(int a, int b, int c)
{
	LinkedNode** head;
	LinkedNode* node;
	LinkedNode* prev;
	int index;

	head = (LinkedNode**) a;
	prev = NULL;
	if (a == NULL)
		return -1;
	node = *head;
	if (node == NULL)
		return -1;
	index = 0;

	while (node != NULL && node->type != b) {
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
