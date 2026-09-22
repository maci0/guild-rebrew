// FUNCTION: GOLD 0x0044c510
// SIZE: 25
// fcn_0044c510 — *(void**)0xfba940 = fcn_0042f7e0(a, [0x6333fc]).

int __cdecl fcn_0042f7e0(int, int);

void __cdecl fcn_0044c510(int a)
{
	*(void**) 0xfba940 = (void*) fcn_0042f7e0(a, *(int*) 0x6333fc);
}
