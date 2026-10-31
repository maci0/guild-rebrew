#include <stdio.h>
#include <string.h>

#include "Develop/Units/d3/d3_animation.h"

extern int gv_00675318;
void __cdecl fcn_0042e540(char* name);
int __cdecl fcn_00413190(int object);

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
        *(int*) &opt = 0;
        opt.mode = 0;
        opt.queue = 1;
        opt.layer = (force & 1) << 3 | 0x10;
        opt.loop = 1;
        opt.reverse = 1;
        if (!fcn_00433ba0(ani)) {
            if (strcmp(name, "bewegung/gehen") == 0 ||
                strcmp(name, "bewegung/karren_ziehen") == 0) {
                d3_LoadAnimStream(path, ani, 1);
            } else {
                d3_LoadAnimStream(path, ani, 0);
            }
        }
        anim = fcn_00434970(*(char**) (*(char**) (obj + 0x34) + 0x1ec) + 0xf4, ani, opt);
        if (!anim) {
            sprintf(msg, "ch_AttachAni(): Could not attach ani: %s", name);
            return 0;
        }
        if (fcn_00413190(*(int*) (obj + 0x88)) == 0) {
            *(int*) (anim + 0x3c) = -1;
        } else {
            int frame = gv_00675318;
            *(int*) (anim + 0x3c) = frame;
        }
    }
    *(char**) (obj + 0x70) = anim;
    *(char*) (obj + 0x85) = -1;
    return anim;
}
#pragma auto_inline(on)
