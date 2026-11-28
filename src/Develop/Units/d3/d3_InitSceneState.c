


#include <string.h>

#include "Develop/Units/d3/g_9baa20.h"

extern int g_9baa00;
extern int g_9baa08;
extern Rec9baa20 g_9baa20;
extern char g_9baae0[];
#include "Develop/DieGildeAddOn/game/game_data.h"
extern int g_9badd4;

void __cdecl d3_InitSceneState(int clientId, int sessionParam)
{
	memset(&g_9baa20, 0, 0x24);
	memset(g_9baae0, 0, 0x2b8);
	g_9baa00 = 1;
	g_9badd0 = clientId;
	g_9badd4 = sessionParam;
	g_9baa08 = 0;
}
