/* gm_RemoveObjectByType — removes a linked-list node by type id. */

#include <stddef.h>

// FUNCTION: SERVER 0x100165d0

extern int g_query_limit; /* 0x10035450 */

void __cdecl gm_FreeObjectListRecursive(void* children);
void __cdecl gm_NoopRet2(void* node);

/* Linked-list node: type id (word), child-list head, next pointer. */
#pragma pack(push, 1)
typedef struct LinkedNode {
	unsigned short id;        /* 0x00 */
	char pad0[0x12];          /* 0x02 */
	struct LinkedNode* children; /* 0x14 */
	char pad1[0x27];          /* 0x18 */
	struct LinkedNode* next;  /* 0x3f */
} LinkedNode;
#pragma pack(pop)

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

	while (node != NULL && node->id != b) {
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
	node->id = 0;
	g_query_limit--;
	return 0;
}
