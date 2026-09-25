// FUNCTION: GOLDTL 0x0050d640
// SIZE: 144

extern char g_7f4ca0[];

char* __cdecl fcn_005463a0(int a, int b, int c);
char* __cdecl fcn_005462a0(void);
char* __cdecl fcn_00503fe0(int a, int b, int c);

int __cdecl fcn_0050d640(int key, char* obj, unsigned int id, char** out)
{
	char* p;
	char* r;
	int n;

	n = 0;
	p = fcn_005463a0(1, n, 0x23);
	while (p != 0) {
		if (n >= 9) {
			break;
		}
		r = fcn_00503fe0(1, 1, *(int*) (p + 0xac));
		if (r != 0 && *(unsigned short*) (r + 0x27) == key && (obj == 0 || obj == r)
		    && (id == 0xffff || *(int*) (g_7f4ca0 + 4 + id * 0x21c) == *(int*) (p + 0xb0))) {
			out[n++] = p;
		}
		p = fcn_005462a0();
	}
	return n;
}
