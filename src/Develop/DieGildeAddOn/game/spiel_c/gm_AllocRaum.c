extern unsigned char g_town_records[5 * 0x2a90];
// FUNCTION: GOLDTL 0x506000
// SIZE: 720
// FUNCTION: SERVER 0x10017c40

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
		slot = (char*) g_town_records + 0x10 + (unsigned int) g_current_season * 0x2a90;
		query_result = (char*) gm_ff_Objekt(*(int*) (obj + 0x14), 1, 0, 0x116);
		if (query_result != NULL) {
			query_result[0x1c] = 0xc;
			query_result[0x1d] = 0;
			*(int*) (query_result + 0xe) = 3;
		}
		else {
			ReportMessage("gm_AllocRaum(): ob_LAGERFLAECHE_ALLGEMEIN is missing in ob_MARKTSTAND!");
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
					LogMessageInternal("D:\\Develop\\DieGildeAddOn\\game\\spiel.c", 0x16a6, "gm_AllocRaum(): Too many objects in 'Marktstand'...", 1);
				}
			}
			prod += 0x80;
			slot += 0x80;
		} while ((int) prod < (int) (g_producer_id_table + 2720));
	}

	return obj;
}

