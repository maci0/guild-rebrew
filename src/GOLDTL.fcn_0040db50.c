/* ADDRESS: GOLD 0x005f216c */
extern char g_6761ec[];



#include "Develop/DieGildeAddOn/game/ch_queue.h"
extern char* g_6b7e98;
void __cdecl fcn_00425bf0(void*, int, char*);

int __cdecl fcn_0040db50(char** a1)
{
	char* p;
	char* q;
	char* e;

	p = *a1;
	if (p == 0) {
		fcn_00425bf0(g_6b7e98, *(int*) (g_6b7e98 + 0x118), g_6761ec);
	} else {
		q = *(char**) (p + 0x128);
		if (q != 0) {
			q[0x190] = 1;
			while ((e = *(char**) (q + 0x28)) != 0) {
				fcn_004050c0(e);
			}
		}
	}
	return 0;
}
