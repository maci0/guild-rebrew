// FUNCTION: GOLDTL 0x57f5d0
// SIZE: 297

// SIZE 0x3c
struct fsm {
	int state;
	int next;
	int pad8;
	int since;
	char pad10[0x28];
	int flag;
};

#pragma pack(1)
// SIZE 0x24d
struct good {
	unsigned char kind;
	char pad[0x24c];
};

// SIZE 0x29
struct item {
	unsigned char good;
	char pad1[0x26];
	unsigned short owner;
};
#pragma pack()

extern struct fsm* g_665f08;
/* volatile: the original loads the tick before the state pointer */
extern volatile int g_6b7fac;
extern struct good* g_868050;
extern unsigned short g_774970;

int __cdecl fcn_0057f5d0(int* ev)
{
	struct item* p;

	if (ev[0] == 0x2b && (p = (struct item*) ev[1]) != 0) {
		if (g_868050[p->good].kind == 0x12 && p->owner == g_774970 && g_665f08->flag == 0
		    && (ev[3] == 0x79 || ev[3] == 0x7a || ev[3] == 0x78)) {
			g_665f08->flag = 1;
			g_665f08->next = 0xa;
			g_665f08->state = g_665f08->next;
			g_665f08->since = g_6b7fac;
		}
	} else if (ev[0] == 0x11 && (p = (struct item*) ev[1]) != 0) {
		if (g_868050[p->good].kind == 0x12 && p->owner == g_774970) {
			if (ev[2] == 0 && g_665f08->flag == 0) {
				g_665f08->next = 9;
			}
			if (ev[2] == 1) {
				if (g_665f08->flag == 1) {
					g_665f08->next = 0xb;
				} else {
					g_665f08->next = 4;
				}
			}
			g_665f08->state = g_665f08->next;
			g_665f08->since = g_6b7fac;
			return 1;
		}
	}
	return 3;
}
