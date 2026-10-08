#include <stdio.h>
#include "../../Units/Error/error.h"
#include "office_slot.h"
#include "game_structs.h"

extern char g_office_slots[0x3f0];
extern unsigned short g_current_hour;
extern int __cdecl ls_ReadVfsDataChecked(void* outBuffer, int elementSize, int elementCount, int streamCtx);
extern void __cdecl srv_InitBuildingTypeTable(void);
extern void __cdecl LogMessageInternal(const char* module, int line, const char* text, int type);
extern int __cdecl sprintf(char* buffer, const char* format, ...);

void* __cdecl gm_LookupEntityRecordById(int);

void* __cdecl gm_LookupEntityRecordById(int);

void* __cdecl gm_LookupEntityRecordById(int entityId);

float g_office_float_table[7][7] = {
	{ 1.0f, -2.5f, -2.5f, -2.5f, -5.0f, -5.0f, -10.0f },
	{ 1.0f, 0.0f, -2.5f, -5.0f, -2.5f, -7.0f, -10.0f },
	{ 1.0f, -2.5f, 0.0f, -2.5f, -5.0f, -5.0f, -10.0f },
	{ 1.0f, -5.0f, -2.5f, 0.0f, -7.5f, -2.5f, -10.0f },
	{ 1.0f, 1.0f, 1.0f, 1.0f, 0.0f, -5.0f, -10.0f },
	{ 1.0f, 1.0f, 1.0f, 1.0f, -5.0f, 0.0f, -10.0f },
	{ 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f },
};

