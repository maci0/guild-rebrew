
/* ADDRESS: GOLDTL 0x004be300 */
int __cdecl d2_FindLinkedRecordIndex(char* p, char* target)
{
	int n;

	for (n = 0; p != 0; n++) {
		if (target == p) {
			return n;
		}
		p = *(char**) (p + 0x3c);
	}
	return n;
}
