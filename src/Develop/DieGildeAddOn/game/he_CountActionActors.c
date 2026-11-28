
// fcn_005241f0 — count != -1 in 8 ints at a+0x8c.

/* ADDRESS: GOLDTL 0x005290b0 */
/* ADDRESS: GOLDDE 0x005122c0 */
int __cdecl he_CountActionActors(char* action)
{
	int i;
	int count;
	count = 0;
	for (i = 0; i < 8; i++) {
		if (*(int*) (action + 0x8c + i * 4) != -1) {
			count++;
		}
	}
	return count;
}

