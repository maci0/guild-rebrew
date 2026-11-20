void __cdecl d2_SetForm(int, int);
void __cdecl io_AppendText(int);
void __cdecl fcn_00471af0(int, int);
extern int* g_665f08; extern char d2_TutorialActive[];

void __cdecl fcn_00471e30(int);
int __cdecl d2_StartTutorial();

/* ADDRESS: GOLDTL 0x005803f0 */
void __cdecl fcn_005803f0(void)
{
	d2_SetForm(*(int*) (*(int*) 0x665f08 + 0x24), 0);
	io_AppendText(0x6811b0);
	fcn_00471af0(*(int*) (*(int*) 0x665f08 + 0x24), 0);
}

/* ADDRESS: GOLDTL 0x005805e0 */
void __cdecl d2_CloseTutorialProgress(void)
{
	int dialog;

	dialog = *(int*) (((char*) g_665f08) + 0x68);
	if (dialog != -1) {
		fcn_00471e30(dialog);
		*(int*) (((char*) g_665f08) + 0x68) = -1;
	}
}

/* ADDRESS: GOLDTL 0x005809d0 */
void __cdecl fcn_005809d0(void)
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
int __cdecl fcn_00580a00(int a1, int a2)
{
	if (a1 != 5) {
		return -2;
	}
	*(int*) 0x6a81dc = *(int*) a2;
	*(char*) 0x6a81e0 = *(char*) (a2 + 4);
	return d2_StartTutorial();
}
