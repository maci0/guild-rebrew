// FUNCTION: GOLDTL 0x5b1960
// SIZE: 32

void __cdecl fcn_0041ddd0(void*);
void __cdecl fcn_005b1960(void* p);

void __cdecl fcn_005b1960(void* p)
{
	void* q;

	q = *(void**) ((char*) p + 0x48);
	if (q != 0) {
		fcn_005b1960(q);
	}
	fcn_0041ddd0(p);
}
