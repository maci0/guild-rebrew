

typedef int (__stdcall* f)(void*);

void __cdecl fcn_00459a90(char* p)
{
	void* q;

	if (p == 0) {
		return;
	}
	q = *(void**) (p + 4);
	if (q != 0) {
		*(int*) 0x14ce728 = ((f) ((int*) *(int*) q)[2])(q);
		*(int*) (p + 4) = 0;
	}
	q = *(void**) p;
	if (q != 0) {
		*(int*) 0x14ce728 = ((f) ((int*) *(int*) q)[2])(q);
		*(int*) p = 0;
	}
	*(int*) (p + 0xc) = -1;
}
