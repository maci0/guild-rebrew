


extern int* sb_BankListHead;
extern int sb_WaveDriver;
extern char sb_NullSampleBank[];

char* __cdecl sb_FindSampleBank(char* key)
{
	char* p;
	int i;

	p = ((char*)sb_BankListHead);
	if (sb_WaveDriver == 0) {
		return sb_NullSampleBank;
	}
	for (; p != 0; p = *(char**) (p + 0x13c)) {
		for (i = 0; i < *(int*) (p + 0x134); i++) {
			if (*(char**) (p + 0x138) + i * 0x40 == key) {
				return p;
			}
		}
	}
	return p;
}
#if defined(REBREW_SERVER) || defined(REBREW_GOLD)
unsigned char _dpad_14483c4[99324];
#endif
