// FUNCTION: GOLD 0x004ccaa0
// SIZE: 101
// FUNCTION: GOLDTL 0x4cd620
// SIZE: 101

#define MIN(a, b) ((a) < (b) ? (a) : (b))
#define MAX(a, b) ((a) < (b) ? (b) : (a))

char* __cdecl fcn_00508e40(int);

int __cdecl fcn_004cd620(char* x, char* out)
{
	char* e;
	int v;

	e = fcn_00508e40(*(int*) (x + 0x10));
	if (out != 0) {
		out[0] = 2;
		out[1] = 0;
		*(int*) (out + 6) = 0;
	}
	if (e == 0)
		return 1;
	v = *(int*) (x + 0x14) + *(int*) (e + 0x194);
	*(int*) (e + 0x194) = MIN(MAX(v, 0), 0x32);
	if (out != 0)
		out[0] = 1;
	return 0;
}
