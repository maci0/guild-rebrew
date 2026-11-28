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

extern void* ch_CharacterSlots[];
#include <math.h>

char* __cdecl d3sm_GetObjectSuperMap(char*);
#include "Develop/Units/d3/client_scene_transform.h"
float __cdecl d3_ComputeYawToTarget(char*, float*);
void __cdecl d3_SetObjectRotation(char*, float*);
char __cdecl d3sm_3D2SuperMap(char*, float*, int*, int*, float*);
void __cdecl d3_GetFloorHeight(char*, float*, int, int*, int*, float*);
extern float flt_0_0;
#include "../../../Units/d3/d3_animation.h"

extern int ch_LowPolyMode;
#include "../../../Units/d3/d3_camera.h"
extern int g_67530c;
extern int g_675310;
extern char d3_Universes[];

char __cdecl d3_SetObjectVisible(char*, char);

void __cdecl d3_SetNodePosition(char*, int*);
void __cdecl d3_SetObjectRotation(char*, float*);
void __cdecl vfs_ToSlashes(char*);
int __cdecl d3_RemoveObjectAnim(char*);


extern char str_empty[];
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
void __cdecl ch_Updatelowpoly(char* obj);
void __cdecl ch_UpdateAttachedModelPosition(char* obj, unsigned char force);
/* ADDRESS: GOLDDE 0x00402360 */
void __cdecl ch_SetPosition(char* obj, float* pos, int flag)
{
	d3_SetNodePosition(*(char**) (obj + 0x34), (int*) pos);
#ifdef REBREW_GOLD
	if (flag != 0) {
		d3_UpdateObjectLighting(*(char**) (obj + 0x34));
	}
#endif
	ch_PlaceOnGround(obj, 0);
	if (*(int*) ((char*) obj + 0x124) != 0) {
		ch_UpdateAttachedModelPosition(obj, 0);
#ifdef REBREW_GOLD
		if (flag != 0) {
			d3_UpdateObjectLighting(**(char***) (obj + 0x124));
		}
#endif
	}
	if (*(int*) ((char*) obj + 0x22c) != 0) {
		ch_Updatelowpoly(obj);
	}
}
