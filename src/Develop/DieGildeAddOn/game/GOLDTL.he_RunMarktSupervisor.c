/* Market supervisor tick: refills the per-player market stock (g_85ab90),
 * re-prices the open slots and runs the trade lager cycles over the three
 * market halls starting at 0x868354.
 *
 * The native frame (0x1a8, no EBP frame) packs nine four/eight byte scratch
 * slots, one 0x80 slot record and one 0xf0 spare buffer; the untyped scratch
 * slots are reused with different meanings in the three passes, so they are
 * named after the pass that owns them. */

#include <string.h>

/* g_7f4c00: 14-byte market stamp, word view of the second field is compared. */
typedef struct {
	int a;
	unsigned short b;
	short b2;
	int c;
	short d;
} pos14m;

/* one market slot record, 0x80 bytes */
typedef struct {
	unsigned short id;
	short pad2;
	int f4;
	int f8;
	int fc;
	int f10;
	int f14;
	int f18;
	int f1c;
	float f20;
	float f24;
	float f28;
	float f2c;
	int f30;
	int f34;
	float f38;
	char pad3c[0x44];
} MarktSlot;

extern pos14m g_7f4c00;
extern char* g_773d78;
extern unsigned char g_773d75;
extern char* g_773da8;
extern char* lpObjektePROT;
extern unsigned char g_7747b0;
extern char g_85ab90[];

extern float g_6628a0;
extern float g_6628a8;
extern float g_6628d8;
extern float g_662910;
extern float g_662948;
extern float g_6629b0;
extern float g_662acc;
extern float g_662d34;
extern float g_664198;
extern float g_665ea0;
extern float g_665ec8;
extern double g_662908;
extern double g_662930;
extern double g_6629c8;
extern double g_6629f8;
extern double g_662ad8;
extern double g_662b20;
extern double g_6640f8;
extern double g_664468;
extern double g_665dd0;

int __cdecl fcn_00500d20(void*, void*);
void __cdecl fcn_00546190(char*);
int __cdecl fcn_0050d320(int, unsigned char);
void __cdecl fcn_004c5150(int, int, unsigned char, int);
char* __cdecl fcn_00503d10(int);
unsigned short* __cdecl fcn_00502cd0(int, int, int, ...);
int __cdecl gm_GetMsgField(void*, void*);
int __cdecl gm_RandomMod(int);
float __cdecl gm_RandomFloat01(void);
void __cdecl fcn_004c51f0(int, int, int, int, unsigned char, int);
int __cdecl fcn_004c61d0(MarktSlot*, unsigned char);
float __cdecl fcn_005025a0(int, int);
char* __cdecl fcn_00503e50(int);
void __cdecl fcn_00500bb0(void*, int, int, int);
void __cdecl fcn_00549330(char*, int);
int __cdecl gm_eval_SlotVoll(char*, int, int);
int __cdecl fcn_64d41a(char*, const char*, ...);

