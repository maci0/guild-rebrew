extern char* lpObjektePROT;

/* ADDRESS: GOLDTL 0x00505840 */
unsigned char __cdecl fcn_00505840(char* a0, char* a1)
{
	unsigned int idx;
	char ch;

	idx = *(unsigned int*) (a0 + 0x48) & 0xffffff;
	ch = *(char*) (a0 + 0x4b);
	if (ch == 1 && lpObjektePROT[idx * 0x41] == 0x21) {
		*(unsigned int*) (a1 + 0x100 + *(unsigned int*) (a1 + 0x200) * 4) = idx;
		*(char**) (a1 + *(unsigned int*) (a1 + 0x200) * 4) = a0;
		*(unsigned int*) (a1 + 0x200) = *(unsigned int*) (a1 + 0x200) + 1;
	}
	return *(int*) (a1 + 0x200) < 0x40 ? 1 : 0;
}
