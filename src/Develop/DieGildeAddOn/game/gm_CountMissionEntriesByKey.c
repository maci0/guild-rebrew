extern char gm_MissionSpecKeyView[];

/* ADDRESS: GOLD 0x004b3b40 */
/* ADDRESS: GOLDTL 0x004b3cb0 */
int __cdecl gm_CountMissionEntriesByKey(int key)
{
	int count;
	int p;

	if (key < 0 || key > 5) {
		return -1;
	}
	count = 0;
	for (p = (int) gm_MissionSpecKeyView; p < (int) gm_MissionSpecKeyView + 0x540; p += 0x1c) {
		if (*(int*) p == key) {
			count++;
		}
	}
	return count;
}
