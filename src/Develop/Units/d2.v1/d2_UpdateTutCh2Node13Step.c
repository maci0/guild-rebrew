


extern int* d2_TutorialState;
extern volatile int gm_GameTicks;

/* ADDRESS: GOLDDE 0x005650e0 */
int __cdecl d2_UpdateTutCh2Node13Step(int* m)
{
	if (m[0] == 0x19 && m[1] != 0 && d2_TutorialState[1] == 4) {
		if (*(short*) m[1] == 0x13) {
			d2_TutorialState[0] = 0xa;
			d2_TutorialState[1] = 0xa;
			d2_TutorialState[3] = gm_GameTicks;
			return 1;
		}
	}
	else if (m[0] == 0x1a && m[1] != 0 && *(short*) m[1] == 0x13) {
		d2_TutorialState[0] = 0xb;
		d2_TutorialState[1] = 0xb;
		d2_TutorialState[3] = gm_GameTicks;
		return 1;
	}
	return 3;
}
