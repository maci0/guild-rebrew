// FUNCTION: GOLDTL 0x405180
// SIZE: 68

void __cdecl fcn_00405180(void* a1, void* a2)
{
	void* p;
	void* q;

	if (a2 != *(void**) ((char*) a1 + 0x128)) {
		if (*(int*) ((char*) a2 + 0x24) == 0) {
			__asm { int 3 }
		}
		q = *(void**) ((char*) a2 + 0x28);
		if (q != 0 && *(void**) ((char*) q + 0x24) != a2) {
			__asm { int 3 }
		}
	}
	p = *(void**) ((char*) a1 + 0x128);
	while (p != 0) {
		q = *(void**) ((char*) p + 0x28);
		if (q != 0 && *(void**) ((char*) q + 0x14) != a1) {
			__asm { int 3 }
		}
		p = *(void**) ((char*) p + 0x28);
	}
}
