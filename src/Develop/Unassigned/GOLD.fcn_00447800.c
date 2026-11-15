#include "Develop/Units/d3/d3_d3d.h"

/* ADDRESS: GOLD 0x00447800 */
void __cdecl fcn_00447800(char* self)
{
	char* list;
	char* ctx;
	unsigned char** items;
	int n;
	int i;
	list = *(char**) (self + 0x1cc);
	if (list != 0) {
		ctx = *(char**) (list + 0x10);
		if (ctx != 0) {
			n = *(int*) (ctx + 0x1e0);
			items = *(unsigned char***) (list + 0x14);
			for (i = 0; i < n; i++) {
				if (items[i] != 0 && *(void**) (items[i] + 0x64) != 0 && !(items[i][0x68] & 0x80)) {
					d3d_PrecacheTexture(*(void**) (items[i] + 0x64));
					items[i][0x68] |= 0x80;
				}
			}
		}
	}
}
