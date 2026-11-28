


// fcn_004b4590 — fcn_00504ce0(a[0x164]) >= b[0x14].

int __cdecl gm_GetOppositeStatIndex(int);

/* ADDRESS: GOLDDE 0x004a29f0 */
int __cdecl gm_CheckStatRankThreshold(char* a, char* b, int u)
{
	(void) u;
	return gm_GetOppositeStatIndex((unsigned char) a[0x164]) >= *(int*) (b + 0x14);
}

