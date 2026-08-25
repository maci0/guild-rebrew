/* gm_RemoveLinkedNodeById — removes a linked-list node by id. */

#include <stddef.h>

// FUNCTION: SERVER 0x10016680

extern int g_query_limit; /* 0x10035450 */

void __cdecl gm_FreeObjectListRecursive(void* children);
void __cdecl gm_NoopRet2(void* node);

/* Linked-list node: active flag, unique id, child-list head, next pointer. */
#pragma pack(push, 1)
typedef struct LinkedNode {
	short active;             /* 0x00 */
	int id;                   /* 0x02 */
	char pad0[0x0e];          /* 0x06 */
	struct LinkedNode* children; /* 0x14 */
	char pad1[0x27];          /* 0x18 */
	struct LinkedNode* next;  /* 0x3f */
} LinkedNode;
#pragma pack(pop)

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
	node->active = 0;
	g_query_limit--;
	return 0;
}
