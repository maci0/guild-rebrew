extern char s_6a5b84[];
extern char s_6a5b8c[];
extern float g_6628a0;
extern float g_662948;
extern float g_6640b4;
extern char* lpGebaeudePROT;
extern char* lpGebaeudeINST;
#include "GOLDTL.fcn_005522d0_gconf.h"

void* __cdecl m_alloc(unsigned int size, const char* tag);
int __cdecl gm_RandomMod(int n);
float __cdecl gm_RandomFloat01Squared(void);
int __cdecl fcn_004c4450(unsigned int id);
void* __cdecl fcn_004c4480(unsigned int id);
unsigned int __cdecl fcn_004c5620(int state, void* ev);
void __cdecl fcn_004c57e0(unsigned int h, int flag);
void __cdecl fcn_004c5c80(unsigned int h);
void __cdecl fcn_004c5da0(unsigned int h, unsigned int id, int a3, int a4, int a5, char* tag);
void __cdecl fcn_00500bb0(void* q, int a2, int a3, int a4);
float __cdecl fcn_00508490(char* entity);
void* __cdecl fcn_00508e40(unsigned int slot_id);
void __cdecl gm_ResolveEntityById(char** out, int a2, int a3, int id);
void __cdecl fcn_0051af00(char* buf, char* fmt, ...);
int __cdecl fcn_00529670(char* a, char* b);
void __cdecl fcn_00546190(void* ev);
void __cdecl fcn_005498b0(char* a1, char* a2, char* a3, char* a4, int a5, float a6);
void __cdecl fcn_00551f90(void* ev);
void __cdecl fcn_005b2810(char* a1, char* a2);

