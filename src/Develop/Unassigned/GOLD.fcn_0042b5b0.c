#include <string.h>

extern int __cdecl ReportClientMessage(char* text);
int __cdecl evt_FindCommand(char* name);

/* ADDRESS: GOLD 0x0042b5b0 */
int __cdecl evt_RegisterScriptCommand(char* name, int handlerAddress, int handlerKind, int n, ...)
{
	char* tab;
	int* va;
	int* dst;
	int i;
	int off;

	i = 0;
	if (strlen(name) > 0x1f) {
		ReportClientMessage((char*) 0x5f8a84);
		return 0;
	}
	if (evt_FindCommand(name) != 0) {
		ReportClientMessage((char*) 0x5f8a50);
		return 0;
	}
	tab = *(char**) 0x6332bc;
	for (; i < 0x100; i++) {
		if (*(int*) (tab + 0x44 + i * 0x4c) == 0) {
			break;
		}
	}
	if (i >= 0x100) {
		ReportClientMessage((char*) 0x5f8a28);
		return 0;
	}
	off = i * 0x4c;
	*(int*) (tab + off + 0x44) = handlerAddress;
	*(int*) (*(char**) 0x6332bc + off + 0x48) = handlerKind;
	*(int*) (*(char**) 0x6332bc + off + 0x20) = n;
	if (0 < n) {
		va = &n;
		dst = (int*) (off + 0x24);
		for (i = n; i > 0; i--) {
			*(int*) ((char*) dst + *(int*) 0x6332bc) = *++va;
			dst++;
		}
	}
	strcpy(*(char**) 0x6332bc + off, name);
	return 1;
}
