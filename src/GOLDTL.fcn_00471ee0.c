extern char* g_1015ea0;
#include "client_types.h"
extern Obj_1038140 g_1038140[];
extern int g_772534;

// FUNCTION: GOLDTL 0x471ee0
void __cdecl fcn_00471ee0(int i, int v)
{
	*(int*) (g_1015ea0 + (*(int*) (((char*)g_1038140) + g_772534 * 0x2bc + 0x194) + i) * 0x2f4 + 0x38) = v;
}
