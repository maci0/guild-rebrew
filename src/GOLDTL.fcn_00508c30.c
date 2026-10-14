unsigned short __cdecl gm_RandomMod(unsigned short n);

/* ADDRESS: GOLD 0x00505be0 */
/* ADDRESS: GOLDTL 0x00508c30 */
void __cdecl fcn_00508c30(unsigned char n, unsigned char* arr)
{
	unsigned char i;
	int k;
	unsigned char cnt;
	unsigned char a;
	unsigned char b;
	unsigned char t;

	for (i = 0; i < n; i++) {
		arr[i] = i;
	}
	if (n < 2) {
		return;
	}
	k = n / 4 > 1 ? n / 4 : 1;
	i = 0;
	cnt = n / 2 + k;
	while (i < cnt) {
		a = (unsigned char) gm_RandomMod(n);
		b = (unsigned char) gm_RandomMod(n);
		if (a != b) {
			t = arr[a];
			arr[a] = arr[b];
			arr[b] = t;
			i++;
		}
	}
}
