#include "g_774a78.h"

extern struct Node* g_774a78;
void __cdecl ls_FreeListNodes(void*);

/* ADDRESS: GOLD 0x005a8a70 */
/* ADDRESS: GOLDTL 0x005b1ef0 */
void __cdecl ls_FreeList774a78(void)
{
	if (g_774a78 != 0) {
		ls_FreeListNodes((void*) g_774a78);
	}
	g_774a78 = 0;
}
