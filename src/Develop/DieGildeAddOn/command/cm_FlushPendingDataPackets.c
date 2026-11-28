#include "Develop/DieGildeAddOn/command/client_packet_queue.h"
#include "Develop/client_types.h"

#include "Develop/DieGildeAddOn/command/client_queued_packet.h"
















typedef struct pkt99_payload {
	unsigned char b[0x80];
} pkt99_payload;
/* SIZE 0x80 */

typedef COMMAND_STATUS_SLOT cell10;

#include "Develop/DieGildeAddOn/game/game_data.h"
extern int g_aed330;
extern CLIENT_QUEUED_PACKET g_aed740[0x8000];
extern COMMAND_STATUS_SLOT cm_CommandStatusQueue[0x8000];

int __cdecl ahm_GetCommandPayloadSize(unsigned char*);

/* ADDRESS: GOLDTL 0x004c4090 */
int __cdecl cm_FlushPendingDataPackets(void)
{
	CLIENT_QUEUED_PACKET* p;
	CLIENT_QUEUED_PACKET* last;
	CLIENT_QUEUED_PACKET* prev;
	int n;
	int i;
	int seq;

	if (g_aed330 == 0)
		return 0;
	if (nt_ConnectionClosed != 0)
		return 0;
	prev = 0;
	n = g_1005768;
	n++;
	for (i = 0; i < g_aed330; i += 0x80) {
		seq = (g_1005768 += 1) & 0x7fff;
		p = &g_aed740[seq];
		p->type = 7;
		p->crc = ahm_GetCommandPayloadSize((unsigned char*) p);
#ifdef REBREW_GOLD
		*(pkt99_payload*) p->data = *(pkt99_payload*) (0xa68800 + i);
#else
		*(pkt99_payload*) p->data = *(pkt99_payload*) (0xaece00 + i);
#endif
		p->flag = 0;
		p->seq = seq;
		p->cur = g_1005768;
		p->nextseq = 0;
		if (prev != 0)
			prev->nextseq = g_1005768;
		prev = p;
		cm_CommandStatusQueue[seq].f0 = 0;
		cm_CommandStatusQueue[seq].f2 = seq;
		last = (*(CLIENT_QUEUED_PACKET**) &g_1005760);
		if (last != 0) {
			while (last->next != 0)
				last = last->next;
			p->prev = last;
			last->next = p;
		} else {
			(*(CLIENT_QUEUED_PACKET**) &g_1005760) = p;
			p->prev = 0;
		}
		p->next = 0;
	}
	g_aed330 = 0;
	return n;
}
