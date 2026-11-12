#include "client_scene_resources.h"
#include "Develop/Units/d3/d3_d3d.h"

typedef union ResourceStyle {
    unsigned int value;
    struct {
        unsigned char alpha;
        unsigned char unused;
        unsigned char b0 : 1;
        unsigned char flag : 1;
        unsigned char rest : 6;
        unsigned char high;
    } bits;
} ResourceStyle;

/* ADDRESS: GOLD 0x00448200 */
SCENE_RESOURCE* __cdecl fcn_00448200(const char* name, unsigned char flag)
{
    ResourceStyle style;
    SCENE_RESOURCE* resource;

    style.value = 0;
    style.bits.alpha = 0x7f;
    style.bits.flag = flag;
    if (d3d_Device != 0 && (*(unsigned char*)0xfe798c & 1)) {
        resource = fcn_004605b0(name, style.value, 0, 0);
        if (resource != 0) {
            fcn_00460e40(resource, 0);
        }
        return resource;
    }
    return 0;
}
