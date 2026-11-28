extern char d2_TutorialState[];
extern volatile int gm_GameTicks;

/* ADDRESS: GOLDTL 0x0057f130 */
/* ADDRESS: GOLDDE 0x00564f00 */
int __cdecl d2_CheckTutCh2Step3Done(int* msg)
{
	short* e;

	if (*msg == 0x19) {
		e = (short*) msg[1];
		if (e != 0 && *e == 0x10e) {
			(*(int**) &d2_TutorialState)[0] = 0xb;
			(*(int**) &d2_TutorialState)[1] = 0xb;
			(*(int**) &d2_TutorialState)[3] = gm_GameTicks;
			return 1;
		}
	}
	return 3;
}
