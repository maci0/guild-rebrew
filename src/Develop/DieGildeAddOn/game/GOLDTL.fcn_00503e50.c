/* fcn_00503e50 — walk the filtered list until the owner matches. */

void* __cdecl gm_StartFilteredEntitySearch(int, int, int);
void* __cdecl gm_FindNextFilteredEntity(void);

/* ADDRESS: GOLDTL 0x00503e50 */
void* __cdecl fcn_00503e50(int a1)
{
	void* entry;

	entry = gm_StartFilteredEntitySearch(1, 0, 0x47);
	if (entry == 0) {
		return 0;
	}
	do {
		if (*(int*) ((char*) entry + 0x65) == a1) {
			return entry;
		}
		entry = gm_FindNextFilteredEntity();
	} while (entry != 0);
	return 0;
}
