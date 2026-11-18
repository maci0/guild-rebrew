extern char* txt_TextEntries[];




#include <string.h>

int sprintf(char*, const char*, ...);
int __cdecl fcn_0042dc90(char*);

int __cdecl fcn_00517b10(char* key, char* out)
{
	char buf[256];
	int r;

	sprintf(buf, "_STADTAUSWAHL_%s_INFO+0", key);
	_strupr(buf);
	r = fcn_0042dc90(buf);
	if (r != -1) {
		strcpy(out, txt_TextEntries[r]);
		return 1;
	}
	strcpy(out, key);
	return 1;
}
