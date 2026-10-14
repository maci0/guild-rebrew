

typedef int (__stdcall* fcn_0047c450_f)(void*, int, int, int, int, int);

int __cdecl fcn_0047c450(void)
{
	void* obj;

	obj = *(void**) 0x6b5de0;
	return ((fcn_0047c450_f) ((int*) *(int*) obj)[0x5c / 4])(obj, 0x2a000, 0x228, 0x144, 0, 0x772614) >= 0;
}
