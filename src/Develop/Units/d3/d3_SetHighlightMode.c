extern int d3_ActiveScene;

char __cdecl d3_ToggleObjectHighlightCallback(char* a, char on);
void __cdecl d3_VisitSceneObjects(int list, int a, int mask, char(__cdecl* fn)(char*, char), int arg);
#include "Develop/Units/d3/client_lighting.h"

/* ADDRESS: GOLDTL 0x0043ace0 */
void __cdecl d3_SetHighlightMode(unsigned char a)
{
	d3_VisitSceneObjects(d3_ActiveScene, 0, 6, d3_ToggleObjectHighlightCallback, a);
	UpdateSceneLighting(1);
}
