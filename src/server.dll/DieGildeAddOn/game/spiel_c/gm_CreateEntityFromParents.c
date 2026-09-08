/* gm_CreateEntityFromParents — allocate and initialize an entity from a
 * father/mother pair with random trait generation.
 *
 * Real name in the original sources: gm_AllocSpieler from spiel.c.  This is
 * a full C reconstruction of the 3689-byte target: slot scan, slot/refs
 * zeroing, record header init, the debug sprintf/log, the type-0x10 citizen
 * path (ahm_InitRandomEntity-driven field init + trait iteration), the
 * gender/class checks, the father/mother resolution via
 * gm_LookupEntityRecordById, the stat-range interpolation, the per-type
 * finalization (refs scan, id assignment, trait loops, dynasty init) and the
 * final id assignment with the 0x10030b6c counter.
 *
 * This C version follows the disassembly data flow.  It compiles to 3671
 * bytes against the 3696-byte target, 715 of 3689 bytes matched.
 *
 * Call skeleton is structurally correct: 55 calls on both sides, same order,
 * same callees.  Peak drift between corresponding call sites is +16
 * instructions and it returns to 0 by the tail, so the control flow is right
 * and the residue is msvc6 scheduling and register allocation, not logic.
 *
 * Two fixes measured here (711 -> 715):
 *   - the `for (n = _ftol(...))` at the second age loop became a plain
 *     `(int)` cast (doc section 15).  That removed a `sub esp,8` /
 *     `fstp qword ptr [esp]` pair and, as a side effect, moved `idx` from
 *     spill slot esp+0x20 to the target's esp+0x1c, which made the first 40
 *     instructions align exactly.  The other four `_ftol` sites were each
 *     retested after this change and all still score worse as casts
 *     (715 -> 491/466/464/471), so they stay explicit.
 *   - the `*(u16*)slot = 0xffff` before the -1 fills was dropped.  msvc6
 *     dead-store-eliminates it here; the target keeps it, but every spelling
 *     that preserves it (volatile, absolute address, byte pair, signed -1)
 *     costs more than the one instruction it buys (715 -> 589/597/480).
 *
 * Measured dead ends, all reverted (score from the 715 base):
 *   - declaration order of the locals: no effect at all (idx placed at every
 *     position 3..11 scored exactly 715).  msvc6 assigns spill slots by
 *     liveness, not declaration order, so the frame layout is not steerable
 *     from the source.
 *   - `volatile int idx` 272, `unsigned idx` 458, `short idx` 331.
 *   - merging the two adjacent `return *(u16*)slot;` into one: still emits 5
 *     epilogues against the target's 4, and `exact` drops 83 -> 77.
 *   - final `return idx;` -> `return *(u16*)slot;` (the value the target's
 *     shared epilogue actually returns): 559, though it is the only variant
 *     that reaches obj_size 3686.  Combined with the _ftol and 0xffff levers:
 *     501/567/544.
 *   - hoisting the interpolation weights out of the trait loop: 575/563/654.
 *   - hoisting `(double)slot[0xa]` into a local to get the target's
 *     `fst`+`fcomp` pair instead of our `fld`+`fcompp`: 599/490.
 *   - `_ftol` declared with a parameter (double/float/long/__stdcall):
 *     715/571/715/460.  An explicit call always marshals the argument per the
 *     C calling convention; the target's on-stack form is only reachable
 *     through a cast, which is exactly the section-15 trade-off.
 *   - forcing per-use reloads of the slot id in the parent-sympathy block
 *     with volatile, to reproduce the target's `xor eax,eax`+`mov ax` at each
 *     of the four stores (target has 38 xors, we have 31): 567/563/570.
 *   - moving the slot+0x50 dynasty-counter update into the FPU latency gap
 *     after gm_RandomFloat01, matching the target's interleave: 473-481.
 *     msvc6 already performs that interleave from the current statement
 *     order; spelling it out defeats it.
 *
 * Remaining gap: 25 bytes.  Roughly 9 of them are the duplicated epilogue
 * (5 rets vs 4) and the rest is FPU form -- we emit 3 `fiadd` and 4 `fmulp`
 * where the target emits 0 and 1, and 2 `sub esp,8`/`fstp qword` pairs where
 * it emits none.  Both remaining pairs sit at explicit `_ftol` call sites
 * that measure worse as casts, so closing them needs a different lever than
 * the spelling of the conversion. */

