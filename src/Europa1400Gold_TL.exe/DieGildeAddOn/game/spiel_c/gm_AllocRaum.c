/* gm_AllocRaum — allocate a building's contents (components,
 * resources, producers) for the given building record.
 *
 * Reconstructed from the disassembly at 0x10017c40: NULL guards on the two
 * entity tables and the 0x5008 pool limit; gm_AllocObjekt for the main
 * object; the entity-type row (`g_entity_type_table + geb[0] * 0x24d`)
 * scanned from field 0x23 for the caller's component id; the 0x40-slot
 * component loop with the type 2/6 early-out and the 0x8000 flag
 * sub-allocation; two gm_ff_Objekt walks (filter 0x2a, then
 * 2/0x116/6) each clamping fields 0x1c/0x1d; the 0x92..0x97 / 0x2db
 * building-type branch with the seasonal slot table at
 * g_slot_array + season * 0x2a90; and the 0x80-stride producer loop with
 * its 16-allocation LogMessageInternal guard.  The original object is kept
 * in a stack slot across the producer loop and is the return value.
 *
 * RELOC 742/742.  Seven shapes are required and must not be undone.  The two
 * that closed it (677 -> 742) are the advance-first scan cursor
 * (`scan += 2;` then read `*scan`, rather than reading `scan + 2` and then
 * advancing), which splits the row base and the cursor into the reference's
 * `lea ebp,[eax+edx*4]` / `lea eax,[ebp+0x23]` pair, and computing `row`
 * before `i = 0`, which frees ebp for that row base.  Each alone is a
 * regression: the scan shape by itself scores 131/743 (one byte long, because
 * geb stays in ebp and `mov cl,[ebp]` needs a displacement byte that
 * `mov cl,[edi]` does not), and the statement swap by itself is 167 at obj
 * 741, one byte short.  Together they are exact.
 *
 * The other five carried it from the start and are still load-bearing: the
 * three table/limit guards merged into one `||`
 * (separate `if`s emit three `xor eax,eax; ret` exits, 54/790); the 0x1c/0x1d
 * clamps written inline instead of through an `unsigned char` temp, which
 * otherwise spills to a stack slot (270 -> 340 -> 551); the producer walk
 * as a `do/while` with an `(int)` limit compare, which gives the reference's
 * `jl` and its loop rotation (551 -> 652); the `query_result+6` source-field store
 * written before the `query_result+0xe` constant store in both query arms, which is the
 * reference's load/store interleave at IDX 89/126 (652 -> 672); and the
 * volatile read of `geb+1` at the gm_AllocObjekt call, which pins that load
 * below the callee-save pushes so obj_id takes esi and geb takes edi as the
 * reference has them at IDX 12-18 (672 -> 677).
 *
 * Dead ends, with the score each produced.  Earlier: hoisting `*(int*)(geb+1)`
 * into a local before the 0xe store (104/747); splitting the 0x7fff mask off
 * the first row word (103/744); reading `geb[0]` into a local before the row
 * multiply (652, neutral); moving `i = 0` above the gm_AllocObjekt call (642).
 *
 * 2026-09-06, against the 677 base.  All neutral at obj 742: the scan cursor
 * as `unsigned short*` walking `sp[1]`/`sp++`, the cursor declared inside the
 * `if` body, the raw row word hoisted into an `unsigned short` temp before the
 * mask, `scan` initialised from `row` and offset in a second statement, the
 * scan cursor indexed by `i` instead of advanced, `register`/plain-alias
 * copies of `geb`, the row offset split into an `int` local, a second `comp2`
 * local for the loop (9a live-range split), `i = i + 1` and `scan = scan + 2`
 * spellings, and a CFLAGS sweep (/O2 /Gd /G5, /Ox /Gd, /O2 /Gd /Gy,
 * /O2 /Gd /Ob1 all identical; /O1 /Gd is 58/742 at obj 669).  Worse: a
 * volatile read of `geb[0]` (113/751), a volatile read of the loop word
 * (673), a volatile-alias read of `row` (73/752), a `char* volatile` cursor
 * (68/760), `unsigned short` comp width (111/752), the mask split into a
 * separate statement (106/744), a plain `while` scan loop (126/743), and
 * computing `row` before the gm_AllocObjekt call (66/736).
 *
 * The 18 residual diffs those notes describe were one problem, not two.  The
 * IDX 33-44 cursor split and the IDX 18/23 `geb`-in-ebp role were the same
 * register-pressure fault: with `i = 0` first, msvc6 has ebp tied up and folds
 * the row+0x23 displacement into the first read.  Freeing ebp and advancing
 * the cursor before the read clears both clusters at once.
 *
 * Operand audit (2026-09-06): every `~~` resolves.  The masked globals are
 * g_item_def_table (0x101de450), g_entity_type_table (0x100a8c30),
 * g_query_limit (0x10035450), g_current_season (0x10035439), g_slot_array
 * (0x1009b770) and g_producer_id_table (0x1002dde0), each matching its declaration
 * here.  The masked calls resolve to gm_AllocObjekt (0x10016760),
 * gm_ff_Objekt (0x10016460), ReportMessage (0x100035c0) and
 * LogMessageInternal (0x10003640) per db/server.dll_functions.csv.  The three
 * message pointers are written as literal addresses and compare `==`, not
 * `~~`; read out of original/server.exe they are 0x100314b8 "gm_AllocRaum():
 * ob_LAGERFLAECHE_ALLGEMEIN is missing in ob_M...", 0x10031484
 * "gm_AllocRaum(): Too many objects in 'Marktstand'..." and 0x10031004
 * "D:\\Develop\\DieGildeAddOn\\game\\spiel.c".
 * Re-audited at RELOC: all 17 `~~` slots are the six globals above plus nine
 * calls to those four functions, and no `**` remains. */

