
// fcn_005316a0 — call [0x5eb25c]([0x6f2588]); call [0x5eb218](0x624944, [0x75e140]).

int (__stdcall* f1_5eb25c)(int);
int (__stdcall* f2_5eb218)(int, int);

void __cdecl fcn_005316a0(void)
{
	((int (__stdcall*)(int)) *(void**) 0x5eb25c)(*(int*) 0x6f2588);
	((int (__stdcall*)(int, int)) *(void**) 0x5eb218)(0x624944, *(int*) 0x75e140);
}
