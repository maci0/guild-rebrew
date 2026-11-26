int __cdecl fcn_004c5620(int, char*);

#include "client_types.h"
extern pos14_7f4c00 gm_GameTime;




char* __cdecl he_StartHandlungSearch(int, int, int, ...);
char* __cdecl he_fn_Handlung(void);

void __cdecl he_AllocApTraitAction(char* action)
{
	char* existing;

	for (existing = he_StartHandlungSearch(2, 0, 0x5f, 2, *(unsigned short*) (action + 8)); existing != 0; existing = he_fn_Handlung()) {
		if (existing != action) {
			*(pos14_7f4c00*) (action + 0x52) = gm_GameTime;
			*(int*) (action + 0x84) = fcn_004c5620(-1, action);
			return;
		}
	}
	*(int*) (action + 0x70) = 0;
	action[0xba] = 0;
}
