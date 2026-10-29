/* AI: a master decides to recruit thieves (Gesetze/slavery economy screen logic).
 * Faithful body: first find a live "Meister" handle, run the masters' house
 * accounting, then choose a target house and decide between spy/lure/break-in
 * messages, ending with a packet build + wsprintf text send. */

#include <string.h>

typedef struct GOLDTL_Msg481 {
	int f0;                         /* 0x00 */
	unsigned char f4;               /* 0x04 */
	char pad5[3];
	int f8;                         /* 0x08 */
	int fc;                         /* 0x0c */
	char pad10[0x18];
	int f28;                        /* 0x28 */
	int f2c;                        /* 0x2c */
	int f30;                        /* 0x30 */
	unsigned short f34;             /* 0x34 */
	unsigned char f36;              /* 0x36 */
	char pad37[0x21];
	int f38[8];                     /* 0x38 */
	int f58;                        /* 0x58 */
	int f5c;                        /* 0x5c */
	int f60;                        /* 0x60 */
	char pad64[0x1c];
	int f80;                        /* 0x80 */
	char pad84[0x74];
} GOLDTL_Msg481;                        /* SIZE 0xf8 */

extern char g_7f4ca0[];
extern unsigned short g_7f4c04;
extern int g_7f4c00;
extern int g_7f4c08;
extern unsigned char* lpGebaeudePROT;
extern char* lpObjektePROT;
extern char* lpGebaeudeINST;
extern unsigned char g_99ef80[];
extern int g_100dc20;
extern int g_100dc38;
extern int g_100dc34;
extern int g_100dc24;
extern char* g_100df20;
extern char* g_100b0c0;
extern int g_100b0a8;
extern int g_100b0ac;
extern short* g_773da8;
extern int g_7747b4;

int __cdecl fcn_00502cd0(int, int, int, int, int);
int __cdecl gm_NextEntityQueryMatch(void);
int __cdecl gm_ResolveEntityById(int, int*, int, int);
void __cdecl fcn_00485650(int, int);
void __cdecl fcn_00486c40(int, int, int);
void __cdecl fcn_00489010(int, int);
void __cdecl ai_MeisterCollectTrans(int);
void __cdecl ai_MeisterTrade(int, int);
void __cdecl fcn_00487000(int);
void __cdecl fcn_00487970(int, int, int);
void __cdecl fcn_00487c00(int, int, int);
void __cdecl fcn_00487470(int);
void __cdecl fcn_004888a0(int);
void __cdecl fcn_00488c00(int);
void __cdecl ai_CalcAngriff(int, int);
int __cdecl gm_SearchTable67(int);
int __cdecl fcn_004fa6f0(int, int*, int*);
int __cdecl fcn_0050c4e0(unsigned char*);
int __cdecl fcn_0050d0c0(unsigned char*, int);
int __cdecl gm_AccumulateTyped2(int);
int __cdecl gm_CheckEntityType(unsigned char*);
int __cdecl fcn_0055c050(unsigned char*);
void __cdecl fcn_004c5530(GOLDTL_Msg481*);
int __cdecl fcn_005463a0(int, int, int, int, int);
unsigned char* __cdecl he_fn_Handlung(void);
unsigned short __cdecl gm_RandomMod(int);
float __cdecl gm_RandomFloat01(void);
int __cdecl wsprintfA(char*, const char*, ...);

