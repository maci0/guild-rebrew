#include "Develop/DieGildeAddOn/game/spiel.h"



#include "Develop/client_types.h"
extern pos14_7f4c00 gm_GameTime;
#include "Develop/DieGildeAddOn/game/game_data.h"
#include "Develop/DieGildeAddOn/command/client_packet_builder.h"
extern char g_67ec2c[];

unsigned short __cdecl gm_RandomMod(int);
void __cdecl gm_AddTime(pos14_7f4c00*, int, int, int);
char* __cdecl he_StartHandlungSearch(int, int, int, ...);
char* __cdecl he_fn_Handlung(void);

char* __cdecl gm_QueryEntities(int, int, ...);

void __cdecl cm_AppendPacketFieldDelta(int, int, int, void*);
void __cdecl cm_RequestChangeAttribute(void);
void __cdecl cm_SendLogAction(char* s);
void __cdecl cm_SendTraceEnd(char* s);
int __cdecl cm_SendAllocCharacter(int, int, int, int, int, int, char*);
int __cdecl cm_SendSetHE(int, char*);

/* ADDRESS: GOLDDE 0x0053d5d0 */
void __cdecl he_InitDunkleEcke(char* u)
{
	char* e;
	char* o;
	char* q;

	if (u[0x78] & 4) {
		return;
	}
	*(int*) (u + 0xac) = -1;
	*(int*) (u + 0xc4) = gm_RandomMod(0x100);
	*(int*) (u + 0xc8) = g_6643d8[gm_RandomMod(0x10)];
	*(int*) (u + 0xbc) = gm_RandomMod(4) + 5;
	*(int*) (u + 0xc0) = 0;
	*(int*) (u + 0xb8) = -1;
	*(pos14_7f4c00*) (u + 0x52) = gm_GameTime;
	*(pos14_7f4c00*) (u + 0x44) = gm_GameTime;
	gm_AddTime((pos14_7f4c00*) (u + 0x52), 0, 1, 0);
	for (e = he_StartHandlungSearch(1, 0, 0x74); e != 0; e = he_fn_Handlung()) {
		if (*(int*) (e + 4) != *(int*) (u + 4) && *(int*) (e + 0xb0) == *(int*) (u + 0xb0)) {
			break;
		}
	}
	if (e == 0) {
		gm_ResolveEntityById((void**) (&o), 0, 0, *(int*) (u + 0xb0));
		if (o != 0) {
			q = gm_QueryEntities(*(int*) (o + 0x5d), 2, 6, 0, 0x12c);
			if (q != 0) {
				int t = gm_GameTime.a;

				cm_BeginPacketFieldDelta(q, *(int*) (q + 2));
				cm_AppendPacketFieldDelta(4, 1, q - cm_PacketDeltaBase + 0x28, &t);
				cm_RequestChangeAttribute();
				cm_SendLogAction(g_67ec2c);
				*(int*) (u + 0xac) = cm_SendAllocCharacter(0xe, *(int*) (o + 1), -1, 0, 0, 0, "DunkleEcke");
				*(int*) (u + 0x84) = cm_SendSetHE(0, u);
				cm_SendTraceEnd(g_67ec2c);
				return;
			}
		}
	}
	*(int*) (u + 0x84) = cm_SendSetHE(-1, u);
}
