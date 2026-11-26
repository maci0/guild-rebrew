#include "Develop/DieGildeAddOn/game/game_data.h"

int __cdecl io_FormatTextBuffer(char*, char*, int);
int __cdecl gm_HandleVerhoer(int, int);

/* ADDRESS: GOLDTL 0x004f9f70 */
int __cdecl gm_DispatchVerhoerAction(int actor, int req)
{
	int res;
	int mode;
	int* target;

	mode = *(int*) req;
	res = 0;
	*(char*) (req + 0x14) = 0;
	if (mode == 3 || mode == 1) {
		if ((*(int*) (actor + 0x1cc) & 0x800) == 0) {
			return 1;
		}
		if (*(char*) (actor + 2) == 6) {
			io_FormatTextBuffer((char*) (req + 0x14), "%s", 0x1e0d);
		}
		if (*(int*) (actor + 0x1c8) & 0x200) {
			return 9;
		}
		if (*(int*) (actor + 0x1cc) & 0x40000) {
			return 1;
		}
		if (*(int*) req == 3) {
			res = gm_HandleVerhoer(actor, req);
		}
		return res | 2;
	}
	if (mode == 4 || mode == 2) {
		if ((*(int*) (actor + 0x1c8) & 0x100) == 0 ||
		    *(int**) (req + 0x21c) == 0) {
			return 1;
		}
		target = *(int**) (req + 0x21c);
		if ((*(int*) ((char*) target + 0x1cc) & 0x800) == 0) {
			return 1;
		}
		if (*(int*) ((char*) target + 0x1cc) & 0x40000) {
			return 1;
		}
		if (mode == 4) {
			res = gm_HandleVerhoer(actor, req);
		} else if (*(char*) (actor + 2) == 6) {
			io_FormatTextBuffer((char*) (req + 0x14), "%s", 0x1e0d);
		}
		return res | 0xa;
	}
	return 1;
}
