/* fcn_00503e50 — walk the filtered list until the owner matches. */

void* __cdecl fcn_00503fe0(int, int, int);
void* __cdecl fcn_00503e80(void);

/* ADDRESS: GOLD 0x00501000 */
/* ADDRESS: GOLDTL 0x00503e50 */
void* __cdecl fcn_00503e50(int a1)
{
	void* entry;

	entry = fcn_00503fe0(1, 0, 0x47);
	if (entry == 0) {
		return 0;
	}
	do {
		if (*(int*) ((char*) entry + 0x65) == a1) {
			return entry;
		}
		entry = fcn_00503e80();
	} while (entry != 0);
	return 0;
}
