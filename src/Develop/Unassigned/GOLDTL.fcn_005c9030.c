


#define MIN(a, b) ((a) < (b) ? (a) : (b))
#define MAX(a, b) ((a) > (b) ? (a) : (b))

int __cdecl fcn_005c9030(int lo, int v, int n, int* out)
{
	int hi;

	if (lo < 1 || n < 1) {
		return 0;
	}
	hi = n * 10000 + lo;
	*out = MAX(MIN(v, hi), lo);
	return 1;
}
