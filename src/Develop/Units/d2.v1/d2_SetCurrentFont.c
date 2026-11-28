int __cdecl d2_GetResourceData(int);
extern char* d2_FileObjTable;

/* ADDRESS: GOLD 0x00476020 */
int __cdecl d2_SetCurrentFont(int index)
{
	int rec;
	int slot;

	if (*(int*) (d2_FileObjTable + index * 0x54 + 0x3c) != 7) {
		return 0;
	}
	rec = d2_GetResourceData(index);
	slot = *(int*) 0x5fe73c;
	*(int*) 0x6ed948 = rec;
	*(int*) 0x5fe718 = index;
	*(int*) 0xf8f084 = *(unsigned short*) (rec + 0x2e);
	if (index != slot) {
		slot += 2;
		*(int*) 0x5fe724 = 4;
	}
	if (index == slot) {
		*(int*) 0x5fe724 = 8;
	}
	*(int*) 0x5fe728 = 2;
	return rec;
}
