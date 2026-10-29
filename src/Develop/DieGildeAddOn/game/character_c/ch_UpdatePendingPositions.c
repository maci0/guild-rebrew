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
void __cdecl ch_UpdatePendingPositions(void)
{
	char** p;
	char* obj;
	char* task;
	float position[4];
	float value;

	p = (char**) g_14d0020;
	do {
		obj = *p;
		if (obj != 0 && (obj[0x8c] & 1) != 0
		    && *(int*) (obj + 0x88) == g_67a370) {
			value = *(float*) (*(char**) (obj + 0x34) + 0x4c);
			position[0] = value + *(float*) (obj + 0x54);
			value = *(float*) (*(char**) (obj + 0x34) + 0x50);
			position[1] = value + *(float*) (obj + 0x58);
			value = *(float*) (*(char**) (obj + 0x34) + 0x54);
			position[2] = value + *(float*) (obj + 0x5c);
			task = *(char**) (obj + 0x128);
			if (task != 0) {
				if (task[9] != '-') {
					ch_SetPosition(obj, position, 0);
				}
			} else {
				ch_SetPosition(obj, position, 0);
			}
			obj[0x8c] &= ~1;
		}
		p++;
	} while ((int) p < (int) ((char**) g_14d0020 + 0x300));
}
