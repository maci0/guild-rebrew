// FUNCTION: GOLDTL 0x4c8a30

int __cdecl fcn_004c4dc0(unsigned char* msg, int serial);
int __cdecl fcn_005015e0(char**, char**, char**, int);

int __cdecl fcn_004c8a30(unsigned char* msg, char* done)
{
	char* a;
	char* b;
	int v;
	unsigned int i;
	unsigned char* p;
	char* base;
	char* dst;
	int type;
	int n;
	unsigned int k;
	unsigned int off;

	v = fcn_004c4dc0(msg, *(int*) (msg + 0x10));
	{
		char* x;

		if (fcn_005015e0(&x, &a, &b, v) == 0) {
			return 1;
		}
		*(int*) (msg + 0x10) = v;
		if (x != 0) {
			base = x;
		} else if (a != 0) {
			base = a;
		} else {
			base = b;
		}
	}
	p = msg + 0x15;
	for (i = 0; i < msg[0x14]; i++) {
		type = (signed char) *p++;
		n = (signed char) *p++;
		off = *(unsigned short*) p;
		p += 2;
		dst = base + off;
		switch (type) {
		case 1:
			for (k = 0; k < (unsigned int) n; k++) {
				*dst += *p;
				p++;
				dst++;
			}
			break;
		case 2:
			for (k = 0; k < (unsigned int) n; k++) {
				*(short*) dst += *(short*) p;
				p += 2;
				dst += 2;
			}
			break;
		case 4:
			for (k = 0; k < (unsigned int) n; k++) {
				*(int*) dst += *(int*) p;
				p += 4;
				dst += 4;
			}
			break;
		}
	}
	if (done != 0) {
		*done = 1;
	}
	return 0;
}
