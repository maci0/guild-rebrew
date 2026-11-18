
/* Walks the stride-0x44 record array a2[4] while the count the g_6652f8
 * table holds for *a2 has entries left, and reports whether a live (non -1)
 * slot was reached. */
/* ADDRESS: GOLDTL 0x004f1860 */
int __cdecl fcn_004f1860(int* a1, int* a2)
{
	int count;
	int i;
	int* cursor;

	i = 0;
	count = *(int*) (0x6652f8 + *a2 * 4);
	if (count <= 0) {
		return 0;
	}
	cursor = (int*) a2[4];
	do {
		if (*cursor != -1) {
			return 1;
		}
		i++;
		cursor = (int*) ((char*) cursor + 0x44);
	} while (i < count);
	return 0;
}
