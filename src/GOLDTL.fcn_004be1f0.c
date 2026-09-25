#include <string.h>

typedef struct fcn_004be1f0_node fcn_004be1f0_node;
struct fcn_004be1f0_node {
	int f0;
	int f4;
	char pad8[0x30];
	fcn_004be1f0_node* prev;
	fcn_004be1f0_node* next;
};
// SIZE 0x40

extern char g_6816dc[];

fcn_004be1f0_node* __cdecl fcn_0041db70(int, char*);

// FUNCTION: GOLDTL 0x4be1f0
// SIZE: 81
// FUNCTION: GOLD 0x004bd950
// SIZE: 96

fcn_004be1f0_node* __cdecl fcn_004be1f0(fcn_004be1f0_node* head)
{
	int n;
	fcn_004be1f0_node* last;
	fcn_004be1f0_node* p;
	fcn_004be1f0_node* q;

	n = 0;
	last = 0;
	for (p = head; p != 0; p = p->next) {
		last = p;
		n++;
	}
	if (head != 0 && n >= 8)
		return 0;
	q = fcn_0041db70(0x40, g_6816dc);
	memset(q, 0, sizeof(*q));
	if (last != 0)
		last->next = q;
	q->prev = last;
	q->f4 = -1;
	return q;
}
