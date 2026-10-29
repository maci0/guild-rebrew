
/* Walks the stride-0x44 record array a2[4] while the count the g_6652f8
 * table holds for *a2 has entries left, and reports whether a live (non -1)
 * slot was reached. */
/* ADDRESS: GOLDTL 0x004f1860 */
int __cdecl fcn_004f1860(int* a1, int* a2)
{
	int n;
	int i;
	int* p;

	i = 0;
	n = *(int*) (0x6652f8 + *a2 * 4);
	if (n <= 0) {
		return 0;
	}
	p = (int*) a2[4];
	do {
		if (*p != -1) {
			return 1;
		}
		i++;
		p = (int*) ((char*) p + 0x44);
	} while (i < n);
	return 0;
}