/* ADDRESS: GOLDTL 0x00568060 */
void __cdecl he_RunMarktSupervisor(char* a0)
{
	union { float f; int n; } uf;
	int i;
	float g;
	union { int n; char* p; } ub;
	union { int n; char* p; } up;
	double d;
	int v;
	char* lager;
	int t;
	MarktSlot rec;
	char scratch[0x100];
	MarktSlot* slot;
	char* ent;
	char* q;
	unsigned char kind;
	char* bar;
	char* pat;

	if (g_773d78 == 0) {
		fcn_00546190(a0);
		return;
	}
	v = fcn_00500d20((void*) (a0 + 0x60), (void*) &g_7f4c00);
	if (g_7f4c00.b > 0x14) {
		fcn_00546190(a0);
		return;
	}
	if (v == 0) {
		return;
	}
	*(pos14m*) (a0 + 0x60) = g_7f4c00;
	if (*(int*) (a0 + 0x70) < -2) {
		return;
	}
	if (*(int*) (a0 + 0x70) < 0) {
		fcn_00549330(a0, *(unsigned short*) g_773da8);
		*(int*) (a0 + 0x70) = 0;
		return;
	}
	if (*(int*) (a0 + 0x70) != 0) {
		return;
	}
	if (fcn_0050d320((int) g_773da8, g_773d75) < 0x4e2000) {
		fcn_004c5150(*(int*) (g_773da8 + 4), -1, g_773d75, 0x4e2000);
	}
	/* pass 1: refill the player's own stock */
	for (i = 0; i < 0x55; i++) {
		slot = (MarktSlot*) (g_85ab90 + g_773d75 * 0x2a90 + i * 0x80);
		if (slot->id == 0) {
			continue;
		}
		memcpy(&rec, slot, 0x80);
		if (slot->f4 == 0) {
			continue;
		}
		kind = *(unsigned char*) (lpObjektePROT + slot->id * 0x41);
		if (kind != 0x25 && kind != 0x17) {
			continue;
		}
		ent = fcn_00503d10(rec.id);
		if (ent == 0) {
			fcn_64d41a(scratch, "Could not find markt-lager:%s",
			    *(char**) (0x14a79c0 + rec.id * 8));
			continue;
		}
		q = (char*) fcn_00502cd0(*(int*) (ent + 0x14), 2, 6, 0,
		    rec.id);
		if (q != 0) {
			ub.n = gm_GetMsgField(ent, q);
		} else {
			ub.n = 0;
		}
		gm_RandomMod(10);
		d = (double) v * g_665dd0;
		uf.f = (float) (rec.f34 * g_665ec8 * d);
		up.n = gm_RandomMod(100) & 0xffff;
		uf.f = (up.n + g_665ea0) * uf.f * g_662910;
		if (uf.f != g_6628a8) {
			if (g_6628a0 > uf.f) {
				uf.f = 1.0f;
			}
		}
		if (ub.n < rec.f34 * g_662908) {
			rec.f10 = (int) (rec.f10 + uf.f);
			if (rec.f20 * g_662908 < rec.f24) {
				fcn_004c51f0(*(int*) (ent + 2), -1,
				    rec.id, (int) uf.f, g_773d75, 0);
				rec.f24 = rec.f34 * g_665ec8 * d * g_662948 + rec.f24;
			}
		} else if (ub.n > rec.f34 * g_6640f8) {
			uf.f = (float) (rec.f34 * g_665ec8 * d);
			rec.f24 = rec.f24 - uf.f * g_662d34;
			if (rec.f20 * g_662ad8 > rec.f24) {
				rec.f24 = rec.f20 * g_662ad8;
			}
			if (g_6628a0 > rec.f24) {
				rec.f24 = 1.0f;
			}
		}
		if (rec.f20 * g_662acc < rec.f24) {
			if (rec.f20 * g_662acc / rec.f24 < gm_RandomFloat01()) {
				rec.f24 = rec.f20 * g_6628d8;
			}
		} else if (rec.f20 * g_6628d8 > rec.f24) {
			if (rec.f24 / (rec.f20 * g_6628d8) < gm_RandomFloat01()) {
				rec.f24 = rec.f20 * g_662acc;
			}
		}
		if ((unsigned short) gm_RandomMod(100) > 0xa || g_7f4c00.b == 0xc) {
			rec.f38 = fcn_005025a0(g_773d75, i);
		}
		fcn_004c61d0(&rec, g_773d75);
	}
	/* pass 2: price the slots the player does not hold */
	for (i = 0; i < 0x55; i++) {
		slot = (MarktSlot*) (g_85ab90 + g_773d75 * 0x2a90 + i * 0x80);
		if (slot->id == 0) {
			continue;
		}
		if (slot->f4 == 0) {
			continue;
		}
		kind = *(unsigned char*) (lpObjektePROT + slot->id * 0x41);
		if (kind == 0x25 || kind == 0x17) {
			continue;
		}
		memcpy(&rec, slot, 0x80);
		ent = fcn_00503d10(rec.id);
		if (ent == 0) {
			continue;
		}
		q = (char*) fcn_00502cd0(*(int*) (ent + 0x14), 1, 0,
		    rec.id);
		if (q != 0) {
			up.n = gm_GetMsgField(ent, q);
		} else {
			up.n = 0;
		}
		gm_RandomMod(10);
		g = (float) (rec.f20 * g_665ec8 * ((double) v * g_665dd0));
		if (g != g_6628a8) {
			rec.f2c = rec.f2c + g;
		}
		if (rec.f2c < g_6628a0) {
			t = 0;
		} else {
			t = (int) rec.f2c;
			rec.f2c = rec.f2c - (float) t;
		}
		if (up.n != t) {
			t = up.n;
		}
		if (up.n < t) {
			t = up.n;
		}
		if (t != 0) {
			rec.f14 = rec.f14 + t;
			rec.f24 = rec.f24 - g * g_662d34;
			if (rec.f24 < g_6629c8) {
				rec.f24 = 1.0f;
			}
			up.n = (int) (t * g_664468);
			if (up.n < 1) {
				up.n = 1;
			}
			if (g_7747b0 < 0x80) {
				fcn_004c51f0(-1, *(int*) (ent + 2),
				    rec.id, up.n, g_773d75, 0);
			}
		} else {
			rec.f24 = rec.f24 + g * g_662948;
			if (gm_RandomFloat01() < g_662ad8) {
				t = (gm_RandomMod(3) & 0xffff) + 1;
				fcn_004c51f0(*(int*) (ent + 2), -1,
				    rec.id, t, g_773d75, 0);
				rec.f24 = g * g_662d34 + rec.f24;
			}
		}
		if (rec.f20 * g_662930 < rec.f24) {
			rec.f24 = rec.f20 * g_662930;
		}
		if (rec.f20 * g_662acc < rec.f24) {
			if (rec.f20 * g_662acc / rec.f24 < gm_RandomFloat01()) {
				if ((float) t < rec.f20 * g_662908) {
					rec.f24 = rec.f20 * g_6628d8;
				} else {
					rec.f24 = rec.f20 * g_662948;
				}
			}
		} else if (rec.f20 * g_6628d8 > rec.f24) {
			if (rec.f24 / (rec.f20 * g_6628d8) < gm_RandomFloat01()) {
				if (t == 0) {
					rec.f24 = rec.f20 * g_662acc;
				} else {
					rec.f24 = rec.f20 * g_664198;
				}
			}
		}
		if ((unsigned short) gm_RandomMod(100) > 0xa || g_7f4c00.b == 0xc) {
			rec.f38 = fcn_005025a0(g_773d75, i);
		}
		fcn_004c61d0(&rec, g_773d75);
	}
	/* pass 3: the three trade lagers next to each market hall */
	i = 1;
	lager = (char*) 0x85d620;
	bar = (char*) 0x868354;
	do {
		if (*bar == 0) {
			break;
		}
		q = fcn_00503e50(i);
		if (q == 0) {
			goto next_lager;
		}
		ent = (char*) fcn_00502cd0(*(int*) (q + 0x5d), 2, 0x1db, 0, 6);
		if (ent == 0) {
			goto next_lager;
		}
		pat = lager;
		for (t = 0; t < 0x55; t++, pat += 0x80) {
			memcpy(&rec, pat, 0x80);
			if (rec.id == 0) {
				continue;
			}
			q = (char*) fcn_00502cd0(*(int*) (ent + 0x14), 1, 0,
			    rec.id);
			if (q == 0) {
				continue;
			}
			ub.n = gm_GetMsgField(ent, q);
			uf.n = ub.n;
			g = (float) (rec.f20 * g_665ec8 * ((double) v * g_665dd0));
			rec.f2c = rec.f2c + g;
			if (rec.f2c < g_6628a0) {
				up.n = 0;
			} else {
				up.n = (int) rec.f2c;
				rec.f2c = rec.f2c - (float) up.n;
			}
			if (ub.n != 0) {
				if (up.n < ub.n) {
					ub.n = up.n;
				}
				if (ub.n < 1) {
					ub.n = 1;
				}
				fcn_004c51f0(-1, *(int*) (ent + 2),
				    rec.id, ub.n, g_773d75, 0);
			}
			if (ub.n < g) {
				rec.f24 = rec.f24 + (g - ub.n) * g_662b20;
				if (rec.f20 * g_662930 < rec.f24) {
					rec.f24 = rec.f20 * g_662930;
				}
			} else {
				rec.f24 = rec.f24 - g * g_662908;
				if (rec.f20 * g_662ad8 > rec.f24) {
					rec.f24 = rec.f20 * g_662ad8;
				}
				if (g_6628a0 > rec.f24) {
					rec.f24 = 1.0f;
				}
			}
			if (rec.f20 * g_6629b0 < rec.f24) {
				if (rec.f20 * g_6629b0 / rec.f24 < gm_RandomFloat01()) {
					rec.f24 = rec.f20 * g_662948;
				}
			} else if (rec.f20 * g_662948 > rec.f24) {
				if (rec.f24 / (rec.f20 * g_662948) < gm_RandomFloat01()) {
					rec.f24 = rec.f20 * g_6629b0;
				}
			}
			if ((unsigned short) gm_RandomMod(100) > 0x4b) {
				rec.f38 = fcn_005025a0(i, t * 0x80);
			}
			fcn_004c61d0(&rec, i);
		}
		pat = lager;
		for (t = 0; t < 0x55; t++, pat += 0x80) {
			memcpy(scratch, pat, 0x80);
			if (((MarktSlot*) scratch)->id == 0) {
				continue;
			}
			q = (char*) fcn_00502cd0(*(int*) (ent + 0x14), 1, 0,
			    ((MarktSlot*) scratch)->id);
			if (q == 0) {
				continue;
			}
			g = (float) (((MarktSlot*) scratch)->f20 * g_665ec8
			    * ((double) v * g_665dd0));
			uf.n = gm_RandomMod(3) & 0xffff;
			uf.f = (float) uf.n + g;
			if (uf.f < g_6628a0) {
				uf.f = 1.0f;
			}
			ub.n = gm_eval_SlotVoll(ent,
			    ((MarktSlot*) scratch)->id, (int) uf.f);
			uf.f = (float) ub.n;
			up.n = gm_GetMsgField(ent, q);
			if (up.n > ((MarktSlot*) scratch)->f20 * g_662908) {
				fcn_004c51f0(*(int*) (ent + 2), -1,
				    ((MarktSlot*) scratch)->id,
				    (int) uf.f, g_773d75, 0);
				((MarktSlot*) scratch)->f24 = g * g_662908
				    + ((MarktSlot*) scratch)->f24;
				if (((MarktSlot*) scratch)->f20 * g_662930
				    < ((MarktSlot*) scratch)->f24) {
					((MarktSlot*) scratch)->f24 =
					    ((MarktSlot*) scratch)->f20 * g_662930;
				}
			} else {
				((MarktSlot*) scratch)->f24 =
				    ((MarktSlot*) scratch)->f24 - g * g_6629f8;
				if (((MarktSlot*) scratch)->f20 * g_662ad8
				    > ((MarktSlot*) scratch)->f24) {
					((MarktSlot*) scratch)->f24 =
					    ((MarktSlot*) scratch)->f20 * g_662ad8;
				}
				if (g_6628a0 > ((MarktSlot*) scratch)->f24) {
					((MarktSlot*) scratch)->f24 = 1.0f;
				}
			}
			if ((unsigned short) gm_RandomMod(100) > 0x4b) {
				((MarktSlot*) scratch)->f38 = fcn_005025a0(i, t);
			}
			fcn_004c61d0((MarktSlot*) scratch, i);
		}
next_lager:
		i++;
		bar += 0x2f4;
		lager += 0x2a90;
	} while (bar < (char*) 0x868c30);
	if (g_7f4c00.b >= 0x16) {
		fcn_00546190(a0);
		return;
	}
	*(pos14m*) (a0 + 0x52) = g_7f4c00;
	fcn_00500bb0(a0 + 0x52, 1, 0, 0);
	*(int*) (a0 + 0x70) = 0;
}
