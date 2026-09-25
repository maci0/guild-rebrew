// FUNCTION: GOLD 0x00576a90
// SIZE: 95
// FUNCTION: GOLDTL 0x57f030
// SIZE: 95

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

extern struct fsm* g_665f08;
/* volatile: the original loads the tick before the state pointer */
extern volatile int g_6b7fac;
extern struct good* g_868050;

int __cdecl fcn_0057f030(int* ev)
{
	if (ev[0] == 0xd && ev[1] != 0 && g_868050[*(unsigned char*) ev[1]].kind == 0xa) {
		g_665f08->state = 0xb;
		g_665f08->next = 0xb;
		g_665f08->since = g_6b7fac;
		return 1;
	}
	return 3;
}
