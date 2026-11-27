
// fcn_0044e6f0 — increments dword at (param2)+8.

/* ADDRESS: GOLDTL 0x0044d8d0 */
void __cdecl d3_AdvanceMatSlot(void* unused, void* a)
{
	(void) unused;
	(*(int*) ((char*) a + 8))++;
}

