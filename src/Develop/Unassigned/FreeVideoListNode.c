


typedef struct Node Node;

// SIZE 0x8
struct Node {
	Node* next;
	Node* prev;
};

#include "client_video_list.h"
void __cdecl free(void* p);

/* ADDRESS: GOLDDE 0x0041c9a0 */
void __cdecl FreeVideoListNode(Node* node)
{
	if (node == 0) {
		return;
	}
	if (node->next != 0) {
		if (node->prev != 0) {
			node->prev->next = node->next;
			node->next->prev = node->prev;
		} else {
			node->next->prev = 0;
		}
	} else if (node->prev != 0) {
		node->prev->next = 0;
		tp_VideoListHead = node->prev;
	} else {
		tp_VideoListHead = 0;
	}
	free(node);
}
