#include "gold_rec.h"

/* ADDRESS: GOLD 0x004e6e20 */
void __cdecl ClearUserRecords(GOLDUser *p, int who)
{
	unsigned short lim = GOLD_limit;
	int i;

	for (i = 0; i < 42; i++) {
		unsigned char *base = (unsigned char *)&GOLD_rec[i].val;
		if (*(int *)(base - 16) == p->f04 && who) {
			*(int *)(base - 16) = -1;
			*(int *)(base - 8) = 0;
			*(base - 4) = (lim > 11) ? 4 : 3;
		} else if (*(int *)base == p->f04) {
			*(base - 4) = 1;
		}
		*(int *)base = -1;
	}

	if (p->b168) {
		for (i = 0; i < 42; i++) {
			unsigned char *base = (unsigned char *)&GOLD_rec[i].f08;
			if (*(base - 4) == (unsigned char)p->b168) {
				if (*(int *)base > 0) {
					(*(int *)base)--;
				}
			}
		}
	}

	p->b168 = 0;
	if (who) {
		p->b166 = 0;
		p->b169 = 0;
	}
}
