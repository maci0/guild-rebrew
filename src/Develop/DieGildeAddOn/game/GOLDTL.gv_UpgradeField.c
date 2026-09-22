#include "rebrew_types.h"
#include "rebrew_globals.h"

// FUNCTION: GOLDTL 0x4f2060
// SIZE: 560

int __cdecl gv_AllocGraveyardField(unsigned char* field);
void __cdecl gv_FreeFieldAllocs(int* slot);

/* Client (GOLDTL) twin: same shape as the server build, but the old field
 * allocation is released by gv_FreeFieldAllocs (0x4f2290, frees +0x1c/+0x20),
 * not by gv_Free3Fields (0x45b790, frees +0x24/+0x28).
 *
 * Upgrades a graveyard field to the next maturity level: allocates a new
 * field slot via gv_AllocGraveyardField, copies the worker data across, then
 * frees the old allocation.  Returns the new field data pointer.
 *
 * RELOC, 570/570. Four shapes were needed together; each is noted at its
 * site below:
 *   - the old_alloc read hoisted above the entry-type guard, which pushes edi
 *     with the other callee-saves and puts the guard zero in it,
 *   - the third counter homed in a plain (not volatile) 4-dword array, which
 *     both reserves the target's `sub esp,0x10` frame and leaves the store
 *     reorderable into the first memcpy's setup,
 *   - the shared 0x88 element count of the last memcpy named in a local, which
 *     stops a tail merge that folded 8 bytes out of the two arms,
 *   - the copy loops written as `while` over a row counter with an explicit
 *     `* 0x14`, which fixes both the SIB base/index roles and the order of the
 *     preheader's two initializations.
 */

