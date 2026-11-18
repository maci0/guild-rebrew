
/* ADDRESS: GOLDTL 0x004bcc50 */
char* __cdecl fcn_004bcc50(char* table, int id)
{
	char* p;
	int i;

	for (i = 0, p = table; i < 0x40; i++, p += 0x18) {
		if (p[0xd] != (char) 0xff) {
			if (*(int*) p == id) {
				return table + i * 0x18;
			}
		}
	}
	return 0;
}