// FUNCTION: GOLDTL 0x506000
// SIZE: 720

#include "../../../Units/Error/error.h"

#include <stdlib.h>
#include "rebrew_types.h"
#include "rebrew_globals.h"

extern int g_query_limit;              /* 0x10035450 */
extern unsigned char g_current_season; /* 0x10035439 */

void* __cdecl gm_AllocObjekt(int, int, int);
unsigned short* __cdecl gm_ff_Objekt(int container_id, int arg_count, int first_arg, ...);

char* __cdecl gm_AllocRaum(char* geb, int obj_id)
{
	char* obj;
	char* row;
	char* scan;
	char* query_result;
	char* sub;
	char* slot;
	char* prod;
	int i;
	int comp;
	int alloc_count;

	if (g_item_def_table == NULL || g_entity_type_table == NULL ||
	    g_query_limit + 0x40 >= 0x5008) {
		return NULL;
	}

	/* The volatile read pins the geb+1 load below the callee-save pushes, so
	 * obj_id claims esi and geb claims edi as the reference has them
	 * (prologue IDX 12-18, 672 -> 677). */
	obj = (char*) gm_AllocObjekt(*(volatile int*) (geb + 1), obj_id, 1);
	/* `row` before `i` is required: it frees ebp for the row base, which is
	 * the byte that the advance-first scan below otherwise costs. */
	row = g_entity_type_table + (unsigned char) geb[0] * 0x24d;
	i = 0;

	/* Skip past the caller's own component id in the type row.  Advancing the
	 * cursor before the read, rather than reading `scan + 2`, is what makes
	 * msvc6 split the row base and the cursor into `lea ebp,[eax+edx*4]` plus
	 * `lea eax,[ebp+0x23]` as the reference does. */
	scan = row + 0x23;
	comp = *(unsigned short*) scan & 0x7fff;
	if (comp != obj_id) {
		do {
			scan += 2;
			comp = *(unsigned short*) scan & 0x7fff;
			i++;
		} while (comp != obj_id);
	}
	i++;

	while (i < 0x40) {
		unsigned short raw = *(unsigned short*) (row + i * 2 + 0x23);
		if (raw == 0) {
			break;
		}
		if (raw != 0xffff) {
			int id = raw & 0x7fff;
			char* def = g_item_def_table + (id << 6) + id;
			if (def[0] == 2 || def[0] == 6) {
				i = 0x40;
			}
			else if (raw & 0x8000) {
				gm_AllocObjekt(*(int*) (obj + 2), id, 1);
			}
		}
		i++;
	}

	query_result = (char*) gm_ff_Objekt(*(int*) (obj + 0x14), 1, 0, 0x2a);
	if (query_result != NULL) {
		/* Source field first: the reference loads geb[1]/obj[2] before it
		 * stores the constant 2 at query_result+0xe (IDX 89/126). */
		*(int*) (query_result + 6) = *(int*) (geb + 1);
		*(int*) (query_result + 0xe) = 2;
		if (row[0x23d] == 0 && row[0x23e] == 0 && row[0x23f] != 0) {
			query_result[0x1c] = row[0x23f];
		}
		else {
			query_result[0x1c] = (char) ((unsigned char) row[0x23d] < 2 ? 2 : (unsigned char) row[0x23d]);
			query_result[0x1d] = (char) ((unsigned char) row[0x23e] < 2 ? 2 : (unsigned char) row[0x23e]);
		}
	}

	query_result = (char*) gm_ff_Objekt(*(int*) (obj + 0x14), 2, 0, 0x116, 6);
	if (query_result != NULL) {
		*(int*) (query_result + 6) = *(int*) (obj + 2);
		*(int*) (query_result + 0xe) = 2;
		if (row[0x23d] == 0 && row[0x23e] == 0 && row[0x23f] != 0) {
			query_result[0x1c] = (char) ((unsigned char) row[0x23f] < 6 ? 6 : (unsigned char) row[0x23f]);
		}
		else {
			query_result[0x1c] = (char) ((unsigned char) row[0x23d] < 6 ? 6 : (unsigned char) row[0x23d]);
			query_result[0x1d] = (char) ((unsigned char) row[0x23e] < 6 ? 6 : (unsigned char) row[0x23e]);
		}
	}

	if ((*(unsigned short*) obj >= 0x92 && *(unsigned short*) obj <= 0x97) ||
	    *(unsigned short*) obj == 0x2db) {
		slot = (char*) &g_slot_array + (unsigned int) g_current_season * 0x2a90;
		query_result = (char*) gm_ff_Objekt(*(int*) (obj + 0x14), 1, 0, 0x116);
		if (query_result != NULL) {
			query_result[0x1c] = 0xc;
			query_result[0x1d] = 0;
			*(int*) (query_result + 0xe) = 3;
		}
		else {
			ReportMessage((char*) 0x100314b8);
		}

		sub = (char*) gm_AllocObjekt(*(int*) (obj + 2), 0xff, 1);
		alloc_count = 0;
		prod = (char*) &g_producer_id_table;
		slot += 4;
		/* Signed bound: the reference ends the walk with `jl`, so the
		 * limit compare must be on int, not on the pointer (which would
		 * emit `jb`).  Testing at the bottom keeps the rotation the
		 * reference has (the loop always runs at least once). */
		do {
			if (*(unsigned short*) (slot + 0x38) == *(unsigned short*) obj &&
			    *(int*) slot != 0) {
				if (alloc_count < 0x10) {
					gm_AllocObjekt(*(int*) (sub + 2), *(unsigned short*) prod, 1);
					alloc_count++;
				}
				else {
					LogMessageInternal((char*) 0x10031004, 0x16a6, (char*) 0x10031484, 1);
				}
			}
			prod += 0x80;
			slot += 0x80;
		} while ((int) prod < 0x10030860);
	}

	return obj;
}
