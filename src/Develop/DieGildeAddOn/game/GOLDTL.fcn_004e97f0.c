#include "client_actions.h"

typedef struct {
	short lo;
	short hi;
	int min_cost;
	int max_cost;
	int a;
	int b;
	int c;
	int d;
} TierInfo;

int __cdecl gm_RandomMod(unsigned short n);
int __cdecl fcn_004e9580(int id, TierInfo* out);
void __cdecl cm_RequestTransferCurrencyNoKill(int a1, int a2, char a3, int a4);
void __cdecl cm_BeginPacketFieldDelta(char* a1, int a2);
int __cdecl cm_AppendPacketFieldDelta(unsigned char size, unsigned char count, unsigned short off, char* src);
void __cdecl cm_RequestChangeAttribute(void);
int __cdecl amt_ApplyForOffice(char* a0, int a1);

/* ADDRESS: GOLDTL 0x004e97f0 */
int __cdecl amt_PurchaseOfficeApplication(unsigned char* entity, int office_id)
{
	int mode;
	TierInfo info;
	unsigned short rnd;
	int lo;

	mode = 3;
	if (entity[2] != 0x13) {
		return 0;
	}
	if (fcn_004e9580(office_id, &info) == 0) {
		return 0;
	}
	lo = info.min_cost;
	cm_RequestTransferCurrencyNoKill(*(int*) (entity + 4), -1, g_773d75,
	    (unsigned short) gm_RandomMod((unsigned short) (info.max_cost - lo + 1)) + lo);
	rnd = (unsigned short) gm_RandomMod((unsigned short) (info.b - info.a + 1)) + info.a;
	cm_BeginPacketFieldDelta(entity, *(int*) (entity + 4));
	cm_AppendPacketFieldDelta(1, 1, 0xd, (char*) &rnd);
	cm_AppendPacketFieldDelta(1, 1, 2, (char*) &mode);
	cm_AppendPacketFieldDelta(1, 1, 0x167, (char*) &office_id);
	cm_RequestChangeAttribute();
	amt_ApplyForOffice(entity, office_id);
	return 1;
}
