#ifndef REBREW_SERVER
#include "Develop/DieGildeAddOn/game/ch_script.h"
#endif
void __cdecl fcn_00438b40(char*, int*);
void __cdecl fcn_004053a0(void*, int);
#ifdef REBREW_GOLD
void __cdecl fcn_00453270(char*);
#endif
#include <stdio.h>
#include <string.h>
#include "../ch_motion.h"

#include "../../../Units/d3/d3_object.h"

#ifdef REBREW_GOLD
#define fcn_00443900 fcn_00447fd0
#define fcn_00413190 fcn_00411be0
#define fcn_00402aa0 fcn_00402540
#define fcn_0040cfb0 fcn_0040c090
#endif

char __cdecl fcn_00443900(void*, void*, void*);
void __cdecl fcn_00438c40(void*, float*);
int __cdecl fcn_00413190(void*);
void __cdecl fcn_00402aa0(char*);
void __cdecl fcn_0040cfb0();
char* __cdecl fcn_0040c230(char*, void (__cdecl*)(), unsigned char, int, ...);
void __cdecl fcn_00425bf0(char*, int, const char*);

extern void* g_14d0020[];
#include <math.h>

char* __cdecl fcn_00402610(char*);
#include "../client_scene_transform.h"
float __cdecl fcn_00444700(char*, float*);
void __cdecl fcn_00438cb0(char*, float*);
char __cdecl fcn_0045b990(char*, float*, int*, int*, float*);
void __cdecl fcn_00441720(char*, float*, int, int*, int*, float*);
extern float g_6628a8;
#include "../../../Units/d3/d3_animation.h"

extern int g_6b5c34;
#include "../../../Units/d3/d3_camera.h"
extern int g_67530c;
extern int g_675310;
extern char g_10432c0[];

char __cdecl fcn_00442c00(char*, char);

void __cdecl fcn_00438b40(char*, int*);
void __cdecl fcn_00438cb0(char*, float*);
void __cdecl fcn_0042e540(char*);
int __cdecl fcn_00413120(char*);




extern char g_6b5c60[];
D3_OBJECT* __cdecl fcn_00442910(D3_OBJECT*, float*, float*, char*);
void __cdecl fcn_00438ac0(char*, int);
void __cdecl fcn_00404a00(char*, int, ...);
void __cdecl fcn_00404b60(char*, int, ...);

#include <stdarg.h>
#include "../ch_queue.h"
#include "Develop/Units/Error/error_message.h"

#ifdef REBREW_GOLD
#define ch_UNIVERSE_STRIDE 0x3e0
#else
#define ch_UNIVERSE_STRIDE 0x3dc
#endif

