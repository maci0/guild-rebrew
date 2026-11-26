unsigned short __cdecl gm_RandomMod(unsigned short n);

/* ADDRESS: GOLDTL 0x00508c30 */
void __cdecl gm_ShuffleBytes(unsigned char count, unsigned char* arr)
{
	unsigned char i;
	int half_swaps;
	unsigned char swaps;
	unsigned char idx_a;
	unsigned char idx_b;
	unsigned char tmp;

	for (i = 0; i < count; i++) {
		arr[i] = i;
	}
	if (count < 2) {
		return;
	}
	half_swaps = count / 4 > 1 ? count / 4 : 1;
	i = 0;
	swaps = count / 2 + half_swaps;
	while (i < swaps) {
		idx_a = (unsigned char) gm_RandomMod(count);
		idx_b = (unsigned char) gm_RandomMod(count);
		if (idx_a != idx_b) {
			tmp = arr[idx_a];
			arr[idx_a] = arr[idx_b];
			arr[idx_b] = tmp;
			i++;
		}
	}
}