OFFICE_ROLE_TEMPLATE g_office_role_templates[40] = {
	{ 0, 0, 0, 0, 0, 0x40a00000 },
	{ 1, 1, 1, 0x1f4, 1, 0x40a00000 },
	{ 2, 1, 2, 0x2bc, 0, 0x40a00000 },
	{ 3, 1, 3, 0x3e8, 0, 0x40a00000 },
	{ 4, 2, 1, 0x1f4, 1, 0x40a00000 },
	{ 5, 2, 2, 0x2bc, 0, 0x40a00000 },
	{ 6, 2, 3, 0x3e8, 0, 0x40a00000 },
	{ 7, 3, 1, 0x1f4, 1, 0x40a00000 },
	{ 8, 3, 2, 0x2bc, 0, 0x40a00000 },
	{ 9, 3, 3, 0x3e8, 0, 0x40a00000 },
	{ 0xa, 4, 4, 0x7d0, 0, 0x40a00000 },
	{ 0xb, 4, 4, 0x7d0, 0, 0x40a00000 },
	{ 0xc, 4, 4, 0x7d0, 0, 0x40a00000 },
	{ 0xd, 4, 5, 0x9c4, 0, 0x40a00000 },
	{ 0xe, 4, 5, 0x9c4, 0, 0x40a00000 },
	{ 0xf, 4, 6, 0xbb8, 0, 0x40a00000 },
	{ 0x10, 5, 4, 0x7d0, 0, 0x40c00000 },
	{ 0x11, 5, 4, 0x7d0, 0, 0x40c00000 },
	{ 0x12, 5, 4, 0x7d0, 0, 0x40c00000 },
	{ 0x13, 5, 5, 0x9c4, 0, 0x40c00000 },
	{ 0x14, 5, 5, 0x9c4, 0, 0x41000000 },
	{ 0x15, 5, 6, 0xbb8, 0, 0x41000000 },
	{ 0x16, 6, 7, 0x1388, 0, 0x40e00000 },
	{ 0x17, 6, 7, 0x1388, 0, 0x40e00000 },
	{ 0x18, 6, 7, 0x1388, 0, 0x41200000 },
	{ 0x19, 6, 8, 0x1b58, 0, 0x40e00000 },
	{ 0x1a, 6, 8, 0x1b58, 0, 0x41400000 },
	{ 0x1b, 6, 9, 0x2710, 0, 0x40e00000 },
	{ 0x1c, 7, 4, 0xbb8, 0, 0x40a00000 },
	{ 0x1d, 7, 4, 0xbb8, 0, 0x40a00000 },
	{ 0x1e, 7, 4, 0xbb8, 0, 0x40a00000 },
	{ 0x1f, 7, 4, 0xbb8, 0, 0x40a00000 },
	{ 0x20, 7, 4, 0xbb8, 0, 0x40a00000 },
	{ 0x21, 7, 4, 0xbb8, 0, 0x40a00000 },
	{ 0x22, 7, 4, 0xbb8, 0, 0x41000000 },
	{ 0x23, 8, 0xa, 0x4e20, 0, 0x40a00000 },
	{ 0x24, 8, 0xa, 0x4e20, 0, 0x40a00000 },
	{ 0x25, 8, 0xb, 0x7530, 0, 0x40a00000 },
	{ 0x26, 8, 0xc, 0xc350, 0, 0x40a00000 },
	{ 0x27, 8, 0xc, 0xc350, 0, 0x40a00000 },
};

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
int __cdecl amt_ExecuteOfficeAssignment(char* cmd_payload)
{
	int iStack;
	int ent;
	int record_index;
	int old_owner;
	int record_off;

	iStack = -1;

	/* Validate associated entity if present */
	if (*(int*) (cmd_payload + 7) != -1) {
		if (gm_LookupEntityRecordById(*(int*) (cmd_payload + 7)) == 0) {
			return 0;
		}
	}

	/* Get owner entity */
	ent = 0;
	if (*(int*) (cmd_payload + 1) != -1) {
		ent = (int)gm_LookupEntityRecordById(*(int*) (cmd_payload + 1));
		if (ent == 0) {
			return 0;
		}
		iStack = *(int*) (ent + 4);
	}

	/* Search table for matching type byte */
	record_index = 0;
	for (; record_index < 0x2a; record_index++) {
		if (((OfficeSlot*) g_office_slots)[record_index].type == *cmd_payload)
			break;
	}
	if (record_index >= 0x2a) {
		return 0;
	}

	record_off = record_index * 0x18;

	/* Lookup existing owner and clear old role references */
	old_owner = (int)gm_LookupEntityRecordById(((OfficeSlot*) g_office_slots)[record_index].entityId);
	if (old_owner != 0 && *(int*) (old_owner + 4) != *(int*) (cmd_payload + 1)) {
		char role;
		role = ((OfficeSlot*) g_office_slots)[record_index].role;

		if (*(char*) (old_owner + 0x166) == role) {
			*(char*) (old_owner + 0x166) = 0;
		}
		else if (*(char*) (old_owner + 0x169) == role) {
			*(char*) (old_owner + 0x169) = 0;
		}
		else {
			int flags;
			if (role == 0x23) {
				flags = *(int*) (old_owner + 0x1cc);
				flags &= 0xfffffdff;
			}
			else if (role == 0x24) {
				flags = *(int*) (old_owner + 0x1cc);
				flags &= 0xfffffbff;
			}
			else if (role == 0x25) {
				flags = *(int*) (old_owner + 0x1cc);
				flags &= 0xfffff7ff;
			}
			else {
				goto after_old_clear;
			}
			*(int*) (old_owner + 0x1cc) = flags;
		}
	}

after_old_clear:
	if (ent == 0) {
		goto final_store;
	}

	{
		int k;

		if ((unsigned char) ((OfficeSlot*) g_office_slots)[record_index].role <= 0x1b) {
			/* Small role path */
			if (*(char*) (ent + 0x166) != 0) {
				/* Search for existing assignment with same owner */
				int j;
				for (j = 0; j < 30; j++) {
					if (((OfficeSlot*) g_office_slots)[j].entityId == iStack) {
						((OfficeSlot*) g_office_slots)[j].entityId = -1;
						((OfficeSlot*) g_office_slots)[j].assignmentId = -1;
						((OfficeSlot*) g_office_slots)[j].state = 4;
						((OfficeSlot*) g_office_slots)[j].count = 0;
						break;
					}
				}
			}

			/* Compare role priorities */
			if (*(unsigned char*) ((unsigned char) ((OfficeSlot*) g_office_slots)[record_index].role * 0x18 + (unsigned int) ((char*) &g_office_role_templates + 0x8)) >=
			    *(unsigned char*) (*(unsigned char*) (ent + 0x166) * 0x18 + (unsigned int) ((char*) &g_office_role_templates + 0x8))) {
				*(char*) (ent + 0x167) = ((OfficeSlot*) g_office_slots)[record_index].role;
			}

			{
				char new_role;
				new_role = ((OfficeSlot*) g_office_slots)[record_index].role;
				*(char*) (ent + 0x166) = new_role;
				if (*(char*) (ent + 0x168) == new_role) {
					*(char*) (ent + 0x168) = 0;
				}
			}

			/* Set flags based on role */
			{
				unsigned char role_val;
				role_val = (unsigned char) ((OfficeSlot*) g_office_slots)[record_index].role;

				if (role_val == 0x0f) {
					*(int*) (ent + 0x1cc) = *(int*) (ent + 0x1cc) | 0x40;
				}
				else if (role_val == 0x15) {
					*(int*) (ent + 0x1cc) = *(int*) (ent + 0x1cc) | 0x80;
				}
				else if (role_val == 0x1b) {
					*(int*) (ent + 0x1cc) = *(int*) (ent + 0x1cc) | 0x100;
				}
			}

			/* Check role's count property */
			if (*(int*) ((unsigned int) (unsigned char) ((OfficeSlot*) g_office_slots)[record_index].role * 0x18 + (unsigned int) ((char*) &g_office_role_templates + 0x10)) != 0) {
				unsigned char* scan;
				k = 0;
				scan = (unsigned char*) ((char*) &g_office_slots + 0x8);

				while ((int) scan < (int) ((char*) &g_office_slots + 0x2d8)) {
					if (*scan == (unsigned char) ((OfficeSlot*) g_office_slots)[record_index].role && k != record_index) {
						goto dec_count;
					}
					scan += 0x18;
					k++;
				}
			}

		final_store:
			((OfficeSlot*) g_office_slots)[record_index].entityId = iStack;
			((OfficeSlot*) g_office_slots)[record_index].assignmentId = *(int*) (cmd_payload + 7);
			((OfficeSlot*) g_office_slots)[record_index].state = cmd_payload[5];
			if (cmd_payload[5] == 3) {
				((OfficeSlot*) g_office_slots)[record_index].count = 0;
			}
			return 1;

		dec_count:
			if (((OfficeSlot*) g_office_slots)[k].state == 3) {
				int cnt;
				cnt = ((OfficeSlot*) g_office_slots)[k].count;
				if (cnt != 0) {
					((OfficeSlot*) g_office_slots)[k].count = cnt - 1;
					if (cnt - 1 == 0) {
						((OfficeSlot*) g_office_slots)[k].state = 4;
					}
				}
			}
			goto final_store;
		}

		if ((unsigned char) ((OfficeSlot*) g_office_slots)[record_index].role >= 0x1c &&
		    (unsigned char) ((OfficeSlot*) g_office_slots)[record_index].role <= 0x22) {
			/* Medium role path (0x1c-0x22) */
			if (*(char*) (ent + 0x169) != 0) {
				int* scan;
				scan = (int*) ((char*) &g_office_slots + 0x2d4);
				do {
					if (*(char*) ((char*) scan + 4) == *(char*) (ent + 0x169) && *scan == *(int*) (ent + 4)) {
						*scan = -1;
					}
					scan = (int*) ((char*) scan + 0x18);
				} while ((int) scan < (int) ((char*) &g_office_slots + 0x37c));
			}

			*(char*) (ent + 0x169) = ((OfficeSlot*) g_office_slots)[record_index].role;
			goto final_store;
		}

		/* High role path (> 0x22) */
		{
			unsigned char role_ch;
			int flags;
			int mask;

			flags = *(int*) (ent + 0x1cc);
			flags &= 0xfffff1ff;
			*(int*) (ent + 0x1cc) = flags;

			role_ch = ((OfficeSlot*) g_office_slots)[record_index].role;
			mask = 0;
			if (role_ch == 0x23) {
				*(int*) (ent + 0x1cc) = flags | 0x200;
				mask = 0x4000;
			}
			else if (role_ch == 0x24) {
				*(int*) (ent + 0x1cc) = flags | 0x400;
				mask = 0x8000;
			}
			else if (role_ch == 0x25) {
				*(int*) (ent + 0x1cc) = flags | 0x800;
				mask = 0x10000;
			}

			{
				int row; extern unsigned char g_slot_table[];
				row = 0;
				do {
					*(int*) ((int) g_slot_table + 0x1cc + row * 0x21c) =
						*(int*) ((int) g_slot_table + 0x1cc + row * 0x21c) & ~mask;
					row++;
				} while (row < 768);
			}
		}
		goto final_store;
	}
}

