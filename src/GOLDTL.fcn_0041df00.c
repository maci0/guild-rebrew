#include <stdio.h>
#include <string.h>

#include "memtrack.h"

extern int g_6b6f64;
extern int g_6b6f68;
extern int g_6b6f6c;
extern int g_6b6f70;
extern int g_6b6f74;
extern MemBlock* g_6b6f80;
extern struct MemPool g_14cc5c0;

// FUNCTION: GOLD 0x00422750
// SIZE: 440
// FUNCTION: GOLDTL 0x41df00
// SIZE: 440

/* Reports the memory tracker's pools, and the live blocks of the pools
 * whose name contains filter. */
void __cdecl fcn_0041df00(const char* filter)
{
	struct MemPool* p;
	MemBlock* b;
	char* colon;
	char show;
	int i;
	char name[0x10];
	char msg[0x400];

	if (g_6b6f68 == 0 && g_6b6f6c == 0) {
		sprintf(msg, "[*] Memory-Subsystem-Information:\n--> max_used %i blocks in %i bytes (%ik).", g_6b6f74, g_6b6f70, g_6b6f70 >> 10);
	} else {
		sprintf(msg, "[*] Memory-Subsystem-Information: [*]\n--> max_used %i blocks in %i bytes (%ik). %i block(s) left in %i (%ik) bytes.",
		    g_6b6f74, g_6b6f70, g_6b6f70 >> 10, g_6b6f6c, g_6b6f68, g_6b6f68 >> 10);
	}
	p = &g_14cc5c0;
	do {
		if (filter != 0 && strstr(p->name, filter) != 0) {
			show = 1;
		} else {
			show = 0;
		}
		if (p->max_blocks > 0 && (p->name[0] != '!' || p->used_blocks != 0 || show) && (filter == 0 || show)) {
			strcpy(name, p->name);
			colon = strrchr(name, ':');
			if (colon != 0) {
				*colon = 0;
			}
			if (p->used == 0 && p->used_blocks == 0) {
				sprintf(msg, "[%s] w/ %i (%ik) bytes in %i block(s) (called %i times).", name, p->max, p->max >> 10, p->max_blocks, p->calls);
			} else {
				sprintf(msg, "[%s] -> w/ %i/%i (%ik/%ik) bytes in %i/%i block(s) (called %i times).", name, p->used, p->max, p->used >> 10,
				    p->max >> 10, p->used_blocks, p->max_blocks, p->calls);
			}
			if (show) {
				for (i = 0, b = g_6b6f80; i < g_6b6f64; i++, b++) {
					if (b->ptr != 0 && b->pool == p) {
						sprintf(msg, "{%s} w/ %i bytes (%ik).", b->tag, b->size, b->size >> 10);
					}
				}
			}
		}
		p = p->next;
	} while (p != 0);
}
