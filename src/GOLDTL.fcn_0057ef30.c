// FUNCTION: GOLD 0x576990
// SIZE: 256
// FUNCTION: GOLDTL 0x57ef30
// SIZE: 247

// SIZE 0x10
struct fsm {
	int state;
	int next;
	int pad8;
	int since;
};

extern int* g_665f08;
/* volatile: the original loads the tick before the state pointer */
extern int g_6b7fac;

int __cdecl fcn_0057ef30(int* ev)
{
	char* p;

	if (ev[0] == 10) {
		if (ev[2] == 0 && (*(struct fsm**)&g_665f08)->next == 4) {
			(*(struct fsm**)&g_665f08)->state = 9;
			(*(struct fsm**)&g_665f08)->next = 9;
			(*(struct fsm**)&g_665f08)->since = (*(volatile int*)&g_6b7fac);
			return 1;
		}
		if (ev[2] == 1) {
			if ((*(struct fsm**)&g_665f08)->next == 9) {
				(*(struct fsm**)&g_665f08)->state = 4;
				(*(struct fsm**)&g_665f08)->next = 4;
				(*(struct fsm**)&g_665f08)->since = (*(volatile int*)&g_6b7fac);
				return 1;
			}
			if ((*(struct fsm**)&g_665f08)->next == 10) {
				(*(struct fsm**)&g_665f08)->state = 0xb;
				(*(struct fsm**)&g_665f08)->next = 0xb;
				(*(struct fsm**)&g_665f08)->since = (*(volatile int*)&g_6b7fac);
				return 1;
			}
		}
	} else if (ev[0] == 7) {
		p = (char*) ev[1];
		if (p != 0 && (*(struct fsm**)&g_665f08)->next == 9 && p[2] == 5) {
			(*(struct fsm**)&g_665f08)->state = 10;
			(*(struct fsm**)&g_665f08)->next = 10;
			(*(struct fsm**)&g_665f08)->since = (*(volatile int*)&g_6b7fac);
			return 1;
		}
	}
	return 3;
}
