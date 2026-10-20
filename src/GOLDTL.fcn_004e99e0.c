/* Office reassignment pass.  Two sweeps over one office's slot list: the
   status 2 entries push the office holders towards or away from the applicant,
   and the status 3 entries resolve a free office by weighted vote over the
   matching slot-table records. */

#include "Develop/DieGildeAddOn/game/aemter.h"

extern char g_slot_table[];
char* __cdecl fcn_00508e40(int);
int __cdecl fcn_004aacb0(unsigned short*, unsigned short*, unsigned short*, int*);
int __cdecl fcn_004aae50(int, unsigned short*, int*, int*);
int __cdecl fcn_004c4450(int);
void __cdecl fcn_004c54c0(int, int, int, int);
int __cdecl fcn_004e8240(unsigned char, unsigned char*, unsigned char*, int, int);
int __cdecl fcn_004e9180(char*, int);
void __cdecl fcn_00535960(void);
unsigned short __cdecl gm_RandomMod(int);

/* ADDRESS: GOLDTL 0x004e99e0 */
void __cdecl fcn_004e99e0(int office, int count, OFFICE_SLOT* list)
{
	int remain;
	int i;
	int k;
	int n;
	int b;
	int amount;
	int vote[6];
	int score[6];
	char* self;
	char* other;
	char* ent;
	OFFICE_SLOT* p;
	OFFICE_SLOT* recs[5];
	int ids[5];
	int version;
	int held;
	int id;
	int j;
	int best;
	int pick;
	int tie;
	char* h;

	remain = 0;
	p = list;
	for (i = count; i > 0; i--) {
		if (p->status == 2) {
			remain++;
		}
		p++;
	}
	for (i = 0; i < count && remain != 0; i++) {
		p = list + i;
		vote[0] = 0;
		vote[1] = 0;
		vote[2] = 0;
		if (p->status != 2) {
			continue;
		}
		remain--;
		self = fcn_00508e40(p->mplayerid);
		other = fcn_00508e40(p->msetter);
		if (self == 0 || other == 0) {
			continue;
		}
		for (k = 0; k < count; k++) {
			ids[k] = 3;
			ent = fcn_00508e40(list[k].mplayerid);
			if (ent != 0 && *(char*) (ent + 0x166) != 0
			    && *(char*) (ent + 0x1b1) == 0) {
				held = fcn_004aacb0((unsigned short*) ent,
				    (unsigned short*) self, (unsigned short*) other,
				    (int*) score);
				ids[k] = held;
				vote[held]++;
			}
		}
		if (vote[0] <= vote[1]) {
			for (k = 0; k < count; k++) {
				id = list[k].mplayerid;
				if (id != *(int*) (self + 4) && id != -1
				    && ids[k] <= 2) {
					if (ids[k] == 0) {
						amount = -20;
					} else if (ids[k] == 1) {
						amount = 0x14;
					} else {
						amount = 4;
					}
					fcn_004c54c0(id, *(int*) (self + 4), amount, 1);
				}
			}
			version = fcn_004e8240(p->id, (unsigned char*) self, 0, 1, 0xff);
		} else {
			for (k = 0; k < count; k++) {
				id = list[k].mplayerid;
				if (id != *(int*) (self + 4) && id != -1
				    && ids[k] <= 2) {
					if (ids[k] == 0) {
						fcn_004c54c0(id, *(int*) (self + 4), -10, 1);
					}
					if (ids[k] == 1) {
						amount = 10;
					} else {
						amount = -4;
					}
					fcn_004c54c0(id, *(int*) (self + 4), amount, 1);
				}
			}
			version = fcn_004e8240(p->id, 0, 0, 3, 0xff);
		}
		if (version != -1) {
			while (!fcn_004c4450(version)) {
				fcn_00535960();
			}
		}
	}
	remain = 0;
	if (1 <= count) {
		p = list;
		for (i = count; i != 0; i--) {
			if (p->status == 3) {
				remain++;
			}
			p++;
		}
	}
	for (i = 0; i < count && remain != 0; i++) {
		p = list + i;
		n = 0;
		vote[0] = 0;
		vote[1] = 0;
		vote[2] = 0;
		vote[3] = 0;
		ids[0] = -1;
		ids[1] = -1;
		ids[2] = -1;
		ids[3] = -1;
		ids[4] = -1;
		if (p->status != 3 || p->pcount == 0) {
			continue;
		}
		remain--;
		{
			for (h = g_slot_table; (int) h < (int) (g_slot_table + 0x64000);
			    h += 0x21c) {
				if (n >= p->pcount || 4 <= n) {
					break;
				}
				if (*(char*) (h + 0x168) == p->mamt) {
					recs[n] = (OFFICE_SLOT*) h;
					ids[n] = *(int*) (h + 4);
					n++;
				}
			}
		}
		if (n == 0) {
			continue;
		}
		if (n != 1) {
			for (k = n; k < 4; k++) {
				ids[k] = -1;
				score[k] = 0;
			}
			for (k = 0; k < count; k++) {
				ent = fcn_00508e40(list[k].mplayerid);
				score[k] = -1;
				if (ent != 0 && fcn_004e9180(ent, p->mamt) != 0
				    && *(char*) (ent + 0x1b1) == 0) {
					score[k] = fcn_004aae50(p->id,
					    (unsigned short*) ent, vote, (int*) ids);
				}
			}
			for (k = 0; k < count; k++) {
				if (score[k] == -1) {
					continue;
				}
				for (j = 0; j < n; j++) {
					if (*(int*) ((char*) recs[j] + 4) == score[k]) {
						vote[j]++;
					}
				}
			}
			{
				best = -1;
				pick = -1;
				tie = 1;
				for (j = 0; j < n; j++) {
					if ((int) vote[j] <= best) {
						if ((int) vote[j] == best) {
							tie = 1;
						}
					} else {
						tie = 0;
						pick = j;
						best = vote[j];
					}
				}
				if (tie) {
					k = gm_RandomMod(n);
					for (j = n; j != 0; j--) {
						if (vote[k] == best) {
							pick = k;
							break;
						}
						k = (k + 1) % n;
					}
				}
				version = fcn_004e8240(p->id,
				    (unsigned char*) recs[pick], 0, 1, 0xff);
			}
		} else {
			version = fcn_004e8240(p->id, (unsigned char*) recs[0], 0, 1, 0xff);
		}
		if (version != -1) {
			while (!fcn_004c4450(version)) {
				fcn_00535960();
			}
		}
	}
}
