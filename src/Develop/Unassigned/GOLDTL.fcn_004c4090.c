#include "client_packet_queue.h"
#include "client_types.h"

#pragma pack(push, 1)
typedef struct pkt99 {
	unsigned char type;
	unsigned short crc;
	unsigned char flag;
	int seq;
	int cur;
	int nextseq;
	unsigned char data[0x80];
	char pad90;
	struct pkt99* prev;
	struct pkt99* next;
} pkt99;
#pragma pack(pop)
/* SIZE 0x99 */

typedef struct pkt99_payload {
	unsigned char b[0x80];
} pkt99_payload;
/* SIZE 0x80 */

typedef cell10_fb5760 cell10;

extern int g_14cbcb0;
extern int g_1005768;
extern int g_1005760;
extern int g_aed330;
extern pkt99 g_aed740[0x8000];
extern cell10_fb5760 g_fb5760[0x8000];

int __cdecl fcn_004c3a50(unsigned char*);

/* ADDRESS: GOLDTL 0x004c4090 */
int __cdecl fcn_004c4090(void)
{
	pkt99* p;
	pkt99* last;
	pkt99* prev;
	int n;
	int i;
	int seq;

	if (g_aed330 == 0)
		return 0;
	if (g_14cbcb0 != 0)
		return 0;
	prev = 0;
	n = g_1005768;
	n++;
	for (i = 0; i < g_aed330; i += 0x80) {
		seq = (g_1005768 += 1) & 0x7fff;
		p = &g_aed740[seq];
		p->type = 7;
		p->crc = fcn_004c3a50((unsigned char*) p);
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
		g_fb5760[seq].f0 = 0;
		g_fb5760[seq].f2 = seq;
		last = (*(pkt99**) &g_1005760);
		if (last != 0) {
			while (last->next != 0)
				last = last->next;
			p->prev = last;
			last->next = p;
		} else {
			(*(pkt99**) &g_1005760) = p;
			p->prev = 0;
		}
		p->next = 0;
	}
	g_aed330 = 0;
	return n;
}
