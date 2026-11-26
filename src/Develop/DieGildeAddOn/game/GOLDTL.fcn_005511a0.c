#include "client_types.h"

extern pos14_7f4c00 gm_GameTime;

extern void __cdecl he_FreeAction(void* a0);
extern void __cdecl gm_AddTime(unsigned int* p, int a, int b, int c);
extern int __cdecl fcn_004c5620(int a, void* b);


/* ADDRESS: GOLDTL 0x005511a0 */
void __cdecl he_RunAction0x5a(char* a0)
{
	int state;

	state = *(int*)(a0 + 0x70);
	if (state >= -2) {
		if (state >= 0) {
			if (state == 0) {
				if ((*(unsigned char*)(a0 + 0x78) & 2) != 0) {
					*(pos14_7f4c00*)(a0 + 0x52) = gm_GameTime;
					gm_AddTime((unsigned int*)(a0 + 0x52), 0, 2, 0);
					*(int*)(a0 + 0x84) = fcn_004c5620(-1, a0);
				}
			}
		} else {
			he_FreeAction(a0);
		}
	}
}
