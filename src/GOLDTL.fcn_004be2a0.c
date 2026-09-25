typedef struct {
	int v[6];
} fcn_004be2a0_block;
// SIZE 0x18

typedef struct fcn_004be2a0_node fcn_004be2a0_node;
struct fcn_004be2a0_node {
	int f0;
	int f4;
	fcn_004be2a0_block a;
	fcn_004be2a0_block b;
	fcn_004be2a0_node* prev;
	fcn_004be2a0_node* next;
};

fcn_004be2a0_node* __cdecl fcn_004be1f0(fcn_004be2a0_node*);

// FUNCTION: GOLD 0x004bda00
// SIZE: 81
// FUNCTION: GOLDTL 0x4be2a0
// SIZE: 81

fcn_004be2a0_node* __cdecl fcn_004be2a0(fcn_004be2a0_node* src)
{
	fcn_004be2a0_node* q;
	fcn_004be2a0_node* head;

	q = 0;
	head = 0;
	for (; src != 0; src = src->next) {
		q = fcn_004be1f0(q);
		if (head == 0)
			head = q;
		q->a = src->a;
		q->f4 = src->f4;
		q->b = src->b;
		q->f0 = src->f0;
	}
	return head;
}
