int __cdecl fcn_0064d41a(char*, char*, ...);
int __cdecl d2_BlitShape(int a1, int a2, int a3, char* a4);

/* ADDRESS: GOLDTL 0x00479e40 */
int __cdecl shp_ShowShapeFromBankWithMode(void* a1, void* a2, int a3, char* record, int entryIndex)
{
	char buf[0x80];
	char* entry;
	unsigned char saved;

	if (record == 0) {
		return 0;
	}
	if (entryIndex > *(unsigned short*) (record + 0x2a)) {
		fcn_0064d41a(buf, (char*) 0x67da68, record + 0xa);
		return 0;
	}
	entry = record + *(int*) (record + entryIndex * 4 + 0x45);
	saved = entry[0xd];
	entry[0xd] = 5;
	d2_BlitShape((int) a1, (int) a2, a3, record + *(int*) (record + entryIndex * 4 + 0x45));
	entry[0xd] = saved;
	return 1;
}
