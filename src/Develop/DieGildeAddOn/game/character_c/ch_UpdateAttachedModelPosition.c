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
void __cdecl ch_UpdateAttachedModelPosition(char* obj, unsigned char force)
{
	char* model;
	char* attachment;
	char* map;
	float position[4];
	float relative[4];
	float rotation[3];
	float dx, dy, dz;
	float distance;
	float scale;
	float angle;
	float height;
	float overlay_height;
	int col, row;
	int cell;

	model = *(char**) (obj + 0x34);
	map = fcn_00402610(obj);
	if (*(char**) (obj + 0x124) == 0) {
		return;
	}
	attachment = **(char***) (obj + 0x124);
	if (fcn_00451840((float*) (model + 0x4c),
	                    (float*) (*(char**) (obj + 0x124) + 4), 0.01f) && !force) {
		return;
	}
	position[0] = *(float*) (*(char**) (obj + 0x34) + 0x78)
	            + *(float*) (*(char**) (obj + 0x34) + 0x4c);
	position[1] = *(float*) (*(char**) (obj + 0x34) + 0x7c)
	            + *(float*) (*(char**) (obj + 0x34) + 0x50);
	position[2] = *(float*) (*(char**) (obj + 0x34) + 0x80)
	            + *(float*) (*(char**) (obj + 0x34) + 0x54);
	dx = position[0] - *(float*) (*(char**) (obj + 0x124) + 4);
	dy = position[1] - *(float*) (*(char**) (obj + 0x124) + 8);
	dz = position[2] - *(float*) (*(char**) (obj + 0x124) + 12);
	distance = (float) sqrt(dz * dz + dy * dy + dx * dx);
	position[0] = (*(float*) (attachment + 0x19c) + *(float*) (attachment + 0x18c))
	            * g_6628a8 + distance * *(float*) (attachment + 0x1ac);
	position[1] = (*(float*) (attachment + 0x1a0) + *(float*) (attachment + 0x190))
	            * g_6628a8 + distance * *(float*) (attachment + 0x1b0);
	position[2] = (*(float*) (attachment + 0x1a4) + *(float*) (attachment + 0x194))
	            * g_6628a8 + distance * *(float*) (attachment + 0x1b4);
	relative[0] = position[0] + *(float*) (attachment + 0x4c);
	relative[1] = position[1] + *(float*) (attachment + 0x50);
	relative[2] = position[2] + *(float*) (attachment + 0x54);
	position[0] = *(float*) (model + 0x4c) - relative[0];
	position[1] = *(float*) (model + 0x50) - relative[1];
	position[2] = *(float*) (model + 0x54) - relative[2];
	scale = 70.0f / (float) sqrt(position[2] * position[2] + position[1] * position[1] + position[0] * position[0]);
	relative[0] = position[0] * scale;
	relative[1] = position[1] * scale;
	relative[2] = position[2] * scale;
	position[0] = *(float*) (model + 0x4c) - relative[0];
	position[1] = *(float*) (model + 0x50) - relative[1];
	position[2] = *(float*) (model + 0x54) - relative[2];
	fcn_00438b40(attachment, (int*) position);
	angle = -(6.2831855f - fcn_00444700(attachment, (float*) (model + 0x4c)));
	*(int*) &rotation[0] = *(int*) (attachment + 0x84);
	*(int*) &rotation[1] = *(int*) (attachment + 0x88);
	*(int*) &rotation[2] = *(int*) (attachment + 0x8c);
	rotation[1] += angle;
	fcn_00438cb0(attachment, rotation);
	if (fcn_0045b990(map, (float*) (attachment + 0x4c), &col, &row, &height)) {
		cell = *(int*) (*(char**) (map + 0x24) + (*(int*) (map + 0x20) * row + col) * 0x1c);
		if ((cell == 0 || cell == 13) && *(char**) (*(char**) (obj + 0x88) + 0xac) == 0) {
			goto cache_position;
		}
		if (*(char**) (*(char**) (obj + 0x88) + 0xac) != 0) {
			fcn_00441720(*(char**) (*(char**) (obj + 0x88) + 0xac),
			            (float*) (attachment + 0x4c), 1, &col, &row, &overlay_height);
		}
		if (cell == 0 || cell == 13 || !(overlay_height - height < -5.0)) {
			height = overlay_height;
		}
		if (!fcn_00413190(*(char**) (obj + 0x88))) {
			height += 3.0f;
		}
		if (force) {
			*(float*) (attachment + 0x50) = height;
		} else {
			*(float*) (attachment + 0x50) += (height - *(float*) (attachment + 0x50)) * 0.25f;
		}
	}
	fcn_00438b40(attachment, (int*) (attachment + 0x4c));
cache_position:
	*(int*) (*(char**) (obj + 0x124) + 4) = *(int*) (model + 0x4c);
	*(int*) (*(char**) (obj + 0x124) + 8) = *(int*) (model + 0x50);
	*(int*) (*(char**) (obj + 0x124) + 12) = *(int*) (model + 0x54);
}
