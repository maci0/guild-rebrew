// FUNCTION: GOLDTL 0x41b250
// SIZE: 52

int __cdecl fcn_0064d41a(char*, char*, ...);

char* __cdecl fcn_0041b250(int* v, char* buf)
{
	char* r;

	r = 0;
	if (v != 0 && buf != 0) {
		fcn_0064d41a(buf, (char*) 0x677864, v[0], v[1], v[3], v[2]);
		r = buf;
	}
	return r;
}
