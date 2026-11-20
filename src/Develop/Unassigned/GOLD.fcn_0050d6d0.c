#include <stdio.h>
#include "client_scene_loader.h"
void __cdecl d3_VisitSceneNodes(int obj, int a, int b, int cb);

/* ADDRESS: GOLD 0x0050d6d0 */
char __cdecl d3_LoadStadtScene(int name)
{
	char buf[256];

	sprintf(buf, (char *)0x622ed4, name);
	if (fcn_0044be60(buf, 0, 0) == 0)
		return 0;
	d3_VisitSceneNodes(*(int *)0x5fb5b0, 0, 6, 0x50d730);
	return 1;
}