/* 0x1001a299 */

/* Reads the office slot table.  The entry count depends on the save
 * version (0x25 for old saves, 0x2a for 0x10051+); each slot's six
 * fields are read with size checks.  Returns 1 on success, 0 on any
 * read failure or a count mismatch. */

void __cdecl amt_FindEntity26(int val)
{
	unsigned int i;
	for (i = 0x29; i != 0; i--) {
		/* asm checks byte at slot+8 (role); stores dword at slot+4 (entityId) */
		if (((OfficeSlot*) g_office_slots)[i].role == 0x26) {
			((OfficeSlot*) g_office_slots)[i].entityId = val;
			return;
		}
	}
}

/* Searches for an entity with type 0x27 (specific entity class)
 * matching the given value. Used for office-related lookups. */

void __cdecl amt_FindEntity27(int val)
{
	unsigned int i;
	for (i = 0x29; i != 0; i--) {
		if (((OfficeSlot*) g_office_slots)[i].role == 0x27) {
			((OfficeSlot*) g_office_slots)[i].entityId = val;
			return;
		}
	}
}

/* Swaps two office holders. Exchanges position assignments
 * between the entities referenced in the param array. Returns 0
 * on success, or non-zero if the swap is invalid. */

int __cdecl amt_SwapOfficeHolders(int* arg1)
{
	OfficeSlot* slot_a;
	OfficeSlot* slot_b;
	char* ent_a;
	char* ent_b;
	char* ent_c;
	int i;

	ent_a = (char*) gm_LookupEntityRecordById(arg1[0]);
	if (ent_a == 0)
		return 0;
	if (*(int*) (ent_a + 0x194) < *(int*) ((char*) arg1 + 6))
		return 0;

	/* find office slot A by type byte */
	i = 0;
	while (1) {
		if (((OfficeSlot*) g_office_slots)[i].type == *((char*) arg1 + 4)) {
			break;
		}
		i++;
		if (i >= 0x1e) {
			return 0;
		}
	}
	slot_a = &((OfficeSlot*) g_office_slots)[i];
	if (slot_a == 0) {
		return 0;
	}
	ent_b = (char*) gm_LookupEntityRecordById(slot_a->entityId);
	if (ent_b == 0) {
		return 0;
	}

	/* find office slot B by type byte */
	i = 0;
	while (1) {
		if (((OfficeSlot*) g_office_slots)[i].type == *((char*) arg1 + 5)) {
			break;
		}
		i++;
		if (i >= 0x1e) {
			return 0;
		}
	}
	slot_b = &((OfficeSlot*) g_office_slots)[i];
	if (slot_b == 0) {
		return 0;
	}
	ent_c = (char*) gm_LookupEntityRecordById(slot_b->entityId);
	if (ent_c == 0) {
		return 0;
	}
	*(char*) (ent_b + 0x166) = slot_b->role;
	*(char*) (ent_c + 0x166) = slot_a->role;
	i = slot_a->entityId;
	slot_a->entityId = slot_b->entityId;
	slot_b->entityId = i;
	*(int*) (ent_a + 0x194) -= *(int*) ((char*) arg1 + 6);
	return 1;
}

/* Clears all entity links for an office position. Removes
 * the holder and resets associated entity references. */

int __cdecl amt_ClearEntityLinks(char* entity)
{
	OfficeSlot* slot;
	unsigned short default_val;
	int i;
	int result;
	int state_tmp;

	default_val = (unsigned short) g_current_hour;
	result = 0;
	slot = (OfficeSlot*) g_office_slots;
	for (i = 0; i < 0x2a; i++) {
		if (slot[i].entityId == *(int*) (entity + 4)) {
			slot[i].entityId = -1;
			slot[i].assignmentId = -1;
			state_tmp = (default_val > 0xb) ? 4 : 3;
			slot[i].state = (char) state_tmp;
			slot[i].count = 0;
			result |= 1;
		}
		else if (slot[i].assignmentId == *(int*) (entity + 4)) {
			slot[i].assignmentId = -1;
			slot[i].state = 1;
		}
	}
	if (*(char*) (entity + 0x168) != 0) {
		for (i = 0; i < 0x2a; i++) {
			if (slot[i].role == *(char*) (entity + 0x168)) {
				if (slot[i].count > 0) {
					slot[i].count--;
					result |= 1;
				}
			}
		}
	}
	*(char*) (entity + 0x166) = 0;
	*(char*) (entity + 0x169) = 0;
	*(char*) (entity + 0x168) = 0;
	return result;
}

/* Client-only office helpers (the Gold T&L client's aemter.c order).  No server
 * function calls them, so /OPT:REF discards them; their absolute fixups still
 * count toward LINK's .reloc reservation. */

typedef struct {
	int type;
	float score;
	unsigned char rank;
	char pad9[3];
} OFFICE_PICK;
// SIZE 0xc

int __cdecl amt_GetSlotByRole(int role, OfficeSlot* out)
{
	int i;

	for (i = 0; i < 0x2a; i++) {
		if (((OfficeSlot*) g_office_slots)[i].role == role) {
			break;
		}
	}
	if (i >= 0x2a) {
		return 0;
	}
	*out = ((OfficeSlot*) g_office_slots)[i];
	return 1;
}

int __cdecl amt_GetRoleGroup(int role)
{
	if (role >= 0x28) {
		return 0;
	}
	return g_office_role_templates[role].f4;
}

