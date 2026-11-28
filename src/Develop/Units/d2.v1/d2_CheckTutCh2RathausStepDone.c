extern int *d2_TutorialState;

/* ADDRESS: GOLDTL 0x0057f180 */
int __cdecl d2_CheckTutCh2RathausStepDone(int* msg)
{
	short* e;

	if (*msg == 0x19) {
		e = (short*) msg[1];
		if (e != 0 && *e == 0x110) {
			d2_TutorialState[0] = 0xb;
			d2_TutorialState[1] = 0xb;
			d2_TutorialState[3] = *(int*) 0x6b7fac;
			return 1;
		}
	}
	return 3;
}
