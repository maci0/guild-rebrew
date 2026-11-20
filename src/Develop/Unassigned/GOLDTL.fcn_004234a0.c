


extern int g_6b7d7c;
char* __cdecl sb_FindSampleByName(int, int);

int __cdecl fcn_004234a0(int a1, int a2)
{
	char* entry;

	if (g_6b7d7c == 0) {
		return 1;
	}
	entry = sb_FindSampleByName(a1, a2);
	if (entry != 0 && entry[0x36] == 2) {
		return 1;
	}
	return 0;
}
