int __cdecl fcn_0041a950(int a);

/* ADDRESS: GOLDTL 0x0041a8d0 */
int __cdecl fcn_0041a8d0(unsigned int* a, unsigned int* b)
{
	unsigned int x;
	unsigned int y;

	if (a[0] < b[0]) {
		return -1;
	}
	if (a[0] > b[0]) {
		return 1;
	}
	if (a[1] < b[1]) {
		return -1;
	}
	if (a[1] > b[1]) {
		return 1;
	}
	x = fcn_0041a950((int) b[3]);
	y = fcn_0041a950((int) a[3]);
	if (y < x) {
		return -1;
	}
	x = fcn_0041a950((int) b[3]);
	y = fcn_0041a950((int) a[3]);
	if (x < y) {
		return 1;
	}
	return 0;
}
