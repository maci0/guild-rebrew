#include "Develop/DieGildeAddOn/game/object_prototype.h"
// 0x100dc20 is one 0xb00-byte block (owner, light count at +0x18, lights at
// +0x300); declaring it as one struct makes the light copy reload the count
// after each store, as the reference does.

#pragma pack(push, 1)
// SIZE 0x43
typedef struct {
	unsigned short id;
	char pad2[0x1a];
	int owner;
	char pad20[0x23];
} Slot;

// SIZE 0x41
typedef struct {
	unsigned char kind;
	char pad1[0x40];
} Kind;

// SIZE 0x24d
typedef struct {
	char pad0[0x247];
	unsigned char level;
	char pad248[5];
} Level;
#pragma pack(pop)

#include "Develop/client_types.h"

extern pos14_7f4c00 gm_GameTime;
extern unsigned short *lpObjekteINST;
extern char *lpObjektePROT;
extern int g_100e74c;
extern char *g_100dbc0[16];
extern unsigned char *lpGebaeudePROT;
#include "Develop/DieGildeAddOn/game/game_data.h"
extern int g_100b0f4;
extern float g_100b0e0;
extern int g_100d10c;
extern float g_100d0f4;
extern LightState ai_MeisterDebugState;

char *__cdecl fcn_00502cd0(int, int, int, int, int, ...);
void __cdecl gm_TryAutoUpgradeBuildingSlots(char *, char *, int);
void __cdecl ai_RequestAusbauUpgrade(char *, char *, int);
char *__cdecl gm_NextEntityQueryMatch(void);
char *__cdecl he_StartHandlungSearch(int, int, int, int, int);
char *__cdecl he_fn_Handlung(void);
void __cdecl ai_MeisterCollectTrans(char *);
void __cdecl ai_CollectThiefGoodsResources(char *, char *, int);
void __cdecl ai_MeisterTradeFernEinkauf(char *, char *);
void __cdecl ai_RebalanceCityStock(char *, char *);

void __cdecl ai_CalcMeisterLager(char *meister)
{
	int flag;
	char *warehouse;
	char *cart;
	char *e;
	char *bld;
	Slot *s;
	float f;
	int i;
	unsigned char lvl;

	if ((*(unsigned int *) (meister + 4) + (unsigned short) gm_GameTime.b) % 3 == 0) {
		if (*(int *) (meister + 0x1b4) & 0x20) {
			return;
		}
		warehouse = fcn_00502cd0(*(int *) (*(char **) (meister + 0x16c) + 0x5d), 2, 6, 0, 0x116);
		if (warehouse == 0) {
			return;
		}
		gm_TryAutoUpgradeBuildingSlots(warehouse, meister, 0x14);
		ai_RequestAusbauUpgrade(warehouse, meister, 0x32);
		flag = 1;
		s = (Slot*) lpObjekteINST;
		for (i = 0; flag && i < 0x5008; s++, i++) {
			if (s->id != 0 && ((OBJECT_PROTOTYPE*) lpObjektePROT)[s->id].kind == 0x1d && s->owner == *(int *) (*(char **) (meister + 0x16c) + 1) &&
			    s->id == 0x136) {
				flag = 0;
			}
		}
		g_100e74c = 0;
		bld = *(char **) (meister + 0x16c);
		for (cart = fcn_00502cd0(*(int *) (bld + 0x5d), 3, 6, 4, 0x1d, 3, *(unsigned short *) (bld + 0x27)); cart != 0;
		     cart = gm_NextEntityQueryMatch()) {
			if (*(int *) (cart + 0x1c) != *(int *) (*(char **) (meister + 0x16c) + 1)) {
				continue;
			}
			for (e = he_StartHandlungSearch(2, 0, 0xb, 3, *(int *) (*(char **) (meister + 0x16c) + 1)); e != 0; e = he_fn_Handlung()) {
				if (*(int *) (e + 0xac) == *(int *) (cart + 2)) {
					break;
				}
			}
			if (e == 0 && g_100e74c < 0x10) {
				g_100dbc0[g_100e74c++] = cart;
			}
		}
		if (g_100e74c == 0) {
			ai_MeisterCollectTrans(meister);
			return;
		}
		*(int *) (meister + 0x1b4) |= 0x20;
		ai_CollectThiefGoodsResources(meister, warehouse, flag);
		bld = *(char **) (meister + 0x16c);
		lvl = ((Level*) lpGebaeudePROT)[*(unsigned char *) bld].level;
		if (lvl == 1) {
			f = *(int *) (bld + 0x39) * 1.5625e-05f;
		} else if (lvl == 2) {
			f = *(int *) (bld + 0x39) * 7.8125e-06f;
		} else if (lvl == 3) {
			f = *(int *) (bld + 0x39) * 3.90625e-06f;
		}
		f = f * 0.5f + 0.25f;
		if (ai_ResourceCount != 0) {
			if (ai_ProductionGoodsCount != 0) {
				if (g_100b0f4 * g_100b0e0 * f > (1.0f - f) * g_100d10c * g_100d0f4) {
					ai_MeisterTradeFernEinkauf(meister, warehouse);
				} else {
					ai_RebalanceCityStock(meister, warehouse);
				}
			} else {
				ai_MeisterTradeFernEinkauf(meister, warehouse);
			}
		} else if (ai_ProductionGoodsCount != 0) {
			ai_RebalanceCityStock(meister, warehouse);
		}
		if (ai_MeisterDebugState.owner == *(char **) (meister + 0x16c)) {
			for (i = 0; ai_MeisterDebugState.count < 4 && i < ai_ResourceCount; i++) {
				ai_MeisterDebugState.lights[ai_MeisterDebugState.count] = ai_ResourceRequests[i];
				ai_MeisterDebugState.count++;
			}
		}
	} else {
		*(int *) (meister + 0x1b4) &= ~0x20;
	}
}
