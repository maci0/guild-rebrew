

// SIZE 0x70
typedef struct Item {
	char pad[0x54];
	unsigned char flags;
	char pad2[0x1b];
} Item;

extern char* d3_TextureBank;
extern unsigned int d3_TextureBankCount;
extern int d3_ActiveScene;

void __cdecl d3_TraverseSceneObjects(int, int, int, void*);
#include "Develop/Units/d3/d3_d3d.h"

void __cdecl d3_PrecacheAllSceneTextures(int flag)
{
	unsigned int i;

	for (i = 0; i < d3_TextureBankCount; i++) {
		((Item*)d3_TextureBank)[i].flags &= 0xbf;
	}
	d3_TraverseSceneObjects(d3_ActiveScene, 0, 0x40, d3_PrecacheObjectTextures);
}
