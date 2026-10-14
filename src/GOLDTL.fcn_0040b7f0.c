#include <string.h>

extern int g_6b8010;

char* __cdecl fcn_00402610(char*);
int __cdecl fcn_00413190(int);
void __cdecl fcn_004050c0(char*);
void __cdecl fcn_004432d0(int, int);
char* __cdecl fcn_00407330(void);
void __cdecl fcn_00455350(char*, char*, float*);
char __cdecl fcn_0045b990(char*, float*, int*, int*, float*);
char* __cdecl fcn_004051d0(char*, char*, int, ...);

/* ADDRESS: GOLD 0x0040a9c0 */
/* ADDRESS: GOLDTL 0x0040b7f0 */

/* Steps a walk-to-exit event: queues a walk to the room's exit cell. */
void __cdecl fcn_0040b7f0(char* ev)
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
	map = fcn_00402610(*(char**) (ev + 0x14));
	saved = g_6b8010;
	room = fcn_00413190(*(int*) (*(char**) (ev + 0x14) + 0x88));
	if (room != *(int*) (ev + 0x30)) {
		fcn_004050c0(ev);
		return;
	}
	fcn_004432d0(room, 1);
	door = fcn_00407330();
	if (door != 0 && map != 0) {
		fcn_00455350(door, door + 0x4c, pos);
		if (fcn_0045b990(map, pos, &col, &row, &height)) {
			walk = fcn_004051d0(*(char**) (ev + 0x14), ev, 0x2d, col, row, room);
			*(int*) (walk + 0x160) |= 0x10;
			*(float*) (walk + 0x144) = pos[0];
			*(float*) (walk + 0x148) = pos[1];
			*(float*) (walk + 0x14c) = pos[2];
			strcpy(walk + 0x70, "Walk2RndDummy");
		}
	}
	fcn_004050c0(ev);
	fcn_004432d0(saved, 1);
}
