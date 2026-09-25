// FUNCTION: GOLD 0x505ca0
// SIZE: 133
// FUNCTION: GOLDTL 0x00508cf0
// SIZE: 133

unsigned short __cdecl fcn_0042e410(unsigned short n);

void __cdecl fcn_00508cf0(unsigned char n, int* arr)
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
		a = fcn_0042e410(n);
		b = fcn_0042e410(n);
		if (a != b) {
			t = arr[a];
			arr[a] = arr[b];
			arr[b] = t;
			j++;
		}
	}
}
