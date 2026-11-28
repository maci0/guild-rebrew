#include "Develop/DieGildeAddOn/game/spiel.h"



#include <string.h>

#include "Develop/DieGildeAddOn/game/entity_record.h"







#include "Develop/client_types.h"
extern pos14_7f4c00 gm_GameTime;
extern unsigned short gm_GameTimeHour;
extern int gm_GameTimeSliceDword;
extern short gm_GameTimeTailWord;
extern unsigned char gm_ActiveTownIndex;
#include "Develop/DieGildeAddOn/command/client_packet_builder.h"
extern char g_67eb48[];


void __cdecl cm_SendLogAction(char* s);
void __cdecl cm_SendTraceEnd(char* s);
void __cdecl cm_RequestMoveCredits(int a, int b, char c, int n);
void __cdecl cm_SendCopyEntityData(char* msg);

void __cdecl cm_AppendPacketFieldValue(int, int, int, int*);
void __cdecl cm_RequestChangeAttribute(void);

/* ADDRESS: GOLDDE 0x0048d7e0 */
int __cdecl ai_RunKreditNehmen(char* actor, char* action, char* terms)
{
	char* p1;
	char* p2;
	int v;
	char msg[0xf8];

	if (*action == 4 && *terms == 0x14) {
		gm_ResolveEntityById((void**) (&p1), 0, 0, *(int*) (action + 4));
		if (p1 != 0) {
			gm_ResolveEntityById((void**) (&p2), 0, 0, *(int*) (action + 8));
			memset(msg, 0, sizeof(msg));
			msg[4] = 0x23;
			*(int*) (msg + 8) = ((ENTITY_RECORD*)gm_EntitySlotTable)[*(unsigned short*) (p1 + 0x27)].entity_id;
			*(int*) (msg + 0xc) = *(int*) (p1 + 1);
			*(int*) (msg + 0x28) = (*(int*)&gm_GameTime);
			*(int*) (msg + 0x2c) = (*(int*)&gm_GameTimeHour);
			*(int*) (msg + 0x30) = gm_GameTimeSliceDword;
			*(short*) (msg + 0x34) = gm_GameTimeTailWord;
			msg[0x36] = 0x12;
			*(int*) (msg + 0x58) = *(int*) (p1 + 1);
			*(int*) (msg + 0x5c) = *(int*) (actor + 4);
			*(int*) (msg + 0x60) = *(int*) (terms + 4);
			*(int*) (msg + 0x64) = *(int*) (terms + 8);
			*(int*) (msg + 0x6c) = *(int*) (terms + 0x10);
			v = *(int*) (terms + 4);
			cm_SendLogAction(g_67eb48);
			cm_RequestMoveCredits(*(int*) (actor + 4), *(int*) (p1 + 1), (*(char*)&gm_ActiveTownIndex), *(int*) (terms + 4));
			cm_SendCopyEntityData(msg);
			if (p2 != 0) {
				cm_BeginPacketFieldDelta(p2, *(int*) (p2 + 1));
				cm_AppendPacketFieldValue(4, 1, p2 - cm_PacketDeltaBase + 0x39, &v);
				cm_RequestChangeAttribute();
			}
			cm_SendTraceEnd(g_67eb48);
		}
	}
	return 0;
}
