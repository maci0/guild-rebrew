
// fcn_00401e50 — call [0x5eb2b0]([0x5f10f8]) unless -1, then reset.

int (__stdcall* fp_5eb2b0)(int);

void __cdecl fcn_00401e50(void)
{
	int h;
	h = *(int*) 0x5f10f8;
	if (h != -1) {
		((int (__stdcall*)(int)) *(void**) 0x5eb2b0)(h);
		*(int*) 0x5f10f8 = 0xffffffff;
	}
}
