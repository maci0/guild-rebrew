

typedef void (__stdcall* fcn_0041b7c0_a)(void*);
typedef int (__stdcall* fcn_0041b7c0_b)(void*);

void __cdecl fcn_0041b7c0(void)
{
	void* p;

	p = *(void**) 0x6b5de4;
	if (p != 0) {
		((fcn_0041b7c0_a) ((int*) *(int*) p)[9])(p);
	}
	p = *(void**) 0x6b5df4;
	if (p != 0) {
		*(int*) 0x14ce728 = ((fcn_0041b7c0_b) ((int*) *(int*) p)[2])(p);
		*(int*) 0x6b5df4 = 0;
	}
}
