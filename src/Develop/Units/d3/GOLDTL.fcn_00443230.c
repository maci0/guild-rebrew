

// SIZE 0x70
typedef struct Item {
	char pad[0x54];
	unsigned char flags;
	char pad2[0x1b];
} Item;

extern char* g_104049c;
extern unsigned int g_10404a0;
extern int g_67a370;

void __cdecl d3_TraverseSceneObjects(int, int, int, void*);
#include "Develop/Units/d3/d3_d3d.h"

void __cdecl d3_PrecacheAllSceneTextures(int flag)
{
	unsigned int i;

	for (i = 0; i < g_10404a0; i++) {
		((Item*)g_104049c)[i].flags &= 0xbf;
	}
	d3_TraverseSceneObjects(g_67a370, 0, 0x40, d3_PrecacheObjectTextures);
}
