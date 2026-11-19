typedef int (__stdcall* g_662454_f)(int);
extern g_662454_f g_662454;
extern g_662454_f g_662454;



#include "Develop/DieGildeAddOn/game/game_data.h"

int __cdecl fcn_0042b120(int);

int __cdecl fcn_0042a390(int* audio)
{
	int r = 0;

	if (g_6b7f90 != 0) {
		if (fcn_0042b120((int) audio) >= 0) {
			if (g_662454(*audio) == 0) {
				r = -1;
			}
		} else {
			r = -1;
		}
	} else {
		r = -1;
	}
	return r;
}
