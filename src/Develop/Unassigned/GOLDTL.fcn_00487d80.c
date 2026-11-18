typedef struct Rec {
	char type;
	char rest[0x40];
} Rec;
// SIZE 0x41

#include "Develop/DieGildeAddOn/game/production_goods.h"





// SIZE 0x58

extern char* lpObjektePROT;
#include "client_types.h"
extern Seg g_100b0c0[];
 

/* ADDRESS: GOLDTL 0x00487d80 */
void __cdecl fcn_00487d80(int* ca, int* cb, PRODUCTION_GOODS_RECORD* n)
{
	int i;
	Seg* s;

	if (!(n->flags & 1)) {
		if (((Rec*)lpObjektePROT)[n->goods_id].type == 0x17 || ((Rec*)lpObjektePROT)[n->goods_id].type == 0x25) {
			(*ca)++;
		} else {
			(*cb)++;
		}
		n->flags |= 1;
	}
	for (i = 0; i < 4; i++) {
		if (n->building_indices[i] < 0) {
			continue;
		}
		s = &g_100b0c0[n->building_indices[i]];
		if (!(s->flags & 1)) {
			if (((Rec*)lpObjektePROT)[s->id].type == 0x17 || ((Rec*)lpObjektePROT)[s->id].type == 0x25) {
				(*ca)++;
			} else {
				(*cb)++;
			}
			s->flags |= 1;
			if (s->next != -1) {
				((PRODUCTION_GOODS_RECORD*)g_100d0c0)[s->next].flags |= 1;
			}
		}
		if (s->next != -1) {
			fcn_00487d80(ca, cb, &((PRODUCTION_GOODS_RECORD*)g_100d0c0)[s->next]);
		}
	}
}
