


// SIZE 0x10
struct fsm {
	int state;
	int next;
	int pad8;
	int since;
};

extern int* d2_TutorialState;
extern volatile int gm_GameTicks;

int __cdecl d2_UpdateTutCh1FocusStep(int* ev)
{
	char* p;

	if (ev[0] == 10) {
		if (ev[2] == 0 && (*(struct fsm**)&d2_TutorialState)->next == 4) {
			(*(struct fsm**)&d2_TutorialState)->state = 9;
			(*(struct fsm**)&d2_TutorialState)->next = 9;
			(*(struct fsm**)&d2_TutorialState)->since = gm_GameTicks;
			return 1;
		}
		if (ev[2] == 1) {
			if ((*(struct fsm**)&d2_TutorialState)->next == 9) {
				(*(struct fsm**)&d2_TutorialState)->state = 4;
				(*(struct fsm**)&d2_TutorialState)->next = 4;
				(*(struct fsm**)&d2_TutorialState)->since = gm_GameTicks;
				return 1;
			}
			if ((*(struct fsm**)&d2_TutorialState)->next == 10) {
				(*(struct fsm**)&d2_TutorialState)->state = 0xb;
				(*(struct fsm**)&d2_TutorialState)->next = 0xb;
				(*(struct fsm**)&d2_TutorialState)->since = gm_GameTicks;
				return 1;
			}
		}
	} else if (ev[0] == 7) {
		p = (char*) ev[1];
		if (p != 0 && (*(struct fsm**)&d2_TutorialState)->next == 9 && p[2] == 5) {
			(*(struct fsm**)&d2_TutorialState)->state = 10;
			(*(struct fsm**)&d2_TutorialState)->next = 10;
			(*(struct fsm**)&d2_TutorialState)->since = gm_GameTicks;
			return 1;
		}
	}
	return 3;
}
