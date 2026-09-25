// FUNCTION: GOLDTL 0x4ccc90
// SIZE: 155

char* __cdecl fcn_004032b0(char*);

int __cdecl fcn_004ccc90(char* x, char* out)
{
	char* a;
	char* c;
	int i;
	int k;

	a = fcn_004032b0(x + 0x10);
	if (a == 0)
		return 1;
	c = *(char**) (a + 0x128);
	if (c == 0 || c[9] != 0x3a)
		return 2;
	i = 0;
	if (*(char**) (c + 0xf4) != 0) {
		*(int*) (c + 0xf0) = *(int*) (x + 0x2c);
		for (k = *(int*) (x + 0x28); i < 2 && k < *(int*) (c + 0xf0); i++, k++) {
			(*(char**) (c + 0xf4))[k * 2] = x[0x30 + i * 2];
			(*(char**) (c + 0xf4))[k * 2 + 1] = x[0x31 + i * 2];
		}
	}
	if (out != 0) {
		out[0] = 1;
		out[1] = 0;
		*(int*) (out + 6) = 0;
	}
	return 0;
}
