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
#include "Develop/DieGildeAddOn/game/entity_record.h"
typedef struct F8 {
	int mask;
	int b;
} F8;
// SIZE 0x8

extern char g_7f4ca0[];
#include "Develop/DieGildeAddOn/game/game_data.h"

unsigned short __cdecl gm_RandomMod(int n);
int __cdecl fcn_00502cd0(int, int, int, int, int);
int __cdecl he_StartHandlungSearch(int, int, int, int, int);
int* __cdecl ai_PickIdleGraveyardWorker(char* q);
int __cdecl ai_SelectRankedCandidates(char* e, int a, int* p, float lo, float hi,
	unsigned short* out);
int __cdecl ai_FindEntityInFavorRange(char* p, int kind, F8 f, int c, float r, int* out);

/* ADDRESS: GOLDTL 0x0048f4f0 */
int __cdecl ai_FindGraveyardTargets(char* e, char* q, Blk24* b1, Blk24* b2)
{
	char* p;
	int* h;
	int t;
	int v;
	unsigned short idx;

	t = 0;
	b1->d = 0;
	b1->c = *(int*) (q + 1);
	if (*(int*) (e + 0x194) < 4)
		return 0;
	if (fcn_00502cd0(*(int*) (q + 0x5d), 2, 0, 0x1fc, 6) == 0)
		return 0;
	h = ai_PickIdleGraveyardWorker(q);
	if (h == 0)
		return 0;
	if (he_StartHandlungSearch(2, 0, 0x88, 3, *(int*) (q + 1)) != 0)
		return 0;
	t = 0xf00500;
	if (ai_SelectRankedCandidates(e, 1, &t, 0, gm_RandomMod(0x20) + 32.0f, &idx) == 0)
		return 0;
	p = ((char *)&((ENTITY_RECORD_VIEW *)g_7f4ca0)[idx]);
	v = *(int*)&((ENTITY_RECORD_VIEW*)p)->ptr_170;
	if (v != 0) {
		b2->b = *(int*) (v + 1);
	} else {
		v = *(int*)&((ENTITY_RECORD_VIEW*)p)->ptr_16c;
		if (v != 0) {
			b2->b = *(int*) (v + 1);
		} else {
			F8 f;
			int found;
			found = -1;
			f.mask = 0x7b4c4a0;
			f.b = 0;
			ai_FindEntityInFavorRange(e, 0, f, 0, 100.0f, &found);
			if (found == -1)
				return 0;
			b2->b = found;
		}
	}
	b2->c = *(int*)&((ENTITY_RECORD_VIEW*)p)->entity_id;
	b2->a = h[1];
	b2->d = 4;
	return 1;
}
