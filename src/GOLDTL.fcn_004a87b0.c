typedef struct {
	int state;
	int flag;
	int c;
	int d;
} fcn_004a87b0_slot;
// SIZE 0x10

typedef struct {
	char pad0[0x4];
	int* f4;
	char pad8[0x98];
	int fa0;
	char pada4[0x14];
	short fb8;
} fcn_004a87b0_game;

extern char* g_1007cd4;
#include "client_types.h"
extern slot_1007ce8 g_1007ce8[];
extern unsigned char g_773d75;

short __cdecl fcn_004a82b0(void);
void __cdecl fcn_004c51a0(int, int, char, int);

// FUNCTION: GOLDTL 0x4a87b0
// SIZE: 94

void __cdecl fcn_004a87b0(void)
{
	int i;

	((fcn_004a87b0_game*)g_1007cd4)->fb8 = fcn_004a82b0();
	if (((fcn_004a87b0_game*)g_1007cd4)->fb8 == 0)
		fcn_004c51a0(((fcn_004a87b0_game*)g_1007cd4)->f4[1], -1, (*(char*)&g_773d75), ((fcn_004a87b0_game*)g_1007cd4)->fa0);
	for (i = 0; i < 24; i++) {
		((fcn_004a87b0_slot*)g_1007ce8)[i].state = 3;
		((fcn_004a87b0_slot*)g_1007ce8)[i].flag = 0;
	}
}
