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
/* ADDRESS: GOLDTL 0x00403880 */
int __cdecl ch_CreateMesh(char* model, char* resource, float* position)
{
    float rotation[4];
    char name[0x100];
    char buffer[0x200];
    char* part;
    char* end;

    rotation[0] = 0.0f;
    rotation[1] = 0.0f;
    rotation[2] = 0.0f;
    rotation[3] = 0.0f;
    if (model == NULL)
        return 0;
    *(D3_OBJECT**) (model + 0x34) = fcn_00442910(NULL, position, rotation, resource);
    *(int*) (model + 0x28) = -1;
    if (*(D3_OBJECT**) (model + 0x34) == NULL) {
        sprintf(buffer, "ch_CreateMesh(): Could not load 3D-Character: %s", resource);
        return 0;
    }
    strcpy(name, resource);
    part = strchr(name, '_');
    if (part != NULL) {
        part++;
        end = strchr(part, '_');
        if (end != NULL)
            *end = 0;
        strcpy(model + 0x130, part);
        *(part - 1) = 0;
        strcpy(model + 0x170, name);
    } else {
        model[0x130] = g_6b5c60[0];
    }
    *(int*) (model + 0x88) = g_67a370;
#ifdef REBREW_GOLD
    (*(D3_OBJECT**) (model + 0x34))->flags2 |= 0x0c;
    (*(D3_OBJECT**) (model + 0x34))->rest &= ~2;
#else
    (*(D3_OBJECT**) (model + 0x34))->flags2 |= 3;
    (*(D3_OBJECT**) (model + 0x34))->flags0 &= ~0x80;
#endif
    (*(D3_OBJECT**) (model + 0x34))->unbekannt_220 = 2;
    (*(D3_OBJECT**) (model + 0x34))->unbekannt_224 = 1;
#ifdef REBREW_GOLD
    (*(D3_OBJECT**) (model + 0x34))->flags3 &= ~4;
    *(float*) ((char*) (*(D3_OBJECT**) (model + 0x34))->zeichendaten + 0x958) = 1.8f;
#else
    (*(D3_OBJECT**) (model + 0x34))->flags3 &= ~1;
    *(float*) ((char*) (*(D3_OBJECT**) (model + 0x34))->zeichendaten + 0x15f8) = 1.8f;
#endif
    *(float*) (model + 0x1a0) = 1.0f;
    *(int*) (model + 0x2c) = -1;
    *(int*) (model + 0x30) = -1;
    strcpy(model + 8, resource);
    (*(D3_OBJECT**) (model + 0x34))->zusatz_flag = 1;
    if (fcn_00413190(*(void**) (model + 0x88)) == 0)
        (*(D3_OBJECT**) (model + 0x34))->darstellungsflag = g_6752a4;
    else
        (*(D3_OBJECT**) (model + 0x34))->darstellungsflag = 0;
    *(int*) ((char*) *(D3_OBJECT**) (model + 0x34) + 0x48) = 0x3000000;
    fcn_004053a0(model, 0);
#ifdef REBREW_GOLD
    fcn_00453270(*(char**) (model + 0x34));
#endif
    fcn_00438ac0(*(char**) (model + 0x34), 1);
    *(int*) (model + 4) = 1;
    if (strstr(model + 8, "RATTE") || strstr(model + 8, "HUND") ||
        strstr(model + 8, "KATZE") || strstr(model + 8, "PFERD")) {
        *(int*) (model + 4) = 2;
        if (strstr(model + 8, "RATTE")) {
            (*(D3_OBJECT**) (model + 0x34))->darstellungsflag = 0;
            (*(D3_OBJECT**) (model + 0x34))->zusatz_flag = 0;
        }
        if (strstr(model + 8, "PFERD")) {
            *(int*) (model + 4) |= 8;
            (*(D3_OBJECT**) (model + 0x34))->darstellungsflag = 0;
        }
    }
    fcn_00404a00(model, 2, "bewegung/gehen", "stehen/stehen_newnoise");
    if (g_6b5c34 != 0 && *(int*) (model + 0x22c) != 0) {
        fcn_00404b60(model, 1, "gehen");
        ch_Updatelowpoly(model);
    }
    *(unsigned short*) (model + 0x8c) |= 0x1000;
    return 1;
}
