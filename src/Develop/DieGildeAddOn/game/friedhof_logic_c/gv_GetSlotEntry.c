/* gv_GetSlotEntry - returns the active slot entry of a worker for the given
 * work type and job index, or NULL when the request is invalid. */

// FUNCTION: SERVER 0x100105b0

extern int __cdecl gv_CheckSlotActive(void* worker, int worktype);

void* __cdecl gv_GetSlotEntry(void* worker, int worktype, unsigned char job)
{
	if (*(int*) ((char*) worker + 4) < 1 || *(int*) ((char*) worker + 4) > 3)
		return 0;
	if (worktype == 0) {
		if (!gv_CheckSlotActive(worker, 0))
			return 0;
		if (*(int*) ((char*) worker + 4) == 1 && job >= 8)
			return 0;
		if (*(int*) ((char*) worker + 4) == 2 && job >= 0xc)
			return 0;
		if (*(int*) ((char*) worker + 4) == 3 && job >= 0x10)
			return 0;
		return (char*) *(void**) ((char*) worker + 8) + (unsigned int) job * 20;
	}
	if (worktype == 1) {
		if (!gv_CheckSlotActive(worker, 1))
			return 0;
		if (*(int*) ((char*) worker + 4) == 1 && job >= 4)
			return 0;
		if (*(int*) ((char*) worker + 4) == 2 && job >= 6)
			return 0;
		if (*(int*) ((char*) worker + 4) == 3 && job >= 8)
			return 0;
		return (char*) *(void**) ((char*) worker + 0xc) + (unsigned int) job * 20;
	}
	if (worktype == 2) {
		if (!gv_CheckSlotActive(worker, 2))
			return 0;
		if (*(int*) ((char*) worker + 4) == 1)
			return 0;
		if (*(int*) ((char*) worker + 4) == 2 && job >= 2)
			return 0;
		if (*(int*) ((char*) worker + 4) == 3 && job >= 4)
			return 0;
		return (char*) *(void**) ((char*) worker + 0x10) + (unsigned int) job * 20;
	}
	if (worktype == 3) {
		if (!gv_CheckSlotActive(worker, 3))
			return 0;
		if (*(int*) ((char*) worker + 4) == 1 || *(int*) ((char*) worker + 4) == 2)
			return 0;
		if (*(int*) ((char*) worker + 4) == 3 && job >= 2)
			return 0;
		return (char*) *(void**) ((char*) worker + 0x14) + (unsigned int) job * 20;
	}
	return 0;
}

/* gv_eval_SlotFrei -- 14 bytes at 0x10010700, between this function and
 * FindSlotEntryFiltered, in the same translation unit in the reference.  The 7
 * bytes of `nop` that separate the two are msvc6's 16-byte intra-section
 * function alignment.
 *
 * It is a filter CALLBACK, not an unreferenced helper.  An earlier version of
 * this comment said "no caller", which was wrong: it has three, none of them a
 * `call` instruction, because all three pass its ADDRESS as the fourth argument
 * of FindSlotEntryFiltered -- gv_SpawnEntities.c:41, gv_HireProductionWorker.c:55
 * and gv_MoveSlotEntry.c:121.  That is also why the catalogue has no name for it
 * and why the callee invokes it indirectly:
 *
 *     if (((int (__cdecl*) (void*, void*)) filter)(filter_arg, cursor)) { ... }
 *
 * The contract is therefore the callee's: `filter(arg, entry)` returns non-zero
 * to accept `entry`.  This one accepts an entry whose owner id is -1, i.e. one
 * with no owner assigned.
 *
 * Named for that.  `_eval_` is this tree's predicate idiom
 * (`gm_eval_SlotVoll`, `gm_eval_ObjektBesitzer`); German `frei` parallels that
 * name's `Voll`, and the +4 field is the owner id -- gv_ReplaceProductionWorker
 * tests the same dword with `!= -1` before resolving it through
 * gm_ResolveEntityById and storing it into `slot + 4`. */

// FUNCTION: SERVER 0x10010700

int __cdecl gv_eval_SlotFrei(void* unused, int* p)
{
	(void) unused;
	return *(int*) ((char*) p + 4) == -1;
}
