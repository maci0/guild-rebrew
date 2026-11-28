


extern int sb_WaveDriver;
char* __cdecl sb_FindSampleByName(int, int);

/* ADDRESS: GOLDDE 0x00420250 */
int __cdecl sb_IsSampleType2(int bank, int name)
{
	char* entry;

	if (sb_WaveDriver == 0) {
		return 1;
	}
	entry = sb_FindSampleByName(bank, name);
	if (entry != 0 && entry[0x36] == 2) {
		return 1;
	}
	return 0;
}
