#include "gold_rec.h"

/* Native view of the 42-row, 0x18-stride slot table at GOLD 0x925120
 * (data row g_9a9220, link symbol _g_office_slots). Field names are
 * inferred from this function. */
typedef struct {
	unsigned char id;
	char pad1[3];
	int owner;
	unsigned char kind;
	char pad9[3];
	int count;
	unsigned char state;
	char pad11[3];
	int holder;
} OFFICESLOT;

extern char g_office_slots[0x3f0];

/* ADDRESS: GOLD 0x004e6e20 */
void __cdecl ClearUserRecords(GOLDUser *p, int who)
{
	unsigned short lim = GOLD_limit;
	int i;

	for (i = 0; i < 42; i++) {
		if (((OFFICESLOT *)g_office_slots)[i].owner == p->f04 && who) {
			((OFFICESLOT *)g_office_slots)[i].owner = -1;
			((OFFICESLOT *)g_office_slots)[i].count = 0;
			((OFFICESLOT *)g_office_slots)[i].state = (lim > 11) ? 4 : 3;
		} else if (((OFFICESLOT *)g_office_slots)[i].holder == p->f04) {
			((OFFICESLOT *)g_office_slots)[i].state = 1;
		} else {
			continue;
		}
		((OFFICESLOT *)g_office_slots)[i].holder = -1;
	}

	if (p->b168) {
		for (i = 0; i < 42; i++) {
			if (((OFFICESLOT *)g_office_slots)[i].kind == (unsigned char)p->b168) {
				if (((OFFICESLOT *)g_office_slots)[i].count > 0) {
					((OFFICESLOT *)g_office_slots)[i].count--;
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
