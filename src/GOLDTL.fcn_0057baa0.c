int __cdecl fcn_004c5620(int, char*);

#include "client_types.h"
extern pos14_7f4c00 g_7f4c00;

// FUNCTION: GOLDTL 0x57baa0
// SIZE: 228

void __cdecl fcn_004acf60(void);
void __cdecl fcn_004ad1c0(void);
void __cdecl fcn_004ad2e0(void);
void __cdecl fcn_004ad630(void);
void __cdecl fcn_004ad6a0(void);
void __cdecl fcn_00500bb0(pos14_7f4c00*, int, int, int);
void __cdecl sim_SetSyncParams(pos14_7f4c00*, int, int, int);

void __cdecl fcn_0057baa0(char* o)
{
	if (o[0x78] & 4) {
		return;
	}
	switch (*(int*) (o + 0x70)) {
	case 0:
		fcn_004acf60();
		fcn_00500bb0((pos14_7f4c00*) (o + 0x52), 2, 0, 0);
		fcn_004c5620(1, o);
		break;
	case 1:
		fcn_004ad1c0();
		fcn_00500bb0((pos14_7f4c00*) (o + 0x52), 2, 0, 0);
		fcn_004c5620(2, o);
		break;
	case 2:
		fcn_004ad2e0();
		sim_SetSyncParams((pos14_7f4c00*) (o + 0x52), 0x16, 0, 0);
		fcn_004c5620(3, o);
		break;
	case 3:
		fcn_004ad630();
		sim_SetSyncParams((pos14_7f4c00*) (o + 0x52), 6, 5, 0);
		((pos14_7f4c00*) (o + 0x52))->a++;
		fcn_004c5620(4, o);
		break;
	case 4:
		fcn_004ad6a0();
		sim_SetSyncParams((pos14_7f4c00*) (o + 0x52), 0xa, 0, 0);
		fcn_004c5620(0, o);
		break;
	}
}