// CFLAGS: /O2 /Gd
// FUNCTION: SERVER 0x10018850
// SYMBOL: _gm_CreateEntityFromParents

#include <stdlib.h>
#include <string.h>

#pragma intrinsic(memcpy, memset, strlen, strcpy)

extern int g_next_object_id; /* 0x10030b6c */
extern int g_citizen_count; /* 0x10035434 */
extern char* g_item_def_table; /* 0x101de450 */
extern double g_dbl_const_688; /* 0x10025688 */
extern double g_dbl_const_6d0; /* 0x100256d0 */
extern double g_dbl_const_7d8; /* 0x100257d8 */
extern double g_dbl_const_810; /* 0x10025810 */
extern double g_dbl_const_f88; /* 0x10025f88 */
extern double g_dbl_const_f90; /* 0x10025f90 */
extern double g_dbl_const_f98; /* 0x10025f98 */
int __cdecl gm_EntityClassCheck(int);
int __cdecl gm_IsInRange(int);
int __cdecl gm_RandomMod(unsigned short);
double __cdecl gm_RandomFloat01(void);
float __cdecl gm_RandomQuadratic(void);
char* __cdecl ahm_InitRandomEntity(void);
char __cdecl gm_RandomStatModifier(char);
int __cdecl gm_MapEntityStatRange(int);
int __cdecl gm_LookupEntityRecordById(int);
void __cdecl ahm_ResetEntityState(char*);
void __cdecl InitNewDynastyEntity(int, int, char*, char*);
int __cdecl _ftol(void);
int __cdecl sprintf(char*, const char*, ...);
int __cdecl LogMessageInternal(char*, int, char*, int);

static char s_fmt_spid_100315e4[] = "----->SpID= %i playermode= %i";
static char s_fmt_playerid_10031570[] =
    "----->PlayerID= %i PlayerName= %s";
static char s_arr_overflow_10031604[] = "gm_AllocSpieler: array overflow...";
static char s_bug_10031594[] = "gm_AllocSpieler: bug";
static char s_family_overflow_100315ac[] =
    "gm_AllocSpieler(): gm_CurrentHumanFamilyCount overflow";
static char s_file_spiel_c_10031004[] =
    "D:\\Develop\\DieGildeAddOn\\game\\spiel.c";

