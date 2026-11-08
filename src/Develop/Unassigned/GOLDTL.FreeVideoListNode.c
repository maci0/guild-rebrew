


typedef struct Node Node;

// SIZE 0x8
struct Node {
	Node* next;
	Node* prev;
};

#include "client_video_list.h"
void __cdecl free(void* p);

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
		g_6b6f84 = node->prev;
	} else {
		g_6b6f84 = 0;
	}
	free(node);
}
