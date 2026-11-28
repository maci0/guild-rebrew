#include <string.h>

int __cdecl d3_CollectUnusedSceneObjects(int, int*);
void __cdecl rd_AllBauplatzToSupermap(int, int);


/* ADDRESS: GOLDTL 0x004bdd40 */
/* ADDRESS: GOLDDE 0x004ab8c0 */
void __cdecl rd_AddUnusedBauplatzToSupermap(int ctx)
{
	int list[256];
	int n;
	int i;

	memset(list, 0, sizeof(list));
	n = d3_CollectUnusedSceneObjects(0, list);
	if (n != 0) {
		for (i = 0; i < n; i++) {
			if (list[i] != 0)
				rd_AllBauplatzToSupermap(ctx, list[i]);
		}
	}
}
