#include "client_actions.h"

typedef struct {
	char pad0[0x4];
	int* f4;
	char pad8[0x98];
	int fa0;
	char pada4[0x8];
	int fac;
} fcn_004a8650_game;
/* SIZE 0xb0 */

/* Zero-initialized module pointer in the GOLD .data tail (VA 0x00f83654). */
char* g_f83654;

int __cdecl fcn_004c51a0(int, int, char, int);

/* ADDRESS: GOLD 0x004a8650 */
void __cdecl fcn_004a8650(void)
{
	((fcn_004a8650_game*)g_f83654)->fa0 = ((fcn_004a8650_game*)g_f83654)->fac * 3;
	fcn_004c51a0(-1, ((fcn_004a8650_game*)g_f83654)->f4[1], g_773d75,
		((fcn_004a8650_game*)g_f83654)->fac);
}
