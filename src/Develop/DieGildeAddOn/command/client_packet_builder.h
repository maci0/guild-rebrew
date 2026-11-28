#ifndef CLIENT_PACKET_BUILDER_H
#define CLIENT_PACKET_BUILDER_H

/* Inferred byte-access interface; the pointer's storage owner is unresolved. */
/* ADDRESS: GOLDTL 0x00aed32c */
/* ADDRESS: GOLD 0x00a68d2c */
extern char* cm_PacketDeltaBase;

void __cdecl cm_BeginPacketFieldDelta(char* base, int entity_id);

#endif
