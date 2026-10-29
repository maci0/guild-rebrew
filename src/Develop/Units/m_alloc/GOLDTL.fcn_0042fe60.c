

#include <string.h>

// SIZE 0x18
typedef struct Entry {
	int a;
	int b;
	int open;
	int c;
	int d;
	int e;
} Entry;

// SIZE 0x11c
typedef struct Node {
	char name[0x100];
	int count;
	Entry* data;
	struct Node* next;
	struct Node* child;
	struct Node* parent;
	char* items;
	char flag;
} Node;

Entry* __cdecl fcn_0042f120(int, int, Node**);
void __cdecl fcn_0042f240(Entry*, Node*, int, char*);
void __cdecl fcn_0042e570(char*);
void __cdecl m_FreeTracked(void*);
int __cdecl fcn_0064f6bb(char*);

char __cdecl fcn_0042fe60(int a1, int a2)
{
	Node* dir;
	char buf[0x100];
	Entry* e;
	Node* d;

	e = fcn_0042f120(a1, a2, &dir);
	if (e != 0 && e->open == 0) {
		d = dir;
		if (d != 0 && d->flag != 0) {
			fcn_0042f240(e, d, 0, buf);
			fcn_0042e570(buf);
			if (--d->count == 0) {
				m_FreeTracked(d->data);
				d->data = 0;
			} else {
				memmove(e, e + 1, (d->count - (e - d->data)) * sizeof(Entry));
			}
			return fcn_0064f6bb(buf) == 0;
		}
	}
	return 0;
}
