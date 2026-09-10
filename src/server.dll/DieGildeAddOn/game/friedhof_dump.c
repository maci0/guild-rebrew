/* friedhof_logic TU - proper C (aggregate of the per-function files). */

// CFLAGS: /O2 /Gd

int g_file_version;
// FUNCTION: SERVER 0x10010530
// SIZE: 113

int __cdecl gv_CheckSlotActive(void* slot, int type)
{
	if (type == 0) {
		if (*(int*) ((char*) slot + 8) != 0 && *(unsigned char*) ((char*) slot + 0x18) != 0)
			return 1;
		return 0;
	}
	if (type == 1) {
		if (*(int*) ((char*) slot + 0xc) != 0 && *(unsigned char*) ((char*) slot + 0x19) != 0)
			return 1;
		return 0;
	}
	if (type == 2) {
		if (*(int*) ((char*) slot + 0x10) != 0 && *(unsigned char*) ((char*) slot + 0x1a) != 0)
			return 1;
		return 0;
	}
	if (type == 3) {
		if (*(int*) ((char*) slot + 0x14) != 0 && *(unsigned char*) ((char*) slot + 0x1b) != 0)
			return 1;
		return 0;
	}
	return 1;
}

// FUNCTION: SERVER 0x10010d10
// SIZE: 570

extern void __cdecl m_FreeTracked(void* ptr);
extern char* g_entity_type_table; /* 0x100A8C30 */
int __cdecl AllocGraveyardField(unsigned char* field);
void __cdecl gv_Free3Fields(int* slot);

/* Upgrades a graveyard field to the next maturity level: allocates a new
 * field slot via AllocGraveyardField, copies the worker data across, then
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

int __cdecl UpgradeGraveyardField(unsigned char* field)
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
	new_alloc = AllocGraveyardField(field);
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
	gv_Free3Fields((int*) old_alloc);
	return *(int*) (field + 0x65);

fail:
	return 0;
}


// FUNCTION: SERVER 0x10011940
// SIZE: 674

extern unsigned short* g_entity_table_end;
extern int g_next_object_id;
extern int g_current_year;
extern int g_1002574c[];
extern float table_1002572c[];
extern unsigned short g_entity_slot_table[];
extern unsigned char g_current_season;
int __cdecl gm_ResolveEntityById(void** dynamic, void** existing, void** static_ptr, int entity_id);
int __cdecl gv_CheckSlotActive(void* slot, int type);
void* __cdecl GetSlotEntry(void* worker, int worktype, unsigned char job);
void* __cdecl FindSlotEntryFiltered(void* filter_arg, void* entity, void* cursor,
                                    void* filter, int type);
int __cdecl gm_SubObjektNoKill(int a, int b, int c);
int __cdecl gm_AddOrAccumulateObject(int a, int b, int c);
int __cdecl _ftol(void);

/* Moves a graveyard worker's slot entry to the field it currently works
 * in: finds the source entry and a free destination slot, copies the
 * entry across, clears the source, and accumulates the produced goods
 * for the current season.
 *
 * The loop walks the destination region for a free (-1) slot, then migrates
 * the source entry there (rep movsd / rep stosd). Each cursor is bounded by
 * its own end pointer, and occupied source entries are skipped by advancing
 * src against src_end (0x10011ac4), not by advancing dst against src.
 *
 * The first gm_ResolveEntityById receives (0, 0, &a, id); the out-param
 * reuses the arg-1 slot, hence the `cmd = a` register copy.
 *
 * RELOC 674/674. What closed the bulk:
 * the 0x1003546c guard read an undeclared `g_1003546c` instead of
 * `g_entity_table_end`; the three -1 guards are one `||` chain, not three
 * separate `goto`s; the source bound g_1002574c[cmd+8] is computed before
 * the FindSlotEntryFiltered call and spilled (0x10011a4d); the post-loop
 * move clears the source entry and fills the destination, not both on
 * found2 (0x10011b0d-0x10011b3e); 0xff lives in one register across the
 * byte and word stores (0x10011b32); the ftol result is a plain cast of a
 * re-read field, not a pushed double (0x10011b7c); the +0x27 index at the
 * gm_AddOrAccumulateObject call site reads rec2 via the [esp+0x1c] reload
 * (0x10011bb1).
 *
 * The last 12 bytes were the skip loop's back edge. Every earlier attempt
 * kept the copy OUTSIDE the skip loop, reached by `goto copy` or by falling
 * out of it, which forces msvc6 to re-test `*src` on the back edge
 * (`cmp [ebx],-1` / `je`, 3 bytes) or to peel a `cmp ebx,ecx` / `jae` pair
 * above it. Measured: do/while 434, explicit goto back edge 434, peeled
 * test 434, no pre-guard 435, bound test hoisted inside `for(;;)` 435 at
 * obj 670, `*(volatile int*)` on the value test 420, short-circuit
 * `while (src < end && *src == -1)` 437 at obj 670.
 *
 * What closes it: put the copy INSIDE the skip loop and leave by `break`.
 * `while (src < src_end) { if (*src != -1) { copy; break; } src += 0x11; }`
 * gives the loop exactly one test per iteration at the top, so the back
 * edge carries nothing and msvc6 emits the target's bare `jmp 0x10011ac4`
 * (0x10011ad0). The `if (src >= src_end) goto done;` after the loop is the
 * shared exit at 0x10011afc. Verified on a standalone probe before editing:
 * the emitted opcode lengths match the target byte for byte.
 *
 * All 19 relocation slots resolved against the target: the eight calls are
 * gm_ResolveEntityById (x2), gv_CheckSlotActive, GetSlotEntry,
 * FindSlotEntryFiltered, gm_SubObjektNoKill, __ftol and
 * gm_AddOrAccumulateObject; the globals are g_entity_table_end,
 * g_entity_type_table, g_1002574c (x2), g_current_year, g_next_object_id,
 * g_current_season (x2), g_entity_slot_table (x2) and table_1002572c. */

