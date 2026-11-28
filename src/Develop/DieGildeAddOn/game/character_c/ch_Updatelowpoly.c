#include <math.h>
#include <stdio.h>
#include <string.h>

#if defined(REBREW_GOLD)
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
void __cdecl d3_SetObjectVisible(char*, int);
void __cdecl d3_UpdateObjectLighting(char*);
int __cdecl CompareVector3WithinTolerance(float*, float*, float);
void __cdecl d3_SetNodePosition(char*, float*);
void __cdecl d3_SetObjectRotation(char*, float*);
int __cdecl d3_FindAnimByName(char*);
void __cdecl d3_LoadAnimStream(char*, char*, int);
char* __cdecl d3_AttachAnimationToContext(char*, char*, D3_ANIMATION_OPTIONS);
char* __cdecl vfs_ToSlashes(char*);
void __cdecl d3_RemoveObjectAnim(char*);
#define I32(p) (*(int*)(p))
#define F32(p) (*(float*)(p))
/* ADDRESS: GOLD 0x00402ba0 */
void __cdecl ch_Updatelowpoly(char* character)
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
                d3_SetObjectVisible(*(char**)(character + 0x34), 0);
            low = *(char**)(character + 0x22c);
            if (I32(low + 0x218) == 1) {
                d3_SetObjectVisible(low, 1);
                d3_UpdateObjectLighting(*(char**)(character + 0x22c));
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
                d3_SetObjectVisible(*(char**)(character + 0x34), 0);
            if ((I32(character + 0x2c) == I32(0x5f1294) && I32(character + 0x30) == I32(0x5f1298)) || !I32(character + 0x30)) {
                if (I32(*(char**)(character + 0x22c) + 0x218) == 1 && !(character[0x8c] & 0x20)) {
                    d3_SetObjectVisible(*(char**)(character + 0x22c), 1);
                    d3_UpdateObjectLighting(*(char**)(character + 0x22c));
                }
            } else if (I32(*(char**)(character + 0x22c) + 0x218) != 1) {
                d3_SetObjectVisible(*(char**)(character + 0x22c), 0);
            }
            if (I32(*(char**)(character + 0x22c) + 0x218) != 1 && I32(*(char**)(character + 0x22c) + 0x1cc) &&
                !CompareVector3WithinTolerance((float*)(*(char**)(character + 0x22c) + 0x4c), (float*)(*(char**)(character + 0x34) + 0x4c), 2.0f))
                d3_SetNodePosition(*(char**)(character + 0x22c), (float*)(*(char**)(character + 0x34) + 0x4c));
            if (I32(*(char**)(character + 0x34) + 0x1cc) &&
                !CompareVector3WithinTolerance((float*)(*(char**)(character + 0x22c) + 0x84), (float*)(*(char**)(character + 0x34) + 0x84), 0.05f))
                d3_SetObjectRotation(*(char**)(character + 0x22c), (float*)(*(char**)(character + 0x34) + 0x84));
            if (0) {
            highpoly_model:
                if (I32(high + 0x218) == 1 && !(flags & 0x20)) {
                    d3_SetObjectVisible(high, 1);
                    d3_UpdateObjectLighting(*(char**)(character + 0x34));
                }
                if (I32(*(char**)(character + 0x22c) + 0x218) != 1)
                    d3_SetObjectVisible(*(char**)(character + 0x22c), 0);
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
                    d3_LoadAnimStream(path, name, 1);
                attached = d3_AttachAnimationToContext(*(char**)(*(char**)(character + 0x22c) + 0x1ec) + 0xf4, name, opt);
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
                d3_SetObjectVisible(*(char**)(character + 0x34), 1);
                d3_UpdateObjectLighting(*(char**)(character + 0x34));
            }
        } else if (I32(*(char**)(character + 0x34) + 0x218) != 1) {
            d3_SetObjectVisible(*(char**)(character + 0x34), 0);
        }
    } else {
        high = *(char**)(character + 0x34);
        if (I32(high + 0x218) == 1 && !(character[0x8c] & 0x20)) {
            d3_SetObjectVisible(high, 1);
            d3_UpdateObjectLighting(*(char**)(character + 0x34));
        }
    }
    low = *(char**)(character + 0x22c);
    if (I32(low + 0x218) != 1)
        d3_SetObjectVisible(low, 0);
}
#else
#ifndef REBREW_SERVER
#include "Develop/DieGildeAddOn/game/ch_script.h"
#endif
void __cdecl d3_SetNodePosition(char*, int*);
#include "Develop/DieGildeAddOn/game/ch_ground.h"
#ifdef REBREW_GOLD
void __cdecl d3_UpdateObjectLighting(char*);
#endif
#include "../ch_motion.h"

#include "../../../Units/d3/d3_object.h"

#ifdef REBREW_GOLD
#define fcn_00443900 fcn_00447fd0
#define d3_GetContextIndex d3_GetSceneContextIndex
#define fcn_00402aa0 fcn_00402540
#define fcn_0040cfb0 fcn_0040c090
#endif

