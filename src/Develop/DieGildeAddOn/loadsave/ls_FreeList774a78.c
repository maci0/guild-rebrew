#include "Develop/DieGildeAddOn/loadsave/g_774a78.h"

extern struct Node* hp_ProdEntryList;
void __cdecl ls_FreeListNodes(void*);

/* ADDRESS: GOLD 0x005a8a70 */
/* ADDRESS: GOLDTL 0x005b1ef0 */
void __cdecl ls_FreeList774a78(void)
{
	if (hp_ProdEntryList != 0) {
		ls_FreeListNodes((void*) hp_ProdEntryList);
	}
	hp_ProdEntryList = 0;
}
