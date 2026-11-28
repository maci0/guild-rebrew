#include "Develop/Units/d3/d3_camera.h"


void __cdecl d3_ComposeObserverMatrix(void*, char*, int, void*);
void __cdecl d3_MatrixToEulerAngles(void*, int);

/* ADDRESS: GOLDDE 0x0044aaf0 */
void __cdecl d3_GetObjectEulerRotation(void* obj, int a2)
{
	char buf[0x40];

	d3_ComposeObserverMatrix(obj, (*(unsigned char*) ((char*) obj + 0x214) & 0x20) ? 0 : d3_ActiveCamera,
	    1, buf);
	d3_MatrixToEulerAngles(buf, a2);
}
