#include <string.h>
#include <stdlib.h>

extern char* gm_CityEntity;
#include "Develop/DieGildeAddOn/game/entity_record.h"

char* __cdecl gm_StartFilteredEntitySearch(int, int, int);
char* __cdecl gm_FindNextFilteredEntity(void);
char* __cdecl gm_LookupEntityRecordById(int);
int __cdecl gm_WalkEntityChain(unsigned short);
int __cdecl amt_SendOfficeCommand(unsigned char, char*, char*, int, int);
void __cdecl amt_NotifyOfficeAppointed(void*, unsigned int);
void __cdecl amt_NotifyOfficeLost(void*, unsigned int);

/* ADDRESS: GOLDTL 0x004ea620 */
void __cdecl fcn_004ea620(void)
{
	int a[6];
	int b[6];
	unsigned int cand[16];
	char* ent;
	char* rec;
	char* existing;
	char* best;
	int value;
	int n;
	int i;
	int count;
	int found;
	int kind;
	unsigned short owner_id;
	unsigned char t;
	int best_i;
	memset(a, 0, sizeof(a));
	memset(b, 0, sizeof(b));
	memset(cand, 0, sizeof(cand));
	a[1] = -1;
	b[1] = -1;
	count = 0;
	value = 0;
	found = 0;
	ent = gm_StartFilteredEntitySearch(1, 5, 4);
	if (ent != 0) {
		do {
			if (count >= 0x10) {
				break;
			}
			owner_id = *(unsigned short*) (ent + 0x27);
			if (owner_id != 0xffff && owner_id != *(unsigned short*) gm_CityEntity && (*(unsigned char*) (ent + 0x5a) & 1) == 0) {
				found++;
				rec = (char*) (((char*)&((ENTITY_RECORD_VIEW*)g_7f4ca0)[owner_id]));
				t = *(unsigned char*) (rec + 0x164);
				if (t >= 1 && t <= 6) {
					for (i = 0; i < 0x10; i++) {
						if (cand[i] == (unsigned int) rec) {
							break;
						}
					}
					if (i == 0x10) {
						cand[count] = (unsigned int) rec;
						count++;
					}
				}
			}
			ent = gm_FindNextFilteredEntity();
		} while (ent != 0);
	}
	ent = gm_StartFilteredEntitySearch(1, 5, 0x10);
	if (ent != 0) {
		do {
			if (count >= 0x10) {
				break;
			}
			owner_id = *(unsigned short*) (ent + 0x27);
			if (owner_id != 0xffff && owner_id != *(unsigned short*) gm_CityEntity && (*(unsigned char*) (ent + 0x5a) & 1) == 0) {
				found++;
				rec = (char*) (((char*)&((ENTITY_RECORD_VIEW*)g_7f4ca0)[owner_id]));
				t = *(unsigned char*) (rec + 0x164);
				if (t >= 0x28 && t <= 0x2d) {
					for (i = 0; i < 0x10; i++) {
						if (cand[i] == (unsigned int) rec) {
							break;
						}
					}
					if (i == 0x10) {
						cand[count] = (unsigned int) rec;
						count++;
					}
				}
			}
			ent = gm_FindNextFilteredEntity();
		} while (ent != 0);
	}
	if (found < 3) {
		return;
	}
	if (count == 0) {
		return;
	}
	n = 2;
	rec = (char*) 0x9a9580;
	do {
		if (n == 0) {
			break;
		}
		t = (unsigned char) rec[8];
		if (t == 0x1d) {
			memcpy(a, rec, 0x18);
			n--;
		} else if (t == 0x1c) {
			memcpy(b, rec, 0x18);
			n--;
		}
		rec -= 0x18;
	} while ((int) rec >= 0x9a9220);
	existing = 0;
	if (b[1] != -1 || a[1] != -1) {
		existing = gm_LookupEntityRecordById(b[1] != -1 ? b[1] : a[1]);
	}
	if (existing != 0) {
		value = gm_WalkEntityChain(*(unsigned short*) existing);
	} else {
		value = 0;
	}
	best = 0;
	for (best_i = 0; best_i < count; best_i++) {
		rec = (char*) cand[best_i];
		n = gm_WalkEntityChain(*(unsigned short*) rec);
		if (n > value) {
			best = rec;
			value = n;
		}
	}
	if (best == 0 || best == existing) {
		return;
	}
	if (existing != 0) {
		t = *(unsigned char*) (best + 0x164);
		if (abs(*(unsigned char*) (existing + 0x164) - t) < 6) {
			amt_NotifyOfficeLost(existing, *(unsigned char*) (existing + 0x169));
			amt_NotifyOfficeAppointed(best, *(unsigned char*) (existing + 0x169));
			t = *(unsigned char*) (best + 0x164);
			if (t >= 1 && t <= 6) {
				amt_SendOfficeCommand((unsigned char) b[0], best, 0, 1, 0xff);
			} else {
				amt_SendOfficeCommand((unsigned char) a[0], best, 0, 1, 0xff);
			}
			return;
		}
		if (t >= 1 && t <= 6) {
			amt_SendOfficeCommand((unsigned char) b[0], best, 0, 1, 0xff);
			amt_SendOfficeCommand((unsigned char) a[0], 0, 0, 1, 0xff);
			kind = 0x1c;
		} else {
			amt_SendOfficeCommand((unsigned char) b[0], 0, 0, 1, 0xff);
			amt_SendOfficeCommand((unsigned char) a[0], best, 0, 1, 0xff);
			kind = 0x1d;
		}
		amt_NotifyOfficeLost(existing, *(unsigned char*) (existing + 0x169));
		amt_NotifyOfficeAppointed(best, kind);
		return;
	}
	t = *(unsigned char*) (best + 0x164);
	if (t >= 1 && t <= 6) {
		amt_SendOfficeCommand((unsigned char) b[0], best, 0, 1, 0xff);
		kind = 0x1c;
	} else {
		amt_SendOfficeCommand((unsigned char) a[0], best, 0, 1, 0xff);
		kind = 0x1d;
	}
	amt_NotifyOfficeAppointed(best, kind);
}
