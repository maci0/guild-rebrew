// FUNCTION: GOLDTL 0x420840
// SIZE: 82

void __cdecl fcn_0064e8fa(char*, char*, int);
void __cdecl fcn_00420120(char*, int);

void __cdecl fcn_00420840(char* p)
{
	if (*(int*) 0x6b71a8 != 0) {
		if (p[0x106] == 0) {
			fcn_0064e8fa((char*) 0x6781ec, (char*) 0x678200, 0x2e5);
		}
		((void (__stdcall*)(int)) *(void**) 0x662074)(0x14cc5a0);
		fcn_00420120(p, 0);
		((void (__stdcall*)(int)) *(void**) 0x662070)(0x14cc5a0);
	}
}
