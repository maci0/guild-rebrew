// FUNCTION: GOLDTL 0x0041f940
// FUNCTION: GOLD 0x004236b0

typedef struct Node Node;

// SIZE 0x8
struct Node {
	Node* next;
	Node* prev;
};

extern Node* g_6b6f84;
void __cdecl fcn_0064dfda(void* p);

void __cdecl fcn_0041f940(Node* n)
{
	if (n == 0) {
		return;
	}
	if (n->next != 0) {
		if (n->prev != 0) {
			n->prev->next = n->next;
			n->next->prev = n->prev;
		} else {
			n->next->prev = 0;
		}
	} else if (n->prev != 0) {
		n->prev->next = 0;
		g_6b6f84 = n->prev;
	} else {
		g_6b6f84 = 0;
	}
	fcn_0064dfda(n);
}
