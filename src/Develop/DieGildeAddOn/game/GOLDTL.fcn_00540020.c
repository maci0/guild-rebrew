/*
 * Round/day refresh for the town view.
 *
 * Rebuilt from the native listing 0x540020..0x541149 (size 4393).  Native
 * frame: `sub esp,0x3b8`, then the four saved registers are pushed below it
 * and locals run from esp+0x10 through esp+0x3b7.
 *
 * Local frame recovered from the esp offsets in the listing:
 *   0x10 int             loop counter, address-taken by fcn_004fd400
 *   0x14 int             age of the newest entity (float bit pattern)
 *   0x18 int             candidate age / scratch
 *   0x1c int             scratch
 *   0x20 Pos (0x14)      the clock record handed to fcn_0052a310; its +0x12
 *                        short is the entity index produced by fcn_004fd400
 *   0x34 Ev (0x7c)       HUD element record, always zeroed 0xf8 with 0x100
 *   0xb0 Ev (0x7c)       second element record, zeroed by the same rep stosd
 *   0x12c Ev (0x7c)      timer record, stamp/now at +0x00/+0x04
 *   0x1a8 char[0x220]    render list filled by fcn_0050e380 (0x210 in use,
 *                        0x10 of tail keeps the native 0x3b8 frame)
 */
#include <string.h>

#include "client_types.h"
#include "he_tables.h"

extern ApEvent g_7dcae0[256];	/* 0x007dcae0 */

#pragma pack(2)
typedef struct {
	int a;
	int b;
	int c;
	short d;
	short e;
	short f;
	short out;			/* +0x12, written by fcn_004fd400 */
} Pos;					/* 0x14 */
#pragma pack()

typedef struct {
	int stamp;			/* +0x00 */
	union {
		unsigned char id;	/* +0x04 */
		int now;		/* +0x04 */
	};
	int ent;			/* +0x08 */
	int kind;			/* +0x0c */
	int f10;			/* +0x10 */
	int f14;			/* +0x14 */
	char pad18[0x10];		/* +0x18..0x27 */
	int year;			/* +0x28 */
	int mon;			/* +0x2c */
	int day;			/* +0x30 */
	short wd;			/* +0x34 */
	unsigned char visible;		/* +0x36 */
	char pad37[0x21];		/* +0x37..0x57 */
	int f58;			/* +0x58 */
	int f5c;			/* +0x5c */
	char pad60[0x1c];
} Ev;					/* 0x7c */

extern int g_774970;			/* 0x00774970 */
extern unsigned char g_7747b0;		/* 0x007747b0 */
extern int g_774950;			/* 0x00774950 */
extern int g_774978;			/* 0x00774978 */
extern int g_7747f0;			/* 0x007747f0 */
extern unsigned char g_77670b;		/* 0x0077670b */
extern signed char g_6a3440;		/* 0x006a3440 */
extern int g_6a3420;			/* 0x006a3420 */
extern int g_6a25b8;			/* 0x006a25b8 */
extern int g_772514;			/* 0x00772514 */
extern unsigned char g_773d75;		/* 0x00773d75 */
extern int g_7e4314;			/* 0x007e4314 */
extern int g_1007cd0;			/* 0x01007cd0 */
extern pos14_7f4c00 g_7f4c00;		/* 0x007f4c00 */
extern char g_7f4ca0[];			/* slot table, stride 0x21c */
extern unsigned char* lpGebaeudePROT;		/* entity type table */
extern float g_696540[];
extern float g_696550[];
extern float g_664138;
extern float g_664154;
extern float g_662a6c;
extern int g_1040480;
extern int g_1040484;
extern int g_1040488;
extern int g_104048c;
extern int g_1040490;
extern int g_1040494;
extern int g_6a3764;
extern int g_6a3768;
extern int g_6a376c;
extern int g_6a3770;
extern int g_6a42f8;
extern int g_6a42fc;
extern int g_6a4300;
extern int g_100f1dc;
extern unsigned char g_14cf950[];

