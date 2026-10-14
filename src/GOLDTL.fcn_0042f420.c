


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

char* __cdecl fcn_0042f420(Node* n, Node* stop, char* out)
{
	char tmp[0x100];
	Node* p;

	p = n;
	if (p == 0) {
		return 0;
	}
	strcpy(out, p->name);
	while (p != 0) {
		if (p->parent == stop) {
			break;
		}
		p = p->parent;
		strcpy(tmp, p->name);
		strcat(tmp, out);
		strcpy(out, tmp);
	}
	return out;
}
