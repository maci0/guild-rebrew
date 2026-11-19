#include <math.h>
#include <stdlib.h>

extern char* d3_ActiveCamera;
#include "Develop/DieGildeAddOn/game/game_data.h"
extern float g_6628a8;
extern float g_1042a10;

/* ADDRESS: GOLDTL 0x004382e0 */
int __cdecl fcn_004382e0(char* obj)
{
	char* ext;
	char* entry;
	int n;
	int idx;
	int max_idx;
	float dx;
	float dy;
	float dz;
	float dist;

	ext = *(char**) (obj + 0x1ec);
	if (ext == 0) {
		return 0;
	}
	n = *(unsigned char*) (ext + 0x163c);
	if (n == 0) {
		return 0;
	}
	if (n == 1) {
		entry = ext + 0xf4;
	}
	else if ((*(unsigned char*) (obj + 0x217) & 0xc) != 0 || d3_ActiveCamera == 0) {
		max_idx = (((*(unsigned char*) (obj + 0x217)) >> 2) & 3) - 1;
		idx = __max(0, __min(n - 1, max_idx));
		entry = ext + 0xf4 + idx * 0x4a4;
	}
	else {
		dx = *(float*) (obj + 0x4c) - *(float*) (d3_ActiveCamera + 0x4c);
		dy = *(float*) (obj + 0x50) - *(float*) (d3_ActiveCamera + 0x50);
		dz = *(float*) (obj + 0x54) - *(float*) (d3_ActiveCamera + 0x54);
		dist = sqrt(dz * dz + dy * dy + dx * dx);
		dist = dist * n * g_1042a10;
		idx = (int) dist;
		if (idx >= n) {
			dist = (float) n - g_6628a0;
		}
		else if (dist < g_6628a8) {
			dist = g_6628a8;
		}
		idx = (int) dist;
		entry = ext + 0xf4 + idx * 0x4a4;
	}
	if (*(int*) (entry + 0x310) == 0 || *(int*) (entry + 0x314) == 0) {
		return 0;
	}
	if (entry == *(char**) (obj + 0x1cc)) {
		return (int) entry;
	}
	*(unsigned char*) (obj + 0x214) |= 0x10;
	return (int) entry;
}
