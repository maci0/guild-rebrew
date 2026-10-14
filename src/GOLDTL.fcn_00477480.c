

typedef int (__stdcall* fcn_00477480_f)(void*);

void __cdecl fcn_00477480(void)
{
	void* p;

	p = *(void**) 0x7725ec;
	if (p != 0) {
		*(int*) 0x14ce728 = ((fcn_00477480_f) ((int*) *(int*) p)[2])(p);
		*(int*) 0x7725ec = 0;
	}
}
