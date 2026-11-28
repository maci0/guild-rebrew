


extern int* d2_TutorialState;
extern volatile int gm_GameTicks;

int __cdecl d2_UpdateTutCh2Action110Step(int* msg)
{
	short* e;

	if (*msg == 0x1a) {
		e = (short*) msg[1];
		if (e != 0 && *e == 0x110) {
			d2_TutorialState[0] = 0xb;
			d2_TutorialState[1] = 0xb;
			d2_TutorialState[3] = gm_GameTicks;
			return 1;
		}
	}
	return 3;
}
