void __cdecl d2_SetForm(int, int);
void __cdecl io_AppendText(int);
void __cdecl d2_SetFormVisibility(int, int);
extern int* d2_TutorialState; extern char d2_TutorialActive[];

void __cdecl d2_DestroyForm(int);
int __cdecl d2_StartTutorial();

/* ADDRESS: GOLDTL 0x005803f0 */
void __cdecl d2_HideTutorialHint(void)
{
	d2_SetForm(*(int*) (*(int*) 0x665f08 + 0x24), 0);
	io_AppendText(0x6811b0);
	d2_SetFormVisibility(*(int*) (*(int*) 0x665f08 + 0x24), 0);
}

/* ADDRESS: GOLDTL 0x005805e0 */
void __cdecl d2_CloseTutorialProgress(void)
{
	int dialog;

	dialog = *(int*) (((char*) d2_TutorialState) + 0x68);
	if (dialog != -1) {
		d2_DestroyForm(dialog);
		*(int*) (((char*) d2_TutorialState) + 0x68) = -1;
	}
}

/* ADDRESS: GOLDTL 0x005809d0 */
void __cdecl d2_ResetTutorialStep(void)
{
	*(int*) (*(int*) 0x665f08 + 0x1c) = 0;
	*(int*) (*(int*) 0x665f08 + 0x20) = -1;
}

/* ADDRESS: GOLDTL 0x005809f0 */
int __cdecl d2_IsTutorialInactive(void)
{
	return *(int*) &d2_TutorialActive == 0;
}

/* ADDRESS: GOLDTL 0x00580a00 */
int __cdecl d2_StartTutorialWithPages(int count, int flags)
{
	if (count != 5) {
		return -2;
	}
	*(int*) 0x6a81dc = *(int*) flags;
	*(char*) 0x6a81e0 = *(char*) (flags + 4);
	return d2_StartTutorial();
}
