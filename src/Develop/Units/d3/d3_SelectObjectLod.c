#include <math.h>
#include <stdlib.h>
#include "Develop/client_types.h"
#include "Develop/Units/d3/client_lighting.h"
#include "Develop/Units/d3/d3_camera.h"
#include "Develop/DieGildeAddOn/game/game_data.h"

extern float flt_0_0;
extern float g_1042a10;

#if defined(REBREW_GOLD)
/* ADDRESS: GOLD 0x0043a000 */
char* __cdecl d3_SelectObjectLod(char* object)
{
    char* model;
    char* page;
    int count;
    int index;
    int selected;
    VECTOR3 delta;
    float level;

    model = *(char**) (object + 0x1ec);
    if (!model)
        return 0;
    if (*(unsigned char*) (model + 0x96c) <= 0)
        return 0;

    if ((*(unsigned char*) (object + 0x213) & 0x30) == 0 && d3_ActiveCamera) {
        delta = *(VECTOR3*) (object + 0x4c);
        delta.x -= *(float*) (d3_ActiveCamera + 0x4c);
        delta.y -= *(float*) (d3_ActiveCamera + 0x50);
        delta.z -= *(float*) (d3_ActiveCamera + 0x54);
        level = (float) sqrt(delta.z * delta.z + delta.y * delta.y + delta.x * delta.x)
            * (float) *(unsigned char*) (model + 0x96c) * *(float*) 0xfc2dd4;
        if ((int) level >= *(unsigned char*) (model + 0x96c))
            level = (float) *(unsigned char*) (model + 0x96c) - 1.0f;
        else if (level < 0.0f)
            level = 0.0f;
        index = (int) level;
        page = model + 0xf4 + index * 0x198;
    } else {
        selected = (*(unsigned char*) (object + 0x213) & 0x30) >> 4;
        index = __max(0, __min(*(unsigned char*) (model + 0x96c) - 1, selected - 1));
        page = model + 0xf4 + index * 0x198;
    }
    if (*(int*) (page + 8) == 0 || *(int*) (page + 0xc) == 0)
        return 0;
    if (page != *(char**) (object + 0x1cc) || d3_LightingUpdatePending)
        object[0x210] |= 0x40;
    return page;
}
#else
/* ADDRESS: GOLDTL 0x004382e0 */
int __cdecl d3_SelectObjectLod(char* obj)
{
	float dx;
	float dy;
	float dz;
	float fn;
	char* ext;
	char* entry;
	int res;
	int idx;
	int max_idx;
	unsigned char n;

	res = 0;
	ext = *(char**) (obj + 0x1ec);
	if (ext == 0) {
		return res;
	}
	n = *(unsigned char*) (ext + 0x163c);
	if (n == 0) {
		return res;
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
		float dist;

		dx = *(float*) (obj + 0x4c) - *(float*) (d3_ActiveCamera + 0x4c);
		dy = *(float*) (obj + 0x50) - *(float*) (d3_ActiveCamera + 0x50);
		dz = *(float*) (obj + 0x54) - *(float*) (d3_ActiveCamera + 0x54);
		fn = (float) *(unsigned char*) (ext + 0x163c);
		dist = sqrt(dz * dz + dy * dy + dx * dx);
		dist = dist * fn * g_1042a10;
		idx = (int) dist;
		if (idx >= *(unsigned char*) (ext + 0x163c)) {
			dist = fn - 1.0f;
		}
		else if (dist < flt_0_0) {
			dist = flt_0_0;
		}
		idx = (int) dist;
		entry = ext + 0xf4 + idx * 0x4a4;
	}
	if (*(int*) (entry + 0x310) == 0 || *(int*) (entry + 0x314) == 0) {
		return res;
	}
	if (entry == *(char**) (obj + 0x1cc)) {
		return (int) entry;
	}
	*(unsigned char*) (obj + 0x214) |= 0x10;
	return (int) entry;
}
#endif
