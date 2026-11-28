extern int *d2_TutorialState;

#pragma auto_inline(off)
#pragma check_stack(off)

/* ADDRESS: GOLDTL 0x0057f090 */
int __cdecl d2_CheckTutCh2Step2Done(register int* p)
{
	register int v;

	if (*p == 0x17) {
		d2_TutorialState[0] = 10;
		d2_TutorialState[1] = 10;
		v = *(int*) 0x6b7fac;
		d2_TutorialState[3] = v;
		return 1;
	} else if (*p == 0x18) {
		d2_TutorialState[0] = 11;
		d2_TutorialState[1] = 11;
		v = *(int*) 0x6b7fac;
		d2_TutorialState[3] = v;
		return 1;
	}
	return 3;
}
