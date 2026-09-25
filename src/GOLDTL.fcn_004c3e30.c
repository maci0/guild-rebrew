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

extern struct node_4c3e30 g_9bade0[0x2000];
extern struct slot_4c3e30 g_fb5760[0x8000];
extern struct node_4c3e30* g_aed200;
extern int g_aed324;
extern char g_1005780;
extern int g_1005768;
extern int g_1005760;

// FUNCTION: GOLDTL 0x4c3e30
// SIZE: 159

void __cdecl fcn_004c3e30(void)
{
	int i;

	for (i = 0; i < 0x2000; i++) {
		g_9bade0[i].used = 0;
		if (i == 0)
			g_9bade0[0].prev = 0;
		else
			g_9bade0[i].prev = &g_9bade0[i - 1];
		if (i < 0x1fff)
			g_9bade0[i].next = &g_9bade0[i + 1];
		else
			g_9bade0[i].next = 0;
	}
	g_aed200 = g_9bade0;
	g_aed324 = 0;
	g_1005780 = 0;
	g_1005768 = 0;
	g_1005760 = 0;
	for (i = 0; i < 0x8000; i++) {
		g_fb5760[i].owner = -1;
		g_fb5760[i].free = 1;
	}
}