char __cdecl d3_MoveObjectToScene(void*, void*, void*);
void __cdecl d3_SetObjectPosition(void*, float*);
int __cdecl d3_GetContextIndex(void*);
void __cdecl ch_EnsureCharacterMeshes(char*);
void __cdecl ch_RunAnimationScript();
char* __cdecl ch_CreateQueuedAction(char*, void (__cdecl*)(), unsigned char, int, ...);
void __cdecl evt_LogScriptError(char*, int, const char*);

#include "Develop/DieGildeAddOn/game/game_data.h"

char* __cdecl d3sm_GetObjectSuperMap(char*);
#include "Develop/Units/d3/client_scene_transform.h"
float __cdecl d3_ComputeYawToTarget(char*, float*);
void __cdecl d3_SetObjectRotation(char*, float*);
char __cdecl d3sm_SampleHeight(char*, float*, int*, int*, float*);
void __cdecl d3_GetFloorHeight(char*, float*, int, int*, int*, float*);
extern float g_6628a8;
#include "../../../Units/d3/d3_animation.h"

#include "../../../Units/d3/d3_camera.h"
extern char g_10432c0[];

char __cdecl d3_SetObjectVisible(char*, char);

void __cdecl d3_SetNodePosition(char*, int*);
void __cdecl d3_SetObjectRotation(char*, float*);
void __cdecl vfs_ToSlashes(char*);
int __cdecl d3_RemoveObjectAnim(char*);




extern char g_6b5c60[];
D3_OBJECT* __cdecl d3_CreateSceneModelObject(D3_OBJECT*, float*, float*, char*);
void __cdecl d3_InvalidateSubTreeFlags(char*, int);
void __cdecl ch_PreloadCharacterMotions(char*, int, ...);
void __cdecl d3_PreloadLowPolyAnims(char*, int, ...);

#include <stdarg.h>
#include "../ch_queue.h"
#include "Develop/Units/Error/error_message.h"

#ifdef REBREW_GOLD
#define ch_UNIVERSE_STRIDE 0x3e0
#else
#define ch_UNIVERSE_STRIDE 0x3dc
#endif

