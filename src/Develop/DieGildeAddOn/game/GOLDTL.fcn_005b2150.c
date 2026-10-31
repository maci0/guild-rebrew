#include "client_types.h"
extern pos14_7f4c00 g_7f4c00;
extern char g_774a80[];
extern char g_6b5c60[];



void __cdecl io_FormatTextBuffer(void*, int, int, int, int, int, int);
void __cdecl fcn_00545d40(int, int, void*, int, int, void*);

void __cdecl fcn_005b2150(void* a1, void* a2, int a3, int a4, int a5)
{
	char t;
	int tag;

	t = *(char*) ((char*) a2 + 2);
	if (t == 6 || t == 7) {
		if (*(char*) ((char*) a2 + 0xc) == 0) {
			tag = 0x20b7;
		} else {
			tag = ((*(int*)&g_7f4c00) >= 0x75) ? 0x20b9 : 0x20b8;
		}
		io_FormatTextBuffer(g_774a80, 0x20b6, *(unsigned short*) a1, a3, a5, a4, tag);
		fcn_00545d40(*(int*) ((char*) a2 + 4), -1, g_774a80, 0, 0x5ff, g_6b5c60);
	}
}
