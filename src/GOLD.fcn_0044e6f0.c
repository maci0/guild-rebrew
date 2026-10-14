/* ADDRESS: GOLD 0x0044e6f0 */
/* ADDRESS: GOLDTL 0x0044d8d0 */

// fcn_0044e6f0 — increments dword at (param2)+8.

void __cdecl fcn_0044e6f0(void* unused, void* a)
{
	(void) unused;
	(*(int*) ((char*) a + 8))++;
}

