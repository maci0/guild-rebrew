


extern char* sv_SelectedBuilding;
extern int* d2_TutorialState;

/* ADDRESS: GOLDDE 0x00565a20 */
int __cdecl d2_GetTutCh3SubStep(void)
{
	unsigned short* p;
	unsigned short k;
	int v;
	int m;

	p = ((unsigned short*)sv_SelectedBuilding);
	if (p != 0) {
		k = *p;
		v = k;
		if (v >= 0x92 && v <= 0x97) {
			m = *(int*) (((char*)d2_TutorialState) + 0x38);
			if (m == 0) {
				return k == 0x92 ? 0 : 3;
			}
			if (m == 1) {
				return k == 0x95 ? 1 : 4;
			}
			if (m == 2) {
				return m;
			}
		}
	}
	return -1;
}