int __cdecl amt_GetSlotByType(unsigned char type, OfficeSlot* out)
{
	int i;

	for (i = 0; i < 0x2a; i++) {
		if ((unsigned char) ((OfficeSlot*) g_office_slots)[i].type == type) {
			break;
		}
	}
	if (i >= 0x2a) {
		return 0;
	}
	*out = ((OfficeSlot*) g_office_slots)[i];
	return 1;
}

int __cdecl amt_GetRoleTemplate(int role, OFFICE_ROLE_TEMPLATE* out)
{
	if (role >= 0x28) {
		*out = g_office_role_templates[0];
		return 0;
	}
	*out = g_office_role_templates[role];
	return 1;
}

int __cdecl amt_ListSlotsOfGroup(int group, int max, OfficeSlot* out)
{
	int n;
	int i;
	int start;

	if (group == 0) {
		return 0;
	}
	if (group <= 6) {
		start = 30;
	}
	else if (group == 8) {
		start = 0x2a;
	}
	else {
		return 0;
	}
	n = 0;
	for (i = start - 1; i >= 0 && n < max; i--) {
		if (g_office_role_templates[(unsigned char) ((OfficeSlot*) g_office_slots)[i].role].f4 == group) {
			out[n++] = ((OfficeSlot*) g_office_slots)[i];
		}
	}
	return n;
}

int __cdecl amt_ListHeldSlotsOfGroup(int group, int max, OfficeSlot* out)
{
	int n;
	int i;
	int start;

	if (group == 0) {
		return 0;
	}
	if (group <= 6) {
		start = 30;
	}
	else if (group == 5) {
		start = 0x2a;
	}
	else {
		return 0;
	}
	n = 0;
	for (i = start - 1; i >= 0 && n < max; i--) {
		if (g_office_role_templates[(unsigned char) ((OfficeSlot*) g_office_slots)[i].role].f4 == group &&
		    gm_LookupEntityRecordById(((OfficeSlot*) g_office_slots)[i].entityId) != 0) {
			out[n++] = ((OfficeSlot*) g_office_slots)[i];
		}
	}
	return n;
}

int __cdecl amt_ListCouncilSlots(int all, int max, OfficeSlot* out)
{
	int n;
	int i;

	n = 0;
	for (i = 30; i < 37; i++) {
		if (n >= max) {
			break;
		}
		if (g_office_role_templates[(unsigned char) ((OfficeSlot*) g_office_slots)[i].role].f4 == 7 &&
		    (all != 0 || ((OfficeSlot*) g_office_slots)[i].entityId != -1)) {
			*out = ((OfficeSlot*) g_office_slots)[i];
			n++;
			out++;
		}
	}
	return n;
}

int __cdecl amt_RankOpenOffices(unsigned char* who, int n, OFFICE_PICK* picks)
{
	int __cdecl amt_GetOfficeAffinity(unsigned char* entity, int role, float* out);
	float score;
	int count;
	int i;
	int j;
	int k;
	int t;
	int found;

	count = 0;
	if (n <= 0) {
		return 0;
	}
	for (j = n - 1; j >= 0; j--) {
		picks[j].score = -100.0f;
		picks[j].type = 0;
		picks[j].rank = 0;
	}
	for (i = 0; i < 30; i++) {
		if (((OfficeSlot*) g_office_slots)[i].state != 3 || ((OfficeSlot*) g_office_slots)[i].count >= 4) {
			continue;
		}
		t = (unsigned char) ((OfficeSlot*) g_office_slots)[i].role;
		if (amt_GetOfficeAffinity(who, t, &score) == 0) {
			continue;
		}
		found = 0;
		for (j = n - 1; j >= 0 && !found; j--) {
			if (picks[j].type == t) {
				found = 1;
			}
		}
		if (found) {
			continue;
		}
		found = 0;
		for (j = n - 1; j >= 0; j--) {
			if (picks[j].rank < (unsigned char) g_office_role_templates[t].f8) {
				continue;
			}
			if (picks[j].rank != (unsigned char) g_office_role_templates[t].f8 || !(picks[j].score <= score)) {
				found = 1;
				break;
			}
		}
		if (j == -1) {
			j = 0;
			if (picks[0].rank < (unsigned char) g_office_role_templates[t].f8 ||
			    (picks[0].rank == (unsigned char) g_office_role_templates[t].f8 && picks[0].score <= score)) {
				found = 1;
			}
		}
		if (found) {
			count++;
			for (k = n - 1; k > j; k--) {
				picks[k] = picks[k - 1];
			}
			picks[j].rank = (unsigned char) g_office_role_templates[t].f8;
			picks[j].score = score;
			picks[j].type = t;
		}
	}
	return count < n ? count : n;
}

int __cdecl amt_RankAllOffices(unsigned char* who, int n, OFFICE_PICK* picks, int* full_out)
{
	int __cdecl amt_GetOfficeAffinity(unsigned char* entity, int role, float* out);
	float score;
	int count;
	int i;
	int j;
	int k;
	int t;
	int found;
	int full;

	count = 0;
	full = 0;
	if (n <= 0) {
		return 0;
	}
	for (j = n - 1; j >= 0; j--) {
		picks[j].score = -100.0f;
		picks[j].type = 0;
		picks[j].rank = 0;
	}
	for (i = 0; i < 30; i++) {
		if (((OfficeSlot*) g_office_slots)[i].state != 3) {
			continue;
		}
		t = (unsigned char) ((OfficeSlot*) g_office_slots)[i].role;
		if (amt_GetOfficeAffinity(who, t, &score) == 0) {
			continue;
		}
		if (((OfficeSlot*) g_office_slots)[i].count >= 4) {
			full = 1;
			continue;
		}
		found = 0;
		for (j = n - 1; j >= 0 && !found; j--) {
			if (picks[j].type == t) {
				found = 1;
			}
		}
		if (found) {
			continue;
		}
		found = 0;
		for (j = n - 1; j >= 0; j--) {
			if (picks[j].rank < (unsigned char) g_office_role_templates[t].f8) {
				continue;
			}
			if (picks[j].rank != (unsigned char) g_office_role_templates[t].f8 || !(picks[j].score <= score)) {
				found = 1;
				break;
			}
		}
		if (j == -1) {
			j = 0;
			if (picks[0].rank < (unsigned char) g_office_role_templates[t].f8 ||
			    (picks[0].rank == (unsigned char) g_office_role_templates[t].f8 && picks[0].score <= score)) {
				found = 1;
			}
		}
		if (found) {
			count++;
			for (k = n - 1; k > j; k--) {
				picks[k] = picks[k - 1];
			}
			picks[j].rank = (unsigned char) g_office_role_templates[t].f8;
			picks[j].score = score;
			picks[j].type = t;
		}
	}
	if (full_out != 0) {
		*full_out = full;
	}
	return count < n ? count : n;
}

