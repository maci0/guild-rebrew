char* __cdecl gm_StartFilteredEntitySearch(int, int, int);
char* __cdecl gm_FindNextFilteredEntity(void);

/* Sums the four group scores of city row a0, column a1, and scales by
 * rate/base unless the rate compares equal or unordered. */
/* ADDRESS: GOLD 0x004ff950 */
int __cdecl fcn_004ff950(int a0, int a1)
{
	char* row;
	char* g;
	int sum;
	int i;
	char* e;

	row = (char*) 0x7d6a70 + a1 * 0x80 + a0 * 0x6810;
	g = row + 0x40;
	sum = 0;
	if (*g == 0) {
		return 0;
	}
	for (i = 0; i < 4; i++) {
		if (*g != 0) {
			e = gm_StartFilteredEntitySearch(1, 5, (unsigned char) *g);
			while (e != 0) {
				sum = (int) ((float) sum + *(float*) (g + 4));
				e = gm_FindNextFilteredEntity();
			}
		}
		g += 8;
	}
	sum = (int) ((float) sum * *(double*) 0x5eb7e8);
	if (!(*(float*) (row + 0x24) == *(float*) 0x5eb788)) {
		sum = (int) (*(float*) (row + 0x24) / *(float*) (row + 0x20) * (float) sum);
	}
	return sum;
}
