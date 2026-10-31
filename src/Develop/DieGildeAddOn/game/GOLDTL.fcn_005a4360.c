


extern unsigned char g_773d75;
extern char g_7f4ca0[];

unsigned short* __cdecl gm_LookupEntityRecordById(int);
void __cdecl io_FormatTextBuffer(void*, int, ...);
int __cdecl fcn_00526010(void*, int, char);
int __cdecl fcn_00526120(char*, int);
void __cdecl fcn_004c5150(int, int, char, int);
#include "Develop/DieGildeAddOn/game/spiel.h"
void __cdecl he_MessageBoxQuickjump(int, int, char*, int, int, int, int, int, int);
void __cdecl fcn_00546190(char*);

void __cdecl fcn_005a4360(char* e, char* s)
{
	char txt[0x200];
	char msg[0x400];
	unsigned short* g;
	char* slot;
	char* p;

	g = gm_LookupEntityRecordById(*(int*) (s + 0xb0));
	io_FormatTextBuffer(msg, 0x18d5, *(int*) (s + 0xb4));
	if (e == 0) {
		return;
	}
	if (fcn_00526010(g, *(int*) (s + 0xb4), (*(char*)&g_773d75)) == 0) {
		return;
	}
	if (fcn_00526120(msg, 1) == 0) {
		return;
	}
	slot = g_7f4ca0 + *(unsigned short*) (e + 0x27) * 540;
	fcn_004c5150(*(int*) (e + 1), *(int*) (s + 0xb0), (*(char*)&g_773d75), *(int*) (s + 0xb4));
	p = (char*) gm_GetEntityTableEntry((char*) (g));
	if (p != 0) {
		*(int*) (p + 0x48) += *(int*) (s + 0xb4);
	}
	if (slot[2] != 5) {
		io_FormatTextBuffer(txt, 0x18d8, *g, e, *(int*) (s + 0xb4));
		he_MessageBoxQuickjump(*(int*) (slot + 4), -1, txt, 0, 0x5ec, *(int*) (e + 1), -1, 0, 0);
	}
	fcn_00546190(s);
}
