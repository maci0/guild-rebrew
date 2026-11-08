

#include "client_lighting.h"

int __cdecl LightCalc(char* p)
{
	UpdateSceneLighting(*p);
	return 1;
}
