#include <stdio.h>
#include <string.h>

extern char s_6750e8[];
extern char s_67daa0[];

char* __cdecl fcn_0041db70(int size, const char* tag);

// FUNCTION: GOLDTL 0x479f70
// SIZE: 117
char* __cdecl fcn_00479f70(const char* name)
{
	FILE* f;
	int len;
	char* buf;

	f = fopen(name, s_6750e8);
	if (!f) {
		return 0;
	}
	fseek(f, 0, SEEK_END);
	len = ftell(f);
	fseek(f, 0, SEEK_SET);
	buf = fcn_0041db70(len, s_67daa0);
	memset(buf, 0, len);
	fread(buf, len, 1, f);
	fclose(f);
	return buf;
}
