extern char d2_Forms[];
extern char d2_Controls[];
void __cdecl d2_PositionWindow(int, int);

/* ADDRESS: GOLDTL 0x00471db0 */
/* ADDRESS: GOLDDE 0x004652b0 */
void __cdecl d2_PositionFormWindows(int groupIndex, int a1)
{
	char* base;
	int i;
	int id;
	int t;

	i = 0;
	base = (char*) ((int) &d2_Forms + groupIndex * 0x2bc);
	if (*(int*) (base + 0x184) <= 0)
		return;
	for (; i < *(int*) (base + 0x184); i++) {
		id = *(int*) (base + 4 + i * 4);
		t = *(int*) (((int) &d2_Controls + 0x31c) + id * 0x3cc);
		if (*(int*) (*(int*) &d2_Controls + t * 756 + 0x40) == 0) {
			d2_PositionWindow(id, a1);
		}
	}
}
