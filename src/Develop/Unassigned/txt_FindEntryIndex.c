#if defined(REBREW_GOLD)
#include <string.h>

/* ADDRESS: GOLD 0x0042e770 */
int __cdecl txt_FindEntryIndex(char* name)
{
	char* e;
	int i;

	i = 0;
	e = (char*) 0xfe7e40;
	do {
		if (_strcmpi(name, e) == 0) {
			return i;
		}
		e += 0x50;
		i++;
	} while ((int) e < 0x114fe40);
	return -1;
}
#else
extern char g_1053000[][0x50];

int __cdecl fcn_0065f220(const char* a, const char* b);

/* ADDRESS: GOLDTL 0x0042dc90 */
int __cdecl txt_FindEntryIndex(const char* name)
{
	int i;

	for (i = 0; i < 0x4800; i++) {
		if (fcn_0065f220(name, g_1053000[i]) == 0) {
			return i;
		}
	}
	return -1;
}
#endif
