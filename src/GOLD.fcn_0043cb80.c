// SIZE 0x211
typedef struct Node {
	char pad0[0x1f0];
	struct Node* next;
	struct Node* prev;
	struct Node* parent;
	struct Node* child;
	char pad200[0x10];
	unsigned char root : 1;
} Node;
/* SIZE 0x214 */

void __cdecl fcn_0043cb20(Node* a, Node* b);
void __cdecl fcn_0043ca20(Node* b);

/* ADDRESS: GOLD 0x0043cb80 */
void __cdecl fcn_0043cb80(Node* a, Node* b)
{
	b->root = a == 0;
	if (a != 0) {
		if (a->child != 0) {
			fcn_0043cb20(a->child, b);
			b->parent = a;
			return;
		}
		a->child = b;
		b->parent = a;
		return;
	}
	fcn_0043ca20(b);
}
