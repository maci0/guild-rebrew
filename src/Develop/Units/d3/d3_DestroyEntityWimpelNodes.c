#include "Develop/Units/d3/d3_object.h"
extern int d3_ActiveScene;
#include "Develop/DieGildeAddOn/game/game_data.h"

// SIZE 0x84
struct D3_WIMPEL_NODE_LIST {
	int n;
	char* a[32];
};



#include <string.h>

void __cdecl d3_VisitSceneObjects(int, char*, int, void*, struct D3_WIMPEL_NODE_LIST*);
char __cdecl d3_CollectWimpelNodes(char*, struct D3_WIMPEL_NODE_LIST*);
void __cdecl d3_RemoveSubTreeFromCellTree(char*, int);


#ifdef REBREW_GOLD
#define OBJ_SND_STATE_OFF 0x1f0
#define OBJ_SND_FLAG_OFF 0x210
#else
#define OBJ_SND_STATE_OFF 0x1f4
#define OBJ_SND_FLAG_OFF 0x214
#endif

/* ADDRESS: GOLD 0x005286e0 */
/* ADDRESS: GOLDDE 0x00516710 */
void __cdecl d3_DestroyEntityWimpelNodes(char* e)
{
	struct D3_WIMPEL_NODE_LIST l;
	char* o;
	int saved;
	int i;

	o = *(char**) (e + 0x61);
	if (o != 0) {
		memset(&l, 0, sizeof(l));
		if ((o[OBJ_SND_FLAG_OFF] & 1) == 0) {
			saved = *(int*) (o + OBJ_SND_STATE_OFF);
			*(int*) (o + OBJ_SND_STATE_OFF) = 0;
			d3_VisitSceneObjects(d3_ActiveScene, *(char**) (e + 0x61), 0x40, (void*) d3_CollectWimpelNodes, &l);
			*(int*) (*(char**) (e + 0x61) + OBJ_SND_STATE_OFF) = saved;
		} else {
			d3_VisitSceneObjects(d3_ActiveScene, o, 0x40, (void*) d3_CollectWimpelNodes, &l);
		}
		for (i = 0; i < l.n; i++) {
			if (g_773dd8 != 0) {
				d3_RemoveSubTreeFromCellTree(l.a[i], g_773dd8);
			}
			d3_DestroyObject((D3_OBJECT*) (l.a[i]));
		}
	}
}