void* __cdecl amt_GetRoleHolder(int role)
{
	int i;

	for (i = 0; i < 0x2a; i++) {
		if (((OfficeSlot*) g_office_slots)[i].role == role) {
			return gm_LookupEntityRecordById(((OfficeSlot*) g_office_slots)[i].entityId);
		}
	}
	return 0;
}

void* __cdecl amt_GetSuperiorHolder(int role)
{
	OfficeSlot slot;

	if (role == 0x24) {
		if (amt_GetSlotByRole(0x27, &slot) != 0) {
			return gm_LookupEntityRecordById(slot.entityId);
		}
	}
	else if (role == 0x25 || role == 0x23) {
		if (amt_GetSlotByRole(0x26, &slot) != 0) {
			return gm_LookupEntityRecordById(slot.entityId);
		}
	}
	return 0;
}

int __cdecl amt_IsNextRoleStep(unsigned char* entity, int role)
{
	OFFICE_ROLE_TEMPLATE want;
	OFFICE_ROLE_TEMPLATE held;
	int a;
	int b;

	if (role == 0 || role > 0x1b) {
		return 0;
	}
	if (amt_GetRoleTemplate(role, &want) == 0) {
		return 0;
	}
	if (amt_GetRoleTemplate(entity[0x166], &held) == 0) {
		return 0;
	}
	if (want.f4 != held.f4) {
		return 0;
	}
	a = (want.f8 & 0xff) % 3;
	b = (held.f8 & 0xff) % 3;
	if (a == 0 && b != 0) {
		return 1;
	}
	if (a == 2 && b == 0) {
		return 1;
	}
	if (a == 1 && b == 2) {
		return 1;
	}
	return 0;
}

int __cdecl amt_HasIdleSuperior(int role)
{
	OFFICE_ROLE_TEMPLATE tmpl;
	OfficeSlot list[6];
	int n;
	int i;
	unsigned char* e;

	if (amt_GetRoleTemplate(role, &tmpl) == 0) {
		return 0;
	}
	n = amt_ListSlotsOfGroup(tmpl.f4, 6, list);
	if (n == 0) {
		return 0;
	}
	for (i = 0; i < n; i++) {
		e = gm_LookupEntityRecordById(list[i].entityId);
		if (e != 0 && amt_IsNextRoleStep(e, role) != 0 && e[0x1b1] == 0) {
			return 1;
		}
	}
	return 0;
}

int __cdecl amt_ListSuperiors(int role, int max, unsigned char** out)
{
	OFFICE_ROLE_TEMPLATE tmpl;
	OfficeSlot list[6];
	int n;
	int i;
	int cnt;
	unsigned char* e;

	if (amt_GetRoleTemplate(role, &tmpl) == 0) {
		return 0;
	}
	n = amt_ListSlotsOfGroup(tmpl.f4, max < 6 ? max : 6, list);
	if (n == 0) {
		return 0;
	}
	n = n < max ? n : max;
	cnt = 0;
	for (i = 0; i < n; i++) {
		e = gm_LookupEntityRecordById(list[i].entityId);
		if (e != 0 && amt_IsNextRoleStep(e, role) != 0) {
			out[cnt++] = e;
		}
	}
	return cnt;
}

int __cdecl amt_ListPromotionRoles(unsigned char* entity, int max, int* out)
{
	OFFICE_ROLE_TEMPLATE tmpl;
	OfficeSlot list[6];
	int want;
	int n;
	int i;
	int cnt;
	int role;
	int level;

	if (entity[0x166] == 0) {
		return 0;
	}
	if (amt_GetRoleTemplate(entity[0x166], &tmpl) == 0) {
		return 0;
	}
	n = amt_ListSlotsOfGroup(tmpl.f4, 6, list);
	if (n == 0) {
		return 0;
	}
	want = (tmpl.f8 & 0xff) % 3 == 1 ? 0 : (tmpl.f8 & 0xff) - 1;
	cnt = 0;
	for (i = 0; i < n && cnt < max; i++) {
		if (list[i].state == 3) {
			role = (unsigned char) list[i].role;
			amt_GetRoleTemplate(role, &tmpl);
			level = tmpl.f8 & 0xff;
			if (level % 3 == 0) {
				out[cnt++] = role;
			}
			else if (want == level) {
				out[cnt++] = role;
				if (tmpl.f10 != 0) {
					break;
				}
			}
		}
	}
	return cnt;
}

void __cdecl amt_ExpandSlots(int count, OfficeSlot* p)
{
	int i;

	for (i = 0; i < count; i++) {
		p[i] = ((OfficeSlot*) g_office_slots)[(unsigned char) p[i].type];
	}
}

int __cdecl amt_FindVacantRoleBelow(int role)
{
	OfficeSlot slot;

	if (role == 0) {
		return 0;
	}
	if (role >= 0x1b) {
		role = 0x1b;
	}
	while (role > 0) {
		if (amt_GetSlotByRole(role, &slot) != 0 && slot.state == 3 && slot.count <= 1) {
			break;
		}
		role--;
	}
	return role;
}

/* Client-only (TL 0x4e9580, discarded): the fixed limits of a role's rank (the template's +8 byte,
 * 1..9); 0 for an unknown role or rank. No server code reads the record. */
typedef struct {
	short lo;
	short hi;
	int cost_lo;
	int cost_hi;
	int a;
	int b;
	int c;
	int d;
} OFFICE_RANK_LIMITS;

