void* __cdecl fcn_005dfb95(int, void*);
int __cdecl atoi(void*);

void __cdecl fcn_0044ecc0(int a1, char* a2)
{
	void* p;

	p = fcn_005dfb95(0, (void*) 0x5ebb58);
	*(int*) (a2 + 4) = atoi(p);
}
