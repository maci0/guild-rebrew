// FUNCTION: GOLD 0x5c6680
// FUNCTION: GOLDTL 0x005d2950

int __cdecl abs(int);
#pragma intrinsic(abs)
unsigned char* __cdecl fcn_00508e40(int);
int __cdecl fcn_00508eb0(unsigned short, int);

int __cdecl fcn_005d2950(int a, int b)
{
	unsigned char* p;
	unsigned char* q;

	p = fcn_00508e40(a);
	q = fcn_00508e40(b);
	if (p == 0 || q == 0) {
		return -0x400;
	}
	if (!(p[8] > 0)) {
		return -0x401;
	}
	if (!(q[8] > 0)) {
		return -0x402;
	}
	if (*(int*) (q + 0x5c) != -1 && *(int*) (q + 0x5c) != a) {
		return -0x403;
	}
	if (*(int*) (p + 0x5c) != -1 && *(int*) (p + 0x5c) != b) {
		return -0x404;
	}
	if (p[0x1b1] > 0) {
		return -0x405;
	}
	if (q[0x1b1] > 0) {
		return -0x406;
	}
	return abs(fcn_00508eb0(*(unsigned short*) p, 0) - fcn_00508eb0(*(unsigned short*) q, 0)) < 6;
}
