typedef struct Rec38 {
	char pad0[0x24];
	int a;
	int b;
	char pad2c[0xc];
} Rec38;
// SIZE 0x38

#include "Develop/DieGildeAddOn/game/game_data.h"

char* __cdecl fcn_0064f026(char* s, const char* delim);
int __cdecl atoi(const char* s);

/* ADDRESS: GOLDTL 0x0044d500 */
void __cdecl d3_ParseMeshMaterialRef(int unused, char* ctx)
{
	char* tok;

	tok = fcn_0064f026(0, " ");
	(*(Rec38**) (ctx + 0x20))[*(int*) (ctx + 0x18)].a = -1;
	(*(Rec38**) (ctx + 0x20))[*(int*) (ctx + 0x18)].b = atoi(tok);
	*(int*) (ctx + 0x18) += 1;
}
