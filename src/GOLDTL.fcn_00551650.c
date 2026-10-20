#include "client_types.h"

extern pos14_7f4c00 g_7f4c00;

int __cdecl fcn_005462a0(void);
int __cdecl fcn_004c5620(char a1, unsigned char* e);
struct unit* __cdecl fcn_005463a0(int n, ...);

/* ADDRESS: GOLDTL 0x00551650 */
void __cdecl fcn_00551650(char* e)
{
	int v;

	v = (int) fcn_005463a0(2, 0, 0x5e, 2, (unsigned int) *(unsigned short*) (e + 8));
	while (v != 0) {
		if (v != (int) e) {
			*(pos14_7f4c00*) (e + 0x52) = g_7f4c00;
			*(int*) (e + 0x84) = fcn_004c5620(-1, (unsigned char*) e);
			return;
		}
		v = (int) fcn_005462a0();
	}
	*(int*) (e + 0x70) = 0;
	*(char*) (e + 0xb8) = 0;
	*(int*) (e + 0x84) = fcn_004c5620(0, (unsigned char*) e);
}
