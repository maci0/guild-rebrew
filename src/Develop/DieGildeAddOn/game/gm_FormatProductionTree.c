#include "Develop/DieGildeAddOn/game/object_prototype.h"

void* __cdecl memset(void*, int, unsigned int);
#pragma intrinsic(memset)

extern char* lpObjektePROT;
extern char g_6aa380[];

int __cdecl fcn_0064d41a(char*, const char*, ...);

void __cdecl gm_FormatProductionTree(char* node, int depth)
{
	char buf[0x200];
	char* c;

	if (node != 0) {
		memset(buf, ' ', sizeof(buf));
		fcn_0064d41a(buf + depth * 2, g_6aa380, ((char *)&((OBJECT_PROTOTYPE *)lpObjektePROT)[*(unsigned short*) node]) + 1,
		    *(int*) (node + 0xe));
		for (c = *(char**) (node + 0x14); c != 0; c = *(char**) (c + 0x3f)) {
			gm_FormatProductionTree(c, depth + 1);
		}
	}
}