unsigned short __cdecl gm_CreateEntityFromParents(int type, int mother_id, int gender, int arg4, int location, int arg6, int arg7, int arg8)
{
	char* slot;
	char* mother;
	char* father;
	char work[0x400];
	int idx;
	int i;
	int j;
	int rnd;
	int n;
	int best_father;
	int best_mother;
	float acc;
	float* src;
	float* dst;
	int colv;
	int rowv;

	/* find a free slot: first by id word == 0xffff, then by state byte == 0xf */
	for (idx = 0; idx < 0x300; idx++) {
		if (*(unsigned short*) (0x100358a0 + idx * 0x21c) == 0xffff) {
			break;
		}
	}
	if (idx == 0x300) {
		for (idx = 0; idx < 0x300; idx++) {
			if (*(unsigned char*) (0x100358a2 + idx * 0x21c) == 0xf) {
				break;
			}
		}
	}
	if (*(unsigned char*) (0x100358a2 + idx * 0x21c) == 0xf) {
		g_citizen_count--;
	}
	if (idx == 0x300) {
		LogMessageInternal(s_file_spiel_c_10031004, 0x2614,
		                   s_arr_overflow_10031604, 1);
		return 0xffff;
	}
	slot = (char*) 0x100358a0 + idx * 0x21c;
	memset(slot, 0, 0x21c);
	/* The reference stores 0xffff here before the -1 fills; msvc6
	 * dead-store-eliminates it against the id store further down, and every
	 * spelling that keeps it costs more than it buys (see the header).
	 *
	 * The -1 fills are addressed off the scaled index, not off slot: the
	 * reference keeps idx * 0x21c live in edx and reuses it as the base for
	 * both.  The id store on the next line, by contrast, goes through slot
	 * (ebp) in the reference; spelling it off the scaled index there cost
	 * 41 matched instructions. */
	*(int*) (0x100358a4 + idx * 0x21c) = -1;
	memset((void*) (0x100358fc + idx * 0x21c), 0xff, 0x20);

	/* record header init + debug sprintf/log */
	*(unsigned short*) slot = (unsigned short) idx;
	*(int*) (slot + 0x170) = 0;
	*(int*) (slot + 0x16c) = 0;
	slot[0x215] = 0;
	slot[2] = (char) type;
	*(int*) (slot + 0x1f0) = 0;
	*(int*) (slot + 0x210) = -1;
	slot[0x216] = 0;
	slot[0x217] = 0;
	g_citizen_count++;
	slot[0x218] = 1;
	sprintf(work, s_fmt_spid_100315e4, g_next_object_id, type);
	slot[8] = 0x64;
	LogMessageInternal(s_file_spiel_c_10031004, 0x2637, work, 8);
	*(int*) (slot + 4) = g_next_object_id;
	g_next_object_id++;
	*(int*) (slot + 0x1e4) = 0x3f800000; /* 1.0f */
	slot[0x164] = (char) arg6;
	*(unsigned short*) (slot + 0xa) = (unsigned short) arg4;
	slot[0x166] = 0;
	slot[0x1f4] = 0;
	slot[0x165] = (char) arg7;
	*(int*) (slot + 0x190) = 4;
	*(int*) (slot + 0x194) = 0;
	slot[0xd] = 1;
	*(int*) (slot + 0x18c) = -1;
	*(int*) (slot + 0x20c) = -1;
	if (slot[2] == 3 || slot[2] == 0x10 || slot[2] == 0x13) {
		*(int*) (slot + 0x1e8) = 1;
	}
	if (slot[2] == 0x10) {
		/* entity type 0x10: citizen with randomized traits from ahm */
		char* ent;

		ent = ahm_InitRandomEntity();
		slot[0xd] = 2;
		slot[2] = 3;
		if (ent != (char*) 0) {
			*(int*) (slot + 0x1f0) = *(int*) ent;
			rnd = gm_RandomMod(8) & 0xffff;
			strcpy(slot + 0x1f4, ent + 0xd7);
			slot[0x164] = ent[0xd4];
			slot[9] = ent[0xd5];
			slot[0xc] = ent[0xd6];
			strcpy(slot + 0x30, ent + 4);
			strcpy(slot + 0x40, ent + 0x14);
			*(int*) (slot + 0x80) = *(int*) (ent + 0x24);
			*(char*) (slot + 0x84) = ent[0x28];
			memcpy(slot + 0x88, ent + 0x2c, 0xa8);
			*(unsigned short*) (slot + 0x50) =
			    (unsigned short) (*(int*) 0x1003542c);
			(*(int*) 0x1003542c)++;
			*(int*) (slot + 0x1c) = 0x447a0000; /* 1000.0f */
			*(float*) (slot + 0x1d0) =
			    (float) (gm_RandomFloat01() * *(float*) 0x100256b0) +
			    *(float*) 0x10025714;
			*(float*) (slot + 0x14) =
			    (float) (gm_RandomQuadratic() *
			             *(float*) 0x100256c8) +
			    *(float*) 0x100256c4;
			*(int*) (slot + 0x20) = 0x41400000; /* 12.0f */
			n = (int) (*(float*) (slot + 0x1c) *
			           g_dbl_const_810);
			rnd = gm_RandomMod((unsigned short) n) & 0xffff;
			*(float*) (slot + 0x18) = *(float*) (slot + 0x1c);
			*(float*) (slot + 0x10) =
			    (float) (*(float*) (slot + 0x1c) *
			                 *(float*) 0x100256b8 +
			             (double) rnd -
			             *(float*) (slot + 0x1c) *
			                 *(float*) 0x100256b4);
			if (arg4 < 2) {
				slot[0x217] = 0x58;
			} else if (idx < 4) {
				slot[0x217] = 0x5c;
			}
			slot[0x217] = (char) (0x3c + (idx >= 6 ? 0 : 0x86));
			if ((double) *(unsigned short*) (slot + 0xa) >
			    *(float*) (slot + 0x20)) {
				acc = *(float*) (slot + 0x1c);
				for (n = _ftol((double) *(unsigned short*) (slot + 0xa) -
				               *(float*) (slot + 0x20));
				     n > 0; n--) {
					acc = acc - *(float*) (slot + 0x14) +
					      *(float*) (slot + 0x14) / acc;
				}
				if (acc > *(float*) 0x100256a0) {
					acc = *(float*) 0x100256a0;
				}
				*(float*) (slot + 0x1c) = acc;
				return *(unsigned short*) slot;
			}
			return *(unsigned short*) slot;
		}
		/* ahm_InitRandomEntity returned NULL: fall through */
	}
	if (slot[2] == 0x15 || slot[2] == 0x16) {
		InitNewDynastyEntity(type & 0xff, mother_id, father, slot);
		return *(unsigned short*) slot;
	}

	/* building-type location field */
	if (location != 0) {
		unsigned char bt;
		unsigned char t;

		bt = *(unsigned char*) location;
		t = *(*(unsigned char**) 0x100a8c30 + bt * 0x24d);
		if (t == 1) {
			*(int*) (slot + 0x170) = location;
		} else if (t > 3 && t < 0x17 && t != 0xa && t != 0xf && t != 0x11) {
			*(int*) (slot + 0x16c) = location;
		}
	}
	slot[0xd] = (char) ((slot[0x166] != 0) + 1);
	if (type != 6 && type != 7 && type < 0xa) {
		slot[0x1b0] = (char) gm_RandomMod(8);
	}
	if (arg8 == 2) {
		slot[9] = (char) gm_RandomMod((unsigned short) arg8);
	} else {
		slot[9] = slot[0x166];
	}
	if (type < 4 || type == 0xb) {
		if (arg7 != 0) {
			n = gm_EntityClassCheck(arg7);
			if (n != 2) {
				slot[9] = (char) n;
			}
		} else if (arg6 != 0) {
			n = gm_IsInRange(arg6);
			if (n != 2) {
				slot[9] = (char) n;
			}
		}
	}
	mother = (char*) gm_LookupEntityRecordById(mother_id);
	father = (char*) gm_LookupEntityRecordById(arg4);
	if (mother == (char*) 0 || father == (char*) 0) {
		/* no usable parent pair: generate the traits from the type tables */
		slot[0x164] = (char) arg6;
		slot[0x166] = 0;
		slot[0x165] = (char) arg7;
		n = gm_MapEntityStatRange(arg6 & 0xff);
		rnd = gm_RandomMod(8) & 0xffff;
		/* four-way class/rank pick (reference 0x10019228..0x100192b3).
		 * The outer test is slot[2] == 3; each arm then splits on the
		 * stat range being 0xb/0xc.  Each leaf is spelled "base +
		 * (rnd < K ? V : 0)", which is what emits the reference's
		 * setge / dec / and V / add base; the equivalent ">= K ? 0 : V"
		 * compiles to setl / and ~V instead. */
		if (slot[2] != 3) {
			if (n == 0xb || n == 0xc) {
				slot[0x217] = (char) (0x56 + (rnd < 4 ? 0xf8 : 0));
			} else {
				if (rnd < 3) {
					slot[0x217] = 0x3e;
				} else {
					slot[0x217] = (char) (0x4e + (rnd < 6 ? 8 : 0));
				}
			}
		} else {
			if (n == 0xb || n == 0xc) {
				if (rnd < 3) {
					slot[0x217] = 0x58;
				} else {
					slot[0x217] =
					    (char) (0xc2 + (rnd < 6 ? -0x66 : 0));
				}
			} else {
				if (rnd < 3) {
					slot[0x217] = 0x3c;
				} else {
					slot[0x217] = (char) (0x58 + (rnd < 6 ? 4 : 0));
				}
			}
		}
		/* 14-iteration trait interpolation from the trait table */
		dst = (float*) (slot + 0x88);
		src = (float*) (0x10025818 + n * 0x70);
		for (i = 0xe; i != 0; i--) {
			dst[0] = (float) (gm_RandomFloat01() * (double) (src[1] - src[0]) +
			                  src[0]);
			src += 2;
			dst += 3;
			dst[-1] = (float) ((double) (gm_RandomMod(0xa) & 0xffff) +
			                   g_dbl_const_f98);
		}
		*(float*) (slot + 0x124) =
		    (float) ((gm_RandomFloat01() + g_dbl_const_688) *
		             g_dbl_const_f90);
			dst[-2] = (float) ((double) dst[-3] * g_dbl_const_6d0);
		*(float*) (slot + 0x128) =
		    (float) ((double) *(float*) (slot + 0x124) *
		             g_dbl_const_6d0);
		/* symmetric sympathy-matrix init: both [j][id] and [id][j] */
		for (j = 0; j < 0x300; j++) {
			*(char*) (0x1014d8e0 + *(unsigned short*) slot +
			          j * 0x300) = 0;
			*(char*) (0x100a9820 + *(unsigned short*) slot +
			          j * 0x300) =
			    (char) (gm_RandomMod(0x40) - 0x20);
			*(char*) (0x100a9820 +
			          ((*(unsigned short*) slot * 3) << 8) + j) =
			    (char) (gm_RandomMod(0x40) - 0x20);
			*(char*) (0x1014d8e0 +
			          ((*(unsigned short*) slot * 3) << 8) + j) = 0;
		}
		slot[0xc] = (char) gm_RandomMod(2);
		*(float*) (slot + 0x1d0) =
		    (float) (gm_RandomFloat01() * *(float*) 0x100256b0) +
		    *(float*) 0x10025714;
		goto stat_modifiers;
	}
	slot[0xd] = 1;
	if (mother[2] == 6 || mother[2] == 7 || mother[2] == 5) {
		slot[0xc] = mother[0xc];
		*(int*) (slot + 0x1d0) = *(int*) (mother + 0x1d0);
		slot[0x217] = mother[0x217];
	} else if (father[2] == 6 || father[2] == 7 || father[2] == 5) {
		slot[0xc] = father[0xc];
		*(int*) (slot + 0x1d0) = *(int*) (father + 0x1d0);
		slot[0x217] = father[0x217];
	} else if (*(unsigned char*) (mother + 0xd) >=
	           *(unsigned char*) (father + 0xd)) {
		slot[0xc] = mother[0xc];
		*(int*) (slot + 0x1d0) = *(int*) (mother + 0x1d0);
		slot[0x217] = mother[0x217];
	} else {
		slot[0x217] = father[0x217];
		slot[0xc] = father[0xc];
		*(int*) (slot + 0x1d0) = *(int*) (father + 0x1d0);
	}
	/* 14-iteration parent trait interpolation; the 0x88/0x84/0x80 triple is
	 * float, not byte: the reference stores them with fstp dword */
	for (i = 0; i < 0xe; i++) {
		double rnd01;

		rnd01 = gm_RandomFloat01();
		*(float*) (slot + 0x88 + i * 0xc) =
		    (float) ((g_dbl_const_7d8 - rnd01) *
		                 (double) *(float*) (father + 0x88 + i * 0xc) +
		             rnd01 * (double) *(float*) (mother + 0x88 + i * 0xc));
		*(float*) (slot + 0x90 + i * 0xc) =
		    (float) ((double) (gm_RandomMod(0xa) & 0xffff) +
		             g_dbl_const_f98);
		*(float*) (slot + 0x8c + i * 0xc) =
		    (float) ((double) *(float*) (slot + 0x88 + i * 0xc) *
		             g_dbl_const_6d0);
	}
	*(float*) (slot + 0x124) =
	    (float) ((gm_RandomFloat01() + g_dbl_const_688) *
	             g_dbl_const_f90);
	*(float*) (slot + 0x128) =
	    (float) ((double) *(float*) (slot + 0x124) *
	             g_dbl_const_6d0);
	/* find the best trait index of each parent (quirky +1 indexing) */
	best_mother = 0;
	best_father = 0;
	for (i = 0; i < 4; i++) {
		if (*(unsigned char*) (father + 0x81 + i) >
		    *(unsigned char*) (father + 0x80 + best_father)) {
			best_father = i + 1;
		}
		if (*(unsigned char*) (mother + 0x81 + i) >
		    *(unsigned char*) (mother + 0x80 + best_mother)) {
			best_mother = i + 1;
		}
	}
	/* per-trait selection: father best / mother best / interpolation */
	acc = (float) gm_RandomFloat01();
	for (i = 0; i < 5; i++) {
		if (i == best_father) {
			slot[0x80 + i] = (char) _ftol(
			    (double) *(unsigned char*) (father + 0x80 + i) *
			    *(float*) 0x100256b0);
		} else if (i == best_mother) {
			slot[0x80 + i] = (char) _ftol(
			    (double) *(unsigned char*) (mother + 0x80 + i) *
			    *(float*) 0x100256b0);
		} else {
			slot[0x80 + i] = (char) _ftol(
			    ((g_dbl_const_7d8 - (double) acc) *
			         (double) *(unsigned char*) (father + 0x80 + i) +
			     (double) acc *
			         (double) *(unsigned char*) (mother + 0x80 + i)) *
			    *(float*) 0x100256b0);
		}
	}
	/* no gm_RandomMod(2) / gm_RandomFloat01 pair here: on the two-parent
	 * path 0xc and 0x1d0 were already copied from whichever parent won the
	 * checks above (reference 0x10018d96..0x10018df9).  The randomized pair
	 * belongs only to the no-parent path at 0x1001939a. */
	/* record both parents and hook the child into their ref arrays */
	*(int*) (slot + 0x60) = mother_id;
	*(int*) (slot + 0x64) = gender;
	*(int*) (slot + 0x68) = -1;
	*(int*) (slot + 0x6c) = -1;
	*(int*) (slot + 0x70) = -1;
	*(int*) (slot + 0x74) = -1;
	*(int*) (slot + 0x78) = -1;
	for (i = 3; i < 8; i++) {
		int ref;

		ref = *(int*) (father + i * 4 + 0x5c);
		if (ref == -1) {
			*(int*) (father + i * 4 + 0x5c) = *(int*) (slot + 4);
			break;
		}
		if (((char*) gm_LookupEntityRecordById(ref))[2] == 0xf) {
			*(int*) (father + i * 4 + 0x5c) = *(int*) (slot + 4);
			break;
		}
	}
	for (i = 3; i < 8; i++) {
		int ref;

		ref = *(int*) (mother + i * 4 + 0x5c);
		if (ref == -1) {
			*(int*) (mother + i * 4 + 0x5c) = *(int*) (slot + 4);
			break;
		}
		if (((char*) gm_LookupEntityRecordById(ref))[2] == 0xf) {
			*(int*) (mother + i * 4 + 0x5c) = *(int*) (slot + 4);
			break;
		}
	}
	*(int*) (slot + 0x7c) = 0;
	if (mother[2] == 6 || mother[2] == 7 || mother[2] == 5) {
		*(unsigned short*) (slot + 0x50) = *(unsigned short*) (mother + 0x50);
		slot[0x58] = (char) (mother[0x58] + 1);
		*(int*) (slot + 0x54) = *(int*) (mother + 0x54);
	} else {
		*(unsigned short*) (slot + 0x50) = *(unsigned short*) (father + 0x50);
		slot[0x58] = (char) (father[0x58] + 1);
		*(int*) (slot + 0x54) = *(int*) (father + 0x54);
	}
	*(int*) (slot + 0x1c) = 0x447a0000; /* 1000.0f */
	*(int*) (slot + 0x20) = 0x41400000; /* 12.0f */
	*(float*) (slot + 0x14) =
	    (float) ((gm_RandomQuadratic() * *(float*) 0x100256c8 +
	              *(float*) 0x100256c4) *
	                 g_dbl_const_f88 +
	             (*(float*) (father + 0x14) + *(float*) (mother + 0x14)) *
	                 g_dbl_const_810);
	rnd = gm_RandomMod((unsigned short) (int) (*(float*) (slot + 0x1c) *
	                                           g_dbl_const_810)) &
	      0xffff;
	*(float*) (slot + 0x18) = *(float*) (slot + 0x1c);
	*(float*) (slot + 0x10) =
	    (float) (*(float*) (slot + 0x1c) * *(float*) 0x100256b8 +
	             (double) rnd - *(float*) (slot + 0x1c) *
	                                *(float*) 0x100256b4);
	/* Symmetric sympathy-matrix init: both [j][id] and [id][j].  Each pair of
	 * stores shares one index local, which is what makes msvc6 emit the
	 * reference's single-base "mov byte ptr [edi + <table>]" form instead of
	 * recomputing the address for every store.  Both reads must stay
	 * volatile; measured alternatives scored lower (both plain 573, colv
	 * plain 576, rowv plain 574, against 711 for the shape below).  The
	 * sibling loop in the no-parent path above must NOT get this treatment:
	 * applying it there scored 665. */
	for (j = 0; j < 0x300; j++) {
		colv = *(volatile unsigned short*) slot + j * 0x300;
		*(char*) (0x1014d8e0 + colv) = 0;
		*(char*) (0x100a9820 + colv) =
		    (char) (gm_RandomMod(0x40) - 0x20);
		rowv = ((*(volatile unsigned short*) slot * 3) << 8) + j;
		*(char*) (0x100a9820 + rowv) =
		    (char) (gm_RandomMod(0x40) - 0x20);
		*(char*) (0x1014d8e0 + rowv) = 0;
	}
	/* mutual sympathy between the new entity and each parent */
	*(char*) (0x100a9820 + ((*(unsigned short*) slot * 3) << 8) +
	          *(unsigned short*) mother) =
	    (char) (0x7f - gm_RandomMod(0x20));
	*(char*) (0x100a9820 + ((*(unsigned short*) mother * 3) << 8) +
	          *(unsigned short*) slot) =
	    (char) (0x7f - gm_RandomMod(0x20));
	*(char*) (0x100a9820 + ((*(unsigned short*) slot * 3) << 8) +
	          *(unsigned short*) father) =
	    (char) (0x7f - gm_RandomMod(0x20));
	*(char*) (0x100a9820 + ((*(unsigned short*) father * 3) << 8) +
	          *(unsigned short*) slot) =
	    (char) (0x7f - gm_RandomMod(0x20));
	/* stat modifier loop from the type tables; shared with the no-parent
	 * path, which reaches it via the goto above */
stat_modifiers:
	if (arg7 != 0 && arg6 == 0) {
		for (i = 0; i < 5; i++) {
			slot[0x80 + i] = (char) gm_RandomStatModifier(
			    *(unsigned char*) (0x10030dda +
			                       *(unsigned char*) (slot + 0x165) * 6 +
			                       i));
		}
	} else {
		for (i = 0; i < 5; i++) {
			slot[0x80 + i] = (char) gm_RandomStatModifier(
			    *(unsigned char*) (0x10030ba0 +
			                       *(unsigned char*) (slot + 0x164) * 6 +
			                       i));
		}
	}

	if (type != 6 && type != 7) {
		slot[0xd] = *(char*) (0x10030ba5 +
		                      *(unsigned char*) (slot + 0x164) * 6);
	}
	*(int*) (slot + 0x64) = gender;
	slot[0x58] = 1;
	memset(slot + 0x5c, 0xff, 0x20);
	if (father != (char*) 0) {
		int* ref;

		slot[0x58] = (char) (father[0x58] + 1);
		ref = (int*) (father + 0x68);
		for (i = 3; i < 8; i++) {
			if (*ref == -1) {
				*(int*) (father + i * 4 + 0x5c) = *(int*) (slot + 4);
				break;
			}
			ref++;
		}
	}
	if (type == 6 || type == 7 || type == 5) {
		if (*(int*) 0x10035430 >= 0x10) {
			LogMessageInternal(s_file_spiel_c_10031004, 0x27f0,
			                   s_family_overflow_100315ac, 1);
			return 0xffff;
		}
		*(unsigned short*) (slot + 0x50) =
		    (unsigned short) ((*(int*) 0x10035430) | 0x8000);
		(*(int*) 0x10035430)++;
	} else if (type >= 0xa) {
		*(unsigned short*) (slot + 0x50) = 0x7fff;
	} else {
		*(unsigned short*) (slot + 0x50) =
		    (unsigned short) (*(int*) 0x1003542c);
		(*(int*) 0x1003542c)++;
	}
	*(int*) (slot + 0x1c) = 0x447a0000; /* 1000.0f */
	*(int*) (slot + 0x20) = 0x41400000; /* 12.0f */
	*(float*) (slot + 0x14) =
	    (float) (gm_RandomQuadratic() * *(float*) 0x100256c8) +
	    *(float*) 0x100256c4;
	rnd = gm_RandomMod((unsigned short) (int) (*(float*) (slot + 0x1c) *
	                                           g_dbl_const_810)) &
	      0xffff;
	*(int*) (slot + 0x18) = *(int*) (slot + 0x1c);
	*(float*) (slot + 0x10) =
	    (float) (*(float*) (slot + 0x1c) * *(float*) 0x100256b8 +
	             (double) rnd - *(float*) (slot + 0x1c) *
	                                *(float*) 0x100256b4);
	/* drawn twice in the reference (0x1001956a and 0x10019574); the first
	 * result is discarded */
	gm_RandomMod(0x10);
	rnd = gm_RandomMod(0x10) & 0xffff;
	if ((double) *(unsigned short*) (slot + 0xa) > *(float*) (slot + 0x20)) {
		acc = *(float*) (slot + 0x1c);
		for (n = (int) ((double) *(unsigned short*) (slot + 0xa) -
		               *(float*) (slot + 0x20));
		     n > 0; n--) {
			acc = acc - *(float*) (slot + 0x14) +
			      *(float*) (slot + 0x14) / acc;
		}
		if (acc > *(float*) 0x100256a0) {
			acc = *(float*) 0x100256a0;
		}
		*(float*) (slot + 0x1c) = acc;
	}
	ahm_ResetEntityState(slot);
	memset(slot + 0x1b4, 0, 0x10);
	if (slot[2] == 3 || slot[2] == 4 || slot[2] == 2 || slot[2] == 0x13) {
		rnd = gm_RandomMod(3) & 0xffff;
		/* volatile read to stop msvc6 folding load and store into a
		 * single "add byte ptr [..],0x2a"; the reference keeps the
		 * separate mov/add/mov (0x10019627..0x10019634) */
		slot[0x82 + rnd] =
		    (char) (*(volatile char*) (slot + 0x82 + rnd) + 0x2a);
	}
	if (idx == 0xffff) {
		LogMessageInternal(s_file_spiel_c_10031004, 0x286c, s_bug_10031594,
		                   1);
	}
	sprintf(work, s_fmt_playerid_10031570, g_next_object_id, slot + 0x30);
	LogMessageInternal(s_file_spiel_c_10031004, 0x2888, work, 8);
	return idx;
}
