// FUNCTION: GOLDTL 0x41fbd0

void* __cdecl fcn_004205e0(int);
void __cdecl fcn_0041fc10(void*, int);

void __cdecl fcn_0041fbd0(int a1, int a2)
{
	void* p;

	if (*(int*) 0x6b71a4 != 0) {
		((void (__stdcall*)(int)) *(void**) 0x662074)(0x14cc5a0);
		p = fcn_004205e0(a1);
		if (p != 0) {
			fcn_0041fc10(p, a2);
		}
		((void (__stdcall*)(int)) *(void**) 0x662070)(0x14cc5a0);
	}
}
