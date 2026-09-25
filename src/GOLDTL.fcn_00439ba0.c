typedef struct Node {
	char pad0[0x1f4];
	struct Node* next;
	struct Node* prev;
	struct Node* parent;
	struct Node* child;
	char pad204[0x10];
	unsigned char root : 1;
} Node;
// SIZE 0x218

// FUNCTION: GOLDTL 0x439ba0
// SIZE: 87
void __cdecl fcn_00439ba0(Node* a, Node* b)
{
	Node* p;

	b->root = a->parent == 0;
	b->parent = a->parent;
	p = a;
	while (p->next != 0) {
		p = p->next;
	}
	p->next = b;
	b->prev = p;
}
