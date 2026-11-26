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

void __cdecl fcn_00557fe0(char* u)
{
	char* x;
	int t;

	switch (*(int*) (u + 0x70)) {
	case 0:
		gm_ResolveEntityById((void**) (&x), 0, 0, *(int*) (u + 0xac));
		if (x == 0 || *(char**) (x + 0x61) == 0) {
			goto kill;
		}
		t = d3_CurrentContextIndex;
		d3_SelectSceneContext(0, 1);
		if (*(unsigned short*) (u + 0xc2) == 0x177) {
			*(char**) (u + 0xb0) = fcn_00557f00(x);
		} else if (*(unsigned short*) (u + 0xc2) == 0x178) {
			*(char**) (u + 0xb0) = fcn_00557f70(x);
		}
		d3_SelectSceneContext(t, 1);
		*(int*) (u + 0x70) = *(char**) (u + 0xb0) != 0 ? 1 : -1;
		break;
	case 1:
		if (fcn_00500cb0(&gm_GameTime, u + 0xb4) == 1) {
			if (*(char**) (u + 0xb0) != 0 && m_is_tracked(*(char**) (u + 0xb0)) != 0) {
				*(int*) (*(char**) (u + 0xb0) + 0x24) = 0;
			}
			*(int*) (u + 0x70) = 2;
		} else if (*(char**) (u + 0xb0) == 0) {
			*(int*) (u + 0x70) = 0;
		}
		break;
	case 2:
		if (*(char**) (u + 0xb0) == 0 || (*(*(char**) (u + 0xb0) + 0x20) & 2) != 0) {
			*(int*) (u + 0x70) = -1;
		}
		break;
	case -2:
	case -1:
		gm_ResolveEntityById((void**) (&x), 0, 0, *(int*) (u + 0xac));
		if (*(char**) (u + 0xb0) != 0 && m_is_tracked(*(char**) (u + 0xb0)) != 0) {
			t = d3_CurrentContextIndex;
			d3_SelectSceneContext(0, 1);
			fcn_00452420(*(char**) (u + 0xb0));
			d3_SelectSceneContext(t, 1);
		}
kill:
		he_FreeAction(u);
		break;
	}
}