int __cdecl gv_UpgradeField(unsigned char* field)
{
	unsigned char* entry;
	void* old_alloc;
	void* new_alloc;
	int maturity;
	int level;
	int type;
	int count8;
	int countc;
	/* The third counter is homed in memory, not a register: the target stores
	 * it to [esp+0x18] (0x10010d8c / 0x10010dc0) and reloads it once at
	 * 0x10010ec2. Taking the address of a 4-dword array forces the home and
	 * reserves the target's `sub esp,0x10` frame; a lone `volatile int` homes
	 * the value but reserves only one dword, and with the do/while copy loops
	 * register pressure is low enough that the frame then collapses to
	 * `push ecx`. Element [2] lands at [esp+0x18] under the four callee-save
	 * pushes.
	 *
	 * Plain, not volatile: volatile also pins the ordering, which blocks the
	 * scheduler from interleaving the store into the first memcpy's setup and
	 * forces a second load for the third loop's guard (LCS 177 against 185). */
	int slot[4];
	int* count10;
	int n10;
	int last_n;
	int i;
	int row;

	/* All four guard failures and the failed-alloc path share one epilogue in
	 * the target (0x10010d70), so they share one `goto fail` here.
	 *
	 * The old_alloc read is hoisted above the entry-type guard and the type
	 * byte is named, which is what puts `mov ebx,[ebp+0x65]` next to
	 * `mov cl,[ebp]` at 0x10010d23 and pushes edi with the other
	 * callee-saves, so the constant 0 lands in edi (0x10010d40). */
	count10 = &slot[2];
	type = field[0];
	old_alloc = *(void**) (field + 0x65);
	entry = (unsigned char*) (g_entity_type_table + type + type * 588);
	if (entry[0] != 0x1d)
		goto fail;
	if (old_alloc == 0)
		goto fail;
	level = *(int*) ((char*) old_alloc + 4);
	if (level >= 3)
		goto fail;
	maturity = entry[0x247];
	if (maturity - level != 1)
		goto fail;
	*(void**) (field + 0x65) = 0;
	new_alloc = gv_AllocGraveyardField(field);
	if (new_alloc == 0) {
		*(void**) (field + 0x65) = old_alloc;
		goto fail;
	}
	/* Re-read rather than reuse `maturity`: the target loads
	 * [esi+0x247] a second time at 0x10010d7a. */
	/* Both arms end in the same four instructions
	 * (`mov ecx,0x88` / two pointer loads / `rep movsd`), but the target
	 * cross-jumps only the last two, joining at 0x10010dfc and keeping
	 * `mov ecx,0x88` and one pointer load duplicated per arm. Naming the
	 * shared 0x88 element count in a local stops the deeper tail merge that
	 * otherwise folds all four and costs 8 bytes. */
	last_n = 0x88;
	if (entry[0x247] == 2) {
		count8 = 8;
		countc = 4;
		*count10 = 0;
		memcpy(*(void**) (*(char**) ((char*) new_alloc + 8) + 0x10),
		       *(void**) (*(char**) ((char*) old_alloc + 8) + 0x10), 0x88 * 4);
		memcpy(*(void**) (*(char**) ((char*) new_alloc + 0xc) + 0x10),
		       *(void**) (*(char**) ((char*) old_alloc + 0xc) + 0x10), last_n * 4);
	} else {
		count8 = 0xc;
		countc = 6;
		*count10 = 2;
		memcpy(*(void**) (*(char**) ((char*) new_alloc + 8) + 0x10),
		       *(void**) (*(char**) ((char*) old_alloc + 8) + 0x10), 0xcc * 4);
		memcpy(*(void**) (*(char**) ((char*) new_alloc + 0xc) + 0x10),
		       *(void**) (*(char**) ((char*) old_alloc + 0xc) + 0x10), 0xcc * 4);
		memcpy(*(void**) (*(char**) ((char*) new_alloc + 0x10) + 0x10),
		       *(void**) (*(char**) ((char*) old_alloc + 0x10) + 0x10), last_n * 4);
	}
	/* Byte-offset stride with a separate count decremented to zero, not
	 * `i * 0x14` off a signed compare: that is what emits the target's
	 * `add esi,0x14` / `dec edi` / `jne` back edge at 0x10010e58. */
	if (((char**) old_alloc)[2] != 0 && count8 > 0) {
		row = 0;
		i = count8;
		while (i != 0) {
			*(int*) (((char**) new_alloc)[2] + row * 0x14) =
			    *(int*) (((char**) old_alloc)[2] + row * 0x14);
			*(int*) (((char**) new_alloc)[2] + row * 0x14 + 4) =
			    *(int*) (((char**) old_alloc)[2] + row * 0x14 + 4);
			*(unsigned short*) (((char**) new_alloc)[2] + row * 0x14 + 8) =
			    *(unsigned short*) (((char**) old_alloc)[2] + row * 0x14 + 8);
			*(unsigned short*) (((char**) new_alloc)[2] + row * 0x14 + 0xa) =
			    *(unsigned short*) (((char**) old_alloc)[2] + row * 0x14 + 0xa);
			*(unsigned char*) (((char**) new_alloc)[2] + row * 0x14 + 0xc) =
			    *(unsigned char*) (((char**) old_alloc)[2] + row * 0x14 + 0xc);
			row++;
			i--;
		}
	}
	if (((char**) old_alloc)[3] != 0 && countc > 0) {
		row = 0;
		i = countc;
		while (i != 0) {
			*(int*) (((char**) new_alloc)[3] + row * 0x14) =
			    *(int*) (((char**) old_alloc)[3] + row * 0x14);
			*(int*) (((char**) new_alloc)[3] + row * 0x14 + 4) =
			    *(int*) (((char**) old_alloc)[3] + row * 0x14 + 4);
			*(unsigned short*) (((char**) new_alloc)[3] + row * 0x14 + 8) =
			    *(unsigned short*) (((char**) old_alloc)[3] + row * 0x14 + 8);
			*(unsigned short*) (((char**) new_alloc)[3] + row * 0x14 + 0xa) =
			    *(unsigned short*) (((char**) old_alloc)[3] + row * 0x14 + 0xa);
			*(unsigned char*) (((char**) new_alloc)[3] + row * 0x14 + 0xc) =
			    *(unsigned char*) (((char**) old_alloc)[3] + row * 0x14 + 0xc);
			row++;
			i--;
		}
	}
	/* One read, not two: the target loads the home into edi at 0x10010ec2 and
	 * uses that single value for both the guard and the loop counter. */
	n10 = *count10;
	if (((char**) old_alloc)[4] != 0 && n10 > 0) {
		row = 0;
		i = n10;
		while (i != 0) {
			*(int*) (((char**) new_alloc)[4] + row * 0x14) =
			    *(int*) (((char**) old_alloc)[4] + row * 0x14);
			*(int*) (((char**) new_alloc)[4] + row * 0x14 + 4) =
			    *(int*) (((char**) old_alloc)[4] + row * 0x14 + 4);
			*(unsigned short*) (((char**) new_alloc)[4] + row * 0x14 + 8) =
			    *(unsigned short*) (((char**) old_alloc)[4] + row * 0x14 + 8);
			*(unsigned short*) (((char**) new_alloc)[4] + row * 0x14 + 0xa) =
			    *(unsigned short*) (((char**) old_alloc)[4] + row * 0x14 + 0xa);
			*(unsigned char*) (((char**) new_alloc)[4] + row * 0x14 + 0xc) =
			    *(unsigned char*) (((char**) old_alloc)[4] + row * 0x14 + 0xc);
			row++;
			i--;
		}
	}
	((char*) new_alloc)[0x18] = ((char*) old_alloc)[0x18];
	((char*) new_alloc)[0x19] = ((char*) old_alloc)[0x19];
	((char*) new_alloc)[0x1a] = ((char*) old_alloc)[0x1a];
	((char*) new_alloc)[0x1b] = ((char*) old_alloc)[0x1b];
	gv_FreeFieldAllocs((int*) old_alloc);
	return *(int*) (field + 0x65);

fail:
	return 0;
}

