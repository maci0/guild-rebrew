#include <string.h>

typedef struct RT_POINT_NODE RT_POINT_NODE;
struct RT_POINT_NODE {
	int f0;
	int f4;
	char pad8[0x30];
	RT_POINT_NODE* prev;
	RT_POINT_NODE* next;
};
// SIZE 0x40

extern char g_6816dc[];

RT_POINT_NODE* __cdecl m_alloc(int, char*);


/* ADDRESS: GOLDTL 0x004be1f0 */
RT_POINT_NODE* __cdecl rt_AllocRoutePoint(RT_POINT_NODE* head)
{
	int n;
	RT_POINT_NODE* last;
	RT_POINT_NODE* p;
	RT_POINT_NODE* q;

	n = 0;
	last = 0;
	for (p = head; p != 0; p = p->next) {
		last = p;
		n++;
	}
	if (head != 0 && n >= 8)
		return 0;
	q = m_alloc(0x40, g_6816dc);
	memset(q, 0, sizeof(*q));
	if (last != 0)
		last->next = q;
	q->prev = last;
	q->f4 = -1;
	return q;
}
