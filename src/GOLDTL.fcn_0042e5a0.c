


#include <string.h>

// SIZE 0x11c
typedef struct Node {
	char name[0x100];
	int count;
	int data;
	struct Node* next;
	struct Node* child;
	struct Node* parent;
	int pad114;
	char flag;
} Node;

extern char g_679e68[];

int __cdecl fcn_0042e4d0(char*, Node*);
void* __cdecl m_alloc(int, void*);

Node* __cdecl fcn_0042e5a0(char* name, Node* parent)
{
	Node* p;
	Node* n;

	if (parent != 0) {
		for (p = parent->child; p != 0; p = p->next) {
			if (fcn_0042e4d0(name, p) == 0) {
				return p;
			}
		}
	}
	n = (Node*) m_alloc(0x11c, g_679e68);
	strcpy(n->name, name);
	n->flag = 0;
	n->parent = parent;
	if (parent != 0) {
		if (parent->child == 0) {
			parent->child = n;
		} else {
			p = parent->child;
			while (p->next != 0) {
				p = p->next;
			}
			p->next = n;
		}
	}
	return n;
}
