


#include "Develop/DieGildeAddOn/game/game_data.h"

double __cdecl fcn_004fc460(float*);

int __cdecl fcn_004b4fa0(void)
{
	float buf[10];

	if (fcn_004fc460(buf) > 0.1)
		return 0;
	if (buf[3] < 0.3f)
		return 0;
	if (buf[1] < 0.3f)
		return 0;
	if (buf[2] < 0.3f)
		return 0;
	return 1;
}
