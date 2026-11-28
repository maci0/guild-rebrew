#include "Develop/DieGildeAddOn/game/spiel.h"



#include <string.h>

typedef struct
{
	int id;
	char count;
	char data[0x77];
} PACKET_DELTA_BUF;
// SIZE 0x7c

extern unsigned int g_aed208;
extern char cm_AttributePacketData[];
#include "Develop/DieGildeAddOn/command/client_packet_builder.h"



void __cdecl cm_BeginPacketFieldDelta(char* src, int id)
{
	void* l0;
	void* l1;
	void* static_ptr;

	(*(PACKET_DELTA_BUF*)cm_AttributePacketData).id = id;
	(*(PACKET_DELTA_BUF*)cm_AttributePacketData).count = 0;
	memset((*(PACKET_DELTA_BUF*)cm_AttributePacketData).data, 0, sizeof((*(PACKET_DELTA_BUF*)cm_AttributePacketData).data));
	g_aed208 = 0;
	if (gm_ResolveEntityById(&l1, &l0, &static_ptr, id) != 0) {
		cm_PacketDeltaBase = src;
	}
}
unsigned char _dpad_aecde0[1088];
