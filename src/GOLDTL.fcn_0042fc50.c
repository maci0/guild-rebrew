// FUNCTION: GOLD 0x00430260
// FUNCTION: GOLDTL 0x42fc50

// SIZE 0x11c
typedef struct Node {
	char name[0x100];
	int count;
	void* data;
	struct Node* next;
	struct Node* child;
	struct Node* parent;
	char* items;
	char flag;
} Node;

extern char g_6b7fe0[];

void __cdecl fcn_0041e2e0(void*, void*);
void __cdecl m_FreeTracked(void*);

void __cdecl fcn_0042fc50(Node* n)
{
	Node* next;
	char* it;
	char* nx;

	while (n != 0) {
		it = n->items;
		next = n->next;
		while (it != 0) {
			nx = *(char**) (it + 0x114);
			fcn_0041e2e0(g_6b7fe0, it);
			it = nx;
		}
		if (n->data != 0) {
			m_FreeTracked(n->data);
			n->data = 0;
		}
		if (n->child != 0) {
			fcn_0042fc50(n->child);
		}
		m_FreeTracked(n);
		n = next;
	}
}
