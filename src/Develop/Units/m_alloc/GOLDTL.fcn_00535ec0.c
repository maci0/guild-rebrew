#include "Develop/DieGildeAddOn/game/ch_queue.h"
#include "client_types.h"

extern unsigned char g_14cf950;
extern char g_6b5c60[];
extern char* g_7e2aa0;
extern char* g_7ea360;
extern char g_7f4ca0[];
extern unsigned char g_7f4e51[];
extern pos14_7f4c00 g_7f4c00;
extern int g_774664;
extern char* g_7746c4;
extern unsigned char* g_7746c8;
extern char* g_7746cc;
extern int g_7747b0;
extern int g_774804;
#include "Develop/DieGildeAddOn/game/game_player.h"

void __cdecl fcn_00406340(char*, char*, int);
char* __cdecl CreateAnimationEvent(char*, char*);
int __cdecl fcn_00406670(char*, char*);
void __cdecl fcn_00407800(char*, int, char*);
void __cdecl m_FreeTracked(void*);
int __cdecl gm_RandomMod(int);
void __cdecl d3_DestroyObject(int);
void __cdecl fcn_004b3b30(void);
void __cdecl fcn_004c5530(void*);
int __cdecl fcn_004c5790(int, void*);
void __cdecl fcn_004c5980(void*);
int __cdecl fcn_004c4450(int);
char* __cdecl fcn_004c4480(int);
int __cdecl fcn_004c6470(int, int);
int __cdecl fcn_004c64b0(int, int, int, int, int, int, char*);
void __cdecl fcn_00500bb0(pos14_7f4c00*, int, int, int);
void __cdecl fcn_00535960(void);

