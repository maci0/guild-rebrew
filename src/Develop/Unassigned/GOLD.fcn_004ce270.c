
// fcn_004ce270 — a[0x16c/4] != b[0x16c/4].

/* ADDRESS: GOLDTL 0x004cf0f0 */
int __cdecl fcn_004ce270(char* a, char* b)
{
	return *(int*) (a + 0x16c) != *(int*) (b + 0x16c);
}

