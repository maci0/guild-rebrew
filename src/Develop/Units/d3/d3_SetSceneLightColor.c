

#include "client_types.h"

#include "client_lighting.h"

int __cdecl d3_SetSceneLightColor(int* a, int* b, int* c)
{
	g_67bbdc.x = (float) *a;
	g_67bbdc.y = (float) *b;
	g_67bbdc.z = (float) *c;
	UpdateSceneLighting(1);
	return 1;
}
