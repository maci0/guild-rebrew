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
 * The original was byte-EXACT via naked _emit; this C version follows the
 * disassembly's data flow and is expected to stay NEAR_MATCHING at the
 * instruction level (msvc6 register allocation / FPU scheduling differs). */

// CFLAGS: /O2 /Gd
// FUNCTION: SERVER 0x10018850
// SYMBOL: _gm_CreateEntityFromParents

#include <stdlib.h>
#include <string.h>

#pragma intrinsic(memcpy, memset, strlen, strcpy)

extern int g_next_object_id; /* 0x10030b6c */
extern char* g_entity_table; /* 0x101de450 */
int __cdecl gm_EntityClassCheck(int);
int __cdecl gm_IsInRange(int);
int __cdecl gm_RandomMod(unsigned short);
double __cdecl gm_RandomFloat01(void);
int __cdecl gm_RandomQuadratic(int);
char* __cdecl ahm_InitRandomEntity(void);
int __cdecl gm_RandomStatModifier(int);
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

int __cdecl gm_CreateEntityFromParents(int type, int mother_id, int gender, int arg4, int location, int arg6, int arg7, int arg8)
{
	char* slot;
	char* father;
	char* mother;
	char work[0x400];
	int idx;
	int i;
	int j;
	int rnd;
	int n;
	int best_father;
	int best_mother;
	float acc;

	/* find a free slot: first by id word == 0xffff, then by state byte == 0xf */
	idx = 0;
	for (i = 0; i < 0x300; i++) {
		if (*(unsigned short*) (0x100358a0 + i * 0x21c) == 0xffff) {
			break;
		}
	}
	if (i == 0x300) {
		for (i = 0; i < 0x300; i++) {
			if (*(unsigned char*) (0x100358a2 + i * 0x21c) == 0xf) {
				break;
			}
		}
	}
	idx = i;
	if (*(unsigned char*) (0x100358a2 + idx * 0x21c) == 0xf) {
		(*(int*) 0x10035434)--;
	}
	if (idx == 0x300) {
		LogMessageInternal(s_file_spiel_c_10031004, 0x2614,
		                   s_arr_overflow_10031604, 1);
		return 0;
	}
	slot = (char*) 0x100358a0 + idx * 0x21c;
	memset(slot, 0, 0x21c);
	*(unsigned short*) slot = 0xffff;
	*(int*) (slot + 4) = -1;
	memset(slot + 0x5c, 0xff, 0x20);

	/* record header init + debug sprintf/log */
	*(unsigned short*) slot = (unsigned short) idx;
	slot[2] = (char) type;
	*(int*) (slot + 0x170) = 0;
	*(int*) (slot + 0x16c) = 0;
	*(int*) (slot + 0x1f0) = 0;
	*(int*) (slot + 0x210) = -1;
	slot[0x215] = 0;
	(*(int*) 0x10035434)++;
	sprintf(work, s_fmt_spid_100315e4, g_next_object_id, type);
	LogMessageInternal(s_file_spiel_c_10031004, 0x2637, work, 1);
	slot[0x216] = 0;
	slot[0x217] = 0;
	slot[0x218] = 1;
	*(int*) (slot + 4) = g_next_object_id;
	g_next_object_id++;
	*(int*) (slot + 0x1e4) = 0x3f800000; /* 1.0f */
	slot[0x164] = (char) arg6;
	slot[8] = 0x64;
	*(unsigned short*) (slot + 0xa) = (unsigned short) arg4;
	slot[0x166] = 0;
	slot[0x165] = (char) arg7;
	slot[0x1f4] = 0;
	*(int*) (slot + 0x190) = 4;
	*(int*) (slot + 0x194) = 0;
	slot[0xd] = 1;
	*(int*) (slot + 0x18c) = -1;
	*(int*) (slot + 0x20c) = -1;
	if (slot[2] == 0x10 || slot[2] == 0x13) {
		*(int*) (slot + 0x1e8) = 1;
		slot[0xd] = 2;
	}
	if (slot[2] == 0x10) {
		/* entity type 0x10: citizen with randomized traits from ahm */
		char* ent;

		ent = ahm_InitRandomEntity();
		slot[2] = 3;
		if (ent != (char*) 0) {
			rnd = gm_RandomMod(8) & 0xffff;
			*(int*) (slot + 0x1f0) = *(int*) ent;
			slot[0x164] = ent[0xd4];
			slot[9] = ent[0xd5];
			slot[0xc] = ent[0xd6];
			strcpy(slot + 0x30, ent + 4);
			strcpy(slot + 0x40, ent + 0x14);
			strcpy(slot + 0x1f4, ent + 0xd7);
			*(int*) (slot + 0x80) = *(int*) (ent + 0x24);
			*(char*) (slot + 0x84) = ent[0x28];
			memcpy(slot + 0x88, ent + 0x2c, 0xa8);
			*(unsigned short*) (slot + 0x50) =
			    (unsigned short) (*(int*) 0x1003542c);
			(*(int*) 0x1003542c)++;
			*(float*) (slot + 0x1c) = 1000.0f;
			*(float*) (slot + 0x1d0) =
			    (float) (gm_RandomFloat01() * *(float*) 0x100256b0) +
			    *(float*) 0x10025714;
			*(float*) (slot + 0x14) =
			    (float) (gm_RandomQuadratic(0x3c) *
			             *(float*) 0x100256c8) +
			    *(float*) 0x100256c4;
			n = (int) (*(float*) (slot + 0x1c) *
			           *(double*) 0x10025810);
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
			slot[0x217] = (char) (0x3c + (idx >= 6 ? 0x86 : 0));
			if ((double) arg4 <= *(float*) (slot + 0x20)) {
				acc = *(float*) (slot + 0x1c);
				for (n = _ftol((double) arg4 - *(float*) (slot + 0x20));
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
		t = *(unsigned char*) ((char*) 0x100a8c30 + bt * 0x24d);
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
		/* one parent missing: inherit from the surviving parent */
		if (mother != (char*) 0) {
			slot[0xc] = mother[0xc];
			*(int*) (slot + 0x1d0) = *(int*) (mother + 0x1d0);
			slot[0x217] = mother[0x217];
		} else if (father != (char*) 0) {
			slot[0xc] = father[0xc];
			*(int*) (slot + 0x1d0) = *(int*) (father + 0x1d0);
			slot[0x217] = father[0x217];
		}
		slot[0x164] = (char) arg6;
		slot[0x166] = 0;
		slot[0x165] = (char) arg7;
		n = gm_MapEntityStatRange(arg6 & 0xff);
		rnd = gm_RandomMod(8) & 0xffff;
		if (slot[2] != 3) {
			if (n == 0xb || n == 0xc) {
				if (rnd < 3) {
					slot[0x217] = 0x3c;
				} else {
					slot[0x217] = (char) (0x58 + (rnd >= 6 ? 4 : 0));
				}
			} else {
				if (rnd < 3) {
					slot[0x217] = 0x58;
				} else {
					slot[0x217] =
					    (char) (0xc2 - (rnd >= 6 ? 0x66 : 0));
				}
			}
		}
		/* 14-iteration trait interpolation from the trait table */
		for (i = 0; i < 0xe; i++) {
			float lo;
			float hi;

			lo = *(float*) (0x10025818 + n * 0x70 + i * 8);
			hi = *(float*) (0x10025818 + n * 0x70 + i * 8 + 4);
			slot[0x88 + i * 0xc] =
			    (char) (int) (gm_RandomFloat01() * (double) (hi - lo) +
			                  lo);
			slot[0x84 + i * 0xc] =
			    (char) (int) ((double) (gm_RandomMod(0xa) & 0xffff) +
			                  *(double*) 0x10025f98);
			slot[0x80 + i * 0xc] =
			    (char) (int) ((double) slot[0x88 + (i - 1) * 0xc] *
			                  *(double*) 0x100256d0);
		}
		slot[0xc] = (char) gm_RandomMod(2);
		*(float*) (slot + 0x1d0) =
		    (float) (gm_RandomFloat01() * *(float*) 0x100256b0) +
		    *(float*) 0x10025714;
		/* 0x300-iteration per-type random tables */
		for (j = 0; j < 0x300; j++) {
			*(char*) (0x100a9820 +
			          ((*(unsigned short*) slot * 3) << 8) + j) =
			    (char) (gm_RandomMod(0x40) - 0x20);
			*(char*) (0x1014d8e0 + *(unsigned short*) slot +
			          j * 0x300) = 0;
		}
		/* stat modifier loop from the type tables */
		if (arg7 != 0 && arg6 == 0) {
			for (i = 0; i < 5; i++) {
				slot[0x80 + i] = (char) gm_RandomStatModifier(
				    *(unsigned char*) (0x10030dda +
				                       slot[0x165] * 3));
			}
		} else {
			for (i = 0; i < 5; i++) {
				slot[0x80 + i] = (char) gm_RandomStatModifier(
				    *(unsigned char*) (0x100a8ba0 +
				                       slot[0x164] * 3));
			}
		}
		goto finalize;
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
	}
	/* 14-iteration parent-byte trait interpolation */
	for (i = 0; i < 0xe; i++) {
		double rnd01;

		rnd01 = gm_RandomFloat01();
		slot[0x88 + i * 0xc] = (char) (int) (
		    (1.0 - rnd01) *
		        (double) *(unsigned char*) (father + 0x88 + i * 0xc) +
		    rnd01 * (double) *(unsigned char*) (mother + 0x88 + i * 0xc));
		slot[0x84 + i * 0xc] =
		    (char) (int) ((double) (gm_RandomMod(0xa) & 0xffff) +
		                  *(double*) 0x10025f98);
		slot[0x80 + i * 0xc] =
		    (char) (int) ((double) slot[0x88 + (i - 1) * 0xc] *
		                  *(double*) 0x100256d0);
	}
	*(float*) (slot + 0x124) =
	    (float) ((gm_RandomFloat01() + *(double*) 0x10025688) *
	             *(double*) 0x10025f90);
	*(float*) (slot + 0x128) =
	    (float) ((double) *(float*) (slot + 0x124) *
	             *(double*) 0x100256d0);
	/* find the best trait index of each parent (quirky +1 indexing) */
	best_mother = 0;
	best_father = 0;
	for (i = 0; i < 4; i++) {
		if (*(unsigned char*) (mother + 0x81 + i) >
		    *(unsigned char*) (mother + 0x80 + best_mother)) {
			best_mother = i + 1;
		}
		if (*(unsigned char*) (father + 0x81 + i) >
		    *(unsigned char*) (father + 0x80 + best_father)) {
			best_father = i + 1;
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
			    ((1.0 - (double) acc) *
			         (double) *(unsigned char*) (father + 0x80 + i) +
			     (double) acc *
			         (double) *(unsigned char*) (mother + 0x80 + i)) *
			    *(float*) 0x100256b0);
		}
	}
	slot[0xc] = (char) gm_RandomMod(2);
	*(float*) (slot + 0x1d0) =
	    (float) (gm_RandomFloat01() * *(float*) 0x100256b0) +
	    *(float*) 0x10025714;
	/* 0x300-iteration per-type random tables */
	for (j = 0; j < 0x300; j++) {
		*(char*) (0x100a9820 +
		          ((*(unsigned short*) slot * 3) << 8) + j) =
		    (char) (gm_RandomMod(0x40) - 0x20);
		*(char*) (0x1014d8e0 + *(unsigned short*) slot +
		          j * 0x300) = 0;
	}
	/* stat modifier loop from the type tables */
	if (arg7 != 0 && arg6 == 0) {
		for (i = 0; i < 5; i++) {
			slot[0x80 + i] = (char) gm_RandomStatModifier(
			    *(unsigned char*) (0x10030dda + slot[0x165] * 3));
		}
	} else {
		for (i = 0; i < 5; i++) {
			slot[0x80 + i] = (char) gm_RandomStatModifier(
			    *(unsigned char*) (0x100a8ba0 + slot[0x164] * 3));
		}
	}

finalize:
	if (type != 6 && type != 7) {
		slot[0xd] = *(char*) (0x100b0ba5 + slot[0x164] * 3);
	}
	memset(slot + 0x5c, 0xff, 0x20);
	*(int*) (slot + 0x64) = gender;
	slot[0x58] = 1;
	if (father != (char*) 0) {
		slot[0x58] = (char) (father[0x58] + 1);
		for (i = 0; i < 8; i++) {
			if (*(int*) (father + 0x68 + i * 4) == -1) {
				*(int*) (father + 0x5c + i * 4) = *(int*) (slot + 4);
				break;
			}
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
	*(float*) (slot + 0x1c) = 1000.0f;
	*(float*) (slot + 0x20) = 12.0f;
	*(float*) (slot + 0x14) =
	    (float) (gm_RandomQuadratic(0x3c) * *(float*) 0x100256c8) +
	    *(float*) 0x100256c4;
	acc = *(float*) (slot + 0x1c);
	for (n = _ftol((double) arg4 - *(float*) (slot + 0x20)); n > 0; n--) {
		acc = acc - *(float*) (slot + 0x14) +
		      *(float*) (slot + 0x14) / acc;
	}
	if (acc > *(float*) 0x100256a0) {
		acc = *(float*) 0x100256a0;
	}
	*(float*) (slot + 0x1c) = acc;
	memset(slot + 0x1b4, 0, 0x10);
	ahm_ResetEntityState(slot);
	if (slot[2] == 3 || slot[2] == 4 || slot[2] == 2 || slot[2] == 0x13) {
		rnd = gm_RandomMod(3) & 0xffff;
		slot[0x82 + rnd] = (char) (slot[0x82 + rnd] + 0x2a);
	}
	if (idx == 0xffff) {
		LogMessageInternal(s_file_spiel_c_10031004, 0x286c, s_bug_10031594,
		                   1);
	}
	sprintf(work, s_fmt_playerid_10031570, g_next_object_id, slot + 0x30);
	LogMessageInternal(s_file_spiel_c_10031004, 0x2888, work, 8);
	return idx;
}
