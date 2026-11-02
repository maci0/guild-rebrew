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
#include "Develop/DieGildeAddOn/game/ch_motion.h"

#include "Develop/Units/d3/d3_object.h"

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
#include "Develop/Units/d3/d3_animation.h"

extern int g_6b5c34;
#include "Develop/Units/d3/d3_camera.h"
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
#include "Develop/DieGildeAddOn/game/ch_queue.h"
#include "Develop/Units/Error/error_message.h"

#ifdef REBREW_GOLD
#define ch_UNIVERSE_STRIDE 0x3e0
#else
#define ch_UNIVERSE_STRIDE 0x3dc
#endif


extern char* g_6b5c20;

CH_QUEUE_SLOT* __cdecl ch_GetFreeQueueEntry(void)
{
	int i;

	for (i = 0; i < 2000;) {
		if (((CH_QUEUE_SLOT*)g_6b5c20)[i++].belegt == 0) {
			break;
		}
	}
	if (i >= 2000) {
		return 0;
	}
	return &((CH_QUEUE_SLOT*)g_6b5c20)[i - 1];
}


int __cdecl ch_RemoveQueueEntry(char* task)
{
    char* next;
    char* previous;
    char* owner;

    if (task == 0) {
        return 0;
    }
    next = *(char**) (task + 0x28);
    if (next == 0) {
        owner = *(char**) (task + 0x14);
        if (owner != 0 && task == *(char**) (owner + 0x128)) {
            *(char**) (owner + 0x128) = next;
            memset(task, 0, 0x194);
            return 1;
        }
    }
    previous = *(char**) (task + 0x24);
    if (previous != 0) {
        *(char**) (previous + 0x28) = next;
    }
    next = *(char**) (task + 0x28);
    if (next != 0) {
        *(char**) (next + 0x24) = previous;
    }
    if (previous == 0) {
        owner = *(char**) (task + 0x14);
        if (owner != 0) {
            *(char**) (owner + 0x128) = next;
        }
    }
    memset(task, 0, 0x194);
    return 1;
}


#include "Develop/Units/m_alloc/m_alloc.h"


int __cdecl ch_ClearActionQueue(void* a1)
{
	void* e;

	e = *(void**) ((char*) a1 + 0x128);
	while (e != 0) {
		if (*(char*) ((char*) e + 9) == 0x2d && *(int*) ((char*) e + 0xf4) != 0) {
			m_FreeTracked((void*) *(int*) ((char*) e + 0xf4));
			*(int*) ((char*) e + 0xf4) = 0;
		}
		ch_RemoveQueueEntry(e);
		e = *(void**) ((char*) a1 + 0x128);
	}
	return 1;
}

/* Original character.c placement is inferred from the ch_ subsystem. */


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
            ch_RemoveQueueEntry(action);
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
            ch_RemoveQueueEntry(action);
            return 0;
        }
        if (*(int*) (*(char**) (object + 0x88) + 0xb0) != 0 &&
            (x > *(int*) (g_10432c0 + universe * ch_UNIVERSE_STRIDE + 0xb4) ||
             y > *(int*) (g_10432c0 + universe * ch_UNIVERSE_STRIDE + 0xb4))) {
            ch_RemoveQueueEntry(position);
            return 0;
        }
    } else if (kind == 0) {
        *(int*) (action + 0x30) = original_kind;
    }
    action[0x10] = 0;
    fcn_00405180(object, action);
    return action;
}

#include "Develop/DieGildeAddOn/game/ch_action.h"

/* Drops an object onto the ground of its map cell; returns the cell type. */
int __cdecl ch_PlaceOnGround(void* object, int force)
{
	char* obj;
	char* map;
	char* node;
	int cell;
	int result;
	int row;
	int col;
	float height;
	float pos[4];

	obj = (char*) object;
	map = fcn_00402610(obj);
	node = *(char**) (obj + 0x34);
	result = 0;
	if (map != 0) {
		*(int*) &pos[0] = *(int*) (node + 0x4c);
		*(int*) &pos[1] = *(int*) (node + 0x50);
		*(int*) &pos[2] = *(int*) (node + 0x54);
		if (fcn_0045b990(map, pos, &col, &row, &height)) {
			cell = *(int*) (*(char**) (map + 0x24) + (*(int*) (map + 0x20) * row + col) * 0x1c);
			if (force != 0 || (cell != 0 && cell != 0xd)) {
				if (*(int*) (*(char**) (obj + 0x88) + 0xac) != 0) {
					fcn_00441720(*(char**) (*(char**) (obj + 0x88) + 0xac), pos, 1, &col, &row, &height);
				}
				if (fcn_00413190(*(void**) (obj + 0x88)) == 0) {
					pos[1] = height + 3.0f;
				} else {
					pos[1] = height;
				}
				fcn_00438b40(node, (int*) pos);
			}
			result = cell;
		} else {
			result = 0;
		}
	}
	return result;
}


int __cdecl ch_ExecuteAction(char* e)
{
	CH_ACTION* t;
	char* s;

	if (*(CH_ACTION**) (e + 0x128) == 0) {
		return 0;
	}
	t = *(CH_ACTION**) (e + 0x128);
	if (t != 0 && t->besitzer != 0 && t->ausfuehren != 0) {
		t->ausfuehren(t);
		t->zustand++;
		if (t->abschluss != 0) {
			s = *(char**) (e + 0x70);
			if (s != 0 && *(int*) (e + 0x80) == 0 &&
			    (int) *(char*) (e + 0x85) != *(unsigned char*) (s + 0x6c) &&
			    *(int*) s >= (int) t->stufe) {
				t->abschluss(t);
				*(char*) (e + 0x85) = *(char*) (*(char**) (e + 0x70) + 0x6c);
			}
		}
	}
	return 1;
}


int __cdecl fcn_00406670(char* p, char* s);


int __cdecl ch_CancelActionQueue(char* e)
{
	CH_ACTION* t;

	if (e == 0) {
		return 0;
	}
	t = *(CH_ACTION**) (e + 0x128);
	if (t == 0) {
		return 0;
	}
	t->unbekannt_190 = 1;
	while (t->naechste != 0) {
		ch_RemoveQueueEntry((char*) t->naechste);
	}
	if ((*(unsigned char*) (e + 0x8c) & 0x10) != 0) {
		fcn_00406670(e, "sitzend/aufstehen");
	}
	return 1;
}


#undef ch_UNIVERSE_STRIDE
#endif

