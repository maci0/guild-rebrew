extern unsigned short* g_772f24;
#include "Develop/DieGildeAddOn/game/game_data.h"
#include "Develop/DieGildeAddOn/command/client_packet_builder.h"

char* __cdecl gm_FindEntityActiveItem(char* o);

void __cdecl cm_AppendPacketFieldValue(int a, int b, int c, int* d);
void __cdecl cm_RequestChangeAttribute(void);
void __cdecl cut_SpawnBombThrow(char* pos, int a, int b);

/* ADDRESS: GOLDTL 0x004d4e30 */
void __cdecl cut_FinishPotThrow(char* e)
{
	char* o;
	char* q;

	o = *(char**) (e + 0x17c);
	if (*(int*) (((char*)g_772f24) + 4) == g_68b79c) {
		q = gm_FindEntityActiveItem(o);
		if (q != 0) {
			int v = -1;

			cm_BeginPacketFieldDelta(q, *(int*) (q + 2));
			cm_AppendPacketFieldValue(4, 1, q - g_aed32c + 0x20, &v);
			cm_RequestChangeAttribute();
		}
	}
	cut_SpawnBombThrow(*(char**) (*(char**) (o + 0x184) + 0x34) + 0x4c, *(int*) (e + 0x180), *(int*) (e + 0x184));
}
