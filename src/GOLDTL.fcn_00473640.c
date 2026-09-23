// FUNCTION: GOLDTL 0x473640
// SIZE: 26

typedef void (__stdcall* f)(void*, int, int, int);

void __cdecl fcn_00473640(void)
{
	void* obj;

	obj = *(void**) 0x6b5de0;
	(*(f) ((int*) *(int*) obj)[0x40 / 4])(obj, 0, 0, *(int*) 0x77250c + 0x24);
}
