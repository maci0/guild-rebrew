#include <stdio.h>
#include <string.h>

// SIZE 0x3dc
struct room_4066d0 {
	char* map;
	char pad[0x3d8];
};

extern char g_1043370[];
extern int g_6b8010;

int __cdecl fcn_00413190(int);
#include "Develop/DieGildeAddOn/game/ch_queue.h"
void __cdecl fcn_004432d0(int, int);
char* __cdecl fcn_00445600(int, int, int, char*);
void __cdecl fcn_00455350(char*, char*, float*);
char __cdecl fcn_0045b990(char*, float*, int*, int*, float*);



/* Steps a change-room event: puts the character's exit object into the new
 * room and queues the walk-in events. */
/* ADDRESS: GOLDTL 0x004066d0 */
void __cdecl UsingGate(char* ev)
{
	char* obj;
	char* map;
	char* door;
	char* next;
	int room;
	int saved;
	int col;
	int row;
	float height;
	float pos[4];
	char msg[0x200];

	obj = *(char**) (ev + 0x14);
	if (*(int*) (ev + 0xc) != 0) {
		return;
	}
	saved = g_6b8010;
	room = fcn_00413190(*(int*) (obj + 0x88));
	if (room == *(int*) (ev + 0x170)) {
		fcn_004050c0(ev);
		return;
	}
	fcn_004432d0(room, 1);
	door = fcn_00445600(0, 0x120, 0, ev + 0x130);
	if (door != 0) {
		map = ((struct room_4066d0*)g_1043370)[room].map;
		fcn_00455350(door, door + 0x4c, pos);
		if (fcn_0045b990(map, pos, &col, &row, &height)) {
			ch_InsertAction(obj, ev, 0x2d, col, row, room);
		} else {
			sprintf(msg, "UsingGate: d3sm_3D2SuperMap() failed... scene:%s   object:%s", *(int*) (obj + 0x88), door);
		}
	}
	fcn_004432d0(saved, 1);
	if (*(int*) (*(char**) (obj + 0x34) + 0x218) != 1) {
		ch_InsertAction(obj, ev, 0x38, 0);
	}
	next = ch_InsertAction(obj, ev, 0x33, *(int*) (ev + 0x170), *(int*) (ev + 0x174), *(int*) (ev + 0x178));
	strcpy(next + 0xf0, ev + 0xf0);
	ch_InsertAction(obj, next, 0x38, 1);
	fcn_004050c0(ev);
}
