


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

extern int* g_665f08;
/* volatile: the original loads the tick before the state pointer */
extern int g_6b7fac;
extern unsigned char* g_868050;
extern unsigned short g_774970;

int __cdecl fcn_0057f770(int* ev)
{
	struct item* p;

	if (ev[0] == 0x2b && (p = (struct item*) ev[1]) != 0) {
		if (((struct good*)g_868050)[p->good].kind == 2 && p->owner == g_774970 && (*(struct fsm**)&g_665f08)->flag == 0
		    && (ev[3] == 5 || ev[3] == 2 || ev[3] == 0xd || ev[3] == 8)) {
			(*(struct fsm**)&g_665f08)->flag = 1;
			(*(struct fsm**)&g_665f08)->next = 0xa;
			(*(struct fsm**)&g_665f08)->state = (*(struct fsm**)&g_665f08)->next;
			(*(struct fsm**)&g_665f08)->since = (*(volatile int*)&g_6b7fac);
		}
	} else if (ev[0] == 0x10 && (p = (struct item*) ev[1]) != 0) {
		if (((struct good*)g_868050)[p->good].kind == 2 && p->owner == g_774970) {
			if (ev[2] == 0 && (*(struct fsm**)&g_665f08)->flag == 0) {
				(*(struct fsm**)&g_665f08)->next = 9;
			}
			if (ev[2] == 1) {
				if ((*(struct fsm**)&g_665f08)->flag == 1) {
					(*(struct fsm**)&g_665f08)->next = 0xb;
				} else {
					(*(struct fsm**)&g_665f08)->next = 4;
				}
			}
			(*(struct fsm**)&g_665f08)->state = (*(struct fsm**)&g_665f08)->next;
			(*(struct fsm**)&g_665f08)->since = (*(volatile int*)&g_6b7fac);
			return 1;
		}
	}
	return 3;
}
