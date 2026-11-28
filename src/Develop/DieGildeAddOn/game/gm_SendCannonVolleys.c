#include <string.h>

extern unsigned char gm_ActiveTownIndex;

int __cdecl gm_FindSlot170Entry(int);
void __cdecl gm_TryRecordCrime(int, int, int, int, int);
void __cdecl cm_RequestTransferCurrencyNoKill(int, int, char, int);
void __cdecl gm_ModifyHealth(int, int);
int __cdecl cm_SendAdjustResourceSlots(void*);

/* ADDRESS: GOLDTL 0x004f0a30 */
/* ADDRESS: GOLDDE 0x004dcd40 */
int __cdecl gm_SendCannonVolleys(char* building, char* payer, unsigned int* firstPayload,
	unsigned int* secondPayload, unsigned int* thirdPayload, unsigned int priority, int hpDelta, unsigned int goldCost)
{
	unsigned int prio;
	unsigned int need_start;
	int ok;
	int ret;
	unsigned int pkt[32];
	char* rec;

	prio = priority;
	ok = 1;
	ret = -1;
	need_start = 0;
	if (building == 0) {
		goto bad;
	}
	if ((rec = (char*) gm_FindSlot170Entry(*(int*) (building + 1))) != 0
		&& !(*(unsigned char*) (rec + 4) & 2)) {
		if (thirdPayload != 0) {
			need_start = 2;
		} else if (secondPayload != 0) {
			need_start = 1;
		}
		memset(pkt, 0, sizeof(pkt));
		if (firstPayload != 0) {
			gm_TryRecordCrime(8, 1, *(int*) (payer + 4), -1, -1);
			gm_ModifyHealth(*(int*) (payer + 4), -hpDelta);
			cm_RequestTransferCurrencyNoKill(-1, *(int*) (payer + 4), (char) gm_ActiveTownIndex, goldCost);
			pkt[0] = *(unsigned int*) (building + 1);
			pkt[1] = prio;
			pkt[2] = need_start;
			ok = 0;
			memcpy(&pkt[3], firstPayload, 0x1a * 4);
			prio = 0;
			ret = cm_SendAdjustResourceSlots(pkt);
		}
		if (secondPayload != 0) {
			if (ok != 0) {
				gm_ModifyHealth(*(int*) (payer + 4), -hpDelta);
				cm_RequestTransferCurrencyNoKill(-1, *(int*) (payer + 4), (char) gm_ActiveTownIndex, goldCost);
				ok = 0;
			}
			pkt[0] = *(unsigned int*) (building + 1);
			pkt[1] = prio;
			pkt[2] = need_start;
			memcpy(&pkt[3], secondPayload, 0x1a * 4);
			prio = 0;
			ret = cm_SendAdjustResourceSlots(pkt);
		}
		if (thirdPayload != 0) {
			if (ok != 0) {
				gm_ModifyHealth(*(int*) (payer + 4), -hpDelta);
				cm_RequestTransferCurrencyNoKill(-1, *(int*) (payer + 4), (char) gm_ActiveTownIndex, goldCost);
			}
			pkt[0] = *(unsigned int*) (building + 1);
			pkt[1] = prio;
			pkt[2] = need_start;
			memcpy(&pkt[3], thirdPayload, 0x1a * 4);
			ret = cm_SendAdjustResourceSlots(pkt);
		}
		return ret;
	}
bad:
	return -1;
}
