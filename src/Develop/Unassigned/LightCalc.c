

#include "Develop/Units/d3/client_lighting.h"

/* ADDRESS: GOLDDE 0x0040daa0 */
int __cdecl LightCalc(char* p)
{
	UpdateSceneLighting(*p);
	return 1;
}
