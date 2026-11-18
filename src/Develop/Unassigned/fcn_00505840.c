extern char* lpObjektePROT;

/* ADDRESS: GOLDTL 0x00505840 */
unsigned char __cdecl fcn_00505840(char* obj, char* list)
{
	unsigned int idx;
	char ch;

	idx = *(unsigned int*) (obj + 0x48) & 0xffffff;
	ch = *(char*) (obj + 0x4b);
	if (ch == 1 && lpObjektePROT[idx * 0x41] == 0x21) {
		*(unsigned int*) (list + 0x100 + *(unsigned int*) (list + 0x200) * 4) = idx;
		*(char**) (list + *(unsigned int*) (list + 0x200) * 4) = obj;
		*(unsigned int*) (list + 0x200) = *(unsigned int*) (list + 0x200) + 1;
	}
	return *(int*) (list + 0x200) < 0x40 ? 1 : 0;
}
