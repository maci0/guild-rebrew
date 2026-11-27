
/* ADDRESS: GOLDTL 0x00545970 */
int __cdecl gm_GetPlayerOrdinal(int index)
{
	int i;
	int count;

	count = 0;
	for (i = 0; i < 768; i++) {
		if (*(unsigned char*) (0x7f4ca2 + i * 0x21c) == 6) {
			if (i == index) {
				return count;
			}
			count++;
		}
	}
	return -1;
}
