#include "Develop/DieGildeAddOn/game/game_data.h"

void __cdecl d3_FreeMeshObject(char* p);

/* ADDRESS: GOLDTL 0x004438b0 */
/* ADDRESS: GOLDDE 0x0043bd00 */
char __cdecl d3_TransferObjectSceneCallback(char* node, char** moveCtx)
{
	char* p;
	char* n;

	*(int*) (node + 0x20c) = (int) moveCtx[1];
	p = *(char**) (moveCtx[0] + 0xa4);
	while (p != g_1040640) {
		n = *(char**) (p + 0x314);
		if (*(char**) (p + 0x2e4) == node) {
			d3_FreeMeshObject(p);
		}
		p = n;
	}
	return 1;
}
