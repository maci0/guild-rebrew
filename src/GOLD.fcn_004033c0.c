// GLOBAL: GOLD 0x5ebba4
extern float g_662d70[];
// GLOBAL: GOLD 0x5f122c
extern unsigned char g_6752a4;
// GLOBAL: GOLD 0x5fb5b0
extern int g_67a370;
#include <stdio.h>

// SIZE 0x212
struct node_4033c0 {
	char pad0[0x1cc];
	int parent;
	char pad1[0x211 - 0x1d0];
	unsigned char pad211 : 3;
	unsigned char lit : 1;
};

char __cdecl fcn_00447fd0(void*, int, int);
void __cdecl fcn_0043b820(void*, float*);
int __cdecl fcn_00411be0(int);
void __cdecl fcn_00402540(char*);

// FUNCTION: GOLD 0x4033c0
// SIZE: 285

/* Moves an object's scene nodes to another room. */
int __cdecl fcn_004033c0(char* obj, int room)
{
	char buf[0x100];
	struct node_4033c0* n;

	if (obj != 0 && *(int*) (obj + 0x88) != 0 && room != 0
	    && fcn_00447fd0(*(void**) (obj + 0x34), *(int*) (obj + 0x88), room)) {
		fcn_0043b820(*(void**) (obj + 0x34), g_662d70);
		if (*(void***) (obj + 0x124) != 0) {
			fcn_00447fd0(**(void***) (obj + 0x124), *(int*) (obj + 0x88), room);
		}
		if (*(void**) (obj + 0x22c) != 0) {
			fcn_00447fd0(*(void**) (obj + 0x22c), *(int*) (obj + 0x88), room);
		}
		*(int*) (obj + 0x88) = room;
		if (fcn_00411be0(room) == 0) {
			n = *(struct node_4033c0**) (obj + 0x34);
			n->lit = g_6752a4;
		} else {
			n = *(struct node_4033c0**) (obj + 0x34);
			n->lit = 0;
		}
		if (room == g_67a370 && (*(struct node_4033c0**) (obj + 0x34))->parent == 0) {
			sprintf(buf, "ch_MoveCharacter2Universe(): character deflated, will be inflated:%s", obj + 0x170);
			fcn_00402540(obj);
		}
		return 1;
	}
	return 0;
}
