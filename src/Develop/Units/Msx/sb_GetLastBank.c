extern int* sb_BankListHead;
extern int sb_WaveDriver;
extern char sb_NullSampleBank[];

/* ADDRESS: GOLD 0x00426630 */
/* ADDRESS: GOLDTL 0x00422aa0 */
char* __cdecl sb_GetLastBank(void)
{
	char* p;

	p = ((char*)sb_BankListHead);
	if (sb_WaveDriver == 0) {
		return sb_NullSampleBank;
	}
	if (p != 0) {
		while (*(char**) (p + 0x13c) != 0) {
			p = *(char**) (p + 0x13c);
		}
	}
	return p;
}
