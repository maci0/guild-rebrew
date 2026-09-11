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
