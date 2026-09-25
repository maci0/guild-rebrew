// FUNCTION: GOLD 0x50d100
// SIZE: 592
// FUNCTION: GOLDTL 0x005105a0
// SIZE: 588

#include <string.h>

extern char* g_868050;
extern char* g_99ec10;

int __cdecl _strcmpi(const char* a, const char* b);

int __cdecl fcn_005105a0(char* o)
{
	char tail[128];
	char base[256];
	char type[256];
	char* p;
	int i;

	strcpy(base, o);
	p = strchr(base, '_');
	if (p == 0) {
		return 0;
	}
	strcpy(type, p + 1);
	*p = 0;
	p = strrchr(type, '_');
	if (p != 0) {
		strcpy(tail, p);
		if (strcmp(tail, "_A") == 0 || strcmp(tail, "_B") == 0 || strcmp(tail, "_C") == 0 ||
		    strcmp(tail, "_D") == 0 || strcmp(tail, "_E") == 0 || strcmp(tail, "_F") == 0 ||
		    strcmp(tail, "_G") == 0 || strcmp(tail, "_H") == 0) {
			*p = 0;
		}
	}
	if (_strcmpi(base, "ob") == 0 || _strcmpi(base + 1, "ob") == 0) {
		for (i = 0; i < 732; i++) {
			if (_strcmpi(type, g_99ec10 + i * 0x41 + 1) == 0) {
				*(int*) (o + 0x48) = i | 0x1000000;
				return 1;
			}
		}
		return 0;
	}
	if (_strcmpi(base, "gb") != 0) {
		return 0;
	}
	for (i = 0; i < 88; i++) {
		if (_strcmpi(type, g_868050 + i * 589 + 1) == 0) {
			*(int*) (o + 0x48) = i | 0x2000000;
			return 1;
		}
	}
	if (strstr(type, "KONTOR") == 0) {
		return 0;
	}
	*(int*) (o + 0x48) = 0x2000047;
	return 1;
}
