// FUNCTION: GOLDTL 0x5b1c90
// SIZE: 75

void __cdecl fcn_0041ddd0(void*);

// SIZE 0x4c
typedef struct Node {
	int id;
	char pad[0x44];
	struct Node* next;
} Node;

int __cdecl fcn_005b1c90(int id)
{
	Node* prev;
	Node* n;

	prev = 0;
	for (n = *(Node**) 0x774a78; n != 0; n = n->next) {
		if (n->id == id) {
			break;
		}
		prev = n;
	}
	if (n == 0) {
		return -1;
	}
	if (prev != 0) {
		prev->next = n->next;
	} else {
		*(Node**) 0x774a78 = n->next;
	}
	fcn_0041ddd0(n);
	return 0;
}
