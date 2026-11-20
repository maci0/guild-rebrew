


#include <string.h>

#include "Develop/DieGildeAddOn/game/game_timestamp.h"






// SIZE 0xe


#include "client_types.h"
extern pos14_7f4c00 gm_GameTime;
extern int g_6a3438;
extern int g_6a3434;
extern int g_6a3430;
extern int g_772620;
extern LightState g_100dc20;
#include "Develop/DieGildeAddOn/game/entity_record.h"

int __cdecl fcn_00500cb0(GAME_TIMESTAMP*, GAME_TIMESTAMP*);
void __cdecl he_RunDueActions(void);
void __cdecl fcn_004fc180(void);
void __cdecl fcn_00500a40(void);
void __cdecl fcn_0047da70(void);
void __cdecl ai_EvaluateMeister(char*);
void __cdecl fcn_0047da10(void);
void __cdecl fcn_005c6310(void);
void __cdecl fcn_00531b80(void);

int __cdecl fcn_004c9440(char* x, char* out)
{
	int i;

	if (fcn_00500cb0(&(*(GAME_TIMESTAMP*)&gm_GameTime), (GAME_TIMESTAMP*) (x + 0x10)) < 0) {
		(*(GAME_TIMESTAMP*)&gm_GameTime) = *(GAME_TIMESTAMP*) (x + 0x10);
		if (g_6a3438 != 0)
			he_RunDueActions();
		if (g_6a3434 != 0) {
			fcn_004fc180();
			if ((*(GAME_TIMESTAMP*)&gm_GameTime).minute % 6 == 0)
				fcn_00500a40();
		}
		if (g_6a3430 != 0)
			fcn_0047da70();
		memset(&g_100dc20, 0, 0xb00);
		if (g_6a3430 != 0) {
			g_772620 = 0;
			for (i = 0; i < 0x300; i++) {
				if (*(unsigned short*) (((char*)&((ENTITY_RECORD_VIEW*)g_7f4ca0)[i])) != 0xffff)
					ai_EvaluateMeister(((char*)&((ENTITY_RECORD_VIEW*)g_7f4ca0)[i]));
			}
			fcn_0047da10();
		}
		fcn_005c6310();
		fcn_00531b80();
	}
	if (out != 0)
		*out = 1;
	return 0;
}
