

#include "Develop/DieGildeAddOn/game/game_data.h"
extern char* g_9b46c0[];
extern char g_68bda0[];

int __cdecl fcn_0064f170(char*, char*, int);

char __cdecl d3_CollectEnemyWareNode(char* node, char* entity)
{
	unsigned short* w;

	w = *(unsigned short**) (entity + 0x16c);
	if (fcn_0064f170(node, g_68bda0, 5) == 0 && *(int*) (*(char**) (node + 0x204) + 0xa) != *w) {
		g_9b46c0[g_772f10] = node;
		g_772f10++;
	}
	return 1;
}