/* ADDRESS: GOLDTL 0x005522d0 */
void __cdecl fcn_005522d0(char* ev)
{
	char buf[512];
	int picks[16];
	float scores[16];
	char* ent;
	char* slot;
	char* listp;
	void* rec;
	void* found;
	void* p;
	int nent;
	int slot_no;
	int bit_lo;
	int bit_hi;
	int sel;
	int left;
	int i;
	int n;
	int count;
	int state;
	float best;
	float f;

	if (*(int*) (ev + 0x70) == -1 || *(int*) (ev + 0x70) == -2) {
		if (*(unsigned char*) (ev + 0x78) & 2) {
			for (i = 0; i < 4; i++) {
				p = fcn_00508e40(*(unsigned int*) (ev + 0xbc + i * 4));
				if (p) {
					fcn_004c5c80(*(unsigned int*) ((char*) p + 4));
					fcn_004c57e0(*(unsigned int*) ((char*) p + 4), 1);
				}
			}
		}
		fcn_00546190(ev);
		return;
	}
	if (*(unsigned char*) (ev + 0x78) & 4) {
		return;
	}
	if (*(int*) (ev + 0x84) != -1 && !fcn_004c4450(*(unsigned int*) (ev + 0x84))) {
		return;
	}
	if (*(int*) (ev + 0x70) == 5) {
		fcn_00551f90(ev);
	}
	switch (*(unsigned int*) (ev + 0x70)) {
	case 0:
		for (i = 0; i < 4; i++) {
			p = 0;
			if (fcn_004c4450(*(unsigned int*) (ev + 0xbc + i * 4)) == 1) {
				p = fcn_004c4480(*(unsigned int*) (ev + 0xbc + i * 4));
			}
			if (p == 0) {
				*(unsigned int*) (ev + 0xbc + i * 4) = 0xffffffff;
			}
			else {
				*(unsigned int*) (ev + 0xbc + i * 4) = *(unsigned int*) ((char*) p + 4);
			}
		}
		fcn_00500bb0(ev + 0x52, 0, 1, 0);
		*(unsigned int*) (ev + 0x84) = fcn_004c5620(1, ev);
		return;
	case 1:
		slot_no = *(unsigned int*) (ev + 0xb0);
		n = 0x100;
		rec = 0;
		do {
			bit_lo = 0;
			bit_hi = 0;
			listp = lpGebaeudeINST + slot_no * 0xa9;
			sel = *(unsigned char*) (lpGebaeudePROT + *(unsigned char*) listp * 0x24d);
			if (sel > 0x1f) {
				bit_hi = 1 << ((sel - 0x20) & 0x1f);
			}
			else {
				bit_lo = 1 << (sel & 0x1f);
			}
			if (*(unsigned short*) (listp + 0x27) != 0xffff
				&& ((bit_lo & 0x807c4110) || (bit_hi & 1))) {
				rec = listp;
				break;
			}
			rec = 0;
			n--;
			slot_no = (slot_no + *(int*) (ev + 0xb4)) % 256;
		} while (n);
		slot_no = (slot_no + *(int*) (ev + 0xb4)) % 256;
		*(unsigned int*) (ev + 0xb0) = slot_no;
		if (rec) {
			fcn_0051af00(buf, s_6a5b8c, rec);
			count = 0;
			for (i = 0; i < 4; i++) {
				p = fcn_00508e40(*(unsigned int*) (ev + 0xbc + i * 4));
				if (p) {
					fcn_004c5c80(*(unsigned int*) ((char*) p + 4));
					fcn_004c5da0(*(unsigned int*) ((char*) p + 4),
						*(unsigned int*) ((char*) rec + 1), -1, 0, 1, s_6a5b84);
					count++;
				}
			}
			fcn_00500bb0(ev + 0x52, 0, count > 0 ? 5 : 0x14, 0);
			*(unsigned int*) (ev + 0xcc) = *(unsigned int*) ((char*) rec + 1);
			*(unsigned int*) (ev + 0x84) = fcn_004c5620(2, ev);
			return;
		}
		fcn_00500bb0(ev + 0x52, 0, 1, 0);
		*(unsigned int*) (ev + 0x84) = fcn_004c5620(-1, ev);
		return;
	case 2:
		rec = 0;
		gm_ResolveEntityById((char**) &rec, 0, 0, *(unsigned int*) (ev + 0xcc));
		fcn_00500bb0(ev + 0x52, 0, 5, 0);
		if (!rec) {
			break;
		}
		for (i = 0; i < 4; i++) {
			p = fcn_00508e40(*(unsigned int*) (ev + 0xbc + i * 4));
			if (p && !fcn_00529670((char*) p, (char*) rec)) {
				*(unsigned int*) (ev + 0x70) = 2;
				fcn_00500bb0(ev + 0x52, 0, 5, 0);
				*(unsigned int*) (ev + 0x84) = fcn_004c5620(2, ev);
				return;
			}
		}
		if (*(unsigned short*) ((char*) rec + 0x27) != 0xffff) {
			slot = (char*) g_slot_table
				+ *(unsigned short*) ((char*) rec + 0x27) * 0x21c;
			found = 0;
			i = 0;
			nent = 0;
			best = 1000.0f;
			for (n = 0; n < 16; n++) {
				picks[n] = -1;
			}
			ent = (char*) g_slot_table + 0x16c;
			left = 0;
			for (;;) {
				if (nent >= 16) {
					break;
				}
				if (*(unsigned char*) (ent - 0x16a) == 0 && *(void**) ent == rec) {
					scores[nent] = 1000.0f;
					picks[nent] = i;
					nent++;
				}
				else if (*(unsigned char*) (ent - 0x16a) == 1 && *(void**) ent == rec) {
					found = ent - 0x16c;
				}
				ent += 0x21c;
				i++;
				if ((int) ent >= 0x85a20c) {
					break;
				}
			}
			if (nent == 0) {
				goto after_scan;
			}
			f = gm_RandomFloat01Squared();
			if (f > g_662948) {
				f = g_6628a0;
			}
			f = f * nent;
			if (f <= g_6628a0) {
				f = g_6628a0;
			}
			count = (int) f;
			if (count > 0) {
				left = 1;
				for (n = 0; n < count; n++) {
					scores[n] = fcn_00508490((char*) g_slot_table + picks[n] * 0x21c);
				}
			}
			p = found;
			if (found && !gm_RandomMod(8)) {
				best = fcn_00508490((char*) found);
				left = 1;
			}
			if (!gm_RandomMod(0x100)) {
				fcn_00508490(slot);
			}
			if (left) {
				fcn_005b2810(slot, (char*) rec);
			}
			for (n = 0; n < count; n++) {
				if (scores[n] < g_6640b4) {
					fcn_005498b0(ev, (char*) g_slot_table + picks[n] * 0x21c,
						slot, (char*) rec, 1, scores[n]);
				}
			}
			if (best < g_6640b4) {
				fcn_005498b0(ev, (char*) found, slot, (char*) rec, 1, best);
			}
		}
after_scan:
		state = *(int*) (ev + 0xac) - 1;
		*(int*) (ev + 0xac) = state;
		if (state > 0) {
			*(unsigned int*) (ev + 0x84) = fcn_004c5620(1, ev);
			return;
		}
		rec = 0;
		gm_ResolveEntityById((char**) &rec, 0, 0, *(unsigned int*) (ev + 0xd0));
		if (!rec) {
			break;
		}
		count = 0;
		for (i = 0; i < 4; i++) {
			p = fcn_00508e40(*(unsigned int*) (ev + 0xbc + i * 4));
			if (p) {
				fcn_004c5c80(*(unsigned int*) ((char*) p + 4));
				fcn_004c5da0(*(unsigned int*) ((char*) p + 4),
					*(unsigned int*) ((char*) rec + 1), -1, 0, 1, s_6a5b84);
				count++;
			}
		}
		fcn_00500bb0(ev + 0x52, 0, count > 0 ? 1 : 10, 0);
		*(unsigned int*) (ev + 0x84) = fcn_004c5620(3, ev);
		return;
	case 3:
		fcn_00500bb0(ev + 0x52, 0, 5, 0);
		rec = 0;
		gm_ResolveEntityById((char**) &rec, 0, 0, *(unsigned int*) (ev + 0xd0));
		if (!rec) {
			break;
		}
		for (i = 0; i < 4; i++) {
			p = fcn_00508e40(*(unsigned int*) (ev + 0xbc + i * 4));
			if (p && !fcn_00529670((char*) p, (char*) rec)) {
				*(unsigned int*) (ev + 0x70) = 3;
				fcn_00500bb0(ev + 0x52, 0, 5, 0);
				*(unsigned int*) (ev + 0x84) = fcn_004c5620(3, ev);
				return;
			}
		}
		break;
	default:
		return;
	}
	*(unsigned int*) (ev + 0x84) = fcn_004c5620(-1, ev);
}
