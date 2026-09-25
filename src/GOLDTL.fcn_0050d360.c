// FUNCTION: GOLD 0x00509f20
// SIZE: 81
// FUNCTION: GOLDTL 0x0050d360
// SIZE: 81

extern char g_7f4ca0[];

char* __cdecl fcn_00508e40(int);
void* __cdecl fcn_00502cd0(int, int, int, ...);
void* __cdecl gm_NextEntityQueryMatch(void);

int __cdecl fcn_0050d360(int idx)
{
	char* o;
	int sum;
	char* r;

	o = fcn_00508e40(*(int*) (g_7f4ca0 + 4 + idx * 0x21c));
	if (o == 0) {
		return -1;
	}
	sum = 0;
	r = fcn_00502cd0(*(int*) (o + 0x178), 1, 4, 9);
	if (r) {
		do {
			sum += *(int*) (r + 0xe);
			r = gm_NextEntityQueryMatch();
		} while (r);
	}
	return sum;
}
