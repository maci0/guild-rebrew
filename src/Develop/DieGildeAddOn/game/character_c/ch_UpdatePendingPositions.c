#ifndef REBREW_SERVER
#include "Develop/DieGildeAddOn/game/ch_script.h"
#endif
void __cdecl d3_SetNodePosition(char*, int*);
#include "Develop/DieGildeAddOn/game/ch_ground.h"
#ifdef REBREW_GOLD
void __cdecl d3_UpdateObjectLighting(char*);
#endif
#include <stdio.h>
#include <string.h>
#include "../ch_motion.h"

#include "../../../Units/d3/d3_object.h"

#ifdef REBREW_GOLD
#define fcn_00443900 fcn_00447fd0
#define d3_GetContextIndex fcn_00411be0
#define fcn_00402aa0 fcn_00402540
#define fcn_0040cfb0 fcn_0040c090
#endif

char __cdecl fcn_00443900(void*, void*, void*);
void __cdecl d3_SetObjectPosition(void*, float*);
int __cdecl d3_GetContextIndex(void*);
void __cdecl fcn_00402aa0(char*);
void __cdecl ch_RunAnimationScript();
char* __cdecl ch_CreateQueuedAction(char*, void (__cdecl*)(), unsigned char, int, ...);
void __cdecl evt_LogScriptError(char*, int, const char*);

#include "Develop/DieGildeAddOn/game/game_data.h"
#include <math.h>

char* __cdecl d3sm_GetObjectSuperMap(char*);
#include "../client_scene_transform.h"
float __cdecl d3_ComputeYawToTarget(char*, float*);
void __cdecl d3_SetObjectRotation(char*, float*);
char __cdecl fcn_0045b990(char*, float*, int*, int*, float*);
void __cdecl fcn_00441720(char*, float*, int, int*, int*, float*);
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
D3_OBJECT* __cdecl fcn_00442910(D3_OBJECT*, float*, float*, char*);
void __cdecl d3_InvalidateSubTreeFlags(char*, int);
void __cdecl ch_PreloadCharacterMotions(char*, int, ...);
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

	p = (char**) ch_CharacterSlots;
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
	} while ((int) p < (int) ((char**) ch_CharacterSlots + 0x300));
}
