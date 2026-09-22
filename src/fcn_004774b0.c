// FUNCTION: GOLDTL 0x4774b0
// SIZE: 16

typedef void (__stdcall* f)(void*);

void __cdecl fcn_004774b0(void)
{
	void* p;

	p = *(void**) 0x7725ec;
	if (p != 0) {
		(*(f) ((int*) *(int*) p)[0x20 / 4])(p);
	}
}
