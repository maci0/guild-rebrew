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
int __cdecl TakeObjectScript(char** ch, char** ani, int* kind, char** dummy, unsigned char* level, char** func)
{
	char* task;

	if (g_6b7ebc != 0 && *(int (__cdecl**)()) (g_6b7ebc + 0x44) == (int (__cdecl*)()) TakeObjectScript) {
		if (*(int*) (*ch + 0x128) != 0) {
			*(int (__cdecl**)()) (g_6b7e98 + 0xc60) = (int (__cdecl*)()) TakeObjectScript;
		}
		return 0;
	}
	if (*ch == 0) {
		fcn_00425bf0(g_6b7e98, *(int*) (g_6b7e98 + 0x118), "TakeObjectScript(): Invalid character");
		return 1;
	}
	if (*dummy == 0) {
		fcn_00425bf0(g_6b7e98, *(int*) (g_6b7e98 + 0x118), "TakeObjectScript(): Invalid dummy");
		return 1;
	}
	task = fcn_0040c230(*ch, fcn_0040cfb0, *level, 0x31, *kind);
	if (task != 0) {
		strcpy(task + 0xf0, *ani);
		if (*dummy != 0 && *(D3_OBJECT_DRAW_DATA**) (*dummy + 0x1ec) != 0 && (*(D3_OBJECT_DRAW_DATA**) (*dummy + 0x1ec))->teile[0].name != 0) {
			strcpy(task + 0x130, (*(D3_OBJECT_DRAW_DATA**) (*dummy + 0x1ec))->teile[0].name);
		}
		strcpy(task + 0x90, *func);
		*(int*) (task + 0x17c) = g_6791c8;
	}
	if (*(int*) (g_6b7e98 + 0xc84) == 1) {
		*(int (__cdecl**)()) (g_6b7e98 + 0xc60) = (int (__cdecl*)()) TakeObjectScript;
	}
	return 0;
}
