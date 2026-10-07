// FUNCTION: GOLD 0x00417e10
// FUNCTION: GOLDTL 0x4193d0

void* __cdecl fcn_00423460(void*);

void* __cdecl fcn_004193d0(char* p)
{
	void* q;

	if (p == 0) {
		return 0;
	}
	q = *(void**) (p + 0x34);
	if (q == 0) {
		return 0;
	}
	return fcn_00423460(q);
}
