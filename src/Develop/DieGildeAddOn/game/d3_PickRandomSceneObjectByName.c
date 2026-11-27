


#include <string.h>

typedef struct {
	char name[0x20];
	char* list[0x20];
	int n;
} pickctx;
// SIZE 0xa4

extern int g_67a370;

int __cdecl d3_CollectSceneObjectsByName(char*, pickctx*);
void __cdecl d3_VisitSceneObjects(int, int, int, int(__cdecl*)(char*, pickctx*), pickctx*);
unsigned short __cdecl gm_RandomMod(int);

char* __cdecl d3_PickRandomSceneObjectByName(char* name)
{
	pickctx c;

	c.n = 0;
	strcpy(c.name, name);
	d3_VisitSceneObjects(g_67a370, 0, 0x380, d3_CollectSceneObjectsByName, &c);
	if (c.n == 0)
		return 0;
	return c.list[gm_RandomMod(c.n)];
}
