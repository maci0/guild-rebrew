int __cdecl gm_MatchSlotEntryId(int*, int*);



int __cdecl FindSlotEntryFiltered(int*, int, int, void*, int);

/* ADDRESS: GOLDDE 0x004ddad0 */
int __cdecl gv_LookupWorkerSlot(int a1, int* a2)
{
	if (a2 == 0 || *a2 == -1) {
		return 0;
	}
	return FindSlotEntryFiltered(a2, a1, 0, (void*) gm_MatchSlotEntryId, 0xff);
}
