/*
 * Round/day refresh for the town view.
 *
 * Rebuilt from the native listing 0x540020..0x541149 (size 4393).  Native
 * frame: `sub esp,0x3b8` with ebx/ebp/esi/edi saved, so the local area is
 * 0x3a8 bytes above a 0x10 save slot.
 *
 * Local frame recovered from the esp offsets in the listing:
 *   0x10 int            loop counter, address-taken by fcn_004fd400
 *   0x14 float          age of the newest entity
 *   0x18 int            candidate age / scratch
 *   0x1c int            scratch
 *   0x20 pos14_7f4c00   the clock record handed to fcn_0052a310
 *   0x30 short          entity index produced by fcn_004fd400
 *   0x34 Ev (0x7c)      HUD element record, always zeroed 0xf8 with 0x100
 *   0xb0 Ev (0x7c)      second element record, zeroed by the same rep stosd
 *   0x12c Ev (0x7c)     timer record: {int stamp; int now}
 *   0x1a8 char[0x210]   render list filled by fcn_0050e380
 */
#include "client_types.h"

#pragma pack(2)
typedef struct {
	int a;
	int b;
	int c;
	short d;
} Date;					/* 0x14 bytes with tail padding */
#pragma pack()

typedef struct {
	char pad0[4];
	unsigned char id;		/* +0x04 */
	char pad5[3];
	int ent;			/* +0x08 entity index */
	int kind;			/* +0x0c */
	char pad10[0x18];
	int year;			/* +0x28 */
	int mon;			/* +0x2c */
	int day;			/* +0x30 */
	short wd;			/* +0x34 */
	unsigned char visible;		/* +0x36 */
	char pad37[0x45];
} Element;				/* 0x7c */

extern int g_774970;			/* 0x00774970 */
extern unsigned char g_7747b0;		/* 0x007747b0 */
extern int g_774950;			/* 0x00774950 */
extern int g_774978;			/* 0x00774978 */
extern int g_6a3420;			/* 0x006a3420 */
extern Date g_7f4c00;			/* 0x007f4c00 */
extern unsigned char g_slot_table[];	/* 0x007f4ca0 */
extern int g_1040480;
extern int g_1040484;
extern int g_1040488;
extern int g_104048c;
extern int g_1040490;
extern int g_1040494;

int __cdecl fcn_00509570(void*);
int __cdecl fcn_00500e20(int*);
int __cdecl fcn_0052a310(Date*);
int __cdecl fcn_004ec9e0(void);
void* __cdecl fcn_004730c0(int, int, int, int, int, int, int);
void __cdecl fcn_005373e0(int, int);
void __cdecl fcn_00469e30(int);
void __cdecl fcn_00473150(void*);
void __cdecl fcn_00535770(int);

/* ADDRESS: GOLDTL 0x00540020 */
void __cdecl fcn_00540020(void)
{
	int i;
	Date pos;
	Element ev;
	Element ev2;
	Element tm;
	unsigned char arr[0x210];
	unsigned char* v5;
	int season;
	int zero;
	void* hp;

	zero = 0;
	hp = 0;
	v5 = (unsigned char*) fcn_00509570(&g_slot_table[(g_774970 & 0xffff) * 0x21c]);
	fcn_00500e20((int*) &g_7f4c00);
	pos = g_7f4c00;
	if ((g_7747b0 & 4) && (2 <= g_774950)) {
		pos.a++;
	}
	season = fcn_0052a310(&pos);
	fcn_004ec9e0();
	*(float*) (v5 + 0x58) = 0.5f;
	*(float*) (v5 + 0x5c) = 1.0f;
	*(float*) (v5 + 0x60) = 1.0f;

	if (g_6a3420 != 0) {
		g_1040488 = zero;
		g_1040480 = g_1040494;
		g_1040484 = zero;
		g_104048c = g_1040490;
		if (g_774978 == zero) {
			hp = fcn_004730c0(zero, zero, g_1040494, g_1040490, 0x67d67c, zero, 1);
			while (!(*(unsigned char*) hp & 4)) {
				fcn_005373e0(0x24087, zero);
			}
			fcn_00469e30(0x79d);
			fcn_00473150(hp);
			fcn_004730c0(zero, zero, g_1040494, g_1040490, 0x67d67c, 0x32, 0xa);
		}
	}
	if (g_7747b0 & 4) {
		fcn_00535770(0x24087);
	}
}
