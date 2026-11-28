

#include "Develop/DieGildeAddOn/game/client_input.h"

/* ADDRESS: GOLDDE 0x00410450 */
int __cdecl io_AcquireMouse(int enable)
{
	INPUT_DEVICE* obj;

#ifdef REBREW_GOLD
	obj = *(INPUT_DEVICE**) 0x14673cc;
#else
	obj = *(INPUT_DEVICE**) 0x14ce90c;
#endif
	if (obj == 0) {
		return 0;
	}
	if (enable != 0) {
		if (obj->vtbl->Acquire(obj) < 0) {
			return 0;
		}
	} else {
		obj->vtbl->Unacquire(obj);
	}
	return 1;
}
