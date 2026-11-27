


#include "Develop/DieGildeAddOn/game/game_data.h"
extern int g_6995bc[];

int __cdecl gm_AmountToUnits(int a, unsigned char k)
{
	return (int) ((float) a / g_6995bc[*(unsigned short*) (g_8680b4 + k * 0x2f4)] + 0.5);
}
