#include "Develop/Units/d3/d3_camera.h"


void __cdecl d3_AnimateObjectTransform(char*, char*, char*, int, int);

/* ADDRESS: GOLDDE 0x004115c0 */
void __cdecl d3_AnimateCameraToNode(char* node, int duration)
{
	d3_AnimateObjectTransform(d3_ActiveCamera, node + 0x5c, node + 0x90, duration, 8);
}
