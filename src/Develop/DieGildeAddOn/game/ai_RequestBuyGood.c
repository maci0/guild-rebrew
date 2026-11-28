extern char s_67fb68[];
#include "Develop/DieGildeAddOn/game/entity_record.h"

char* __cdecl gm_StartFilteredEntitySearch(int, int, int);
char* __cdecl fcn_00502cd0(int, int, int, int);
void __cdecl cm_SendLogAction(char* s);
void __cdecl cm_RequestElectionOrTrade(void* msg);
void __cdecl cm_RequestLinkEvidence(int, int);
void __cdecl cm_RequestTransferCurrencyNoKill(int, int, int, int);
void __cdecl cm_SendTraceEnd(char* s);

struct BUY_GOOD_MSG {
	int tag;
	int who;
	int where;
	int what;
	int amount;
};
// SIZE 0x14


/* ADDRESS: GOLDTL 0x004ab3e0 */
int __cdecl ai_RequestBuyGood(char* actor, char* good, char* target)
{
	struct BUY_GOOD_MSG msg;
	char* found;
	char* entry;
	int i;

	found = gm_StartFilteredEntitySearch(1, 1, *(int*) (target + 4));
	if (found == 0)
		return 0;
	entry = fcn_00502cd0(*(int*) (found + 0x5d), 1, 0, 0x120);
	if (entry == 0)
		return 0;
	entry = fcn_00502cd0(*(int*) (entry + 0x14), 1, 0, 0x12c);
	if (entry == 0)
		return 0;
	for (i = 0; i < 3; i++) {
		if (*(int*) (entry + 0x1c + i * 4) == *(int*) (good + 4))
			break;
	}
	if (i == 3)
		return 0;
	msg.tag = 0x62757920;
	msg.where = *(int*) (found + 1);
	msg.who = *(int*) (actor + 4);
	msg.what = *(int*) (good + 4);
	msg.amount = *(int*) (good + 0x10);
	cm_SendLogAction(s_67fb68);
	cm_RequestElectionOrTrade(&msg);
	cm_RequestLinkEvidence(*(int*) (good + 4), *(int*) (actor + 4));
	cm_RequestTransferCurrencyNoKill(((ENTITY_RECORD_VIEW*)gm_EntitySlotTable)[*(unsigned short*) (found + 0x27)].entity_id,
	    *(int*) (actor + 4), 0, *(int*) (good + 0x10));
	cm_SendTraceEnd(s_67fb68);
	return 1;
}
