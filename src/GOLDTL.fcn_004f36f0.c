// FUNCTION: GOLD 0x4f15e0
// FUNCTION: GOLDTL 0x004f36f0

int __cdecl fcn_004f3e60(char* e, int* out);
int* __cdecl fcn_004f1a40(char* e);
int* __cdecl fcn_004f1a10(char* e, int* r);
int __cdecl fcn_004f1790(int d, int* s);
int __cdecl fcn_004f3280(char* e, int a, int b, int c, int d);

int __cdecl fcn_004f36f0(char* e)
{
	int* r;
	int* s;
	int k;

	if (fcn_004f3e60(e, 0) != 1) {
		return -1;
	}
	r = fcn_004f1a40(e);
	if (r == 0) {
		return -1;
	}
	s = fcn_004f1a10(e, r);
	if (s == 0) {
		return -1;
	}
	k = fcn_004f1790(*(int*) (e + 0x65), s);
	if (k == -1) {
		return k;
	}
	return fcn_004f3280(e, *s, k, *r, 0x1c);
}
