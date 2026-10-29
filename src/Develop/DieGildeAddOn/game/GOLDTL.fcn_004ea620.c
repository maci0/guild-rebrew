#include <string.h>
#include <stdlib.h>

extern char* g_773da8;

char* __cdecl gm_StartFilteredEntitySearch(int, int, int);
char* __cdecl gm_FindNextFilteredEntity(void);
char* __cdecl fcn_00508e40(int);
int __cdecl gm_WalkEntityChain(unsigned short);
int __cdecl fcn_004e8240(unsigned char, char*, char*, int, int);
void __cdecl fcn_004ea4b0(void*, unsigned int);
void __cdecl fcn_004ea560(void*, unsigned int);

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
	int t;

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
			kind = *(unsigned short*) (ent + 0x27);
			if (kind != 0xffff && kind != *(unsigned short*) g_773da8 && (*(unsigned char*) (ent + 0x5a) & 1) == 0) {
				found++;
				rec = (char*) (kind * 0x21c + 0x7f4ca0);
				t = *(unsigned char*) (kind * 0x21c + 0x7f4e04);
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
			kind = *(unsigned short*) (ent + 0x27);
			if (kind != 0xffff && kind != *(unsigned short*) g_773da8 && (*(unsigned char*) (ent + 0x5a) & 1) == 0) {
				found++;
				rec = (char*) (kind * 0x21c + 0x7f4ca0);
				t = *(unsigned char*) (kind * 0x21c + 0x7f4e04);
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
	best = 0;
	value = 0;
	if (b[1] != -1 || a[1] != -1) {
		existing = fcn_00508e40(b[1] != -1 ? b[1] : a[1]);
		if (existing != 0) {
			value = gm_WalkEntityChain(*(unsigned short*) existing);
		}
	}
	for (i = 0; i < count; i++) {
		n = gm_WalkEntityChain(*(unsigned short*) cand[i]);
		if (value < n) {
			value = n;
			best = (char*) cand[i];
		}
	}
	if (best == 0 || best == existing) {
		return;
	}
	t = *(unsigned char*) (best + 0x164);
	if (existing != 0) {
		kind = *(unsigned char*) (existing + 0x164);
		if (abs(kind - t) < 6) {
			fcn_004ea560(existing, *(unsigned char*) (existing + 0x169));
			fcn_004ea4b0(best, *(unsigned char*) (existing + 0x169));
			if (t >= 1 && t <= 6) {
				fcn_004e8240((unsigned char) b[0], best, 0, 1, 0xff);
			} else {
				fcn_004e8240((unsigned char) a[0], best, 0, 1, 0xff);
			}
			return;
		}
		if (t >= 1 && t <= 6) {
			fcn_004e8240((unsigned char) b[0], best, 0, 1, 0xff);
			fcn_004e8240((unsigned char) a[0], 0, 0, 1, 0xff);
			kind = 0x1c;
		} else {
			fcn_004e8240((unsigned char) b[0], 0, 0, 1, 0xff);
			fcn_004e8240((unsigned char) a[0], best, 0, 1, 0xff);
			kind = 0x1d;
		}
		fcn_004ea560(existing, *(unsigned char*) (existing + 0x169));
		fcn_004ea4b0(best, kind);
		return;
	}
	if (t >= 1 && t <= 6) {
		fcn_004e8240((unsigned char) b[0], best, 0, 1, 0xff);
		kind = 0x1c;
	} else {
		fcn_004e8240((unsigned char) a[0], best, 0, 1, 0xff);
		kind = 0x1d;
	}
	fcn_004ea4b0(best, kind);
}
