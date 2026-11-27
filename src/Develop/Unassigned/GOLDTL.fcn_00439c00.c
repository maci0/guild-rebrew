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

void __cdecl d3_AppendObjectSibling(Node* a, Node* b);
void __cdecl fcn_00439aa0(Node* b);

/* ADDRESS: GOLDTL 0x00439c00 */
void __cdecl d3_AttachSceneNode(Node* a, Node* b)
{
	b->root = a == 0;
	if (a != 0) {
		if (a->child != 0) {
			d3_AppendObjectSibling(a->child, b);
			b->parent = a;
			return;
		}
		a->child = b;
		b->parent = a;
		return;
	}
	fcn_00439aa0(b);
}
