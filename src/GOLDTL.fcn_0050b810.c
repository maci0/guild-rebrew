/* fcn_0050b810 — sum one field over the query matches. */

void* __cdecl fcn_00502cd0(int, int, int, int);
void* __cdecl fcn_00502850(void);

// FUNCTION: GOLDTL 0x50b810
int __cdecl fcn_0050b810(int a1)
{
	void* entry;
	int total;

	total = 0;
	entry = fcn_00502cd0(a1, 1, 4, 9);
	while (entry != 0) {
		total = total + *(int*) ((char*) entry + 0xe);
		entry = fcn_00502850();
	}
	return total;
}
