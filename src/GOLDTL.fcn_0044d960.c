// FUNCTION: GOLD 0x44f030
// SIZE: 95
// FUNCTION: GOLDTL 0x44d960
// SIZE: 95

int __cdecl fcn_004011a0(int, void*);
char* __cdecl fcn_0064d1a0(char*, int);

void __cdecl fcn_0044d960(int r, int* o)
{
	char buf[0x100];
	char* p;
	char* d;
	char* q;
	char c;

	fcn_004011a0(r, buf);
	p = fcn_0064d1a0(buf, '.');
	if (p != 0) {
		*p = 0;
	}
	q = buf;
	d = (char*) o[4] + o[2] * 0xe0 + 0x40;
	do {
		c = *q++;
		*d++ = c;
	} while (c != 0);
}
