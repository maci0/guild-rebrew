


#define MINF(a, b) ((a) < (b) ? (a) : (b))
#define MAXF(a, b) ((a) > (b) ? (a) : (b))

unsigned char* __cdecl fcn_00508e40(int h);

int __cdecl fcn_004cd7a0(char* o, char* out)
{
	unsigned char* p;
	int i;
	int f;

	if (out != 0) {
		out[0] = 2;
		out[1] = 0;
		*(int*) (out + 6) = 0;
	}
	p = fcn_00508e40(*(int*) (o + 0x10));
	if (p == 0) {
		return 1;
	}
	i = *(int*) (o + 0x14);
	if (i < 0 || i > 4) {
		return 1;
	}
	f = (p[0x80 + i] + *(int*) (o + 0x18));
	p[0x80 + i] = (unsigned char) (int) MAXF(MINF(f, 252.0f), 0.0f);
	if (out != 0) {
		out[0] = 1;
	}
	return 0;
}
