extern char* sv_SelectedBuilding;
extern char* sv_SelectedBuilding;



extern int* d2_TutorialState;

/* ADDRESS: GOLDDE 0x00565900 */
int __cdecl d2_GetTutCh5SubStep(void)
{
	unsigned short* p;
	unsigned short k;
	int v;

	p = ((unsigned short*)sv_SelectedBuilding);
	if (p != 0) {
		k = *p;
		v = k;
		if (v >= 0x92 && (v <= 0x97 || v == 0x2db) &&
		    *(int*) ((int) d2_TutorialState + 0x38) == 0) {
			return k != 0x92;
		}
	}
	return -1;
}