int __cdecl fcn_00509570(void*);
int __cdecl fcn_00500e20(int*);
int __cdecl fcn_0052a310(pos14_7f4c00*);
void __cdecl fcn_0052a890(pos14_7f4c00*);
int __cdecl fcn_004ec9e0(void);
void* __cdecl fcn_004730c0(int, int, int, int, int, int, int);
int __cdecl fcn_005373e0(int, int);
void __cdecl fcn_00469e30(int);
void __cdecl fcn_00469e70(void);
void __cdecl fcn_00473150(void*);
void __cdecl fcn_00535770(int);
void __cdecl fcn_005355f0(void);
void __cdecl fcn_0050e380(int, void*);
void __cdecl fcn_004fd400(short*, int*);
void* __cdecl fcn_004c5790(int, void*);
int __cdecl fcn_004c4450(void*);
void __cdecl fcn_00535960(void);
void __cdecl fcn_0042df30(int, int);
int __cdecl fcn_005463a0(int, ...);
void __cdecl fcn_004c5530(void*);
void __cdecl fcn_004c4eb0(int);
void __cdecl fcn_004c4ef0(int);
void __cdecl fcn_004c5150(int, int, char, int);
int __cdecl fcn_004c51a0(int, int, unsigned char, int);
void __cdecl fcn_004bbc30(int, int);
int __cdecl fcn_00471af0(int, int);
void __cdecl fcn_005459a0(int);
int __cdecl d2_CreateScrollPerga(void);
void __cdecl fcn_004727a0(int, int);
int __cdecl fcn_00472830(int, int);
void __cdecl fcn_0046e830(int, int, int, int, int);
int __cdecl fcn_00519190(int, ...);
void __cdecl fcn_004c57e0(int, int);
int __cdecl fcn_00546fe0(int);
void __cdecl fcn_00516f60(void);
void __cdecl fcn_005270c0(int);
void __cdecl fcn_00528fd0(void);
int __cdecl fcn_0050d2a0(void*);
void* __cdecl fcn_00503fe0(int, int, int);
void* __cdecl fcn_00502cd0(int, int, int, int);
int __cdecl fcn_00502850(void);
int __cdecl fcn_0047dca0(void*);
void __cdecl ch_SetVisible(int, int);
void* __cdecl fcn_00503e80(void);
int __cdecl fcn_00504bd0(int);
int __cdecl fcn_0047d240(void*);
int __cdecl fcn_0042e410(int);
int __cdecl fcn_00508da0(void*);
int __cdecl fcn_0050cf50(void*, int);
int __cdecl fcn_0047dd60(void*);
int __cdecl fcn_00567170(void*, int*, int*, int*);
void* __cdecl fcn_00426cc0(int);
void __cdecl fcn_00428720(void*);
void __cdecl fcn_00406120(void*);
char* __cdecl fcn_0040c120(void*, int, ...);
void __cdecl fcn_004ec660(void*);
void __cdecl fcn_004c2d90(float, int);

#define SLOTPTR(k) ((char*) g_7f4ca0 + (k) * 0x21c)
#define SLOT4(k) (*(int *) (SLOTPTR(k) + 4))
#define ENTTYPE(t) (*(unsigned char *) (lpGebaeudePROT + (t) * 0x24d))
#define ENTCLASS(t) (*(unsigned char *) (lpGebaeudePROT + (t) * 0x24d + 0x247))
#define OBJBYTE (*(unsigned char *) obj)