int __cdecl amt_GetRankLimits(int role, OFFICE_RANK_LIMITS* out)
{
	OFFICE_ROLE_TEMPLATE tmpl;

	if (amt_GetRoleTemplate(role, &tmpl) == 0) {
		return 0;
	}
	switch ((unsigned char) tmpl.f8) {
	case 1:
	case 2:
		out->lo = 0x10;
		out->hi = 0x14;
		out->cost_lo = 0x9c400;
		out->cost_hi = 0x138800;
		out->a = 3;
		out->b = 4;
		out->c = 2;
		out->d = 3;
		return 1;
	case 3:
	case 4:
		out->lo = 0x14;
		out->hi = 0x18;
		out->cost_lo = 0x138800;
		out->cost_hi = 0x1d4c00;
		out->a = 4;
		out->b = 5;
		out->c = 3;
		out->d = 4;
		return 1;
	case 5:
		out->lo = 0x18;
		out->hi = 0x1c;
		out->cost_lo = 0x1d4c00;
		out->cost_hi = 0x271000;
		out->a = 5;
		out->b = 6;
		out->c = 3;
		out->d = 4;
		return 1;
	case 6:
		out->lo = 0x18;
		out->hi = 0x1c;
		out->cost_lo = 0x222e00;
		out->cost_hi = 0x30d400;
		out->a = 6;
		out->b = 7;
		out->c = 3;
		out->d = 5;
		return 1;
	case 7:
	case 8:
	case 9:
		out->lo = 0x1c;
		out->hi = 0x20;
		out->cost_lo = 0x30d400;
		out->cost_hi = 0x493e00;
		out->a = 7;
		out->b = 8;
		out->c = 5;
		out->d = 6;
		return 1;
	}
	return 0;
}

int __cdecl amt_ListRolesOfLevel(int level, int max, int* out)
{
	OFFICE_ROLE_TEMPLATE tmpl;
	int i;
	int n;
	int role;

	if (max < 1) {
		return 0;
	}
	n = 0;
	for (i = 0; i < 0x1c && n < max; i++) {
		role = (unsigned char) ((OfficeSlot*) g_office_slots)[i].role;
		amt_GetRoleTemplate(role, &tmpl);
		if ((unsigned char) tmpl.f8 == level) {
			out[n++] = role;
		}
	}
	return n;
}

int __cdecl amt_GetRoleLevel(int role)
{
	OFFICE_ROLE_TEMPLATE tmpl;

	amt_GetRoleTemplate(role, &tmpl);
	return tmpl.f8 & 0xff;
}

int __cdecl amt_GetGroupVacancyFlags(int group)
{
	extern char g_entity_state_base[2];
	extern char g_dynamic_entities[];
	OfficeSlot list[6];
	unsigned char* holder;
	unsigned char* setter;
	unsigned char* e;
	int flags;
	int n;
	int i;
	int j;

	flags = 0;
	n = amt_ListSlotsOfGroup(group, 6, list);
	for (i = 0; i < n; i++) {
		if (list[i].state == 2) {
			holder = gm_LookupEntityRecordById(list[i].assignmentId);
			setter = gm_LookupEntityRecordById(list[i].entityId);
			if (holder == 0 || holder[8] == 0 || holder[0x1b1] != 0 || setter == 0 || setter[8] == 0) {
				continue;
			}
			for (j = 0; j < n; j++) {
				if (list[j].entityId == list[i].assignmentId) {
					flags |= 1;
					break;
				}
			}
		}
		else if (list[i].state == 3 && list[i].count > 0) {
			for (e = (unsigned char*) g_entity_state_base; e < (unsigned char*) g_dynamic_entities; e += 0x21c) {
				if (e[0x166] == (unsigned char) list[i].role) {
					flags |= 1;
					if ((e[0] == 6 || e[0] == 7) && e[0x1af] == 0) {
						flags |= 2;
						break;
					}
				}
			}
		}
	}
	if (flags & 1) {
		for (i = 0; i < n; i++) {
			e = gm_LookupEntityRecordById(list[i].entityId);
			if (e != 0 && (e[2] == 6 || e[2] == 7) && e[0x1b1] == 0) {
				flags |= 2;
				break;
			}
		}
	}
	return (flags & 2) >> 1;
}

int __cdecl amt_IsPendingAssignment(int group, char* slot)
{
	OfficeSlot list[6];
	int n;
	int i;
	unsigned char* a;
	unsigned char* b;

	if (slot[0x10] != 2) {
		return 0;
	}
	n = amt_ListSlotsOfGroup(group, 6, list);
	a = gm_LookupEntityRecordById(*(int*) (slot + 0x14));
	b = gm_LookupEntityRecordById(*(int*) (slot + 4));
	if (a == 0 || a[8] == 0 || a[0x1b1] != 0 || b == 0 || b[8] == 0) {
		return 0;
	}
	for (i = 0; i < n; i++) {
		if (list[i].entityId == *(int*) (slot + 0x14)) {
			return 1;
		}
	}
	return 0;
}

int __cdecl amt_HasCouncilHolder(void)
{
	int left;
	int i;

	left = 7;
	for (i = 36; i != 0 && left != 0; i--) {
		if (g_office_role_templates[(unsigned char) ((OfficeSlot*) g_office_slots)[i].role].f4 == 7) {
			if (((OfficeSlot*) g_office_slots)[i].entityId != -1) {
				if (gm_LookupEntityRecordById(((OfficeSlot*) g_office_slots)[i].entityId) != 0) {
					return 1;
				}
			}
			else {
				left--;
			}
		}
	}
	return 0;
}

/* Updates entity links for an office assignment. Sets up
 * the bidirectional references between the office slot and
 * the entity holding it. */

