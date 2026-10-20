#include "client_types.h"
#include "Develop/DieGildeAddOn/game/aemter.h"
#include "Develop/DieGildeAddOn/game/entity.h"

char* __cdecl fcn_00508e40(int);
int __cdecl fcn_004e8240(unsigned char id, unsigned char* ea, unsigned char* eb, int x1, int x2);
int __cdecl fcn_004c4450(int);
void __cdecl fcn_00535960(void);
void __cdecl fcn_004e99e0(int, int, OFFICE_SLOT*);

/* ADDRESS: GOLDTL 0x004e9ee0 */
int __cdecl fcn_004e9ee0(void)
{
	int flags[6] = {0, 0, 0, 0, 0, 0};
	int order[6] = {6, 5, 4, 3, 2, 1};
	OFFICE_SLOT recs[6];
	OFFICE_SLOT* rp;
	char* e1;
	char* e2;
	char* h;
	unsigned char m;
	int n;
	int result;
	int i;
	int j;
	int v;

	result = 0;
	for (i = 0; i < 6; i++) {
		n = fcn_004e8b80(order[i], 6, recs);
		if (n > 0) {
			rp = recs;
			j = n;
			do {
				if (rp->status == 2) {
					e1 = fcn_00508e40(rp->msetter);
					e2 = fcn_00508e40(rp->mplayerid);
					if (e1 != 0 && *(unsigned char*) (e1 + 8) != 0) {
						if (e2 != 0 && *(unsigned char*) (e2 + 8) != 0) {
							flags[i] |= 1;
						} else {
							v = fcn_004e8240(rp->id, 0, 0, 4, 0xff);
							if (v != -1) {
								while (!fcn_004c4450(v)) {
									fcn_00535960();
								}
							}
						}
					} else {
						v = fcn_004e8240(rp->id, (unsigned char*) e2, 0, 1, 0xff);
						if (v != -1) {
							while (!fcn_004c4450(v)) {
								fcn_00535960();
							}
						}
					}
				} else if (rp->status == 3 && rp->pcount >= 1) {
					m = rp->mamt;
					for (h = (char*) g_slot_table + 2;
						(int) h < (int) ((char*) g_slot_table + 768 * 0x21c + 2);
						h += 0x21c) {
						if (h[0x166] == m) {
							flags[i] |= 1;
							if ((*h == 6 || *h == 7) && h[0x1af] == 0) {
								flags[i] |= 2;
								break;
							}
						}
					}
				}
				rp++;
				j--;
			} while (j != 0);
		}
		if ((flags[i] & 1) && n > 0) {
			for (j = 0; j < n; j++) {
				e1 = fcn_00508e40(recs[j].mplayerid);
				if (e1 != 0 && (e1[2] == 6 || e1[2] == 7) && e1[0x1b1] == 0) {
					flags[i] |= 2;
					break;
				}
			}
		}
		if (flags[i] & 2) {
			result = 1;
		} else if ((flags[i] & 1) && result == 0) {
			fcn_004e99e0(order[i], n, recs);
		}
	}
	return result;
}
