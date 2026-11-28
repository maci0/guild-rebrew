extern int d2_DialogButtonAction;
extern int d2_DialogButtonAction;



void __cdecl d2_TurnBookPagesForward(void);
void __cdecl d2_TurnBookPagesBack(void);

/* ADDRESS: GOLDDE 0x0051d510 */
void __cdecl d2_HandleBookPageButton(void)
{
	int v;

	v = *(int*) ((char*)&d2_DialogButtonAction);
	if (v == 0x767) {
		d2_TurnBookPagesForward();
	} else if (v == 0x768) {
		d2_TurnBookPagesBack();
	}
}
