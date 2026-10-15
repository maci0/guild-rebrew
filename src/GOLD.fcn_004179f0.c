#include "Develop/Units/d3/d3_camera.h"
#include <math.h>

extern float g_662d40[3];

void __cdecl fcn_00454030(float*, float*);
void __cdecl fcn_00458a10(char*, char*, float*);
float __cdecl fcn_004539e0(float*, float*);
void __cdecl fcn_004272f0(void*, int);

/* ADDRESS: GOLD 0x004179f0 */

/* Pans a sound source by the angle between the camera's forward axis and
 * the direction to the emitting object. */
void __cdecl fcn_004179f0(char* src)
{
	float pos[4];
	float fwd[4];
	float dir[4];
	float m[16];

	if (src == 0 || *(char**) (src + 0x38) == 0 || *(void**) (src + 0x34) == 0) {
		return;
	}
	fcn_00454030((float*) (((char*)g_6b8014) + 0x18c), m);
	fwd[0] = g_662d40[0] * m[0] + g_662d40[1] * m[4] + g_662d40[2] * m[8];
	fwd[1] = g_662d40[0] * m[1] + g_662d40[1] * m[5] + g_662d40[2] * m[9];
	fwd[2] = g_662d40[0] * m[2] + g_662d40[1] * m[6] + g_662d40[2] * m[10];
	fcn_00458a10(*(char**) (src + 0x38), *(char**) (src + 0x38) + 0x4c, pos);
	dir[0] = pos[0] - *(float*) (((char*)g_6b8014) + 0x4c);
	dir[1] = pos[1] - *(float*) (((char*)g_6b8014) + 0x50);
	dir[2] = pos[2] - *(float*) (((char*)g_6b8014) + 0x54);
	fcn_004272f0(*(void**) (src + 0x34), (int) (sin(fcn_004539e0(dir, fwd)) * 63.5 + 63.0));
}
