// FUNCTION: GOLDTL 0x43c140
// SIZE: 137

char __cdecl fcn_0043c140(int* img, int x, int y, int n)
{
	unsigned char c = 0xff;
	int i;
	int j;
	int off;

	for (j = y; j <= y + n; j++) {
		for (i = x; i <= x + n; i++) {
			off = (img[3] & j) * img[0] + (img[3] & i);
			if (c == 0xff) {
				c = ((unsigned char*) img[5])[off];
			} else if (c != ((unsigned char*) img[5])[off]) {
				return 0;
			}
		}
	}
	return 1;
}
