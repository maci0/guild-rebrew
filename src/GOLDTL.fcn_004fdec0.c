// FUNCTION: GOLD 0x004fb770
// SIZE: 288
// FUNCTION: GOLDTL 0x004fdec0
// SIZE: 288

#include <stdio.h>
#include <string.h>

extern char g_69649c[];
extern char g_6964b4[];
extern char g_696488[];
extern int g_773d40;
extern char* g_773d44;

int __cdecl _strcmpi(const char* a, const char* b);

int __cdecl fcn_004fdec0(char* name)
{
	char base[128];
	char full[128];
	char suffix[128];
	char* p;
	int result;
	int i;
	int j;

	result = 0xff;
	strcpy(base, name);
	p = strrchr(base, '_');
	if (p != 0) {
		strcpy(suffix, p + 1);
		*p = 0;
	}
	for (i = 0; i < 4 && result == 0xff; i++) {
		sprintf(full, g_69649c, base, i, suffix);
		if (strstr(base, g_6964b4) != 0) {
			sprintf(full, g_696488, base, i);
		}
		for (j = 0; j < g_773d40; j++) {
			if (g_773d44[j * 0x30] == 0) {
				break;
			}
			if (_strcmpi(full, g_773d44 + j * 0x30) == 0) {
				result = j;
				break;
			}
		}
	}
	if (result == 0xff) {
		return 0;
	}
	return result;
}
