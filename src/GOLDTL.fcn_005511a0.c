#include "client_types.h"

extern pos14_7f4c00 g_7f4c00;

extern void __cdecl fcn_00546190(void* a0);
extern void __cdecl fcn_00500bb0(unsigned int* p, int a, int b, int c);
extern int __cdecl fcn_004c5620(int a, void* b);

/* ADDRESS: GOLDTL 0x005511a0 */

void __cdecl fcn_005511a0(char* a0)
{
	int v1;

	v1 = *(int*)(a0 + 0x70);
	if (v1 >= -2) {
		if (v1 >= 0) {
			if (v1 == 0) {
				if ((*(unsigned char*)(a0 + 0x78) & 2) != 0) {
					*(pos14_7f4c00*)(a0 + 0x52) = g_7f4c00;
					fcn_00500bb0((unsigned int*)(a0 + 0x52), 0, 2, 0);
					*(int*)(a0 + 0x84) = fcn_004c5620(-1, a0);
				}
			}
		} else {
			fcn_00546190(a0);
		}
	}
}