/* ADDRESS: GOLDTL 0x00540020 */
void __cdecl fcn_00540020(void)
{
	int i;
	int agebits;
	int cand;
	int left;
	Pos pos;
	Ev evs[2];
	Ev tm;
	unsigned char arr[0x220];
	unsigned char* v5;
	int season;
	void* hp;
	void* wait;
	void* obj;
	int n;
	int w;

	v5 = (unsigned char*) fcn_00509570(SLOTPTR(g_774970 & 0xffff));
	hp = 0;
	fcn_00500e20((int*) &g_7f4c00);
	pos.a = g_7f4c00.a;
	pos.b = g_7f4c00.b;
	pos.c = g_7f4c00.c;
	pos.d = g_7f4c00.d;
	if ((g_7747b0 & 4) && (g_774950 > 1)) {
		pos.a++;
	}
	season = fcn_0052a310((pos14_7f4c00*) &pos);
	fcn_004ec9e0();
	*(float*) (v5 + 0x58) = 0.5f;
	*(float*) (v5 + 0x5c) = 1.0f;
	*(float*) (v5 + 0x60) = 1.0f;

	if (g_6a3420 != 0) {
		g_1040488 = 0;
		g_1040480 = g_1040494;
		g_1040484 = 0;
		g_104048c = g_1040490;
		if (g_774978 == 0) {
			hp = fcn_004730c0(0, 0, g_1040494, g_1040490, 0x67d67c, 0, 1);
			while (!(*(unsigned char*) hp & 4)) {
				fcn_005373e0(0, 0x24087);
			}
			fcn_00469e30(0x79d);
			fcn_00473150(hp);
			fcn_004730c0(0, 0, g_1040494, g_1040490, 0x67d67c, 0x32, 0xa);
		}
	}
	if (g_7747b0 & 4) {
		fcn_00535770(0x24087);
	}

	fcn_0050e380(g_774970 & 0xffff, arr);
	fcn_0052a890((pos14_7f4c00*) &pos);
	g_7e4314 = fcn_0052a310((pos14_7f4c00*) &pos);
	fcn_004fd400(&pos.out, &i);
	i = 0;
	tm.stamp = pos.a;
	tm.now = (*(int (__stdcall **) (void)) 0x662318) ();
	wait = fcn_004c5790(0, &tm);
	while (fcn_004c4450(wait) == 0) {
		fcn_00535960();
	}
	fcn_0042df30(0x538060, 1);

	if ((g_7747b0 & 0x80) == 0) {
		if (fcn_005463a0(1, 0, 0x66) == 0) {
			memset(evs, 0, sizeof(evs));
			evs[0].ent = SLOT4(g_774970 & 0xffff);
			evs[0].year = g_7f4c00.a;
			evs[0].id = 0x66;
			evs[0].kind = -1;
			evs[0].visible = 1;
			evs[0].mon = g_7f4c00.b;
			evs[0].day = g_7f4c00.c;
			evs[0].wd = g_7f4c00.d;
			fcn_004c5530(&evs[0]);
		}
		if (fcn_005463a0(1, 0, 0x70) == 0) {
			memset(evs, 0, sizeof(evs));
			evs[0].ent = SLOT4(g_774970 & 0xffff);
			evs[0].year = g_7f4c00.a;
			evs[0].id = 0x70;
			evs[0].kind = -1;
			evs[0].visible = 1;
			evs[0].mon = g_7f4c00.b;
			evs[0].day = g_7f4c00.c;
			evs[0].wd = g_7f4c00.d;
			fcn_004c5530(&evs[0]);
		}
		if (fcn_005463a0(1, 0, 0x68) == 0) {
			memset(evs, 0, sizeof(evs));
			evs[0].ent = SLOT4(g_774970 & 0xffff);
			evs[0].year = g_7f4c00.a;
			evs[0].id = 0x68;
			evs[0].kind = -1;
			evs[0].visible = 1;
			evs[0].mon = g_7f4c00.b;
			evs[0].day = g_7f4c00.c;
			evs[0].wd = g_7f4c00.d;
			fcn_004c5530(&evs[0]);
		}
	}
	if (g_7747f0 != 0) {
		if (fcn_005463a0(1, 0, 0x85) == 0) {
			memset(evs, 0, sizeof(evs));
			evs[0].ent = SLOT4(g_774970 & 0xffff);
			evs[0].year = g_7f4c00.a;
			evs[0].id = 0x85;
			evs[0].kind = -1;
			evs[0].visible = 1;
			evs[0].mon = g_7f4c00.b;
			evs[0].day = g_7f4c00.c;
			evs[0].wd = g_7f4c00.d;
			fcn_004c5530(&evs[0]);
		}
	}
	if (fcn_005463a0(1, 0, 0x7c) == 0) {
		memset(evs, 0, sizeof(evs));
		evs[0].ent = SLOT4(g_774970 & 0xffff);
		evs[0].year = g_7f4c00.a;
		evs[0].id = 0x7c;
		evs[0].kind = -1;
		evs[0].visible = 1;
		evs[0].mon = g_7f4c00.b;
		evs[0].day = g_7f4c00.c;
		evs[0].wd = g_7f4c00.d;
		fcn_004c5530(&evs[0]);
	}
	if (fcn_005463a0(1, 0, 0x93) == 0) {
		memset(evs, 0, sizeof(evs));
		evs[0].ent = SLOT4(g_774970 & 0xffff);
		evs[0].year = g_7f4c00.a;
		evs[0].id = 0x93;
		evs[0].kind = -1;
		evs[0].visible = 1;
		evs[0].mon = g_7f4c00.b;
		evs[0].day = g_7f4c00.c;
		evs[0].wd = g_7f4c00.d;
		fcn_004c5530(&evs[0]);
	}
	if (fcn_005463a0(1, 0, 0x84) == 0 && g_77670b != 0) {
		memset(evs, 0, sizeof(evs));
		evs[0].ent = SLOT4(g_774970 & 0xffff);
		evs[0].year = g_7f4c00.a;
		evs[0].id = 0x84;
		evs[0].kind = -1;
		evs[0].visible = 1;
		evs[0].mon = g_7f4c00.b;
		evs[0].day = g_7f4c00.c;
		evs[0].wd = g_7f4c00.d;
		fcn_004c5530(&evs[0]);
	}

	if (g_6a25b8 != -1) {
		fcn_00471af0(g_6a25b8, 0);
	}
	fcn_005459a0(0xffff);
	if (g_6a3420 != 0) {
		w = d2_CreateScrollPerga();
		fcn_004727a0(w, 2);
		fcn_00519190(0x7d);
		fcn_0046e830(-1, -1, g_772514, fcn_00472830(w, 1), 0x767);
		*(int*) (0x10161b4 + fcn_00472830(w, 1) * 972) = 0x18;
		fcn_004727a0(w, 1);
		fcn_00519190(0x2051, &pos, (int) g_696540[season],
			     (int) g_696550[season] % 12);
		fcn_00519190(0x1ef9);
		fcn_00519190(0x1eff, *(int*) (SLOTPTR(g_774970 & 0xffff) + 0x190));
		i = 0;
		while (i < 0x100) {
			if ((*(int*) ((char*) g_7dcae0 + i * 0x50 + 8) != 0
			     || *(int*) ((char*) g_7dcae0 + i * 0x50 + 0xc) != 0
			     || *(char*) ((char*) g_7dcae0 + i * 0x50 + 0x10) != 0)
			    && *(int*) ((char*) g_7dcae0 + i * 0x50 + 4) == (g_774970 & 0xffff)) {
				if (*(int*) ((char*) g_7dcae0 + i * 0x50 + 8) != 0) {
					if (*(int*) ((char*) g_7dcae0 + i * 0x50 + 8) >= 0) {
						fcn_00519190(0x1efc,
							     (char*) g_7dcae0 + i * 0x50 + 0x10,
							     *(int*) ((char*) g_7dcae0 + i * 0x50 + 8));
					} else {
						fcn_00519190(0x1efb,
							     (char*) g_7dcae0 + i * 0x50 + 0x10,
							     *(int*) ((char*) g_7dcae0 + i * 0x50 + 8));
					}
				} else if (*(int*) ((char*) g_7dcae0 + i * 0x50 + 0xc) > 0) {
					fcn_00519190(0x1efe,
						     (char*) g_7dcae0 + i * 0x50 + 0x10,
						     *(int*) ((char*) g_7dcae0 + i * 0x50 + 0xc));
				} else if (*(int*) ((char*) g_7dcae0 + i * 0x50 + 0xc) < 0) {
					fcn_00519190(0x1efd,
						     (char*) g_7dcae0 + i * 0x50 + 0x10,
						     *(int*) ((char*) g_7dcae0 + i * 0x50 + 0xc));
				} else {
					fcn_00519190(0x1efb,
						     (char*) g_7dcae0 + i * 0x50 + 0x10);
				}
			}
			i++;
		}
		for (i = 0; arr[4 + i * 5] != 0; i++) {
			if (i >= 9) {
				break;
			}
			fcn_00519190(0x1efd, arr[4 + i * 5] + 0x253, *(int*) (arr + 5 + i * 5));
		}
		fcn_00519190(0x1efa, *(int*) (SLOTPTR(g_774970 & 0xffff) + 0x194));
		while (fcn_005373e0(0x540020, 0x24087) != 0) {
			if (g_100f1dc == 2 || g_14cf950[0] == 0x1c) {
				*(int*) 0x774654 = 1;
			}
		}
		hp = fcn_004730c0(0, 0, g_1040494, g_1040490, 0x67d67c, 0x1e, 1);
		while (!(*(unsigned char*) hp & 4)) {
			fcn_005373e0(0, *(int*) 0x7e46ac | 0x80);
		}
		fcn_005355f0();
		fcn_00469e70();
	}
	fcn_004c51a0(-1, SLOT4(g_774970 & 0xffff), g_773d75,
		     -fcn_00546fe0(g_774970 & 0xffff));
	fcn_004bbc30(3, SLOT4(g_774970 & 0xffff));
	fcn_004c5790(1, 0);
	if (g_7747b0 & 4) {
		fcn_00535770(0x24087);
	}
	g_1040488 = g_6a376c;
	g_1040480 = g_6a3764;
	g_1040484 = g_6a3768;
	g_104048c = g_6a3770;
	fcn_00516f60();
	fcn_005270c0(1);
	fcn_00528fd0();
	if (g_6a3420 != 0) {
		if (hp != 0) {
			fcn_00473150(hp);
		}
		fcn_004730c0(0, 0, g_1040494, g_1040490, 0x67d67c, 0x32, 0xa);
	}
	if (g_6a25b8 != -1) {
		fcn_00471af0(g_6a25b8, 1);
	}
	if (g_6a3440 != 5 && g_6a3440 > -1) {
		if (fcn_005463a0(2, 0, 0x4c, 2, g_774970 & 0xffff) == 0) {
			memset(evs, 0, sizeof(evs));
			evs[0].id = 0x4c;
			evs[0].ent = SLOT4(g_774970 & 0xffff);
			evs[0].kind = SLOT4(g_774970 & 0xffff);
			evs[0].f10 = 0;
			evs[0].f14 = 0;
			evs[0].year = g_7f4c00.a;
			evs[0].mon = g_7f4c00.b;
			evs[0].day = g_7f4c00.c;
			evs[0].wd = g_7f4c00.d;
			evs[0].visible = 1;
			fcn_004c5530(&evs[0]);
		}
	}

	if (g_7747b0 & 8) {
		char* p;

		p = (char*) fcn_00503fe0(1, 0, 0x44);
		obj = fcn_00502cd0(*(int*) (p + 0x5d), 1, 4, 0x1d);
		if (obj != 0) {
			char* s;
			int ent;

			do {
				ent = *(int*) ((char*) obj + 0x3b);
				p = fcn_00503fe0(1, 1, *(int*) ((char*) obj + 0x1c));
				if (p != 0
				    && (s = SLOTPTR(*(unsigned short*) (p + 0x27))) != 0
				    && fcn_0047dca0(s) != 0)
					ch_SetVisible(ent, 1);
				else
					ch_SetVisible(ent, 0);
			} while ((obj = fcn_00502850()) != 0);
		}
	}

	for (i = 0; i < 0x300; i++) {
		int leftw;

		if (*(unsigned short*) SLOTPTR(i) == 0xffff) {
			continue;
		}
		if (*(unsigned char*) (SLOTPTR(i) + 2) == 6 || *(unsigned char*) (SLOTPTR(i) + 2) == 7) {
			continue;
		}
		leftw = fcn_0050d2a0(SLOTPTR(i)) * 75;
		left = leftw;
		n = 0;
		obj = fcn_00503fe0(1, 4, i);
		if (obj != 0) {
			do {
				if (fcn_00504bd0(OBJBYTE) == 1 || fcn_00504bd0(OBJBYTE) == 4
				    || fcn_00504bd0(OBJBYTE) == 2 || ENTTYPE(OBJBYTE) == 0x13
				    || ENTTYPE(OBJBYTE) == 4 || ENTTYPE(OBJBYTE) == 0x10
				    || ENTTYPE(OBJBYTE) == 5 || ENTTYPE(OBJBYTE) == 9) {
					unsigned char c = ENTCLASS(OBJBYTE);

					if (c == 1) {
						n += 2;
					} else if (c == 2) {
						n += 4;
					} else if (c == 3) {
						n += 8;
					}
				}
				if (fcn_0047d240(SLOTPTR(i)) != 0 || *(unsigned char*) (SLOTPTR(i) + 2) == 1) {
					w = (int) (fcn_0042e410(0x5a) & 0xffff);
					if (fcn_00508da0(obj) < w) {
						int ent;

						cand = fcn_0050cf50(obj, 0x64);
						*(float*) &agebits = (float) cand * g_664138;
						if (g_664154 > *(float*) &agebits) {
							*(float*) &agebits = 32.0f;
						}
						if ((*(float*) &cand = (float) left) * g_662a6c > *(float*) &agebits) {
							memset(evs, 0, sizeof(evs));
							evs[0].id = 0x1c;
							evs[0].kind = -1;
							evs[0].visible = 1;
							evs[0].f5c = 0xa;
							evs[0].ent = SLOT4(i);
							evs[0].f58 = *(int*) ((char*) obj + 1);
							fcn_004c4eb0(0x67e330);
							fcn_004c5150(-1, SLOT4(i), g_773d75,
								     (int) (*(float*) &agebits));
							fcn_004c5530(&evs[0]);
							fcn_004c4ef0(0x67e330);
							ent = (int) fcn_00509570(SLOTPTR(i));
							if (ent != 0) {
								*(int*) (ent + 0x44) =
									(int) ((float) *(int*) (ent + 0x44)
									       + *(float*) &agebits);
							}
							leftw = (int) (*(float*) &cand - *(float*) &agebits);
							left = leftw;
						}
					}
				}
			} while ((obj = fcn_00503e80()) != 0);
		}

		obj = fcn_00503fe0(1, 4, i);
		if (obj != 0) {
			do {
				unsigned char c;
				int v;

				if (fcn_00504bd0(OBJBYTE) != 1 && fcn_00504bd0(OBJBYTE) != 4
				    && fcn_00504bd0(OBJBYTE) != 2 && ENTTYPE(OBJBYTE) != 0x13
				    && ENTTYPE(OBJBYTE) != 4 && ENTTYPE(OBJBYTE) != 0x10
				    && ENTTYPE(OBJBYTE) != 5 && ENTTYPE(OBJBYTE) != 9) {
					goto next2;
				}
				c = ENTCLASS(OBJBYTE);
				if (c == 1) {
					v = leftw * 2 / n;
					*(volatile int*) ((char*) obj + 0x39) = v;
					v = v < 0 ? 0 : v;
					*(volatile int*) ((char*) obj + 0x39) = v;
					if (ENTTYPE(OBJBYTE) == 5) {
						if (v >= 0x2ee00) {
							v = 0x2ee00;
						}
					} else if (v >= 0xfa00) {
						v = 0xfa00;
					}
					*(volatile int*) ((char*) obj + 0x39) = v;
				} else if (c == 2) {
					v = leftw * 4 / n;
					*(volatile int*) ((char*) obj + 0x39) = v;
					v = v < 0 ? 0 : v;
					*(volatile int*) ((char*) obj + 0x39) = v;
					if (ENTTYPE(OBJBYTE) == 5) {
						if (v >= 0x4e200) {
							v = 0x4e200;
						}
					} else if (v >= 0x1f400) {
						v = 0x1f400;
					}
					*(volatile int*) ((char*) obj + 0x39) = v;
				} else if (c == 3) {
					v = leftw * 8 / n;
					*(volatile int*) ((char*) obj + 0x39) = v;
					v = v < 0 ? 0 : v;
					*(volatile int*) ((char*) obj + 0x39) = v;
					if (ENTTYPE(OBJBYTE) == 5) {
						if (v >= 0x9c400) {
							v = 0x9c400;
						}
					} else if (v >= 0x3e800) {
						v = 0x3e800;
					}
					*(volatile int*) ((char*) obj + 0x39) = v;
				}
next2:
				;
			} while ((obj = fcn_00503e80()) != 0);
		}
	}

	for (i = 0; i < 0x300; i++) {

		if (*(unsigned short*) SLOTPTR(i) == 0xffff) {
			continue;
		}
		((int*) (SLOTPTR(i) + 0x1c8))[0] &= 0xffffe7ff;
		if (fcn_0047dd60(SLOTPTR(i)) != 0) {
			*(int*) (SLOTPTR(i) + 0x1b8) = *(int*) (*(int*) (SLOTPTR(i) + 0x16c) + 0x39);
		}
	}

	cand = -1;
	agebits = -1;
	for (i = 0; i < 0x300; i++) {

		if (*(char**) (SLOTPTR(i) + 0x184) == 0) {
			continue;
		}
		if (fcn_00567170(SLOTPTR(i), &cand, &agebits, &left) == 0) {
			continue;
		}
		if (cand == *(int*) (*(char**) (SLOTPTR(i) + 0x184) + 0x2c)
		    && agebits == *(int*) (*(char**) (SLOTPTR(i) + 0x184) + 0x30)) {
			continue;
		}
		if (*(int*) (*(char**) (SLOTPTR(i) + 0x184) + 0x28) != -1) {
			fcn_00428720(fcn_00426cc0(*(int*) (*(char**) (SLOTPTR(i) + 0x184) + 0x28)));
		}
		fcn_00406120(*(char**) (SLOTPTR(i) + 0x184));
		if (agebits != -1) {
			char* r = fcn_0040c120(*(char**) (SLOTPTR(i) + 0x184), 0x33, left, cand, agebits);

			if (r != 0) {
				r += 0x70;
				*(int*) r = g_6a42f8;
				*(int*) (r + 4) = g_6a42fc;
				*(int*) (r + 8) = g_6a4300;
			}
		}
		if ((g_7747b0 & 8) && *(char**) (SLOTPTR(i) + 0x184) != 0
		    && *(unsigned char*) (SLOTPTR(i) + 2) == 0x0d && *(int*) (SLOTPTR(i) + 0x17c) == 0) {
			fcn_004c57e0(*(int*) (SLOTPTR(i) + 4), 1);
		}
	}

	g_1007cd0 = 1;
	fcn_004ec660(SLOTPTR(g_774970 & 0xffff));
	fcn_004c2d90(1.0f, 0x7d0);
}
