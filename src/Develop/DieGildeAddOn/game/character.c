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
#include "ch_motion.h"

#include "../../Units/d3/d3_object.h"

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
#include "client_scene_transform.h"
float __cdecl fcn_00444700(char*, float*);
void __cdecl fcn_00438cb0(char*, float*);
char __cdecl fcn_0045b990(char*, float*, int*, int*, float*);
void __cdecl fcn_00441720(char*, float*, int, int*, int*, float*);
extern float g_6628a8;
#include "../../Units/d3/d3_animation.h"

extern int g_6b5c34;
#include "../../Units/d3/d3_camera.h"
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




#ifndef REBREW_SERVER
#include <stdarg.h>
#include "ch_queue.h"
#include "Develop/Units/Error/error_message.h"

#ifdef REBREW_GOLD
#define ch_UNIVERSE_STRIDE 0x3e0
#else
#define ch_UNIVERSE_STRIDE 0x3dc
#endif

/* Original character.c placement is inferred from the ch_ subsystem. */
/* ADDRESS: GOLDTL 0x004051d0 */
char* __cdecl ch_InsertAction(char* object, char* position, int kind, ...)
{
    /* Native initializes this fallback value only for an unregistered kind. */
    int original_kind;
    char* action;
    char* previous;
    int i;
    va_list arguments;

    if (position == 0) {
        return 0;
    }
    if (g_14d0c40[kind].handler == 0) {
        original_kind = kind;
        kind = 0;
    }
    action = (char*) ch_GetFreeQueueEntry();
    if (action == 0) {
        ReportClientMessage("ch_InsertAction(): Could not ch_GetFreeQueueEntry()");
        return 0;
    }
    previous = *(char**) (position + 0x24);
    *(char**) (position + 0x24) = action;
    *(char**) (action + 0x24) = previous;
    *(char**) (action + 0x28) = position;
    if (previous != 0) {
        *(char**) (previous + 0x28) = action;
    } else {
        *(char**) (*(char**) (position + 0x14) + 0x128) = action;
    }
    *(int*) action = g_14d0c40[kind].handler;
    *(char**) (action + 0x14) = object;
    action[9] = (char) kind;
    *(int*) (action + 0xc) = 0;
    va_start(arguments, kind);
    for (i = 0; i < g_14d0c40[(unsigned char) action[9]].param; i++) {
        ((int*) (action + 0x30))[i] = va_arg(arguments, int);
    }
    va_end(arguments);
    if (kind == 0x33) {
        i = -1;
        if ((*(int*) (action + 0x30) == 0 && *(int*) (action + 0x34) != i) ||
            (*(int*) (action + 0x30) != 0 && *(int*) (action + 0x34) == i)) {
            ReportClientMessage("ch_InsertAction(): move2universe: invalid combination of ids and universeindex");
            fcn_004050c0(action);
            return 0;
        }
    } else if (kind == 0x2d) {
        int x;
        int y;
        int universe;

        if ((x = *(int*) (action + 0x30)) < 0 || x > 256 ||
            (y = *(int*) (action + 0x34)) < 0 || y > 256 ||
            (universe = *(int*) (action + 0x38)) < 0 || universe > 64 ||
            g_10432c0[universe * ch_UNIVERSE_STRIDE + 0x3d5] != 0) {
            fcn_004050c0(action);
            return 0;
        }
        if (*(int*) (*(char**) (object + 0x88) + 0xb0) != 0 &&
            (x > *(int*) (g_10432c0 + universe * ch_UNIVERSE_STRIDE + 0xb4) ||
             y > *(int*) (g_10432c0 + universe * ch_UNIVERSE_STRIDE + 0xb4))) {
            fcn_004050c0(position);
            return 0;
        }
    } else if (kind == 0) {
        *(int*) (action + 0x30) = original_kind;
    }
    action[0x10] = 0;
    fcn_00405180(object, action);
    return action;
}

#undef ch_UNIVERSE_STRIDE
#endif

