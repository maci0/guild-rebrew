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

// GLOBAL: SERVER 0x101de5a0
extern char g_office_slots[]; /* 0x101de5a0 */
// GLOBAL: SERVER 0x10029bb8
extern OFFICE_ROLE_TEMPLATE g_office_role_templates[];
void* __cdecl gm_LookupEntityRecordById(int entityId);

/* Validates whether an entity can take an office position.  Scans the
 * office slot table for the requested type; on a hit verifies the slot is
 * free (no holder, type 3, fewer than 4 incumbents) and, when a home
 * office type is given, that both table entries agree on the holder
 * byte.  Returns 1 when valid, 0 otherwise. */

// FUNCTION: SERVER 0x1000b1c0
// SIZE: 205

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

// FUNCTION: SERVER 0x1000b290
// SIZE: 425
//   RELOC 425/425, obj 425, 0 structural and 0 register diffs.  The shape is
//   load-bearing in four places; each was needed to get here and each still
//   regresses the function on its own:
//     - the requested office byte is homed in the dead arg1 slot
//       (`*(unsigned char*) &arg1 = cmd[6]`).  The original reloads it as a
//       dword for both the copy compare and the +0x168 store, which is what
//       makes it use a 0x18 frame with `push edi` in the prologue;
//     - the copy index is spelled `g_office_role_templates[((OFFICE_SLOT*) g_office_slots)[i].mamt]`, not
//       through a row pointer, so it CSEs with the `.mamt` the guard left in al
//       and emits `and eax,0xff` / `lea ecx,[eax+eax*2]`;
//     - the home dword is re-read through a `unsigned int*` local taken
//       immediately before the read (`hp = (unsigned int*) &arg1; hw = *hp`),
//       placed after the copy.  This is what schedules `mov eax,[esp+0x2c]`
//       ahead of the `lea esi` / `rep movsd` block, as the target does, and
//       keeps the value live in eax to `mov [ebp+0x168],al`;
//     - guards and increments are i-first in the x5 branch and j-first in the
//       j branch, which merges the two epilogues the way the target does.
//   Ruled out for the home re-read, all worse: a plain `*(unsigned int*)`
//   cast at the same spot (109, obj 423), a `volatile` cast (411, the load
//   sinks past `rep movsd`), the `hp` assignment hoisted above the copy or up
//   to the home store (109-236), a `volatile` qualifier on the home store
//   (125), and the read taken through an `unsigned char*` home pointer (109).
//   CFLAGS are inert: /G3 /G4 /G5 /GB /Gy /Gs /Gf /GF /Ob1 /Ot /Ze /Ox all
//   give 425/425; /G6 gives 386 and also breaks amt_ValidateOfficeCandidate.
//   `/DREBREW_ALLOW_NAKED` in this function's CFLAGS is inert: the file has
//   no `__asm` and no `naked` attribute.

unsigned int __cdecl amt_ValidateAndAssignOffice(unsigned int* arg1)
{
	unsigned char* cmd;
	unsigned int* arg1_alias;
	unsigned char* rec;
	unsigned char x5;
	unsigned int arg1_value;
	int f0v;
	OFFICE_ROLE_TEMPLATE copy;
	int i;
	int j;
	cmd = (unsigned char*) arg1;
	rec = gm_LookupEntityRecordById(*(int*) cmd);
	if (rec == 0)
		return 0;
	if (*(unsigned short*) rec == 0xffff)
		return 0;
	if (rec[0x168] != 0)
		return 0;
	i = 0;
	for (; i < 30; i++) {
		if (((OFFICE_SLOT*) g_office_slots)[i].id == cmd[4])
			break;
	}
	if (i >= 30)
		return 0;
	*(unsigned char*) &arg1 = cmd[6];
	if (*(unsigned char*) &arg1 != ((OFFICE_SLOT*) g_office_slots)[i].mamt)
		return 0;
	x5 = cmd[5];
	if (x5 != 0xff) {
		for (j = 0; j < 30; j++) {
			if (((OFFICE_SLOT*) g_office_slots)[j].id == x5)
				break;
		}
		if (j >= 30)
			return 0;
		if (((OFFICE_SLOT*) g_office_slots)[i].mamt != ((OFFICE_SLOT*) g_office_slots)[j].mamt)
			return 0;
		copy = g_office_role_templates[((OFFICE_SLOT*) g_office_slots)[i].mamt];
		arg1_alias = (unsigned int*) &arg1;
		arg1_value = *arg1_alias;
		f0v = copy.f0;
		if (f0v != (int) (arg1_value & 0xff) || copy.f10 == 0)
			return 0;
		{
			int type_i;
			int type_j;
			type_i = ((OFFICE_SLOT*) g_office_slots)[i].mplayerid;
			type_j = ((OFFICE_SLOT*) g_office_slots)[j].mplayerid;
			if (type_i != -1 ||
			    ((OFFICE_SLOT*) g_office_slots)[i].status != 3 ||
			    ((OFFICE_SLOT*) g_office_slots)[i].pcount >= 4 ||
			    type_j != -1 ||
			    ((OFFICE_SLOT*) g_office_slots)[j].pcount >= 4)
				return 0;
			rec[0x168] = (unsigned char) arg1_value;
			((OFFICE_SLOT*) g_office_slots)[i].pcount++;
			((OFFICE_SLOT*) g_office_slots)[j].pcount++;
			return 1;
		}
	}
	{
		int type_i;
		type_i = ((OFFICE_SLOT*) g_office_slots)[i].mplayerid;
		if (type_i != -1 ||
		    ((OFFICE_SLOT*) g_office_slots)[i].status != 3 ||
		    ((OFFICE_SLOT*) g_office_slots)[i].pcount >= 4)
			return 0;
		rec[0x168] = *(unsigned char*) &arg1;
		((OFFICE_SLOT*) g_office_slots)[i].pcount++;
		return 1;
	}
}

/* Validates a generic office command string.  Parses the command buffer
 * and checks that the referenced entities and office type are valid.
 * Returns 1 when valid, 0 otherwise. */

// FUNCTION: SERVER 0x1000b440
// SIZE: 133

int __cdecl amt_ValidateCommand(char* arg1)
{
	int i;

	if (((unsigned char*) arg1)[6] == 0xff)
		return 1;

	i = 0;
	for (; i < 42; i++) {
		if (((OFFICE_SLOT*) g_office_slots)[i].id == ((unsigned char*) arg1)[0])
			break;
	}
	if (i >= 42)
		return 0;

	if (((OFFICE_SLOT*) g_office_slots)[i].status != 1)
		return 0;
	if (((OFFICE_SLOT*) g_office_slots)[i].msetter != -1)
		return 0;
	if (*(int*) (arg1 + 7) != -1) {
		if (gm_LookupEntityRecordById(*(int*) (arg1 + 7)) == 0)
			return 0;
	}
	if (*(int*) (arg1 + 1) != -1) {
		if (gm_LookupEntityRecordById(*(int*) (arg1 + 1)) == 0)
			return 0;
	}
	return 1;
}
