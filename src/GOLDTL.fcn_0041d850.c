// FUNCTION: GOLDTL 0x41d850
// SIZE: 83

void __cdecl DispatchLogOutput(char*, int, int);

void __cdecl fcn_0041d850(void)
{
	int a;

	for (a = 0x677918; a < 0x677948; a += 4) {
		DispatchLogOutput((char*) 0x677d18, *(int*) 0x6b6f50, *(int*) a);
	}
	if (*(unsigned char*) 0x6b6f50 & 8) {
		((void (__stdcall*)(void)) *(void**) 0x662060)();
		*(int*) 0x14ce724 = 0;
	}
	*(int*) 0x6b6f48 = 0;
	*(int*) 0x14ce600 = 0;
	*(int*) 0x6b6f50 = 0;
}
