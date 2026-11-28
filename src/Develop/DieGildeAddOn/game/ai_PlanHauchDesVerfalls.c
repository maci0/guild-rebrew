typedef struct Blk24 {
	unsigned char kind;
	char pad1[3];
	int a;
	int b;
	int c;
	int d;
	float f;
} Blk24;
// SIZE 0x18

typedef struct F8 {
	int mask;
	int b;
} F8;
// SIZE 0x8

#include "Develop/DieGildeAddOn/game/entity_record.h"
#include "Develop/DieGildeAddOn/game/game_data.h"
#include "Develop/DieGildeAddOn/game/game_player.h"

unsigned short __cdecl gm_RandomMod(int n);
int __cdecl gm_QueryEntities(int, int, int, int, int);
int __cdecl he_StartHandlungSearch(int, int, int, int, int);
int* __cdecl ai_PickIdleGraveyardWorker(char* q);
int __cdecl ai_SelectRankedCandidates(char* e, int a, int* p, int b, float r, unsigned short* out);
int __cdecl ai_FindEntityInFavorRange(char* p, int kind, F8 f, int c, float r, int* out);

/* ADDRESS: GOLDTL 0x0048f8f0 */
int __cdecl ai_PlanHauchDesVerfalls(char* e, char* q, Blk24* b1, Blk24* b2)
{
	char* p;
	int* h;
	int t;
	int v;
	unsigned short idx;

	t = 0;
	b1->d = 2;
	b1->c = *(int*) (q + 1);
	if (gm_QueryEntities(*(int*) (q + 0x5d), 2, 0, 0x204, 6) == 0)
		return 0;
	h = ai_PickIdleGraveyardWorker(q);
	if (h == 0)
		return 0;
	if (he_StartHandlungSearch(2, 0, 0x89, 3, *(int*) (q + 1)) != 0)
		return 0;
	t = 0xf00500;
	if (ai_SelectRankedCandidates(e, 1, &t, 0, gm_RandomMod(0x20) + 32.0f, &idx) == 0)
		return 0;
	p = ((char*)&((ENTITY_RECORD_VIEW*)gm_EntitySlotTable)[idx]);
	b2->c = *(int*) (p + 4);
	b2->a = h[1];
	b2->d = 4;
	v = *(int*) (p + 0x170);
	if (v != 0) {
		b2->b = *(int*) (v + 1);
		return 1;
	}
	v = *(int*) (p + 0x16c);
	if (v != 0) {
		b2->b = *(int*) (v + 1);
		return 1;
	}
	{
		F8 f;
		int out;

		f.mask = 0x7b4c4a0;
		f.b = 0;
		out = -1;
		ai_FindEntityInFavorRange(((char*)&((ENTITY_RECORD_VIEW*)gm_EntitySlotTable)[gm_LocalPlayerSlot]), 0, f, 0, 100.0f, &out);
		if (out == -1)
			return 0;
		b2->b = out;
	}
	return 1;
}
