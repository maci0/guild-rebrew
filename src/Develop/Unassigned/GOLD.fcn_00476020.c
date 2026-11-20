int __cdecl fcn_004690a0(int);
extern char* g_772500;

/* ADDRESS: GOLD 0x00476020 */
int __cdecl fcn_00476020(int index)
{
	int rec;
	int slot;

	if (*(int*) (g_772500 + index * 0x54 + 0x3c) != 7) {
		return 0;
	}
	rec = fcn_004690a0(index);
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
