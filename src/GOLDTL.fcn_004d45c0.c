

#include "Develop/DieGildeAddOn/game/cutscene_clock.h"
extern int g_14ce8e0;
extern int g_774654;

int __cdecl fcn_005373e0(void*, int);
void __cdecl fcn_0052ae80(void);
void __cdecl fcn_004d06d0(void);
void __cdecl fcn_004cf180(void);
void __cdecl fcn_004cf6b0(void);
void __cdecl fcn_004d0070(void);

void __cdecl fcn_004d45c0(int dur)
{
	int start;

	start = g_772f30;
	if (fcn_005373e0(fcn_004d45c0, 0x7d6c6) != 0) {
		do {
			fcn_0052ae80();
			fcn_004d06d0();
			fcn_004cf180();
			fcn_004cf6b0();
			if (g_14ce8e0 != 0 || g_772f30 >= start + dur)
				g_774654 = 1;
			fcn_004d0070();
		} while (fcn_005373e0(fcn_004d45c0, 0x7d6c6) != 0);
	}
}