void __cdecl amt_UpdateEntityLinks(char* entity, int arg2)
{
	OfficeSlot* slot;
	unsigned short default_val;
	int i;
	int result;

	default_val = (unsigned short) g_current_hour;
	result = 0;
	slot = (OfficeSlot*) g_office_slots;
	for (i = 0; i < 0x2a; i++) {
		if (slot[i].entityId == *(int*) (entity + 4) && arg2 != 0) {
			slot[i].entityId = -1;
			slot[i].assignmentId = -1;
			slot[i].state = (default_val > 0xb) ? 4 : 3;
			slot[i].count = 0;
			result |= 1;
		}
		else if (slot[i].assignmentId == *(int*) (entity + 4)) {
			slot[i].assignmentId = -1;
			slot[i].state = 1;
		}
	}
	if (*(char*) (entity + 0x168) != 0) {
		for (i = 0; i < 0x2a; i++) {
			if (slot[i].role == *(char*) (entity + 0x168)) {
				if (slot[i].count > 0) {
					slot[i].count--;
					result |= 1;
				}
			}
		}
	}
	if (arg2 != 0) {
		*(char*) (entity + 0x166) = 0;
		*(char*) (entity + 0x169) = 0;
	}
	*(char*) (entity + 0x168) = 0;
}

/* Client-only building-upgrade checks (discarded; see the block above). */

int __cdecl amt_CanUpgradeBuildingTier1(char* building)
{
	unsigned char kind;

	kind = *(unsigned char*) (building + 0x169);
	if (kind < 0x1e || kind > 0x21) {
		return 0;
	}
	if ((*(int*) (building + 0x1c8) & 0x4000000) != 0) {
		return -1;
	}
	if (*(int*) (building + 0x194) < 3) {
		return -2;
	}
	return 1;
}

int __cdecl amt_CanUpgradeBuildingTier2(unsigned char* building)
{
	extern char* g_entity_type_table;
	unsigned char* __cdecl gm_StartFilteredEntitySearch(int a, int b, int kind);
	unsigned char* hit;
	int kind;

	if (building[0x169] < 0x1e || building[0x169] > 0x21) {
		return 0;
	}
	switch (building[0x169]) {
	case 0x1f:
		kind = 0x18;
		break;
	case 0x20:
		kind = 0x19;
		break;
	case 0x21:
		kind = 0x1a;
		break;
	case 0x1e:
		kind = 0x17;
		break;
	default:
		return 0;
	}
	hit = gm_StartFilteredEntitySearch(1, 5, kind);
	if (hit == 0 || (hit[0x5a] & 1) != 0) {
		return 0;
	}
	if ((unsigned char) g_entity_type_table[*hit * 0x24d + 0x247] < 2) {
		return 0;
	}
	if (*(unsigned int*) (building + 0x1c8) & 0x8000000) {
		return -1;
	}
	return *(int*) (building + 0x194) < 5 ? -2 : 1;
}

int __cdecl amt_CanUpgradeBuildingTier3(unsigned char* building)
{
	extern char* g_entity_type_table;
	unsigned char* __cdecl gm_StartFilteredEntitySearch(int a, int b, int kind);
	unsigned char* hit;
	int kind;

	if (building[0x169] < 0x1e || building[0x169] > 0x21) {
		return 0;
	}
	switch (building[0x169]) {
	case 0x1f:
		kind = 0x18;
		break;
	case 0x20:
		kind = 0x19;
		break;
	case 0x21:
		kind = 0x1a;
		break;
	case 0x1e:
		kind = 0x17;
		break;
	default:
		return 0;
	}
	hit = gm_StartFilteredEntitySearch(1, 5, kind);
	if (hit == 0 || (hit[0x5a] & 1) != 0) {
		return 0;
	}
	if ((unsigned char) g_entity_type_table[*hit * 0x24d + 0x247] < 3) {
		return 0;
	}
	if (*(unsigned int*) (building + 0x1c8) & 0x10000000) {
		return -1;
	}
	return *(int*) (building + 0x194) < 8 ? -2 : 1;
}

/* Client-only (TL 0x4ec410, discarded): writes the 42 office slots that amt_fio_LoadAemter reads. The
 * client formats the count message and drops it; its log macro compiles to nothing there. */
int __cdecl amt_fio_SaveAemter(void* file)
{
	extern unsigned int __cdecl vfs_fwrite(void* buf, int size, int count, char* stream);
	int count;
	char msg[0x100];
	int i;

	count = 0x2a;
	if (file == 0) {
		return 0;
	}
	if (!vfs_fwrite(&count, 4, 1, file)) {
		return 0;
	}
	sprintf(msg, "amt_fio_SaveAemter(): count is %i", count);
	for (i = 0; i < 0x2a; i++) {
		if (!vfs_fwrite(&((OFFICE_SLOT*) g_office_slots)[i].id, 1, 1, file)) {
			return 0;
		}
		if (!vfs_fwrite(&((OFFICE_SLOT*) g_office_slots)[i].mplayerid, 4, 1, file)) {
			return 0;
		}
		if (!vfs_fwrite(&((OFFICE_SLOT*) g_office_slots)[i].mamt, 1, 1, file)) {
			return 0;
		}
		if (!vfs_fwrite(&((OFFICE_SLOT*) g_office_slots)[i].pcount, 4, 1, file)) {
			return 0;
		}
		if (!vfs_fwrite(&((OFFICE_SLOT*) g_office_slots)[i].status, 1, 1, file)) {
			return 0;
		}
		if (!vfs_fwrite(&((OFFICE_SLOT*) g_office_slots)[i].msetter, 4, 1, file)) {
			return 0;
		}
	}
	return 1;
}

/* Validates if an entity is eligible for an office position.
 * Checks entity type, existing office holdings, and eligibility
 * requirements. Returns 0 on success, non-zero on failure. */

/* Game function - entity role/assignment table manager */
/* Updates a 0x18-byte record table at 0x101de5a0, clears old roles, sets new assignments */