/* ADDRESS: GOLDTL 0x00535ec0 */
void __cdecl fcn_00535ec0(void)
{
	/* Slot, seat and action records are built in fixed char buffers and
	   written through byte offsets; the slot table stride is 0x21c. */
	char slot_buf[0x114];
	char seat_buf[0xf8];
	char act_buf[0xf8];

	switch (g_14cf950) {
	case 0x20: {
		unsigned short si;
		unsigned short slot_id;
		int slot_val;
		int* l2;
		char* p;
		int n;
		int i;

		for (i = 0; i < 0x45; i++) {
			((int*) slot_buf)[i] = 0;
		}
		si = g_774970;
		slot_buf[8] = 4;
		slot_buf[0x26] = 0x22;
		*(int*) (slot_buf + 0x14) = -1;
		slot_buf[0x30] = 2;
		slot_val = *(int*) (si * 0x21c + 0x7f4ca4);
		*(int*) (slot_buf + 0x0c) = slot_val;
		*(int*) (slot_buf + 0x34) = slot_val;
		l2 = (int*) (slot_buf + 0x34);
		n = 1;
		p = g_7f4ca0;
		while (n < 2) {
			slot_id = *(unsigned short*) p;
			if (slot_id != 0xffff && *(unsigned char*) (p + 0x166) != 0
			    && si != slot_id) {
				l2[n] = *(int*) (p + 4);
				n++;
			}
			p += 0x21c;
			if (p >= (char*) 0x85a0a0) {
				break;
			}
		}
		*(pos14_7f4c00*) (slot_buf + 0x18) = g_7f4c00;
		slot_buf[0x7c] = 0;
		fcn_00500bb0((pos14_7f4c00*) (slot_buf + 0x18), 0, 0x1e, 0);
		fcn_004c5980(slot_buf + 0x0c);
		return;
	}
	case 0x19:
		fcn_004c6470(*(int*) (g_774970 * 0x21c + 0x7f4ca4), 1);
		return;
	case 0x22: {
		char* m;

		if (g_7ea360 == 0) {
			return;
		}
		m_FreeTracked(*(void**) (g_7ea360 + 0x184));
		*(int*) (g_7ea360 + 0x184) = 0;
		return;
	}
	case 0x24:
		g_7f4e51[g_774970 * 0x21c] = 2;
		return;
	case 0x16: {
		int i;

		i = g_774664;
		*(int*) (i * 0x21c + 0x7f4cc4) += gm_RandomMod(0x80) & 0xffff;
		return;
	}
	case 0x30:
		if (g_7e2aa0 == 0) {
			return;
		}
		act_buf[4] = 0x47;
		*(int*) (act_buf + 0x0c) = -1;
		act_buf[0x36] = 2;
		*(int*) (act_buf + 8) = *(int*) (g_774970 * 0x21c + 0x7f4ca4);
		*(pos14_7f4c00*) (act_buf + 0x28) = g_7f4c00;
		*(int*) (act_buf + 0x5c) = *(int*) (g_774970 * 0x21c + 0x7f4ca4);
		*(unsigned short*) (act_buf + 0x62) = 0x1d76;
		*(unsigned short*) (act_buf + 0x60) = 0x1d6d;
		*(int*) (act_buf + 0x58) = *(int*)
		    (*(unsigned short*) (g_7e2aa0 + 0x27) * 0x21c + 0x7f4ca4);
		fcn_004c5530(act_buf);
		return;
	case 0x23: {
		char* q;
		int slot_off;
		int n;

		slot_off = g_774970 * 0x21c;
		if (*(int*) (slot_off + 0x7f4cfc) != -1) {
			return;
		}
		for (n = g_774970 + 1; n < 0xff; n++) {
			q = (char*) (n * 0x21c + 0x7f4ca2);
			if (*(unsigned char*) (q + 7) == 1 && *(unsigned char*) q != 0x0a
			    && *(int*) (q + 0x5a) == -1) {
				*(char*) (n * 0x21c + 0x7f4ca2) = 8;
				*(int*) (n * 0x21c + 0x7f4cfc) = *(int*) (slot_off + 0x7f4ca4);
				*(unsigned short*) (n * 0x21c + 0x7f4cf0) =
				    *(unsigned short*) (slot_off + 0x7f4cf0);
				*(int*) (slot_off + 0x7f4cfc) = *(int*) (n * 0x21c + 0x7f4ca4);
				*(unsigned char*) (slot_off + 0x7f4ca8) = 0;
				return;
			}
		}
		return;
	}
	case 0x17:
		fcn_004b3b30();
		return;
	case 0x11: {
		char* p;
		char* m;
		int n;
		int e;

		if (g_7746c8 == 0 && g_7746c4 == 0) {
			return;
		}
		e = 0;
		if (g_7746c8 != 0) {
			e = (int) g_7746c8;
		} else if (g_7746c4 != 0) {
			e = (int) g_7746c4;
		}
		n = fcn_004c64b0(0, *(int*) (e + 1), *(int*) (g_7746cc + 2), 0, 4, 0,
		    g_6b5c60);
		if (fcn_004c4450(n) == 0) {
			do {
				fcn_00535960();
			} while (fcn_004c4450(n) == 0);
		}
		p = fcn_004c4480(n);
		m = *(char**) (p + 0x184);
		if (m != 0) {
			m[0x8d] |= 0x10;
			fcn_00407800(m, 2, "ub_BIERKRUG");
			CreateAnimationEvent(*(char**) (p + 0x184), "sitzend/hinsetzen");
			fcn_00406340(*(char**) (p + 0x184), "sitzend/sitz_schreiben", 4);
		}
		return;
	}
	case 0x25: {
		int i;

		if (g_7ea360 == 0) {
			return;
		}
		for (i = 0; i < 0x3e; i++) {
			((int*) seat_buf)[i] = 0;
		}
		seat_buf[4] = 0x72;
		*(int*) (seat_buf + 0x0c) = -1;
		seat_buf[0x36] = 2;
		*(int*) (seat_buf + 8) = *(int*) (g_774970 * 0x21c + 0x7f4ca4);
		*(pos14_7f4c00*) (seat_buf + 0x28) = g_7f4c00;
		*(int*) (seat_buf + 0x5c) = *(int*) (g_7ea360 + 4);
		fcn_004c5530(seat_buf);
		return;
	}
	case 0x26:
		if (g_7e2aa0 == 0) {
			return;
		}
		d3_DestroyObject(*(int*) (g_7e2aa0 + 0x61));
		return;
	case 0x2e: {
		unsigned char seat_id;
		int slot_off;
		int slot_val;
		char* q;
		int n;
		int i;

		if (g_774804 != 0) {
			return;
		}
		for (i = 0; i < 0x45; i++) {
			((int*) slot_buf)[i] = 0;
		}
		slot_off = g_774970 * 0x21c;
		seat_id = *(unsigned char*) (slot_off + 0x7f4ca9);
		q = (char*) 0x7f4ec5;
		n = 1;
		do {
			if (*(unsigned char*) q != seat_id) {
				break;
			}
			q += 0x21c;
			n++;
		} while (q < (char*) 0x85a0a9);
		slot_val = *(int*) (slot_off + 0x7f4ca4);
		*(int*) (slot_buf + 0x0c) = slot_val;
		*(int*) (slot_buf + 0x34) = slot_val;
		slot_buf[8] = 6;
		slot_buf[0x26] = 0x20;
		*(int*) (slot_buf + 0x14) = -1;
		slot_buf[0x30] = 2;
		*(int*) (slot_buf + 0x38) = *(int*) (n * 0x21c + 0x7f4ca4);
		*(pos14_7f4c00*) (slot_buf + 0x18) = g_7f4c00;
		fcn_00500bb0((pos14_7f4c00*) (slot_buf + 0x18), 0, 0x1e, 0);
		fcn_004c5980(slot_buf + 0x0c);
		return;
	}
	case 0x1e: {
		char* m;

		*(unsigned char*) (g_774970 * 0x21c + 0x7f4e06) =
		    *(unsigned char*) (g_774970 * 0x21c + 0x7f4e06) == 0 ? 0x0f : 0;
		if (g_7ea360 == 0) {
			return;
		}
		ch_CancelActionQueue(*(char**) (g_7ea360 + 0x184));
		m = *(char**) (g_7ea360 + 0x184);
		if (*(unsigned char*) (m + 0x8c) & 0x10) {
			fcn_00406670(m, "sitzend/aufstehen");
			return;
		}
		CreateAnimationEvent(m, "sitzend/hinsetzen");
		fcn_00406340(*(char**) (g_7ea360 + 0x184), "sitzend/sitz_schreiben", 6);
		return;
	}
	case 0x1f: {
		int i;

		if ((g_7747b0 & 4) == 0) {
			return;
		}
		for (i = 0; i < 0x1f; i++) {
			((int*) seat_buf)[i] = 0;
		}
		*(int*) seat_buf = -1;
		fcn_004c5790(0x11, seat_buf);
		return;
	}
	default:
		return;
	}
}
#if defined(REBREW_SERVER) || defined(REBREW_GOLD)
unsigned char _dpad_7e6068[17144];
#else
/* Reference gaps only; the emitted objects inside the span keep their own rows. */
unsigned char _dpad_7e6160[16896];
#endif
#if defined(REBREW_SERVER) || defined(REBREW_GOLD)
unsigned char _dpad_7ea360[38816];
#else
/* Reference gaps only; the emitted objects inside the span keep their own rows. */
unsigned char _dpad_7ea364[28];
unsigned char _dpad_7ea3bc[4];
unsigned char _dpad_7ea3c2[38398];
unsigned char _dpad_7f39c2[110];
unsigned char _dpad_7f3a38[36];
unsigned char _dpad_7f3a60[96];
unsigned char _dpad_7f3ae0[32];
#endif
