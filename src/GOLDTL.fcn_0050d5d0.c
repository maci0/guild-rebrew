// FUNCTION: GOLDTL 0x0050d5d0
// SIZE: 102

extern char g_7f4ca0[];

char* __cdecl fcn_005463a0(int a, int b, int c);
char* __cdecl fcn_005462a0(void);

int __cdecl fcn_0050d5d0(int id, char* owner, char** out)
{
	char* p;
	int n;

	n = 0;
	p = fcn_005463a0(1, n, 0x23);
	while (p != 0) {
		if (n >= 9) {
			break;
		}
		if (*(int*) (p + 0xb0) == *(int*) (g_7f4ca0 + 4 + id * 0x21c) && (owner == 0 || *(int*) (p + 0xac) == *(int*) (owner + 1))) {
			out[n++] = p;
		}
		p = fcn_005462a0();
	}
	return n;
}
