#include "Develop/DieGildeAddOn/game/spiel.h"



#include "client_types.h"
extern pos14_7f4c00 gm_GameTime;
#include "Develop/DieGildeAddOn/game/game_data.h"
#include "client_packet_builder.h"
extern char g_67ec2c[];

unsigned short __cdecl gm_RandomMod(int);
void __cdecl gm_AddTime(pos14_7f4c00*, int, int, int);
char* __cdecl he_StartHandlungSearch(int, int, int, ...);
char* __cdecl he_fn_Handlung(void);

char* __cdecl fcn_00502cd0(int, int, ...);

void __cdecl cm_AppendPacketFieldDelta(int, int, int, void*);
void __cdecl fcn_004c5360(void);
void __cdecl fcn_004c4eb0(char* s);
void __cdecl fcn_004c4ef0(char* s);
int __cdecl fcn_004c64b0(int, int, int, int, int, int, char*);
int __cdecl fcn_004c5620(int, char*);

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
			q = fcn_00502cd0(*(int*) (o + 0x5d), 2, 6, 0, 0x12c);
			if (q != 0) {
				int t = gm_GameTime.a;

				cm_BeginPacketFieldDelta(q, *(int*) (q + 2));
				cm_AppendPacketFieldDelta(4, 1, q - g_aed32c + 0x28, &t);
				fcn_004c5360();
				fcn_004c4eb0(g_67ec2c);
				*(int*) (u + 0xac) = fcn_004c64b0(0xe, *(int*) (o + 1), -1, 0, 0, 0, "DunkleEcke");
				*(int*) (u + 0x84) = fcn_004c5620(0, u);
				fcn_004c4ef0(g_67ec2c);
				return;
			}
		}
	}
	*(int*) (u + 0x84) = fcn_004c5620(-1, u);
}
