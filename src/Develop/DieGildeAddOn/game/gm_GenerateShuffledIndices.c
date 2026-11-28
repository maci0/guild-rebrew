


unsigned short __cdecl gm_RandomMod(unsigned short n);

/* ADDRESS: GOLDDE 0x004f3e70 */
void __cdecl gm_GenerateShuffledIndices(unsigned char n, int* arr)
{
	int i;
	int j;
	int cnt;
	unsigned int a;
	unsigned int b;
	int t;

	for (i = 0; i < n; i++) {
		arr[i] = i;
	}
	if (n < 2) {
		return;
	}
	cnt = (n >> 1) + ((n & 0xfc) > 4 ? n >> 2 : 1);
	j = 0;
	while (j < cnt) {
		a = gm_RandomMod(n);
		b = gm_RandomMod(n);
		if (a != b) {
			t = arr[a];
			arr[a] = arr[b];
			arr[b] = t;
			j++;
		}
	}
}
