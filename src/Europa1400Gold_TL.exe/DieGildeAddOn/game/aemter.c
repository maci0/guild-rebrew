/* aemter - office slot table helpers (proper C) */

#include <stdio.h>
#include "../../Units/Error/error.h"

/* Office slot entry lifted to game_structs.h (this TU had spelled the
 * six fields `a/b/c/type/d`; the amt_fio_LoadAemter twin's read-order
 * names are the ones kept). */
#include "game_structs.h"

/* 24-byte copy payload fetched from the g_office_role_templates template table.
 * Lifted to game_structs.h (shared-layout rule: cm_ExAllocRaum.c's
 * copy_12_dwords is byte-identical, this copy names the touched fields). */
#include "game_structs.h"

// FUNCTION: GOLDTL 0x4e7f20
// SIZE: 208


int __cdecl amt_ValidateOfficeCandidate(int* arg1)
{
	unsigned char* rec;
	unsigned char holder;
	OFFICE_SLOT* p;
	int i;

	rec = gm_LookupEntityRecordById(arg1[0]);
	if (rec == 0 || rec[0x168] != 0)
		return 0;

	i = 0;
	for (; i < 30; i++) {
		if (((OFFICE_SLOT*) g_office_slots)[i].id == ((unsigned char*) arg1)[4])
			break;
	}
	if (i >= 30)
		return 0;

	if (((OFFICE_SLOT*) g_office_slots)[i].mplayerid != -1 ||
	    ((OFFICE_SLOT*) g_office_slots)[i].status != 3 ||
	    ((OFFICE_SLOT*) g_office_slots)[i].pcount >= 4)
		return 0;
	holder = ((OFFICE_SLOT*) g_office_slots)[i].mamt;
	if (((unsigned char*) arg1)[6] != holder)
		return 0;

	if (((unsigned char*) arg1)[5] != 0xff) {
		i = 0;
		for (; i < 30; i++) {
			if (((OFFICE_SLOT*) g_office_slots)[i].id == ((unsigned char*) arg1)[5])
				break;
		}
		if (i >= 30)
			return 0;

		if (holder != ((OFFICE_SLOT*) g_office_slots)[i].mamt ||
		    ((OFFICE_SLOT*) g_office_slots)[i].mplayerid != -1 ||
		    ((OFFICE_SLOT*) g_office_slots)[i].status != 3 ||
		    ((OFFICE_SLOT*) g_office_slots)[i].pcount >= 4)
			return 0;
	}
	return 1;
}

/* Validates preconditions and assigns an office to an entity.  Performs
 * eligibility checks, then updates the office holder table and entity
 * links. */
