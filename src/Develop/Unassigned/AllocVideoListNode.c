


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
		if (tp_VideoListHead != 0) {
			cursor = tp_VideoListHead;
			while (cursor->prev != 0) {
				cursor = cursor->prev;
			}
			cursor->prev = node;
			node->next = cursor;
		} else {
			tp_VideoListHead = node;
		}
	}
	return node;
}
