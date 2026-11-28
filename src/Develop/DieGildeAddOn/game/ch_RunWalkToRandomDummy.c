#include <string.h>

#include "Develop/DieGildeAddOn/game/game_data.h"

char* __cdecl d3sm_GetObjectSuperMap(char*);
int __cdecl d3_GetContextIndex(int);
#include "Develop/DieGildeAddOn/game/ch_queue.h"
void __cdecl d3_SelectSceneContext(int, int);
char* __cdecl ch_SelectRandomDummy(void);
void __cdecl d3_TransformPoint(char*, char*, float*);
char __cdecl d3sm_3D2SuperMap(char*, float*, int*, int*, float*);



/* Steps a walk-to-exit event: queues a walk to the room's exit cell. */
/* ADDRESS: GOLDTL 0x0040b7f0 */
void __cdecl ch_RunWalkToRandomDummy(char* ev)
{
	char* map;
	char* door;
	char* walk;
	int saved;
	int room;
	int col;
	int row;
	float height;
	float pos[4];

	if (*(int*) (ev + 0xc) != 0) {
		return;
	}
	map = d3sm_GetObjectSuperMap(*(char**) (ev + 0x14));
	saved = d3_CurrentContextIndex;
	room = d3_GetContextIndex(*(int*) (*(char**) (ev + 0x14) + 0x88));
	if (room != *(int*) (ev + 0x30)) {
		ch_RemoveQueueEntry(ev);
		return;
	}
	d3_SelectSceneContext(room, 1);
	door = ch_SelectRandomDummy();
	if (door != 0 && map != 0) {
		d3_TransformPoint(door, door + 0x4c, pos);
		if (d3sm_3D2SuperMap(map, pos, &col, &row, &height)) {
			walk = ch_InsertAction(*(char**) (ev + 0x14), ev, 0x2d, col, row, room);
			*(int*) (walk + 0x160) |= 0x10;
			*(float*) (walk + 0x144) = pos[0];
			*(float*) (walk + 0x148) = pos[1];
			*(float*) (walk + 0x14c) = pos[2];
			strcpy(walk + 0x70, "Walk2RndDummy");
		}
	}
	ch_RemoveQueueEntry(ev);
	d3_SelectSceneContext(saved, 1);
}
