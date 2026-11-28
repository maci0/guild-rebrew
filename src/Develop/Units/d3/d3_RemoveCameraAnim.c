extern char g_6b5cc0[];
extern char g_6b5cbc[];
#include "Develop/Units/d3/d3_camera.h"


void __cdecl d3_FreeObjectAnimation(void*);

/* ADDRESS: GOLDDE 0x0040ebb0 */
void __cdecl d3_RemoveCameraAnim(void)
{
	d3_FreeObjectAnimation(d3_ActiveCamera);
	*(int*) &g_6b5cc0 = 0;
	*(int*) &g_6b5cbc = 0;
}
