


extern int* d2_TutorialState;

void __cdecl d2_TurnBookPagesForward(int);
void __cdecl d2_TurnBookPagesBack(int);

/* ADDRESS: GOLDDE 0x00565ac0 */
int __cdecl d2_AdvanceTutCh3BookCue(void)
{
	int* g;

	g = d2_TutorialState;
	if (g[16] == 2 && g[20] != 0) {
		d2_TurnBookPagesForward(g[20]);
		return 0;
	}
	if (g[16] == 3 && g[20] != 0) {
		d2_TurnBookPagesBack(g[20]);
	}
	return 0;
}