int __cdecl gv_MoveSlotEntry(void* a)
{
	void* cmd;
	void* rec2;
	void* slot;
	void* found2;
	void* found;
	int* src_entry;
	int* dst_entry;
	int* dst_end;
	int* src_end;
	int src_count;
	int clear;
	int count;
	int i;

	cmd = a;
	gm_ResolveEntityById(0, 0, &a, *(int*) a);
	if (a == 0)
		return -6;
	gm_ResolveEntityById(&rec2, 0, 0, *(int*) ((char*) cmd + 4));
	/* The three -1 exits share one epilogue in the target (0x10011bd8),
	 * reached by a far jump from each guard. */
	if (rec2 == 0 || *(unsigned short*) ((char*) rec2 + 0x27) == 0xffff ||
	    0x100358a0 + (*(unsigned short*) ((char*) rec2 + 0x27) & 0xffff) * 540 ==
	        g_entity_table_end)
		return -1;
	if (*(unsigned char*) (g_entity_type_table + *(unsigned char*) rec2 +
	    *(unsigned char*) rec2 * 588) != 0x1d)
		return -2;
	slot = *(void**) ((char*) rec2 + 0x65);
	if (slot == 0)
		return -3;
	if (!gv_CheckSlotActive(slot, *(int*) ((char*) cmd + 8)))
		return -4;
	found = GetSlotEntry(slot, *(int*) ((char*) cmd + 8),
	                     *(unsigned char*) ((char*) cmd + 0xc));
	/* One -7 epilogue in the target at 0x10011a7b, shared by all three
	 * guards. */
	if (found == 0)
		goto fail7;
	if (*(unsigned short*) ((char*) found + 8) != *(unsigned short*) ((char*) a + 0x50))
		goto fail7;

	src_entry = *(int**) ((char*) found + 0x10);
	/* The source bound is computed before the call (0x10011a4d) and spilled
	 * to [esp+0x10]. */
	src_count = g_1002574c[*(int*) ((char*) cmd + 8)];
	found2 = FindSlotEntryFiltered(a, rec2, 0, (void*) 0x10010700,
	                               *(int*) ((char*) cmd + 0xd));
	if (found2 == 0)
		goto fail7;
	dst_entry = *(int**) ((char*) found2 + 0x10);
	dst_end = dst_entry + g_1002574c[*(int*) ((char*) cmd + 0xd)] * 17;
	src_end = src_entry + src_count * 17;

	if (dst_entry < dst_end) {
		for (;;) {
			if (*dst_entry == -1) {
				/* Skip occupied source entries by walking src, not dst;
				 * both bounds are the ends, not each other (0x10011ac0).
				 * The copy lives INSIDE the skip loop, exited by `break`:
				 * that is what emits the target's bare `jmp 0x10011ac4`
				 * back edge instead of a duplicated `cmp [ebx],-1`/`je`. */
				while (src_entry < src_end) {
					if (*src_entry != -1) {
						memcpy(dst_entry, src_entry, 0x44);
						memset(src_entry, 0, 0x44);
						*src_entry = -1;
						break;
					}
					src_entry += 0x11;
				}
				if (src_entry >= src_end)
					goto done;
			}
			dst_entry += 0x11;
			if (dst_entry < dst_end)
				continue;
			break;
		}
	}
done:

	/* The move clears the source entry (found) and fills the destination
	 * (found2): 0x10011b0d-0x10011b3e. */
	*(int*) ((char*) found2 + 4) = *(int*) ((char*) found + 4);
	*(int*) ((char*) found + 4) = -1;
	*(unsigned short*) ((char*) found2 + 8) = *(unsigned short*) ((char*) found + 8);
	*(unsigned short*) ((char*) found + 8) = 0xffff;
	/* 0xff is materialized once in a 32-bit register (0x10011b32) and reused
	 * by both the byte and the word store. */
	clear = 0xff;
	*(unsigned short*) ((char*) found2 + 0xa) = (unsigned short) (g_current_year + 0xa);
	*(unsigned char*) ((char*) found2 + 0xc) = (unsigned char) clear;
	*(unsigned short*) ((char*) found + 0xa) = (unsigned short) clear;
	*(int*) ((char*) cmd + 0x15) = g_next_object_id;

	count = *(int*) ((char*) cmd + 0x11);
	if (count > 0) {
		gm_SubObjektNoKill(*(int*) ((char*) a + 4),
		                   (unsigned int) *(unsigned short*) ((char*) g_entity_slot_table +
		                                                       g_current_season * 756),
		                   count);
		/* fild re-reads the field (0x10011b7c) instead of the register, and
		 * the conversion is an implicit cast, not a pushed double. */
		i = (int) ((float) *(int*) ((char*) cmd + 0x11) *
		           table_1002572c[*(int*) ((char*) cmd + 0xd)]);
		gm_AddOrAccumulateObject(*(int*) (0x100358a4 +
		                                 (unsigned short) *(unsigned short*) ((char*) rec2 + 0x27) * 540),
		                         (unsigned int) *(unsigned short*) ((char*) g_entity_slot_table +
		                                                             g_current_season * 756),
		                         i);
	}
	return 0;

fail7:
	return -7;

fail1:
	return -1;
}

