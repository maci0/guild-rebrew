#include "Develop/DieGildeAddOn/game/entity_record.h"








#include "client_types.h"
extern pos14_7f4c00 gm_GameTime;

char* __cdecl gm_LookupEntityRecordById(int id);
char* __cdecl he_StartHandlungSearch(int a, int b, int c);
char* __cdecl he_fn_Handlung(void);
int __cdecl gm_FindSimilarEntities(char* e, int a2, int kind, float lo, float hi, unsigned short* ids);
unsigned short __cdecl gm_RandomMod(int n);

/* ADDRESS: GOLD 0x004a91a0 */
/* ADDRESS: GOLDTL 0x004a92c0 */
int __cdecl ai_PreparePrivBeleidigung(int unused1, char* actor, int ctx, int unused4, char* out)
{
	unsigned short ids[12];
	char* p;
	int n;
	int kind;

	if ((*(int*)&gm_GameTime) % 4 == (*(int*) (actor + 4) & 3) && !gm_LookupEntityRecordById(*(int*) (actor + 0x5c))) {
		for (p = he_StartHandlungSearch(1, 0, 0x41); p; p = he_fn_Handlung()) {
			if (*(int*) (p + 0xb0) == *(int*) (actor + 4) || *(int*) (p + 0xac) == *(int*) (actor + 4)) {
				return 0;
			}
		}
		kind = (actor[9] ? -1 : 0) + 0xc0140a;
		n = gm_FindSimilarEntities(actor, 0xc, kind, 30.0f, 100.0f, ids);
		if (n) {
			out[0] = 7;
			*(int*) (out + 4) = ((ENTITY_RECORD*)g_7f4ca0)[ids[gm_RandomMod(n)]].entity_id;
			return 1;
		}
	}
	return 0;
}
