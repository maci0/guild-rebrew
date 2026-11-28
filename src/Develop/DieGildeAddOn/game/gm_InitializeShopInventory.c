


#pragma pack(push, 1)
// SIZE 0x69
typedef struct {
	char pad0[0x5d];
	int home;
	char pad61[4];
	int variant;
} Estate;

// SIZE 0x6
typedef struct {
	char pad0[2];
	int id;
} Shop;
#pragma pack(pop)

// SIZE 0x2f4
typedef struct {
	char pad0[0x2ac];
	unsigned short buy[16];
	unsigned short sell[16];
	char pad2ec[8];
} Variant;

extern char g_868060[];
#include "Develop/DieGildeAddOn/command/client_packet_builder.h"
extern unsigned char g_773d75;

Estate* __cdecl gm_StartFilteredEntitySearch(int, int, int);
Shop* __cdecl fcn_00502cd0(int, int, int, int, int);

void __cdecl cm_AppendPacketFieldDelta(int, int, int, int*);
void __cdecl cm_RequestChangeAttribute(void);
int __cdecl cm_SendSellObjekt(int, int, int, int, char, int);
Estate* __cdecl gm_AddObjekt(void);
Estate* __cdecl gm_FindNextFilteredEntity(void);

void __cdecl gm_InitializeShopInventory(void)
{
	Estate* s;
	int count;
	int kind;
	Shop* w;
	unsigned short* p;
	int i;

	s = gm_StartFilteredEntitySearch(1, 0, 0x47);
	if (s == 0) {
		return;
	}
	do {
		kind = s->variant;
		w = fcn_00502cd0(s->home, 2, 0, 0x1db, 6);
		if (w != 0) {
			count = 0;
			for (i = 0; i < 16; i++) {
				if (((Variant*)g_868060)[kind].buy[i] != 0) {
					count++;
				}
			}
			cm_BeginPacketFieldDelta((char*) w, w->id);
			cm_AppendPacketFieldDelta(1, 1, (char*) w - g_aed32c + 0x1c, &count);
			count = 4;
			cm_AppendPacketFieldDelta(4, 1, (char*) w - g_aed32c + 0xe, &count);
			cm_RequestChangeAttribute();
			p = ((Variant*)g_868060)[kind].buy;
			for (i = 16; i != 0; i--) {
				if (*p != 0) {
					cm_SendSellObjekt(w->id, -1, *p, 1, (*(char*)&g_773d75), 0);
					cm_SendSellObjekt(-1, w->id, *p, 1, (*(char*)&g_773d75), 0);
				}
				p++;
			}
		}
		w = fcn_00502cd0(s->home, 2, 0, 0x1dc, 6);
		if (w != 0) {
			count = 0;
			for (i = 0; i < 16; i++) {
				if (((Variant*)g_868060)[kind].sell[i] != 0) {
					count++;
				}
			}
			cm_BeginPacketFieldDelta((char*) w, w->id);
			cm_AppendPacketFieldDelta(1, 1, (char*) w - g_aed32c + 0x1c, &count);
			count = 4;
			cm_AppendPacketFieldDelta(4, 1, (char*) w - g_aed32c + 0xe, &count);
			cm_RequestChangeAttribute();
			p = ((Variant*)g_868060)[kind].sell;
			for (i = 16; i != 0; i--) {
				if (*p != 0) {
					cm_SendSellObjekt(w->id, -1, *p, 1, (*(char*)&g_773d75), 0);
					cm_SendSellObjekt(-1, w->id, *p, 1, (*(char*)&g_773d75), 0);
				}
				p++;
			}
		}
		s = gm_FindNextFilteredEntity();
	} while (s != 0);
}
