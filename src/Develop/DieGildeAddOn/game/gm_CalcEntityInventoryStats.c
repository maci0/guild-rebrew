


#include <string.h>

typedef struct
{
	int x0;
	int n;
	int x8[16];
	unsigned short x48[16];
	int x68[16];
	int xa8;
	int xac;
	int xb0;
	char* xb4;
} Stats;
// SIZE 0xb8

char* __cdecl gm_QueryEntities(int list, int a, int b, ...);
char* __cdecl gm_NextEntityQueryMatch(void);
int __cdecl gm_GetStorageSlotCapacity(char* q, int id);
float __cdecl eval_ObjektPreis2Credits(int id, int n);

/* ADDRESS: GOLDDE 0x004f8bd0 */
int __cdecl gm_CalcEntityInventoryStats(char* e, Stats* s)
{
	char* q;
	char* r;

	memset(s, 0, sizeof(Stats));
	q = gm_QueryEntities(*(int*) (e + 0x14), 1, 0, 0x1dd);
	if (q == 0) {
		return 0;
	}
	r = gm_QueryEntities(*(int*) (q + 0x14), 1, 5);
	s->x0 = *(unsigned char*) (q + 0x1c);
	while (r != 0) {
		s->x68[s->n] = *(int*) (r + 0xe);
		s->x8[s->n] = gm_GetStorageSlotCapacity(q, *(unsigned short*) r);
		s->xa8 += s->x8[s->n];
		s->xac += *(int*) (r + 0xe);
		s->x48[s->n] = *(unsigned short*) r;
		s->n++;
		s->xb0 = (int) (eval_ObjektPreis2Credits(*(unsigned short*) r, 100) * *(int*) (r + 0xe) + s->xb0);
		r = gm_NextEntityQueryMatch();
	}
	s->xb4 = q;
	return 1;
}
