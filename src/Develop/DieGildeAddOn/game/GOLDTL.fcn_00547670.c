


// SIZE 0x21c
#include "Develop/DieGildeAddOn/game/entity_record.h"








#include "client_types.h"
extern pos14_7f4c00 gm_GameTime;
extern int g_7747b4;
extern unsigned char g_773d75;

int __cdecl gm_AccumulateTyped2(ENTITY_RECORD*);
int __cdecl fcn_004c5150(int, int, char, int);
int __cdecl fcn_004c4450(int);
void __cdecl fcn_00535960(void);

void __cdecl gm_ReplenishAiBuildingFunds(void)
{
	int cmd_handle;
	int batch_count;
	int i;
	int limit;
	int funds;

	cmd_handle = -1;
	if ((*(int*)&gm_GameTime) % ((*(int*)&gm_GameTime) / 10 + 1) == 0) {
		limit = (g_7747b4 * 5 + 20) * 1600;
		batch_count = 0;
		for (i = 0; i < 768; i++) {
			if (((ENTITY_RECORD_VIEW*)g_7f4ca0)[i].entity_type == 5) {
				funds = gm_AccumulateTyped2(((ENTITY_RECORD*)&((ENTITY_RECORD_VIEW*)g_7f4ca0)[i]));
				if (funds < limit) {
					cmd_handle = fcn_004c5150(((ENTITY_RECORD_VIEW*)g_7f4ca0)[i].entity_id, -1, (*(char*)&g_773d75), limit - funds);
					batch_count++;
				}
			} else if (((ENTITY_RECORD_VIEW*)g_7f4ca0)[i].entity_type == 4
				|| (((ENTITY_RECORD_VIEW*)g_7f4ca0)[i].entity_type == 2 && (*(int*)&gm_GameTime) % 4 == (((ENTITY_RECORD_VIEW*)g_7f4ca0)[i].entity_id & 3))) {
				funds = gm_AccumulateTyped2(((ENTITY_RECORD*)&((ENTITY_RECORD_VIEW*)g_7f4ca0)[i]));
				if (funds < limit) {
					cmd_handle = fcn_004c5150(((ENTITY_RECORD_VIEW*)g_7f4ca0)[i].entity_id, -1, (*(char*)&g_773d75), limit - funds);
					batch_count++;
				}
			}
			if (batch_count >= 32 && cmd_handle != -1) {
				do {
					if (fcn_004c4450(cmd_handle) != 0) {
						break;
					}
					fcn_00535960();
				} while (1);
				cmd_handle = -1;
				batch_count = 0;
			}
		}
	}
}
