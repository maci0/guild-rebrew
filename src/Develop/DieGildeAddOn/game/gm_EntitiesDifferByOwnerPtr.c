
// fcn_004ce270 — a[0x16c/4] != b[0x16c/4].

/* ADDRESS: GOLDTL 0x004cf0f0 */
/* ADDRESS: GOLDDE 0x004bc5d0 */
int __cdecl gm_EntitiesDifferByOwnerPtr(char* a, char* b)
{
	return *(int*) (a + 0x16c) != *(int*) (b + 0x16c);
}

