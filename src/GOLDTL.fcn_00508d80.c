// FUNCTION: GOLD 0x00505d30
// SIZE: 110
// FUNCTION: GOLDTL 0x00508d80
// SIZE: 110

unsigned short __cdecl fcn_0042e410(unsigned short n);

void __cdecl fcn_00508d80(unsigned int n, int* arr)
{
	unsigned int c;
	int cnt;
	int j;
	unsigned int a;
	unsigned int b;
	int t;

	if (n < 2) {
		return;
	}
	c = n >> 2;
	if (c <= 1) {
		c = 1;
	}
	cnt = (n >> 1) + c;
	j = 0;
	while (j < cnt) {
		a = fcn_0042e410((unsigned short) n);
		b = fcn_0042e410((unsigned short) n);
		if (a != b) {
			t = arr[a];
			arr[a] = arr[b];
			arr[b] = t;
			j++;
		}
	}
}
