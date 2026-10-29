#include "Develop/DieGildeAddOn/game/ch_script.h"


extern char* g_6b7e98;
extern char g_676330[];

void __cdecl fcn_00425bf0(void*, int, void*);

int __cdecl fcn_0040dfb0(char** pp, int* on)
{
	void* g;

	if (*pp == 0) {
		g = *(void**) ((char*)&g_6b7e98);
		fcn_00425bf0(g, *(int*) ((char*) g + 0x118), (void*) g_676330);
		return 1;
	}
	if (*on != 0) {
		*(short*) (*pp + 0x8c) |= 0x200;
	} else {
		*(short*) (*pp + 0x8c) &= ~0x200;
	}
	return 1;
}
