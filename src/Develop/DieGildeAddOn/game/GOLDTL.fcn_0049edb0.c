#include "Develop/DieGildeAddOn/game/spiel.h"



#include <string.h>

#include "Develop/DieGildeAddOn/game/entity_record.h"







#include "client_types.h"
extern pos14_7f4c00 gm_GameTime;
extern unsigned short g_7f4c04;
extern int g_7f4c08;
extern short g_7f4c0c;
extern unsigned char g_773d75;
#include "client_packet_builder.h"
extern char g_67eb48[];


void __cdecl cm_SendLogAction(char* s);
void __cdecl cm_SendTraceEnd(char* s);
void __cdecl cm_RequestMoveCredits(int a, int b, char c, int n);
void __cdecl cm_SendCopyEntityData(char* msg);

void __cdecl cm_AppendPacketFieldValue(int, int, int, int*);
void __cdecl cm_RequestChangeAttribute(void);

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
			*(int*) (msg + 8) = ((ENTITY_RECORD*)g_7f4ca0)[*(unsigned short*) (p1 + 0x27)].entity_id;
			*(int*) (msg + 0xc) = *(int*) (p1 + 1);
			*(int*) (msg + 0x28) = (*(int*)&gm_GameTime);
			*(int*) (msg + 0x2c) = (*(int*)&g_7f4c04);
			*(int*) (msg + 0x30) = g_7f4c08;
			*(short*) (msg + 0x34) = g_7f4c0c;
			msg[0x36] = 0x12;
			*(int*) (msg + 0x58) = *(int*) (p1 + 1);
			*(int*) (msg + 0x5c) = *(int*) (actor + 4);
			*(int*) (msg + 0x60) = *(int*) (terms + 4);
			*(int*) (msg + 0x64) = *(int*) (terms + 8);
			*(int*) (msg + 0x6c) = *(int*) (terms + 0x10);
			v = *(int*) (terms + 4);
			cm_SendLogAction(g_67eb48);
			cm_RequestMoveCredits(*(int*) (actor + 4), *(int*) (p1 + 1), (*(char*)&g_773d75), *(int*) (terms + 4));
			cm_SendCopyEntityData(msg);
			if (p2 != 0) {
				cm_BeginPacketFieldDelta(p2, *(int*) (p2 + 1));
				cm_AppendPacketFieldValue(4, 1, p2 - g_aed32c + 0x39, &v);
				cm_RequestChangeAttribute();
			}
			cm_SendTraceEnd(g_67eb48);
		}
	}
	return 0;
}
