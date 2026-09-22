// FUNCTION: GOLDTL 0x41e490
// SIZE: 61

void __cdecl fcn_0041e490(int* p, int* o1, int* o2, int* o3)
{
	int* q;
	int a;
	int b;
	int c;

	a = 0;
	b = 0;
	c = 0;
	if (p != 0) {
		q = (int*) *p;
		if (q != 0) {
			a = q[0];
			b = q[1];
			c = q[2];
		}
	}
	if (o1 != 0) {
		*o1 = a;
	}
	if (o2 != 0) {
		*o2 = b;
	}
	if (o3 != 0) {
		*o3 = c;
	}
}
