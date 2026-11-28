#include "Develop/DieGildeAddOn/command/client_packet_queue.h"
#include "Develop/client_types.h"

#include "Develop/DieGildeAddOn/command/client_queued_packet.h"
















typedef COMMAND_STATUS_SLOT cell10;
/* SIZE 0xa */

#include "Develop/DieGildeAddOn/game/game_data.h"
extern unsigned char* g_14cbca8;
extern int g_aecde0;
extern int g_aed330;
extern CLIENT_QUEUED_PACKET g_aed740[0x8000];
extern COMMAND_STATUS_SLOT cm_CommandStatusQueue[0x8000];

unsigned short __cdecl ahm_GetCommandPayloadSize(CLIENT_QUEUED_PACKET*);
int __cdecl cm_FlushPendingDataPackets(void);


/* ADDRESS: GOLDTL 0x004c4330 */
/* ADDRESS: GOLDDE 0x004b1d40 */
int __cdecl cm_EnqueueClientPacket(CLIENT_QUEUED_PACKET* queuedInput)
{
	CLIENT_QUEUED_PACKET* p;
	CLIENT_QUEUED_PACKET* q;
	CLIENT_QUEUED_PACKET* last;
	int n;
	int seq;

	if (nt_ConnectionClosed != 0)
		return -1;
	n = g_1005768 + 1;
	seq = n & 0x7fff;
	p = &g_aed740[seq];
	if (nt_ClientSocket != -1 && (*(CLIENT_QUEUED_PACKET**)&g_14cbca8) == p)
		return -1;
	for (q = (*(CLIENT_QUEUED_PACKET**)&g_1005760); q != 0; q = q->next) {
		if (q == p)
			return -1;
	}
	g_1005768 = n;
	*p = *queuedInput;
	p->crc = ahm_GetCommandPayloadSize(p);
	p->flag = 0;
	p->seq = seq;
	p->cur = g_1005768;
	p->nextseq = 0;
	if (queuedInput->type == 0x20 && queuedInput->data[0] == 0xe)
		g_aecde0 = p->cur;
	cm_CommandStatusQueue[seq].f0 = 0;
	cm_CommandStatusQueue[seq].f2 = seq;
	last = (*(CLIENT_QUEUED_PACKET**)&g_1005760);
	if (last != 0) {
		while (last->next != 0)
			last = last->next;
		p->prev = last;
		last->next = p;
	} else {
		(*(CLIENT_QUEUED_PACKET**)&g_1005760) = p;
		p->prev = 0;
	}
	p->next = 0;
	if (g_aed330 != 0)
		p->nextseq = cm_FlushPendingDataPackets();
	return seq;
}
