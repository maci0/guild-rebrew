/* gm_FreeObjectListRecursive — unlink and dispose every node of the object
 * linked list rooted at *head (each node is a 0x43-byte pool slot).
 * Recursively frees each node's child list (offset 0x14) first, then hands
 * the node to gm_NoopRet2 (a free stub). Returns -1 on an empty list. */

// CFLAGS: /O2 /Gd
// FUNCTION: SERVER 0x10016710

#include <stdlib.h>

#pragma pack(push, 1)
typedef struct EntitySlot {
	short active;               /* 0x00 */
	int id;                     /* 0x02 */
	char pad[0x0e];             /* 0x06 */
	void* child;                /* 0x14 */
	char pad2[0x3f - 0x18];     /* 0x18 */
	struct EntitySlot* next;    /* 0x3f */
} EntitySlot;
#pragma pack(pop)

void __cdecl gm_NoopRet2(void* node);

int __cdecl gm_FreeObjectListRecursive(EntitySlot** head)
{
	EntitySlot* node;

	if (head == NULL)
		return 0;
	node = *head;
	if (node == NULL)
		return -1;
	do {
		*head = node->next;
		if (node->child != NULL)
			gm_FreeObjectListRecursive((EntitySlot**) &node->child);
		gm_NoopRet2(node);
		node = *head;
	} while (node != NULL);
	return 0;
}
