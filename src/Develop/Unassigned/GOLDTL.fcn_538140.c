

// fcn_005316a0 — call [0x6622cc]([0x774940]); call [0x662280](0x6a37fc, [0x7e1f80]).

int (__stdcall* f1_5eb25c)(int);
int (__stdcall* f2_5eb218)(int, int);

void __cdecl fcn_005316a0(void)
{
	((int (__stdcall*)(int)) *(void**) 0x6622cc)(*(int*) 0x774940);
	((int (__stdcall*)(int, int)) *(void**) 0x662280)(0x6a37fc, *(int*) 0x7e1f80);
}
