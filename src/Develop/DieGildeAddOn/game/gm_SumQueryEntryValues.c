/* fcn_0050b810 — sum one field over the query matches. */

void* __cdecl gm_QueryEntities(int, int, int, int);
void* __cdecl gm_NextEntityQueryMatch(void);

/* ADDRESS: GOLDTL 0x0050b810 */
/* ADDRESS: GOLDDE 0x004f8000 */
int __cdecl gm_SumQueryEntryValues(int list)
{
	void* entry;
	int total;

	total = 0;
	entry = gm_QueryEntities(list, 1, 4, 9);
	while (entry != 0) {
		total = total + *(int*) ((char*) entry + 0xe);
		entry = gm_NextEntityQueryMatch();
	}
	return total;
}
