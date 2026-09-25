// FUNCTION: GOLD 0x00417db0
// SIZE: 25
// FUNCTION: GOLDTL 0x419370
// SIZE: 25

void __cdecl fcn_004237f0(void*);

void __cdecl fcn_00419370(char* p)
{
	void* q;

	if (p == 0) {
		return;
	}
	q = *(void**) (p + 0x34);
	if (q == 0) {
		return;
	}
	fcn_004237f0(q);
}
