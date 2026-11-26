#include <string.h>
#include "Develop/DieGildeAddOn/game/object_prototype.h"
typedef struct Rec {
	char type;
	char rest[0x40];
} Rec;

extern char* lpObjektePROT;
extern unsigned char g_773d75;
#include "Develop/DieGildeAddOn/game/game_data.h"

int __cdecl gm_AccumulateTyped2(void*);
char* __cdecl gm_StartFilteredEntitySearch(int, int, int);
void* __cdecl gm_FindNextFilteredEntity(void);
int __cdecl gm_GetBuildingTypeCategory(int);
char* __cdecl gm_NextEntityQueryMatch(void);
void* __cdecl fcn_00502cd0(int, int, ...);
float __cdecl fcn_0050bb50(int, unsigned char);
int __cdecl gm_GetMsgField(void*, void*);
void __cdecl cm_RequestMoveCredits(int, int, unsigned char, int);
int __cdecl cm_RequestTransferCurrencyNoKill(int, int, unsigned char, int);
int __cdecl cm_SendSellObjekt(int, int, int, int, unsigned char, int);
void __cdecl io_FormatTextBuffer(void*, int, ...);

/* ADDRESS: GOLDTL 0x005c4ec0 */
int __cdecl gm_CollectPaymentOrLiquidate(int receiverId, char* ownerEntity, int requestedAmount, char* outLog)
{
	char buf[0x100];
	char* ent;
	void* obj;
	unsigned short* sub;
	int cat;
	int amount;
	int remaining;
	int written;
	int total;
	int found;
	int div;
	int got;

	found = 0;
	written = 0;
	total = 0;
	got = gm_AccumulateTyped2(ownerEntity);
	remaining = requestedAmount;
	amount = got < remaining ? got : remaining;
	if (amount > 0) {
		cm_RequestMoveCredits(receiverId, *(int*) (ownerEntity + 4), g_773d75, amount);
		remaining -= amount;
		written = amount;
	}
	while (remaining > 0) {
		if (found) {
			break;
		}
		ent = gm_StartFilteredEntitySearch(1, 4, *(unsigned short*) ownerEntity);
		found = 1;
		while (ent != 0) {
			if (remaining <= 0) {
				break;
			}
			cat = *(unsigned char*) ent;
			cat = gm_GetBuildingTypeCategory(cat);
			if (cat == 1 || cat == 2 || cat == 8) {
				obj = fcn_00502cd0(*(int*) (ent + 0x5d), 2, 6, 0, 0x2a);
				if (obj == 0) {
					obj = fcn_00502cd0(*(int*) (ent + 0x5d), 2, 6, 0, 0x116);
				}
				if (obj != 0) {
					sub = (unsigned short*) fcn_00502cd0(*(int*) ((char*) obj + 0x14), 1, 5);
					while (sub != 0 && remaining > 0) {
						if ((*(char *)&((OBJECT_PROTOTYPE*) lpObjektePROT)[*sub].kind) != 0x17
							&& (*(char *)&((OBJECT_PROTOTYPE*) lpObjektePROT)[*sub].kind) != 0x25) {
							div = (int) (fcn_0050bb50(*sub, g_773d75) * 0.5);
							if (div != 0) {
								amount = remaining / div;
								if (amount <= 1) {
									amount = 1;
								}
								if (gm_GetMsgField(obj, sub) <= amount) {
									amount = gm_GetMsgField(obj, sub);
								}
								cm_SendSellObjekt(-1, *(int*) ((char*) obj + 2), *sub, amount, g_773d75, 0);
								div *= amount;
								total += div;
								remaining -= div;
								written += div;
								if (div != 0) {
									found = 0;
								}
							}
						}
						sub = (unsigned short*) gm_NextEntityQueryMatch();
					}
				}
			}
			ent = gm_FindNextFilteredEntity();
		}
		if (remaining <= 0) {
			break;
		}
	}
	found = 0;
	while (remaining > 0) {
		if (found) {
			break;
		}
		ent = gm_StartFilteredEntitySearch(1, 4, *(unsigned short*) ownerEntity);
		found = 1;
		while (ent != 0) {
			if (remaining <= 0) {
				break;
			}
			cat = *(unsigned char*) ent;
			cat = gm_GetBuildingTypeCategory(cat);
			if (cat == 1 || cat == 2 || cat == 8) {
				obj = fcn_00502cd0(*(int*) (ent + 0x5d), 2, 6, 0, 0x2a);
				if (obj != 0) {
					sub = (unsigned short*) fcn_00502cd0(*(int*) ((char*) obj + 0x14), 1, 5);
					while (sub != 0 && remaining > 0) {
						if ((*(char *)&((OBJECT_PROTOTYPE*) lpObjektePROT)[*sub].kind) == 0x17
							|| (*(char *)&((OBJECT_PROTOTYPE*) lpObjektePROT)[*sub].kind) == 0x25) {
							div = (int) (fcn_0050bb50(*sub, g_773d75) * 0.5);
							if (div != 0) {
								amount = remaining / div;
								if (amount <= 1) {
									amount = 1;
								}
								if (gm_GetMsgField(obj, sub) <= amount) {
									amount = gm_GetMsgField(obj, sub);
								}
								cm_SendSellObjekt(-1, *(int*) ((char*) obj + 2), *sub, amount, g_773d75, 0);
								div *= amount;
								total += div;
								remaining -= div;
								written += div;
								if (div != 0) {
									found = 0;
								}
							}
						}
						sub = (unsigned short*) gm_NextEntityQueryMatch();
					}
				}
			}
			ent = gm_FindNextFilteredEntity();
		}
		if (remaining <= 0) {
			break;
		}
	}
	if (total != 0) {
		cm_RequestMoveCredits(receiverId, -1, g_773d75, total);
		io_FormatTextBuffer(buf, 0x18eb, total);
		strcat(outLog, buf);
		return written;
	}
	if (remaining > 0) {
		cm_RequestTransferCurrencyNoKill(receiverId, *(int*) (ownerEntity + 4), g_773d75, remaining);
	}
	return written;
}