#undef ch_UNIVERSE_STRIDE
/* ADDRESS: GOLDTL 0x004033e0 */
void __cdecl ch_Updatelowpoly(char* obj)
{
	D3_ANIMATION_OPTIONS opt;
	char ani[0x100];
	char path[0x100];
	char msg[0x200];
	float dx, dy, dz;
	char* anim;
	unsigned short flags;

	if (*(char**) (obj + 0x22c) == 0) {
		return;
	}
	if (ch_LowPolyMode != 0) {
		*(int*) (*(char**) (obj + 0x22c) + 0x204) = *(int*) (*(char**) (obj + 0x34) + 0x204);
		*(int*) (*(char**) (obj + 0x22c) + 0x48) = *(int*) (*(char**) (obj + 0x34) + 0x48);
		flags = *(unsigned short*) (obj + 0x8c);
		if ((flags & 0x200) != 0) {
			if (*(int*) (*(char**) (obj + 0x34) + 0x218) != 1) {
				d3_SetObjectVisible(*(char**) (obj + 0x34), 0);
			}
			if (*(int*) (*(char**) (obj + 0x22c) + 0x218) == 1) {
				d3_SetObjectVisible(*(char**) (obj + 0x22c), 1);
			}
			return;
		}
		if (*(char**) (obj + 0x88) == g_10432c0) {
			if (ch_LowPolyMode != 1) {
				goto lowpoly_model;
			}
			if (d3_ActiveCamera == 0) {
				goto lowpoly_model;
			}
			dx = *(float*) (d3_ActiveCamera + 0x4c) - *(float*) (*(char**) (obj + 0x34) + 0x4c);
			dy = *(float*) (d3_ActiveCamera + 0x50) - *(float*) (*(char**) (obj + 0x34) + 0x50);
			dz = *(float*) (d3_ActiveCamera + 0x54) - *(float*) (*(char**) (obj + 0x34) + 0x54);
			dz = (float) sqrt(dz * dz + dy * dy + dx * dx);
			if (!(dz < 1500.0f)) {
			lowpoly_model:
				if (*(int*) (*(char**) (obj + 0x34) + 0x218) != 1) {
					d3_SetObjectVisible(*(char**) (obj + 0x34), 0);
				}
				if ((*(int*) (obj + 0x2c) == g_67530c && *(int*) (obj + 0x30) == g_675310) || *(int*) (obj + 0x30) == 0) {
					if (*(int*) (*(char**) (obj + 0x22c) + 0x218) == 1 && (obj[0x8c] & 0x20) == 0) {
						d3_SetObjectVisible(*(char**) (obj + 0x22c), 1);
					}
				} else {
					if (*(int*) (*(char**) (obj + 0x22c) + 0x218) != 1) {
						d3_SetObjectVisible(*(char**) (obj + 0x22c), 0);
					}
				}
				if (*(int*) (*(char**) (obj + 0x22c) + 0x218) != 1
				    && *(char**) (*(char**) (obj + 0x22c) + 0x1cc) != 0
				    && !CompareVector3WithinTolerance((float*) (*(char**) (obj + 0x22c) + 0x4c),
				                       (float*) (*(char**) (obj + 0x34) + 0x4c), 2.0f)) {
					d3_SetNodePosition(*(char**) (obj + 0x22c), (int*) (*(char**) (obj + 0x34) + 0x4c));
				}
				if (*(char**) (*(char**) (obj + 0x34) + 0x1cc) != 0
				    && !CompareVector3WithinTolerance((float*) (*(char**) (obj + 0x22c) + 0x84),
				                       (float*) (*(char**) (obj + 0x34) + 0x84), 0.05f)) {
					d3_SetObjectRotation(*(char**) (obj + 0x22c), (float*) (*(char**) (obj + 0x34) + 0x84));
				}
			} else {
				if (*(int*) (*(char**) (obj + 0x34) + 0x218) == 1 && (flags & 0x20) == 0) {
					d3_SetObjectVisible(*(char**) (obj + 0x34), 1);
				}
				if (*(int*) (*(char**) (obj + 0x22c) + 0x218) != 1) {
					d3_SetObjectVisible(*(char**) (obj + 0x22c), 0);
				}
			}
			if (*(char**) (*(char**) (obj + 0x22c) + 0x1cc) == 0 || (obj[0x8c] & 0x80) != 0) {
				return;
			}
			if (*(char**) (obj + 0x70) != 0
			    && *(char**) (*(char**) (*(char**) (obj + 0x22c) + 0x1cc) + 0x390) == 0) {
				if (!strstr(*(char**) (*(char**) (obj + 0x70) + 0x68), "gehen")
				    && !strstr(*(char**) (*(char**) (obj + 0x70) + 0x68), "karren_ziehen")) {
					return;
				}
				sprintf(path, "lowpolycharacter/%s/%s_%s_LOW.baf", obj + 0x230, "gehen", obj + 0x230);
				sprintf(ani, "%s_%s_LOW.baf", "gehen", obj + 0x230);
				vfs_ToSlashes(ani);
				memset(&opt, 0, sizeof(opt));
				opt.queue = 1;
				*(int*) &opt = 0;
				opt.layer = 8;
				opt.mode = 0;
				opt.reverse = 0;
				opt.loop = 0;
				if (d3_FindAnimByName(ani) == 0) {
					d3_LoadAnimStream(path, ani, 1);
				}
				anim = d3_AttachAnimationToContext(*(char**) (*(char**) (obj + 0x22c) + 0x1ec) + 0xf4, ani, opt);
				if (anim == 0) {
					sprintf(msg, "ch_Updatelowpoly(): Could not attach ani: %s", path);
					*(unsigned short*) (obj + 0x8c) |= 0x80;
					return;
				}
				*(int*) (*(char**) (*(char**) (obj + 0x22c) + 0x1cc) + 0x328) = **(int**) (obj + 0x70);
				*(int*) (anim + 0x3c) = -1;
				return;
			}
			if (*(char**) (obj + 0x70) == 0
			    && *(char**) (*(char**) (*(char**) (obj + 0x22c) + 0x1cc) + 0x390) != 0) {
				d3_RemoveObjectAnim(*(char**) (obj + 0x22c));
				return;
			}
			if (*(char**) (obj + 0x70) != 0
			    && *(char**) (*(char**) (*(char**) (obj + 0x22c) + 0x1cc) + 0x390) != 0) {
				*(int*) (*(char**) (*(char**) (obj + 0x22c) + 0x1cc) + 0x388) = *(int*) (*(char**) (obj + 0x70) + 0x60);
			}
			return;
		}
		if ((*(int*) (obj + 0x2c) == g_67530c && *(int*) (obj + 0x30) == g_675310) || *(int*) (obj + 0x30) == 0) {
			if (*(int*) (*(char**) (obj + 0x34) + 0x218) == 1 && (flags & 0x20) == 0) {
				d3_SetObjectVisible(*(char**) (obj + 0x34), 1);
			}
		} else {
			if (*(int*) (*(char**) (obj + 0x34) + 0x218) != 1) {
				d3_SetObjectVisible(*(char**) (obj + 0x34), 0);
			}
		}
	} else {
		if (*(int*) (*(char**) (obj + 0x34) + 0x218) == 1 && (obj[0x8c] & 0x20) == 0) {
			d3_SetObjectVisible(*(char**) (obj + 0x34), 1);
		}
	}
	if (*(int*) (*(char**) (obj + 0x22c) + 0x218) != 1) {
		d3_SetObjectVisible(*(char**) (obj + 0x22c), 0);
	}
}
#endif
