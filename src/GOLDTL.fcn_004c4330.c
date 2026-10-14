#include "client_packet_queue.h"
#pragma pack(1)
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
// SIZE 0x99

#include "client_types.h"
typedef cell10_fb5760 cell10;
// SIZE 0xa
#pragma pack()

extern int g_14cbcb0;
extern int g_1005768;
extern int g_14cbca0;
extern unsigned char* g_14cbca8;
extern int g_1005760;
extern int g_aecde0;
extern int g_aed330;
extern pkt99 g_aed740[0x8000];
extern cell10_fb5760 g_fb5760[0x8000];

unsigned short __cdecl fcn_004c3a50(pkt99*);
int __cdecl fcn_004c4090(void);

// FUNCTION: GOLD 0x4c39c0
// FUNCTION: GOLDTL 0x4c4330

int __cdecl fcn_004c4330(pkt99* a1)
{
	pkt99* p;
	pkt99* q;
	pkt99* last;
	int n;
	int seq;

	if (g_14cbcb0 != 0)
		return -1;
	n = g_1005768 + 1;
	seq = n & 0x7fff;
	p = &g_aed740[seq];
	if (g_14cbca0 != -1 && (*(pkt99**)&g_14cbca8) == p)
		return -1;
	for (q = (*(pkt99**)&g_1005760); q != 0; q = q->next) {
		if (q == p)
			return -1;
	}
	g_1005768 = n;
	*p = *a1;
	p->crc = fcn_004c3a50(p);
	p->flag = 0;
	p->seq = seq;
	p->cur = g_1005768;
	p->nextseq = 0;
	if (a1->type == 0x20 && a1->data[0] == 0xe)
		g_aecde0 = p->cur;
	g_fb5760[seq].f0 = 0;
	g_fb5760[seq].f2 = seq;
	last = (*(pkt99**)&g_1005760);
	if (last != 0) {
		while (last->next != 0)
			last = last->next;
		p->prev = last;
		last->next = p;
	} else {
		(*(pkt99**)&g_1005760) = p;
		p->prev = 0;
	}
	p->next = 0;
	if (g_aed330 != 0)
		p->nextseq = fcn_004c4090();
	return seq;
}
