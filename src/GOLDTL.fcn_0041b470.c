// FUNCTION: GOLDTL 0x41b470
// SIZE: 63

int __cdecl fcn_0064dc43(char*, char*, ...);

char __cdecl fcn_0041b470(char* s, int* v)
{
	char r;

	r = 0;
	if (s != 0 && *s != 0 && v != 0) {
		v[2] = 0;
		r = fcn_0064dc43(s, (char*) 0x677864, v, v + 1, v + 3, v + 2) == 4;
	}
	return r;
}
