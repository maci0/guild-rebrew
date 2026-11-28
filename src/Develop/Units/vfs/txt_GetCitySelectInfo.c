extern char* txt_TextEntries[];




#include <string.h>

int sprintf(char*, const char*, ...);
int __cdecl txt_FindEntryIndex(char*);

int __cdecl txt_GetCitySelectInfo(char* key, char* out)
{
	char buf[256];
	int r;

	sprintf(buf, "_STADTAUSWAHL_%s_INFO+0", key);
	_strupr(buf);
	r = txt_FindEntryIndex(buf);
	if (r != -1) {
		strcpy(out, txt_TextEntries[r]);
		return 1;
	}
	strcpy(out, key);
	return 1;
}
