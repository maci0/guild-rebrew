#include "client_types.h"
extern pos14_7f4c00 g_7f4c00;

unsigned short __cdecl gm_RandomMod(int);

/* ADDRESS: GOLD 0x004a9150 */
/* ADDRESS: GOLDTL 0x004a9270 */

int __cdecl fcn_004a9270(int a, char* e)
{
	if (*(int*) (e + 0x194) >= 8 && *(unsigned int*) (e + 4) % 4 == (*(int*)&g_7f4c00) % 4 && gm_RandomMod(4) == 0)
		return 1;
	return 0;
}
