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


void __cdecl ch_SetPosition(char* a1, float* a2, int flag)
{
	fcn_00438b40(*(char**) (a1 + 0x34), (int*) a2);
#ifdef REBREW_GOLD
	if (flag != 0) {
		fcn_00453270(*(char**) (a1 + 0x34));
	}
#endif
	fcn_004053a0(a1, 0);
	if (*(int*) ((char*) a1 + 0x124) != 0) {
		ch_UpdateAttachedModelPosition(a1, 0);
#ifdef REBREW_GOLD
		if (flag != 0) {
			fcn_00453270(**(char***) (a1 + 0x124));
		}
#endif
	}
	if (*(int*) ((char*) a1 + 0x22c) != 0) {
		ch_Updatelowpoly(a1);
	}
}

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

extern char g_6b5c60[];
D3_OBJECT* __cdecl fcn_00442910(D3_OBJECT*, float*, float*, char*);
void __cdecl fcn_00438ac0(char*, int);
void __cdecl fcn_00404a00(char*, int, ...);
void __cdecl fcn_00404b60(char*, int, ...);

/* ADDRESS: GOLDTL 0x00403880 */
/* ADDRESS: GOLD 0x00403070 */
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

int __cdecl ch_MoveCharacter2Universe(char* obj, void* universe)
{
	char buf[0x100];
	D3_OBJECT* n;

	if (obj != 0 && *(void**) (obj + 0x88) != 0 && universe != 0
	    && fcn_00443900(*(void**) (obj + 0x34), *(void**) (obj + 0x88), universe)) {
		fcn_00438c40(*(void**) (obj + 0x34), g_662d70);
		if (*(void***) (obj + 0x124) != 0) {
			fcn_00443900(**(void***) (obj + 0x124), *(void**) (obj + 0x88), universe);
		}
		if (*(void**) (obj + 0x22c) != 0) {
			fcn_00443900(*(void**) (obj + 0x22c), *(void**) (obj + 0x88), universe);
		}
		*(void**) (obj + 0x88) = universe;
		if (fcn_00413190(universe) == 0) {
			n = *(D3_OBJECT**) (obj + 0x34);
			n->darstellungsflag = g_6752a4;
		} else {
			n = *(D3_OBJECT**) (obj + 0x34);
			n->darstellungsflag = 0;
		}
		if (universe == (void*) g_67a370 && (*(D3_OBJECT**) (obj + 0x34))->kontext == 0) {
			sprintf(buf, "ch_MoveCharacter2Universe(): character deflated, will be inflated:%s", obj + 0x170);
			fcn_00402aa0(obj);
		}
		return 1;
	}
	return 0;
}

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
/* ADDRESS: GOLD 0x004048b0 */
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
        fcn_0041d9e0("ch_InsertAction(): Could not ch_GetFreeQueueEntry()");
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
            fcn_0041d9e0("ch_InsertAction(): move2universe: invalid combination of ids and universeindex");
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
