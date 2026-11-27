#include <stdio.h>
#include <string.h>

// SIZE 0x3dc
struct room_4066d0 {
	char* map;
	char pad[0x3d8];
};

extern char g_1043370[];
#include "Develop/DieGildeAddOn/game/game_data.h"

int __cdecl d3_GetContextIndex(int);
#include "Develop/DieGildeAddOn/game/ch_queue.h"
void __cdecl d3_SelectSceneContext(int, int);
char* __cdecl d3_FindSceneObject(int, int, int, char*);
void __cdecl d3_TransformPoint(char*, char*, float*);
char __cdecl d3sm_SampleHeight(char*, float*, int*, int*, float*);



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
	saved = d3_CurrentContextIndex;
	room = d3_GetContextIndex(*(int*) (obj + 0x88));
	if (room == *(int*) (ev + 0x170)) {
		ch_RemoveQueueEntry(ev);
		return;
	}
	d3_SelectSceneContext(room, 1);
	door = d3_FindSceneObject(0, 0x120, 0, ev + 0x130);
	if (door != 0) {
		map = ((struct room_4066d0*)g_1043370)[room].map;
		d3_TransformPoint(door, door + 0x4c, pos);
		if (d3sm_SampleHeight(map, pos, &col, &row, &height)) {
			ch_InsertAction(obj, ev, 0x2d, col, row, room);
		} else {
			sprintf(msg, "UsingGate: d3sm_3D2SuperMap() failed... scene:%s   object:%s", *(int*) (obj + 0x88), door);
		}
	}
	d3_SelectSceneContext(saved, 1);
	if (*(int*) (*(char**) (obj + 0x34) + 0x218) != 1) {
		ch_InsertAction(obj, ev, 0x38, 0);
	}
	next = ch_InsertAction(obj, ev, 0x33, *(int*) (ev + 0x170), *(int*) (ev + 0x174), *(int*) (ev + 0x178));
	strcpy(next + 0xf0, ev + 0xf0);
	ch_InsertAction(obj, next, 0x38, 1);
	ch_RemoveQueueEntry(ev);
}
