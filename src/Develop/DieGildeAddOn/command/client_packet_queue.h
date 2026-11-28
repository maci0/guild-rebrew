#ifndef CLIENT_PACKET_QUEUE_H
#define CLIENT_PACKET_QUEUE_H

/* Reconstructed queue interface; original header path is unproved. */
/* Assembled incoming command bytes; storage owner and full extent are unresolved. */
/* ADDRESS: GOLDTL 0x00aed340 */
/* ADDRESS: GOLD 0x00a68d40 */
extern unsigned char cm_IncomingPacketData[];

char* __cdecl cut_AllocCutscene(void* source);

struct pkt99;
int __cdecl cm_EnqueueClientPacket(struct pkt99* packet);

#endif
