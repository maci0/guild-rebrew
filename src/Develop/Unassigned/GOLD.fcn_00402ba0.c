#include <math.h>
#include <stdio.h>
#include <string.h>
typedef struct D3_ANIMATION_OPTIONS {
    unsigned char mode;
    unsigned char layer;
    unsigned char pad2[2];
    unsigned int loop : 1;
    unsigned int reverse : 1;
    unsigned int pad4 : 30;
    unsigned char blend : 1;
    unsigned char queue : 1;
    unsigned char pad8[3];
} D3_ANIMATION_OPTIONS;
void __cdecl fcn_00442c00(char*, int);
void __cdecl fcn_00453270(char*);
int __cdecl CompareVector3WithinTolerance(float*, float*, float);
void __cdecl fcn_00438b40(char*, float*);
void __cdecl d3_SetObjectRotation(char*, float*);
int __cdecl d3_FindAnimByName(char*);
void __cdecl fcn_0044e4a0(char*, char*, int);
char* __cdecl fcn_00435550(char*, char*, D3_ANIMATION_OPTIONS);
char* __cdecl vfs_ToSlashes(char*);
void __cdecl d3_RemoveObjectAnim(char*);
#define I32(p) (*(int*)(p))
#define F32(p) (*(float*)(p))
/* ADDRESS: GOLD 0x00402ba0 */
void __cdecl fcn_00402ba0(char* character)
{
    D3_ANIMATION_OPTIONS opt;
    char name[256];
    char path[256];
    char error[512];
    char* low;
    char* high;
    char* animation;
    char* attached;
    float dx;
    float dy;
    float dz;
    unsigned short flags;
    low = *(char**)(character + 0x22c);
    if (!low)
        return;
    if (I32(0x631064)) {
        I32(low + 0x200) = I32(*(char**)(character + 0x34) + 0x200);
        I32(*(char**)(character + 0x22c) + 0x48) = I32(*(char**)(character + 0x34) + 0x48);
        flags = *(unsigned short*)(character + 0x8c);
        if (flags & 0x200) {
            if (I32(*(char**)(character + 0x34) + 0x218) != 1)
                fcn_00442c00(*(char**)(character + 0x34), 0);
            low = *(char**)(character + 0x22c);
            if (I32(low + 0x218) == 1) {
                fcn_00442c00(low, 1);
                fcn_00453270(*(char**)(character + 0x22c));
            }
            return;
        }
        if (I32(character + 0x88) == 0xfd7ba0) {
            if (I32(0x631064) != 1 || !I32(0xfc2dec)) {
                goto lowpoly_model;
            }
            high = *(char**)(character + 0x34);
            dx = F32(I32(0xfc2dec) + 0x4c) - F32(high + 0x4c);
            dy = F32(I32(0xfc2dec) + 0x50) - F32(high + 0x50);
            dz = F32(I32(0xfc2dec) + 0x54) - F32(high + 0x54);
            dz = (float)sqrt(dz * dz + dy * dy + dx * dx);
            if (dz < 1500.0f)
                goto highpoly_model;
            lowpoly_model:
            if (I32(*(char**)(character + 0x34) + 0x218) != 1)
                fcn_00442c00(*(char**)(character + 0x34), 0);
            if ((I32(character + 0x2c) == I32(0x5f1294) && I32(character + 0x30) == I32(0x5f1298)) || !I32(character + 0x30)) {
                if (I32(*(char**)(character + 0x22c) + 0x218) == 1 && !(character[0x8c] & 0x20)) {
                    fcn_00442c00(*(char**)(character + 0x22c), 1);
                    fcn_00453270(*(char**)(character + 0x22c));
                }
            } else if (I32(*(char**)(character + 0x22c) + 0x218) != 1) {
                fcn_00442c00(*(char**)(character + 0x22c), 0);
            }
            if (I32(*(char**)(character + 0x22c) + 0x218) != 1 && I32(*(char**)(character + 0x22c) + 0x1cc) &&
                !CompareVector3WithinTolerance((float*)(*(char**)(character + 0x22c) + 0x4c), (float*)(*(char**)(character + 0x34) + 0x4c), 2.0f))
                fcn_00438b40(*(char**)(character + 0x22c), (float*)(*(char**)(character + 0x34) + 0x4c));
            if (I32(*(char**)(character + 0x34) + 0x1cc) &&
                !CompareVector3WithinTolerance((float*)(*(char**)(character + 0x22c) + 0x84), (float*)(*(char**)(character + 0x34) + 0x84), 0.05f))
                d3_SetObjectRotation(*(char**)(character + 0x22c), (float*)(*(char**)(character + 0x34) + 0x84));
            if (0) {
            highpoly_model:
                if (I32(high + 0x218) == 1 && !(flags & 0x20)) {
                    fcn_00442c00(high, 1);
                    fcn_00453270(*(char**)(character + 0x34));
                }
                if (I32(*(char**)(character + 0x22c) + 0x218) != 1)
                    fcn_00442c00(*(char**)(character + 0x22c), 0);
            }
            animation = *(char**)(*(char**)(character + 0x22c) + 0x1cc);
            if (!animation || (*(signed char*)(character + 0x8c) & 0x80))
                return;
            high = *(char**)(character + 0x70);
            if (high && !I32(animation + 0x84)) {
                if (!strstr(*(char**)(high + 0x68), "gehen") &&
                    !strstr(*(char**)(*(char**)(character + 0x70) + 0x68), "karren_ziehen"))
                    return;
                sprintf(path, "lowpolycharacter/%s/%s_%s_LOW.baf", character + 0x230, "gehen", character + 0x230);
                sprintf(name, "%s_%s_LOW.baf", "gehen", character + 0x230);
                vfs_ToSlashes(name);
                memset(&opt, 0, sizeof(opt));
                opt.queue = 1;
                *(int*)&opt = 0;
                opt.layer = 8;
                opt.mode = 0;
                opt.reverse = 0;
                opt.loop = 0;
                if (!d3_FindAnimByName(name))
                    fcn_0044e4a0(path, name, 1);
                attached = fcn_00435550(*(char**)(*(char**)(character + 0x22c) + 0x1ec) + 0xf4, name, opt);
                if (!attached) {
                    sprintf(error, "ch_Updatelowpoly(): Could not attach ani: %s", path);
                    *(unsigned char*)(character + 0x8c) |= 0x80;
                    return;
                }
                I32(*(char**)(*(char**)(character + 0x22c) + 0x1cc) + 0x1c) = I32(*(char**)(character + 0x70));
                I32(attached + 0x3c) = -1;
                return;
            }
            if (!high && I32(animation + 0x84)) {
                d3_RemoveObjectAnim(*(char**)(character + 0x22c));
                return;
            }
            if (high && I32(animation + 0x84))
                I32(animation + 0x7c) = I32(high + 0x60);
            return;
        }
        if ((I32(character + 0x2c) == I32(0x5f1294) && I32(character + 0x30) == I32(0x5f1298)) || !I32(character + 0x30)) {
            if (I32(*(char**)(character + 0x34) + 0x218) == 1 && !(flags & 0x20)) {
                fcn_00442c00(*(char**)(character + 0x34), 1);
                fcn_00453270(*(char**)(character + 0x34));
            }
        } else if (I32(*(char**)(character + 0x34) + 0x218) != 1) {
            fcn_00442c00(*(char**)(character + 0x34), 0);
        }
    } else {
        high = *(char**)(character + 0x34);
        if (I32(high + 0x218) == 1 && !(character[0x8c] & 0x20)) {
            fcn_00442c00(high, 1);
            fcn_00453270(*(char**)(character + 0x34));
        }
    }
    low = *(char**)(character + 0x22c);
    if (I32(low + 0x218) != 1)
        fcn_00442c00(low, 0);
}
