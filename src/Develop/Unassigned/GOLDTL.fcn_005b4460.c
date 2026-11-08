

extern int g_14ce8e0;
#include "client_dialog_state.h"

void __cdecl d2_CreateScrollPerga(void);
int __cdecl fcn_005373e0(void*, int);
void __cdecl d2_UpdateScrollPerga(void);
void __cdecl fcn_005355f0(void);

void __cdecl fcn_005b4460(void)
{
	d2_CreateScrollPerga();
	while (fcn_005373e0(fcn_005b4460, 0x657c7) != 0) {
		d2_UpdateScrollPerga();
		if (g_14ce8e0 != 0) {
			g_774654 = 1;
		}
	}
	fcn_005355f0();
}
