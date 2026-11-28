extern void* g_1041d04;
extern int g_6b8708;
extern int g_6b8704;
extern void* g_6b870c;
extern int g_6b8700;
#include "Develop/DieGildeAddOn/game/game_data.h"
#include "Develop/Units/d3/client_lighting.h"


void __cdecl m_FreeTracked(int);

void __cdecl d3_ResetLightBuffers(void)
{
	g_6b8708 = 0;
	g_6b8704 = 0;
	m_FreeTracked((*(int*)&g_1041d04));
	(*(int*)&g_1041d04) = 0;
	g_6b8700 = 0;
	d3_MaxActiveLights = 0;
	m_FreeTracked((*(int*)&g_6b870c));
	(*(int*)&g_6b870c) = 0;
	g_6b86d4 = 0;
}
