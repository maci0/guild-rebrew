/* fcn_0057f3b0 — on the first pass, tag the filtered entry. */

void* __cdecl fcn_00503fe0(int, int, int);
void __cdecl fcn_00526920(void*, int, int);

// FUNCTION: GOLDTL 0x57f3b0
// SIZE: 42
void __cdecl fcn_0057f3b0(int a1)
{
	void* entry;

	if (a1 == 1) {
		entry = fcn_00503fe0(1, 5, 0xa);
		if (entry != 0) {
			fcn_00526920(entry, -1, 0x6b5c60);
		}
	}
}
