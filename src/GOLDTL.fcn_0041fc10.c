// FUNCTION: GOLDTL 0x41fc10
// SIZE: 98

int __cdecl fcn_0042ae10(int, int);

void __cdecl fcn_0041fc10(char* p, int a2)
{
	if (*(int*) 0x6b71a4 != 0 && p != 0) {
		((void (__stdcall*)(int)) *(void**) 0x662074)(0x14cc5a0);
		*(int*) (p + 0x118) = a2;
		if (*(int*) (p + 0x114) == 0 && p[0x104] != 0) {
			*(int*) (p + 0x11c) = a2;
			if (*(int*) (p + 0x100) != 0) {
				fcn_0042ae10(*(int*) (p + 0x100), a2);
			}
		}
		((void (__stdcall*)(int)) *(void**) 0x662070)(0x14cc5a0);
	}
}
