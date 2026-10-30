#include "client_types.h"

typedef Voice_14cbbe0 Voice;

extern char* g_6b7e88;
extern int g_6b7e8c;
int __cdecl fcn_0042aaa0(int h);

/* ADDRESS: GOLDTL 0x004258d0 */
int __cdecl fcn_004258d0(void)
{
	int count;
	int i;

	count = 0;
	if (g_6b7e88 != 0) {
		for (i = 0; i < g_6b7e8c; i++) {
			if (((Voice*) g_6b7e88)[i].sample != 0) {
				if (fcn_0042aaa0(((Voice*) g_6b7e88)[i].h) == 4) {
					count++;
				} else if (((Voice*) g_6b7e88)[i].f18 != 0 && ((Voice*) g_6b7e88)[i].loop != 1 &&
				    (((Voice*) g_6b7e88)[i].flags & 0xe) == 0) {
					count++;
				} else if ((((Voice*) g_6b7e88)[i].flags & 0x10) != 0) {
					count++;
				}
			}
		}
	}
	return count;
}
