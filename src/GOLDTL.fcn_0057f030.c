// FUNCTION: GOLD 0x00576a90
// FUNCTION: GOLDTL 0x57f030

// SIZE 0x10
struct fsm {
	int state;
	int next;
	int pad8;
	int since;
};

#pragma pack(1)
// SIZE 0x24d
struct good {
	unsigned char kind;
	char pad[0x24c];
};
#pragma pack()

extern int* g_665f08;
/* volatile: the original loads the tick before the state pointer */
extern int g_6b7fac;
extern unsigned char* g_868050;

int __cdecl fcn_0057f030(int* ev)
{
	if (ev[0] == 0xd && ev[1] != 0 && ((struct good*)g_868050)[*(unsigned char*) ev[1]].kind == 0xa) {
		((struct fsm*)g_665f08)->state = 0xb;
		((struct fsm*)g_665f08)->next = 0xb;
		((struct fsm*)g_665f08)->since = (*(volatile int*)&g_6b7fac);
		return 1;
	}
	return 3;
}
