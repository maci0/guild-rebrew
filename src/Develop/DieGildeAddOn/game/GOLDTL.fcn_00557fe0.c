#include "Develop/DieGildeAddOn/game/spiel.h"



#include "client_types.h"
extern pos14_7f4c00 gm_GameTime;
#include "Develop/DieGildeAddOn/game/game_data.h"


void __cdecl d3_SelectSceneContext(int, int);
char* __cdecl fcn_00557f00(char*);
char* __cdecl fcn_00557f70(char*);
int __cdecl fcn_00500cb0(pos14_7f4c00*, char*);
#include "Develop/Units/m_alloc/m_alloc_checks.h"
void __cdecl fcn_00452420(char*);
void __cdecl he_FreeAction(char*);

void __cdecl he_RunTimedEffectAction(char* action)
{
	char* target;
	int saved_ctx;

	switch (*(int*) (action + 0x70)) {
	case 0:
		gm_ResolveEntityById((void**) (&target), 0, 0, *(int*) (action + 0xac));
		if (target == 0 || *(char**) (target + 0x61) == 0) {
			goto kill;
		}
		saved_ctx = d3_CurrentContextIndex;
		d3_SelectSceneContext(0, 1);
		if (*(unsigned short*) (action + 0xc2) == 0x177) {
			*(char**) (action + 0xb0) = fcn_00557f00(target);
		} else if (*(unsigned short*) (action + 0xc2) == 0x178) {
			*(char**) (action + 0xb0) = fcn_00557f70(target);
		}
		d3_SelectSceneContext(saved_ctx, 1);
		*(int*) (action + 0x70) = *(char**) (action + 0xb0) != 0 ? 1 : -1;
		break;
	case 1:
		if (fcn_00500cb0(&gm_GameTime, action + 0xb4) == 1) {
			if (*(char**) (action + 0xb0) != 0 && m_is_tracked(*(char**) (action + 0xb0)) != 0) {
				*(int*) (*(char**) (action + 0xb0) + 0x24) = 0;
			}
			*(int*) (action + 0x70) = 2;
		} else if (*(char**) (action + 0xb0) == 0) {
			*(int*) (action + 0x70) = 0;
		}
		break;
	case 2:
		if (*(char**) (action + 0xb0) == 0 || (*(*(char**) (action + 0xb0) + 0x20) & 2) != 0) {
			*(int*) (action + 0x70) = -1;
		}
		break;
	case -2:
	case -1:
		gm_ResolveEntityById((void**) (&target), 0, 0, *(int*) (action + 0xac));
		if (*(char**) (action + 0xb0) != 0 && m_is_tracked(*(char**) (action + 0xb0)) != 0) {
			saved_ctx = d3_CurrentContextIndex;
			d3_SelectSceneContext(0, 1);
			fcn_00452420(*(char**) (action + 0xb0));
			d3_SelectSceneContext(saved_ctx, 1);
		}
kill:
		he_FreeAction(action);
		break;
	}
}