#undef ch_UNIVERSE_STRIDE
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
	if (g_6b5c34 != 0) {
		*(int*) (*(char**) (obj + 0x22c) + 0x204) = *(int*) (*(char**) (obj + 0x34) + 0x204);
		*(int*) (*(char**) (obj + 0x22c) + 0x48) = *(int*) (*(char**) (obj + 0x34) + 0x48);
		flags = *(unsigned short*) (obj + 0x8c);
		if ((flags & 0x200) != 0) {
			if (*(int*) (*(char**) (obj + 0x34) + 0x218) != 1) {
				fcn_00442c00(*(char**) (obj + 0x34), 0);
			}
			if (*(int*) (*(char**) (obj + 0x22c) + 0x218) == 1) {
				fcn_00442c00(*(char**) (obj + 0x22c), 1);
			}
			return;
		}
		if (*(char**) (obj + 0x88) == g_10432c0) {
			if (g_6b5c34 == 1 && g_6b8014 != 0
			    && (dx = *(float*) (g_6b8014 + 0x4c) - *(float*) (*(char**) (obj + 0x34) + 0x4c),
			         dy = *(float*) (g_6b8014 + 0x50) - *(float*) (*(char**) (obj + 0x34) + 0x50),
			         dz = *(float*) (g_6b8014 + 0x54) - *(float*) (*(char**) (obj + 0x34) + 0x54),
			         (float) sqrt(dz * dz + dy * dy + dx * dx) < 1500.0f)) {
				goto detailed_model;
			}
			if (*(int*) (*(char**) (obj + 0x34) + 0x218) != 1) {
				fcn_00442c00(*(char**) (obj + 0x34), 0);
			}
			if ((*(int*) (obj + 0x2c) == g_67530c && *(int*) (obj + 0x30) == g_675310) || *(int*) (obj + 0x30) == 0) {
				if (*(int*) (*(char**) (obj + 0x22c) + 0x218) == 1 && (obj[0x8c] & 0x20) == 0) {
					fcn_00442c00(*(char**) (obj + 0x22c), 1);
				}
			} else {
				if (*(int*) (*(char**) (obj + 0x22c) + 0x218) != 1) {
					fcn_00442c00(*(char**) (obj + 0x22c), 0);
				}
			}
			if (*(int*) (*(char**) (obj + 0x22c) + 0x218) != 1
			    && *(char**) (*(char**) (obj + 0x22c) + 0x1cc) != 0
			    && !fcn_00451840((float*) (*(char**) (obj + 0x22c) + 0x4c),
			                       (float*) (*(char**) (obj + 0x34) + 0x4c), 2.0f)) {
				fcn_00438b40(*(char**) (obj + 0x22c), (int*) (*(char**) (obj + 0x34) + 0x4c));
			}
			if (*(char**) (*(char**) (obj + 0x34) + 0x1cc) != 0
			    && !fcn_00451840((float*) (*(char**) (obj + 0x22c) + 0x84),
			                       (float*) (*(char**) (obj + 0x34) + 0x84), 0.05f)) {
				fcn_00438cb0(*(char**) (obj + 0x22c), (float*) (*(char**) (obj + 0x34) + 0x84));
			}
			goto animation;
		detailed_model:
			if (*(int*) (*(char**) (obj + 0x34) + 0x218) == 1 && (flags & 0x20) == 0) {
				fcn_00442c00(*(char**) (obj + 0x34), 1);
			}
			if (*(int*) (*(char**) (obj + 0x22c) + 0x218) != 1) {
				fcn_00442c00(*(char**) (obj + 0x22c), 0);
			}
		animation:
			if (*(char**) (*(char**) (obj + 0x22c) + 0x1cc) == 0 || (obj[0x8c] & 0x80) != 0) {
				return;
			}
			if (*(char**) (obj + 0x70) != 0) {
				if (*(char**) (*(char**) (*(char**) (obj + 0x22c) + 0x1cc) + 0x390) == 0) {
					if (!strstr(*(char**) (*(char**) (obj + 0x70) + 0x68), "gehen")
					    && !strstr(*(char**) (*(char**) (obj + 0x70) + 0x68), "karren_ziehen")) {
						return;
					}
					sprintf(path, "lowpolycharacter/%s/%s_%s_LOW.baf", obj + 0x230, "gehen", obj + 0x230);
					sprintf(ani, "%s_%s_LOW.baf", "gehen", obj + 0x230);
					fcn_0042e540(ani);
					memset(&opt, 0, sizeof(opt));
					opt.queue = 1;
					opt.reverse = 0;
					opt.loop = 0;
					*(int*) &opt = 0;
					opt.layer = 8;
					opt.mode = 0;
					if (fcn_00433ba0(ani) == 0) {
						d3_LoadAnimStream(path, ani, 1);
					}
					anim = fcn_00434970(*(char**) (*(char**) (obj + 0x22c) + 0x1ec) + 0xf4, ani, opt);
					if (anim == 0) {
						sprintf(msg, "ch_Updatelowpoly(): Could not attach ani: %s", path);
						obj[0x8c] |= 0x80;
						return;
					}
					*(int*) (*(char**) (*(char**) (obj + 0x22c) + 0x1cc) + 0x328) = **(int**) (obj + 0x70);
					*(int*) (anim + 0x3c) = -1;
					return;
				}
				if (*(char**) (obj + 0x70) != 0) {
					goto update_frame;
				}
			}
			if (*(char**) (*(char**) (*(char**) (obj + 0x22c) + 0x1cc) + 0x390) != 0) {
				fcn_00413120(*(char**) (obj + 0x22c));
				return;
			}
			if (*(char**) (obj + 0x70) == 0) {
				return;
			}
		update_frame:
			if (*(char**) (*(char**) (*(char**) (obj + 0x22c) + 0x1cc) + 0x390) == 0) {
				return;
			}
			*(int*) (*(char**) (*(char**) (obj + 0x22c) + 0x1cc) + 0x388) = *(int*) (*(char**) (obj + 0x70) + 0x60);
			return;
		}
		if ((*(int*) (obj + 0x2c) == g_67530c && *(int*) (obj + 0x30) == g_675310) || *(int*) (obj + 0x30) == 0) {
			if (*(int*) (*(char**) (obj + 0x34) + 0x218) == 1 && (flags & 0x20) == 0) {
				fcn_00442c00(*(char**) (obj + 0x34), 1);
			}
		} else {
			if (*(int*) (*(char**) (obj + 0x34) + 0x218) != 1) {
				fcn_00442c00(*(char**) (obj + 0x34), 0);
			}
		}
	} else {
		if (*(int*) (*(char**) (obj + 0x34) + 0x218) == 1 && (obj[0x8c] & 0x20) == 0) {
			fcn_00442c00(*(char**) (obj + 0x34), 1);
		}
	}
	if (*(int*) (*(char**) (obj + 0x22c) + 0x218) != 1) {
		fcn_00442c00(*(char**) (obj + 0x22c), 0);
	}
}
/* Layout scaffolding: shifts the next source object to its reference
 * VA. 0x90 filler, not reconstruction. Generated by the text lead pass. */
#pragma data_seg(".text")
unsigned char _tlead_ch_Updatelowpoly[32] = {
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90
};
