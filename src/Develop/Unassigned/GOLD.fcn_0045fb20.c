
// fcn_0045fb20 — *(void**)0xfb91b8 = fcn_0042f7e0(a, [0x6333fc]).

int __cdecl fcn_0042f7e0(int, int);

void __cdecl fcn_0045fb20(int a)
{
	*(void**) 0xfb91b8 = (void*) fcn_0042f7e0(a, *(int*) 0x6333fc);
}
