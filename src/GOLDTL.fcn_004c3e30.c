#pragma pack(push, 1)
struct node_4c3e30 {
	char used;
	char data[0x90];
	struct node_4c3e30* prev;
	struct node_4c3e30* next;
};
// SIZE 0x99

struct slot_4c3e30 {
	char free;
	char pad1;
	int owner;
	char pad6[4];
};
// SIZE 0xa
#pragma pack(pop)

extern char g_9bade0[];
#include "client_types.h"
extern cell10_fb5760 g_fb5760[0x8000];
extern char* g_aed200;
extern char* g_aed324;
extern char g_1005780;
extern int g_1005768;
extern int g_1005760;

// FUNCTION: GOLDTL 0x4c3e30

void __cdecl fcn_004c3e30(void)
{
	int i;

	for (i = 0; i < 0x2000; i++) {
		((struct node_4c3e30*)g_9bade0)[i].used = 0;
		if (i == 0)
			((struct node_4c3e30*)g_9bade0)[0].prev = 0;
		else
			((struct node_4c3e30*)g_9bade0)[i].prev = &((struct node_4c3e30*)g_9bade0)[i - 1];
		if (i < 0x1fff)
			((struct node_4c3e30*)g_9bade0)[i].next = &((struct node_4c3e30*)g_9bade0)[i + 1];
		else
			((struct node_4c3e30*)g_9bade0)[i].next = 0;
	}
	(*(struct node_4c3e30**)&g_aed200) = ((struct node_4c3e30*)g_9bade0);
	(*(int*)&g_aed324) = 0;
	g_1005780 = 0;
	g_1005768 = 0;
	g_1005760 = 0;
	for (i = 0; i < 0x8000; i++) {
		((struct slot_4c3e30*)g_fb5760)[i].owner = -1;
		((struct slot_4c3e30*)g_fb5760)[i].free = 1;
	}
}
