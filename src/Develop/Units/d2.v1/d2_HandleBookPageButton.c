extern int g_100f1dc;
extern int g_100f1dc;



void __cdecl d2_TurnBookPagesForward(void);
void __cdecl d2_TurnBookPagesBack(void);

void __cdecl d2_HandleBookPageButton(void)
{
	int v;

	v = *(int*) ((char*)&g_100f1dc);
	if (v == 0x767) {
		d2_TurnBookPagesForward();
	} else if (v == 0x768) {
		d2_TurnBookPagesBack();
	}
}
