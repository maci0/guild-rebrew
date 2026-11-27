#include "Develop/Units/d3/d3_camera.h"

/* ADDRESS: GOLDTL 0x0052d7c0 */
void __cdecl d3_SetActiveCameraTransform(int* src)
{
	if (((char*)d3_ActiveCamera) != 0 && src != 0) {
		*(int*) (((char*)d3_ActiveCamera) + 0x4c) = src[0];
		*(int*) (((char*)d3_ActiveCamera) + 0x50) = src[1];
		*(int*) (((char*)d3_ActiveCamera) + 0x54) = src[2];
		*(int*) (((char*)d3_ActiveCamera) + 0x84) = src[4];
		*(int*) (((char*)d3_ActiveCamera) + 0x88) = src[5];
		*(int*) (((char*)d3_ActiveCamera) + 0x8c) = src[6];
	}
}