/* ADDRESS: GOLDTL 0x004813b0 */
void __cdecl ai_CalcMeisterDiebe(unsigned char* rec)
{
	GOLDTL_Msg481 msg;
	char text[0x400];
	int found;
	int saved;
	int handle;
	int iter;
	int i;
	int j;
	int total;
	int match;
	int sel;
	int cx;
	int cy;
	int best;
	int best_score;
	int factor;
	int maxfactor;
	unsigned char* e;
	unsigned char* best_e;
	unsigned char* hsel;
	unsigned char* node;
	char* owner;
	unsigned char type;
	int bVar;

	handle = 0;
	saved = 0;
	best_e = 0;
	factor = 0;
	best_score = 0;
	maxfactor = 0;
	best = 0;
	cx = 0;
	cy = 0;

	hsel = (unsigned char*) *(int*) (rec + 0x16c);
	found = fcn_00502cd0(*(int*) (hsel + 0x5d), 2, 6, 0, 0x116);
	do {
		if (found == 0) {
			saved = handle;
			if (handle == 0) {
				goto common;
			}
			break;
		}
		iter = gm_ResolveEntityById(0, (int*) &msg, 0, *(int*) (found + 6));
		if (iter != 0
		    && *(char*) (lpObjektePROT + (unsigned int) (unsigned short) msg.f0 * 0x41) == 2) {
			handle = found;
		}
		found = gm_NextEntityQueryMatch();
	} while (handle == 0);
	g_100b0ac = 0;
	g_100b0a8 = 0;
	saved = handle;
	fcn_00485650((int) rec, handle);
	hsel = (unsigned char*) *(int*) (rec + 0x16c);
	fcn_00486c40((int) rec, handle, *(int*) (hsel + 0x39));
	fcn_00489010((int) rec, handle);
	i = g_100b0a8;
	if (g_100dc20 == *(int*) (rec + 0x16c) && g_100dc38 < 4) {
		e = (unsigned char*) g_100b0c0;
		j = 0;
		do {
			if (i <= j) {
				break;
			}
			{
				int* dst = (int*) (g_100df20 + g_100dc38 * 0x40);
				int* src = (int*) e;
				int k;
				for (k = 0; k < 0x10; k++) {
					dst[k] = src[k];
				}
			}
			g_100dc38 = g_100dc38 + 1;
			j = j + 1;
			e = e + 0x40;
		} while (g_100dc38 < 4);
		handle = saved;
	}
	ai_MeisterCollectTrans((int) rec);
	ai_MeisterTrade((int) rec, handle);
common:
	fcn_00487000((int) rec);
	fcn_00487970(handle, (int) rec, 10);
	fcn_00487c00(handle, (int) rec, 10);
	fcn_00487470((int) rec);
	found = fcn_00502cd0(*(int*) (*(int*) (rec + 0x16c) + 0x5d), 2, 6, 0, 0x60);
	if (found != 0) {
		fcn_004888a0((int) rec);
	}
	fcn_00488c00((int) rec);
	if ((unsigned short) g_7f4c04 < 7
	    || (*(int*) (rec + 4) + ((unsigned int) g_7f4c04 & 0xffff)) % 3 != 0) {
		*(unsigned int*) (rec + 0x1b4) = *(unsigned int*) (rec + 0x1b4) & 0xffffffdf;
		return;
	}
	if ((*(unsigned int*) (rec + 0x1b4) & 0x20) != 0) {
		return;
	}
	total = 0;
	match = 0;
	*(unsigned int*) (rec + 0x1b4) = *(unsigned int*) (rec + 0x1b4) | 0x20;
	e = (unsigned char*) g_7f4ca0;
	do {
		if (e[8] != 0 && *(unsigned short*) e != 0xffff && e[2] != 0x0a
		    && *(int*) (e + 0x16c) == *(int*) (rec + 0x16c)
		    && e[0x165] != 0
		    && (node = (unsigned char*) *(int*) (e + 0x184)) != 0
		    && *(int*) (node + 0x2c) == *(int*) (*(int*) (e + 0x16c) + 1)
		    && (total = total + 1, *(int*) (e + 0x17c) == 0)) {
			match = match + 1;
		}
		e = e + 0x21c;
	} while ((int) e < 0x85a0a0);
	if (g_100dc20 == *(int*) (rec + 0x16c)) {
		g_100dc34 = match;
		if (*(int*) (rec + 0x1c0) != -1) {
			g_100dc24 = gm_SearchTable67(*(int*) (rec + 0x1c0));
		}
	}
	j = total >> 1;
	if (total - j <= j) {
		j = total - j;
	}
	if (match < j) {
		owner = (char*) (rec + 0x30);
		wsprintfA(text, "ai_CalcMeisterDiebe(): Meister %s hat gerade keine Leute...", owner);
		return;
	}
	hsel = (unsigned char*) *(int*) (rec + 0x16c);
	type = *(unsigned char*) ((unsigned int) (*(unsigned short*) (hsel + 0x27)) * 0x21c + 0x7f4ca2);
	if (type == 6 || type == 7) {
		sel = gm_RandomMod(2);
		if (sel == 0) {
			goto L16d6;
		}
		if (*(int*) (rec + 0x1c0) == -1) {
			goto L16d6;
		}
		if (gm_RandomMod(2) == 0) {
			goto L16d6;
		}
		goto L176c;
	}
	if (gm_RandomFloat01() <= 0.85f || (match < 3 || g_7f4c00 < 7 - g_7747b4)) {
		sel = gm_RandomMod(3);
L16d6:
		if (sel == 1) {
			if (!(gm_RandomFloat01() < 0.95f)) {
				return;
			}
			owner = (char*) (rec + 0x30);
			wsprintfA(text, "ai_CalcMeisterDiebe(): Meister %s m\366chte entf\374hren", owner);
			maxfactor = 0;
			cx = 8;
			cy = 8;
			{
				unsigned char* tbl = g_99ef80;
				int a;
				int b;
				for (a = 0; a < 8; a++) {
					for (b = 0; b < 8; b++) {
						unsigned short lo = *(unsigned short*) (tbl + a * 0xc + b * 0xc0);
						unsigned short hi = *(unsigned short*) (tbl + a * 0xc + b * 0xc0 + 2);
						float f = (float) lo * 0.125f + (float) hi;
						if ((float) maxfactor <= f) {
							maxfactor = (int) f;
						}
					}
				}
			}
			if (maxfactor == 0) {
				maxfactor = 0x3f800000;
			}
			e = 0;
			i = 0x100;
			{
				unsigned char* p = (unsigned char*) lpGebaeudeINST;
				while (i-- != 0) {
					if (*p != 0) {
						int k = gm_GetBuildingTypeCategory(*p);
						unsigned short hid = *(unsigned short*) (p + 0x27);
						unsigned short pid = *(unsigned short*) (hsel + 0x27);
						if (hid != pid && hid != 0xffff && (p[0x5a] & 1) == 0
						    && k != 3 && k != 5 && k != 0) {
							int q = *(int*) ((unsigned int) hid * 0x21c + 0x7f4e0c);
							if ((q == 0 || *(unsigned short*) (q + 0x27) != pid)
							    && *(unsigned char*) ((unsigned int) hid * 0x21c + 0x7f4ca2) < 8) {
								node = (unsigned char*) *(int*) (p + 0x61);
								if (node == 0
								    || fcn_004fa6f0((int) (node + 0x4c), &cx, &cy) == 0) {
									factor = 0;
								} else {
									int off = (cy + cx * 8) * 0x18;
									factor = (int) (1.0f
									                - ((float) *(unsigned short*) (g_99ef80 + off)
									                   * 0.125f
									                   + (float) *(unsigned short*) (g_99ef80 + off + 2))
									                / (float) maxfactor);
								}
								sel = gm_RandomMod(100);
								{
									float f = (float) (sel & 0xffff) * (float) factor * 0.01f;
									if (e != 0) {
										int a = gm_AccumulateTyped2((unsigned int) (*(unsigned short*) (p + 0x27)) * 0x21c + 0x7f4ca0);
										float fa = (float) a * f;
										int b = gm_AccumulateTyped2((unsigned int) (*(unsigned short*) (e + 0x27)) * 0x21c + 0x7f4ca0);
										if (!(fa > (float) b * (float) best_score)) {
											goto L2065;
										}
									}
									e = p;
									best_score = (int) f;
								}
							}
						}
					}
L2065:
					p = p + 0xa9;
				}
			}
			found = fcn_00502cd0(*(int*) (*(int*) (rec + 0x16c) + 0x5d), 1, 0, 0x65, 0);
			if (found != 0 && e != 0 && *(int*) (*(int*) (rec + 0x16c) + 0x65) == -1) {
				found = (int) fcn_005463a0(2, 0, 0x3c, 3, *(int*) (*(int*) (rec + 0x16c) + 1));
				if (found != 0) {
					return;
				}
				owner = (char*) (rec + 0x30);
				wsprintfA(text, "ai_CalcMeisterDiebe(): Meister %s", owner);
				goto packet_61;
			}
			return;
		} else if (sel == 0) {
			goto L176c;
		} else if (sel == 3) {
			goto L1e70;
		} else if (sel < 2) {
			return;
		}
		return;
	}
	{
		unsigned char* p = (unsigned char*) lpGebaeudeINST;
		if (gm_RandomFloat01() > 0.85f && match >= 3 && g_7f4c00 >= 7 - g_7747b4) {
			L1e70:
			ai_CalcAngriff((int) rec, handle);
			goto L2267;
		}
		i = 0x100;
		while (i != 0) {
			if (*p != 0) {
				unsigned char* ent = (unsigned char*) (lpGebaeudePROT + (unsigned int) *p * 0x24d);
				short hid = *(short*) (p + 0x27);
				if (hid != *(short*) (hsel + 0x27) && hid != -1 && (p[0x5a] & 1) == 0
				    && hid != *g_773da8 && gm_CheckEntityType(p) == 0 && *ent != '!'
				    && fcn_0055c050(p) != 0) {
					if (*(int*) (p + 0x61) == 0
					    || fcn_004fa6f0(*(int*) (p + 0x61) + 0x4c, &cx, &cy) == 0) {
						factor = 0;
					} else {
						int off = (cy + cx * 8) * 0x18;
						factor = (int) (1.0f
						                - ((float) *(unsigned short*) (g_99ef80 + off) * 0.125f
						                   + (float) *(unsigned short*) (g_99ef80 + off + 2))
						                / (float) maxfactor);
					}
					j = fcn_0050c4e0(p);
					sel = gm_RandomMod(100);
					{
						float f = (float) (sel & 0xffff) * (8.0f - (float) j) * (float) factor * 0.5f * 0.01f;
						if (best_e != 0) {
							int a = fcn_0050d0c0(p, saved != 0);
							float fa = (float) a * f;
							int b = fcn_0050d0c0(best_e, saved != 0);
							if (!(fa > (float) b * (float) best_score)) {
								goto L1a0c;
							}
						}
						best_e = p;
						best_score = (int) f;
					}
				}
			}
L1a0c:
			p = p + 0xa9;
			i = i - 1;
		}
	}
	owner = (char*) (rec + 0x30);
	if (best_e == 0) {
		*(int*) (rec + 0x1c0) = -1;
		goto L2267;
	}
	*(int*) (rec + 0x1c0) = *(int*) (best_e + 1);
L176c:
	owner = (char*) (rec + 0x30);
	wsprintfA(text, "ai_CalcMeisterDiebe(): Meister %s m\366chte einbrechen", owner);
	if (*(int*) (rec + 0x1c0) != -1) {
		e = (unsigned char*) gm_SearchTable67(*(int*) (rec + 0x1c0));
		if (e == 0) {
			*(int*) (rec + 0x1c0) = -1;
		} else if (*(short*) (e + 0x27) == *(short*) (*(int*) (rec + 0x16c) + 0x27)) {
			*(int*) (rec + 0x1c0) = -1;
		}
	}
	if (*(int*) (rec + 0x1c0) == -1) {
		maxfactor = 0;
		cx = 8;
		cy = 8;
		{
			unsigned char* tbl = g_99ef80;
			int a;
			int b;
			for (a = 0; a < 8; a++) {
				for (b = 0; b < 8; b++) {
					float f = (float) *(unsigned short*) (tbl + a * 0xc + b * 0xc0) * 0.125f
					          + (float) *(unsigned short*) (tbl + a * 0xc + b * 0xc0 + 2);
					if ((float) maxfactor <= f) {
						maxfactor = (int) f;
					}
				}
			}
		}
		if (maxfactor == 0) {
			maxfactor = 0x3f800000;
		}
		best_e = 0;
		best_score = 0;
		{
			unsigned char* p = (unsigned char*) lpGebaeudeINST;
			i = 0x100;
			while (i != 0) {
				if (*p != 0) {
					unsigned char* ent = (unsigned char*) (lpGebaeudePROT + (unsigned int) *p * 0x24d);
					short hid = *(short*) (p + 0x27);
					if (hid != *(short*) (hsel + 0x27) && hid != -1 && (p[0x5a] & 1) == 0
					    && hid != *g_773da8 && gm_CheckEntityType(p) == 0 && *ent != '!'
					    && fcn_0055c050(p) != 0) {
						if (*(int*) (p + 0x61) == 0
						    || fcn_004fa6f0(*(int*) (p + 0x61) + 0x4c, &cx, &cy) == 0) {
							factor = 0;
						} else {
							int off = (cy + cx * 8) * 0x18;
							factor = (int) (1.0f
							                - ((float) *(unsigned short*) (g_99ef80 + off) * 0.125f
							                   + (float) *(unsigned short*) (g_99ef80 + off + 2))
							                / (float) maxfactor);
						}
						j = fcn_0050c4e0(p);
						sel = gm_RandomMod(100);
						{
							float f = (float) (sel & 0xffff) * (8.0f - (float) j) * (float) factor * 0.5f * 0.01f;
							if (best_e != 0) {
								int a = fcn_0050d0c0(p, saved != 0);
								float fa = (float) a * f;
								int b = fcn_0050d0c0(best_e, saved != 0);
								if (!(fa > (float) b * (float) best_score)) {
									goto L1a0c2;
								}
							}
							best_e = p;
							best_score = (int) f;
						}
					}
				}
L1a0c2:
				p = p + 0xa9;
				i = i - 1;
			}
		}
		if (best_e == 0) {
			*(int*) (rec + 0x1c0) = -1;
			goto L2267;
		}
		*(int*) (rec + 0x1c0) = *(int*) (best_e + 1);
	}
	if (best_e != 0) {
		found = fcn_00502cd0(*(int*) (*(int*) (rec + 0x16c) + 0x5d), 1, 0, 0xca, 0);
		while (found != 0) {
			if (*(int*) (found + 0x2a) == *(int*) (best_e + 1)) {
				unsigned char b = *(unsigned char*) (found + 0x37);
				if (b > 0x5e
				    || (sel = gm_RandomMod(0x14),
				        (float) *(unsigned char*) (found + 0x36) * 2.0f
				        + (float) (sel & 0xffff) <= (float) b)) {
					found = (int) fcn_005463a0(2, 0, 0x40, 3, *(int*) (*(int*) (rec + 0x16c) + 1));
					goto L1af1;
				}
				break;
			}
			found = gm_NextEntityQueryMatch();
		}
		found = (int) fcn_005463a0(2, 0, 0x40, 3, *(int*) (*(int*) (rec + 0x16c) + 1));
L1af1:
		while (found != 0) {
			if (*(int*) (found + 0xac) == *(int*) (best_e + 1)) {
				owner = (char*) (rec + 0x30);
				wsprintfA(text, "ai_CalcMeisterDiebe(): Meister %s hat aber noch eine Spionage bei '%s' nicht beendet", owner, (char*) *(int*) (rec + 0x20));
				return;
			}
			found = (int) he_fn_Handlung();
		}
		found = (int) fcn_005463a0(2, 0, 0x3f, 3, *(int*) (*(int*) (rec + 0x16c) + 1));
		while (found != 0) {
			if (*(int*) (found + 0xac) == *(int*) (best_e + 1)) {
				owner = (char*) (rec + 0x30);
				wsprintfA(text, "ai_CalcMeisterDiebe(): Meister %s", owner);
				return;
			}
			found = (int) he_fn_Handlung();
		}
		owner = (char*) (rec + 0x30);
		wsprintfA(text, "ai_CalcMeisterDiebe(): Meister %s", owner);
		goto packet_40;
	}
	goto L2267;

L2267:
	owner = (char*) (rec + 0x30);
	wsprintfA(text, "ai_CalcMeisterDiebe(): Meister %s", owner);
	goto packet_61;
packet_61:
	{
		int n;
		memset(&msg, 0, sizeof msg);
		hsel = (unsigned char*) *(int*) (rec + 0x16c);
		msg.f4 = 0x61;
		msg.f8 = *(int*) ((unsigned int) (*(unsigned short*) (hsel + 0x27)) * 0x21c + 0x7f4ca4);
		msg.fc = *(int*) (hsel + 1);
		msg.f28 = g_7f4c00;
		msg.f2c = (int) g_7f4c04;
		msg.f30 = g_7f4c08;
		msg.f34 = *(unsigned short*) (int) 0x7f4c0c;
		msg.f36 = 1;
		msg.f80 = *(int*) ((unsigned int) (*(unsigned short*) (hsel + 0x27)) * 0x21c + 0x7f4ca4);
		n = handle;
		if (n > 7) {
			n = 8;
		}
		i = 0;
		if (n > 0) {
			unsigned char* p = (unsigned char*) 0x7f4e05;
			do {
				if ((int) p > 0x85a204) {
					break;
				}
				if (*(short*) (p - 0x165) != -1 && *(int*) (p + 7) == *(int*) (hsel)
				    && *p != 0 && *(int*) (p + 0x17) == 0 && *(int*) (p + 0x1f) != 0
				    && *(int*) (*(int*) (p + 0x1f) + 0x2c) == *(int*) (*(int*) (p + 7) + 1)) {
					msg.f38[i] = *(int*) (p - 0x161);
					i = i + 1;
				}
				p = p + 0x21c;
			} while (i < n);
			if (i > 7) {
				goto L237c;
			}
		}
		for (; i < 8; i++) {
			msg.f38[i] = -1;
		}
L237c:
		if (msg.f38[0] != -1) {
			fcn_004c5530(&msg);
		}
		return;
	}
packet_40:
	{
		int n;
		memset(&msg, 0, sizeof msg);
		hsel = (unsigned char*) *(int*) (rec + 0x16c);
		msg.f4 = 0x40;
		msg.f8 = *(int*) ((unsigned int) (*(unsigned short*) (hsel + 0x27)) * 0x21c + 0x7f4ca4);
		msg.fc = *(int*) (hsel + 1);
		msg.f28 = g_7f4c00;
		msg.f2c = (int) g_7f4c04;
		msg.f30 = g_7f4c08;
		msg.f34 = *(unsigned short*) (int) 0x7f4c0c;
		msg.f36 = 1;
		msg.f58 = *(int*) (best_e + 1);
		msg.f5c = *(int*) (hsel + 1);
		n = handle;
		if (n > 7) {
			n = 8;
		}
		i = 0;
		if (n > 0) {
			unsigned char* p = (unsigned char*) 0x7f4e05;
			do {
				if ((int) p > 0x85a204) {
					break;
				}
				if (*(short*) (p - 0x165) != -1 && *(int*) (p + 7) == *(int*) (hsel)
				    && *p != 0 && *(int*) (p + 0x17) == 0 && *(int*) (p + 0x1f) != 0
				    && *(int*) (*(int*) (p + 0x1f) + 0x2c) == *(int*) (*(int*) (p + 7) + 1)) {
					msg.f38[i] = *(int*) (p - 0x161);
					i = i + 1;
				}
				p = p + 0x21c;
			} while (i < n);
			if (i > 7) {
				goto L1e26;
			}
		}
		for (; i < 8; i++) {
			msg.f38[i] = -1;
		}
L1e26:
		fcn_004c5530(&msg);
		return;
	}
}
unsigned char _dpad_99ec10[880];
unsigned char _dpad_99ef80[1552];
