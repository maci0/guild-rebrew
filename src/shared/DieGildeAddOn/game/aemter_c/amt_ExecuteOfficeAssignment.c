// FUNCTION: SERVER 0x1000b4d0
#include "../../../Units/Error/error.h"
#include "../office_slot.h"

extern char g_office_slots[]; /* 0x101de5a0 */
void* __cdecl gm_LookupEntityRecordById(int);
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
			if (*(unsigned char*) ((unsigned char) ((OfficeSlot*) g_office_slots)[record_index].role * 0x18 + 0x10029bc0) >=
			    *(unsigned char*) (*(unsigned char*) (ent + 0x166) * 0x18 + 0x10029bc0)) {
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
			if (*(int*) ((unsigned int) (unsigned char) ((OfficeSlot*) g_office_slots)[record_index].role * 0x18 + 0x10029bc8) != 0) {
				unsigned char* scan;
				k = 0;
				scan = (unsigned char*) 0x101de5a8;

				while ((int) scan < 0x101de878) {
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
				scan = (int*) 0x101de874;
				do {
					if (*(char*) ((char*) scan + 4) == *(char*) (ent + 0x169) && *scan == *(int*) (ent + 4)) {
						*scan = -1;
					}
					scan = (int*) ((char*) scan + 0x18);
				} while ((int) scan < 0x101de91c);
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
				int row;
				row = 0;
				do {
					*(int*) (0x10035a6c + row * 0x21c) =
						*(int*) (0x10035a6c + row * 0x21c) & ~mask;
					row++;
				} while (row < 768);
			}
		}
		goto final_store;
	}
}