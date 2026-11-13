#include <math.h>
#include <stdio.h>
#include <string.h>
void __cdecl fcn_00442c00(char*, int);
void __cdecl fcn_00453270(char*);
int __cdecl CompareVector3WithinTolerance(float*, float*, float);
void __cdecl fcn_00438b40(char*, float*);
void __cdecl fcn_00438cb0(char*, float*);
int __cdecl fcn_00433f40(char*);
void __cdecl fcn_0044e4a0(char*, char*, int);
char* __cdecl fcn_00435550(char*, char*, int, int, int);
char* __cdecl vfs_ToSlashes(char*);
void __cdecl fcn_00411b70(char*);
#define I32(p) (*(int*)(p))
#define F32(p) (*(float*)(p))
/* ADDRESS: GOLD 0x00402ba0 */
void __cdecl fcn_00402ba0(char* character)
{
    char* low;
    char* high;
    char* animation;
    char* attached;
    float dx;
    float dy;
    float dz;
    char path[256];
    char name[256];
    char error[512];
    low = *(char**)(character + 0x22c);
    if (!low)
        return;
    high = *(char**)(character + 0x34);
    if (I32(0x631064)) {
        I32(low + 0x200) = I32(high + 0x200);
        I32(low + 0x48) = I32(high + 0x48);
        if (*(unsigned short*)(character + 0x8c) & 0x200) {
            if (I32(high + 0x218) != 1)
                fcn_00442c00(high, 0);
            low = *(char**)(character + 0x22c);
            if (I32(low + 0x218) == 1) {
                fcn_00442c00(low, 1);
                fcn_00453270(*(char**)(character + 0x22c));
            }
            return;
        }
        if (I32(character + 0x88) == 0xfd7ba0) {
            if (I32(0x631064) == 1 && I32(0xfc2dec)) {
                dx = F32(I32(0xfc2dec) + 0x4c) - F32(high + 0x4c);
                dy = F32(I32(0xfc2dec) + 0x50) - F32(high + 0x50);
                dz = F32(I32(0xfc2dec) + 0x54) - F32(high + 0x54);
                if (sqrt(dx * dx + (dy * dy + dz * dz)) < 1500.0f) {
                    if (I32(high + 0x218) == 1 && !(character[0x8c] & 0x20)) {
                        fcn_00442c00(high, 1);
                        fcn_00453270(*(char**)(character + 0x34));
                    }
                    if (I32(*(char**)(character + 0x22c) + 0x218) != 1)
                        fcn_00442c00(*(char**)(character + 0x22c), 0);
                    goto update_animation;
                }
            }
            high = *(char**)(character + 0x34);
            if (I32(high + 0x218) != 1)
                fcn_00442c00(high, 0);
            if ((I32(character + 0x2c) != I32(0x5f1294) || I32(character + 0x30) != I32(0x5f1298)) && I32(character + 0x30)) {
                if (I32(*(char**)(character + 0x22c) + 0x218) != 1)
                    fcn_00442c00(*(char**)(character + 0x22c), 0);
            } else if (I32(*(char**)(character + 0x22c) + 0x218) == 1 && !(character[0x8c] & 0x20)) {
                fcn_00442c00(*(char**)(character + 0x22c), 1);
                fcn_00453270(*(char**)(character + 0x22c));
            }
            low = *(char**)(character + 0x22c);
            high = *(char**)(character + 0x34);
            if (I32(low + 0x218) != 1 && I32(low + 0x1cc) &&
                !CompareVector3WithinTolerance((float*)(low + 0x4c), (float*)(high + 0x4c), 2.0f))
                fcn_00438b40(low, (float*)(high + 0x4c));
            high = *(char**)(character + 0x34);
            low = *(char**)(character + 0x22c);
            if (I32(high + 0x1cc) && !CompareVector3WithinTolerance((float*)(low + 0x84), (float*)(high + 0x84), 0.05f))
                fcn_00438cb0(low, (float*)(high + 0x84));
        update_animation:
            animation = *(char**)(*(char**)(character + 0x22c) + 0x1cc);
            if (!animation || (signed char)character[0x8c] < 0)
                return;
            high = *(char**)(character + 0x70);
            if (high && !I32(animation + 0x84)) {
                if (!strstr(*(char**)(high + 0x68), "gehen") &&
                    !strstr(*(char**)(*(char**)(character + 0x70) + 0x68), "karren_ziehen"))
                    return;
                sprintf(path, "lowpolycharacter/%s/%s_%s_LOW.baf", character + 0x230, "gehen", character + 0x230);
                sprintf(name, "%s_%s_LOW.baf", "gehen", character + 0x230);
                vfs_ToSlashes(name);
                if (!fcn_00433f40(name))
                    fcn_0044e4a0(path, name, 1);
                attached = fcn_00435550(*(char**)(*(char**)(character + 0x22c) + 0x1ec) + 0xf4, name, 0x800, 0, 2);
                if (!attached) {
                    sprintf(error, "ch_Updatelowpoly(): Could not attach ani: %s", path);
                    character[0x8c] |= 0x80;
                    return;
                }
                *(char**)(*(char**)(*(char**)(character + 0x22c) + 0x1cc) + 0x1c) = *(char**)(character + 0x70);
                I32(attached + 0x3c) = -1;
                return;
            }
            if (I32(animation + 0x84) && !high) {
                fcn_00411b70(*(char**)(character + 0x22c));
                return;
            }
            if (high && I32(animation + 0x84))
                I32(animation + 0x7c) = I32(high + 0x60);
            return;
        }
        if ((I32(character + 0x2c) != I32(0x5f1294) || I32(character + 0x30) != I32(0x5f1298)) && I32(character + 0x30)) {
            if (I32(high + 0x218) != 1)
                fcn_00442c00(high, 0);
        } else if (I32(high + 0x218) == 1 && !(character[0x8c] & 0x20)) {
            fcn_00442c00(high, 1);
            fcn_00453270(*(char**)(character + 0x34));
        }
    } else if (I32(high + 0x218) == 1 && !(character[0x8c] & 0x20)) {
        fcn_00442c00(high, 1);
        fcn_00453270(*(char**)(character + 0x34));
    }
    low = *(char**)(character + 0x22c);
    if (I32(low + 0x218) != 1)
        fcn_00442c00(low, 0);
}
