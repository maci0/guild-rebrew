

typedef int (__stdcall* fcn_00452340_f)(void*);

void __cdecl fcn_00452340(void)
{
	void* p;

	p = *(void**) 0x104095c;
	*(int*) 0x14ce728 = ((fcn_00452340_f) ((int*) *(int*) p)[2])(p);
	*(int*) 0x104095c = 0;
}
