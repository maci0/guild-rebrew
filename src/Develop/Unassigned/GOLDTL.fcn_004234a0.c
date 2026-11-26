


extern int g_6b7d7c;
char* __cdecl sb_FindSampleByName(int, int);

int __cdecl sb_IsSampleType2(int bank, int name)
{
	char* entry;

	if (g_6b7d7c == 0) {
		return 1;
	}
	entry = sb_FindSampleByName(bank, name);
	if (entry != 0 && entry[0x36] == 2) {
		return 1;
	}
	return 0;
}
