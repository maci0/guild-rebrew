#include <stdio.h>

// SIZE 0x216
struct node_403bc0 {
	char pad0[0x1cc];
	int parent;
	char pad1[0x215 - 0x1d0];
	unsigned char hidden : 1;
	unsigned char lit : 1;
};

extern float g_662d70[4];
extern unsigned char g_6752a4;
extern int g_67a370;

char __cdecl fcn_00443900(void*, int, int);
void __cdecl fcn_00438c40(void*, float*);
int __cdecl fcn_00413190(int);
void __cdecl fcn_00402aa0(char*);

// FUNCTION: GOLDTL 0x403bc0
// SIZE: 284

/* Moves an object's scene nodes to another room. */
int __cdecl fcn_00403bc0(char* obj, int room)
{
	char buf[0x100];
	struct node_403bc0* n;

	if (obj != 0 && *(int*) (obj + 0x88) != 0 && room != 0
	    && fcn_00443900(*(void**) (obj + 0x34), *(int*) (obj + 0x88), room)) {
		fcn_00438c40(*(void**) (obj + 0x34), g_662d70);
		if (*(void***) (obj + 0x124) != 0) {
			fcn_00443900(**(void***) (obj + 0x124), *(int*) (obj + 0x88), room);
		}
		if (*(void**) (obj + 0x22c) != 0) {
			fcn_00443900(*(void**) (obj + 0x22c), *(int*) (obj + 0x88), room);
		}
		*(int*) (obj + 0x88) = room;
		if (fcn_00413190(room) == 0) {
			n = *(struct node_403bc0**) (obj + 0x34);
			n->lit = g_6752a4;
		} else {
			n = *(struct node_403bc0**) (obj + 0x34);
			n->lit = 0;
		}
		if (room == g_67a370 && (*(struct node_403bc0**) (obj + 0x34))->parent == 0) {
			sprintf(buf, "ch_MoveCharacter2Universe(): character deflated, will be inflated:%s", obj + 0x170);
			fcn_00402aa0(obj);
		}
		return 1;
	}
	return 0;
}
