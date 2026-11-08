#include "Develop/DieGildeAddOn/game/spiel.h"

/* ADDRESS: GOLD 0x00503fa0 */
/* ADDRESS: GOLDTL 0x00506fd0 */
int __cdecl fcn_00506fd0(int a)
{
	int k;

	k = gm_MapEntityStatRange(a);
	if (k == 0) {
		return 0;
	}
	switch (k) {
	case 11:
		return 0x4;
	case 9:
		return 0x5;
	case 7:
		return 0x7;
	case 6:
		return 0x8;
	case 8:
		return 0x9;
	case 5:
		return 0xe;
	case 12:
		return 0x10;
	case 1:
		return 0x12;
	case 10:
		return 0x13;
	case 2:
		return 0x14;
	case 3:
		return 0x15;
	case 4:
		return 0x16;
	case 13:
		return 0x1d;
	case 16:
		return 0;
	}
	return 0;
}

/* ADDRESS: GOLD 0x00504290 */
/* ADDRESS: GOLDTL 0x005072c0 */
int __cdecl fcn_005072c0(int a)
{
	int k;

	k = gm_MapEntityStatRange(a);
	if (k == 0) {
		return 0;
	}
	switch (k) {
	case 11:
		return 0xb;
	case 9:
		return 0xe;
	case 7:
		return 0x14;
	case 6:
		return 0x17;
	case 8:
		return 0x1a;
	case 5:
		return 0x21;
	case 12:
		return 0x27;
	case 1:
		return 0x29;
	case 10:
		return 0x2c;
	case 2:
		return 0x2f;
	case 3:
		return 0x32;
	case 4:
		return 0x35;
	case 13:
		return 0x48;
	case 15:
		return 0x51;
	case 14:
		return 0x4e;
	}
	return 0;
}
