


#include <stdlib.h>
#include <string.h>

typedef struct Node Node;

// SIZE 0x8
struct Node {
	Node* next;
	Node* prev;
};

#include "client_video_list.h"

Node* __cdecl AllocVideoListNode(void)
{
	Node* node;
	Node* cursor;

	node = (Node*) malloc(0x148);
	if (node != 0) {
		memset(node, 0, 0x148);
		if (g_6b6f84 != 0) {
			cursor = g_6b6f84;
			while (cursor->prev != 0) {
				cursor = cursor->prev;
			}
			cursor->prev = node;
			node->next = cursor;
		} else {
			g_6b6f84 = node;
		}
	}
	return node;
}
