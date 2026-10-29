#include "client_types.h"
extern Win_1015f40 g_1015f40[0x60];
extern Obj_1038140 g_1038140[];
extern int g_772534;

int __cdecl fcn_00471f80(int id);

/* ADDRESS: GOLDTL 0x00471ff0 */
int __cdecl fcn_00471ff0(int j, int k)
{
	char* m;

	m = ((char*)g_1015f40) + ((int*) (((char*)g_1038140) + g_772534 * 0x2bc + 4))[k] * 0x3cc;
	if (j > *(int*) (m + 0x2c)) {
		return 0;
	}
	return fcn_00471f80((*(int**) (m + 0x28))[j]);
}
