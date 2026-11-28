
/* ADDRESS: GOLDTL 0x004265f0 */
/* ADDRESS: GOLDDE 0x004210c0 */
int __cdecl evt_MatchTokenPrefix(char* a, char* b)
{
	int i;

	i = 0;
	do {
		if (b[i] == 0) {
			break;
		}
		if (a[i] != b[i]) {
			return 0;
		}
		i++;
	} while (i < 0x80);
	return i;
}
