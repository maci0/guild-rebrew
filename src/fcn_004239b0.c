// FUNCTION: GOLDTL 0x4239b0
// SIZE: 36

void* __cdecl fcn_004239b0(void)
{
	char* p;
	void* r;

	r = 0;
	p = *(char**) 0x6b7d68;
	if (p != 0) {
		r = *(void**) (p + 0x3c);
		if (r != 0) {
			while (*(void**) ((char*) r + 0x3c) != 0) {
				r = *(void**) ((char*) r + 0x3c);
			}
		}
	}
	return r;
}