/* Byte-match note: RELOC 836/836.  Two levers, in the high-role block:
 *
 * The ecx/edx naming residue: spelling the clear as `*scan & ~mask` inline,
 * instead of hoisting `neg_mask = ~mask` into a local, puts role_ch in cl and
 * the mask in edx as the reference does (826 -> 829).
 *
 * The preheader order (`not edx; mov eax,0x10035a6c`, where a pointer-cursor
 * loop emits `mov eax,0x10035a6c; not edx`): counting rows and spelling the
 * address as `0x10035a6c + row * 0x21c` gives msvc6 a multiply to strength-
 * reduce, and it then materialises the negated mask before the table base.
 * The `while ((int) scan < 0x1009ae6c)` bound became `row < 768` (the table is
 * 768 rows of 0x21c: 0x1009ae6c - 0x10035a6c = 0x65400 = 768 * 0x21c).
 * A byte-offset counter (`off += 0x21c`, `off < 0x65400`) also emits the `not`
 * first, but recomputes the bound with a `lea`/`cmp` pair against 0x65400 and
 * is longer.
 *
 * Dead ends on the pointer-cursor shape, all 829/836: for/while/do-while loop
 * forms, `&=` vs explicit and, `~mask` on either operand side, `mask ^ -1`,
 * `mask ^ 0xffffffff`, char / unsigned int / int pointer cursors, `scan +=
 * 0x87`, scan declared before, after, and outside the mask block, an unsigned
 * mask, an unsigned loop bound, a load/modify/store body with an explicit
 * temp, advancing the cursor before the store to mirror the target's
 * `[eax-0x21c]` write-back, a dead `~mask` consumer before the loop, a scan
 * base spelled `0x1009ae6c - 0x65400`, and a separate row counter beside the
 * pointer cursor.  Regressions: an end-pointer local (828), hoisting `~mask`
 * into a local or the for-init (826), negating mask in place before the loop
 * (826), an index-only walk (817/843, wrong size), a volatile mask read
 * (740/851), a switch over role_ch (jump table, 740/836), and assigning mask
 * before the flag store in each arm (755/836).
 *
 * The earlier note that the preheader order and the mask register were one
 * inseparable decision held only for the pointer-cursor shapes probed then:
 * every one that emitted `not` first also moved the mask to ecx.  The row
 * multiply emits `not` first while keeping the mask in esi/edx, so the two are
 * separable after all. */

int __cdecl amt_fio_LoadAemter(int streamCtx, int version)
{
	int value;
	char msg[0x100];
	unsigned int count;
	unsigned int i;

	count = (version >= 0x10051) ? 0x2a : 0x25;

	srv_InitBuildingTypeTable();

	if (streamCtx == 0)
		return 0;

	if (!ls_ReadVfsDataChecked(&value, 4, 1, streamCtx)) {
		LogMessageInternal("D:\\Develop\\DieGildeAddOn\\game\\aemter.c", 0xe73,
		                   "amt_fio_LoadAemter(): Can't load count", 1);
		return 0;
	}
	if (value != (int) count) {
		sprintf(msg, "amt_fio_LoadAemter(): count read is %i, expected %i",
		        value, 0x2a);
		LogMessageInternal("D:\\Develop\\DieGildeAddOn\\game\\aemter.c", 0xe7c,
		                   msg, 1);
		return 0;
	}
	for (i = 0; i < count; i++) {
		if (!ls_ReadVfsDataChecked(&((OFFICE_SLOT*) g_office_slots)[i].id, 1, 1, streamCtx)) {
			LogMessageInternal("D:\\Develop\\DieGildeAddOn\\game\\aemter.c", 0xe82,
			                   "amt_fio_LoadAemter(): Can't load id", 1);
			return 0;
		}
		if (!ls_ReadVfsDataChecked(&((OFFICE_SLOT*) g_office_slots)[i].mplayerid, 4, 1, streamCtx)) {
			LogMessageInternal("D:\\Develop\\DieGildeAddOn\\game\\aemter.c", 0xe83,
			                   "amt_fio_LoadAemter(): Can't load mplayerid", 1);
			return 0;
		}
		if (!ls_ReadVfsDataChecked(&((OFFICE_SLOT*) g_office_slots)[i].mamt, 1, 1, streamCtx)) {
			LogMessageInternal("D:\\Develop\\DieGildeAddOn\\game\\aemter.c", 0xe84,
			                   "amt_fio_LoadAemter(): Can't load mamt", 1);
			return 0;
		}
		if (!ls_ReadVfsDataChecked(&((OFFICE_SLOT*) g_office_slots)[i].pcount, 4, 1, streamCtx)) {
			LogMessageInternal("D:\\Develop\\DieGildeAddOn\\game\\aemter.c", 0xe85,
			                   "amt_fio_LoadAemter(): Can't load pcount", 1);
			return 0;
		}
		if (!ls_ReadVfsDataChecked(&((OFFICE_SLOT*) g_office_slots)[i].status, 1, 1, streamCtx)) {
			LogMessageInternal("D:\\Develop\\DieGildeAddOn\\game\\aemter.c", 0xe86,
			                   "amt_fio_LoadAemter(): Can't load status", 1);
			return 0;
		}
		if (!ls_ReadVfsDataChecked(&((OFFICE_SLOT*) g_office_slots)[i].msetter, 4, 1, streamCtx)) {
			LogMessageInternal("D:\\Develop\\DieGildeAddOn\\game\\aemter.c", 0xe87,
			                   "amt_fio_LoadAemter(): Can't load msetter", 1);
			return 0;
		}
	}
	return 1;
}

/* Client-only town-hall helpers (discarded; see the blocks above). */

void* __cdecl amt_GetTownHallHolder(unsigned char* building)
{
	extern char* g_entity_type_table;
	int* office;

	if (g_entity_type_table[building[0] * 0x24d] == 0x1e) {
		office = *(int**) (building + 0x65);
		if (office != 0) {
			return gm_LookupEntityRecordById(*office);
		}
	}
	/* placeholder: inferred server log call, see msvc6-link-layout 5f */
	LogMessageInternal("D:\\Develop\\DieGildeAddOn\\game\\aemter.c", __LINE__, "amt_GetTownHallHolder(): no town hall office", 1);
	return 0;
}

int __cdecl amt_CountTownHallSeats(char* entity)
{
	int __cdecl ahm_CheckFlag(void* entity);
	char* seats;
	int i;
	int n;

	if (ahm_CheckFlag(entity) == 0) {
		return 0;
	}
	n = 0;
	seats = *(char**) (*(char**) (entity + 0x16c) + 0x65);
	for (i = 0; i < 6; i++) {
		if (*(int*) (seats + 0xc + i * 8) != 0) {
			n++;
		}
	}
	return n;
}

/* 0x101de5a0 */

/* Nothing reads this table; it opens the TU's data (8-aligned, so the
 * link pads four bytes ahead of it). */
