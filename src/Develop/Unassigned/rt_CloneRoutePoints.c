typedef struct {
	int v[6];
} ROUTE_BLOCK;
// SIZE 0x18

typedef struct ROUTE_NODE ROUTE_NODE;
struct ROUTE_NODE {
	int f0;
	int f4;
	ROUTE_BLOCK a;
	ROUTE_BLOCK b;
	ROUTE_NODE* prev;
	ROUTE_NODE* next;
};

ROUTE_NODE* __cdecl rt_AllocRoutePoint(ROUTE_NODE*);


/* ADDRESS: GOLDTL 0x004be2a0 */
/* ADDRESS: GOLDDE 0x004abe20 */
ROUTE_NODE* __cdecl rt_CloneRoutePoints(ROUTE_NODE* src)
{
	ROUTE_NODE* q;
	ROUTE_NODE* head;

	q = 0;
	head = 0;
	for (; src != 0; src = src->next) {
		q = rt_AllocRoutePoint(q);
		if (head == 0)
			head = q;
		q->a = src->a;
		q->f4 = src->f4;
		q->b = src->b;
		q->f0 = src->f0;
	}
	return head;
}
