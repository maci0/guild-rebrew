#ifndef D2_DEPENDENCY_NODE_H
#define D2_DEPENDENCY_NODE_H

#include "Develop/client_types.h"

typedef struct DEPENDENCY_DIAGRAM_NODE {
	int item_id;
	int parent_a;
	int parent_b;
	unsigned short depth;
	unsigned short unk_0e;
	int x;
	int y;
	int unk_18;
	int unk_1c;
	int unk_20;
	int unk_24;
	int unk_28;
	int unk_2c;
	unsigned char state;
	unsigned char unk_31[3];
} DEPENDENCY_DIAGRAM_NODE;
// SIZE 0x34

extern Rec34_7f3f00 g_7f3f00[];

#endif
