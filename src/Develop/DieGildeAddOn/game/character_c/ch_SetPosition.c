#ifndef REBREW_SERVER
#include "Develop/DieGildeAddOn/game/ch_script.h"
#endif
void __cdecl fcn_00438b40(char*, int*);
#include "Develop/DieGildeAddOn/game/ch_ground.h"
#ifdef REBREW_GOLD
void __cdecl fcn_00453270(char*);
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

extern void* ch_CharacterSlots[];
#include <math.h>

char* __cdecl fcn_00402610(char*);
#include "../client_scene_transform.h"
float __cdecl fcn_00444700(char*, float*);
void __cdecl d3_SetObjectRotation(char*, float*);
char __cdecl fcn_0045b990(char*, float*, int*, int*, float*);
void __cdecl fcn_00441720(char*, float*, int, int*, int*, float*);
extern float g_6628a8;
#include "../../../Units/d3/d3_animation.h"

extern int ch_LowPolyMode;
#include "../../../Units/d3/d3_camera.h"
extern int g_67530c;
extern int g_675310;
extern char g_10432c0[];

char __cdecl fcn_00442c00(char*, char);

void __cdecl fcn_00438b40(char*, int*);
void __cdecl d3_SetObjectRotation(char*, float*);
void __cdecl vfs_ToSlashes(char*);
int __cdecl d3_RemoveObjectAnim(char*);


extern char g_6b5c60[];
D3_OBJECT* __cdecl fcn_00442910(D3_OBJECT*, float*, float*, char*);
void __cdecl fcn_00438ac0(char*, int);
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
void __cdecl ch_Updatelowpoly(char* obj);
void __cdecl ch_UpdateAttachedModelPosition(char* obj, unsigned char force);
void __cdecl ch_SetPosition(char* obj, float* pos, int flag)
{
	fcn_00438b40(*(char**) (obj + 0x34), (int*) pos);
#ifdef REBREW_GOLD
	if (flag != 0) {
		fcn_00453270(*(char**) (obj + 0x34));
	}
#endif
	ch_PlaceOnGround(obj, 0);
	if (*(int*) ((char*) obj + 0x124) != 0) {
		ch_UpdateAttachedModelPosition(obj, 0);
#ifdef REBREW_GOLD
		if (flag != 0) {
			fcn_00453270(**(char***) (obj + 0x124));
		}
#endif
	}
	if (*(int*) ((char*) obj + 0x22c) != 0) {
		ch_Updatelowpoly(obj);
	}
}
