#include <stdio.h>
#include <string.h>

#include "Develop/Units/d3/d3_animation.h"

extern int g_675318;
void __cdecl fcn_0042e540(char* name);
int __cdecl fcn_00413190(char* object);

#pragma intrinsic(memcmp, memcpy, memset, strcmp, strcpy, strlen, abs, labs, fabs)
#pragma auto_inline(off)
/* ADDRESS: GOLDTL 0x00404dc0 */
char* __cdecl ch_AttachAni(char* obj, char* name, unsigned char force)
{
    D3_ANIMATION_OPTIONS opt;
    char* anim;
    char ani[0x110];
    char path[0x110];
    char msg[0x200];

    fcn_0042e540(name);
    sprintf(path, "character/%s/%s_%s.baf", obj + 0x130, name, obj + 0x130);
    sprintf(ani, "%s_%s", name, obj + 0x130);
    fcn_0042e540(ani);
    if (*name) {
        memset(&opt, 0, sizeof(opt));
        opt.reverse = 1;
        opt.loop = 1;
        opt.queue = 1;
        opt.layer = ((force & 1) << 3) | 0x10;
        if (!fcn_00433ba0(ani)) {
            d3_LoadAnimStream(path, ani,
                strcmp(name, "bewegung/gehen") == 0 ||
                strcmp(name, "bewegung/karren_ziehen") == 0);
        }
        anim = fcn_00434970(*(char**) (*(char**) (obj + 0x34) + 0x1ec) + 0xf4, ani, opt);
        if (!anim) {
            sprintf(msg, "ch_AttachAni(): Could not attach ani: %s", name);
            return 0;
        }
        if (!fcn_00413190(*(char**) (obj + 0x88)))
            *(int*) (anim + 0x3c) = -1;
        else
            *(int*) (anim + 0x3c) = g_675318;
    }
    *(char**) (obj + 0x70) = anim;
    *(char*) (obj + 0x85) = -1;
    return anim;
}
#pragma auto_inline(on)
