
/* ADDRESS: GOLDTL 0x004bcc20 */
char* __cdecl plt_FindRecordByOwner(char* entries, int id)
{
	char* p;
	int i;

	for (i = 0, p = entries + 0x14; i < 0x40; i++, p += 0x18) {
		if (p[-7] != (char) 0xff) {
			if (*(int*) p == id) {
				return entries + i * 0x18;
			}
		}
	}
	return 0;
}
