#include "client_types.h"

typedef Voice_14cbbe0 Voice;

extern char* g_6b7e88;
extern int g_6b7e8c;
int __cdecl fcn_0042aaa0(int h);

/* ADDRESS: GOLDTL 0x004258d0 */
int __cdecl fcn_004258d0(void)
{
	Voice* e;
	int count;
	int i;

	count = 0;
	if (g_6b7e88 != 0) {
		for (i = 0; i < g_6b7e8c; i++) {
			e = &((Voice*) g_6b7e88)[i];
			if (e->sample != 0) {
				if (fcn_0042aaa0(e->h) == 4) {
					count++;
				} else if (e->f18 != 0 && e->loop != 1 && (e->flags & 0xe) == 0) {
					count++;
				} else if ((e->flags & 0x10) != 0) {
					count++;
				}
			}
		}
	}
	return count;
}
