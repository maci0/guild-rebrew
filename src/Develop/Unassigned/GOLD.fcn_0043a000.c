#include <math.h>
#include <stdlib.h>
#include "client_types.h"
#include "client_lighting.h"
#include "Develop/Units/d3/d3_camera.h"

/* ADDRESS: GOLD 0x0043a000 */
char* __cdecl d3_SelectObjectLod(char* object)
{
    char* model;
    char* eye;
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

    eye = d3_ActiveCamera;
    if ((*(unsigned char*) (object + 0x213) & 0x30) == 0 && eye) {
        delta = *(VECTOR3*) (object + 0x4c);
        delta.x -= *(float*) (eye + 0x4c);
        delta.y -= *(float*) (eye + 0x50);
        delta.z -= *(float*) (eye + 0x54);
        level = (float) sqrt(delta.z * delta.z + delta.y * delta.y + delta.x * delta.x)
            * (float) *(unsigned char*) (model + 0x96c) * *(float*) 0xfc2dd4;
        if ((int) level >= *(unsigned char*) (model + 0x96c))
            level = (float) *(unsigned char*) (model + 0x96c) - 1.0f;
        else if (level < 0.0f)
            level = 0.0f;
        index = (int) level;
    } else {
        selected = (*(unsigned char*) (object + 0x213) & 0x30) >> 4;
        index = __max(0, __min(*(unsigned char*) (model + 0x96c) - 1, selected - 1));
    }
    page = model + 0xf4 + index * 0x198;
    if (*(int*) (page + 8) == 0 || *(int*) (page + 0xc) == 0)
        return 0;
    if (page != *(char**) (object + 0x1cc) || d3_LightingUpdatePending)
        object[0x210] |= 0x40;
    return page;
}
