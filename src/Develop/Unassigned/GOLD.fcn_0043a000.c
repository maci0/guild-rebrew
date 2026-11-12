#include <math.h>
#include "client_types.h"
#include "client_lighting.h"
#include "Develop/Units/d3/d3_camera.h"

/* ADDRESS: GOLD 0x0043a000 */
char* __cdecl fcn_0043a000(char* object)
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
    count = *(unsigned char*) (model + 0x96c);
    if (count == 0)
        return 0;
    selected = (*(unsigned char*) (object + 0x213) & 0x30) >> 4;
    eye = g_6b8014;
    if (selected == 0 && eye) {
        delta = *(VECTOR3*) (object + 0x4c);
        delta.x -= *(float*) (eye + 0x4c);
        delta.y -= *(float*) (eye + 0x50);
        delta.z -= *(float*) (eye + 0x54);
        level = (float) sqrt(delta.z * delta.z + delta.y * delta.y + delta.x * delta.x)
            * (float) count * *(float*) 0xfc2dd4;
        if ((int) level >= count)
            level = (float) count - 1.0f;
        else if (level < 0.0f)
            level = 0.0f;
        index = (int) level;
    } else {
        index = count - 1;
        selected--;
        if (index >= selected)
            index = selected;
        if (index < 0)
            index = 0;
    }
    page = model + 0xf4 + index * 0x198;
    if (*(int*) (page + 8) == 0 || *(int*) (page + 0xc) == 0)
        return 0;
    if (page != *(char**) (object + 0x1cc) || LightingUpdatePending)
        object[0x210] |= 0x40;
    return page;
}
