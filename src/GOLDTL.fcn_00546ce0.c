/* fcn_00546ce0 — drain the entries selected by the record's first word. */

void* __cdecl fcn_005463a0(int, int, int);
void __cdecl fcn_00546be0(void*);
void* __cdecl fcn_005462a0(void);

// FUNCTION: GOLD 0x0053efa0
// FUNCTION: GOLDTL 0x546ce0
void __cdecl fcn_00546ce0(unsigned short* a1)
{
	void* entry;

	entry = fcn_005463a0(1, 2, *a1);
	while (entry != 0) {
		fcn_00546be0(entry);
		entry = fcn_005462a0();
	}
}
