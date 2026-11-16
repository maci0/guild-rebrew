int __cdecl gv_CheckSlotActive(void*, int);

/* ADDRESS: GOLD 0x004ef570 */
void* __cdecl fcn_004ef570(void* worker, int worktype, unsigned char job)
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

